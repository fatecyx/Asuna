#ifndef _CG_INTERFACE_H_b287d2b7_4f81_49b6_8890_5cdbff338740
#define _CG_INTERFACE_H_b287d2b7_4f81_49b6_8890_5cdbff338740

#include "pragma_once.h"
#include "CG_Types.h"

#define CG_METHOD_CALLTYPE STDCALL

#if !defined(interface)
    #define interface struct
#endif


#if CPP_DEFINED

#define CG_INTERFACE(iface)           interface NOVTABLE iface
#define CG_INTERFACE_(iface, ...)     interface NOVTABLE iface : public __VA_ARGS__

#define CG_METHOD(method)           virtual CGSTATUS    CG_METHOD_CALLTYPE method
#define CG_METHOD_TYPE(type,method) virtual type        CG_METHOD_CALLTYPE method

#elif   // CPP_DEFINED

#define CG_METHOD(method)           CGSTATUS    (CG_METHOD_CALLTYPE * method)
#define CG_METHOD_TYPE(type,method) type        (CG_METHOD_CALLTYPE * method)

#define CG_INTERFACE(iface)    typedef interface iface { \
                                    struct iface##Vtbl FAR* Function; \
                                } iface; \
                                typedef struct iface##Vtbl iface##Vtbl; \
                                struct iface##Vtbl

#define CG_INTERFACE_(iface, ...)     CG_INTERFACE(iface)

#endif  // CPP_DEFINED

#define CG_INTERFACE(iface)           interface NOVTABLE iface

#define CG_METHODIMPL            CGSTATUS    CG_METHOD_CALLTYPE
#define CG_METHODIMPL_TYPE(type) type        CG_METHOD_CALLTYPE

CG_INTERFACE(ICGUnknown)
{
    CG_METHOD(QueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, AddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, Release)  (THIS) PURE;
};

CG_INTERFACE(ICGNonDelegatingUnknown)
{
    CG_METHOD(NonDelegatingQueryInterface)       (THIS_ REFIID iid, PVOID *ppvObject) PURE;
    CG_METHOD_TYPE(ULONG, NonDelegatingAddRef)   (THIS) PURE;
    CG_METHOD_TYPE(ULONG, NonDelegatingRelease)  (THIS) PURE;
};

class CCGUnknownBase : public ICGNonDelegatingUnknown
{
protected:
    ULONG       m_RefCount;
    ICGUnknown *m_pUnknownOuter;

public:
    CCGUnknownBase()
    {
        m_RefCount = 1;
    }

    // ICGNonDelegatingUnknown
    CG_METHODIMPL_TYPE(ULONG) NonDelegatingAddRef()
    {
        return _InterlockedIncrement((PLONG)&m_RefCount);
    }

    CG_METHODIMPL_TYPE(ULONG) NonDelegatingRelease()
    {
        return _InterlockedDecrement((PLONG)&m_RefCount);
    }

    // IUnknown
    CG_METHODIMPL QueryInterface(REFIID iid, PVOID *ppvObject)
    {
        return m_pUnknownOuter->QueryInterface(iid, ppvObject);
    }

    CG_METHODIMPL_TYPE(ULONG) AddRef()
    {
        return m_pUnknownOuter->AddRef();
    }

    CG_METHODIMPL_TYPE(ULONG) Release()
    {
        return m_pUnknownOuter->Release();
    }
};

template<class Type>
class NOVTABLE CCGUnknownImpl : public CCGUnknownBase
{
public:
    CCGUnknownImpl(ICGUnknown *pUnknownOuter)
    {
        if (pUnknownOuter == NULL)
            *(PVOID *)&m_pUnknownOuter = (PVOID)(ICGNonDelegatingUnknown *)(Type *)this;
        else
            m_pUnknownOuter = pUnknownOuter;
    }

    // ICGNonDelegatingUnknown
    ForceInline CG_METHODIMPL NonDelegatingQueryInterface(REFIID iid, PVOID *ppvObject)
    {
        if (ppvObject == NULL)
            return STATUS_INVALID_PARAMETER_2;

        *ppvObject = NULL;

        return ((Type *)this)->QueryInterface0(iid, ppvObject);
    }

    CG_METHODIMPL_TYPE(ULONG) NonDelegatingRelease()
    {
        ULONG RefCount = __super::NonDelegatingRelease();

        if (RefCount == 0)
            delete (Type *)this;

        return RefCount;
    }

    // others
    CGSTATUS QueryInterface0(REFIID iid, PVOID *ppvObject)
    {
        UNREFERENCED_PARAMETER(iid);
        UNREFERENCED_PARAMETER(ppvObject);

        return STATUS_NOINTERFACE;
    }
};

#define CG_IUNKNOWN_IMPLEMENT(cls) \
            ForceInline CG_METHODIMPL QueryInterface(REFIID iid, PVOID *ppvObject) \
            { \
                return CCGUnknownImpl<cls>::QueryInterface(iid, ppvObject); \
            } \
            ForceInline CG_METHODIMPL_TYPE(ULONG) AddRef() \
            { \
                return CCGUnknownImpl<cls>::AddRef(); \
            } \
            ForceInline CG_METHODIMPL_TYPE(ULONG) Release() \
            { \
                return CCGUnknownImpl<cls>::Release(); \
            } \
            ForceInline CG_METHODIMPL NonDelegatingQueryInterface(REFIID iid, PVOID *ppvObject) \
            { \
                return CCGUnknownImpl<cls>::NonDelegatingQueryInterface(iid, ppvObject); \
            } \
            ForceInline CG_METHODIMPL_TYPE(ULONG) NonDelegatingAddRef() \
            { \
                return CCGUnknownImpl<cls>::NonDelegatingAddRef(); \
            } \
            ForceInline CG_METHODIMPL_TYPE(ULONG) NonDelegatingRelease() \
            { \
                return CCGUnknownImpl<cls>::NonDelegatingRelease(); \
            }

typedef
CGSTATUS
(CG_METHOD_CALLTYPE
*CreateInterfaceFunc)(
    interface ICGCoreBase   *pCore,
    ICGUnknown              *pUnknownOuter,
    REFIID                   InterfaceId,
    PVOID                   *ppvObject
);

CG_API
CGSTATUS
CG_METHOD_CALLTYPE
CreateInterface(
    interface ICGCoreBase   *pCore,
    ICGUnknown              *pUnknownOuter,
    REFIID                   InterfaceId,
    PVOID                   *ppvObject
);

#endif // _CG_INTERFACE_H_b287d2b7_4f81_49b6_8890_5cdbff338740
