/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *  This program is free software; you can redistribute it and/or modify
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
/* Last modified: Sun 18 Aug 2002 07:50:33 GMT
 */

#include <stdlib.h>
#include <unistd.h>

#include <curses.h>

#include <ncurses/menu.h>
#include <ncurses/form.h>
#include <ncurses/panel.h>

#define EXIT_SUCCESS 0

typedef struct windowpane {
		WINDOW	*ft;
		WINDOW	*fb;
		PANEL		*pt;
		PANEL		*pb;
} windowpane;

static void create_window(name)
		char *name;
{
		windowpane win;
		FIELD **f = (FIELD **) calloc(3, sizeof(FIELD *));

		move(LINES - 2, 0);
		addstr("plaap\n");
		addstr("plaap");

		win.ft = newwin( LINES/2, COLS, 0, 0);
		win.fb = newwin( LINES/2, COLS, LINES/2, 0);

		intrflush(win.ft, FALSE);
		intrflush(win.fb, FALSE);

		win.pt = new_panel(win.ft);
		win.pb = new_panel(win.fb);

		keypad(win.ft, TRUE);
		keypad(win.fb, TRUE);
		box(win.ft, 0, 0);
		box(win.fb, 0, 0);

		f[0] = new_field(1, COLS, 0, 0, 0, 0);
		set_field_back(f[0], A_REVERSE);
		set_field_buffer(f[0], 0, name);

		f[1] = new_field(6, COLS, 1, 0, 0, 0);
		set_field_buffer(f[1], 0, name);
		set_field_just(f[1], JUSTIFY_LEFT);


		FORM *winform = new_form(f);
		set_form_win( winform, win.ft);
		set_form_win( winform, derwin(win.ft, 20, 20, 1, 11));
		post_form(winform);

		update_panels();

		doupdate();
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		initscr();

		start_color();
		cbreak();
		noecho();

		create_window("poekoe");
		sleep(10);

		endwin();

		return EXIT_SUCCESS;
}
