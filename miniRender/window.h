#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <windows.h>
#include <vector>
#include "type.h"
#include "rasterization.h"

class BaseWindow {
public:
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
};

class Window:public BaseWindow {
public:
	HWND hwnd;
	MSG msg;
	HDC memdc;
	HBITMAP bitmap;
	bool isClose;
	int width;
	int height;
	bool keyboard[4]; // 顺序为：上下左右
	bool mouseLeft; // 鼠标左键是否按下
	vec2f mouseLocOld; //上一帧的鼠标位置
	int wheelAngle; // 滚轮距离
	unsigned char *windowFramebuffer;
	Rasterization *r;
	
	Window(Rasterization *r);
	void windowInit();
	void windowDraw();
	void handleMsg();
	void handleKeyboardAndMouseEvent();
	LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // !__WINDOW_H__
