#include "window.h"

Window::Window(Rasterization *r)
{
	this->r = r;
	this->isClose = false;
	this->width = r->width;
	this->height = r->height;
	for (int i = 0; i < 4; ++i) {
		this->keyboard[i] = false;
	}
	this->mouseLeft = false;
	this->wheelAngle = 0;
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

	LPVOID ptr;
	BITMAPINFOHEADER bi;
	memset(&bi, 0, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;   //从上到下
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = width * height * 4;

	HDC hdc = GetDC(hwnd);
	memdc = CreateCompatibleDC(hdc);
	ReleaseDC(hwnd, hdc);
	bitmap = CreateDIBSection(memdc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &ptr, 0, 0);
	SelectObject(memdc, bitmap);
	windowFramebuffer = (unsigned char*)ptr;
	memset(windowFramebuffer, 0, width * height * 4);

	ShowWindow(hwnd, SW_NORMAL);
	handleMsg();
}

void Window::windowDraw()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int indexWindowFB = (width * (height - j - 1) + i) * 4;
			int indexFB = r->getIndex(i, j);
			//framebuffer是以左下角为起点，windowFramebuffer是以左上角为起点
			windowFramebuffer[indexWindowFB] = r->frameBuffer[indexFB][2];
			windowFramebuffer[indexWindowFB + 1] = r->frameBuffer[indexFB][1];
			windowFramebuffer[indexWindowFB + 2] = r->frameBuffer[indexFB][0];
		}

	}

	HDC hDC = GetDC(hwnd);
	BitBlt(hDC, 0, 0, width, height, memdc, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hDC);
}

void Window::handleMsg()
{
	while (1)
	{
		// Peek不阻塞，Get会阻塞，PM_NOREMOVE表示如果有消息不处理（留给接下来的Get处理）
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break; //没消息就溜，确定有消息再用Get
		if (!GetMessage(&msg, NULL, 0, 0)) break;

		TranslateMessage(&msg);	 //转换消息 虚拟按键->字符
		DispatchMessage(&msg); //传送消息给回调
	}
}

LRESULT Window::handleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:  //正在销毁窗口
		this->isClose = true;
		return 0;

	case WM_CLOSE:
		this->isClose = true;
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			this->keyboard[0] = true;
		}
		if (wParam == VK_DOWN) {
			this->keyboard[1] = true;
		}
		if (wParam == VK_LEFT) {
			this->keyboard[2] = true;
		}
		if (wParam == VK_RIGHT) {
			this->keyboard[3] = true;
		}
		return 0;

	case WM_KEYUP:
		if (wParam == VK_UP) {
			this->keyboard[0] = false;
		}
		if (wParam == VK_DOWN) {
			this->keyboard[1] = false;
		}
		if (wParam == VK_LEFT) {
			this->keyboard[2] = false;
		}
		if (wParam == VK_RIGHT) {
			this->keyboard[3] = false;
		}
		return 0;

	case WM_LBUTTONDOWN:
		this->mouseLeft = true;
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point); // 从屏幕空间转到窗口空间
		this->mouseLocOld = { (float)point.x, (float)point.y };
		return 0;

	case WM_LBUTTONUP:
		this->mouseLeft = false;
		return 0;

	case WM_MOUSEWHEEL:
		this->wheelAngle = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Window::handleKeyboardAndMouseEvent()
{
	if (keyboard[0]) {
		for (int i = 0; i < 3; ++i) {
			r->scene->camera->posi[i] += r->scene->camera->front[i] * 0.1;
		}
	}
	if (keyboard[1]) {
		for (int i = 0; i < 3; ++i) {
			r->scene->camera->posi[i] -= r->scene->camera->front[i] * 0.1;
		}
	}
	if (keyboard[2]) {
		vec3f tmp = normalized(crossProduct(r->scene->camera->front, r->scene->camera->up));
		for (int i = 0; i < 3; ++i) {
			r->scene->camera->posi[i] -= tmp[i] * 0.1;
		}
	}
	if (keyboard[3]) {
		vec3f tmp = normalized(crossProduct(r->scene->camera->front, r->scene->camera->up));
		for (int i = 0; i < 3; ++i) {
			r->scene->camera->posi[i] += tmp[i] * 0.1;
		}
	}
	if (mouseLeft) {
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(hwnd, &point); // 从屏幕空间转到窗口空间
		vec2f mouseLocNew = { (float)point.x,(float)point.y };
		vec3f mouseOffset = { (mouseLocNew[0] - mouseLocOld[0])*0.5,(mouseLocNew[1] - mouseLocOld[1])*0.5 };
		mouseLocOld = mouseLocNew;
		r->scene->camera->yaw += mouseOffset[0];
		r->scene->camera->pitch += mouseOffset[1];
		if (r->scene->camera->pitch > 89) {
			r->scene->camera->pitch = 89;
		}
		if (r->scene->camera->pitch < -89) {
			r->scene->camera->pitch = -89;
		}
		r->scene->camera->handlePitchAndYawChange();
	}
	if (wheelAngle) {
		r->scene->camera->verticalAngle += wheelAngle*0.01;
		if (r->scene->camera->verticalAngle > 179)
			r->scene->camera->verticalAngle = 179;
		if (r->scene->camera->verticalAngle < 1)
			r->scene->camera->verticalAngle = 1;
		wheelAngle = 0;
	}

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