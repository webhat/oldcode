
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

/* CVSVERSION: $Id: v_sock.h,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

#ifndef HAVE_V_SOCK_H
#define HAVE_V_SOCK_H
	#include <netdb.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	#define SA struct sockaddr
	#define SAI struct sockaddr_in
	#define IA struct in_addr
	#define BIGSIZ 8192

	#ifndef INADDR_NONE
		#define INADDR_NONE 0xffffffff
	#endif

	#ifdef MAXHOSTNAMELEN
		#undef MAXHOSTNAMELEN
	#endif
	#define MAXHOSTNAMELEN 256

	extern int inet_atontoa( char *in, IA *out);

#endif /* HAVE_V_SOCK_H */
