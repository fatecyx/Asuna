#ifndef _MY_XML_H_
#define _MY_XML_H_

#include "../common/bl_common.h"

#if !defined(XML_PARSER_API)
    #define XML_PARSER_API EXTC_IMPORT
#endif

#pragma pack(1)

/************************************************************************/
/* ansi version                                                         */
/************************************************************************/
typedef struct
{
    PChar pszName;
    PChar pszValue;
} SXmlAttributeA;

typedef struct _SXmlNodeA
{
    PChar              pszNodeName;
    ULong              NodeCount;
    struct _SXmlNodeA *pSubNode;
    ULong              AttributeCount;
    SXmlAttributeA    *pAttribute;
    PChar              pszData;
} SXmlNodeA;

typedef struct
{
    ULong      NodeCount;
    SXmlNodeA *pNode;
} SXmlInfoA;

/************************************************************************/
/* unicode version                                                      */
/************************************************************************/
typedef struct
{
    PWChar pszName;
    PWChar pszValue;
} SXmlAttributeW;

typedef struct _SXmlNodeW
{
    PWChar             pszNodeName;
    ULong              NodeCount;
    struct _SXmlNodeW *pSubNode;
    ULong              AttributeCount;
    SXmlAttributeW    *pAttribute;
    PWChar             pszData;
} SXmlNodeW;

typedef struct
{
    ULong      NodeCount;
    SXmlNodeW *pNode;
} SXmlInfoW;

#pragma pack()

#if defined(UNICODE) || defined(_UNICODE)
    typedef SXmlInfoW SXmlInfo;
    typedef SXmlNodeW SXmlNode;
    typedef SXmlAttributeW SXmlAttribute;

    #define XmlParse         XmlParseW
    #define XmlFindNode      XmlFindNodeW
    #define XmlFindAttribute XmlFindAttributeW
#else
    typedef SXmlInfoA SXmlInfo;
    typedef SXmlNodeA SXmlNode;
    typedef SXmlAttributeA SXmlAttribute;

    #define XmlParse         XmlParseA
    #define XmlFindNode      XmlFindNodeA
    #define XmlFindAttribute XmlFindAttributeA
#endif /* UNICODE */

typedef union
{
    SXmlInfo  xml;
    SXmlInfoA xmla;
    SXmlInfoW xmlw;
} UXmlInfo;

_MY_C_HEAD_

XML_PARSER_API Bool            STDCALL XmlParseA(PVoid pXmlBuffer, SXmlInfoA *pXmlInfoA);
XML_PARSER_API Bool            STDCALL XmlParseW(PVoid pXmlBuffer, SXmlInfoW *pXmlInfoW);
XML_PARSER_API Bool            STDCALL XmlUnicodeToMultiByte(UInt CodePage, const SXmlInfoW *pXmlInfoW, SXmlInfoA *pXmlInfoA);
XML_PARSER_API Bool            STDCALL XmlMultiByteToUnicode(UInt CodePage, const SXmlInfoA *pXmlInfoA, SXmlInfoW *pXmlInfoW);
XML_PARSER_API Void            STDCALL XmlDestroy(PVoid pXmlInfo);

XML_PARSER_API SXmlNodeA*      STDCALL XmlFindNodeA(SXmlInfoA* pXml, PCChar pszNode);
XML_PARSER_API SXmlNodeW*      STDCALL XmlFindNodeW(SXmlInfoW* pXml, PCWChar pszNode);
XML_PARSER_API SXmlAttributeA* STDCALL XmlFindAttributeA(SXmlNodeA *pNode, PCChar  pszAttributeName, PCChar  pszAttributeValue);
XML_PARSER_API SXmlAttributeW* STDCALL XmlFindAttributeW(SXmlNodeW *pNode, PCWChar pszAttributeName, PCWChar pszAttributeValue);

_MY_C_TAIL_

#endif /* _MY_XML_H_ */