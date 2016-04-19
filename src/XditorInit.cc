/*
 * XditorInit.cc
 *
 *  Created on: 04.04.2016
 *      Author: desikabj
 */

#include <XditorInit.h>

void init_x(XditorBuf **pXditorBuf) {
/* get the colors black and white (see section for details) */
	unsigned long black,white;

	(*pXditorBuf)->dis=XOpenDisplay(NULL);
	(*pXditorBuf)->screen=DefaultScreen((*pXditorBuf)->dis);
	black=BlackPixel((*pXditorBuf)->dis, (*pXditorBuf)->screen),
	white=WhitePixel((*pXditorBuf)->dis, (*pXditorBuf)->screen);
	(*pXditorBuf)->win=XCreateSimpleWindow((*pXditorBuf)->dis,DefaultRootWindow((*pXditorBuf)->dis),0,0, 300, 300, 5,black, white);
	XSetStandardProperties((*pXditorBuf)->dis,(*pXditorBuf)->win,"BDPad++","Hi",None,NULL,0,NULL);
	XSelectInput((*pXditorBuf)->dis, (*pXditorBuf)->win, ExposureMask|ButtonPressMask|KeyPressMask|StructureNotifyMask);
	// I support the WM_DELETE_WINDOW protocol
	Atom WM_DELETE_WINDOW = XInternAtom((*pXditorBuf)->dis, "WM_DELETE_WINDOW", False);
	XSetWMProtocols((*pXditorBuf)->dis, (*pXditorBuf)->win, &WM_DELETE_WINDOW, 1);
	(*pXditorBuf)->gc=XCreateGC((*pXditorBuf)->dis, (*pXditorBuf)->win, 0,0);
	XSetBackground((*pXditorBuf)->dis,(*pXditorBuf)->gc,white);
	XSetForeground((*pXditorBuf)->dis,(*pXditorBuf)->gc,black);
	XClearWindow((*pXditorBuf)->dis, (*pXditorBuf)->win);
	XMapRaised((*pXditorBuf)->dis, (*pXditorBuf)->win);
};

void close_x(XditorBuf **pXditorBuf) {
	XFreeGC((*pXditorBuf)->dis, (*pXditorBuf)->gc);
	XDestroyWindow((*pXditorBuf)->dis,(*pXditorBuf)->win);
	XCloseDisplay((*pXditorBuf)->dis);
	delete (*pXditorBuf);
};

void redraw(XditorBuf **pXditorBuf) {
	XClearWindow((*pXditorBuf)->dis, (*pXditorBuf)->win);
};
