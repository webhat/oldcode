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

/* CVSVERSION: $Id: bind.c,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

#include <config.h>
#include <headers.h>

#ifndef HAVE_TAO_SOCKET_H
	#include <socket/t_socket.h>
#define HAVE_TAO_SOCKET_H
#endif /* HAVE_TAO_SOCKET_H */

#ifndef HAVE_V_SOCK_H
  #include <socket/v_sock.h>
  #define HAVE_V_SOCK_H
#endif /* HAVE_V_SOCK_H */

#include <string.h>

//FIXME: A function should be written to support function overloading
//	for the functions defined below.
//	This function accepts a tao_c
//	void tbind( tao_c *in);

USHORT bind_on_interface( USHORT prt, UCHAR *src) {
				TPORT tport;
				THOST thost;
				int i;
				SAI serv;
				USHORT sock, sockfd;
				size_t sz = sizeof( struct sockaddr_in);

				bzero( &serv, sizeof( SAI));
				bzero( &thost, sizeof( thost));
				bzero( &tport, sizeof( tport));

				if(( sock = socket( PF_INET, SOCK_STREAM, 0)) < 0)
								broke("no socket");
				debug( 9, "socket");

				setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

				serv.sin_family = AF_INET;
				serv.sin_port = htons( prt);
				tport.num = htons( prt);
				strncpy( thost.name, src, sizeof( src));
				inet_atontoa( thost.name, thost.iaddrs);

//				memcpy(&serv.sin_addr, &thost.iaddrs, sizeof( thost.iaddrs));
				memset(&serv.sin_addr, 0, sizeof( serv.sin_addr));

				if( bind( sock, (struct sockaddr *) &serv, sizeof( serv)))
								broke("no bind");
				debug( 9, "bind");

				if( listen( sock, 2))
								broke("no listen");
				debug( 9, "listen");

				while((sockfd = accept( (int) sock, (struct sockaddr *) &serv, &sz)) >= 0){
								debug(1, "accept");
								return (USHORT) sockfd;
				}

				return (USHORT) sockfd;
}

USHORT bind_on_port( UINT prt, void *src) {
				//FIXME: This function should contain source to bind to a port.
				return (USHORT) prt;
}

USHORT bind_on_device( UCHAR *src) {
				return (USHORT) 0;
}
