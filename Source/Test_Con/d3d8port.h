#ifndef _D3D8PORT_H_1b37b920_7e12_4129_962a_39fc38ed2983_
#define _D3D8PORT_H_1b37b920_7e12_4129_962a_39fc38ed2983_

#include "MyLibraryUser.h"
#include <d3d9.h>

/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:   d3d8.h
 *  Content:    Direct3D include file
 *
 ****************************************************************************/

#ifndef _D3D8_H_
#define _D3D8_H_

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0800
#endif  //DIRECT3D_VERSION

// include this file content only if compiling for DX8 interfaces
#if(DIRECT3D_VERSION >= 0x0800)


/* This identifier is passed to Direct3DCreate8 in order to ensure that an
 * application was built against the correct header files. This number is
 * incremented whenever a header (or other) change would require applications
 * to be rebuilt. If the version doesn't match, Direct3DCreate8 will fail.
 * (The number itself has no meaning.)*/

#define D3D8_SDK_VERSION 220


#include <stdlib.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

#include <windows.h>

#if !defined(HMONITOR_DECLARED) && (WINVER < 0x0500)
    #define HMONITOR_DECLARED
    DECLARE_HANDLE(HMONITOR);
#endif

#define D3DAPI WINAPI

/*
 * Interface IID's
 */
#if defined( _WIN32 ) && !defined( _NO_COM)

/* IID_IDirect3D8 */
/* {1DD9E8DA-1C77-4d40-B0CF-98FEFDFF9512} */
DEFINE_GUID(IID_IDirect3D8, 0x1dd9e8da, 0x1c77, 0x4d40, 0xb0, 0xcf, 0x98, 0xfe, 0xfd, 0xff, 0x95, 0x12);

/* IID_IDirect3DDevice8 */
/* {7385E5DF-8FE8-41D5-86B6-D7B48547B6CF} */
DEFINE_GUID(IID_IDirect3DDevice8, 0x7385e5df, 0x8fe8, 0x41d5, 0x86, 0xb6, 0xd7, 0xb4, 0x85, 0x47, 0xb6, 0xcf);

/* IID_IDirect3DResource8 */
/* {1B36BB7B-09B7-410a-B445-7D1430D7B33F} */
DEFINE_GUID(IID_IDirect3DResource8, 0x1b36bb7b, 0x9b7, 0x410a, 0xb4, 0x45, 0x7d, 0x14, 0x30, 0xd7, 0xb3, 0x3f);

/* IID_IDirect3DBaseTexture8 */
/* {B4211CFA-51B9-4a9f-AB78-DB99B2BB678E} */
DEFINE_GUID(IID_IDirect3DBaseTexture8, 0xb4211cfa, 0x51b9, 0x4a9f, 0xab, 0x78, 0xdb, 0x99, 0xb2, 0xbb, 0x67, 0x8e);

/* IID_IDirect3DTexture8 */
/* {E4CDD575-2866-4f01-B12E-7EECE1EC9358} */
DEFINE_GUID(IID_IDirect3DTexture8, 0xe4cdd575, 0x2866, 0x4f01, 0xb1, 0x2e, 0x7e, 0xec, 0xe1, 0xec, 0x93, 0x58);

/* IID_IDirect3DCubeTexture8 */
/* {3EE5B968-2ACA-4c34-8BB5-7E0C3D19B750} */
DEFINE_GUID(IID_IDirect3DCubeTexture8, 0x3ee5b968, 0x2aca, 0x4c34, 0x8b, 0xb5, 0x7e, 0x0c, 0x3d, 0x19, 0xb7, 0x50);

/* IID_IDirect3DVolumeTexture8 */
/* {4B8AAAFA-140F-42ba-9131-597EAFAA2EAD} */
DEFINE_GUID(IID_IDirect3DVolumeTexture8, 0x4b8aaafa, 0x140f, 0x42ba, 0x91, 0x31, 0x59, 0x7e, 0xaf, 0xaa, 0x2e, 0xad);

/* IID_IDirect3DVertexBuffer8 */
/* {8AEEEAC7-05F9-44d4-B591-000B0DF1CB95} */
DEFINE_GUID(IID_IDirect3DVertexBuffer8, 0x8aeeeac7, 0x05f9, 0x44d4, 0xb5, 0x91, 0x00, 0x0b, 0x0d, 0xf1, 0xcb, 0x95);

/* IID_IDirect3DIndexBuffer8 */
/* {0E689C9A-053D-44a0-9D92-DB0E3D750F86} */
DEFINE_GUID(IID_IDirect3DIndexBuffer8, 0x0e689c9a, 0x053d, 0x44a0, 0x9d, 0x92, 0xdb, 0x0e, 0x3d, 0x75, 0x0f, 0x86);

/* IID_IDirect3DSurface8 */
/* {B96EEBCA-B326-4ea5-882F-2FF5BAE021DD} */
DEFINE_GUID(IID_IDirect3DSurface8, 0xb96eebca, 0xb326, 0x4ea5, 0x88, 0x2f, 0x2f, 0xf5, 0xba, 0xe0, 0x21, 0xdd);

/* IID_IDirect3DVolume8 */
/* {BD7349F5-14F1-42e4-9C79-972380DB40C0} */
DEFINE_GUID(IID_IDirect3DVolume8, 0xbd7349f5, 0x14f1, 0x42e4, 0x9c, 0x79, 0x97, 0x23, 0x80, 0xdb, 0x40, 0xc0);

/* IID_IDirect3DSwapChain8 */
/* {928C088B-76B9-4C6B-A536-A590853876CD} */
DEFINE_GUID(IID_IDirect3DSwapChain8, 0x928c088b, 0x76b9, 0x4c6b, 0xa5, 0x36, 0xa5, 0x90, 0x85, 0x38, 0x76, 0xcd);

#endif

#ifdef __cplusplus

interface IDirect3D8;
interface IDirect3DDevice8;

interface IDirect3DResource8;
interface IDirect3DBaseTexture8;
interface IDirect3DTexture8;
interface IDirect3DVolumeTexture8;
interface IDirect3DCubeTexture8;

interface IDirect3DVertexBuffer8;
interface IDirect3DIndexBuffer8;

interface IDirect3DSurface8;
interface IDirect3DVolume8;

interface IDirect3DSwapChain8;

#endif


typedef interface IDirect3D8                IDirect3D8;
typedef interface IDirect3DDevice8          IDirect3DDevice8;
typedef interface IDirect3DResource8        IDirect3DResource8;
typedef interface IDirect3DBaseTexture8     IDirect3DBaseTexture8;
typedef interface IDirect3DTexture8         IDirect3DTexture8;
typedef interface IDirect3DVolumeTexture8   IDirect3DVolumeTexture8;
typedef interface IDirect3DCubeTexture8     IDirect3DCubeTexture8;
typedef interface IDirect3DVertexBuffer8    IDirect3DVertexBuffer8;
typedef interface IDirect3DIndexBuffer8     IDirect3DIndexBuffer8;
typedef interface IDirect3DSurface8         IDirect3DSurface8;
typedef interface IDirect3DVolume8          IDirect3DVolume8;
typedef interface IDirect3DSwapChain8       IDirect3DSwapChain8;


// #include "d3d8types.h"

/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3d8types.h
 *  Content:    Direct3D capabilities include file
 *
 ***************************************************************************/

#ifndef _D3D8TYPES_H_
#define _D3D8TYPES_H_

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0800
#endif  //DIRECT3D_VERSION

// include this file content only if compiling for DX8 interfaces
#if(DIRECT3D_VERSION >= 0x0800)

#include <float.h>

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201) // anonymous unions warning
#if defined(_X86_) || defined(_IA64_)
#pragma pack(4)
#endif

// maps unsigned 8 bits/channel to D3DCOLOR
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

// maps floating point channels (0.f to 1.f range) to D3DCOLOR
#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))


typedef struct _D3DVIEWPORT8 {
    DWORD       X;
    DWORD       Y;            /* Viewport Top left */
    DWORD       Width;
    DWORD       Height;       /* Viewport Dimensions */
    float       MinZ;         /* Min/max of clip Volume */
    float       MaxZ;
} D3DVIEWPORT8;

/*
 * Values for clip fields.
 */

// Max number of user clipping planes, supported in D3D.
#define D3DMAXUSERCLIPPLANES 32

// These bits could be ORed together to use with D3DRS_CLIPPLANEENABLE
//
#define D3DCLIPPLANE0 (1 << 0)
#define D3DCLIPPLANE1 (1 << 1)
#define D3DCLIPPLANE2 (1 << 2)
#define D3DCLIPPLANE3 (1 << 3)
#define D3DCLIPPLANE4 (1 << 4)
#define D3DCLIPPLANE5 (1 << 5)

// The following bits are used in the ClipUnion and ClipIntersection
// members of the D3DCLIPSTATUS8
//

#define D3DCS_LEFT        0x00000001L
#define D3DCS_RIGHT       0x00000002L
#define D3DCS_TOP         0x00000004L
#define D3DCS_BOTTOM      0x00000008L
#define D3DCS_FRONT       0x00000010L
#define D3DCS_BACK        0x00000020L
#define D3DCS_PLANE0      0x00000040L
#define D3DCS_PLANE1      0x00000080L
#define D3DCS_PLANE2      0x00000100L
#define D3DCS_PLANE3      0x00000200L
#define D3DCS_PLANE4      0x00000400L
#define D3DCS_PLANE5      0x00000800L

#define D3DCS_ALL (D3DCS_LEFT   | \
                   D3DCS_RIGHT  | \
                   D3DCS_TOP    | \
                   D3DCS_BOTTOM | \
                   D3DCS_FRONT  | \
                   D3DCS_BACK   | \
                   D3DCS_PLANE0 | \
                   D3DCS_PLANE1 | \
                   D3DCS_PLANE2 | \
                   D3DCS_PLANE3 | \
                   D3DCS_PLANE4 | \
                   D3DCS_PLANE5)

typedef struct _D3DCLIPSTATUS8 {
    DWORD ClipUnion;
    DWORD ClipIntersection;
} D3DCLIPSTATUS8;

typedef struct _D3DMATERIAL8 {
    D3DCOLORVALUE   Diffuse;        /* Diffuse color RGBA */
    D3DCOLORVALUE   Ambient;        /* Ambient color RGB */
    D3DCOLORVALUE   Specular;       /* Specular 'shininess' */
    D3DCOLORVALUE   Emissive;       /* Emissive color RGB */
    float           Power;          /* Sharpness if specular highlight */
} D3DMATERIAL8;

typedef struct _D3DLIGHT8 {
    D3DLIGHTTYPE    Type;            /* Type of light source */
    D3DCOLORVALUE   Diffuse;         /* Diffuse color of light */
    D3DCOLORVALUE   Specular;        /* Specular color of light */
    D3DCOLORVALUE   Ambient;         /* Ambient color of light */
    D3DVECTOR       Position;         /* Position in world space */
    D3DVECTOR       Direction;        /* Direction in world space */
    float           Range;            /* Cutoff range */
    float           Falloff;          /* Falloff */
    float           Attenuation0;     /* Constant attenuation */
    float           Attenuation1;     /* Linear attenuation */
    float           Attenuation2;     /* Quadratic attenuation */
    float           Theta;            /* Inner angle of spotlight cone */
    float           Phi;              /* Outer angle of spotlight cone */
} D3DLIGHT8;

/*
 * Options for clearing
 */
#define D3DCLEAR_TARGET            0x00000001l  /* Clear target surface */
#define D3DCLEAR_ZBUFFER           0x00000002l  /* Clear target z buffer */
#define D3DCLEAR_STENCIL           0x00000004l  /* Clear stencil planes */

/*
 * The following defines the rendering states
 */

typedef struct _D3D8LINEPATTERN {
    WORD    wRepeatFactor;
    WORD    wLinePattern;
} D3D8LINEPATTERN;

#define D3DTS_WORLDMATRIX(index) (D3DTRANSFORMSTATETYPE)(index + 256)
#define D3DTS_WORLD  D3DTS_WORLDMATRIX(0)
#define D3DTS_WORLD1 D3DTS_WORLDMATRIX(1)
#define D3DTS_WORLD2 D3DTS_WORLDMATRIX(2)
#define D3DTS_WORLD3 D3DTS_WORLDMATRIX(3)

// Bias to apply to the texture coordinate set to apply a wrap to.
#define D3DRENDERSTATE_WRAPBIAS                 128UL

/* Flags to construct the WRAP render states */
#define D3DWRAP_U   0x00000001L
#define D3DWRAP_V   0x00000002L
#define D3DWRAP_W   0x00000004L

/* Flags to construct the WRAP render states for 1D thru 4D texture coordinates */
#define D3DWRAPCOORD_0   0x00000001L    // same as D3DWRAP_U
#define D3DWRAPCOORD_1   0x00000002L    // same as D3DWRAP_V
#define D3DWRAPCOORD_2   0x00000004L    // same as D3DWRAP_W
#define D3DWRAPCOORD_3   0x00000008L

/* Flags to construct D3DRS_COLORWRITEENABLE */
#define D3DCOLORWRITEENABLE_RED     (1L<<0)
#define D3DCOLORWRITEENABLE_GREEN   (1L<<1)
#define D3DCOLORWRITEENABLE_BLUE    (1L<<2)
#define D3DCOLORWRITEENABLE_ALPHA   (1L<<3)

/*
 * State enumerants for per-stage texture processing.
 */
typedef enum _D3D8TEXTURESTAGESTATETYPE
{
    D3D8TSS_COLOROP        =  1, /* D3DTEXTUREOP - per-stage blending controls for color channels */
    D3D8TSS_COLORARG1      =  2, /* D3DTA_* (texture arg) */
    D3D8TSS_COLORARG2      =  3, /* D3DTA_* (texture arg) */
    D3D8TSS_ALPHAOP        =  4, /* D3DTEXTUREOP - per-stage blending controls for alpha channel */
    D3D8TSS_ALPHAARG1      =  5, /* D3DTA_* (texture arg) */
    D3D8TSS_ALPHAARG2      =  6, /* D3DTA_* (texture arg) */
    D3D8TSS_BUMPENVMAT00   =  7, /* float (bump mapping matrix) */
    D3D8TSS_BUMPENVMAT01   =  8, /* float (bump mapping matrix) */
    D3D8TSS_BUMPENVMAT10   =  9, /* float (bump mapping matrix) */
    D3D8TSS_BUMPENVMAT11   = 10, /* float (bump mapping matrix) */
    D3D8TSS_TEXCOORDINDEX  = 11, /* identifies which set of texture coordinates index this texture */
    D3D8TSS_ADDRESSU       = 13, /* D3DTEXTUREADDRESS for U coordinate */
    D3D8TSS_ADDRESSV       = 14, /* D3DTEXTUREADDRESS for V coordinate */
    D3D8TSS_BORDERCOLOR    = 15, /* D3DCOLOR */
    D3D8TSS_MAGFILTER      = 16, /* D3DTEXTUREFILTER filter to use for magnification */
    D3D8TSS_MINFILTER      = 17, /* D3DTEXTUREFILTER filter to use for minification */
    D3D8TSS_MIPFILTER      = 18, /* D3DTEXTUREFILTER filter to use between mipmaps during minification */
    D3D8TSS_MIPMAPLODBIAS  = 19, /* float Mipmap LOD bias */
    D3D8TSS_MAXMIPLEVEL    = 20, /* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
    D3D8TSS_MAXANISOTROPY  = 21, /* DWORD maximum anisotropy */
    D3D8TSS_BUMPENVLSCALE  = 22, /* float scale for bump map luminance */
    D3D8TSS_BUMPENVLOFFSET = 23, /* float offset for bump map luminance */
    D3D8TSS_TEXTURETRANSFORMFLAGS = 24, /* D3DTEXTURETRANSFORMFLAGS controls texture transform */
    D3D8TSS_ADDRESSW       = 25, /* D3DTEXTUREADDRESS for W coordinate */
    D3D8TSS_COLORARG0      = 26, /* D3DTA_* third arg for triadic ops */
    D3D8TSS_ALPHAARG0      = 27, /* D3DTA_* third arg for triadic ops */
    D3D8TSS_RESULTARG      = 28, /* D3DTA_* arg for result (CURRENT or TEMP) */
    D3D8TSS_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
} D3D8TEXTURESTAGESTATETYPE;


/* Bits for Flags in ProcessVertices call */

#define D3DPV_DONOTCOPYDATA     (1 << 0)

//-------------------------------------------------------------------

// Flexible vertex format bits
//
#define D3D8FVF_POSITION_MASK    0x00E
#define D3D8FVF_LASTBETA_UBYTE4  0x1000
#define D3D8FVF_RESERVED2        0xE000  // 4 reserved bits

//---------------------------------------------------------------------
// Vertex Shaders
//

/*

Vertex Shader Declaration

The declaration portion of a vertex shader defines the static external
interface of the shader.  The information in the declaration includes:

- Assignments of vertex shader input registers to data streams.  These
assignments bind a specific vertex register to a single component within a
vertex stream.  A vertex stream element is identified by a byte offset
within the stream and a type.  The type specifies the arithmetic data type
plus the dimensionality (1, 2, 3, or 4 values).  Stream data which is
less than 4 values are always expanded out to 4 values with zero or more
0.F values and one 1.F value.

- Assignment of vertex shader input registers to implicit data from the
primitive tessellator.  This controls the loading of vertex data which is
not loaded from a stream, but rather is generated during primitive
tessellation prior to the vertex shader.

- Loading data into the constant memory at the time a shader is set as the
current shader.  Each token specifies values for one or more contiguous 4
DWORD constant registers.  This allows the shader to update an arbitrary
subset of the constant memory, overwriting the device state (which
contains the current values of the constant memory).  Note that these
values can be subsequently overwritten (between DrawPrimitive calls)
during the time a shader is bound to a device via the
SetVertexShaderConstant method.


Declaration arrays are single-dimensional arrays of DWORDs composed of
multiple tokens each of which is one or more DWORDs.  The single-DWORD
token value 0xFFFFFFFF is a special token used to indicate the end of the
declaration array.  The single DWORD token value 0x00000000 is a NOP token
with is ignored during the declaration parsing.  Note that 0x00000000 is a
valid value for DWORDs following the first DWORD for multiple word tokens.

[31:29] TokenType
    0x0 - NOP (requires all DWORD bits to be zero)
    0x1 - stream selector
    0x2 - stream data definition (map to vertex input memory)
    0x3 - vertex input memory from tessellator
    0x4 - constant memory from shader
    0x5 - extension
    0x6 - reserved
    0x7 - end-of-array (requires all DWORD bits to be 1)

NOP Token (single DWORD token)
    [31:29] 0x0
    [28:00] 0x0

Stream Selector (single DWORD token)
    [31:29] 0x1
    [28]    indicates whether this is a tessellator stream
    [27:04] 0x0
    [03:00] stream selector (0..15)

Stream Data Definition (single DWORD token)
    Vertex Input Register Load
      [31:29] 0x2
      [28]    0x0
      [27:20] 0x0
      [19:16] type (dimensionality and data type)
      [15:04] 0x0
      [03:00] vertex register address (0..15)
    Data Skip (no register load)
      [31:29] 0x2
      [28]    0x1
      [27:20] 0x0
      [19:16] count of DWORDS to skip over (0..15)
      [15:00] 0x0
    Vertex Input Memory from Tessellator Data (single DWORD token)
      [31:29] 0x3
      [28]    indicates whether data is normals or u/v
      [27:24] 0x0
      [23:20] vertex register address (0..15)
      [19:16] type (dimensionality)
      [15:04] 0x0
      [03:00] vertex register address (0..15)

Constant Memory from Shader (multiple DWORD token)
    [31:29] 0x4
    [28:25] count of 4*DWORD constants to load (0..15)
    [24:07] 0x0
    [06:00] constant memory address (0..95)

Extension Token (single or multiple DWORD token)
    [31:29] 0x5
    [28:24] count of additional DWORDs in token (0..31)
    [23:00] extension-specific information

End-of-array token (single DWORD token)
    [31:29] 0x7
    [28:00] 0x1fffffff

The stream selector token must be immediately followed by a contiguous set of stream data definition tokens.  This token sequence fully defines that stream, including the set of elements within the stream, the order in which the elements appear, the type of each element, and the vertex register into which to load an element.
Streams are allowed to include data which is not loaded into a vertex register, thus allowing data which is not used for this shader to exist in the vertex stream.  This skipped data is defined only by a count of DWORDs to skip over, since the type information is irrelevant.
The token sequence:
Stream Select: stream=0
Stream Data Definition (Load): type=FLOAT3; register=3
Stream Data Definition (Load): type=FLOAT3; register=4
Stream Data Definition (Skip): count=2
Stream Data Definition (Load): type=FLOAT2; register=7

defines stream zero to consist of 4 elements, 3 of which are loaded into registers and the fourth skipped over.  Register 3 is loaded with the first three DWORDs in each vertex interpreted as FLOAT data.  Register 4 is loaded with the 4th, 5th, and 6th DWORDs interpreted as FLOAT data.  The next two DWORDs (7th and 8th) are skipped over and not loaded into any vertex input register.   Register 7 is loaded with the 9th and 10th DWORDS interpreted as FLOAT data.
Placing of tokens other than NOPs between the Stream Selector and Stream Data Definition tokens is disallowed.

*/

typedef enum _D3DVSD_TOKENTYPE
{
    D3DVSD_TOKEN_NOP        = 0,    // NOP or extension
    D3DVSD_TOKEN_STREAM,            // stream selector
    D3DVSD_TOKEN_STREAMDATA,        // stream data definition (map to vertex input memory)
    D3DVSD_TOKEN_TESSELLATOR,       // vertex input memory from tessellator
    D3DVSD_TOKEN_CONSTMEM,          // constant memory from shader
    D3DVSD_TOKEN_EXT,               // extension
    D3DVSD_TOKEN_END = 7,           // end-of-array (requires all DWORD bits to be 1)
    D3DVSD_FORCE_DWORD = 0x7fffffff,// force 32-bit size enum
} D3DVSD_TOKENTYPE;

#define D3DVSD_TOKENTYPESHIFT   29
#define D3DVSD_TOKENTYPEMASK    (7 << D3DVSD_TOKENTYPESHIFT)

#define D3DVSD_STREAMNUMBERSHIFT 0
#define D3DVSD_STREAMNUMBERMASK (0xF << D3DVSD_STREAMNUMBERSHIFT)

#define D3DVSD_DATALOADTYPESHIFT 28
#define D3DVSD_DATALOADTYPEMASK (0x1 << D3DVSD_DATALOADTYPESHIFT)

#define D3DVSD_DATATYPESHIFT 16
#define D3DVSD_DATATYPEMASK (0xF << D3DVSD_DATATYPESHIFT)

#define D3DVSD_SKIPCOUNTSHIFT 16
#define D3DVSD_SKIPCOUNTMASK (0xF << D3DVSD_SKIPCOUNTSHIFT)

#define D3DVSD_VERTEXREGSHIFT 0
#define D3DVSD_VERTEXREGMASK (0x1F << D3DVSD_VERTEXREGSHIFT)

#define D3DVSD_VERTEXREGINSHIFT 20
#define D3DVSD_VERTEXREGINMASK (0xF << D3DVSD_VERTEXREGINSHIFT)

#define D3DVSD_CONSTCOUNTSHIFT 25
#define D3DVSD_CONSTCOUNTMASK (0xF << D3DVSD_CONSTCOUNTSHIFT)

#define D3DVSD_CONSTADDRESSSHIFT 0
#define D3DVSD_CONSTADDRESSMASK (0x7F << D3DVSD_CONSTADDRESSSHIFT)

#define D3DVSD_CONSTRSSHIFT 16
#define D3DVSD_CONSTRSMASK (0x1FFF << D3DVSD_CONSTRSSHIFT)

#define D3DVSD_EXTCOUNTSHIFT 24
#define D3DVSD_EXTCOUNTMASK (0x1F << D3DVSD_EXTCOUNTSHIFT)

#define D3DVSD_EXTINFOSHIFT 0
#define D3DVSD_EXTINFOMASK (0xFFFFFF << D3DVSD_EXTINFOSHIFT)

#define D3DVSD_MAKETOKENTYPE(tokenType) ((tokenType << D3DVSD_TOKENTYPESHIFT) & D3DVSD_TOKENTYPEMASK)

// macros for generation of CreateVertexShader Declaration token array

// Set current stream
// _StreamNumber [0..(MaxStreams-1)] stream to get data from
//
#define D3DVSD_STREAM( _StreamNumber ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAM) | (_StreamNumber))

// Set tessellator stream
//
#define D3DVSD_STREAMTESSSHIFT 28
#define D3DVSD_STREAMTESSMASK (1 << D3DVSD_STREAMTESSSHIFT)
#define D3DVSD_STREAM_TESS( ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAM) | (D3DVSD_STREAMTESSMASK))

// bind single vertex register to vertex element from vertex stream
//
// _VertexRegister [0..15] address of the vertex register
// _Type [D3DVSDT_*] dimensionality and arithmetic data type

#define D3DVSD_REG( _VertexRegister, _Type ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAMDATA) |            \
     ((_Type) << D3DVSD_DATATYPESHIFT) | (_VertexRegister))

// Skip _DWORDCount DWORDs in vertex
//
#define D3DVSD_SKIP( _DWORDCount ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_STREAMDATA) | 0x10000000 | \
     ((_DWORDCount) << D3DVSD_SKIPCOUNTSHIFT))

// load data into vertex shader constant memory
//
// _ConstantAddress [0..95] - address of constant array to begin filling data
// _Count [0..15] - number of constant vectors to load (4 DWORDs each)
// followed by 4*_Count DWORDS of data
//
#define D3DVSD_CONST( _ConstantAddress, _Count ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_CONSTMEM) | \
     ((_Count) << D3DVSD_CONSTCOUNTSHIFT) | (_ConstantAddress))

// enable tessellator generated normals
//
// _VertexRegisterIn  [0..15] address of vertex register whose input stream
//                            will be used in normal computation
// _VertexRegisterOut [0..15] address of vertex register to output the normal to
//
#define D3DVSD_TESSNORMAL( _VertexRegisterIn, _VertexRegisterOut ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_TESSELLATOR) | \
     ((_VertexRegisterIn) << D3DVSD_VERTEXREGINSHIFT) | \
     ((0x02) << D3DVSD_DATATYPESHIFT) | (_VertexRegisterOut))

// enable tessellator generated surface parameters
//
// _VertexRegister [0..15] address of vertex register to output parameters
//
#define D3DVSD_TESSUV( _VertexRegister ) \
    (D3DVSD_MAKETOKENTYPE(D3DVSD_TOKEN_TESSELLATOR) | 0x10000000 | \
     ((0x01) << D3DVSD_DATATYPESHIFT) | (_VertexRegister))

// Generates END token
//
#define D3DVSD_END() 0xFFFFFFFF

// Generates NOP token
#define D3DVSD_NOP() 0x00000000

// bit declarations for _Type fields
#define D3DVSDT_FLOAT1      0x00    // 1D float expanded to (value, 0., 0., 1.)
#define D3DVSDT_FLOAT2      0x01    // 2D float expanded to (value, value, 0., 1.)
#define D3DVSDT_FLOAT3      0x02    // 3D float expanded to (value, value, value, 1.)
#define D3DVSDT_FLOAT4      0x03    // 4D float
#define D3DVSDT_D3DCOLOR    0x04    // 4D packed unsigned bytes mapped to 0. to 1. range
                                    // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
#define D3DVSDT_UBYTE4      0x05    // 4D unsigned byte
#define D3DVSDT_SHORT2      0x06    // 2D signed short expanded to (value, value, 0., 1.)
#define D3DVSDT_SHORT4      0x07    // 4D signed short

// assignments of vertex input registers for fixed function vertex shader
//
#define D3DVSDE_POSITION        0
#define D3DVSDE_BLENDWEIGHT     1
#define D3DVSDE_BLENDINDICES    2
#define D3DVSDE_NORMAL          3
#define D3DVSDE_PSIZE           4
#define D3DVSDE_DIFFUSE         5
#define D3DVSDE_SPECULAR        6
#define D3DVSDE_TEXCOORD0       7
#define D3DVSDE_TEXCOORD1       8
#define D3DVSDE_TEXCOORD2       9
#define D3DVSDE_TEXCOORD3       10
#define D3DVSDE_TEXCOORD4       11
#define D3DVSDE_TEXCOORD5       12
#define D3DVSDE_TEXCOORD6       13
#define D3DVSDE_TEXCOORD7       14
#define D3DVSDE_POSITION2       15
#define D3DVSDE_NORMAL2         16

// Maximum supported number of texture coordinate sets
#define D3DDP_MAXTEXCOORD   8


//
// Co-Issue Instruction Modifier - if set then this instruction is to be
// issued in parallel with the previous instruction(s) for which this bit
// is not set.
//
#define D3DSI_COISSUE           0x40000000

//
// Parameter Token Bit Definitions
//
#define D3D8SP_REGNUM_MASK       0x00001FFF

// destination parameter write mask
#define D3DSP_WRITEMASK_0       0x00010000  // Component 0 (X;Red)
#define D3DSP_WRITEMASK_1       0x00020000  // Component 1 (Y;Green)
#define D3DSP_WRITEMASK_2       0x00040000  // Component 2 (Z;Blue)
#define D3DSP_WRITEMASK_3       0x00080000  // Component 3 (W;Alpha)
#define D3DSP_WRITEMASK_ALL     0x000F0000  // All Components

// destination parameter 
#define D3DSP_DSTSHIFT_SHIFT    24
#define D3DSP_DSTSHIFT_MASK     0x0F000000

// destination/source parameter register type

typedef enum _D3D8SHADER_PARAM_REGISTER_TYPE
{
    D3D8SPR_TEMP     = 0<<D3DSP_REGTYPE_SHIFT, // Temporary Register File
    D3D8SPR_INPUT    = 1<<D3DSP_REGTYPE_SHIFT, // Input Register File
    D3D8SPR_CONST    = 2<<D3DSP_REGTYPE_SHIFT, // Constant Register File
    D3D8SPR_ADDR     = 3<<D3DSP_REGTYPE_SHIFT, // Address Register (VS)
    D3D8SPR_TEXTURE  = 3<<D3DSP_REGTYPE_SHIFT, // Texture Register File (PS)
    D3D8SPR_RASTOUT  = 4<<D3DSP_REGTYPE_SHIFT, // Rasterizer Register File
    D3D8SPR_ATTROUT  = 5<<D3DSP_REGTYPE_SHIFT, // Attribute Output Register File
    D3D8SPR_TEXCRDOUT= 6<<D3DSP_REGTYPE_SHIFT, // Texture Coordinate Output Register File
    D3D8SPR_FORCE_DWORD  = 0x7fffffff,         // force 32-bit size enum
} D3D8SHADER_PARAM_REGISTER_TYPE;



// Source operand swizzle definitions
//
#define D3DVS_SWIZZLE_SHIFT     16
#define D3DVS_SWIZZLE_MASK      0x00FF0000

// The following bits define where to take component X from:

#define D3DVS_X_X       (0 << D3DVS_SWIZZLE_SHIFT)
#define D3DVS_X_Y       (1 << D3DVS_SWIZZLE_SHIFT)
#define D3DVS_X_Z       (2 << D3DVS_SWIZZLE_SHIFT)
#define D3DVS_X_W       (3 << D3DVS_SWIZZLE_SHIFT)

// The following bits define where to take component Y from:

#define D3DVS_Y_X       (0 << (D3DVS_SWIZZLE_SHIFT + 2))
#define D3DVS_Y_Y       (1 << (D3DVS_SWIZZLE_SHIFT + 2))
#define D3DVS_Y_Z       (2 << (D3DVS_SWIZZLE_SHIFT + 2))
#define D3DVS_Y_W       (3 << (D3DVS_SWIZZLE_SHIFT + 2))

// The following bits define where to take component Z from:

#define D3DVS_Z_X       (0 << (D3DVS_SWIZZLE_SHIFT + 4))
#define D3DVS_Z_Y       (1 << (D3DVS_SWIZZLE_SHIFT + 4))
#define D3DVS_Z_Z       (2 << (D3DVS_SWIZZLE_SHIFT + 4))
#define D3DVS_Z_W       (3 << (D3DVS_SWIZZLE_SHIFT + 4))

// The following bits define where to take component W from:

#define D3DVS_W_X       (0 << (D3DVS_SWIZZLE_SHIFT + 6))
#define D3DVS_W_Y       (1 << (D3DVS_SWIZZLE_SHIFT + 6))
#define D3DVS_W_Z       (2 << (D3DVS_SWIZZLE_SHIFT + 6))
#define D3DVS_W_W       (3 << (D3DVS_SWIZZLE_SHIFT + 6))

// Value when there is no swizzle (X is taken from X, Y is taken from Y,
// Z is taken from Z, W is taken from W
//
#define D3DVS_NOSWIZZLE (D3DVS_X_X | D3DVS_Y_Y | D3DVS_Z_Z | D3DVS_W_W)

// source parameter swizzle
#define D3DSP_SWIZZLE_SHIFT     16
#define D3DSP_SWIZZLE_MASK      0x00FF0000

#define D3DSP_NOSWIZZLE \
    ( (0 << (D3DSP_SWIZZLE_SHIFT + 0)) | \
      (1 << (D3DSP_SWIZZLE_SHIFT + 2)) | \
      (2 << (D3DSP_SWIZZLE_SHIFT + 4)) | \
      (3 << (D3DSP_SWIZZLE_SHIFT + 6)) )

// pixel-shader swizzle ops
#define D3DSP_REPLICATERED \
    ( (0 << (D3DSP_SWIZZLE_SHIFT + 0)) | \
      (0 << (D3DSP_SWIZZLE_SHIFT + 2)) | \
      (0 << (D3DSP_SWIZZLE_SHIFT + 4)) | \
      (0 << (D3DSP_SWIZZLE_SHIFT + 6)) )

#define D3DSP_REPLICATEGREEN \
    ( (1 << (D3DSP_SWIZZLE_SHIFT + 0)) | \
      (1 << (D3DSP_SWIZZLE_SHIFT + 2)) | \
      (1 << (D3DSP_SWIZZLE_SHIFT + 4)) | \
      (1 << (D3DSP_SWIZZLE_SHIFT + 6)) )

#define D3DSP_REPLICATEBLUE \
    ( (2 << (D3DSP_SWIZZLE_SHIFT + 0)) | \
      (2 << (D3DSP_SWIZZLE_SHIFT + 2)) | \
      (2 << (D3DSP_SWIZZLE_SHIFT + 4)) | \
      (2 << (D3DSP_SWIZZLE_SHIFT + 6)) )

#define D3DSP_REPLICATEALPHA \
    ( (3 << (D3DSP_SWIZZLE_SHIFT + 0)) | \
      (3 << (D3DSP_SWIZZLE_SHIFT + 2)) | \
      (3 << (D3DSP_SWIZZLE_SHIFT + 4)) | \
      (3 << (D3DSP_SWIZZLE_SHIFT + 6)) )

// pixel shader version token
#define D3DPS_VERSION(_Major,_Minor) (0xFFFF0000|((_Major)<<8)|(_Minor))

// vertex shader version token
#define D3DVS_VERSION(_Major,_Minor) (0xFFFE0000|((_Major)<<8)|(_Minor))

// extract major/minor from version cap
#define D3DSHADER_VERSION_MAJOR(_Version) (((_Version)>>8)&0xFF)
#define D3DSHADER_VERSION_MINOR(_Version) (((_Version)>>0)&0xFF)

// destination/source parameter register type
#define D3DSI_COMMENTSIZE_SHIFT     16
#define D3DSI_COMMENTSIZE_MASK      0x7FFF0000
#define D3DSHADER_COMMENT(_DWordSize) \
    ((((_DWordSize)<<D3DSI_COMMENTSIZE_SHIFT)&D3DSI_COMMENTSIZE_MASK)|D3DSIO_COMMENT)

// pixel/vertex shader end token
#define D3DPS_END()  0x0000FFFF
#define D3DVS_END()  0x0000FFFF

//---------------------------------------------------------------------

// High order surfaces
//

typedef enum _D3DORDERTYPE
{
   D3DORDER_LINEAR      = D3DDEGREE_LINEAR,
   D3DORDER_QUADRATIC   = D3DDEGREE_QUADRATIC,
   D3DORDER_CUBIC       = D3DDEGREE_CUBIC,
   D3DORDER_QUINTIC     = D3DDEGREE_QUINTIC,
   D3DORDER_FORCE_DWORD = D3DDEGREE_FORCE_DWORD,
} D3DORDERTYPE;


//---------------------------------------------------------------------


/* SwapEffects */
typedef enum _D3D8SWAPEFFECT
{
    D3D8SWAPEFFECT_DISCARD           = 1,
    D3D8SWAPEFFECT_FLIP              = 2,
    D3D8SWAPEFFECT_COPY              = 3,
    D3D8SWAPEFFECT_COPY_VSYNC        = 4,

    D3D8SWAPEFFECT_FORCE_DWORD       = 0x7fffffff
} D3D8SWAPEFFECT;


/* RefreshRate pre-defines */
#define D3DPRESENT_RATE_DEFAULT         0x00000000
#define D3DPRESENT_RATE_UNLIMITED       0x7fffffff


/* Resize Optional Parameters */
typedef struct _D3D8PRESENT_PARAMETERS_
{
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    D3DFORMAT           BackBufferFormat;
    UINT                BackBufferCount;

    D3DMULTISAMPLE_TYPE MultiSampleType;

    D3D8SWAPEFFECT      SwapEffect;
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    D3DFORMAT           AutoDepthStencilFormat;
    DWORD               Flags;

    /* Following elements must be zero for Windowed mode */
    UINT                FullScreen_RefreshRateInHz;
    UINT                FullScreen_PresentationInterval;

} D3D8PRESENT_PARAMETERS;



/* Usages */
#define D3DUSAGE_RENDERTARGET       (0x00000001L)
#define D3DUSAGE_DEPTHSTENCIL       (0x00000002L)

/* Usages for Vertex/Index buffers */
#define D3DUSAGE_WRITEONLY          (0x00000008L)
#define D3DUSAGE_SOFTWAREPROCESSING (0x00000010L)
#define D3DUSAGE_DONOTCLIP          (0x00000020L)
#define D3DUSAGE_POINTS             (0x00000040L)
#define D3DUSAGE_RTPATCHES          (0x00000080L)
#define D3DUSAGE_NPATCHES           (0x00000100L)
#define D3DUSAGE_DYNAMIC            (0x00000200L)



/* Lock flags */

#define D3DLOCK_READONLY           0x00000010L
#define D3DLOCK_DISCARD             0x00002000L
#define D3DLOCK_NOOVERWRITE        0x00001000L
#define D3DLOCK_NOSYSLOCK          0x00000800L

#define D3DLOCK_NO_DIRTY_UPDATE     0x00008000L



/* Surface Description */
typedef struct _D3D8SURFACE_DESC
{
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    UINT                Size;

    D3DMULTISAMPLE_TYPE MultiSampleType;
    UINT                Width;
    UINT                Height;
} D3D8SURFACE_DESC;

typedef struct _D3D8VOLUME_DESC
{
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    UINT                Size;

    UINT                Width;
    UINT                Height;
    UINT                Depth;
} D3D8VOLUME_DESC;

/* Structures for high order primitives */
typedef struct _D3D8RECTPATCH_INFO
{
    UINT                StartVertexOffsetWidth;
    UINT                StartVertexOffsetHeight;
    UINT                Width;
    UINT                Height;
    UINT                Stride;
    D3DBASISTYPE        Basis;
    D3DORDERTYPE        Order;
} D3D8RECTPATCH_INFO;

/* Adapter Identifier */

#define MAX_DEVICE_IDENTIFIER_STRING        512
typedef struct _D3DADAPTER_IDENTIFIER8
{
    char            Driver[MAX_DEVICE_IDENTIFIER_STRING];
    char            Description[MAX_DEVICE_IDENTIFIER_STRING];

#ifdef _WIN32
    LARGE_INTEGER   DriverVersion;            /* Defined for 32 bit components */
#else
    DWORD           DriverVersionLowPart;     /* Defined for 16 bit driver components */
    DWORD           DriverVersionHighPart;
#endif

    DWORD           VendorId;
    DWORD           DeviceId;
    DWORD           SubSysId;
    DWORD           Revision;

    GUID            DeviceIdentifier;

    DWORD           WHQLLevel;

} D3DADAPTER_IDENTIFIER8;


/* Raster Status structure returned by GetRasterStatus */



/* Debug monitor tokens (DEBUG only)

   Note that if D3DRS_DEBUGMONITORTOKEN is set, the call is treated as
   passing a token to the debug monitor.  For example, if, after passing
   D3DDMT_ENABLE/DISABLE to D3DRS_DEBUGMONITORTOKEN other token values
   are passed in, the enabled/disabled state of the debug
   monitor will still persist.

   The debug monitor defaults to enabled.

   Calling GetRenderState on D3DRS_DEBUGMONITORTOKEN is not of any use.
*/

// GetInfo IDs

#define D3DDEVINFOID_RESOURCEMANAGER    5           /* Used with D3DDEVINFO_RESOURCEMANAGER */
#define D3DDEVINFOID_VERTEXSTATS        6           /* Used with D3DDEVINFO_D3DVERTEXSTATS */


#pragma pack()
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4201)
#endif

#endif /* (DIRECT3D_VERSION >= 0x0800) */
#endif /* _D3D8TYPES(P)_H_ */



// #include "d3d8caps.h"

/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3d8caps.h
 *  Content:    Direct3D capabilities include file
 *
 ***************************************************************************/

#ifndef _D3D8CAPS_H
#define _D3D8CAPS_H

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0800
#endif  //DIRECT3D_VERSION

// include this file content only if compiling for DX8 interfaces
#if(DIRECT3D_VERSION >= 0x0800)

#if defined(_X86_) || defined(_IA64_)
#pragma pack(4)
#endif

typedef struct _D3DCAPS8
{
    /* Device Info */
    D3DDEVTYPE  DeviceType;
    UINT    AdapterOrdinal;

    /* Caps from DX7 Draw */
    DWORD   Caps;
    DWORD   Caps2;
    DWORD   Caps3;
    DWORD   PresentationIntervals;

    /* Cursor Caps */
    DWORD   CursorCaps;

    /* 3D Device Caps */
    DWORD   DevCaps;

    DWORD   PrimitiveMiscCaps;
    DWORD   RasterCaps;
    DWORD   ZCmpCaps;
    DWORD   SrcBlendCaps;
    DWORD   DestBlendCaps;
    DWORD   AlphaCmpCaps;
    DWORD   ShadeCaps;
    DWORD   TextureCaps;
    DWORD   TextureFilterCaps;          // D3DPTFILTERCAPS for IDirect3DTexture8's
    DWORD   CubeTextureFilterCaps;      // D3DPTFILTERCAPS for IDirect3DCubeTexture8's
    DWORD   VolumeTextureFilterCaps;    // D3DPTFILTERCAPS for IDirect3DVolumeTexture8's
    DWORD   TextureAddressCaps;         // D3DPTADDRESSCAPS for IDirect3DTexture8's
    DWORD   VolumeTextureAddressCaps;   // D3DPTADDRESSCAPS for IDirect3DVolumeTexture8's

    DWORD   LineCaps;                   // D3DLINECAPS

    DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;

    DWORD   MaxTextureRepeat;
    DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
    float   MaxVertexW;

    float   GuardBandLeft;
    float   GuardBandTop;
    float   GuardBandRight;
    float   GuardBandBottom;

    float   ExtentsAdjust;
    DWORD   StencilCaps;

    DWORD   FVFCaps;
    DWORD   TextureOpCaps;
    DWORD   MaxTextureBlendStages;
    DWORD   MaxSimultaneousTextures;

    DWORD   VertexProcessingCaps;
    DWORD   MaxActiveLights;
    DWORD   MaxUserClipPlanes;
    DWORD   MaxVertexBlendMatrices;
    DWORD   MaxVertexBlendMatrixIndex;

    float   MaxPointSize;

    DWORD   MaxPrimitiveCount;          // max number of primitives per DrawPrimitive call
    DWORD   MaxVertexIndex;
    DWORD   MaxStreams;
    DWORD   MaxStreamStride;            // max stride for SetStreamSource

    DWORD   VertexShaderVersion;
    DWORD   MaxVertexShaderConst;       // number of vertex shader constant registers

    DWORD   PixelShaderVersion;
    float   MaxPixelShaderValue;        // max value of pixel shader arithmetic component

} D3DCAPS8;

//
// BIT DEFINES FOR D3DCAPS8 DWORD MEMBERS
//

//
// Caps
//
#define D3DCAPS_READ_SCANLINE           0x00020000L

//
// Caps2
//
#define D3DCAPS2_NO2DDURING3DSCENE      0x00000002L
#define D3DCAPS2_FULLSCREENGAMMA        0x00020000L
#define D3DCAPS2_CANRENDERWINDOWED      0x00080000L
#define D3DCAPS2_CANCALIBRATEGAMMA      0x00100000L
#define D3DCAPS2_RESERVED               0x02000000L
#define D3DCAPS2_CANMANAGERESOURCE      0x10000000L
#define D3DCAPS2_DYNAMICTEXTURES        0x20000000L

//
// Caps3
//
#define D3DCAPS3_RESERVED               0x8000001fL

// Indicates that the device can respect the ALPHABLENDENABLE render state
// when fullscreen while using the FLIP or DISCARD swap effect.
// COPY and COPYVSYNC swap effects work whether or not this flag is set.
#define D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD   0x00000020L

//
// PresentationIntervals
//
#define D3DPRESENT_INTERVAL_DEFAULT     0x00000000L
#define D3DPRESENT_INTERVAL_ONE         0x00000001L
#define D3DPRESENT_INTERVAL_TWO         0x00000002L
#define D3DPRESENT_INTERVAL_THREE       0x00000004L
#define D3DPRESENT_INTERVAL_FOUR        0x00000008L
#define D3DPRESENT_INTERVAL_IMMEDIATE   0x80000000L

//
// CursorCaps
//
// Driver supports HW color cursor in at least hi-res modes(height >=400)
#define D3DCURSORCAPS_COLOR             0x00000001L
// Driver supports HW cursor also in low-res modes(height < 400)
#define D3DCURSORCAPS_LOWRES            0x00000002L

//
// DevCaps
//
#define D3DDEVCAPS_EXECUTESYSTEMMEMORY  0x00000010L /* Device can use execute buffers from system memory */
#define D3DDEVCAPS_EXECUTEVIDEOMEMORY   0x00000020L /* Device can use execute buffers from video memory */
#define D3DDEVCAPS_TLVERTEXSYSTEMMEMORY 0x00000040L /* Device can use TL buffers from system memory */
#define D3DDEVCAPS_TLVERTEXVIDEOMEMORY  0x00000080L /* Device can use TL buffers from video memory */
#define D3DDEVCAPS_TEXTURESYSTEMMEMORY  0x00000100L /* Device can texture from system memory */
#define D3DDEVCAPS_TEXTUREVIDEOMEMORY   0x00000200L /* Device can texture from device memory */
#define D3DDEVCAPS_DRAWPRIMTLVERTEX     0x00000400L /* Device can draw TLVERTEX primitives */
#define D3DDEVCAPS_CANRENDERAFTERFLIP   0x00000800L /* Device can render without waiting for flip to complete */
#define D3DDEVCAPS_TEXTURENONLOCALVIDMEM 0x00001000L /* Device can texture from nonlocal video memory */
#define D3DDEVCAPS_DRAWPRIMITIVES2      0x00002000L /* Device can support DrawPrimitives2 */
#define D3DDEVCAPS_SEPARATETEXTUREMEMORIES 0x00004000L /* Device is texturing from separate memory pools */
#define D3DDEVCAPS_DRAWPRIMITIVES2EX    0x00008000L /* Device can support Extended DrawPrimitives2 i.e. DX7 compliant driver*/
#define D3DDEVCAPS_HWTRANSFORMANDLIGHT  0x00010000L /* Device can support transformation and lighting in hardware and DRAWPRIMITIVES2EX must be also */
#define D3DDEVCAPS_CANBLTSYSTONONLOCAL  0x00020000L /* Device supports a Tex Blt from system memory to non-local vidmem */
#define D3DDEVCAPS_HWRASTERIZATION      0x00080000L /* Device has HW acceleration for rasterization */
#define D3DDEVCAPS_PUREDEVICE           0x00100000L /* Device supports D3DCREATE_PUREDEVICE */
#define D3DDEVCAPS_QUINTICRTPATCHES     0x00200000L /* Device supports quintic Beziers and BSplines */
#define D3DDEVCAPS_RTPATCHES            0x00400000L /* Device supports Rect and Tri patches */
#define D3DDEVCAPS_RTPATCHHANDLEZERO    0x00800000L /* Indicates that RT Patches may be drawn efficiently using handle 0 */
#define D3DDEVCAPS_NPATCHES             0x01000000L /* Device supports N-Patches */

//
// PrimitiveMiscCaps
//
#define D3DPMISCCAPS_MASKZ              0x00000002L
#define D3DPMISCCAPS_LINEPATTERNREP     0x00000004L
#define D3DPMISCCAPS_CULLNONE           0x00000010L
#define D3DPMISCCAPS_CULLCW             0x00000020L
#define D3DPMISCCAPS_CULLCCW            0x00000040L
#define D3DPMISCCAPS_COLORWRITEENABLE   0x00000080L
#define D3DPMISCCAPS_CLIPPLANESCALEDPOINTS 0x00000100L /* Device correctly clips scaled points to clip planes */
#define D3DPMISCCAPS_CLIPTLVERTS        0x00000200L /* device will clip post-transformed vertex primitives */
#define D3DPMISCCAPS_TSSARGTEMP         0x00000400L /* device supports D3DTA_TEMP for temporary register */
#define D3DPMISCCAPS_BLENDOP            0x00000800L /* device supports D3DRS_BLENDOP */
#define D3DPMISCCAPS_NULLREFERENCE      0x00001000L /* Reference Device that doesnt render */

//
// LineCaps
//
#define D3DLINECAPS_TEXTURE             0x00000001L
#define D3DLINECAPS_ZTEST               0x00000002L
#define D3DLINECAPS_BLEND               0x00000004L
#define D3DLINECAPS_ALPHACMP            0x00000008L
#define D3DLINECAPS_FOG                 0x00000010L

//
// RasterCaps
//
#define D3DPRASTERCAPS_DITHER           0x00000001L
#define D3DPRASTERCAPS_PAT              0x00000008L
#define D3DPRASTERCAPS_ZTEST            0x00000010L
#define D3DPRASTERCAPS_FOGVERTEX        0x00000080L
#define D3DPRASTERCAPS_FOGTABLE         0x00000100L
#define D3DPRASTERCAPS_ANTIALIASEDGES   0x00001000L
#define D3DPRASTERCAPS_MIPMAPLODBIAS    0x00002000L
#define D3DPRASTERCAPS_ZBIAS            0x00004000L
#define D3DPRASTERCAPS_ZBUFFERLESSHSR   0x00008000L
#define D3DPRASTERCAPS_FOGRANGE         0x00010000L
#define D3DPRASTERCAPS_ANISOTROPY       0x00020000L
#define D3DPRASTERCAPS_WBUFFER          0x00040000L
#define D3DPRASTERCAPS_WFOG             0x00100000L
#define D3DPRASTERCAPS_ZFOG             0x00200000L
#define D3DPRASTERCAPS_COLORPERSPECTIVE 0x00400000L /* Device iterates colors perspective correct */
#define D3DPRASTERCAPS_STRETCHBLTMULTISAMPLE  0x00800000L

//
// ZCmpCaps, AlphaCmpCaps
//
#define D3DPCMPCAPS_NEVER               0x00000001L
#define D3DPCMPCAPS_LESS                0x00000002L
#define D3DPCMPCAPS_EQUAL               0x00000004L
#define D3DPCMPCAPS_LESSEQUAL           0x00000008L
#define D3DPCMPCAPS_GREATER             0x00000010L
#define D3DPCMPCAPS_NOTEQUAL            0x00000020L
#define D3DPCMPCAPS_GREATEREQUAL        0x00000040L
#define D3DPCMPCAPS_ALWAYS              0x00000080L

//
// SourceBlendCaps, DestBlendCaps
//
#define D3DPBLENDCAPS_ZERO              0x00000001L
#define D3DPBLENDCAPS_ONE               0x00000002L
#define D3DPBLENDCAPS_SRCCOLOR          0x00000004L
#define D3DPBLENDCAPS_INVSRCCOLOR       0x00000008L
#define D3DPBLENDCAPS_SRCALPHA          0x00000010L
#define D3DPBLENDCAPS_INVSRCALPHA       0x00000020L
#define D3DPBLENDCAPS_DESTALPHA         0x00000040L
#define D3DPBLENDCAPS_INVDESTALPHA      0x00000080L
#define D3DPBLENDCAPS_DESTCOLOR         0x00000100L
#define D3DPBLENDCAPS_INVDESTCOLOR      0x00000200L
#define D3DPBLENDCAPS_SRCALPHASAT       0x00000400L
#define D3DPBLENDCAPS_BOTHSRCALPHA      0x00000800L
#define D3DPBLENDCAPS_BOTHINVSRCALPHA   0x00001000L

//
// ShadeCaps
//
#define D3DPSHADECAPS_COLORGOURAUDRGB       0x00000008L
#define D3DPSHADECAPS_SPECULARGOURAUDRGB    0x00000200L
#define D3DPSHADECAPS_ALPHAGOURAUDBLEND     0x00004000L
#define D3DPSHADECAPS_FOGGOURAUD            0x00080000L

//
// TextureCaps
//
#define D3DPTEXTURECAPS_PERSPECTIVE         0x00000001L /* Perspective-correct texturing is supported */
#define D3DPTEXTURECAPS_POW2                0x00000002L /* Power-of-2 texture dimensions are required - applies to non-Cube/Volume textures only. */
#define D3DPTEXTURECAPS_ALPHA               0x00000004L /* Alpha in texture pixels is supported */
#define D3DPTEXTURECAPS_SQUAREONLY          0x00000020L /* Only square textures are supported */
#define D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE 0x00000040L /* Texture indices are not scaled by the texture size prior to interpolation */
#define D3DPTEXTURECAPS_ALPHAPALETTE        0x00000080L /* Device can draw alpha from texture palettes */
// Device can use non-POW2 textures if:
//  1) D3DTEXTURE_ADDRESS is set to CLAMP for this texture's stage
//  2) D3DRS_WRAP(N) is zero for this texture's coordinates
//  3) mip mapping is not enabled (use magnification filter only)
#define D3DPTEXTURECAPS_NONPOW2CONDITIONAL  0x00000100L
#define D3DPTEXTURECAPS_PROJECTED           0x00000400L /* Device can do D3DTTFF_PROJECTED */
#define D3DPTEXTURECAPS_CUBEMAP             0x00000800L /* Device can do cubemap textures */
#define D3DPTEXTURECAPS_VOLUMEMAP           0x00002000L /* Device can do volume textures */
#define D3DPTEXTURECAPS_MIPMAP              0x00004000L /* Device can do mipmapped textures */
#define D3DPTEXTURECAPS_MIPVOLUMEMAP        0x00008000L /* Device can do mipmapped volume textures */
#define D3DPTEXTURECAPS_MIPCUBEMAP          0x00010000L /* Device can do mipmapped cube maps */
#define D3DPTEXTURECAPS_CUBEMAP_POW2        0x00020000L /* Device requires that cubemaps be power-of-2 dimension */
#define D3DPTEXTURECAPS_VOLUMEMAP_POW2      0x00040000L /* Device requires that volume maps be power-of-2 dimension */

//
// TextureFilterCaps
//
#define D3DPTFILTERCAPS_MINFPOINT           0x00000100L /* Min Filter */
#define D3DPTFILTERCAPS_MINFLINEAR          0x00000200L
#define D3DPTFILTERCAPS_MINFANISOTROPIC     0x00000400L
#define D3DPTFILTERCAPS_MIPFPOINT           0x00010000L /* Mip Filter */
#define D3DPTFILTERCAPS_MIPFLINEAR          0x00020000L
#define D3DPTFILTERCAPS_MAGFPOINT           0x01000000L /* Mag Filter */
#define D3DPTFILTERCAPS_MAGFLINEAR          0x02000000L
#define D3DPTFILTERCAPS_MAGFANISOTROPIC     0x04000000L
#define D3DPTFILTERCAPS_MAGFAFLATCUBIC      0x08000000L
#define D3DPTFILTERCAPS_MAGFGAUSSIANCUBIC   0x10000000L

//
// TextureAddressCaps
//
#define D3DPTADDRESSCAPS_WRAP           0x00000001L
#define D3DPTADDRESSCAPS_MIRROR         0x00000002L
#define D3DPTADDRESSCAPS_CLAMP          0x00000004L
#define D3DPTADDRESSCAPS_BORDER         0x00000008L
#define D3DPTADDRESSCAPS_INDEPENDENTUV  0x00000010L
#define D3DPTADDRESSCAPS_MIRRORONCE     0x00000020L

//
// StencilCaps
//
#define D3DSTENCILCAPS_KEEP             0x00000001L
#define D3DSTENCILCAPS_ZERO             0x00000002L
#define D3DSTENCILCAPS_REPLACE          0x00000004L
#define D3DSTENCILCAPS_INCRSAT          0x00000008L
#define D3DSTENCILCAPS_DECRSAT          0x00000010L
#define D3DSTENCILCAPS_INVERT           0x00000020L
#define D3DSTENCILCAPS_INCR             0x00000040L
#define D3DSTENCILCAPS_DECR             0x00000080L

//
// TextureOpCaps
//
#define D3DTEXOPCAPS_DISABLE                    0x00000001L
#define D3DTEXOPCAPS_SELECTARG1                 0x00000002L
#define D3DTEXOPCAPS_SELECTARG2                 0x00000004L
#define D3DTEXOPCAPS_MODULATE                   0x00000008L
#define D3DTEXOPCAPS_MODULATE2X                 0x00000010L
#define D3DTEXOPCAPS_MODULATE4X                 0x00000020L
#define D3DTEXOPCAPS_ADD                        0x00000040L
#define D3DTEXOPCAPS_ADDSIGNED                  0x00000080L
#define D3DTEXOPCAPS_ADDSIGNED2X                0x00000100L
#define D3DTEXOPCAPS_SUBTRACT                   0x00000200L
#define D3DTEXOPCAPS_ADDSMOOTH                  0x00000400L
#define D3DTEXOPCAPS_BLENDDIFFUSEALPHA          0x00000800L
#define D3DTEXOPCAPS_BLENDTEXTUREALPHA          0x00001000L
#define D3DTEXOPCAPS_BLENDFACTORALPHA           0x00002000L
#define D3DTEXOPCAPS_BLENDTEXTUREALPHAPM        0x00004000L
#define D3DTEXOPCAPS_BLENDCURRENTALPHA          0x00008000L
#define D3DTEXOPCAPS_PREMODULATE                0x00010000L
#define D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR     0x00020000L
#define D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA     0x00040000L
#define D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR  0x00080000L
#define D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA  0x00100000L
#define D3DTEXOPCAPS_BUMPENVMAP                 0x00200000L
#define D3DTEXOPCAPS_BUMPENVMAPLUMINANCE        0x00400000L
#define D3DTEXOPCAPS_DOTPRODUCT3                0x00800000L
#define D3DTEXOPCAPS_MULTIPLYADD                0x01000000L
#define D3DTEXOPCAPS_LERP                       0x02000000L

//
// FVFCaps
//
#define D3DFVFCAPS_TEXCOORDCOUNTMASK    0x0000ffffL /* mask for texture coordinate count field */
#define D3DFVFCAPS_DONOTSTRIPELEMENTS   0x00080000L /* Device prefers that vertex elements not be stripped */
#define D3DFVFCAPS_PSIZE                0x00100000L /* Device can receive point size */

//
// VertexProcessingCaps
//
#define D3DVTXPCAPS_TEXGEN              0x00000001L /* device can do texgen */
#define D3DVTXPCAPS_MATERIALSOURCE7     0x00000002L /* device can do DX7-level colormaterialsource ops */
#define D3DVTXPCAPS_DIRECTIONALLIGHTS   0x00000008L /* device can do directional lights */
#define D3DVTXPCAPS_POSITIONALLIGHTS    0x00000010L /* device can do positional lights (includes point and spot) */
#define D3DVTXPCAPS_LOCALVIEWER         0x00000020L /* device can do local viewer */
#define D3DVTXPCAPS_TWEENING            0x00000040L /* device can do vertex tweening */
#define D3DVTXPCAPS_NO_VSDT_UBYTE4      0x00000080L /* device does not support D3DVSDT_UBYTE4 */

#pragma pack()

#endif /* (DIRECT3D_VERSION >= 0x0800) */
#endif /* _D3D8CAPS_H_ */




#ifdef __cplusplus
extern "C" {
#endif

/*
 * DLL Function for creating a Direct3D8 object. This object supports
 * enumeration and allows the creation of Direct3DDevice8 objects.
 * Pass the value of the constant D3D_SDK_VERSION to this function, so
 * that the run-time can validate that your application was compiled
 * against the right headers.
 */

IDirect3D8 * WINAPI Direct3DCreate8(UINT SDKVersion);


/*
 * Direct3D interfaces
 */






#undef INTERFACE
#define INTERFACE IDirect3D8

DECLARE_INTERFACE_(IDirect3D8, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3D8 methods ***/
    STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) PURE;
    STDMETHOD_(UINT, GetAdapterCount)(THIS) PURE;
    STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier) PURE;
    STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter) PURE;
    STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed) PURE;
    STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType) PURE;
    STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps) PURE;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter) PURE;
    STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface) PURE;
};

typedef struct IDirect3D8 *LPDIRECT3D8, *PDIRECT3D8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3D8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3D8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3D8_RegisterSoftwareDevice(p,a) (p)->lpVtbl->RegisterSoftwareDevice(p,a)
#define IDirect3D8_GetAdapterCount(p) (p)->lpVtbl->GetAdapterCount(p)
#define IDirect3D8_GetAdapterIdentifier(p,a,b,c) (p)->lpVtbl->GetAdapterIdentifier(p,a,b,c)
#define IDirect3D8_GetAdapterModeCount(p,a) (p)->lpVtbl->GetAdapterModeCount(p,a)
#define IDirect3D8_EnumAdapterModes(p,a,b,c) (p)->lpVtbl->EnumAdapterModes(p,a,b,c)
#define IDirect3D8_GetAdapterDisplayMode(p,a,b) (p)->lpVtbl->GetAdapterDisplayMode(p,a,b)
#define IDirect3D8_CheckDeviceType(p,a,b,c,d,e) (p)->lpVtbl->CheckDeviceType(p,a,b,c,d,e)
#define IDirect3D8_CheckDeviceFormat(p,a,b,c,d,e,f) (p)->lpVtbl->CheckDeviceFormat(p,a,b,c,d,e,f)
#define IDirect3D8_CheckDeviceMultiSampleType(p,a,b,c,d,e) (p)->lpVtbl->CheckDeviceMultiSampleType(p,a,b,c,d,e)
#define IDirect3D8_CheckDepthStencilMatch(p,a,b,c,d,e) (p)->lpVtbl->CheckDepthStencilMatch(p,a,b,c,d,e)
#define IDirect3D8_GetDeviceCaps(p,a,b,c) (p)->lpVtbl->GetDeviceCaps(p,a,b,c)
#define IDirect3D8_GetAdapterMonitor(p,a) (p)->lpVtbl->GetAdapterMonitor(p,a)
#define IDirect3D8_CreateDevice(p,a,b,c,d,e,f) (p)->lpVtbl->CreateDevice(p,a,b,c,d,e,f)
#else
#define IDirect3D8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D8_AddRef(p) (p)->AddRef()
#define IDirect3D8_Release(p) (p)->Release()
#define IDirect3D8_RegisterSoftwareDevice(p,a) (p)->RegisterSoftwareDevice(a)
#define IDirect3D8_GetAdapterCount(p) (p)->GetAdapterCount()
#define IDirect3D8_GetAdapterIdentifier(p,a,b,c) (p)->GetAdapterIdentifier(a,b,c)
#define IDirect3D8_GetAdapterModeCount(p,a) (p)->GetAdapterModeCount(a)
#define IDirect3D8_EnumAdapterModes(p,a,b,c) (p)->EnumAdapterModes(a,b,c)
#define IDirect3D8_GetAdapterDisplayMode(p,a,b) (p)->GetAdapterDisplayMode(a,b)
#define IDirect3D8_CheckDeviceType(p,a,b,c,d,e) (p)->CheckDeviceType(a,b,c,d,e)
#define IDirect3D8_CheckDeviceFormat(p,a,b,c,d,e,f) (p)->CheckDeviceFormat(a,b,c,d,e,f)
#define IDirect3D8_CheckDeviceMultiSampleType(p,a,b,c,d,e) (p)->CheckDeviceMultiSampleType(a,b,c,d,e)
#define IDirect3D8_CheckDepthStencilMatch(p,a,b,c,d,e) (p)->CheckDepthStencilMatch(a,b,c,d,e)
#define IDirect3D8_GetDeviceCaps(p,a,b,c) (p)->GetDeviceCaps(a,b,c)
#define IDirect3D8_GetAdapterMonitor(p,a) (p)->GetAdapterMonitor(a)
#define IDirect3D8_CreateDevice(p,a,b,c,d,e,f) (p)->CreateDevice(a,b,c,d,e,f)
#endif



















#undef INTERFACE
#define INTERFACE IDirect3DDevice8

DECLARE_INTERFACE_(IDirect3DDevice8, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DDevice8 methods ***/
    STDMETHOD(TestCooperativeLevel)(THIS) PURE;
    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) PURE;
    STDMETHOD(ResourceManagerDiscardBytes)(THIS_ DWORD Bytes) PURE;
    STDMETHOD(GetDirect3D)(THIS_ IDirect3D8** ppD3D8) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS8* pCaps) PURE;
    STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) PURE;
    STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap) PURE;
    STDMETHOD_(void, SetCursorPosition)(THIS_ int X,int Y,DWORD Flags) PURE;
    STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow) PURE;
    STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3D8PRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain) PURE;
    STDMETHOD(Reset)(THIS_ D3D8PRESENT_PARAMETERS* pPresentationParameters) PURE;
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD_(void, SetGammaRamp)(THIS_ DWORD Flags,CONST D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD_(void, GetGammaRamp)(THIS_ D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD(CreateTexture)(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture) PURE;
    STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture) PURE;
    STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture) PURE;
    STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer) PURE;
    STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer) PURE;
    STDMETHOD(CreateRenderTarget)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CreateImageSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CopyRects)(THIS_ IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray) PURE;
    STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture) PURE;
    STDMETHOD(GetFrontBuffer)(THIS_ IDirect3DSurface8* pDestSurface) PURE;
    STDMETHOD(SetRenderTarget)(THIS_ IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil) PURE;
    STDMETHOD(GetRenderTarget)(THIS_ IDirect3DSurface8** ppRenderTarget) PURE;
    STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface8** ppZStencilSurface) PURE;
    STDMETHOD(BeginScene)(THIS) PURE;
    STDMETHOD(EndScene)(THIS) PURE;
    STDMETHOD(Clear)(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) PURE;
    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) PURE;
    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
    STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL8* pMaterial) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL8* pMaterial) PURE;
    STDMETHOD(SetLight)(THIS_ DWORD Index,CONST D3DLIGHT8*) PURE;
    STDMETHOD(GetLight)(THIS_ DWORD Index,D3DLIGHT8*) PURE;
    STDMETHOD(LightEnable)(THIS_ DWORD Index,BOOL Enable) PURE;
    STDMETHOD(GetLightEnable)(THIS_ DWORD Index,BOOL* pEnable) PURE;
    STDMETHOD(SetClipPlane)(THIS_ DWORD Index,CONST float* pPlane) PURE;
    STDMETHOD(GetClipPlane)(THIS_ DWORD Index,float* pPlane) PURE;
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD Value) PURE;
    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue) PURE;
    STDMETHOD(BeginStateBlock)(THIS) PURE;
    STDMETHOD(EndStateBlock)(THIS_ DWORD* pToken) PURE;
    STDMETHOD(ApplyStateBlock)(THIS_ DWORD Token) PURE;
    STDMETHOD(CaptureStateBlock)(THIS_ DWORD Token) PURE;
    STDMETHOD(DeleteStateBlock)(THIS_ DWORD Token) PURE;
    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type,DWORD* pToken) PURE;
    STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS8* pClipStatus) PURE;
    STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS8* pClipStatus) PURE;
    STDMETHOD(GetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture8** ppTexture) PURE;
    STDMETHOD(SetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture8* pTexture) PURE;
    STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage,D3D8TEXTURESTAGESTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses) PURE;
    STDMETHOD(GetInfo)(THIS_ DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize) PURE;
    STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries) PURE;
    STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries) PURE;
    STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber) PURE;
    STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber) PURE;
    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) PURE;
    STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount) PURE;
    STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags) PURE;
    STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage) PURE;
    STDMETHOD(SetVertexShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(GetVertexShader)(THIS_ DWORD* pHandle) PURE;
    STDMETHOD(DeleteVertexShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(SetVertexShaderConstant)(THIS_ DWORD Register,CONST void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetVertexShaderConstant)(THIS_ DWORD Register,void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetVertexShaderDeclaration)(THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(GetVertexShaderFunction)(THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride) PURE;
    STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride) PURE;
    STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex) PURE;
    STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex) PURE;
    STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction,DWORD* pHandle) PURE;
    STDMETHOD(SetPixelShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(GetPixelShader)(THIS_ DWORD* pHandle) PURE;
    STDMETHOD(DeletePixelShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(SetPixelShaderConstant)(THIS_ DWORD Register,CONST void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetPixelShaderConstant)(THIS_ DWORD Register,void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetPixelShaderFunction)(THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(DrawRectPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) PURE;
    STDMETHOD(DrawTriPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) PURE;
    STDMETHOD(DeletePatch)(THIS_ UINT Handle) PURE;
};

typedef struct IDirect3DDevice8 *LPDIRECT3DDEVICE8, *PDIRECT3DDEVICE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DDevice8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DDevice8_TestCooperativeLevel(p) (p)->lpVtbl->TestCooperativeLevel(p)
#define IDirect3DDevice8_GetAvailableTextureMem(p) (p)->lpVtbl->GetAvailableTextureMem(p)
#define IDirect3DDevice8_ResourceManagerDiscardBytes(p,a) (p)->lpVtbl->ResourceManagerDiscardBytes(p,a)
#define IDirect3DDevice8_GetDirect3D(p,a) (p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice8_GetDeviceCaps(p,a) (p)->lpVtbl->GetDeviceCaps(p,a)
#define IDirect3DDevice8_GetDisplayMode(p,a) (p)->lpVtbl->GetDisplayMode(p,a)
#define IDirect3DDevice8_GetCreationParameters(p,a) (p)->lpVtbl->GetCreationParameters(p,a)
#define IDirect3DDevice8_SetCursorProperties(p,a,b,c) (p)->lpVtbl->SetCursorProperties(p,a,b,c)
#define IDirect3DDevice8_SetCursorPosition(p,a,b,c) (p)->lpVtbl->SetCursorPosition(p,a,b,c)
#define IDirect3DDevice8_ShowCursor(p,a) (p)->lpVtbl->ShowCursor(p,a)
#define IDirect3DDevice8_CreateAdditionalSwapChain(p,a,b) (p)->lpVtbl->CreateAdditionalSwapChain(p,a,b)
#define IDirect3DDevice8_Reset(p,a) (p)->lpVtbl->Reset(p,a)
#define IDirect3DDevice8_Present(p,a,b,c,d) (p)->lpVtbl->Present(p,a,b,c,d)
#define IDirect3DDevice8_GetBackBuffer(p,a,b,c) (p)->lpVtbl->GetBackBuffer(p,a,b,c)
#define IDirect3DDevice8_GetRasterStatus(p,a) (p)->lpVtbl->GetRasterStatus(p,a)
#define IDirect3DDevice8_SetGammaRamp(p,a,b) (p)->lpVtbl->SetGammaRamp(p,a,b)
#define IDirect3DDevice8_GetGammaRamp(p,a) (p)->lpVtbl->GetGammaRamp(p,a)
#define IDirect3DDevice8_CreateTexture(p,a,b,c,d,e,f,g) (p)->lpVtbl->CreateTexture(p,a,b,c,d,e,f,g)
#define IDirect3DDevice8_CreateVolumeTexture(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateVolumeTexture(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice8_CreateCubeTexture(p,a,b,c,d,e,f) (p)->lpVtbl->CreateCubeTexture(p,a,b,c,d,e,f)
#define IDirect3DDevice8_CreateVertexBuffer(p,a,b,c,d,e) (p)->lpVtbl->CreateVertexBuffer(p,a,b,c,d,e)
#define IDirect3DDevice8_CreateIndexBuffer(p,a,b,c,d,e) (p)->lpVtbl->CreateIndexBuffer(p,a,b,c,d,e)
#define IDirect3DDevice8_CreateRenderTarget(p,a,b,c,d,e,f) (p)->lpVtbl->CreateRenderTarget(p,a,b,c,d,e,f)
#define IDirect3DDevice8_CreateDepthStencilSurface(p,a,b,c,d,e) (p)->lpVtbl->CreateDepthStencilSurface(p,a,b,c,d,e)
#define IDirect3DDevice8_CreateImageSurface(p,a,b,c,d) (p)->lpVtbl->CreateImageSurface(p,a,b,c,d)
#define IDirect3DDevice8_CopyRects(p,a,b,c,d,e) (p)->lpVtbl->CopyRects(p,a,b,c,d,e)
#define IDirect3DDevice8_UpdateTexture(p,a,b) (p)->lpVtbl->UpdateTexture(p,a,b)
#define IDirect3DDevice8_GetFrontBuffer(p,a) (p)->lpVtbl->GetFrontBuffer(p,a)
#define IDirect3DDevice8_SetRenderTarget(p,a,b) (p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice8_GetRenderTarget(p,a) (p)->lpVtbl->GetRenderTarget(p,a)
#define IDirect3DDevice8_GetDepthStencilSurface(p,a) (p)->lpVtbl->GetDepthStencilSurface(p,a)
#define IDirect3DDevice8_BeginScene(p) (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice8_EndScene(p) (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice8_Clear(p,a,b,c,d,e,f) (p)->lpVtbl->Clear(p,a,b,c,d,e,f)
#define IDirect3DDevice8_SetTransform(p,a,b) (p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice8_GetTransform(p,a,b) (p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice8_MultiplyTransform(p,a,b) (p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice8_SetViewport(p,a) (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DDevice8_GetViewport(p,a) (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DDevice8_SetMaterial(p,a) (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DDevice8_GetMaterial(p,a) (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DDevice8_SetLight(p,a,b) (p)->lpVtbl->SetLight(p,a,b)
#define IDirect3DDevice8_GetLight(p,a,b) (p)->lpVtbl->GetLight(p,a,b)
#define IDirect3DDevice8_LightEnable(p,a,b) (p)->lpVtbl->LightEnable(p,a,b)
#define IDirect3DDevice8_GetLightEnable(p,a,b) (p)->lpVtbl->GetLightEnable(p,a,b)
#define IDirect3DDevice8_SetClipPlane(p,a,b) (p)->lpVtbl->SetClipPlane(p,a,b)
#define IDirect3DDevice8_GetClipPlane(p,a,b) (p)->lpVtbl->GetClipPlane(p,a,b)
#define IDirect3DDevice8_SetRenderState(p,a,b) (p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice8_GetRenderState(p,a,b) (p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice8_BeginStateBlock(p) (p)->lpVtbl->BeginStateBlock(p)
#define IDirect3DDevice8_EndStateBlock(p,a) (p)->lpVtbl->EndStateBlock(p,a)
#define IDirect3DDevice8_ApplyStateBlock(p,a) (p)->lpVtbl->ApplyStateBlock(p,a)
#define IDirect3DDevice8_CaptureStateBlock(p,a) (p)->lpVtbl->CaptureStateBlock(p,a)
#define IDirect3DDevice8_DeleteStateBlock(p,a) (p)->lpVtbl->DeleteStateBlock(p,a)
#define IDirect3DDevice8_CreateStateBlock(p,a,b) (p)->lpVtbl->CreateStateBlock(p,a,b)
#define IDirect3DDevice8_SetClipStatus(p,a) (p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice8_GetClipStatus(p,a) (p)->lpVtbl->GetClipStatus(p,a)
#define IDirect3DDevice8_GetTexture(p,a,b) (p)->lpVtbl->GetTexture(p,a,b)
#define IDirect3DDevice8_SetTexture(p,a,b) (p)->lpVtbl->SetTexture(p,a,b)
#define IDirect3DDevice8_GetTextureStageState(p,a,b,c) (p)->lpVtbl->GetTextureStageState(p,a,b,c)
#define IDirect3DDevice8_SetTextureStageState(p,a,b,c) (p)->lpVtbl->SetTextureStageState(p,a,b,c)
#define IDirect3DDevice8_ValidateDevice(p,a) (p)->lpVtbl->ValidateDevice(p,a)
#define IDirect3DDevice8_GetInfo(p,a,b,c) (p)->lpVtbl->GetInfo(p,a,b,c)
#define IDirect3DDevice8_SetPaletteEntries(p,a,b) (p)->lpVtbl->SetPaletteEntries(p,a,b)
#define IDirect3DDevice8_GetPaletteEntries(p,a,b) (p)->lpVtbl->GetPaletteEntries(p,a,b)
#define IDirect3DDevice8_SetCurrentTexturePalette(p,a) (p)->lpVtbl->SetCurrentTexturePalette(p,a)
#define IDirect3DDevice8_GetCurrentTexturePalette(p,a) (p)->lpVtbl->GetCurrentTexturePalette(p,a)
#define IDirect3DDevice8_DrawPrimitive(p,a,b,c) (p)->lpVtbl->DrawPrimitive(p,a,b,c)
#define IDirect3DDevice8_DrawIndexedPrimitive(p,a,b,c,d,e) (p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e)
#define IDirect3DDevice8_DrawPrimitiveUP(p,a,b,c,d) (p)->lpVtbl->DrawPrimitiveUP(p,a,b,c,d)
#define IDirect3DDevice8_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice8_ProcessVertices(p,a,b,c,d,e) (p)->lpVtbl->ProcessVertices(p,a,b,c,d,e)
#define IDirect3DDevice8_CreateVertexShader(p,a,b,c,d) (p)->lpVtbl->CreateVertexShader(p,a,b,c,d)
#define IDirect3DDevice8_SetVertexShader(p,a) (p)->lpVtbl->SetVertexShader(p,a)
#define IDirect3DDevice8_GetVertexShader(p,a) (p)->lpVtbl->GetVertexShader(p,a)
#define IDirect3DDevice8_DeleteVertexShader(p,a) (p)->lpVtbl->DeleteVertexShader(p,a)
#define IDirect3DDevice8_SetVertexShaderConstant(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstant(p,a,b,c)
#define IDirect3DDevice8_GetVertexShaderConstant(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstant(p,a,b,c)
#define IDirect3DDevice8_GetVertexShaderDeclaration(p,a,b,c) (p)->lpVtbl->GetVertexShaderDeclaration(p,a,b,c)
#define IDirect3DDevice8_GetVertexShaderFunction(p,a,b,c) (p)->lpVtbl->GetVertexShaderFunction(p,a,b,c)
#define IDirect3DDevice8_SetStreamSource(p,a,b,c) (p)->lpVtbl->SetStreamSource(p,a,b,c)
#define IDirect3DDevice8_GetStreamSource(p,a,b,c) (p)->lpVtbl->GetStreamSource(p,a,b,c)
#define IDirect3DDevice8_SetIndices(p,a,b) (p)->lpVtbl->SetIndices(p,a,b)
#define IDirect3DDevice8_GetIndices(p,a,b) (p)->lpVtbl->GetIndices(p,a,b)
#define IDirect3DDevice8_CreatePixelShader(p,a,b) (p)->lpVtbl->CreatePixelShader(p,a,b)
#define IDirect3DDevice8_SetPixelShader(p,a) (p)->lpVtbl->SetPixelShader(p,a)
#define IDirect3DDevice8_GetPixelShader(p,a) (p)->lpVtbl->GetPixelShader(p,a)
#define IDirect3DDevice8_DeletePixelShader(p,a) (p)->lpVtbl->DeletePixelShader(p,a)
#define IDirect3DDevice8_SetPixelShaderConstant(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstant(p,a,b,c)
#define IDirect3DDevice8_GetPixelShaderConstant(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstant(p,a,b,c)
#define IDirect3DDevice8_GetPixelShaderFunction(p,a,b,c) (p)->lpVtbl->GetPixelShaderFunction(p,a,b,c)
#define IDirect3DDevice8_DrawRectPatch(p,a,b,c) (p)->lpVtbl->DrawRectPatch(p,a,b,c)
#define IDirect3DDevice8_DrawTriPatch(p,a,b,c) (p)->lpVtbl->DrawTriPatch(p,a,b,c)
#define IDirect3DDevice8_DeletePatch(p,a) (p)->lpVtbl->DeletePatch(p,a)
#else
#define IDirect3DDevice8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice8_AddRef(p) (p)->AddRef()
#define IDirect3DDevice8_Release(p) (p)->Release()
#define IDirect3DDevice8_TestCooperativeLevel(p) (p)->TestCooperativeLevel()
#define IDirect3DDevice8_GetAvailableTextureMem(p) (p)->GetAvailableTextureMem()
#define IDirect3DDevice8_ResourceManagerDiscardBytes(p,a) (p)->ResourceManagerDiscardBytes(a)
#define IDirect3DDevice8_GetDirect3D(p,a) (p)->GetDirect3D(a)
#define IDirect3DDevice8_GetDeviceCaps(p,a) (p)->GetDeviceCaps(a)
#define IDirect3DDevice8_GetDisplayMode(p,a) (p)->GetDisplayMode(a)
#define IDirect3DDevice8_GetCreationParameters(p,a) (p)->GetCreationParameters(a)
#define IDirect3DDevice8_SetCursorProperties(p,a,b,c) (p)->SetCursorProperties(a,b,c)
#define IDirect3DDevice8_SetCursorPosition(p,a,b,c) (p)->SetCursorPosition(a,b,c)
#define IDirect3DDevice8_ShowCursor(p,a) (p)->ShowCursor(a)
#define IDirect3DDevice8_CreateAdditionalSwapChain(p,a,b) (p)->CreateAdditionalSwapChain(a,b)
#define IDirect3DDevice8_Reset(p,a) (p)->Reset(a)
#define IDirect3DDevice8_Present(p,a,b,c,d) (p)->Present(a,b,c,d)
#define IDirect3DDevice8_GetBackBuffer(p,a,b,c) (p)->GetBackBuffer(a,b,c)
#define IDirect3DDevice8_GetRasterStatus(p,a) (p)->GetRasterStatus(a)
#define IDirect3DDevice8_SetGammaRamp(p,a,b) (p)->SetGammaRamp(a,b)
#define IDirect3DDevice8_GetGammaRamp(p,a) (p)->GetGammaRamp(a)
#define IDirect3DDevice8_CreateTexture(p,a,b,c,d,e,f,g) (p)->CreateTexture(a,b,c,d,e,f,g)
#define IDirect3DDevice8_CreateVolumeTexture(p,a,b,c,d,e,f,g,h) (p)->CreateVolumeTexture(a,b,c,d,e,f,g,h)
#define IDirect3DDevice8_CreateCubeTexture(p,a,b,c,d,e,f) (p)->CreateCubeTexture(a,b,c,d,e,f)
#define IDirect3DDevice8_CreateVertexBuffer(p,a,b,c,d,e) (p)->CreateVertexBuffer(a,b,c,d,e)
#define IDirect3DDevice8_CreateIndexBuffer(p,a,b,c,d,e) (p)->CreateIndexBuffer(a,b,c,d,e)
#define IDirect3DDevice8_CreateRenderTarget(p,a,b,c,d,e,f) (p)->CreateRenderTarget(a,b,c,d,e,f)
#define IDirect3DDevice8_CreateDepthStencilSurface(p,a,b,c,d,e) (p)->CreateDepthStencilSurface(a,b,c,d,e)
#define IDirect3DDevice8_CreateImageSurface(p,a,b,c,d) (p)->CreateImageSurface(a,b,c,d)
#define IDirect3DDevice8_CopyRects(p,a,b,c,d,e) (p)->CopyRects(a,b,c,d,e)
#define IDirect3DDevice8_UpdateTexture(p,a,b) (p)->UpdateTexture(a,b)
#define IDirect3DDevice8_GetFrontBuffer(p,a) (p)->GetFrontBuffer(a)
#define IDirect3DDevice8_SetRenderTarget(p,a,b) (p)->SetRenderTarget(a,b)
#define IDirect3DDevice8_GetRenderTarget(p,a) (p)->GetRenderTarget(a)
#define IDirect3DDevice8_GetDepthStencilSurface(p,a) (p)->GetDepthStencilSurface(a)
#define IDirect3DDevice8_BeginScene(p) (p)->BeginScene()
#define IDirect3DDevice8_EndScene(p) (p)->EndScene()
#define IDirect3DDevice8_Clear(p,a,b,c,d,e,f) (p)->Clear(a,b,c,d,e,f)
#define IDirect3DDevice8_SetTransform(p,a,b) (p)->SetTransform(a,b)
#define IDirect3DDevice8_GetTransform(p,a,b) (p)->GetTransform(a,b)
#define IDirect3DDevice8_MultiplyTransform(p,a,b) (p)->MultiplyTransform(a,b)
#define IDirect3DDevice8_SetViewport(p,a) (p)->SetViewport(a)
#define IDirect3DDevice8_GetViewport(p,a) (p)->GetViewport(a)
#define IDirect3DDevice8_SetMaterial(p,a) (p)->SetMaterial(a)
#define IDirect3DDevice8_GetMaterial(p,a) (p)->GetMaterial(a)
#define IDirect3DDevice8_SetLight(p,a,b) (p)->SetLight(a,b)
#define IDirect3DDevice8_GetLight(p,a,b) (p)->GetLight(a,b)
#define IDirect3DDevice8_LightEnable(p,a,b) (p)->LightEnable(a,b)
#define IDirect3DDevice8_GetLightEnable(p,a,b) (p)->GetLightEnable(a,b)
#define IDirect3DDevice8_SetClipPlane(p,a,b) (p)->SetClipPlane(a,b)
#define IDirect3DDevice8_GetClipPlane(p,a,b) (p)->GetClipPlane(a,b)
#define IDirect3DDevice8_SetRenderState(p,a,b) (p)->SetRenderState(a,b)
#define IDirect3DDevice8_GetRenderState(p,a,b) (p)->GetRenderState(a,b)
#define IDirect3DDevice8_BeginStateBlock(p) (p)->BeginStateBlock()
#define IDirect3DDevice8_EndStateBlock(p,a) (p)->EndStateBlock(a)
#define IDirect3DDevice8_ApplyStateBlock(p,a) (p)->ApplyStateBlock(a)
#define IDirect3DDevice8_CaptureStateBlock(p,a) (p)->CaptureStateBlock(a)
#define IDirect3DDevice8_DeleteStateBlock(p,a) (p)->DeleteStateBlock(a)
#define IDirect3DDevice8_CreateStateBlock(p,a,b) (p)->CreateStateBlock(a,b)
#define IDirect3DDevice8_SetClipStatus(p,a) (p)->SetClipStatus(a)
#define IDirect3DDevice8_GetClipStatus(p,a) (p)->GetClipStatus(a)
#define IDirect3DDevice8_GetTexture(p,a,b) (p)->GetTexture(a,b)
#define IDirect3DDevice8_SetTexture(p,a,b) (p)->SetTexture(a,b)
#define IDirect3DDevice8_GetTextureStageState(p,a,b,c) (p)->GetTextureStageState(a,b,c)
#define IDirect3DDevice8_SetTextureStageState(p,a,b,c) (p)->SetTextureStageState(a,b,c)
#define IDirect3DDevice8_ValidateDevice(p,a) (p)->ValidateDevice(a)
#define IDirect3DDevice8_GetInfo(p,a,b,c) (p)->GetInfo(a,b,c)
#define IDirect3DDevice8_SetPaletteEntries(p,a,b) (p)->SetPaletteEntries(a,b)
#define IDirect3DDevice8_GetPaletteEntries(p,a,b) (p)->GetPaletteEntries(a,b)
#define IDirect3DDevice8_SetCurrentTexturePalette(p,a) (p)->SetCurrentTexturePalette(a)
#define IDirect3DDevice8_GetCurrentTexturePalette(p,a) (p)->GetCurrentTexturePalette(a)
#define IDirect3DDevice8_DrawPrimitive(p,a,b,c) (p)->DrawPrimitive(a,b,c)
#define IDirect3DDevice8_DrawIndexedPrimitive(p,a,b,c,d,e) (p)->DrawIndexedPrimitive(a,b,c,d,e)
#define IDirect3DDevice8_DrawPrimitiveUP(p,a,b,c,d) (p)->DrawPrimitiveUP(a,b,c,d)
#define IDirect3DDevice8_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h) (p)->DrawIndexedPrimitiveUP(a,b,c,d,e,f,g,h)
#define IDirect3DDevice8_ProcessVertices(p,a,b,c,d,e) (p)->ProcessVertices(a,b,c,d,e)
#define IDirect3DDevice8_CreateVertexShader(p,a,b,c,d) (p)->CreateVertexShader(a,b,c,d)
#define IDirect3DDevice8_SetVertexShader(p,a) (p)->SetVertexShader(a)
#define IDirect3DDevice8_GetVertexShader(p,a) (p)->GetVertexShader(a)
#define IDirect3DDevice8_DeleteVertexShader(p,a) (p)->DeleteVertexShader(a)
#define IDirect3DDevice8_SetVertexShaderConstant(p,a,b,c) (p)->SetVertexShaderConstant(a,b,c)
#define IDirect3DDevice8_GetVertexShaderConstant(p,a,b,c) (p)->GetVertexShaderConstant(a,b,c)
#define IDirect3DDevice8_GetVertexShaderDeclaration(p,a,b,c) (p)->GetVertexShaderDeclaration(a,b,c)
#define IDirect3DDevice8_GetVertexShaderFunction(p,a,b,c) (p)->GetVertexShaderFunction(a,b,c)
#define IDirect3DDevice8_SetStreamSource(p,a,b,c) (p)->SetStreamSource(a,b,c)
#define IDirect3DDevice8_GetStreamSource(p,a,b,c) (p)->GetStreamSource(a,b,c)
#define IDirect3DDevice8_SetIndices(p,a,b) (p)->SetIndices(a,b)
#define IDirect3DDevice8_GetIndices(p,a,b) (p)->GetIndices(a,b)
#define IDirect3DDevice8_CreatePixelShader(p,a,b) (p)->CreatePixelShader(a,b)
#define IDirect3DDevice8_SetPixelShader(p,a) (p)->SetPixelShader(a)
#define IDirect3DDevice8_GetPixelShader(p,a) (p)->GetPixelShader(a)
#define IDirect3DDevice8_DeletePixelShader(p,a) (p)->DeletePixelShader(a)
#define IDirect3DDevice8_SetPixelShaderConstant(p,a,b,c) (p)->SetPixelShaderConstant(a,b,c)
#define IDirect3DDevice8_GetPixelShaderConstant(p,a,b,c) (p)->GetPixelShaderConstant(a,b,c)
#define IDirect3DDevice8_GetPixelShaderFunction(p,a,b,c) (p)->GetPixelShaderFunction(a,b,c)
#define IDirect3DDevice8_DrawRectPatch(p,a,b,c) (p)->DrawRectPatch(a,b,c)
#define IDirect3DDevice8_DrawTriPatch(p,a,b,c) (p)->DrawTriPatch(a,b,c)
#define IDirect3DDevice8_DeletePatch(p,a) (p)->DeletePatch(a)
#endif



#undef INTERFACE
#define INTERFACE IDirect3DSwapChain8

DECLARE_INTERFACE_(IDirect3DSwapChain8, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DSwapChain8 methods ***/
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer) PURE;
};

typedef struct IDirect3DSwapChain8 *LPDIRECT3DSWAPCHAIN8, *PDIRECT3DSWAPCHAIN8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSwapChain8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSwapChain8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DSwapChain8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DSwapChain8_Present(p,a,b,c,d) (p)->lpVtbl->Present(p,a,b,c,d)
#define IDirect3DSwapChain8_GetBackBuffer(p,a,b,c) (p)->lpVtbl->GetBackBuffer(p,a,b,c)
#else
#define IDirect3DSwapChain8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DSwapChain8_AddRef(p) (p)->AddRef()
#define IDirect3DSwapChain8_Release(p) (p)->Release()
#define IDirect3DSwapChain8_Present(p,a,b,c,d) (p)->Present(a,b,c,d)
#define IDirect3DSwapChain8_GetBackBuffer(p,a,b,c) (p)->GetBackBuffer(a,b,c)
#endif



#undef INTERFACE
#define INTERFACE IDirect3DResource8

DECLARE_INTERFACE_(IDirect3DResource8, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
};

typedef struct IDirect3DResource8 *LPDIRECT3DRESOURCE8, *PDIRECT3DRESOURCE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DResource8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DResource8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DResource8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DResource8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DResource8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DResource8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DResource8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DResource8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DResource8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DResource8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DResource8_GetType(p) (p)->lpVtbl->GetType(p)
#else
#define IDirect3DResource8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DResource8_AddRef(p) (p)->AddRef()
#define IDirect3DResource8_Release(p) (p)->Release()
#define IDirect3DResource8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DResource8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DResource8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DResource8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DResource8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DResource8_GetPriority(p) (p)->GetPriority()
#define IDirect3DResource8_PreLoad(p) (p)->PreLoad()
#define IDirect3DResource8_GetType(p) (p)->GetType()
#endif




#undef INTERFACE
#define INTERFACE IDirect3DBaseTexture8

DECLARE_INTERFACE_(IDirect3DBaseTexture8, IDirect3DResource8)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
};

typedef struct IDirect3DBaseTexture8 *LPDIRECT3DBASETEXTURE8, *PDIRECT3DBASETEXTURE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DBaseTexture8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DBaseTexture8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DBaseTexture8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DBaseTexture8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DBaseTexture8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DBaseTexture8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DBaseTexture8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DBaseTexture8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DBaseTexture8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DBaseTexture8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DBaseTexture8_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DBaseTexture8_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DBaseTexture8_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DBaseTexture8_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#else
#define IDirect3DBaseTexture8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DBaseTexture8_AddRef(p) (p)->AddRef()
#define IDirect3DBaseTexture8_Release(p) (p)->Release()
#define IDirect3DBaseTexture8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DBaseTexture8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DBaseTexture8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DBaseTexture8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DBaseTexture8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DBaseTexture8_GetPriority(p) (p)->GetPriority()
#define IDirect3DBaseTexture8_PreLoad(p) (p)->PreLoad()
#define IDirect3DBaseTexture8_GetType(p) (p)->GetType()
#define IDirect3DBaseTexture8_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DBaseTexture8_GetLOD(p) (p)->GetLOD()
#define IDirect3DBaseTexture8_GetLevelCount(p) (p)->GetLevelCount()
#endif





#undef INTERFACE
#define INTERFACE IDirect3DTexture8

DECLARE_INTERFACE_(IDirect3DTexture8, IDirect3DBaseTexture8)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3D8SURFACE_DESC *pDesc) PURE;
    STDMETHOD(GetSurfaceLevel)(THIS_ UINT Level,IDirect3DSurface8** ppSurfaceLevel) PURE;
    STDMETHOD(LockRect)(THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS_ UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(THIS_ CONST RECT* pDirtyRect) PURE;
};

typedef struct IDirect3DTexture8 *LPDIRECT3DTEXTURE8, *PDIRECT3DTEXTURE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DTexture8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DTexture8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DTexture8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DTexture8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DTexture8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DTexture8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DTexture8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DTexture8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DTexture8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DTexture8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DTexture8_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DTexture8_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DTexture8_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DTexture8_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DTexture8_GetLevelDesc(p,a,b) (p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DTexture8_GetSurfaceLevel(p,a,b) (p)->lpVtbl->GetSurfaceLevel(p,a,b)
#define IDirect3DTexture8_LockRect(p,a,b,c,d) (p)->lpVtbl->LockRect(p,a,b,c,d)
#define IDirect3DTexture8_UnlockRect(p,a) (p)->lpVtbl->UnlockRect(p,a)
#define IDirect3DTexture8_AddDirtyRect(p,a) (p)->lpVtbl->AddDirtyRect(p,a)
#else
#define IDirect3DTexture8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DTexture8_AddRef(p) (p)->AddRef()
#define IDirect3DTexture8_Release(p) (p)->Release()
#define IDirect3DTexture8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DTexture8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DTexture8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DTexture8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DTexture8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DTexture8_GetPriority(p) (p)->GetPriority()
#define IDirect3DTexture8_PreLoad(p) (p)->PreLoad()
#define IDirect3DTexture8_GetType(p) (p)->GetType()
#define IDirect3DTexture8_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DTexture8_GetLOD(p) (p)->GetLOD()
#define IDirect3DTexture8_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DTexture8_GetLevelDesc(p,a,b) (p)->GetLevelDesc(a,b)
#define IDirect3DTexture8_GetSurfaceLevel(p,a,b) (p)->GetSurfaceLevel(a,b)
#define IDirect3DTexture8_LockRect(p,a,b,c,d) (p)->LockRect(a,b,c,d)
#define IDirect3DTexture8_UnlockRect(p,a) (p)->UnlockRect(a)
#define IDirect3DTexture8_AddDirtyRect(p,a) (p)->AddDirtyRect(a)
#endif





#undef INTERFACE
#define INTERFACE IDirect3DVolumeTexture8

DECLARE_INTERFACE_(IDirect3DVolumeTexture8, IDirect3DBaseTexture8)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3D8VOLUME_DESC *pDesc) PURE;
    STDMETHOD(GetVolumeLevel)(THIS_ UINT Level,IDirect3DVolume8** ppVolumeLevel) PURE;
    STDMETHOD(LockBox)(THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) PURE;
    STDMETHOD(UnlockBox)(THIS_ UINT Level) PURE;
    STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX* pDirtyBox) PURE;
};

typedef struct IDirect3DVolumeTexture8 *LPDIRECT3DVOLUMETEXTURE8, *PDIRECT3DVOLUMETEXTURE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVolumeTexture8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVolumeTexture8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVolumeTexture8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVolumeTexture8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVolumeTexture8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVolumeTexture8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVolumeTexture8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVolumeTexture8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DVolumeTexture8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DVolumeTexture8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DVolumeTexture8_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DVolumeTexture8_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DVolumeTexture8_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DVolumeTexture8_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DVolumeTexture8_GetLevelDesc(p,a,b) (p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DVolumeTexture8_GetVolumeLevel(p,a,b) (p)->lpVtbl->GetVolumeLevel(p,a,b)
#define IDirect3DVolumeTexture8_LockBox(p,a,b,c,d) (p)->lpVtbl->LockBox(p,a,b,c,d)
#define IDirect3DVolumeTexture8_UnlockBox(p,a) (p)->lpVtbl->UnlockBox(p,a)
#define IDirect3DVolumeTexture8_AddDirtyBox(p,a) (p)->lpVtbl->AddDirtyBox(p,a)
#else
#define IDirect3DVolumeTexture8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVolumeTexture8_AddRef(p) (p)->AddRef()
#define IDirect3DVolumeTexture8_Release(p) (p)->Release()
#define IDirect3DVolumeTexture8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVolumeTexture8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DVolumeTexture8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DVolumeTexture8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DVolumeTexture8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DVolumeTexture8_GetPriority(p) (p)->GetPriority()
#define IDirect3DVolumeTexture8_PreLoad(p) (p)->PreLoad()
#define IDirect3DVolumeTexture8_GetType(p) (p)->GetType()
#define IDirect3DVolumeTexture8_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DVolumeTexture8_GetLOD(p) (p)->GetLOD()
#define IDirect3DVolumeTexture8_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DVolumeTexture8_GetLevelDesc(p,a,b) (p)->GetLevelDesc(a,b)
#define IDirect3DVolumeTexture8_GetVolumeLevel(p,a,b) (p)->GetVolumeLevel(a,b)
#define IDirect3DVolumeTexture8_LockBox(p,a,b,c,d) (p)->LockBox(a,b,c,d)
#define IDirect3DVolumeTexture8_UnlockBox(p,a) (p)->UnlockBox(a)
#define IDirect3DVolumeTexture8_AddDirtyBox(p,a) (p)->AddDirtyBox(a)
#endif





#undef INTERFACE
#define INTERFACE IDirect3DCubeTexture8

DECLARE_INTERFACE_(IDirect3DCubeTexture8, IDirect3DBaseTexture8)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3D8SURFACE_DESC *pDesc) PURE;
    STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface8** ppCubeMapSurface) PURE;
    STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect) PURE;
};

typedef struct IDirect3DCubeTexture8 *LPDIRECT3DCUBETEXTURE8, *PDIRECT3DCUBETEXTURE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DCubeTexture8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DCubeTexture8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DCubeTexture8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DCubeTexture8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DCubeTexture8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DCubeTexture8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DCubeTexture8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DCubeTexture8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DCubeTexture8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DCubeTexture8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DCubeTexture8_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DCubeTexture8_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DCubeTexture8_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DCubeTexture8_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DCubeTexture8_GetLevelDesc(p,a,b) (p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DCubeTexture8_GetCubeMapSurface(p,a,b,c) (p)->lpVtbl->GetCubeMapSurface(p,a,b,c)
#define IDirect3DCubeTexture8_LockRect(p,a,b,c,d,e) (p)->lpVtbl->LockRect(p,a,b,c,d,e)
#define IDirect3DCubeTexture8_UnlockRect(p,a,b) (p)->lpVtbl->UnlockRect(p,a,b)
#define IDirect3DCubeTexture8_AddDirtyRect(p,a,b) (p)->lpVtbl->AddDirtyRect(p,a,b)
#else
#define IDirect3DCubeTexture8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DCubeTexture8_AddRef(p) (p)->AddRef()
#define IDirect3DCubeTexture8_Release(p) (p)->Release()
#define IDirect3DCubeTexture8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DCubeTexture8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DCubeTexture8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DCubeTexture8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DCubeTexture8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DCubeTexture8_GetPriority(p) (p)->GetPriority()
#define IDirect3DCubeTexture8_PreLoad(p) (p)->PreLoad()
#define IDirect3DCubeTexture8_GetType(p) (p)->GetType()
#define IDirect3DCubeTexture8_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DCubeTexture8_GetLOD(p) (p)->GetLOD()
#define IDirect3DCubeTexture8_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DCubeTexture8_GetLevelDesc(p,a,b) (p)->GetLevelDesc(a,b)
#define IDirect3DCubeTexture8_GetCubeMapSurface(p,a,b,c) (p)->GetCubeMapSurface(a,b,c)
#define IDirect3DCubeTexture8_LockRect(p,a,b,c,d,e) (p)->LockRect(a,b,c,d,e)
#define IDirect3DCubeTexture8_UnlockRect(p,a,b) (p)->UnlockRect(a,b)
#define IDirect3DCubeTexture8_AddDirtyRect(p,a,b) (p)->AddDirtyRect(a,b)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DVertexBuffer8

DECLARE_INTERFACE_(IDirect3DVertexBuffer8, IDirect3DResource8)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD(Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc) PURE;
};

typedef struct IDirect3DVertexBuffer8 *LPDIRECT3DVERTEXBUFFER8, *PDIRECT3DVERTEXBUFFER8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexBuffer8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexBuffer8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVertexBuffer8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVertexBuffer8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexBuffer8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVertexBuffer8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVertexBuffer8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVertexBuffer8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DVertexBuffer8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DVertexBuffer8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DVertexBuffer8_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DVertexBuffer8_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirect3DVertexBuffer8_Unlock(p) (p)->lpVtbl->Unlock(p)
#define IDirect3DVertexBuffer8_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#else
#define IDirect3DVertexBuffer8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVertexBuffer8_AddRef(p) (p)->AddRef()
#define IDirect3DVertexBuffer8_Release(p) (p)->Release()
#define IDirect3DVertexBuffer8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVertexBuffer8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DVertexBuffer8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DVertexBuffer8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DVertexBuffer8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DVertexBuffer8_GetPriority(p) (p)->GetPriority()
#define IDirect3DVertexBuffer8_PreLoad(p) (p)->PreLoad()
#define IDirect3DVertexBuffer8_GetType(p) (p)->GetType()
#define IDirect3DVertexBuffer8_Lock(p,a,b,c,d) (p)->Lock(a,b,c,d)
#define IDirect3DVertexBuffer8_Unlock(p) (p)->Unlock()
#define IDirect3DVertexBuffer8_GetDesc(p,a) (p)->GetDesc(a)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DIndexBuffer8

DECLARE_INTERFACE_(IDirect3DIndexBuffer8, IDirect3DResource8)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD(Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc) PURE;
};

typedef struct IDirect3DIndexBuffer8 *LPDIRECT3DINDEXBUFFER8, *PDIRECT3DINDEXBUFFER8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DIndexBuffer8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DIndexBuffer8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DIndexBuffer8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DIndexBuffer8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DIndexBuffer8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DIndexBuffer8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DIndexBuffer8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DIndexBuffer8_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DIndexBuffer8_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DIndexBuffer8_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DIndexBuffer8_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DIndexBuffer8_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirect3DIndexBuffer8_Unlock(p) (p)->lpVtbl->Unlock(p)
#define IDirect3DIndexBuffer8_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#else
#define IDirect3DIndexBuffer8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DIndexBuffer8_AddRef(p) (p)->AddRef()
#define IDirect3DIndexBuffer8_Release(p) (p)->Release()
#define IDirect3DIndexBuffer8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DIndexBuffer8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DIndexBuffer8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DIndexBuffer8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DIndexBuffer8_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DIndexBuffer8_GetPriority(p) (p)->GetPriority()
#define IDirect3DIndexBuffer8_PreLoad(p) (p)->PreLoad()
#define IDirect3DIndexBuffer8_GetType(p) (p)->GetType()
#define IDirect3DIndexBuffer8_Lock(p,a,b,c,d) (p)->Lock(a,b,c,d)
#define IDirect3DIndexBuffer8_Unlock(p) (p)->Unlock()
#define IDirect3DIndexBuffer8_GetDesc(p,a) (p)->GetDesc(a)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DSurface8

DECLARE_INTERFACE_(IDirect3DSurface8, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DSurface8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(THIS_ D3D8SURFACE_DESC *pDesc) PURE;
    STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS) PURE;
};

typedef struct IDirect3DSurface8 *LPDIRECT3DSURFACE8, *PDIRECT3DSURFACE8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSurface8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSurface8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DSurface8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DSurface8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DSurface8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DSurface8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DSurface8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DSurface8_GetContainer(p,a,b) (p)->lpVtbl->GetContainer(p,a,b)
#define IDirect3DSurface8_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#define IDirect3DSurface8_LockRect(p,a,b,c) (p)->lpVtbl->LockRect(p,a,b,c)
#define IDirect3DSurface8_UnlockRect(p) (p)->lpVtbl->UnlockRect(p)
#else
#define IDirect3DSurface8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DSurface8_AddRef(p) (p)->AddRef()
#define IDirect3DSurface8_Release(p) (p)->Release()
#define IDirect3DSurface8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DSurface8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DSurface8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DSurface8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DSurface8_GetContainer(p,a,b) (p)->GetContainer(a,b)
#define IDirect3DSurface8_GetDesc(p,a) (p)->GetDesc(a)
#define IDirect3DSurface8_LockRect(p,a,b,c) (p)->LockRect(a,b,c)
#define IDirect3DSurface8_UnlockRect(p) (p)->UnlockRect()
#endif




#undef INTERFACE
#define INTERFACE IDirect3DVolume8

DECLARE_INTERFACE_(IDirect3DVolume8, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVolume8 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(THIS_ D3D8VOLUME_DESC *pDesc) PURE;
    STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) PURE;
    STDMETHOD(UnlockBox)(THIS) PURE;
};

typedef struct IDirect3DVolume8 *LPDIRECT3DVOLUME8, *PDIRECT3DVOLUME8;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVolume8_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVolume8_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVolume8_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVolume8_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVolume8_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVolume8_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVolume8_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVolume8_GetContainer(p,a,b) (p)->lpVtbl->GetContainer(p,a,b)
#define IDirect3DVolume8_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#define IDirect3DVolume8_LockBox(p,a,b,c) (p)->lpVtbl->LockBox(p,a,b,c)
#define IDirect3DVolume8_UnlockBox(p) (p)->lpVtbl->UnlockBox(p)
#else
#define IDirect3DVolume8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVolume8_AddRef(p) (p)->AddRef()
#define IDirect3DVolume8_Release(p) (p)->Release()
#define IDirect3DVolume8_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVolume8_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DVolume8_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DVolume8_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DVolume8_GetContainer(p,a,b) (p)->GetContainer(a,b)
#define IDirect3DVolume8_GetDesc(p,a) (p)->GetDesc(a)
#define IDirect3DVolume8_LockBox(p,a,b,c) (p)->LockBox(a,b,c)
#define IDirect3DVolume8_UnlockBox(p) (p)->UnlockBox()
#endif

/****************************************************************************
 * Flags for SetPrivateData method on all D3D8 interfaces
 *
 * The passed pointer is an IUnknown ptr. The SizeOfData argument to SetPrivateData
 * must be set to sizeof(IUnknown*). Direct3D will call AddRef through this
 * pointer and Release when the private data is destroyed. The data will be
 * destroyed when another SetPrivateData with the same GUID is set, when
 * FreePrivateData is called, or when the D3D8 object is freed.
 ****************************************************************************/
#define D3DSPD_IUNKNOWN                         0x00000001L

/****************************************************************************
 *
 * Parameter for IDirect3D8 Enum and GetCaps8 functions to get the info for
 * the current mode only.
 *
 ****************************************************************************/

#define D3DCURRENT_DISPLAY_MODE                 0x00EFFFFFL

/****************************************************************************
 *
 * Flags for IDirect3D8::CreateDevice's BehaviorFlags
 *
 ****************************************************************************/

#define D3DCREATE_FPU_PRESERVE                  0x00000002L
#define D3DCREATE_MULTITHREADED                 0x00000004L

#define D3DCREATE_PUREDEVICE                    0x00000010L
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING     0x00000020L
#define D3DCREATE_HARDWARE_VERTEXPROCESSING     0x00000040L
#define D3DCREATE_MIXED_VERTEXPROCESSING        0x00000080L

#define D3DCREATE_DISABLE_DRIVER_MANAGEMENT     0x00000100L


/****************************************************************************
 *
 * Parameter for IDirect3D8::CreateDevice's iAdapter
 *
 ****************************************************************************/

#define D3DADAPTER_DEFAULT                     0

/****************************************************************************
 *
 * Flags for IDirect3D8::EnumAdapters
 *
 ****************************************************************************/

#define D3DENUM_NO_WHQL_LEVEL                   0x00000002L

/****************************************************************************
 *
 * Maximum number of back-buffers supported in DX8
 *
 ****************************************************************************/

#define D3DPRESENT_BACK_BUFFERS_MAX             3L

/****************************************************************************
 *
 * Flags for IDirect3DDevice8::SetGammaRamp
 *
 ****************************************************************************/

#define D3DSGR_NO_CALIBRATION                  0x00000000L
#define D3DSGR_CALIBRATE                       0x00000001L

/****************************************************************************
 *
 * Flags for IDirect3DDevice8::SetCursorPosition
 *
 ****************************************************************************/

#define D3DCURSOR_IMMEDIATE_UPDATE             0x00000001L

/****************************************************************************
 *
 * Flags for DrawPrimitive/DrawIndexedPrimitive
 *   Also valid for Begin/BeginIndexed
 *   Also valid for VertexBuffer::CreateVertexBuffer
 ****************************************************************************/


/*
 *  DirectDraw error codes
 */
#define _FACD3D  0x876
#define MAKE_D3DHRESULT( code )  MAKE_HRESULT( 1, _FACD3D, code )

/*
 * Direct3D Errors
 */
#define D3D_OK                              S_OK

#define D3DERR_WRONGTEXTUREFORMAT               MAKE_D3DHRESULT(2072)
#define D3DERR_UNSUPPORTEDCOLOROPERATION        MAKE_D3DHRESULT(2073)
#define D3DERR_UNSUPPORTEDCOLORARG              MAKE_D3DHRESULT(2074)
#define D3DERR_UNSUPPORTEDALPHAOPERATION        MAKE_D3DHRESULT(2075)
#define D3DERR_UNSUPPORTEDALPHAARG              MAKE_D3DHRESULT(2076)
#define D3DERR_TOOMANYOPERATIONS                MAKE_D3DHRESULT(2077)
#define D3DERR_CONFLICTINGTEXTUREFILTER         MAKE_D3DHRESULT(2078)
#define D3DERR_UNSUPPORTEDFACTORVALUE           MAKE_D3DHRESULT(2079)
#define D3DERR_CONFLICTINGRENDERSTATE           MAKE_D3DHRESULT(2081)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER         MAKE_D3DHRESULT(2082)
#define D3DERR_CONFLICTINGTEXTUREPALETTE        MAKE_D3DHRESULT(2086)
#define D3DERR_DRIVERINTERNALERROR              MAKE_D3DHRESULT(2087)

#define D3DERR_NOTFOUND                         MAKE_D3DHRESULT(2150)
#define D3DERR_MOREDATA                         MAKE_D3DHRESULT(2151)
#define D3DERR_DEVICELOST                       MAKE_D3DHRESULT(2152)
#define D3DERR_DEVICENOTRESET                   MAKE_D3DHRESULT(2153)
#define D3DERR_NOTAVAILABLE                     MAKE_D3DHRESULT(2154)
#define D3DERR_OUTOFVIDEOMEMORY                 MAKE_D3DHRESULT(380)
#define D3DERR_INVALIDDEVICE                    MAKE_D3DHRESULT(2155)
#define D3DERR_INVALIDCALL                      MAKE_D3DHRESULT(2156)
#define D3DERR_DRIVERINVALIDCALL                MAKE_D3DHRESULT(2157)

#ifdef __cplusplus
};
#endif

#endif /* (DIRECT3D_VERSION >= 0x0800) */
#endif /* _D3D_H_ */

#endif // _D3D8PORT_H_1b37b920_7e12_4129_962a_39fc38ed2983_
