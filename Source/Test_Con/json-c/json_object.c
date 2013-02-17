/*
 * $Id: json_object.c,v 1.17 2006/07/25 03:24:50 mclark Exp $
 *
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "debug.h"
#include "printbuf.h"
#include "linkhash.h"
#include "arraylist.h"
#include "json_object.h"
#include "json_object_private.h"

#if !HAVE_STRNDUP
  wchar_t * strndup(const wchar_t * str, size_t n);
#endif /* !HAVE_STRNDUP */

/* #define REFCOUNT_DEBUG 1 */

const wchar_t *json_number_chars = L"0123456789.+-eE";
const wchar_t *json_hex_chars = L"0123456789abcdef";

#ifdef REFCOUNT_DEBUG
const wchar_t * json_type_name[] = {
  "null",
  "boolean",
  "double",
  "int",
  "object",
  "array",
  "string",
};
#endif /* REFCOUNT_DEBUG */

void json_object_generic_delete(struct json_object* jso);
struct json_object* json_object_new(enum json_type o_type);


/* ref count debugging */

#ifdef REFCOUNT_DEBUG

struct lh_table *json_object_table;

void json_object_init(void) __attribute__ ((constructor));
void json_object_init(void) {
  MC_DEBUG("json_object_init: creating object table\n");
  json_object_table = lh_kptr_table_new(128, L"json_object_table", NULL);
}

void json_object_fini(void) __attribute__ ((destructor));
void json_object_fini(void) {
  struct lh_entry *ent;
  if(MC_GET_DEBUG()) {
    if (json_object_table->count) {
      MC_DEBUG("json_object_fini: %d referenced objects at exit\n",
  	       json_object_table->count);
      lh_foreach(json_object_table, ent) {
        struct json_object* obj = (struct json_object*)ent->v;
        MC_DEBUG("\t%s:%p\n", json_type_name[obj->o_type], obj);
      }
    }
  }
  MC_DEBUG("json_object_fini: freeing object table\n");
  lh_table_free(json_object_table);
}
#endif /* REFCOUNT_DEBUG */


/* string escaping */

int json_escape_str(struct printbuf *pb, wchar_t *str)
{
  int pos = 0, start_offset = 0;
  unsigned long c;
  do {
    c = str[pos];
    switch(c) {
    case '\0':
      break;
    case '\b':
    case '\n':
    case '\r':
    case '\t':
    case '"':
    case '\\':
    case '/':
      if(pos - start_offset > 0)
	printbuf_memappend(pb, str + start_offset, pos - start_offset);
      if(c == '\b') printbuf_memappend(pb, L"\\b", 2);
      else if(c == '\n') printbuf_memappend(pb, L"\\n", 2);
      else if(c == '\r') printbuf_memappend(pb, L"\\r", 2);
      else if(c == '\t') printbuf_memappend(pb, L"\\t", 2);
      else if(c == '"') printbuf_memappend(pb, L"\\\"", 2);
      else if(c == '\\') printbuf_memappend(pb, L"\\\\", 2);
      else if(c == '/') printbuf_memappend(pb, L"\\/", 2);
      start_offset = ++pos;
      break;
    default:
      if(c < ' ') {
	if(pos - start_offset > 0)
	  printbuf_memappend(pb, str + start_offset, pos - start_offset);
	sprintbuf(pb, L"\\u00%c%c",
		  json_hex_chars[c >> 4],
		  json_hex_chars[c & 0xf]);
	start_offset = ++pos;
      } else pos++;
    }
  } while(c);
  if(pos - start_offset > 0)
    printbuf_memappend(pb, str + start_offset, pos - start_offset);
  return 0;
}


/* reference counting */

extern struct json_object* json_object_get(struct json_object *jso)
{
  if(jso) {
    jso->_ref_count++;
  }
  return jso;
}

extern void json_object_put(struct json_object *jso)
{
  if(jso) {
    jso->_ref_count--;
    if(!jso->_ref_count) jso->_delete(jso);
  }
}


/* generic object construction and destruction parts */

void json_object_generic_delete(struct json_object* jso)
{
#ifdef REFCOUNT_DEBUG
  MC_DEBUG("json_object_delete_%s: %p\n",
	   json_type_name[jso->o_type], jso);
  lh_table_delete(json_object_table, jso);
#endif /* REFCOUNT_DEBUG */
  printbuf_free(jso->_pb);
  free(jso);
}

struct json_object* json_object_new(enum json_type o_type)
{
  struct json_object *jso;

  jso = (struct json_object*)calloc(sizeof(struct json_object), 1);
  if(!jso) return NULL;
  jso->o_type = o_type;
  jso->_ref_count = 1;
  jso->_delete = &json_object_generic_delete;
#ifdef REFCOUNT_DEBUG
  lh_table_insert(json_object_table, jso, jso);
  MC_DEBUG("json_object_new_%s: %p\n", json_type_name[jso->o_type], jso);
#endif /* REFCOUNT_DEBUG */
  return jso;
}


/* type checking functions */

int json_object_is_type(struct json_object *jso, enum json_type type)
{
  return (jso->o_type == type);
}

enum json_type json_object_get_type(struct json_object *jso)
{
  return jso->o_type;
}


/* json_object_to_json_string */

const wchar_t * json_object_to_json_string(struct json_object *jso)
{
  if(!jso) return L"null";
  if(!jso->_pb) {
    if(!(jso->_pb = printbuf_new())) return NULL;
  } else {
    printbuf_reset(jso->_pb);
  }
  if(jso->_to_json_string(jso, jso->_pb) < 0) return NULL;
  return jso->_pb->buf;
}


/* json_object_object */

int json_object_object_to_json_string(struct json_object* jso,
					     struct printbuf *pb)
{
  int i=0;
  struct json_object_iter iter;
  sprintbuf(pb, L"{");

  /* CAW: scope operator to make ANSI correctness */
  /* CAW: switched to json_object_object_foreachC which uses an iterator struct */
	json_object_object_foreachC(jso, iter) {
			if(i) sprintbuf(pb, L",");
			sprintbuf(pb, L" \"");
			json_escape_str(pb, iter.key);
			sprintbuf(pb, L"\": ");
			if(iter.val == NULL) sprintbuf(pb, L"null");
			else iter.val->_to_json_string(iter.val, pb);
			i++;
	}

  return sprintbuf(pb, L" }");
}

void json_object_lh_entry_free(struct lh_entry *ent)
{
  free(ent->k);
  json_object_put((struct json_object*)ent->v);
}

void json_object_object_delete(struct json_object* jso)
{
  lh_table_free(jso->o.c_object);
  json_object_generic_delete(jso);
}

struct json_object* json_object_new_object(void)
{
  struct json_object *jso = json_object_new(json_type_object);
  if(!jso) return NULL;
  jso->_delete = &json_object_object_delete;
  jso->_to_json_string = &json_object_object_to_json_string;
  jso->o.c_object = lh_kchar_table_new(JSON_OBJECT_DEF_HASH_ENTRIES,
					NULL, &json_object_lh_entry_free);
  return jso;
}

struct lh_table* json_object_get_object(struct json_object *jso)
{
  if(!jso) return NULL;
  switch(jso->o_type) {
  case json_type_object:
    return jso->o.c_object;
  default:
    return NULL;
  }
}

void json_object_object_add(struct json_object* jso, const wchar_t *key,
			    struct json_object *val)
{
  lh_table_delete(jso->o.c_object, key);
  lh_table_insert(jso->o.c_object, _wcsdup(key), val);
}

struct json_object* json_object_object_get(struct json_object* jso, const wchar_t *key)
{
  return (struct json_object*) lh_table_lookup(jso->o.c_object, key);
}

void json_object_object_del(struct json_object* jso, const wchar_t *key)
{
  lh_table_delete(jso->o.c_object, key);
}


/* json_object_boolean */

int json_object_boolean_to_json_string(struct json_object* jso,
					      struct printbuf *pb)
{
  if(jso->o.c_boolean) return sprintbuf(pb, L"true");
  else return sprintbuf(pb, L"false");
}

struct json_object* json_object_new_boolean(boolean b)
{
  struct json_object *jso = json_object_new(json_type_boolean);
  if(!jso) return NULL;
  jso->_to_json_string = &json_object_boolean_to_json_string;
  jso->o.c_boolean = b;
  return jso;
}

boolean json_object_get_boolean(struct json_object *jso)
{
  if(!jso) return FALSE;
  switch(jso->o_type) {
  case json_type_boolean:
    return jso->o.c_boolean;
  case json_type_int:
    return (jso->o.c_int != 0);
  case json_type_double:
    return (jso->o.c_double != 0);
  case json_type_string:
    return (StrLengthW(jso->o.c_string) != 0);
  default:
    return FALSE;
  }
}


/* json_object_int */

int json_object_int_to_json_string(struct json_object* jso,
					  struct printbuf *pb)
{
  return sprintbuf(pb, L"%d", jso->o.c_int);
}

struct json_object* json_object_new_int(__int64 i)
{
  struct json_object *jso = json_object_new(json_type_int);
  if(!jso) return NULL;
  jso->_to_json_string = &json_object_int_to_json_string;
  jso->o.c_int = i;
  return jso;
}

int json_object_get_int(struct json_object *jso)
{
  int cint;

  if(!jso) return 0;
  switch(jso->o_type) {
  case json_type_int:
    return jso->o.c_int;
  case json_type_double:
    return (int)jso->o.c_double;
  case json_type_boolean:
    return jso->o.c_boolean;
  case json_type_string:
    if(swscanf(jso->o.c_string, L"%d", &cint) == 1) return cint;
  default:
    return 0;
  }
}


/* json_object_double */

int json_object_double_to_json_string(struct json_object* jso,
					     struct printbuf *pb)
{
  return sprintbuf(pb, L"%lf", jso->o.c_double);
}

struct json_object* json_object_new_double(double d)
{
  struct json_object *jso = json_object_new(json_type_double);
  if(!jso) return NULL;
  jso->_to_json_string = &json_object_double_to_json_string;
  jso->o.c_double = d;
  return jso;
}

double json_object_get_double(struct json_object *jso)
{
  double cdouble;

  if(!jso) return 0.0;
  switch(jso->o_type) {
  case json_type_double:
    return jso->o.c_double;
  case json_type_int:
    return jso->o.c_int;
  case json_type_boolean:
    return jso->o.c_boolean;
  case json_type_string:
    if(swscanf(jso->o.c_string, L"%lf", &cdouble) == 1) return cdouble;
  default:
    return 0.0;
  }
}


/* json_object_string */

int json_object_string_to_json_string(struct json_object* jso,
					     struct printbuf *pb)
{
  sprintbuf(pb, L"\"");
  json_escape_str(pb, jso->o.c_string);
  sprintbuf(pb, L"\"");
  return 0;
}

void json_object_string_delete(struct json_object* jso)
{
  free(jso->o.c_string);
  json_object_generic_delete(jso);
}

struct json_object* json_object_new_string(const wchar_t *s)
{
  struct json_object *jso = json_object_new(json_type_string);
  if(!jso) return NULL;
  jso->_delete = &json_object_string_delete;
  jso->_to_json_string = &json_object_string_to_json_string;
  jso->o.c_string = _wcsdup(s);
  return jso;
}

struct json_object* json_object_new_string_len(const wchar_t *s, int len)
{
  struct json_object *jso = json_object_new(json_type_string);
  if(!jso) return NULL;
  jso->_delete = &json_object_string_delete;
  jso->_to_json_string = &json_object_string_to_json_string;
  jso->o.c_string = strndup(s, len);
  return jso;
}

const wchar_t * json_object_get_string(struct json_object *jso)
{
  if(!jso) return NULL;
  switch(jso->o_type) {
  case json_type_string:
    return jso->o.c_string;
  default:
    return json_object_to_json_string(jso);
  }
}


/* json_object_array */

int json_object_array_to_json_string(struct json_object* jso,
					    struct printbuf *pb)
{
  int i;
  sprintbuf(pb, L"[");
  for(i=0; i < json_object_array_length(jso); i++) {
	  struct json_object *val;
	  if(i) { sprintbuf(pb, L", "); }
	  else { sprintbuf(pb, L" "); }

      val = json_object_array_get_idx(jso, i);
	  if(val == NULL) { sprintbuf(pb, L"null"); }
	  else { val->_to_json_string(val, pb); }
  }
  return sprintbuf(pb, L" ]");
}

void json_object_array_entry_free(void *data)
{
  json_object_put((struct json_object*)data);
}

void json_object_array_delete(struct json_object* jso)
{
  array_list_free(jso->o.c_array);
  json_object_generic_delete(jso);
}

struct json_object* json_object_new_array(void)
{
  struct json_object *jso = json_object_new(json_type_array);
  if(!jso) return NULL;
  jso->_delete = &json_object_array_delete;
  jso->_to_json_string = &json_object_array_to_json_string;
  jso->o.c_array = array_list_new(&json_object_array_entry_free);
  return jso;
}

struct array_list* json_object_get_array(struct json_object *jso)
{
  if(!jso) return NULL;
  switch(jso->o_type) {
  case json_type_array:
    return jso->o.c_array;
  default:
    return NULL;
  }
}

int json_object_array_length(struct json_object *jso)
{
  return array_list_length(jso->o.c_array);
}

int json_object_array_add(struct json_object *jso,struct json_object *val)
{
  return array_list_add(jso->o.c_array, val);
}

int json_object_array_put_idx(struct json_object *jso, int idx,
			      struct json_object *val)
{
  return array_list_put_idx(jso->o.c_array, idx, val);
}

struct json_object* json_object_array_get_idx(struct json_object *jso,
					      int idx)
{
  return (struct json_object*)array_list_get_idx(jso->o.c_array, idx);
}

