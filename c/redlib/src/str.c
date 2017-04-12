
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
/* Last modified: Tue 23 Apr 2002 21:20:07 GMT
 */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define R_EXTERN
#include "str.h"


char *strupper( buf)
				char *buf;
{
				int i;
				char *tmpbuf = calloc( 1, strlen( buf) + 1);

				for( i = 0; i < strlen(buf) ; i++ )
								if( islower(buf[i]))
												tmpbuf[i] = toupper( buf[i]);
								else
												tmpbuf[i] = buf[i];

				return tmpbuf;
}


char *strlower( buf)
				char *buf;
{
				int i;
				char *tmpbuf = calloc( 1, strlen( buf) + 1);

				for( i = 0; i < strlen(buf) ; i++ )
								if( isupper(buf[i]))
												tmpbuf[i] = tolower( buf[i]);
								else
												tmpbuf[i] = buf[i];

				return tmpbuf;
}

int strptrlen( buf)
				const char **buf;
{
				int i;

				for( i = 0; buf[i][0] != '\0' || buf[i][0] != (char)NULL; i++);

				return (i);
}
