#include "Matrix.h"
#include "my_mem.h"

CMatrix::CMatrix()
{
    m_uiColumn     = 0;
    m_uiLine       = 0;
    m_uiMatrixSize = 0;
    m_pMatrix      = NULL;
    m_pfMatrix     = NULL;
    m_hHeap        = GetProcessHeap();
}

CMatrix::CMatrix(UINT32 uiLine, UINT32 uiColumn, INT32 i, ...)
{
    va_list arg_ptr;

    m_hHeap     = GetProcessHeap();
    m_pMatrix   = NULL;
    m_pfMatrix  = NULL;
    va_start(arg_ptr, uiColumn);
    CreateMatrix(uiLine, uiColumn, arg_ptr);
}

CMatrix::CMatrix(UINT32 uiLine, UINT32 uiColumn, DOUBLE i, ...)
{
    va_list arg_ptr;

    m_hHeap     = GetProcessHeap();
    m_pMatrix   = NULL;
    m_pfMatrix  = NULL;
    va_start(arg_ptr, uiColumn);
    CreateMatrixF(uiLine, uiColumn, arg_ptr);
}

CMatrix::CMatrix(const CMatrix &m)
{
    *this = m;
}

CMatrix::~CMatrix()
{
    DestroyMatrix();
}

BOOL CMatrix::CreateMatrix(UINT32 uiLine, UINT32 uiColumn, INT32 i, ...)
{
    va_list arg;
    va_start(arg, uiColumn);
    return CreateMatrix(uiLine, uiColumn, arg);
}

BOOL CMatrix::CreateMatrix(UINT32 uiLine, UINT32 uiColumn, va_list arg)
{
    DestroyMatrix();

    m_uiLine   = uiLine;
    m_uiColumn = uiColumn;
    m_uiMatrixSize = m_uiLine * m_uiColumn * sizeof(**m_pMatrix);
    m_pMatrix = (PINT32 *)HeapAlloc(m_hHeap, 0, uiLine * sizeof(*m_pMatrix));
    for (UINT32 l = 0; l != uiLine; ++l)
    {
        m_pMatrix[l] = (PINT32)HeapAlloc(m_hHeap, 0, uiColumn * sizeof(**m_pMatrix));
    }

    if (m_pMatrix == NULL)
    {
        return FALSE;
    }

    for (int l = 0; l != uiLine; ++l)
    {
        for (int c = 0; c != uiColumn; ++c)
        {
            m_pMatrix[l][c] = *(PINT32)arg;
            va_arg(arg, INT32);
        }
    }

    return TRUE;
}

BOOL CMatrix::CreateMatrixF(UINT32 uiLine, UINT32 uiColumn, DOUBLE i, ...)
{
    va_list arg;
    va_start(arg, uiColumn);
    return CreateMatrix(uiLine, uiColumn, arg);
}

BOOL CMatrix::CreateMatrixF(UINT32 uiLine, UINT32 uiColumn, va_list arg)
{
    DestroyMatrix();

    m_uiLine   = uiLine;
    m_uiColumn = uiColumn;
    m_uiMatrixSize = m_uiLine * m_uiColumn * sizeof(**m_pfMatrix);
    m_pfMatrix = (PFLOAT *)HeapAlloc(m_hHeap, 0, uiLine * sizeof(*m_pfMatrix));
    for (UINT32 l = 0; l != uiLine; ++l)
    {
        m_pfMatrix[l] = (PFLOAT)HeapAlloc(m_hHeap, 0, uiColumn * sizeof(**m_pfMatrix));
    }

    if (m_pfMatrix == NULL)
    {
        return FALSE;
    }

    for (int l = 0; l != uiLine; ++l)
    {
        for (int c = 0; c != uiColumn; ++c)
        {
            m_pfMatrix[l][c] = (FLOAT)va_arg(arg, double);
        }
    }

    return TRUE;
}

VOID CMatrix::DestroyMatrix()
{
    if (m_pMatrix)
    {
        for (UINT32 l = 0; l != m_uiLine; ++l)
        {
            if (m_pMatrix[l])
            {
                HeapFree(m_hHeap, 0, m_pMatrix[l]);
            }
        }

        HeapFree(m_hHeap, 0, m_pMatrix);
        m_pMatrix = NULL;
    }

    if (m_pfMatrix)
    {
        for (UINT32 l = 0; l != m_uiLine; ++l)
        {
            if (m_pfMatrix[l])
            {
                HeapFree(m_hHeap, 0, m_pfMatrix[l]);
            }
        }

        HeapFree(m_hHeap, 0, m_pfMatrix);
        m_pfMatrix = NULL;
    }
}

BOOL CMatrix::Multiply(const CMatrix &m)
{
    UINT32  uiColumn;
    PINT32 *pMatrix;

    uiColumn = min(m_uiColumn, m.m_uiLine);
    pMatrix = (PINT32 *)HeapAlloc(m_hHeap, 0, m_uiLine * sizeof(*pMatrix));
    for (UINT32 l = 0; l != m_uiLine; ++l)
    {
        pMatrix[l] = (PINT32)HeapAlloc(m_hHeap, 0, uiColumn * sizeof(**pMatrix));
    }

    for (UINT32 line = 0; line != m_uiLine; ++line)
    {
        for (UINT32 column = 0; column != uiColumn; ++column)
        {
            INT32 val = 0;
            for (UINT32 c = 0; c != uiColumn; ++c)
            {
                val += m_pMatrix[line][c] * m.m_pMatrix[c][column];
            }
            pMatrix[line][column] = val;
        }
    }

    m_uiColumn = uiColumn;
    DestroyMatrix();
    m_pMatrix = pMatrix;
    m_uiMatrixSize = m_uiLine * m_uiColumn * sizeof(**m_pMatrix);

    return TRUE;
}

BOOL CMatrix::MultiplyF(const CMatrix &m)
{
    UINT32  uiColumn;
    PFLOAT *pMatrix;

    uiColumn = min(m_uiColumn, m.m_uiLine);
    pMatrix = (PFLOAT *)HeapAlloc(m_hHeap, 0, m_uiLine * sizeof(*pMatrix));
    for (UINT32 l = 0; l != m_uiLine; ++l)
    {
        pMatrix[l] = (PFLOAT)HeapAlloc(m_hHeap, 0, uiColumn * sizeof(**pMatrix));
    }

    for (UINT32 line = 0; line != m_uiLine; ++line)
    {
        for (UINT32 column = 0; column != uiColumn; ++column)
        {
            FLOAT val = 0;
            for (UINT32 c = 0; c != uiColumn; ++c)
            {
                val += m_pfMatrix[line][c] * m.m_pfMatrix[c][column];
            }
            pMatrix[line][column] = val;
        }
    }

    m_uiColumn = uiColumn;
    DestroyMatrix();
    m_pfMatrix = pMatrix;
    m_uiMatrixSize = m_uiLine * m_uiColumn * sizeof(**m_pfMatrix);

    return TRUE;
}

CMatrix& CMatrix::operator= (const CMatrix &m)
{
    if (this != &m)
    {
        if (m.m_pMatrix)
        {
            m_uiLine       = m.m_uiLine;
            m_uiColumn     = m.m_uiColumn;
            m_uiMatrixSize = m.m_uiMatrixSize;
            m_hHeap        = GetProcessHeap();
            m_pfMatrix     = NULL;
            m_pMatrix      = (PINT32 *)HeapAlloc(m_hHeap, 0, m_uiLine * sizeof(*m_pMatrix));
            for (UINT32 l = 0; l != m_uiLine; ++l)
            {
                m_pMatrix[l] = (PINT32)HeapAlloc(m_hHeap, 0, m_uiColumn * sizeof(**m_pMatrix));
            }
            
            for (UINT32 l = 0; l != m_uiLine; ++l)
            {
                memcpy(m_pMatrix[l], m.m_pMatrix[l], m_uiColumn * sizeof(**m_pMatrix));
            }
        }
        else if (m.m_pfMatrix)
        {
            m_uiLine       = m.m_uiLine;
            m_uiColumn     = m.m_uiColumn;
            m_uiMatrixSize = m.m_uiMatrixSize;
            m_hHeap        = GetProcessHeap();
            m_pMatrix      = NULL;
            m_pfMatrix     = (PFLOAT *)HeapAlloc(m_hHeap, 0, m_uiLine * sizeof(*m_pfMatrix));
            for (UINT32 l = 0; l != m_uiLine; ++l)
            {
                m_pfMatrix[l] = (PFLOAT)HeapAlloc(m_hHeap, 0, m_uiColumn * sizeof(**m_pfMatrix));
            }
            
            for (UINT32 l = 0; l != m_uiLine; ++l)
            {
                memcpy(m_pfMatrix[l], m.m_pfMatrix[l], m_uiColumn * sizeof(**m_pfMatrix));
            }
        }
    }

    return *this;
}

CMatrix operator* (const CMatrix &m1, const CMatrix &m2)
{
    CMatrix m(m1);

    if (m.m_pfMatrix || m2.m_pfMatrix)
    {
        m.MultiplyF(m2);
    }
    else if (m.m_pMatrix && m2.m_pMatrix)
    {
        m.Multiply(m2);
    }

    return m;
}