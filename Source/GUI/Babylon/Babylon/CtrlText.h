#include "Babylon.h"

#pragma pack(1)

typedef struct
{
    TChar *name;
    WORD  id;
} SCtrlInfo;

#pragma pack()

extern SCtrlInfo   g_ciCheckBox[];
extern const DWORD g_dwCheckBox;

extern SCtrlInfo   g_ciLButton[];
extern const DWORD g_dwLButton;
    
extern SCtrlInfo   g_ciRButton[];
extern const DWORD g_dwRButton;
