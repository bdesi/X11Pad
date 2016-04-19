/*
 * main.cc
 *
 *  Created on: 01.04.2016
 *      Author: desikabj
 */

/* include the X library headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <XditorInit.h>

int main () {
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */
	char text[255];		/* a char buffer for KeyPress Events */
	XditorBuf *bufInit;

	//bufInit=(XditorBuf*) malloc(sizeof (XditorBuf));
	// C++ style allocation
	bufInit= new XditorBuf;
	init_x(&bufInit);

	/* look for events forever... */
	while(1) {
		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		XNextEvent(bufInit->dis, &event);

		if (event.type==Expose && event.xexpose.count==0) {
		/* the window was exposed redraw it! */
			redraw(&bufInit);
		}
		if (event.type==KeyPress) {
			XLookupString(&event.xkey,text,255,&key,0);
			fprintf(stderr, "You pressed the %c key!\n",text[0]);
			/*Close the program if q is pressed.*/
			if (XLookupKeysym(&event.xkey, 0) == XK_q) {
				close_x(&bufInit);
				exit(0);
			}
			if (XLookupKeysym(&event.xkey, 0) == XK_r) {

				/* draw a rectangle whose top-left corner is at '120,150', its width is */
				/* 50 pixels, and height is 60 pixels.                                  */
				XDrawRectangle(bufInit->dis, bufInit->win, bufInit->gc, 120, 150, 50, 60);
			}
			if (XLookupKeysym(&event.xkey, 0) == XK_p) {
				/* draw a filled rectangle of the same size as above, to the left of the  */
				/* previous rectangle. note that this rectangle is one pixel smaller than */
				/* the previous line, since 'XFillRectangle()' assumes it is filling up   */
				/* an already drawn rectangle. This may be used to draw a rectangle using */
				/* one color, and later to fill it using another color.                   */
				XFillRectangle(bufInit->dis, bufInit->win, bufInit->gc, 60, 150, 50, 60);
			}
		}
		if (event.type==ButtonPress) {
		/* tell where the mouse Button was Pressed */
			int x=event.xbutton.x,
			    y=event.xbutton.y;

			strcpy(text,"X is FUN!");
			XSetForeground(bufInit->dis,bufInit->gc,rand()%event.xbutton.x%255);
			XDrawString(bufInit->dis,bufInit->win,bufInit->gc,x,y, text, strlen(text));
		}
		if (event.type==ClientMessage)
        {
			fprintf(stderr, "Application closed clicked!!!\n");
			XCloseDisplay(bufInit->dis);
			break;
        }
		if (event.type==ConfigureNotify)
		{
			fprintf(stderr, "Window moved or resized!\n");
		}
	}

	return 0;
}

