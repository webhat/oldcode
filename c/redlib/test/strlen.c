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
/* Last modified: Tue 23 Jul 2002 22:47:39 GMT
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				char *len;
				char *len2 = "poekoe";
				//char len[4];
				//char len2[4];

				len = malloc(2);
				strncpy(len, "boelie ", 6);
				strcat(len, "boelie");
				strcat(len, "boelie");
				strcat(len, "boelie");
				strcat(len, "boelie");
				strncpy(len, "blebt", 4);

				//strcat(len2, "poekoeboelie");

				printf("%d: %s\n", strlen(len), len);
				printf("%d: %s\n", strlen(len2), len2);

				return 0;
}


