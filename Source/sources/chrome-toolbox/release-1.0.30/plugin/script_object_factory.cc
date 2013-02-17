#include "script_object_factory.h"

namespace {

NPObject* Allocate(NPP npp, NPClass *aClass) {
  return NULL;
}

void Deallocate(NPObject *npobj) {
  ScriptObjectBase* pObject = (ScriptObjectBase*)npobj;
  pObject->Deallocate();
}

void Invalidate(NPObject *npobj) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  object->Invalidate();
}

bool HasMethod(NPObject *npobj, NPIdentifier name) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->HasMethod(name);
}

bool Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args,
            uint32_t argCount, NPVariant *result) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->Invoke(name, args, argCount, result);
}

bool InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount,
                   NPVariant *result) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->InvokeDefault(args, argCount, result);
}

bool HasProperty(NPObject *npobj, NPIdentifier name) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->HasProperty(name);
}

bool GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->GetProperty(name, result);
}

bool SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->SetProperty(name, value);
}

bool RemoveProperty(NPObject *npobj, NPIdentifier name) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->RemoveProperty(name);
}

bool Enumerate(NPObject *npobj, NPIdentifier **value, uint32_t *count) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->Enumerate(value, count);
}

bool Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, 
               NPVariant *result) {
  ScriptObjectBase* object = (ScriptObjectBase*)npobj;
  return object->Construct(args, argCount, result);
}

NPClass npclass_ = {
  NP_CLASS_STRUCT_VERSION,
  Allocate,
  Deallocate,
  Invalidate,
  HasMethod,
  Invoke,
  InvokeDefault,
  HasProperty,
  GetProperty,
  SetProperty,
  RemoveProperty,
  Enumerate,
  Construct
};

}

ScriptObjectBase* ScriptObjectFactory::CreateObject(NPP npp,
    NPAllocateFunctionPtr allocate) {
  npclass_.allocate = allocate;
  ScriptObjectBase* object = (ScriptObjectBase*)NPN_CreateObject(npp, 
                                                                 &npclass_);
  if (object) {
    object->InitHandler();
  }
  return object;
}
