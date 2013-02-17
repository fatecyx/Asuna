#ifndef _MODELSCRIPT_H_
#define _MODELSCRIPT_H_

#include "pragma_once.h"
#include "WindowBase.h"
#include "MyString.h"

using namespace MY_LIB_NAME;

typedef struct
{
    SizeT   PhysicalLine;
    SizeT   LogicalLine;
    SizeT   CharNameIndex;
    StringW VoiceName;
    StringW Text;
} SScriptText;

typedef MyLib::Vector<SScriptText> VectorText;

enum
{
    SCR_ERROR_SUCCESS = 0,

    SCR_ERROR_FIRST = 0x80000000,

    SCR_ERROR_IO_FAILED_OPEN = SCR_ERROR_FIRST,
    SCR_ERROR_IO_FAILED_SEEK,
    SCR_ERROR_IO_FAILED_READ,
    SCR_ERROR_IO_FAILED_WRITE,
    SCR_ERROR_OUT_OF_MEMORY,
    SCR_ERROR_INVALID_ENCODING,
    SCR_ERROR_INVALID_TRANSLATION_FILE,
    SCR_ERROR_EMPTY_ORIGINAL_TEXT,
    SCR_ERROR_EMPTY_TRANSLATION_TEXT,

    SCR_ERROR_LAST,
};

#define SCR_FAILED(Result) ((Long)(Result) < 0)
#define SCR_SUCCESS(Result) !SCR_FAILED(Result)

class CModelScript : public MyWindowClass::CModelBase
{
protected:
    CMem       m_mem;
    String     m_ScriptPath;
    VectorText m_VecTextOrigianl;
    VectorText m_VecTextTranslation;
    MyLib::Vector<StringW> m_VecCharNameOriginal;
    MyLib::Vector<StringW> m_VecCharNameTranslation;

public:    
    PCTChar GetErrorString(Long ErrorCode);

    Long ParseScript(PCTChar pszScriptPath);

    PWChar GetCharNameOriginalByIndex(SizeT Index);
    PWChar GetCharNameTranslationByIndex(SizeT Index);

    Bool UpdateTextOriginal(SizeT Index, PCWChar pszText, SScriptText **pChangedText);
    Bool UpdateTextTranslation(SizeT Index, PCWChar pszText, SScriptText **pChangedText);

    SizeT GetTextListOriginal(SScriptText **pScriptText);
    SizeT GetTextListTranslation(SScriptText **pScriptText);
    SizeT GetTextListOriginalCount();
    SizeT GetTextListTranslationCount();

    SScriptText* GetTextOriginal(SizeT Index);
    SScriptText* GetTextTranslation(SizeT Index);

    Void GetTextSelectionRange(SScriptText *pText, PSizeT pStart, PSizeT pEnd);

    Long SaveTranslationToFile();
    Long DeleteTranslationFile();
    Long SubmitAllTranslation();

private:
    Void GenerateTranslationFileName(PTChar pszScriptPath);

    Long ParseScriptWorker(PVoid pvBuffer, SizeT BufferSize);
    Long ParseTranslationFile(PCTChar pszScriptPath);

    SizeT FindCharName(PCWChar pszCharName);

    Bool   IsComment(PWChar pszText);
    Bool   IsControlSentance(PWChar pszText);
    PWChar PeekLine(PVoid pBuffer, PVoid pEndOfBuffer, PVoid pOutBuffer, PSizeT pcbOutBuffer);

    Bool UpdateTextWorker(VectorText &VecText, SizeT Index, PCWChar pszText, SScriptText **pChangedText);
};

#endif /* _MODELSCRIPT_H_ */