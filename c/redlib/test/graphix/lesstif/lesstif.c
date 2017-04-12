/* Copyright (C) 1997-2.12  Daniel W. Crompton <redhat@rphh.org> */

/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/* CVSVERSION: $Id: $ */
/* Last modified: Fri 14 Feb 2003 01:50:13 GMT
 */

/* 
LDFLAGS='-L/usr/X11R6/lib/ -L/usr/local/LessTif/Motif2.1/lib/ -lMrm -lXm -lXt -lXext -lX11 -lSM -lICE -lXp'
CFLAGS='-Wall -ggdb3 -I/usr/local/LessTif/Motif2.1/include/ -I/usr/X11R6/include/'
 */

#include <Xm/Xm.h>
#include <Xm/MainW.h>

//#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_FONT "-schumacher-clean-medium-r-normal--*-*-*-*-c-60-iso646.1991-irv"

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		Window X_win;
		Display *X_disp;
		char *X_disp_name = NULL;
		XSetWindowAttributes X_win_attr;
		XTextProperty X_win_name, X_win_icon;
		char *win_name = "Windows Name";
		char *win_icon = "Windows Icon";
		XSizeHints X_size_hints;
		XWMHints X_wm_hints;
		XClassHint X_class_hints;
		GC X_gc, X_gc_inv, X_gc_headbar, X_gc_headbar_inv;
		unsigned long X_gc_value_mask = 0;
		XGCValues X_gc_values;
		XFontStruct *X_font_info;
		int x_dim, y_dim;

		x_dim = y_dim = 250;

		memset( &X_size_hints, 0x00, sizeof(XSizeHints));
		memset( &X_wm_hints, 0x00, sizeof(XWMHints));
		memset( &X_class_hints, 0x00, sizeof(XClassHint));

		if((X_disp = XOpenDisplay(X_disp_name)) == NULL)
		{
				printf("Error: %s\n",X_disp_name);
				exit(-1);
		}
		X_win = XCreateSimpleWindow(X_disp, RootWindow(X_disp,DefaultScreen(X_disp)),
						0,																					/* X */
						0,																					/* Y */
						x_dim,																			/* X width */
						y_dim,																			/* Y width */
						2,																					/* border width */
						BlackPixel(X_disp, DefaultScreen(X_disp)),	/* border */
						BlackPixel(X_disp, DefaultScreen(X_disp)));	/* background */

		X_win_attr.save_under = 1;
		//X_win_attr.colormap = default_cmap;
		X_win_attr.backing_store = Always;

		XChangeWindowAttributes(X_disp,X_win, CWSaveUnder| CWBackingStore/*| CWColormap*/, &X_win_attr);

		XStringListToTextProperty(&win_name, 1, &X_win_name);
		XStringListToTextProperty(&win_icon, 1, &X_win_icon);

		X_size_hints.flags = PPosition| PSize | PMinSize | PMaxSize;
		X_size_hints.max_width = X_size_hints.min_width = x_dim;
		X_size_hints.max_height = X_size_hints.min_height = y_dim;

		X_wm_hints.initial_state = NormalState;
		X_wm_hints.input = True;
		X_wm_hints.icon_pixmap =
				XCreateBitmapFromData(X_disp, X_win, (char *) "test value", 5, 5);
		X_wm_hints.flags = StateHint | IconPixmapHint | InputHint;

		X_class_hints.res_name = argv[0];
		X_class_hints.res_class = "Classname";

		XSetWMProperties(X_disp, X_win, &X_win_name, &X_win_icon,
						argv, argc, &X_size_hints, &X_wm_hints, &X_class_hints);

		X_gc							= XCreateGC(X_disp, X_win, X_gc_value_mask, &X_gc_values);
		X_gc_inv					= XCreateGC(X_disp, X_win, X_gc_value_mask, &X_gc_values);
		X_gc_headbar			= XCreateGC(X_disp, X_win, X_gc_value_mask, &X_gc_values);
		X_gc_headbar_inv	= XCreateGC(X_disp, X_win, X_gc_value_mask, &X_gc_values);

		if((X_font_info = XLoadQueryFont(X_disp, MY_FONT)) == NULL)
		{
				printf("Error loading font\n");
		}
		else
				XSetFont(X_disp, X_gc, X_font_info->fid);

		XSetState(X_disp, X_gc,
						WhitePixel(X_disp, DefaultScreen(X_disp)),
						BlackPixel(X_disp, DefaultScreen(X_disp)),
						GXcopy,
						AllPlanes);

		XSetState(X_disp, X_gc_inv,
						BlackPixel(X_disp, DefaultScreen(X_disp)),
						WhitePixel(X_disp, DefaultScreen(X_disp)),
						GXinvert,
						AllPlanes);

		XSetState(X_disp, X_gc_headbar,
						BlackPixel(X_disp, DefaultScreen(X_disp)),
						WhitePixel(X_disp, DefaultScreen(X_disp)),
						GXcopy,
						AllPlanes);

		XSetState(X_disp, X_gc_headbar_inv,
						WhitePixel(X_disp, DefaultScreen(X_disp)),
						BlackPixel(X_disp, DefaultScreen(X_disp)),
						GXcopy,
						AllPlanes);

		XMapWindow(X_disp, X_win);
		XSync(X_disp, 0);
		while (1)
		{
				XEvent report;
				XNextEvent(X_disp, &report);
				if(report.type == MapNotify) break;
				printf("X\n");
		};
		/*
		Widget XMww = (Widget)calloc(1, sizeof(Widget));

		XmCreateMainWindow(XmGetDestination(X_disp), "Main Window", NULL, 0);
		*/

		return 0;
}

