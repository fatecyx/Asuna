#ifndef _HDCALC_H_
#define _HDCALC_H_

ATOM    WINAPI   MyRegisterClass(HINSTANCE);
BOOL    WINAPI   InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif /* _HDCALC_H_ */