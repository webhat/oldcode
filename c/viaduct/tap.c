/*
    Copyright (C) 1997-2000  Daniel W. Crompton <redhat@rphh.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* CVSVERSION: $Id: tap.c,v 1.1.1.1 2000/07/14 20:12:45 webhat Exp $ */

#include <config.h>
#include <headers.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

extern int debug( int lvl, char* body);

int file( char *name ) {
// FIXME: Add access(2) instead of file(3), as defined in tap.c
//				struct stat *buf = (struct stat *) malloc( sizeof( struct stat));
//				return stat( name, buf);
// FIX:
				return access( name, R_OK|W_OK);
}

int chardev( int fd ) {
				struct stat buf;
				fstat( fd, &buf);
				return S_ISCHR( buf.st_dev);
}

int tap( int fd ) {
				int tap_dev;
				char *file = "";

				sprintf( file, "/dev/tap%d", fd);
				debug( 2, file);
				
				tap_dev = open( file ,O_RDWR);
				debug( 2, "tap open");

				write( tap_dev, "test", 0);

				close( tap_dev);
				return 0;
}




