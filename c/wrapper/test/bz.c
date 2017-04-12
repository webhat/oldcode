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

#include <stdio.h>
#include <stdlib.h>
#include <bzlib.h>
#include <string.h>

int main( int argc, char **argv);

int main( int argc, char **argv)
{
				BZFILE *f = calloc( 1, sizeof( BZFILE *));
				char *buff = malloc( 4096);

				f = BZ2_bzopen( "./tst.bz2", "r9");

				if ( NULL == f) 
				{
								printf( "f empty\n");
				}

#if 0
				buff = gzgets( f, buff, 4095);
#else
				if ( -1 == BZ2_bzread( f, buff, 4095))
				{
								printf( "tst.bz2 empty\n");
				}
#endif

				printf( "read:     ");
				printf( "%s\n", buff);

				BZ2_bzflush( f);
				BZ2_bzclose( f);

				free( buff);
				buff = malloc( 4096);

				f = BZ2_bzopen( "./tst2.bz2", "a+rw9");

				printf( "append:   ");
				fgets( buff, 4095, stdin);

				if( -1 == BZ2_bzwrite( f, buff, strlen( buff)))
				{
								printf( "tst.bz2 failed to write\n");
				}

				printf( "appended: ");
				if ( -1 == BZ2_bzread( f, buff, 4095))
				{
								printf( "tst.bz2 empty\n");
				}

				printf( "%s [%d]", buff, strlen( buff));

				BZ2_bzflush( f);
				BZ2_bzclose( f);

				return 0;
}
