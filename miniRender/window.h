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
	bool keyboard[4]; // ˳��Ϊ����������
	bool mouseLeft; // �������Ƿ���
	vec2f mouseLocOld; //��һ֡�����λ��
	int wheelAngle; // ���־���
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
