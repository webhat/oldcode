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

/* don't forget to compile with -lbsd-compat*/
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

/* #define _REENTRANT */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define R_EXTERN /* */
#include "mem.h"

/* TODO:
 *		Look up the signal thingies to set and
 * unset mtrace() (c/doc/libc.ps)
 */

/* TODO:
 * 		Implement optional lazyfits.
 * (c/doc/lazy-fits.ps)
 *
 * XXX:
 * 		Reserve allocation pointer and
 * boundary pointer in global registers
 * to speed up allocation.
 *
 * |1111|0000|0000|0000|0000|1111|0000|0000|
 *      ^                   ^
 *      alloc ptr           bound ptr
 * 		Look at obstack in gcc compiler.
 */

static char *mmessage;

/* to be called from _init */
void _init_mem()
{
				mmessage = calloc( 1, 6);
				if( mmessage == NULL)
				{
								fprintf( stderr, "Error: %s", strerror(errno));
								exit(-1);
				}

				strncat( mmessage, "Error", 5);
}

void set_mmessage( message)
				const char *message;
{
				mmessage = realloc( mmessage, strlen( message));
				if( mmessage == NULL)
				{
								fprintf( stderr, "Error: %s", strerror(errno));
								exit(-1);
				}

				strncpy( mmessage, message, strlen( message));
}

void unset_mmessage()
{
				mmessage = realloc( mmessage, 6);
				if( mmessage == NULL)
				{
								fprintf( stderr, "Error: %s", strerror(errno));
								exit(-1);
				}

				strncat( mmessage, "Error", 5);
}

/* to be called from _fini */
void _fini_mem()
{
				free( mmessage);
}

/* calloc */
void *xcalloc( nmemb, size)
				size_t nmemb;
				size_t size;
{
				register void *out = calloc( nmemb, size);

				if( out == NULL)
				{
								fprintf( stderr, "%s: %s", mmessage, strerror( errno));
								exit(-1);
				}
				return out;
}

/* malloc */
void *xmalloc( size)
				size_t size;
{
				register void *out = malloc( size);

				if( out == NULL)
				{
								fprintf( stderr, "%s: %s", mmessage, strerror( errno));
								exit(-1);
				}
				return out;
}

/* realloc */
void *xrealloc( ptr, size)
				void *ptr;
				size_t size;
{
				register void *out = realloc( ptr, size);

				if( out == NULL)
				{
								fprintf( stderr, "%s: %s", mmessage, strerror( errno));
								exit(-1);
				}
				return out;
}

/* free */
#undef xfree
void xfree( ptr)
				void *ptr;
{
				free( ptr);
}

