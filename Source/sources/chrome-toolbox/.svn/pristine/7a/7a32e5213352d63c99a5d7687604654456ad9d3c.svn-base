#include "api_hook.h"
#include "apihook.h"
#include "log.h"
#include "mydsound.h"

HMODULE g_module;
Log g_log;

#pragma data_seg("Shared")
BOOL g_browser_mute = FALSE;
#pragma data_seg()
#pragma comment(linker, "/Section:Shared,rws")

typedef int (WINAPI* PfnWaveOutWrite)(HWAVEOUT hwo, LPWAVEHDR pwh, 
                                      UINT cbwh);
typedef int (WINAPI* PfnMidiStreamOut)(HMIDISTRM hms, LPMIDIHDR pmh, 
                                       UINT cbmh);
typedef int (WINAPI* PfnDirectSoundCreate)(LPCGUID pcGuidDevice, 
                                           LPDIRECTSOUND *ppDS, 
                                           LPUNKNOWN pUnkOuter);
typedef int (WINAPI* PfnDirectSoundCreate8)(LPCGUID pcGuidDevice, 
                                            LPDIRECTSOUND8 *ppDS, 
                                            LPUNKNOWN pUnkOuter);

ApiHook* g_direct_sound_create;
ApiHook* g_direct_sound_create_8;
ApiHook* g_wave_out_write;
ApiHook* g_midi_stream_out;

MMRESULT WINAPI HookWaveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh) {
  if (g_browser_mute) {
    memset(pwh->lpData, 0 , pwh->dwBufferLength);
  }

  MMRESULT result = ((PfnWaveOutWrite)(PROC)*g_wave_out_write)(hwo, pwh, cbwh);
  return result;
}

HRESULT WINAPI HookDirectSoundCreate(LPCGUID pcGuidDevice, 
                                     LPDIRECTSOUND *ppDS, 
                                     LPUNKNOWN pUnkOuter) {
  g_log.WriteLog("msg", "Hook_DirectSoundCreate");
  HRESULT hr = ((PfnDirectSoundCreate)(PROC)*g_direct_sound_create)(
      pcGuidDevice, ppDS, pUnkOuter);

  if (SUCCEEDED(hr)) {
    MyDirectSound* p = new MyDirectSound;
    p->direct_sound_ = *ppDS;
    *ppDS = p;
    g_log.WriteLog("msg", "Hook_DirectSoundCreate Success");
  }
  return hr;
}

HRESULT WINAPI HookDirectSoundCreate8(LPCGUID pcGuidDevice, 
                                      LPDIRECTSOUND8 *ppDS, 
                                      LPUNKNOWN pUnkOuter) {
  g_log.WriteLog("msg", "Hook_DirectSoundCreate8");
  HRESULT hr = ((PfnDirectSoundCreate8)(PROC)*g_direct_sound_create_8)(
      pcGuidDevice, ppDS, pUnkOuter);

  if (SUCCEEDED(hr)) {
    MyDirectSound8* p = new MyDirectSound8;
    p->direct_sound_ = *ppDS;
    *ppDS = p;
    g_log.WriteLog("msg", "Hook_DirectSoundCreate8 Success");
  }
  return hr;
}

MMRESULT WINAPI HookMidiStreamOut(HMIDISTRM hms, LPMIDIHDR pmh, UINT cbmh) {
  if (g_browser_mute) {
    memset(pmh->lpData, 0 , pmh->dwBufferLength);
  }

  MMRESULT result = ((PfnMidiStreamOut)(PROC)*g_midi_stream_out)(
      hms, pmh, cbmh);
  return result;
}

void Init() {
  ApiHook::Init();
  g_direct_sound_create = new ApiHook("dsound.dll", "DirectSoundCreate", 
                                      (PROC)HookDirectSoundCreate, TRUE);
  g_direct_sound_create_8 = new ApiHook("dsound.dll", "DirectSoundCreate8", 
                                        (PROC)HookDirectSoundCreate8, TRUE);
  g_wave_out_write = new ApiHook("winmm.dll", "waveOutWrite", 
                                 (PROC) HookWaveOutWrite, TRUE);
  g_midi_stream_out = new ApiHook("winmm.dll", "midiStreamOut", 
                                  (PROC)HookMidiStreamOut, TRUE);
  
}

void UnInit() {
  ApiHook::UnInit();
  delete g_direct_sound_create;
  delete g_direct_sound_create_8;
  delete g_wave_out_write;
  delete g_midi_stream_out;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
  g_module = hModule;

  switch(reason) {
    case DLL_PROCESS_ATTACH:
      //g_Log.OpenLog("APIHOOK");
      Init();
      g_log.WriteLog("Msg", "DLL_PROCESS_ATTACH");
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      UnInit();
      g_log.WriteLog("Msg", "DLL_PROCESS_DETACH");
      break;
  }
  return TRUE;
}

void SetBrowserMute(BOOL flag) {
  g_browser_mute = flag;
}