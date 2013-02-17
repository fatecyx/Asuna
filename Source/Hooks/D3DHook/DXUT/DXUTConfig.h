#ifndef _DXUTCONFIG_H_3eb9e976_9609_494b_bd2f_750d6f0a186d_
#define _DXUTCONFIG_H_3eb9e976_9609_494b_bd2f_750d6f0a186d_

#define DXUT_EXPORT     0
#define DXUT_IMPORT     0

#if (DXUT_EXPORT + DXUT_IMPORT) > 1
    #error multi-mode
#endif

#if DXUT_EXPORT

    #define DXUT_API DECL_EXPORT

#elif DXUT_IMPORT

    #define DXUT_API DECL_IMPORT

#else

    #define DXUT_API

#endif // DXUT_API

#endif // _DXUTCONFIG_H_3eb9e976_9609_494b_bd2f_750d6f0a186d_
