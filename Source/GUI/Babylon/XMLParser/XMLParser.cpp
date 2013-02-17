#pragma comment(linker,"/MERGE:.text=.Amano /SECTION:.Amano,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Amano")
#pragma comment(linker,"/MERGE:.data=.Amano")
#define XML_PARSER_API EXTC_EXPORT

#include "my_xml.h"
#include "my_mem.h"
#include "tinyxml/tinyxml.h"

_MY_C_HEAD_

PWChar MBytesToWChar(UInt CodePage, PCChar lpMultiByteStr, int cbMultiByte = -1)
{
    UInt32 Size;
    PWChar pBuffer;

    if (lpMultiByteStr == NULL)
        return NULL;

    Size = MultiByteToWideChar(CodePage, 0, lpMultiByteStr, cbMultiByte, NULL, 0);
    pBuffer = (PWChar)malloc((Size + 1) * sizeof(*pBuffer));
    if (pBuffer == NULL)
        return NULL;

    Size = MultiByteToWideChar(CodePage, 0, lpMultiByteStr, cbMultiByte, pBuffer, Size);
    pBuffer[Size] = 0;

    return pBuffer;
}

PChar WCharToMBytes(UInt CodePage, PCWChar lpWideCharStr, int cchWideChar = -1)
{
    UInt32 Size;
    PChar  pBuffer;

    if (lpWideCharStr == NULL)
        return NULL;

    Size = WideCharToMultiByte(CodePage, 0, lpWideCharStr, cchWideChar, NULL, 0, NULL, NULL);
    pBuffer = (PChar)malloc(Size + 1);
    if (pBuffer == NULL)
        return NULL;

    Size = WideCharToMultiByte(CodePage, 0, lpWideCharStr, cchWideChar, pBuffer, Size, NULL, NULL);
    pBuffer[Size] = 0;

    return pBuffer;
}

PTChar ConvertText(UInt CodePage, LPCVoid pText, Bool bConvToUnicode)
{
    PVoid pvBuffer = NULL;

    if (pText == NULL)
        return NULL;

    if (bConvToUnicode)
    {
        pvBuffer = MBytesToWChar(CodePage, (PChar)pText);
    }
    else if (CodePage == CP_ACP)
    {
        Int Length;

        Length = StrLengthA((PChar)pText) + 1;
        pvBuffer = malloc(Length);
        if (pvBuffer != NULL)
        {
            memcpy(pvBuffer, pText, Length);
        }
    }
    else
    {
        PWChar pWideChar;

        pWideChar = MBytesToWChar(CodePage, (PChar)pText);
        pvBuffer  = WCharToMBytes(CP_ACP, pWideChar);
        free(pWideChar);
    }

    return (PTChar)pvBuffer;
}

#define SAFE_FREE(p) if ((p) != NULL) { free(p); (p) = NULL; }

Void XmlDestroyNode(SXmlNode *pNode)
{
    SAFE_FREE(pNode->pszNodeName);

    if (pNode->pAttribute != NULL)
    {
        SXmlAttribute *pAttribute;

        pAttribute = pNode->pAttribute;
        for (ULong AttributeCount = pNode->AttributeCount; AttributeCount; --AttributeCount)
        {
            SAFE_FREE(pAttribute->pszName);
            SAFE_FREE(pAttribute->pszValue);
            ++pAttribute;
        }

        free(pNode->pAttribute);
        pNode->pAttribute     = NULL;
        pNode->AttributeCount = 0;
    }

    if (pNode->pSubNode != NULL)
    {
        SXmlNode *pSubNode;

        pSubNode = pNode->pSubNode;
        for (ULong NodeCount = pNode->NodeCount; NodeCount; --NodeCount)
        {
            XmlDestroyNode(pSubNode);
            ++pSubNode;
        }

        free(pNode->pSubNode);
        pNode->pSubNode  = NULL;
        pNode->NodeCount = 0;
    }
}

ForceInline Void XmlDestroyWorker(SXmlInfo *pXmlInfo)
{
    if (pXmlInfo == NULL)
        return;

    SXmlNode *pNode;

    pNode = pXmlInfo->pNode;
    if (pNode != NULL)
    {
        for (ULong i = pXmlInfo->NodeCount; i; --i)
        {
            XmlDestroyNode(pNode);
            ++pNode;
        }

        free(pXmlInfo->pNode);
        pXmlInfo->pNode     = NULL;
        pXmlInfo->NodeCount = 0;
    }
}

Void STDCALL XmlDestroy(PVoid pXmlInfo)
{
    XmlDestroyWorker((SXmlInfo *)pXmlInfo);
}

ULong GetSiblingNodeCount(TiXmlElement *pElement)
{
    ULong         Count;
    TiXmlElement *pElem;

    if (pElement == NULL)
        return 0;

    Count = 1;
    pElem = pElement;
    while (pElem = pElem->NextSiblingElement())
        ++Count;

    return Count;
}

ULong GetAttributeCount(TiXmlElement *pElement)
{
    ULong Count;
    TiXmlAttribute *pAttribute;

    if (pElement == NULL)
        return 0;

    pAttribute = pElement->FirstAttribute();
    if (pAttribute == NULL)
        return 0;

    Count = 0;
    do
    {
        ++Count;
    } while (pAttribute = pAttribute->Next());

    return Count;
}

Bool AddNode(TiXmlElement *pElement, SXmlNode *pNode, UInt CodePage, Bool bConvToUnicode)
{ 
    PChar           pszElementData;
    TiXmlElement   *pXmlSubElem;
    TiXmlAttribute *pXmlAttribute;
    ULong NodeCount, AttributeCount, Size;

    pNode->pszNodeName = ConvertText(CodePage, pElement->Value(), bConvToUnicode);
    if (pNode->pszNodeName == NULL)
        return False;

    pszElementData = (PChar)pElement->GetText();
    if (pszElementData != NULL && *pszElementData != 0)
    {
        pNode->pszData = ConvertText(CodePage, pszElementData, bConvToUnicode);
    }

    AttributeCount = GetAttributeCount(pElement);
    if (AttributeCount != 0)
    {
        SXmlAttribute *pAttribute;

        Size = AttributeCount * sizeof(*pXmlAttribute);
        pAttribute = (SXmlAttribute *)malloc(Size);
        if (pAttribute == NULL)
            return False;

        pNode->pAttribute = pAttribute;
        pNode->AttributeCount = AttributeCount;
        ZeroMemory(pAttribute, Size);

        pXmlAttribute = pElement->FirstAttribute();
        for (ULong i = 0; i != AttributeCount; ++i)
        {
            PTChar pszText;
            pszText = ConvertText(CodePage, pXmlAttribute->Name(), bConvToUnicode);
            if (pszText == NULL)
                return False;

            pAttribute->pszName = pszText;

            pszText = ConvertText(CodePage, pXmlAttribute->Value(), bConvToUnicode);
            if (pszText == NULL)
                return False;

            pAttribute->pszValue = pszText;

            pXmlAttribute = pXmlAttribute->Next();
            ++pAttribute;
        }
    }

    pXmlSubElem = pElement->FirstChildElement();
    NodeCount = GetSiblingNodeCount(pXmlSubElem);
    if (NodeCount != 0)
    {
        Size = NodeCount * sizeof(*pNode->pSubNode);
        pNode->pSubNode = (SXmlNode *)malloc(Size);
        if (pNode->pSubNode == NULL)
            return False;

        pNode->NodeCount = NodeCount;
        pNode = pNode->pSubNode;
        ZeroMemory(pNode, Size);
        while (NodeCount--)
        {
            if (!AddNode(pXmlSubElem, pNode, CodePage, bConvToUnicode))
                return False;

            pXmlSubElem = pXmlSubElem->NextSiblingElement();
            ++pNode;
        }
    }

    return True;
}

NoInline Bool XmlParseWorker(PVoid pXmlBuffer, SXmlInfo *pXmlInfo, Bool bConvToUnicode)
{
    if (pXmlInfo == NULL)
        return False;

    TiXmlDocument Doc;
    TiXmlElement *pElem;

    SXmlNode      *pNode, *pNodeRoot;
    SXmlAttribute *pAttribute;

    ULong NodeCount;
    UInt  CodePage;

#define XMLPARSE_ASSERT(expression) if (!(expression)) goto PARSE_FAIL;

    pXmlInfo->NodeCount = 0;
    pXmlInfo->pNode     = NULL;

    if (Doc.Parse((PCChar)pXmlBuffer) == NULL)
        return False;

    pElem = Doc.FirstChildElement();
    if (pElem == NULL)
        return False;

    switch (Doc.GetEncoding())
    {
        case TIXML_ENCODING_UTF8:
            CodePage = CP_UTF8;
            break;

        case TIXML_ENCODING_LEGACY:
        default:
            CodePage = CP_ACP;
    }

    NodeCount = GetSiblingNodeCount(pElem);
    if (NodeCount == 0)
        return False;

    pNode = (SXmlNode *)malloc(NodeCount * sizeof(*pNode));
    if (pNode == NULL)
        return False;

    pNodeRoot = pNode;
    ZeroMemory(pNode, NodeCount * sizeof(*pNode));

    for (ULong i = NodeCount; i; --i)
    {
        XMLPARSE_ASSERT(AddNode(pElem, pNode, CodePage, bConvToUnicode));
        pElem = pElem->NextSiblingElement();
        ++pNode;
    }

    pXmlInfo->NodeCount = NodeCount;
    pXmlInfo->pNode     = pNodeRoot;

    return True;

PARSE_FAIL:
    SXmlInfo Xml;

    Xml.pNode = pNodeRoot;
    Xml.NodeCount = NodeCount;
    XmlDestroy(&Xml);

    return False;

#undef XMLPARSE_ASSERT

}

Bool STDCALL XmlParseA(PVoid pXmlBuffer, SXmlInfoA *pXmlA)
{
    return XmlParseWorker(pXmlBuffer, (SXmlInfo *)pXmlA, False);
}

Bool STDCALL XmlParseW(PVoid pXmlBuffer, SXmlInfoW *pXmlW)
{
    return XmlParseWorker(pXmlBuffer, (SXmlInfo *)pXmlW, True);
}

Bool STDCALL XmlUnicodeToMultiByte(UInt CodePage, const SXmlInfoW *pXmlInfoW, SXmlInfoA *pXmlInfoA)
{
    return True;
}
Bool STDCALL XmlMultiByteToUnicode(UInt CodePage, const SXmlInfoA *pXmlInfoA, SXmlInfoW *pXmlInfoW)
{
    return True;
}

SXmlNodeA* STDCALL XmlFindNodeA(SXmlInfoA* pXmlInfo, PCChar pszNodeName)
{
    SXmlNodeA *pNode;

    if (pXmlInfo == NULL || pszNodeName == NULL)
        return NULL;

    pNode = pXmlInfo->pNode;
    if (pNode == NULL)
        return NULL;

    for (UInt32 i = pXmlInfo->NodeCount; i; --i)
    {
        if (!strcmp(pNode->pszNodeName, pszNodeName))
            return pNode;
        ++pNode;
    }

    return NULL;
}

SXmlNodeW* STDCALL XmlFindNodeW(SXmlInfoW* pXmlInfo, PCWChar pszNodeName)
{
    SXmlNodeW *pNode;

    if (pXmlInfo == NULL || pszNodeName == NULL)
        return NULL;

    pNode = pXmlInfo->pNode;
    if (pNode == NULL)
        return NULL;

    for (UInt32 i = pXmlInfo->NodeCount; i; --i)
    {
        if (!wcscmp(pNode->pszNodeName, pszNodeName))
            return pNode;
        ++pNode;
    }

    return NULL;
}

SXmlAttributeA* STDCALL XmlFindAttributeA(SXmlNodeA *pNode, PCChar pszAttributeName, PCChar pszAttributeValue)
{
    if (pNode == NULL)
        return NULL;

    if (pszAttributeName == NULL && pszAttributeValue == NULL)
        return NULL;

    SXmlAttributeA *pAttribute;

    pAttribute = pNode->pAttribute;
    if (pAttribute == NULL)
        return NULL;

    for (ULong i = pNode->AttributeCount; i; --i, ++pAttribute)
    {
        if (pszAttributeName != NULL)
        {
            if (strcmp(pAttribute->pszName, pszAttributeName))
                continue;
        }

        if (pszAttributeValue != NULL)
        {
            if (strcmp(pAttribute->pszValue, pszAttributeValue))
                continue;
        }

        return pAttribute;
    }

    return NULL;
}

SXmlAttributeW* STDCALL XmlFindAttributeW(SXmlNodeW *pNode, PCWChar pszAttributeName, PCWChar pszAttributeValue)
{
    if (pNode == NULL)
        return NULL;

    if (pszAttributeName == NULL && pszAttributeValue == NULL)
        return NULL;

    SXmlAttributeW *pAttribute;

    pAttribute = pNode->pAttribute;
    if (pAttribute == NULL)
        return NULL;

    for (ULong i = pNode->AttributeCount; i; --i, ++pAttribute)
    {
        if (pszAttributeName != NULL)
        {
            if (wcscmp(pAttribute->pszName, pszAttributeName))
                continue;
        }

        if (pszAttributeValue != NULL)
        {
            if (wcscmp(pAttribute->pszValue, pszAttributeValue))
                continue;
        }

        return pAttribute;
    }

    return NULL;
}

_MY_C_TAIL_