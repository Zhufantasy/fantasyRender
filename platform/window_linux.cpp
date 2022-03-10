#include "../window.h"

RenderWindow::RenderWindow(Rasterization *r)
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

void RenderWindow::windowInit()
{
    xDisplay=XOpenDisplay(NULL);

    xScreen=XDefaultScreen(xDisplay);
    Window root=XRootWindow(xDisplay,xScreen);
    handle=XCreateSimpleWindow(xDisplay,root,0,0,width,height,0,XWhitePixel(xDisplay,xScreen),XBlackPixel(xDisplay,xScreen));
    long mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask;
    XSelectInput(xDisplay,handle,mask);
    Atom deleteWindow = XInternAtom(xDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(xDisplay, handle, &deleteWindow, 1);

    int depth=XDefaultDepth(xDisplay,xScreen);
    Visual *xVisual=XDefaultVisual(xDisplay,xScreen);
    windowFramebuffer=(unsigned char*)malloc(width*height*4);
    memset(windowFramebuffer, 0, width * height * 4);
    xImage=XCreateImage(xDisplay,xVisual,depth,ZPixmap,0,(char*)windowFramebuffer,width,height,32,0);

    XMapWindow(xDisplay,handle);
    XFlush(xDisplay);

}

void RenderWindow::windowDraw()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int indexWindowFB = (width * (height - j - 1) + i) * 4;
			int indexFB = r->getIndex(i, j);
			//framebuffer�������½�Ϊ��㣬windowFramebuffer�������Ͻ�Ϊ���
			windowFramebuffer[indexWindowFB] = r->frameBuffer[indexFB][2];
			windowFramebuffer[indexWindowFB + 1] = r->frameBuffer[indexFB][1];
			windowFramebuffer[indexWindowFB + 2] = r->frameBuffer[indexFB][0];
		}

	}

    GC gc=XDefaultGC(xDisplay,xScreen);
    XPutImage(xDisplay,handle,gc,xImage,0,0,0,0,width,height);
    XFlush(xDisplay);
}

void RenderWindow::handleMsg()
{
    int count=XPending(xDisplay);
    while(count>0){
        XEvent event;
        XNextEvent(xDisplay,&event);
        handleMessage(&event);
        count--;
    }
    XFlush(xDisplay);
}

void RenderWindow::handleMessage(XEvent *event)
{
    if(event->type == ClientMessage){
        static Atom protocols = None;
        static Atom deleteWindow = None;
        if (protocols == None) {
            protocols = XInternAtom(xDisplay, "WM_PROTOCOLS", True);
            deleteWindow = XInternAtom(xDisplay, "WM_DELETE_WINDOW", True);
        }
        if (event->xclient.message_type == protocols) {
            Atom protocol = event->xclient.data.l[0];
            if (protocol == deleteWindow) {
                this->isClose = true;
            }
        }
    }
    else if(event->type == KeyPress){
            KeySym *keysyms;
            KeySym keysym;
            int dummy;
            keysyms = XGetKeyboardMapping(xDisplay, event->xkey.keycode, 1, &dummy);
            keysym = keysyms[0];
            XFree(keysyms);

            switch (keysym) {
                case XK_Up:        this->keyboard[0] = true;     break;
                case XK_Down:      this->keyboard[1] = true;     break;
                case XK_Left:      this->keyboard[2] = true;     break;
                case XK_Right:     this->keyboard[3] = true;     break;
                default:           break;
            }
    }
    else if(event->type == KeyRelease){
            KeySym *keysyms;
            KeySym keysym;
            int dummy;
            keysyms = XGetKeyboardMapping(xDisplay, event->xkey.keycode, 1, &dummy);
            keysym = keysyms[0];
            XFree(keysyms);

            switch (keysym) {
                case XK_Up:        this->keyboard[0] = false;     break;
                case XK_Down:      this->keyboard[1] = false;     break;
                case XK_Left:      this->keyboard[2] = false;     break;
                case XK_Right:     this->keyboard[3] = false;     break;
                default:           break;
            }
    }
    else if(event->type == ButtonPress){
        if(event->xbutton.button == Button1){
		    this->mouseLeft = true;
            Window root, child;
            int root_x, root_y, window_x, window_y;
            unsigned int mask;
            XQueryPointer(xDisplay, handle, &root, &child, &root_x, &root_y, &window_x, &window_y, &mask);
            this->mouseLocOld = { (float)window_x, (float)window_y };
        }
        else if(event->xbutton.button == Button4){
            this->wheelAngle = 120;
        }
        else if(event->xbutton.button == Button5){
            this->wheelAngle = -120;
        }
    }
    else if(event->type == ButtonRelease){
        if(event->xbutton.button == Button1){
		    this->mouseLeft = false;
        }
        else if(event->xbutton.button == Button4){
            this->wheelAngle = 120;
        }
        else if(event->xbutton.button == Button5){
            this->wheelAngle = -120;
        }
    }
}

void RenderWindow::handleKeyboardAndMouseEvent()
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
        Window root, child;
        int root_x, root_y, window_x, window_y;
        unsigned int mask;
        XQueryPointer(xDisplay, handle, &root, &child, &root_x, &root_y, &window_x, &window_y, &mask);
		vec2f mouseLocNew = { (float)window_x,(float)window_y };
		vec3f mouseOffset = { (mouseLocNew[0] - mouseLocOld[0])*0.5,(mouseLocNew[1] - mouseLocOld[1])*0.5 };
		mouseLocOld = mouseLocNew;
		r->scene->camera->yaw += mouseOffset[0];
		r->scene->camera->pitch -= mouseOffset[1];
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
		if (r->scene->camera->verticalAngle > 90)
			r->scene->camera->verticalAngle = 90;
		if (r->scene->camera->verticalAngle < 1)
			r->scene->camera->verticalAngle = 1;
		wheelAngle = 0;
	}

}