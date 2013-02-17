#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <Windows.h>
#include "my_common.h"

class CMatrix
{
    friend CMatrix operator* (const CMatrix &m1, const CMatrix &m2);
public:
    CMatrix();
    CMatrix(const CMatrix &m);
    CMatrix(UINT32 uiLine, UINT32 uiColumn, INT32 i, ...);
    CMatrix(UINT32 uiLine, UINT32 uiColumn, DOUBLE i, ...);
    virtual ~CMatrix();

public:
    BOOL    CreateMatrix (UINT32 uiLine, UINT32 uiColumn, INT32 i, ...);
    BOOL    CreateMatrix (UINT32 uiLine, UINT32 uiColumn, va_list arg);
    BOOL    CreateMatrixF(UINT32 uiLine, UINT32 uiColumn, DOUBLE i, ...);
    BOOL    CreateMatrixF(UINT32 uiLine, UINT32 uiColumn, va_list arg);
    VOID    DestroyMatrix();
    UINT32  GetLineNumber();
    UINT32  GetColumnNumber();
    UINT32  GetMatrixSize();
    LPVOID  GetMatrixPointer();
    CMatrix& operator= (const CMatrix &m);

private:
    BOOL Multiply(const CMatrix &m);
    BOOL MultiplyF(const CMatrix &m);

private:
    UINT32  m_uiLine, m_uiColumn, m_uiMatrixSize;
    PINT32 *m_pMatrix;
    PFLOAT *m_pfMatrix;
    HANDLE  m_hHeap;
};

FORCEINLINE LPVOID CMatrix::GetMatrixPointer()
{
    return m_pMatrix ? m_pMatrix : m_pfMatrix ? (LPVOID)m_pfMatrix : NULL;
}

FORCEINLINE UINT32 CMatrix::GetLineNumber()
{
    return m_uiLine;
}

FORCEINLINE UINT32 CMatrix::GetColumnNumber()
{
    return m_uiColumn;
}

FORCEINLINE UINT32 CMatrix::GetMatrixSize()
{
    return m_uiMatrixSize;
}

#endif /* _MATRIX_H_ */