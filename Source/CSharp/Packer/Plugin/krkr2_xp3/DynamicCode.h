#ifndef _DYNAMICCODE_H_
#define _DYNAMICCODE_H_

#include "my_headers.h"

class CDynamicCodeBase
{
public:
    typedef UInt32 (CDECL *F_GetMask)(UInt32 Hash);
    typedef struct
    {
        PByte  pbBuffer;
        PByte  pbBufferCur;
        UInt32 BufferSize;
        UInt32 Hash;
    } SCodeInfo;

    CDynamicCodeBase();
    ~CDynamicCodeBase();

    Bool Init();
    Void Release();
    UInt32 GetMask(UInt32 &Hash);

protected:
    Bool GenerateCode(UInt32 Index);
    Bool GenerateFunction(UInt32 uLoop);
    virtual Bool GenerateBody(UInt32 uLoop);
    virtual Bool GenerateBody2(UInt32 uLoop);
    virtual Bool GenerateTail();
    UInt32 GenerateSeed();

    Bool   AppendBytes(UInt32 uCount, LPVoid lpBytes);
    Bool   HasEnoughSpace(UInt32 uSizeToAppend);

protected:
    SCodeInfo m_Info;
    PByte m_pbFunction;
    PUInt32 m_pEncryptBlock;
};

#define FuncSize 0x80
#define FuncCount 0x80

class CFateHA : public CDynamicCodeBase
{
public:
    CFateHA() { m_pEncryptBlock = (PUInt32)m_EncryptBlock; }

protected:
    Bool   GenerateBody(UInt32 uLoop);
    Bool   GenerateBody2(UInt32 uLoop);
    Bool   GenerateTail();
    const static UInt32 m_EncryptBlock[0x400];
};

class CRealSister : public CDynamicCodeBase
{
public:
    CRealSister() { m_pEncryptBlock = (PUInt32)m_EncryptBlock; }

protected:
    Bool   GenerateBody(UInt32 uLoop);
    Bool   GenerateBody2(UInt32 uLoop);
    Bool   GenerateTail();
    const static UInt32 m_EncryptBlock[0x400];
};

class CNatsuZora : public CDynamicCodeBase
{
public:
    CNatsuZora() { m_pEncryptBlock = (PUInt32)m_EncryptBlock; }

protected:
    Bool   GenerateBody(UInt32 uLoop);
    Bool   GenerateBody2(UInt32 uLoop);
    Bool   GenerateTail();
    const static UInt32 m_EncryptBlock[0x400];
};

class CTenshin : public CDynamicCodeBase
{
public:
    CTenshin() { m_pEncryptBlock = (PUInt32)m_EncryptBlock; }

protected:
    Bool   GenerateBody(UInt32 uLoop);
    Bool   GenerateBody2(UInt32 uLoop);
    Bool   GenerateTail();
    const static UInt32 m_EncryptBlock[0x400];
};

#define AddBytes(...) { \
                          Byte bytes[] = { __VA_ARGS__ }; \
                          if (AppendBytes(sizeof(bytes), bytes) == False) \
                              return False; \
                      }

#define AddDword(__val) { \
                            UInt32 __v = (UInt32)(__val); \
                            if (AppendBytes(sizeof(__v), &__v) == False) \
                                return False; \
                        }

#endif /* _DYNAMICCODE_H_ */