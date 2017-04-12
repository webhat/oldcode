/*
 *  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
/* $Id: $ */

/* #define DEBUG */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void xwrite( out)
				const char *out;
{
				fprintf( stdout, "%s\n", out);
}

void xerror( err)
				const char *err;
{
				fprintf( stderr, "Error: %s\n", err);
}

char *xread( fmt)
				const char *fmt;
{
				char *buf = calloc( 1, 4097);
				char *out = calloc( 1, 4097);
				int i;

				/* TODO: xread
				 * 		This should be implementation
				 * dependant, if a user wishes to use readline
				 * or even gets or fscanf should be possible.
				 * However the default should be fgetc(stdin)
				 * with a '\0' at 4097.
				 */

				for( i = 0; i < 4096 ; i++ )
				{
								buf[i] = fgetc( stdin);
								if( buf[i] == EOF || buf[i] == '\n')
												break;
				}

				buf[i] = '\0';

				sscanf( buf, fmt, out);

				return out;
}

#ifdef DEBUG
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				xwrite( "out");
				xerror( "err");
				printf( "xread: %s\n", xread( "%s\n"));
				return 0;
}
#endif /* DEBUG */

