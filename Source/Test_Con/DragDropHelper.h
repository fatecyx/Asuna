#ifndef _DRAGDROPHELPER_H_52fd957a_cae0_4641_9d0b_2ce18fe60017_
#define _DRAGDROPHELPER_H_52fd957a_cae0_4641_9d0b_2ce18fe60017_

#include "MyLibrary.h"
#include <shlobj.h>
#include <objidl.h>

class DragDropHelper : public IEnumFORMATETC , public IDataObject , public IDropSource
{
protected:
    BOOL        m_EnumeratorReaded;
    BOOL        m_DragStart;
    BOOL        m_DragStop;
    LPFORMATETC m_FormatEtc;
    HGLOBAL     m_hGlobal;

public:
    DragDropHelper(HGLOBAL hGlobal = NULL, LPFORMATETC FormatEtc = NULL);

    HRESULT DragTo(HGLOBAL hGlobal, LPFORMATETC FormatEtc);

    //
    // IUnknown
    //
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *Object);
    ULONG   STDMETHODCALLTYPE AddRef();
    ULONG   STDMETHODCALLTYPE Release();

    //
    // IEnumFORMATETC
    //
    HRESULT STDMETHODCALLTYPE Next(ULONG celt , LPFORMATETC rgelt , PULONG pceltFetched);
    HRESULT STDMETHODCALLTYPE Skip(ULONG celt);
    HRESULT STDMETHODCALLTYPE Reset();
    HRESULT STDMETHODCALLTYPE Clone(IEnumFORMATETC **ppenum);

    //
    // IDataObject
    //
    HRESULT STDMETHODCALLTYPE GetData(LPFORMATETC pformatetcIn ,STGMEDIUM *pmedium);
    HRESULT STDMETHODCALLTYPE GetDataHere(LPFORMATETC pformatetc , STGMEDIUM *pmedium);
    HRESULT STDMETHODCALLTYPE QueryGetData(LPFORMATETC pformatetc);
    HRESULT STDMETHODCALLTYPE GetCanonicalFormatEtc(LPFORMATETC pformatectIn , LPFORMATETC pformatetcOut);
    HRESULT STDMETHODCALLTYPE SetData(LPFORMATETC pformatetc , STGMEDIUM *pmedium , BOOL fRelease);
    HRESULT STDMETHODCALLTYPE EnumFormatEtc(ULONG Direction , IEnumFORMATETC **ppenumFormatEtc);
    HRESULT STDMETHODCALLTYPE DAdvise(LPFORMATETC pformatetc , ULONG advf , IAdviseSink *pAdvSink , PULONG pdwConnection);
    HRESULT STDMETHODCALLTYPE DUnadvise(ULONG dwConnection);
    HRESULT STDMETHODCALLTYPE EnumDAdvise(IEnumSTATDATA **ppenumAdvise);

    //
    // IDropSource
    //
    HRESULT STDMETHODCALLTYPE QueryContinueDrag(BOOL fEscapePressed , ULONG grfKeyState);
    HRESULT STDMETHODCALLTYPE GiveFeedback(ULONG dwEffect);
};

DragDropHelper::DragDropHelper(HGLOBAL hGlobal /* = NULL */, LPFORMATETC FormatEtc /* = NULL */)
{
    m_EnumeratorReaded  = FALSE;
    m_DragStart         = FALSE;
    m_DragStop          = FALSE;
    m_hGlobal           = hGlobal;
    m_FormatEtc         = FormatEtc;
}

HRESULT DragDropHelper::DragTo(HGLOBAL hGlobal, LPFORMATETC FormatEtc)
{
    ULONG Effect;

    m_hGlobal   = hGlobal;
    m_FormatEtc = FormatEtc;

    return DoDragDrop(this, this, DROPEFFECT_COPY, &Effect);
}

/************************************************************************
  IUnknown
************************************************************************/
HRESULT STDMETHODCALLTYPE DragDropHelper::QueryInterface(REFIID riid, PVOID *Object)
{
    if(riid==IID_IUnknown)
    {
        *Object = (IUnknown *)(IDataObject *)this;
    }
    else if(riid==IID_IEnumFORMATETC)
    {
        *Object = (IEnumFORMATETC *)this;
    }
    else if(riid==IID_IDataObject)
    {
        *Object = (IDataObject *)this;
    }
    else if(riid==IID_IDropSource)
    {
        *Object = (IDropSource *)this;
    }
    else
    {
        *Object = NULL;
        return E_NOINTERFACE;
    }

    return S_OK;
}

ULONG STDMETHODCALLTYPE DragDropHelper::AddRef()
{
    return 1;
}

ULONG STDMETHODCALLTYPE DragDropHelper::Release()
{
    return 1;
}

/************************************************************************
  IEnumFORMATETC
************************************************************************/
HRESULT STDMETHODCALLTYPE DragDropHelper::Next(ULONG celt , FORMATETC *rgelt , ULONG *pceltFetched)
{
    if (m_EnumeratorReaded)
    {
        if (pceltFetched != NULL)
        {
            *pceltFetched = 0;
        }

        return S_FALSE;
    }
    else
    {
        m_EnumeratorReaded = TRUE;

        if (celt != NULL)
        {
            if (pceltFetched != NULL)
            {
                *pceltFetched = 1;
            }

            if (rgelt != NULL)
            {
                *rgelt = *m_FormatEtc;
            }
        }

        return celt == 1 ? S_OK : S_FALSE;
    }
}

HRESULT STDMETHODCALLTYPE DragDropHelper::Skip(ULONG celt)
{
    return S_FALSE;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::Reset()
{
    m_EnumeratorReaded = FALSE;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::Clone(IEnumFORMATETC **ppenum)
{
    *ppenum = this;

    return S_OK;
}

/************************************************************************
  IDataObject
************************************************************************/

HRESULT STDMETHODCALLTYPE DragDropHelper::GetData(FORMATETC *pformatetcIn ,STGMEDIUM *pmedium)
{
    if (pformatetcIn->cfFormat != CF_HDROP || !FLAG_ON(pformatetcIn->tymed, TYMED_HGLOBAL))
    {
        return DV_E_FORMATETC;
    }

    pmedium->tymed          = TYMED_HGLOBAL;
    pmedium->hGlobal        = OleDuplicateData(m_hGlobal, CF_HDROP, 0);
    pmedium->pUnkForRelease = NULL;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::GetDataHere(FORMATETC *pformatetc, STGMEDIUM *pmedium)
{
    return DV_E_TYMED;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::QueryGetData(LPFORMATETC pformatetc)
{
    if (pformatetc == NULL)
        return S_FALSE;

    if (pformatetc->cfFormat != CF_HDROP || !FLAG_ON(pformatetc->tymed, TYMED_HGLOBAL))
    {
        return DV_E_TYMED;
    }
    else
    {
        return S_OK;
    }
}

HRESULT STDMETHODCALLTYPE DragDropHelper::GetCanonicalFormatEtc(__RPC__in_opt FORMATETC *pformatectIn , __RPC__out FORMATETC *pformatetcOut)
{
//    *pformatetcOut = m_FormatEtc;
    return DATA_S_SAMEFORMATETC;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::SetData(FORMATETC *pformatetc , STGMEDIUM *pmedium , BOOL fRelease)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::EnumFormatEtc(DWORD Direction, IEnumFORMATETC **ppenumFormatEtc)
{
    switch (Direction)
    {
        case DATADIR_GET:
            break;

        default:
            return OLE_S_USEREG;
    }

    Reset();

    *ppenumFormatEtc = this;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
    return OLE_E_ADVISENOTSUPPORTED;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::DUnadvise(DWORD dwConnection)
{
    return OLE_E_ADVISENOTSUPPORTED;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::EnumDAdvise(IEnumSTATDATA **ppenumAdvise)
{
    return OLE_E_ADVISENOTSUPPORTED;
}

/************************************************************************
  IDropSource
************************************************************************/

HRESULT STDMETHODCALLTYPE DragDropHelper::QueryContinueDrag(BOOL fEscapePressed , DWORD grfKeyState)
{
    BOOL LeftPressed;

    if (fEscapePressed)
    {
        return DRAGDROP_S_CANCEL;
    }

    LeftPressed = FLAG_ON(grfKeyState, MK_LBUTTON);

    if (!m_DragStart)
    {
        m_DragStart = LeftPressed;
    }
    else if (!LeftPressed)
    {
        m_DragStop = TRUE;
    }

    return !m_DragStop ? S_OK : DRAGDROP_S_DROP;
}

HRESULT STDMETHODCALLTYPE DragDropHelper::GiveFeedback(DWORD dwEffect)
{
    return DRAGDROP_S_USEDEFAULTCURSORS;
//    return m_DragStart ? DRAGDROP_S_USEDEFAULTCURSORS : S_OK;
}


#endif // _DRAGDROPHELPER_H_52fd957a_cae0_4641_9d0b_2ce18fe60017_
