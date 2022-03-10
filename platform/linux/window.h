#pragma once
#ifndef __RENDERWINDOW_H__
#define __RENDERWINDOW_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include "../../type.h"
#include "../../rasterization.h"

class RenderWindow {
public:
    Display *xDisplay;
    int xScreen;
    Window handle;
    XImage *xImage;

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
	void handleMessage(XEvent *event);
};

#endif // !__WINDOW_H__
