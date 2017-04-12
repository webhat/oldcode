/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

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
/* Last modified: Thu 28 Nov 2002 00:07:40 GMT
 */

/* run with: xgettext -o l18n.pot -k_ -kN_ l18n.c */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(str)						gettext(str)
#define gettext_nop(str)	(str)
#define N_(str)						gettext_nop(str)

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		int i, length, counter = 0;
		char *mess, line[11], *info[] = {
		N_("digit"), N_("digits")};

		setlocale(LC_ALL, "");
		bindtextdomain("l18n", ".");
		textdomain("l18n");

		printf(_("Please type in a line\n"));
		fgets(line, 11, stdin);
		length = strlen(line);
		for(i = 0; i < length; i++)
				counter += isdigit(line[i])?1:0;
		mess = counter > 1?info[1]:info[0];
		printf(_("You typed %d %s\n"),
						counter, _(mess));
		exit(0);
}

