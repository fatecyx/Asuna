#ifndef APIHOOK_MYDSOUND_H_
#define APIHOOK_MYDSOUND_H_

#include <dsound.h>

#include "log.h"

extern BOOL g_browser_mute;
extern Log g_log;

// it's a wapper of IDirectSoundBuffer interface for mute some audio
// played by dsound
class MyDirectSoundBuffer : public IDirectSoundBuffer {
  // IUnknown methods
  STDMETHOD(QueryInterface)       (THIS_ __in REFIID iid, __deref_out LPVOID* lpout) {
    return directsound_buffer_->QueryInterface(iid, lpout);
  }
  STDMETHOD_(ULONG,AddRef)        (THIS) {
    return directsound_buffer_->AddRef();
  }
  STDMETHOD_(ULONG,Release)       (THIS) {
    return directsound_buffer_->Release();
  }

  // IDirectSoundBuffer methods
  STDMETHOD(GetCaps)              (THIS_ __out LPDSBCAPS pDSBufferCaps) {
    return directsound_buffer_->GetCaps(pDSBufferCaps);
  }
  STDMETHOD(GetCurrentPosition)   (THIS_ __out_opt LPDWORD pdwCurrentPlayCursor, __out_opt LPDWORD pdwCurrentWriteCursor) {
    return directsound_buffer_->GetCurrentPosition(pdwCurrentPlayCursor, pdwCurrentWriteCursor);
  }
  STDMETHOD(GetFormat)            (THIS_ __out_bcount_opt(dwSizeAllocated) LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, __out_opt LPDWORD pdwSizeWritten) {
    return directsound_buffer_->GetFormat(pwfxFormat, dwSizeAllocated, pdwSizeWritten);
  }
  STDMETHOD(GetVolume)            (THIS_ __out LPLONG plVolume) {
    return directsound_buffer_->GetVolume(plVolume);
  }
  STDMETHOD(GetPan)               (THIS_ __out LPLONG plPan) {
    return directsound_buffer_->GetPan(plPan);
  }
  STDMETHOD(GetFrequency)         (THIS_ __out LPDWORD pdwFrequency) {
    return directsound_buffer_->GetFrequency(pdwFrequency);
  }
  STDMETHOD(GetStatus)            (THIS_ __out LPDWORD pdwStatus) {
    return directsound_buffer_->GetStatus(pdwStatus);
  }
  STDMETHOD(Initialize)           (THIS_ __in LPDIRECTSOUND pDirectSound, __in LPCDSBUFFERDESC pcDSBufferDesc) {
    return directsound_buffer_->Initialize(pDirectSound, pcDSBufferDesc);
  }
  STDMETHOD(Lock)                 (THIS_ DWORD dwOffset, DWORD dwBytes,
    __deref_out_bcount(*pdwAudioBytes1) LPVOID *ppvAudioPtr1, __out LPDWORD pdwAudioBytes1,
    __deref_opt_out_bcount(*pdwAudioBytes2) LPVOID *ppvAudioPtr2, __out_opt LPDWORD pdwAudioBytes2, DWORD dwFlags) {
      return directsound_buffer_->Lock(dwOffset, dwBytes, ppvAudioPtr1, pdwAudioBytes1, ppvAudioPtr2, pdwAudioBytes2, dwFlags);
  }
  STDMETHOD(Play)                 (THIS_ DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags) {
    return directsound_buffer_->Play(dwReserved1, dwPriority, dwFlags);
  }
  STDMETHOD(SetCurrentPosition)   (THIS_ DWORD dwNewPosition) {
    return directsound_buffer_->SetCurrentPosition(dwNewPosition);
  }
  STDMETHOD(SetFormat)            (THIS_ __in LPCWAVEFORMATEX pcfxFormat) {
    return directsound_buffer_->SetFormat(pcfxFormat);
  }
  STDMETHOD(SetVolume)            (THIS_ LONG lVolume) {
    return directsound_buffer_->SetVolume(lVolume);
  }
  STDMETHOD(SetPan)               (THIS_ LONG lPan) {
    return directsound_buffer_->SetPan(lPan);
  }
  STDMETHOD(SetFrequency)         (THIS_ DWORD dwFrequency) {
    return directsound_buffer_->SetFrequency(dwFrequency);
  }
  STDMETHOD(Stop)                 (THIS) {
    return directsound_buffer_->Stop();
  }
  STDMETHOD(Unlock)               (THIS_ __in_bcount(dwAudioBytes1) LPVOID pvAudioPtr1, DWORD dwAudioBytes1,
    __in_bcount_opt(dwAudioBytes2) LPVOID pvAudioPtr2, DWORD dwAudioBytes2) {
      if (g_browser_mute) {
        if (pvAudioPtr1) {
          memset(pvAudioPtr1, 0, dwAudioBytes1);
        }
        if (pvAudioPtr2) {
          memset(pvAudioPtr2, 0 ,dwAudioBytes2);
        }
      }
      return directsound_buffer_->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);
  }
  STDMETHOD(Restore)              (THIS) {
    return directsound_buffer_->Restore();
  }

public:
  IDirectSoundBuffer* directsound_buffer_;
};

// it's a wapper of IDirectSound interface for mute some audio
// played by dsound
class MyDirectSound : public IDirectSound {

  // IUnknown methods
  STDMETHOD(QueryInterface)       (THIS_ __in REFIID iid, __deref_out LPVOID* lpout) {
    return direct_sound_->QueryInterface(iid, lpout);
  }
  STDMETHOD_(ULONG,AddRef)        (THIS) {
    return direct_sound_->AddRef();
  }
  STDMETHOD_(ULONG,Release)       (THIS) {
    return direct_sound_->Release();
  }

  // IDirectSound methods
  STDMETHOD(CreateSoundBuffer)    (THIS_ __in LPCDSBUFFERDESC pcDSBufferDesc, __deref_out LPDIRECTSOUNDBUFFER *ppDSBuffer, __null LPUNKNOWN pUnkOuter) {
    HRESULT hr = direct_sound_->CreateSoundBuffer(pcDSBufferDesc, ppDSBuffer, pUnkOuter);
    if (SUCCEEDED(hr)) {
      g_log.WriteLog("msg", "CreateSoundBuffer Success");
      MyDirectSoundBuffer* p = new MyDirectSoundBuffer;
      p->directsound_buffer_ = *ppDSBuffer;
      *ppDSBuffer = p;
    }
    return hr;
  }
  STDMETHOD(GetCaps)              (THIS_ __out LPDSCAPS pDSCaps) {
    return direct_sound_->GetCaps(pDSCaps);
  }
  STDMETHOD(DuplicateSoundBuffer) (THIS_ __in LPDIRECTSOUNDBUFFER pDSBufferOriginal, __deref_out LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate) {
    return direct_sound_->DuplicateSoundBuffer(pDSBufferOriginal, ppDSBufferDuplicate);
  }
  STDMETHOD(SetCooperativeLevel)  (THIS_ HWND hwnd, DWORD dwLevel) {
    return direct_sound_->SetCooperativeLevel(hwnd, dwLevel);
  }
  STDMETHOD(Compact)              (THIS) {
    return direct_sound_->Compact();
  }
  STDMETHOD(GetSpeakerConfig)     (THIS_ __out LPDWORD pdwSpeakerConfig) {
    return direct_sound_->GetSpeakerConfig(pdwSpeakerConfig);
  }
  STDMETHOD(SetSpeakerConfig)     (THIS_ DWORD dwSpeakerConfig) {
    return direct_sound_->SetSpeakerConfig(dwSpeakerConfig);
  }
  STDMETHOD(Initialize)           (THIS_ __in_opt LPCGUID pcGuidDevice) {
    return direct_sound_->Initialize(pcGuidDevice);
  }

public:
  IDirectSound* direct_sound_;
};

class MyDirectSound8 : public IDirectSound8 {
  // IUnknown methods
  STDMETHOD(QueryInterface)       (THIS_ __in REFIID iid, __deref_out LPVOID* lpout) {
    return direct_sound_->QueryInterface(iid, lpout);
  }
  STDMETHOD_(ULONG,AddRef)        (THIS) {
    return direct_sound_->AddRef();
  }
  STDMETHOD_(ULONG,Release)       (THIS) {
    return direct_sound_->Release();
  }

  // IDirectSound methods
  STDMETHOD(CreateSoundBuffer)    (THIS_ __in LPCDSBUFFERDESC pcDSBufferDesc, __deref_out LPDIRECTSOUNDBUFFER *ppDSBuffer, __null LPUNKNOWN pUnkOuter) {
    HRESULT hr = direct_sound_->CreateSoundBuffer(pcDSBufferDesc, ppDSBuffer, pUnkOuter);
    if (SUCCEEDED(hr)) {
      g_log.WriteLog("msg", "CreateSoundBuffer Success");
      MyDirectSoundBuffer* p = new MyDirectSoundBuffer;
      p->directsound_buffer_ = *ppDSBuffer;
      *ppDSBuffer = p;
    }
    return hr;
  }
  STDMETHOD(GetCaps)              (THIS_ __out LPDSCAPS pDSCaps) {
    return direct_sound_->GetCaps(pDSCaps);
  }
  STDMETHOD(DuplicateSoundBuffer) (THIS_ __in LPDIRECTSOUNDBUFFER pDSBufferOriginal, __deref_out LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate) {
    return direct_sound_->DuplicateSoundBuffer(pDSBufferOriginal, ppDSBufferDuplicate);
  }
  STDMETHOD(SetCooperativeLevel)  (THIS_ HWND hwnd, DWORD dwLevel) {
    return direct_sound_->SetCooperativeLevel(hwnd, dwLevel);
  }
  STDMETHOD(Compact)              (THIS) {
    return direct_sound_->Compact();
  }
  STDMETHOD(GetSpeakerConfig)     (THIS_ __out LPDWORD pdwSpeakerConfig) {
    return direct_sound_->GetSpeakerConfig(pdwSpeakerConfig);
  }
  STDMETHOD(SetSpeakerConfig)     (THIS_ DWORD dwSpeakerConfig) {
    return direct_sound_->SetSpeakerConfig(dwSpeakerConfig);
  }
  STDMETHOD(Initialize)           (THIS_ __in_opt LPCGUID pcGuidDevice) {
    return direct_sound_->Initialize(pcGuidDevice);
  }

  // IDirectSound8 methods
  STDMETHOD(VerifyCertification)  (THIS_ __out LPDWORD pdwCertified) {
    return direct_sound_->VerifyCertification(pdwCertified);
  }

public:
  IDirectSound8* direct_sound_;

};

#endif