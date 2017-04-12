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

/* CVSVERSION: $Id: getby.c,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

/***********************************************************
 * This file defines all the getby functions:
 * 
 * the getby() functions return a TAO struct containing
 * either address or port bindings.
 ***********************************************************/

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

int inet_atontoa( char *in, IA *out) {

				if( inet_aton( in, out)) {
								/* TODO: create a check whether this is a hostname or not */
								debug( 1, "ERROR inet_aton()");
								return 0;
				}

				if( !strcmp( in, inet_ntoa( *out))) {
								debug( 1, "PASSED");
								return 1;
				}

				debug( 1, "ERROR passed through");
				return 0;
}

THOST *getbyname( char *name, USHORT num) {
				struct hostent *hosten;
				IA *addrs;
				THOST *rtao;

				if( inet_aton( name, (IA *) &addrs)) {
								debug( 9, (char *) &addrs);
								hosten = gethostbyaddr( (char *) &addrs, sizeof( addrs), AF_INET);
								//strncpy( rtao->name, hosten->h_name, MAXHOSTNAMELEN -2);
								debug( 9, rtao->name);
								//debug( 9, &hosten->h_name);
								debug( 10, "inet_aton true");
				} else {
								hosten = gethostbyname( (char *) &name);
								debug( 9, rtao->name);
								//debug( 9, &hosten->h_name);
								debug( 10, "inet_aton false");
				}
				if( !hosten) broke( "Host lookup failed!");

				debug( 9, "Anything happen?");
				return ( rtao);
}


/*
extern int herrno;

THOST *getbyname ( char *name, USHORT num) {
				struct hostent * hostend;
				THOST *host;
				IA addr;

				errno = 0;
				h_errno = 0;
				addr.s_addr = inet_addr( name);

				//host = (THOST *) malloc( sizeof( THOST));

				if( addr.s_addr == INADDR_NONE) {
								if( num) broke( "Eh? It's an address, not an IP number"); 
								hostend = gethostbyname( name);
								//strncpy( host->name, hostend->h_name, MAXHOSTNAMELEN - 2);
								//debug(1, host->name);
				} else {
								strncpy( host->addrs[0], inet_ntoa( addr), sizeof( host->addrs));
								if( num) return ( host);
								hostend = gethostbyaddr((char *) name, sizeof( IA), AF_INET);
								//if( hostend)
									//							strncpy( host->name, hostend->h_name, MAXHOSTNAMELEN - 2);
								//debug(1, host->name);
				}

				return ( host);
}
*/

