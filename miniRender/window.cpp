#include "window.h"

Window::Window(Rasterization *r)
{
	this->width = r->width;
	this->height = r->height;
	this->r = r;
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
	//UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		r->render();
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT Window::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		vec3f tmpColor;
		int tmpIndex;

		for (int i = 0; i < this->width; ++i) {
			for (int j = 0; j < this->height; ++j) {
				tmpIndex = r->getIndex(i, j);
				tmpColor = r->frameBuffer[tmpIndex];
				SetPixel(hdc, i, j, RGB(tmpColor[0], tmpColor[1], tmpColor[2]));
			}
		}
		EndPaint(hwnd, &ps);
		return 0;
	}

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
		PostQuitMessage(0);
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