#include "window.h"

Window::Window(Rasterization *r)
{
	this->r = r;
	this->isClose = false;
	this->width = r->width;
	this->height = r->height;
}

void Window::windowInit()
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.lpszClassName = "fantasyRenderWindow";
	wc.hInstance = hInst;
	wc.lpfnWndProc = Window::wndProc;

	RegisterClass(&wc);

	hwnd = CreateWindow(
		"fantasyRenderWindow",
		"fantasyRender",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL, NULL, hInst, this
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "创建窗口出错!", "error", MB_OK);
	}

	SetProp(hwnd, "struct_window_pointer", this);
}

void Window::windowShow()
{
	ShowWindow(hwnd, SW_SHOW);
}

void Window::handleMsg()
{
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT Window::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//case WM_LBUTTONDOWN:  //用户单击鼠标左键
	//{
	//	char szPoint[56];
	//	//保存坐标信息
	//	wsprintf(szPoint, "X = %d,Y = %d", LOWORD(lParam), HIWORD(lParam));
	//	str = szPoint;
	//	if (wParam & MK_SHIFT)
	//		str = str + " Shift Key is down";
	//	InvalidateRect(hwnd, NULL, 1);
	//	return 0;
	//}

	case WM_DESTROY:  //正在销毁窗口
		this->isClose = true;
		return 0;

	case WM_CLOSE:
		this->isClose = true;
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK BaseWindow::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window *pthis = nullptr;
	pthis = (Window*)GetProp(hwnd, "struct_window_pointer");
	if (pthis == NULL) {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return pthis->handleMessage(hwnd, msg, wParam, lParam);
}