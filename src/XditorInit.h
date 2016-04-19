/*
 * XditorInit.h
 *
 *  Created on: 04.04.2016
 *      Author: desikabj
 */

#ifndef XDITORINIT_H_
#define XDITORINIT_H_

/* include some silly stuff */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

struct XInitBuffer{
	Display *dis;
	int screen;
	Window win;
	GC gc;
};

typedef XInitBuffer XditorBuf;

/* here are our X routines declared! */
void init_x(XditorBuf **pXditorBuf);
void close_x(XditorBuf **pXditorBuf);
void redraw(XditorBuf **pXditorBuf);


#endif /* XDITORINIT_H_ */
