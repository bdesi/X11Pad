int main(){

	/* this variable will contain the pointer to the Display structure */
	/* returned when opening a connection.                             */
	Display* display;
	char *msg = "Hello, World!";

	/* open the connection to the display "simey:0". */
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot connect to X server %s\n", "0:0");
		exit (-1);
	}


	/* this variable will be used to store the "default" screen of the  */
	/* X server. usually an X server has only one screen, so we're only */
	/* interested in that screen.                                       */
	int screen_num;

	/* these variables will store the size of the screen, in pixels.    */
	int screen_width;
	int screen_height;
	int win_border_width = 2;

	/* this variable will be used to store the ID of the root window of our */
	/* screen. Each screen always has a root window that covers the whole   */
	/* screen, and always exists.                                           */
	Window root_window;

	/* these variables will be used to store the IDs of the black and white */
	/* colors of the given screen. More on this will be explained later.    */
	unsigned long white_pixel;
	unsigned long black_pixel;

	/* check the number of the default screen for our X server. */
	screen_num = DefaultScreen(display);

	/* find the width of the default screen of our X server, in pixels. */
	screen_width = DisplayWidth(display, screen_num);

	/* find the height of the default screen of our X server, in pixels. */
	screen_height = DisplayHeight(display, screen_num);

	/* find the ID of the root window of the screen. */
	root_window = RootWindow(display, screen_num);

	/* find the value of a white pixel on this screen. */
	white_pixel = WhitePixel(display, screen_num);

	/* find the value of a black pixel on this screen. */
	black_pixel = BlackPixel(display, screen_num);


	/* this variable will store the ID of the newly created window. */
	Window win;

	/* these variables will store the window's width and height. */
	int win_width;
	int win_height;

	/* these variables will store the window's location. */
	int win_x;
	int win_y;

	/* calculate the window's width and height. */
	win_width = DisplayWidth(display, screen_num) / 3;
	win_height = DisplayHeight(display, screen_num) / 3;

	/* position of the window is top-left corner - 0,0. */
	win_x = win_y = 0;

	/* create the window, as specified earlier. */
	win = XCreateSimpleWindow(display,
	                          RootWindow(display, screen_num),
	                          win_x, win_y,
	                          win_width, win_height,
	                          win_border_width, BlackPixel(display, screen_num),
	                          WhitePixel(display, screen_num));



	/* this variable will contain the handle to the returned graphics context. */
	GC gc;

	/* these variables are used to specify various attributes for the GC. */
	/* initial values for the GC. */
	XGCValues values;

	values.cap_style = CapButt;
	values.join_style = JoinBevel;
	/* which values in 'values' to check when creating the GC. */
	unsigned long valuemask = GCCapStyle | GCJoinStyle;

	/* create a new graphical context. */
	gc = XCreateGC(display, win, valuemask, &values);

	if (gc < 0) {
	    fprintf(stderr, "XCreateGC: \n");
	}

	XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask);

	XMapWindow(display, win);

	/* this structure will contain the event's data, once received. */
	XEvent an_event;

	/* enter an "endless" loop of handling events. */
	while (1) {
	    XNextEvent(display, &an_event);
	    switch (an_event.type) {
	    case Expose:
			/* if we have several other expose events waiting, don't redraw. */
			/* we will do the redrawing when we receive the last of them.    */
			if (an_event.xexpose.count > 0)
				break;
			/* ok, now draw the line... */
			XDrawLine(display, win, gc, 0, 100, 400, 100);
			XDrawString(display, win, gc, 50, 50, msg, strlen(msg));
	        break;
	 	case KeyPress:
			/*Close the program if q is pressed.*/
			if (XLookupKeysym(&an_event.xkey, 0) == XK_q) {
				exit(0);
			}
			if (XLookupKeysym(&an_event.xkey, 0) == XK_r) {

				/* draw a rectangle whose top-left corner is at '120,150', its width is */
				/* 50 pixels, and height is 60 pixels.                                  */
				XFlush(display);
				XDrawRectangle(display, win, gc, 120, 150, 50, 60);
			}
			if (XLookupKeysym(&an_event.xkey, 0) == XK_p) {
				/* draw a filled rectangle of the same size as above, to the left of the  */
				/* previous rectangle. note that this rectangle is one pixel smaller than */
				/* the previous line, since 'XFillRectangle()' assumes it is filling up   */
				/* an already drawn rectangle. This may be used to draw a rectangle using */
				/* one color, and later to fill it using another color.                   */
				XFillRectangle(display, win, gc, 60, 150, 50, 60);
			}
			break;
	      default: /* unknown event type - ignore it. */
	        break;
	    }
	}

	XCloseDisplay(display);

  return 0;
}
 
