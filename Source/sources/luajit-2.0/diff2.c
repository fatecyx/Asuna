diff --git a/src/buildvm.c b/src2/buildvm.c
index 122e126..767bcb9 100644
--- a/src/buildvm.c
+++ b/src2/buildvm.c
@@ -109,7 +109,7 @@ static const char *sym_decorate(BuildCtx *ctx,
   const char *symprefix = ctx->mode != BUILD_elfasm ? "_" : "";
 #endif
   sprintf(name, "%s%s%s", symprefix, prefix, suffix);
-  p = strchr(name, '@');
+  p = _mbschr(name, '@');
   if (p) {
     if (!LJ_64 && (ctx->mode == BUILD_coffasm || ctx->mode == BUILD_peobj))
       name[0] = '@';
@@ -332,7 +332,7 @@ static void emit_vmdef(BuildCtx *ctx)
   for (i = 0; irfield_names[i]; i++) {
     char *p;
     lower(buf, irfield_names[i]);
-    p = strchr(buf, '_');
+    p = _mbschr(buf, '_');
     if (p) *p = '.';
     fprintf(ctx->fp, "\"%s\", ", buf);
   }
@@ -378,7 +378,7 @@ static BuildMode parsemode(const char *mode)
 {
   int i;
   for (i = 0; modenames[i]; i++)
-    if (!strcmp(mode, modenames[i]))
+    if (!_mbscmp(mode, modenames[i]))
       return (BuildMode)i;
   usage();
   return (BuildMode)-1;
diff --git a/src/buildvm_fold.c b/src2/buildvm_fold.c
index b43d2c4..f03fca9 100644
--- a/src/buildvm_fold.c
+++ b/src2/buildvm_fold.c
@@ -95,28 +95,28 @@ static uint32_t nexttoken(char **pp, int allowlit, int allowany)
   char *p = *pp;
   if (p) {
     uint32_t i;
-    char *q = strchr(p, ' ');
+    char *q = _mbschr(p, ' ');
     if (q) *q++ = '\0';
     *pp = q;
-    if (allowlit && !strncmp(p, "IRFPM_", 6)) {
+    if (allowlit && !_mbsncmp(p, "IRFPM_", 6)) {
       for (i = 0; irfpm_names[i]; i++)
-	if (!strcmp(irfpm_names[i], p+6))
+	if (!_mbscmp(irfpm_names[i], p+6))
 	  return i;
-    } else if (allowlit && !strncmp(p, "IRFL_", 5)) {
+    } else if (allowlit && !_mbsncmp(p, "IRFL_", 5)) {
       for (i = 0; irfield_names[i]; i++)
-	if (!strcmp(irfield_names[i], p+5))
+	if (!_mbscmp(irfield_names[i], p+5))
 	  return i;
-    } else if (allowlit && !strncmp(p, "IRCALL_", 7)) {
+    } else if (allowlit && !_mbsncmp(p, "IRCALL_", 7)) {
       for (i = 0; ircall_names[i]; i++)
-	if (!strcmp(ircall_names[i], p+7))
+	if (!_mbscmp(ircall_names[i], p+7))
 	  return i;
-    } else if (allowlit && !strncmp(p, "IRCONV_", 7)) {
+    } else if (allowlit && !_mbsncmp(p, "IRCONV_", 7)) {
       for (i = 0; irt_names[i]; i++) {
-	const char *r = strchr(p+7, '_');
-	if (r && !strncmp(irt_names[i], p+7, r-(p+7))) {
+	const char *r = _mbschr(p+7, '_');
+	if (r && !_mbsncmp(irt_names[i], p+7, r-(p+7))) {
 	  uint32_t j;
 	  for (j = 0; irt_names[j]; j++)
-	    if (!strcmp(irt_names[j], r+1))
+	    if (!_mbscmp(irt_names[j], r+1))
 	      return (i << 5) + j;
 	}
       }
@@ -125,11 +125,11 @@ static uint32_t nexttoken(char **pp, int allowlit, int allowany)
 	i = i*10 + (*p - '0');
       if (*p == '\0')
 	return i;
-    } else if (allowany && !strcmp("any", p)) {
+    } else if (allowany && !_mbscmp("any", p)) {
       return allowany;
     } else {
       for (i = 0; ir_names[i]; i++)
-	if (!strcmp(ir_names[i], p))
+	if (!_mbscmp(ir_names[i], p))
 	  return i;
     }
     fprintf(stderr, "Error: bad fold definition token \"%s\" at line %d\n", p, lineno);
@@ -196,9 +196,9 @@ void emit_fold(BuildCtx *ctx)
   while (fgets(buf, sizeof(buf), fp) != NULL) {
     lineno++;
     /* The prefix must be at the start of a line, otherwise it's ignored. */
-    if (!strncmp(buf, FOLDDEF_PREFIX, sizeof(FOLDDEF_PREFIX)-1)) {
+    if (!_mbsncmp(buf, FOLDDEF_PREFIX, sizeof(FOLDDEF_PREFIX)-1)) {
       char *p = buf+sizeof(FOLDDEF_PREFIX)-1;
-      char *q = strchr(p, ')');
+      char *q = _mbschr(p, ')');
       if (p[0] == '(' && q) {
 	p++;
 	*q = '\0';
diff --git a/src/buildvm_lib.c b/src2/buildvm_lib.c
index 8d9bcea..d7daa4c 100644
--- a/src/buildvm_lib.c
+++ b/src2/buildvm_lib.c
@@ -27,7 +27,7 @@ static void libdef_name(const char *p, int kind)
   size_t n = strlen(p);
   if (kind != LIBINIT_STRING) {
     if (n > modnamelen && p[modnamelen] == '_' &&
-	!strncmp(p, modname, modnamelen)) {
+	!_mbsncmp(p, modname, modnamelen)) {
       p += modnamelen+1;
       n -= modnamelen+1;
     }
@@ -97,7 +97,7 @@ static int find_ffofs(BuildCtx *ctx, const char *name)
   int i;
   for (i = 0; i < ctx->nglob; i++) {
     const char *gl = ctx->globnames[i];
-    if (gl[0] == 'f' && gl[1] == 'f' && gl[2] == '_' && !strcmp(gl+3, name)) {
+    if (gl[0] == 'f' && gl[1] == 'f' && gl[2] == '_' && !_mbscmp(gl+3, name)) {
       return (int)((uint8_t *)ctx->glob[i] - ctx->code);
     }
   }
@@ -156,7 +156,7 @@ static uint32_t find_rec(char *name)
   char *p = (char *)obuf;
   uint32_t n;
   for (n = 2; *p; n++) {
-    if (strcmp(p, name) == 0)
+    if (_mbscmp(p, name) == 0)
       return n;
     p += strlen(p)+1;
   }
@@ -178,7 +178,7 @@ static void libdef_rec(BuildCtx *ctx, char *p, int arg)
       fprintf(ctx->fp, ",\n0");
     recffid = ffid;
     if (*p == '.') p = funcname;
-    q = strchr(p, ' ');
+    q = _mbschr(p, ' ');
     if (q) *q++ = '\0';
     n = find_rec(p);
     if (q)
@@ -225,14 +225,14 @@ static void libdef_push(BuildCtx *ctx, char *p, int arg)
 	optr += sizeof(double);
 	return;
       }
-    } else if (!strcmp(p, "lastcl")) {
+    } else if (!_mbscmp(p, "lastcl")) {
       if (optr+1 > obuf+sizeof(obuf)) {
 	fprintf(stderr, "Error: output buffer overflow\n");
 	exit(1);
       }
       *optr++ = LIBINIT_LASTCL;
       return;
-    } else if (len > 4 && !strncmp(p, "top-", 4)) {
+    } else if (len > 4 && !_mbsncmp(p, "top-", 4)) {
       if (optr+2 > obuf+sizeof(obuf)) {
 	fprintf(stderr, "Error: output buffer overflow\n");
 	exit(1);
@@ -322,7 +322,7 @@ void emit_lib(BuildCtx *ctx)
 	p += sizeof(LIBDEF_PREFIX)-1;
 	for (ldh = libdef_handlers; ldh->suffix != NULL; ldh++) {
 	  size_t n, len = strlen(ldh->suffix);
-	  if (!strncmp(p, ldh->suffix, len)) {
+	  if (!_mbsncmp(p, ldh->suffix, len)) {
 	    p += len;
 	    n = ldh->stop ? strcspn(p, ldh->stop) : 0;
 	    if (!p[n]) break;
diff --git a/src/lib_aux.c b/src2/lib_aux.c
index 628d6a5..eba6916 100644
--- a/src/lib_aux.c
+++ b/src2/lib_aux.c
@@ -6,6 +6,7 @@
 ** Copyright (C) 1994-2008 Lua.org, PUC-Rio. See Copyright Notice in lua.h
 */
 
+#include <Windows.h>
 #include <errno.h>
 #include <stdarg.h>
 #include <stdio.h>
@@ -29,7 +30,7 @@ LUALIB_API const char *luaL_findtable(lua_State *L, int idx,
   const char *e;
   lua_pushvalue(L, idx);
   do {
-    e = strchr(fname, '.');
+    e = _mbschr(fname, '.');
     if (e == NULL) e = fname + strlen(fname);
     lua_pushlstring(L, fname, (size_t)(e - fname));
     lua_rawget(L, -2);
@@ -99,7 +100,7 @@ LUALIB_API const char *luaL_gsub(lua_State *L, const char *s,
   size_t l = strlen(p);
   luaL_Buffer b;
   luaL_buffinit(L, &b);
-  while ((wild = strstr(s, p)) != NULL) {
+  while ((wild = _mbsstr(s, p)) != NULL) {
     luaL_addlstring(&b, s, (size_t)(wild - s));  /* push prefix */
     luaL_addstring(&b, r);  /* push replacement in place of pattern */
     s = wild + l;  /* continue after `p' */
@@ -254,6 +255,7 @@ LUALIB_API int luaL_loadfile(lua_State *L, const char *filename)
   FileReaderCtx ctx;
   int status;
   const char *chunkname;
+
   if (filename) {
     ctx.fp = fopen(filename, "rb");
     if (ctx.fp == NULL) {
diff --git a/src/lib_base.c b/src2/lib_base.c
index f897598..332a3fc 100644
--- a/src/lib_base.c
+++ b/src2/lib_base.c
@@ -503,7 +503,7 @@ LJLIB_CF(print)
     }
     if (i)
       putchar('\t');
-    fwrite(str, 1, size, stdout);
+    _write(_fileno(stdout), str, size);
   }
   putchar('\n');
   return 0;
diff --git a/src/lib_debug.c b/src2/lib_debug.c
index 3f1cb8c..fec84a5 100644
--- a/src/lib_debug.c
+++ b/src2/lib_debug.c
@@ -117,24 +117,24 @@ LJLIB_CF(debug_getinfo)
   if (!lua_getinfo(L1, options, &ar))
     lj_err_arg(L, arg+2, LJ_ERR_INVOPT);
   lua_createtable(L, 0, 16);
-  if (strchr(options, 'S')) {
+  if (_mbschr(options, 'S')) {
     settabss(L, "source", ar.source);
     settabss(L, "short_src", ar.short_src);
     settabsi(L, "linedefined", ar.linedefined);
     settabsi(L, "lastlinedefined", ar.lastlinedefined);
     settabss(L, "what", ar.what);
   }
-  if (strchr(options, 'l'))
+  if (_mbschr(options, 'l'))
     settabsi(L, "currentline", ar.currentline);
-  if (strchr(options, 'u'))
+  if (_mbschr(options, 'u'))
     settabsi(L, "nups", ar.nups);
-  if (strchr(options, 'n')) {
+  if (_mbschr(options, 'n')) {
     settabss(L, "name", ar.name);
     settabss(L, "namewhat", ar.namewhat);
   }
-  if (strchr(options, 'L'))
+  if (_mbschr(options, 'L'))
     treatstackoption(L, L1, "activelines");
-  if (strchr(options, 'f'))
+  if (_mbschr(options, 'f'))
     treatstackoption(L, L1, "func");
   return 1;  /* return table */
 }
@@ -222,9 +222,9 @@ static void hookf(lua_State *L, lua_Debug *ar)
 static int makemask(const char *smask, int count)
 {
   int mask = 0;
-  if (strchr(smask, 'c')) mask |= LUA_MASKCALL;
-  if (strchr(smask, 'r')) mask |= LUA_MASKRET;
-  if (strchr(smask, 'l')) mask |= LUA_MASKLINE;
+  if (_mbschr(smask, 'c')) mask |= LUA_MASKCALL;
+  if (_mbschr(smask, 'r')) mask |= LUA_MASKRET;
+  if (_mbschr(smask, 'l')) mask |= LUA_MASKLINE;
   if (count > 0) mask |= LUA_MASKCOUNT;
   return mask;
 }
@@ -284,7 +284,7 @@ LJLIB_CF(debug_debug)
     char buffer[250];
     fputs("lua_debug> ", stderr);
     if (fgets(buffer, sizeof(buffer), stdin) == 0 ||
-	strcmp(buffer, "cont\n") == 0)
+	_mbscmp(buffer, "cont\n") == 0)
       return 0;
     if (luaL_loadbuffer(L, buffer, strlen(buffer), "=(debug command)") ||
 	lua_pcall(L, 0, 0, 0)) {
diff --git a/src/lib_io.c b/src2/lib_io.c
index 7a59cc4..05d3631 100644
--- a/src/lib_io.c
+++ b/src2/lib_io.c
@@ -287,6 +287,27 @@ LJLIB_CF(io_method_flush)		LJLIB_REC(io_flush 0)
   return io_pushresult(L, fflush(io_tofile(L)->fp) == 0, NULL);
 }
 
+__inline int __fastcall my_fseek64(FILE *fp, int64_t offset, int origin)
+{
+    int64_t ret;
+
+    ret = fseek(fp, 0, SEEK_CUR);
+    ret = _lseeki64(_fileno(fp), offset, origin);
+
+    return ret == -1 ? 1 : 0;
+}
+
+__inline int64_t __fastcall my_ftell64(FILE *fp)
+{
+    int ret;
+    fpos_t pos;
+
+    ret = fseek(fp, 0, SEEK_CUR);
+    ret = fgetpos(fp, &pos);
+
+    return ret ? ret : pos;
+}
+
 LJLIB_CF(io_method_seek)
 {
   FILE *fp = io_tofile(L)->fp;
@@ -309,7 +330,7 @@ LJLIB_CF(io_method_seek)
 #if LJ_TARGET_POSIX
   res = fseeko(fp, ofs, opt);
 #elif _MSC_VER >= 1400
-  res = _fseeki64(fp, ofs, opt);
+  res = my_fseek64(fp, ofs, opt);
 #elif defined(__MINGW32__)
   res = fseeko64(fp, ofs, opt);
 #else
@@ -320,7 +341,7 @@ LJLIB_CF(io_method_seek)
 #if LJ_TARGET_POSIX
   ofs = ftello(fp);
 #elif _MSC_VER >= 1400
-  ofs = _ftelli64(fp);
+  ofs = my_ftell64(fp);
 #elif defined(__MINGW32__)
   ofs = ftello64(fp);
 #else
diff --git a/src/lib_jit.c b/src2/lib_jit.c
index 9b28520..00f3949 100644
--- a/src/lib_jit.c
+++ b/src2/lib_jit.c
@@ -458,7 +458,7 @@ static int jitopt_flag(jit_State *J, const char *str)
     size_t len = *(const uint8_t *)lst;
     if (len == 0)
       break;
-    if (strncmp(str, lst+1, len) == 0 && str[len] == '\0') {
+    if (_mbsncmp(str, lst+1, len) == 0 && str[len] == '\0') {
       if (set) J->flags |= opt; else J->flags &= ~opt;
       return 1;  /* Ok. */
     }
@@ -475,7 +475,7 @@ static int jitopt_param(jit_State *J, const char *str)
   for (i = 0; i < JIT_P__MAX; i++) {
     size_t len = *(const uint8_t *)lst;
     lua_assert(len != 0);
-    if (strncmp(str, lst+1, len) == 0 && str[len] == '=') {
+    if (_mbsncmp(str, lst+1, len) == 0 && str[len] == '=') {
       int32_t n = 0;
       const char *p = &str[len+1];
       while (*p >= '0' && *p <= '9')
@@ -590,7 +590,7 @@ static uint32_t jit_cpudetect(lua_State *L)
   if (!(flags & JIT_F_ARMV7)) {
     struct utsname ut;
     uname(&ut);
-    if (strncmp(ut.machine, "armv", 4) == 0) {
+    if (_mbsncmp(ut.machine, "armv", 4) == 0) {
       if (ut.machine[4] >= '7')
 	flags |= JIT_F_ARMV6|JIT_F_ARMV6T2|JIT_F_ARMV7;
       else if (ut.machine[4] == '6')
diff --git a/src/lib_os.c b/src2/lib_os.c
index 7292940..c898cbc 100644
--- a/src/lib_os.c
+++ b/src2/lib_os.c
@@ -162,7 +162,7 @@ LJLIB_CF(os_date)
   }
   if (stm == NULL) {  /* invalid date? */
     setnilV(L->top-1);
-  } else if (strcmp(s, "*t") == 0) {
+  } else if (_mbscmp(s, "*t") == 0) {
     lua_createtable(L, 0, 9);  /* 9 = number of fields */
     setfield(L, "sec", stm->tm_sec);
     setfield(L, "min", stm->tm_min);
diff --git a/src/lib_package.c b/src2/lib_package.c
index cb5f64e..6a43462 100644
--- a/src/lib_package.c
+++ b/src2/lib_package.c
@@ -9,6 +9,7 @@
 #define lib_package_c
 #define LUA_LIB
 
+#include <Windows.h>
 #include "lua.h"
 #include "lauxlib.h"
 #include "lualib.h"
@@ -86,7 +87,7 @@ static void setprogdir(lua_State *L)
   char *lb;
   DWORD nsize = sizeof(buff);
   DWORD n = GetModuleFileNameA(NULL, buff, nsize);
-  if (n == 0 || n == nsize || (lb = strrchr(buff, '\\')) == NULL) {
+  if (n == 0 || n == nsize || (lb = _mbsrchr(buff, '\\')) == NULL) {
     luaL_error(L, "unable to get ModuleFileName");
   } else {
     *lb = '\0';
@@ -271,7 +272,7 @@ static const char *pushnexttemplate(lua_State *L, const char *path)
   const char *l;
   while (*path == *LUA_PATHSEP) path++;  /* skip separators */
   if (*path == '\0') return NULL;  /* no more templates */
-  l = strchr(path, *LUA_PATHSEP);  /* find next separator */
+  l = _mbschr(path, *LUA_PATHSEP);  /* find next separator */
   if (l == NULL) l = path + strlen(path);
   lua_pushlstring(L, path, (size_t)(l - path));  /* template */
   return l;
@@ -324,14 +325,118 @@ static void loaderror(lua_State *L, const char *filename)
 	     lua_tostring(L, 1), filename, lua_tostring(L, -1));
 }
 
+#include "lj_frame.h"
+#include "lj_debug.h"
+
+wchar_t* __fastcall findnamew(const wchar_t *lpFileName)
+{
+    wchar_t ch;
+    wchar_t *pBackSlash, *pSlash, *pszFileName;
+
+    pBackSlash = 0;
+    pSlash = 0;
+    pszFileName = (wchar_t *)lpFileName;
+    for (;;)
+    {
+        ch = *pszFileName++;
+        if (ch == 0)
+            break;
+        if  (ch == '/')
+            pSlash = pszFileName - 1;
+        else if  (ch == '\\')
+            pBackSlash = pszFileName - 1;
+    }
+
+    pBackSlash = max(pBackSlash, pSlash);
+    if  (pBackSlash == 0)
+        pBackSlash = (wchar_t *)lpFileName;
+    else
+        ++pBackSlash;
+
+    return pBackSlash;
+}
+
+const char* getcurchunkname(lua_State *L, int *len)
+{
+    cTValue     *frame, *bottom;
+    GCfunc      *fn;
+    GCstr       *chunkname;
+    int          namelen;
+    const char  *pname;
+
+    bottom = tvref(L->stack);
+    for (frame = L->base - 1; frame > bottom; --frame)
+    {
+        fn = frame_func(frame);
+        if (fn == NULL)
+            continue;
+        if (!isluafunc(fn))
+            continue;
+        if (fn->c.gct != ~LJ_TFUNC)
+            continue;
+
+        chunkname = proto_chunkname(funcproto(fn));
+        namelen = chunkname->len;
+        pname = strdata(chunkname);
+        switch (pname[0])
+        {
+            case '@':
+            case '=':
+                ++pname;
+                --namelen;
+                break;
+        }
+
+//        if ((*(int *)pname & 0xFFFF) == '\\.')
+//            continue;
+
+        if (len != NULL)
+            *len = namelen + 1;
+
+        return pname;
+    }
+
+    return NULL;
+}
+
 static int lj_cf_package_loader_lua(lua_State *L)
 {
+  int result;
+  const char *chunkname;
   const char *filename;
   const char *name = luaL_checkstring(L, 1);
+  wchar_t szCurPath[MAX_PATH], szScriptPath[MAX_PATH];
+
+  szCurPath[0] = 0;
+
+  chunkname = getcurchunkname(L, &result);
+  if (chunkname != NULL)
+  {
+    MultiByteToWideChar(CP_ACP, 0, chunkname, result, szScriptPath, _countof(szScriptPath));
+    *findnamew(szScriptPath) = 0;
+    if (szScriptPath[0] != 0)
+    {
+      GetCurrentDirectoryW(_countof(szCurPath), szCurPath);
+      SetCurrentDirectoryW(szScriptPath);
+    }
+  }
+
   filename = findfile(L, name, "path");
-  if (filename == NULL) return 1;  /* library not found in this path */
-  if (luaL_loadfile(L, filename) != 0)
+  if (filename == NULL && szCurPath[0] != 0)
+  {
+    SetCurrentDirectoryW(szCurPath);
+    szCurPath[0] = 0;
+    filename = findfile(L, name, "path");
+  }
+
+  result = filename == NULL ? 0 : luaL_loadfile(L, filename); /* library not found in this path */
+
+  if (szCurPath[0] != 0)
+    SetCurrentDirectoryW(szCurPath);
+
+  if (result != 0)
     loaderror(L, filename);
+
   return 1;  /* library loaded successfully */
 }
 
@@ -349,7 +454,7 @@ static int lj_cf_package_loader_croot(lua_State *L)
 {
   const char *filename;
   const char *name = luaL_checkstring(L, 1);
-  const char *p = strchr(name, '.');
+  const char *p = _mbschr(name, '.');
   int st;
   if (p == NULL) return 0;  /* is root */
   lua_pushlstring(L, name, (size_t)(p - name));
@@ -463,7 +568,7 @@ static void modinit(lua_State *L, const char *modname)
   lua_setfield(L, -2, "_M");  /* module._M = module */
   lua_pushstring(L, modname);
   lua_setfield(L, -2, "_NAME");
-  dot = strrchr(modname, '.');  /* look for last dot in module name */
+  dot = _mbsrchr(modname, '.');  /* look for last dot in module name */
   if (dot == NULL) dot = modname; else dot++;
   /* set _PACKAGE as package name (full module name minus last part) */
   lua_pushlstring(L, modname, (size_t)(dot - modname));
diff --git a/src/lib_string.c b/src2/lib_string.c
index 5cbe6e4..3731f58 100644
--- a/src/lib_string.c
+++ b/src2/lib_string.c
@@ -478,7 +478,7 @@ static int str_find_aux(lua_State *L, int find)
   else if ((size_t)(init) > l1)
     init = (ptrdiff_t)l1;
   if (find && (lua_toboolean(L, 4) ||  /* explicit request? */
-      strpbrk(p, SPECIALS) == NULL)) {  /* or no special characters? */
+      _mbspbrk(p, SPECIALS) == NULL)) {  /* or no special characters? */
     /* do a plain search */
     const char *s2 = lmemfind(s+init, l1-(size_t)init, p, l2);
     if (s2) {
@@ -689,7 +689,7 @@ static void addquoted(lua_State *L, luaL_Buffer *b, int arg)
 static const char *scanformat(lua_State *L, const char *strfrmt, char *form)
 {
   const char *p = strfrmt;
-  while (*p != '\0' && strchr(FMT_FLAGS, *p) != NULL) p++;  /* skip flags */
+  while (*p != '\0' && _mbschr(FMT_FLAGS, *p) != NULL) p++;  /* skip flags */
   if ((size_t)(p - strfrmt) >= sizeof(FMT_FLAGS))
     lj_err_caller(L, LJ_ERR_STRFMTR);
   if (lj_char_isdigit(uchar(*p))) p++;  /* skip width */
@@ -702,7 +702,7 @@ static const char *scanformat(lua_State *L, const char *strfrmt, char *form)
   if (lj_char_isdigit(uchar(*p)))
     lj_err_caller(L, LJ_ERR_STRFMTW);
   *(form++) = '%';
-  strncpy(form, strfrmt, (size_t)(p - strfrmt + 1));
+  _mbsncpy(form, strfrmt, (size_t)(p - strfrmt + 1));
   form += p - strfrmt + 1;
   *form = '\0';
   return p;
@@ -810,7 +810,7 @@ LJLIB_CF(string_format)
 	continue;
       case 's': {
 	GCstr *str = lj_lib_checkstr(L, arg);
-	if (!strchr(form, '.') && str->len >= 100) {
+	if (!_mbschr(form, '.') && str->len >= 100) {
 	  /* no precision and string is too long to be formatted;
 	     keep original string */
 	  setstrV(L, L->top++, str);
diff --git a/src/lj_api.c b/src2/lj_api.c
index a6fbb1c..b0abf15 100644
--- a/src/lj_api.c
+++ b/src2/lj_api.c
@@ -491,7 +491,7 @@ LUALIB_API int luaL_checkoption(lua_State *L, int idx, const char *def,
   if (s == NULL && (s = def) == NULL)
     lj_err_argt(L, idx, LUA_TSTRING);
   for (i = 0; lst[i]; i++)
-    if (strcmp(lst[i], s) == 0)
+    if (_mbscmp(lst[i], s) == 0)
       return (int)i;
   lj_err_argv(L, idx, LJ_ERR_INVOPTM, s);
 }
diff --git a/src/lj_asm.c b/src2/lj_asm.c
index 204d332..9222649 100644
--- a/src/lj_asm.c
+++ b/src2/lj_asm.c
@@ -210,7 +210,7 @@ static void ra_dprintf(ASMState *as, const char *fmt, ...)
   ra_dbg_mcp = NULL;
   p += sprintf(p, "%08x  \e[36m%04d ", (uintptr_t)as->mcp, as->curins-REF_BIAS);
   for (;;) {
-    const char *e = strchr(fmt, '$');
+    const char *e = _mbschr(fmt, '$');
     if (e == NULL) break;
     memcpy(p, fmt, (size_t)(e-fmt));
     p += e-fmt;
diff --git a/src/lj_clib.c b/src2/lj_clib.c
index ff576d3..10bebce 100644
--- a/src/lj_clib.c
+++ b/src2/lj_clib.c
@@ -47,8 +47,8 @@ LJ_NORET LJ_NOINLINE static void clib_error_(lua_State *L)
 
 static const char *clib_extname(lua_State *L, const char *name)
 {
-  if (!strchr(name, '/')) {
-    if (!strchr(name, '.')) {
+  if (!_mbschr(name, '/')) {
+    if (!_mbschr(name, '.')) {
       name = lj_str_pushf(L, CLIB_SOEXT, name);
       L->top--;
     }
@@ -66,9 +66,9 @@ static const char *clib_resolve_lds(lua_State *L, const char *name)
   FILE *fp = fopen(name, "r");
   if (fp) {
     char *p, *e, buf[256];
-    if (fgets(buf, sizeof(buf), fp) && !strncmp(buf, "/* GNU ld script", 16)) {
+    if (fgets(buf, sizeof(buf), fp) && !_mbsncmp(buf, "/* GNU ld script", 16)) {
       while (fgets(buf, sizeof(buf), fp)) {
-	if (!strncmp(buf, "GROUP", 5) && (p = strchr(buf, '('))) {
+	if (!_mbsncmp(buf, "GROUP", 5) && (p = _mbschr(buf, '('))) {
 	  while (*++p == ' ') ;
 	  for (e = p; *e && *e != ' ' && *e != ')'; e++) ;
 	  fclose(fp);
@@ -87,7 +87,7 @@ static void *clib_loadlib(lua_State *L, const char *name, int global)
 		   RTLD_LAZY | (global?RTLD_GLOBAL:RTLD_LOCAL));
   if (!h) {
     const char *e, *err = dlerror();
-    if (*err == '/' && (e = strchr(err, ':')) &&
+    if (*err == '/' && (e = _mbschr(err, ':')) &&
 	(name = clib_resolve_lds(L, strdata(lj_str_new(L, err, e-err))))) {
       h = dlopen(name, RTLD_LAZY | (global?RTLD_GLOBAL:RTLD_LOCAL));
       if (h) return h;
diff --git a/src/lj_crecord.c b/src2/lj_crecord.c
index 8d2248a..d2b514b 100644
--- a/src/lj_crecord.c
+++ b/src2/lj_crecord.c
@@ -1074,7 +1074,7 @@ void LJ_FASTCALL recff_ffi_string(jit_State *J, RecordFFData *rd)
       tr = crec_ct_tv(J, ctype_get(cts, CTID_P_CVOID), 0, tr, &rd->argv[0]);
     } else {
       tr = crec_ct_tv(J, ctype_get(cts, CTID_P_CCHAR), 0, tr, &rd->argv[0]);
-      trlen = lj_ir_call(J, IRCALL_strlen, tr);
+      trlen = lj_ir_call(J, IRCALL__mbslen, tr);
     }
     J->base[0] = emitir(IRT(IR_XSNEW, IRT_STR), tr, trlen);
   }  /* else: interpreter will throw. */
diff --git a/src/lj_debug.c b/src2/lj_debug.c
index 1c4bac4..8874bce 100644
--- a/src/lj_debug.c
+++ b/src2/lj_debug.c
@@ -292,7 +292,7 @@ void lj_debug_shortname(char *out, GCstr *str)
 {
   const char *src = strdata(str);
   if (*src == '=') {
-    strncpy(out, src+1, LUA_IDSIZE);  /* Remove first char. */
+    _mbsncpy(out, src+1, LUA_IDSIZE);  /* Remove first char. */
     out[LUA_IDSIZE-1] = '\0';  /* Ensures null termination. */
   } else if (*src == '@') {  /* Output "source", or "...source". */
     size_t len = str->len-1;
@@ -309,7 +309,7 @@ void lj_debug_shortname(char *out, GCstr *str)
     strcpy(out, "[string \""); out += 9;
     if (src[len] != '\0') {  /* Must truncate? */
       if (len > LUA_IDSIZE-15) len = LUA_IDSIZE-15;
-      strncpy(out, src, len); out += len;
+      _mbsncpy(out, src, len); out += len;
       strcpy(out, "..."); out += 3;
     } else {
       strcpy(out, src); out += len;
diff --git a/src/lj_ircall.h b/src2/lj_ircall.h
index a1f0b05..66692df 100644
--- a/src/lj_ircall.h
+++ b/src2/lj_ircall.h
@@ -122,7 +122,7 @@ typedef struct CCallInfo {
   _(lj_carith_powi64,	ARG2_64,   N, I64, CCI_NOFPRCLOBBER) \
   _(lj_carith_powu64,	ARG2_64,   N, U64, CCI_NOFPRCLOBBER) \
   _(lj_cdata_setfin,	2,        FN, P32, CCI_L) \
-  _(strlen,		1,         N, INTP, 0) \
+  _(_mbslen,		1,         N, INTP, 0) \
   _(memcpy,		3,         S, PTR, 0) \
   _(memset,		3,         S, PTR, 0)
 #else
diff --git a/src/lj_lex.c b/src2/lj_lex.c
index 00daccd..e9b8be6 100644
--- a/src/lj_lex.c
+++ b/src2/lj_lex.c
@@ -9,6 +9,7 @@
 #define lj_lex_c
 #define LUA_CORE
 
+#include <Windows.h>
 #include "lj_obj.h"
 #include "lj_gc.h"
 #include "lj_err.h"
@@ -290,6 +291,8 @@ static void read_string(LexState *ls, int delim, TValue *tv)
       continue;
       }
     default:
+      if (IsDBCSLeadByte(ls->current))
+        save_and_next(ls);
       save_and_next(ls);
       break;
     }
diff --git a/src/lj_opt_fold.c b/src2/lj_opt_fold.c
index 2ecac2d..e9701a5 100644
--- a/src/lj_opt_fold.c
+++ b/src2/lj_opt_fold.c
@@ -511,7 +511,7 @@ LJFOLDF(kfold_strref_snew)
 }
 
 LJFOLD(CALLN CARG IRCALL_lj_str_cmp)
-LJFOLDF(kfold_strcmp)
+LJFOLDF(kfold__mbscmp)
 {
   if (irref_isk(fleft->op1) && irref_isk(fleft->op2)) {
     GCstr *a = ir_kstr(IR(fleft->op1));
diff --git a/src/lj_parse.c b/src2/lj_parse.c
index f0bb441..465324d 100644
--- a/src/lj_parse.c
+++ b/src2/lj_parse.c
@@ -2312,8 +2312,8 @@ static int predict_next(LexState *ls, FuncState *fs, BCPos pc)
   default:
     return 0;
   }
-  return (name->len == 5 && !strcmp(strdata(name), "pairs")) ||
-	 (name->len == 4 && !strcmp(strdata(name), "next"));
+  return (name->len == 5 && !_mbscmp(strdata(name), "pairs")) ||
+	 (name->len == 4 && !_mbscmp(strdata(name), "next"));
 }
 
 /* Parse 'for' iterator. */
diff --git a/src/lj_str.c b/src2/lj_str.c
index cd3a8b6..dfa74aa 100644
--- a/src/lj_str.c
+++ b/src2/lj_str.c
@@ -326,7 +326,7 @@ const char *lj_str_pushvf(lua_State *L, const char *fmt, va_list argp)
   lj_str_needbuf(L, sb, (MSize)strlen(fmt));
   lj_str_resetbuf(sb);
   for (;;) {
-    const char *e = strchr(fmt, '%');
+    const char *e = _mbschr(fmt, '%');
     if (e == NULL) break;
     addstr(L, sb, fmt, (MSize)(e-fmt));
     /* This function only handles %s, %c, %d, %f and %p formats. */
diff --git a/src/luaconf.h b/src2/luaconf.h
index 4a243ff..e075028 100644
--- a/src/luaconf.h
+++ b/src2/luaconf.h
@@ -8,13 +8,26 @@
 
 #include <limits.h>
 #include <stddef.h>
-
+#include <mbstring.h>
+#include <io.h>
+#define static
 /* Default path for loading Lua and C modules with require(). */
 #if defined(_WIN32)
 /*
 ** In Windows, any exclamation mark ('!') in the path is replaced by the
 ** path of the directory of the executable file of the current process.
 */
+//#define static
+
+//#define strlen    _mbstrlen
+//#define strncpy   _mbsncpy
+//#define strchr    _mbschr
+//#define strrchr   _mbsrchr
+//#define strstr    _mbsstr
+//#define strncmp   _mbsncmp
+//#define strcmp    _mbscmp
+//#define strpbrk   _mbspbrk
+
 #define LUA_LDIR	"!\\lua\\"
 #define LUA_CDIR	"!\\"
 #define LUA_PATH_DEFAULT \
diff --git a/src/luajit.c b/src2/luajit.c
index 17d3b5f..873b38e 100644
--- a/src/luajit.c
+++ b/src2/luajit.c
@@ -6,10 +6,14 @@
 ** Copyright (C) 1994-2008 Lua.org, PUC-Rio. See Copyright Notice in lua.h
 */
 
+#pragma comment(linker,"/ENTRY:main")
+
+#include <Windows.h>
 #include <signal.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <locale.h>
 
 #define luajit_c
 
@@ -203,7 +207,7 @@ static int incomplete(lua_State *L, int status)
     size_t lmsg;
     const char *msg = lua_tolstring(L, -1, &lmsg);
     const char *tp = msg + lmsg - (sizeof(LUA_QL("<eof>")) - 1);
-    if (strstr(msg, LUA_QL("<eof>")) == tp) {
+    if (_mbsstr(msg, LUA_QL("<eof>")) == tp) {
       lua_pop(L, 1);
       return 1;
     }
@@ -270,6 +274,8 @@ static void dotty(lua_State *L)
   progname = oldprogname;
 }
 
+wchar_t* __fastcall findnamew(const wchar_t *lpFileName);
+
 static int handle_script(lua_State *L, char **argv, int n)
 {
   int status;
@@ -277,8 +283,18 @@ static int handle_script(lua_State *L, char **argv, int n)
   int narg = getargs(L, argv, n);  /* collect arguments */
   lua_setglobal(L, "arg");
   fname = argv[n];
-  if (strcmp(fname, "-") == 0 && strcmp(argv[n-1], "--") != 0)
+  if (_mbscmp(fname, "-") == 0 && _mbscmp(argv[n-1], "--") != 0)
     fname = NULL;  /* stdin */
+
+  if (fname != NULL)
+  {
+    wchar_t path[MAX_PATH];
+    MultiByteToWideChar(CP_ACP, 0, fname, -1, path, MAX_PATH);
+    *findnamew(path) = 0;
+    if (path[0] != 0)
+      SetCurrentDirectoryW(path);
+  }
+
   status = luaL_loadfile(L, fname);
   lua_insert(L, -(narg+1));
   if (status == 0)
@@ -297,7 +313,7 @@ static int loadjitmodule(lua_State *L)
   lua_concat(L, 2);
   if (lua_pcall(L, 1, 1, 0)) {
     const char *msg = lua_tostring(L, -1);
-    if (msg && !strncmp(msg, "module ", 7)) {
+    if (msg && !_mbsncmp(msg, "module ", 7)) {
     err:
       l_message(progname,
 		"unknown luaJIT command or jit.* modules not installed");
@@ -318,7 +334,7 @@ static int runcmdopt(lua_State *L, const char *opt)
   int narg = 0;
   if (opt && *opt) {
     for (;;) {  /* Split arguments. */
-      const char *p = strchr(opt, ',');
+      const char *p = _mbschr(opt, ',');
       narg++;
       if (!p) break;
       if (p == opt)
@@ -338,7 +354,7 @@ static int runcmdopt(lua_State *L, const char *opt)
 /* JIT engine control command: try jit library first or load add-on module. */
 static int dojitcmd(lua_State *L, const char *cmd)
 {
-  const char *opt = strchr(cmd, '=');
+  const char *opt = _mbschr(cmd, '=');
   lua_pushlstring(L, cmd, opt ? (size_t)(opt - cmd) : strlen(cmd));
   lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
   lua_getfield(L, -1, "jit");  /* Get jit.* module table. */
@@ -534,7 +550,7 @@ static int pmain(lua_State *L)
   return 0;
 }
 
-int main(int argc, char **argv)
+__forceinline int main2(int argc, char **argv)
 {
   int status;
   struct Smain s;
@@ -551,3 +567,25 @@ int main(int argc, char **argv)
   return (status || s.status) ? EXIT_FAILURE : EXIT_SUCCESS;
 }
 
+typedef struct
+{
+    int newmode;
+} __my_startupinfo;
+
+__declspec(dllimport) void __cdecl __getmainargs (int *argc, char ***argv, char ***envp, int, __my_startupinfo *);
+
+#define getargsA(pargc, pargv) \
+    { \
+        char **__envp__;int __dowildcard = 0;__my_startupinfo _my_startupinfo;\
+        __getmainargs((pargc), (pargv), (&__envp__), __dowildcard, &_my_startupinfo); \
+    }
+
+void __cdecl main(int argc, char **argv)
+{
+    getargsA(&argc, &argv);
+    setlocale(LC_CTYPE, ".936");
+    main2(argc, argv);
+    exit(0);
+}
+
+
diff --git a/src/msvcbuild.bat b/src2/msvcbuild.bat
index 7322919..42b4df1 100644
--- a/src/msvcbuild.bat
+++ b/src2/msvcbuild.bat
@@ -14,13 +14,17 @@
 @if not defined INCLUDE goto :FAIL
 
 @setlocal
-@set LJCOMPILE=cl /nologo /c /MD /O2 /W3 /D_CRT_SECURE_NO_DEPRECATE
-@set LJLINK=link /nologo
+@set LJCOMPILE=cl /nologo /c /MD /O2 /W3 /MP /GL /GS- /Ob1
+@set LJLINK=link /nologo /ltcg /fixed
 @set LJMT=mt /nologo
 @set LJLIB=lib /nologo
 @set DASMDIR=..\dynasm
 @set DASM=lua %DASMDIR%\dynasm.lua
 @set ALL_LIB=lib_base.c lib_math.c lib_bit.c lib_string.c lib_table.c lib_io.c lib_os.c lib_package.c lib_debug.c lib_jit.c lib_ffi.c
+@set INLUCDE=E:\WINDDK\7600.16385.1\INC\CRT;%INCLUDE%
+@set LIB=E:\WINDDK\7600.16385.1\LIB\CRT\I386;%LIB%
+
+del *.pdb
 
 if not exist buildvm_x86.h^
   %DASM% -LN -o buildvm_x86.h buildvm_x86.dasc
@@ -64,7 +68,8 @@ buildvm -m folddef -o lj_folddef.h lj_opt_fold.c
 @if errorlevel 1 goto :BAD
 @goto :MTDLL
 :STATIC
-%LJCOMPILE% /DLUA_BUILD_AS_DLL lj_*.c lib_*.c
+%LJCOMPILE% lj_*.c lib_*.c
+::/DLUA_BUILD_AS_DLL 
 @if errorlevel 1 goto :BAD
 %LJLIB% /OUT:lua51.lib lj_*.obj lib_*.obj
 @if errorlevel 1 goto :BAD
@@ -80,12 +85,12 @@ if exist lua51.dll.manifest^
 
 %LJCOMPILE% luajit.c
 @if errorlevel 1 goto :BAD
-%LJLINK% /out:luajit.exe luajit.obj lua51.lib
+%LJLINK% /out:luajit.exe luajit.obj lua51.lib kernel32.lib
 @if errorlevel 1 goto :BAD
 if exist luajit.exe.manifest^
   %LJMT% -manifest luajit.exe.manifest -outputresource:luajit.exe
 
-@del *.obj *.manifest buildvm.exe
+@del *.obj *.manifest buildvm.exe *.lib *.exp
 @echo.
 @echo === Successfully built LuaJIT ===
 
