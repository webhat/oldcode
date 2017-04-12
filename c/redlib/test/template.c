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

/* XXX: how to write a module
 *
 * 		The code as seen below can be easily modified for your own
 * module. It is for you to decide how you want to use the first
 * agrument to the function.
 * 		For a network module one could use a struct containing
 * ip address, port number, socket fd etc. Or even, as viaduct(1)
 * does, pass argc and argv in a struct so the arguments can be
 * parsed from the command line. Although this would be dangerous
 * if your program is setuid or setgid and allows users to load
 * their own modules.
 * 		the second argument is the possition the module has been
 * loaded in the list. This will allow for slightly less strict
 * programming, in most cases code doesn't need to be reentrant.
 *
 * Now you can compile with:
 *
 * 		gcc -Wall -shared -o template.o template.c
 *
 * 		If you are using _init or _fini then it is advised to
 * compile without -nostdlib, or it won't work:
 *
 * 		gcc -Wall -shared -nostdlib -o template.o template.c
 */

#include <stdio.h>

/* prototypes */
int     open( void *, int );
int     close( void *, int );
int     read( void *, int );
int     write( void *, int );
int     cmp( void *, int );
int     help( void *, int );
int     func9( void *, int );		/* example extra function, may become
																 * obsolete.
																 */

void _init()
{
				printf("_init\n");
}

void _fini()
{
				printf("_fini\n");
}

/* functions */
int open( in, num )
	void   *in;
	int num;
{
				printf( "called open from template\n" );
				return 0;
}

int close( in, num )
	void   *in;
	int num;
{
				printf( "called close from template\n" );
				return 0;
}

int read( in, num )
	void   *in;
	int num;
{
				printf( "called read from template\n" );
				return 0;
}

int write( in, num )
	void   *in;
	int num;
{
				printf( "called write from template\n" );
				return 0;
}

int cmp( in, num )
	void   *in;
	int num;
{
				printf( "called cmp from template\n" );
				return 0;
}

int help( in, num )
	void   *in;
	int num;
{
				printf( "called help from template\n" );
				return 0;
}

/* example extra function, may become obsolete */
int func9( in, num )
	void   *in;
	int num;
{
				printf( "called func9 from template\n" );
				return 0;
}
