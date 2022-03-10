#ifndef __RENDERWINDOW_H__
#define __RENDERWINDOW_H__

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#include <vector>
#include "type.h"
#include "rasterization.h"

#ifdef _WIN32
class BaseWindow {
public:
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
};
#elif __linux__
class BaseWindow{
	//nothing to do
};
#endif

class RenderWindow:public BaseWindow {
public:
#ifdef _WIN32
	HWND hwnd;
	MSG msg;
	HDC memdc;
	HBITMAP bitmap;
#elif __linux__
    Display *xDisplay;
    int xScreen;
    Window handle;
    XImage *xImage;
#endif

	bool isClose;
	int width;
	int height;
	bool keyboard[4]; // ˳��Ϊ����������
	bool mouseLeft; // �������Ƿ���
	vec2f mouseLocOld; //��һ֡�����λ��?
	int wheelAngle; // ���־���
	unsigned char *windowFramebuffer;
	Rasterization *r;
	
	RenderWindow(Rasterization *r);
	void windowInit();
	void windowDraw();
	void handleMsg();
	void handleKeyboardAndMouseEvent();

#ifdef _WIN32
	LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#elif __linux__
	void handleMessage(XEvent *event);
#endif
};

#endif // !__WINDOW_H__
