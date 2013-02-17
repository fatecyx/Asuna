#ifdef _EXPORT_APIHOOK_INCLUDE_
#define APIHOOK_EXPORT __declspec(dllexport)
#else
#define APIHOOK_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif  

APIHOOK_EXPORT void SetBrowserMute(BOOL flag);

#ifdef __cplusplus
}
#endif
