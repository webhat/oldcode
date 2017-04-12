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
/* $Id: crossfun.c,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

/*
 * This file defines al the cross writing functions. This after
 * something Peter Zijlstra suggested; glueing fd's together for
 * the basic functionallity.
 *
 * WARNING:
 *
 * The functins defined in here are the source functions that
 * most other functions rely on for the writing and reading from
 * one interface or device to another.
 * If you really feel the need to edit here, then use the TRACK
 * define to see what is actually going on in here, as there is
 * some juju-magic in here.
 */

#include <config.h>
#include <headers.h>

#ifndef HAVE_CROSS_H
  #include <cross/cross.h>
  #define HAVE_CROSS_H
#endif /* HAVE_CROSS_H */

/*
 * This function plugs the src fd into the dest fd
 */

void src2dest( int src, int dest ) {
				int res = 0;
				char CR_buf[1];

				while(( res = read( src, CR_buf, 1)) > 0) {
#ifdef TRACK
								debug( 9, CR_buf);
#endif /* TRACK */
								write( dest, CR_buf, res);
								bzero( &CR_buf, 1);
				}

				pthread_exit( NULL );
}

/*
 * WARNING: DON'T TOUCH!!!!!!
 *
 * This function plugs into the linux kernel viaduct module.
 * If you think you want to add code to this, please be
 * carefull, this can give you more problems than you think.
 * This due to the fact that you are messing with the device
 * /dev/viaduct*
 */

int attach( int dev ) {
				return 0;
}


