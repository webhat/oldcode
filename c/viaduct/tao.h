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

/* CVSVERSION: $Id: tao.h,v 1.1.1.1 2000/07/14 20:22:56 webhat Exp $ */

#ifndef HAVE_TAO_H
#include <config.h>
#include <headers.h>

#ifndef UINT
	#define UINT unsigned int
#endif /* UINT */


#include <socket/t_socket.h>

typedef struct tao_opt {
				volatile int verbose;	/* This can be redefined by any thread. */
				volatile int timeout;
				//enum ser_e { ignore = 0, src, dst, socket = 4 } ser; 
				UINT ser;	/* 0 = ignore, (in/output handled differently)
										 1 = src serial to socket,
										 2 = dst serial from socket,
										 3 = src & dst serial
										 4 = ignore, (file to and from socket)
										 5 = src file and dst serial,
										 6 = src serial and dst file,
										 7 = file to file
									 */
				union com {
								char *file;
								struct {
												THOST *host;	/* src host data */
												TPORT *port;	/* src port data */
								} addr;
				} src, dst;

				// FIXME: This could be unsafe to use. Probably why it isn't used yet.
				volatile int srcfd;
				volatile int dstfd;
} tao_opt;

#define HAVE_TAO_H
#endif /* HAVE_TAO_H */


