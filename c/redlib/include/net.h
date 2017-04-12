/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *  This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/* CVSVERSION: $Id: $ */
/* Last modified: Tue 28 Jan 2003 22:33:20 GMT
 */

#ifndef HAVE_NET_H
# define HAVE_NET_H

# include "default.h"

typedef struct sockaddr			SA;
typedef struct sockaddr_in	SAI;
typedef struct in_addr			IA;

# if !defined(INADDR_NONE)
#  define INADDR_NONE 0xffffffff
# endif /* !defined(INADDR_NONE) */

# if defined(MAXHOSTNAMELEN)
#  undef MAXHOSTNAMELEN
# endif /* defined(MAXHOSTNAMELEN) */
# define MAXHOSTNAMELEN 256
# define MAXPORT 65536

# if !defined(SO_REUSEPORT)
#  define SO_REUSEPORT 15
# endif /* !defined(SO_REUSEPORT) */

#if defined(REDLIB_SRC)
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
#endif /* defined(REDLIB_SRC) */


typedef struct {
				char		prot[16];
				char		host[MAXHOSTNAMELEN+1];
				unsigned short	port;
				char		path[(MAXHOSTNAMELEN*4)+1];
				char		attr[(MAXHOSTNAMELEN*4)+1];
				char		user[(MAXHOSTNAMELEN*4)+1];
				char		pass[(MAXHOSTNAMELEN*4)+1];
} url_s;

typedef struct {
				SAI sai									__ATTRIB(__aligned__);
				IA ia										__ATTRIB(__aligned__);
				char hostname[MAXHOSTNAMELEN+1];
				char portname[MAXHOSTNAMELEN+1];
				int sock;
} serv;

typedef union
{
				const char *c;
				int i;
} __ATTRIB(__transparent_union__) portnum;

/* PARSE FUNCTIONS */
R_EXTERN url_s	*rurl( const char *);

/* NETWORK FUNCIONS */
/* udp */
R_EXTERN serv		*rbind_u( const char *, unsigned int);
R_EXTERN serv		*rconnect_u( const char *, unsigned int);

/* tcp */
R_EXTERN serv		*rbind( const char *, unsigned int);
R_EXTERN serv		*rconnect( const char *, unsigned int);
R_EXTERN int		rin2out( serv *, serv *, size_t);

/* RESOLV FUNCTIONS */
R_EXTERN serv		*rgetby( const char *);
R_EXTERN serv		*rgetbyp( portnum);

/* CONTROL FUNCTIONS */
R_EXTERN int		rbuf2stdout( int);
R_EXTERN int		rbuf2stderr( int);

#endif /* HAVE_NET_H */


