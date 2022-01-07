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
	unsigned int width;
	unsigned int height;
	vec2f mouseLocation;
	Rasterization *r;
	
	Window(Rasterization *r);
	void windowInit();
	void windowShow();
	LRESULT handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // !__WINDOW_H__

