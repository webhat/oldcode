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
/* Last modified: Sat 07 Sep 2002 16:37:54 GMT
 */

/*
#define COLOR_B_WHITE				"\033[1;1m"
#define COLOR_BOLD					"\033[1;4m"
#define COLOR_B_WHITE_DARKGREY	"\033[1;5m"
#define COLOR_B_WHITE_BLACK	"\033[1;6m"
#define COLOR_BLACK					"\033[1;30m"
#define COLOR_RED						"\033[1;31m"
#define COLOR_GREEN					"\033[1;32m"
#define COLOR_YELLOW				"\033[1;33m"
#define COLOR_BLUE					"\033[1;34m"
#define COLOR_PURPLE				"\033[1;35m"
#define COLOR_CYAN					"\033[1;36m"
//#define COLOR_BLUE					"\033[1;37m"
//#define COLOR_BLUE					"\033[1;38m"
#define COLOR_WHITE					"\033[0;39m"
#define COLOR_BOLD_WHITE_RED	"\033[1;40m"
#define COLOR_BOLD_WHITE_GREEN		"\033[1;41m"
#define COLOR_BOLD_WHITE_BROWN		"\033[1;42m"
#define COLOR_BOLD_WHITE_BLUE		"\033[1;43m"
#define COLOR_BOLD_WHITE_PURPLE		"\033[1;44m"
#define COLOR_BOLD_WHITE_CYAN		"\033[1;45m"
#define COLOR_BOLD_WHITE_GREY		"\033[1;46m"
*/

#include <string.h>
#include <stdio.h>

#include "../include/colour.h"

int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				int i, j, x;
				for(i = 30; i < 49; i++) {
								COLOR_RESET;
								if(i%10 == 0) {
												printf("   ");
												for(x = 0; x < 20; x++)
																printf("%2d",x);
												for(x = 21; x < 24; x++)
																printf("%2d",x);
												printf("\n");
								}
								printf("%02d ", i);
								for(j = 0; j < 20; j++) {
												COLOR_RESET;
												printf("\033[%d;%dm",	j,i,j,i);
												printf(" %%");
								}
								COLOR_RESET;
								for(j = 21; j < 24; j++) {
												COLOR_RESET;
												printf("\033[%d;%dm",	j,i,j,i);
												printf(" %%");
								}
								COLOR_RESET;
								printf("\n");
				}
				COLOR_RESET;
				printf("\n");
				return 0;
}

