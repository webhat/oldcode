/*  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
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
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#define R_EXTERN
#include "net.h"
#include "str.h"

#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* #include <sys/types.h>  */
/* #include <sys/socket.h> */
/* #include <netinet/in.h> */
/* #include <arpa/inet.h>  */

#if defined(DEBUG)
# define bail(X) exit(X)
#else /* defined(DEBUG) */
# define bail(X) return NULL
#endif /* defined(DEBUG) */

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

static int r_bufferout;
static __inline__ serv *rconnect_d( const char *host,
												unsigned int port,
												unsigned int prot);
static __inline__ serv *rbind_d( const char *host,
												unsigned int port,
												unsigned int prot);

url_s *rurl( url)
				const char *url;
{
				url_s *line = calloc( 1, sizeof( url_s)+1);
				char *ptr, *bot, *prt;
				int i;

				if( line == NULL)
				{
								fprintf( stderr, "Error: `%s'\n", strerror( errno));
								exit(-1);
				}

				ptr = strstr( url, ":");

#ifdef DEBUG
				fprintf( stderr, "url: `%s'\n", url);
#endif /* DEBUG */

				if( 16 < (ptr-url))
				{
								fprintf( stderr, "Error: protocol name exceeds standaard\n");
								return NULL;
				}

				strncat( line->prot, url, (ptr-url));
				for(i = 0; i < strlen(line->prot); i++)
								if(isupper(line->prot[i]))
												line->prot[i] = tolower(line->prot[i]);

#ifdef DEBUG
				fprintf( stderr, "prot `%s' len: %d\n", line->prot, (ptr-url));
#endif /* DEBUG */

				bot = (char *) ptr;

				bot++;
				bot++;
				bot++;

				if((bot-url) >= strlen(url)) return NULL;

				/* username & password `plaap:poekoe@' */
				if((ptr = strstr(bot, "@")) != NULL)
				{
								char *userpass = calloc(1,(ptr-bot)+1);
								if(userpass == NULL)
								{
												fprintf( stderr, "Error: `%s'\n", strerror( errno));
												exit(-1);
								}
								strncat(userpass, bot, ptr-bot);

								if((prt = strstr(userpass, ":")) != NULL)
								{
												prt++;
												strncat( line->pass, prt, (userpass-prt));
												prt--;
								}
								strncat( line->user, userpass, (prt-userpass));

#ifdef DEBUG
								fprintf( stderr, "user `%s' len: %d\n", line->user, (prt-userpass));
								fprintf( stderr, "pass `%s' len: %d\n", line->pass, strlen(line->pass));
#endif /* DEBUG */
								bot = (char*)(++ptr);
								FREE(userpass);
				}

				ptr = (char*) strstr( bot, "/"); /* host and port */

				if((prt = (char*) strstr( bot, ":")) == NULL) /* port */
				{
								struct servent *s = getservbyname( line->prot, NULL);
								strncat( line->host, bot, ((ptr-bot)<MAXHOSTNAMELEN*4)?(ptr-bot):(MAXHOSTNAMELEN*4));
								/*
								line->port = ntohs((*getservbyname( line->prot, NULL)).s_port);
								*/
								if(s != NULL)
												line->port = (unsigned short) ntohs(s->s_port);
								else
												line->port = (unsigned short) 0;
#ifdef DEBUG
								fprintf( stderr, "host `%s' len: %d\n", line->host, (ptr-bot));
								fprintf( stderr, "port `%d' len: 0\n", line->port);
#endif /* DEBUG */
				}
				else
				{
								strncat( line->host, bot, ((ptr-bot)<MAXHOSTNAMELEN*4)?(ptr-bot):(MAXHOSTNAMELEN*4));
								prt++;
								line->port = (unsigned short) atoi( prt);
#ifdef DEBUG
								fprintf( stderr, "host `%s' len: %d\n", line->host, (prt-bot));
								fprintf( stderr, "port `%d' len: %d\n", line->port, (ptr-prt));
#endif /* DEBUG */
				}

				if(ptr == NULL)
								return line;

				bot = (char *) ptr;

				memset(line->path, 0x00, (MAXHOSTNAMELEN*4)+1);

				ptr = strstr( bot, "?");
				strncat( line->path, bot, ((ptr-bot)<MAXHOSTNAMELEN*4)?(ptr-bot):(MAXHOSTNAMELEN*4));

#ifdef DEBUG
				fprintf( stderr, "path `%s' len: %d\n", line->path, (ptr-bot));
#endif /* DEBUG */

				if( ptr == NULL)
								return line;

				ptr++;
				memset(line->attr, 0x00, (MAXHOSTNAMELEN*4)+1);
				strncat( line->attr, ptr, (strlen(ptr)<MAXHOSTNAMELEN*4)?strlen(ptr):(MAXHOSTNAMELEN*4));

#ifdef DEBUG
				fprintf( stderr, "attr `%s' len: %d\n", line->attr, strlen(ptr));
#endif /* DEBUG */

				if( ptr == NULL)
								return line;
				/* TODO:
				 * 	#anchor
				 */

				return line;
}

static serv *rbind_d( host, port, prot)
				const char *host;
				unsigned int port;
				unsigned int prot;
{
				int i = 1;
				serv *sv, sv_by;

				sv = calloc( 1, sizeof( serv)+1);

				if( sv == NULL)
				{
								fprintf( stderr, "Error: `%s'\n", strerror( errno));
								exit(-1);
				}

				if( (sv->sock = socket( PF_INET, SOCK_STREAM, prot)) < 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}

				if( setsockopt( sv->sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof( i)) != 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}

#if 0
				if( setsockopt( sv->sock, SOL_SOCKET, SO_REUSEPORT, &i, sizeof( i)) != 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}
#endif /* 0 */

				/* sv->ia = rgetby( host)->ia; */
				if( host == NULL)
								memset( &(sv->sai.sin_addr), 0x00, sizeof( sv->sai.sin_addr));
				else
				{
								sv_by = *rgetby( host);
								memcpy( &sv->ia, &sv_by.ia, sizeof( sv_by.ia));
								memcpy( &(sv->sai.sin_addr), &(sv->ia), sizeof( sv->ia));
				}

				fprintf( stderr, "host:   `%s'\n", host);
				fprintf( stderr, "ip:     `%s'\n", inet_ntoa(sv->sai.sin_addr));

				sv->sai.sin_family = AF_INET;
				sv->sai.sin_port = htons( port);

				if( bind( sv->sock, (SA *) &sv->sai, sizeof(sv->sai)))
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}  

				if( listen( sv->sock, 2))
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}

				return sv;
}

static serv *rconnect_d( host, port, prot)
				const char *host;
				unsigned int port;
				unsigned int prot;
{
				serv *sv;
				int i = 1;

				sv = calloc( 1, sizeof( serv)+1);

				if( sv == NULL)
				{
								fprintf( stderr, "Error: `%s'\n", strerror( errno));
								exit(-1);
				}

				if( host == NULL)
								memset( &(sv->sai.sin_addr), 0x00, sizeof( sv->sai.sin_addr));
				else
				{
								sv = rgetby( host);
								memcpy( &(sv->sai.sin_addr), &(sv->ia), sizeof( sv->ia));
				}

				if( (sv->sock = socket( PF_INET, SOCK_STREAM, prot)) < 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}

				if( setsockopt( sv->sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof( i)) != 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}

#if 0
				if( setsockopt( sv->sock, SOL_SOCKET, SO_REUSEPORT, &i, sizeof( i)) != 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}
#endif /* 0 */

				sv->sai.sin_family = AF_INET;
				sv->sai.sin_port = htons( port);

				if( (connect( sv->sock, (SA *) &sv->sai , sizeof( SA))) < 0)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								bail(-1);
				}  

				return sv;
}

serv *rbind_u( host, port)
				const char *host;
				unsigned int port;
{
				return rbind_d( host, port, IPPROTO_UDP);
}

serv *rconnect_u( host, port)
				const char *host;
				unsigned int port;
{
				return rconnect_d( host, port, IPPROTO_UDP);
}

serv *rbind( host, port)
				const char *host;
				unsigned int port;
{
				return rbind_d( host, port, IPPROTO_TCP);
}

serv *rconnect( host, port)
				const char *host;
				unsigned int port;
{
				return rconnect_d( host, port, IPPROTO_TCP);
}

int	rin2out( in, out, sz)
				serv *in;
				serv *out;
				size_t sz;
{
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
				char buf[sz+1];
#else /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
				char *buf = malloc( sz);
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

				if( (size_t)0 == sz) return -1;

				memset( buf, 0x00, sz+1);

				while( read( in->sock, buf, sz) > 0)
				{
								write( out->sock, buf, sz);
								switch( r_bufferout)
								{
												case '1':
																fprintf( stdout, "%s", buf);
																break;
												case '2':
																fprintf( stderr, "%s", buf);
																break;
								}      
								memset( buf, 0x00, sz+1);
				}     

				return -1;
}

serv *rgetby( name)
				const char *name;
{
				struct hostent host;
				serv *sv;

				sv = calloc( 1, sizeof( serv)+1);

				if( sv == NULL)
				{
								fprintf( stderr, "Error: `%s'\n", strerror( errno));
								exit(-1);
				}

				memset( sv, 0x00, sizeof(serv));

				if( inet_aton( name, (IA *) &(sv->ia)))
				{
								/* FIXME: dumps here if not in /etc/hosts with no DNS */
								host = *gethostbyaddr( (char *) &(sv->ia), sizeof(sv->ia), AF_INET);

								strncpy( sv->hostname, host.h_name, MAXHOSTNAMELEN);
#ifdef DEBUG
								fprintf( stderr, "byaddr: `%s'\n", host.h_name);
#endif /* DEBUG */
				}
				else
				{
								host = *gethostbyname( name);

								strncpy(sv->hostname, name, MAXHOSTNAMELEN);
								memcpy( &sv->ia, host.h_addr_list[0], sizeof(host.h_addr_list[0]));
#ifdef DEBUG
								fprintf( stderr, "byname: `%s'\n", host.h_name);
#endif /* DEBUG */
				}

				return sv;
}

serv *rgetbyp( port)
				portnum port;
{
				struct servent serve;
				serv *sv;

				sv = calloc( 1, sizeof( serv)+1);

				if( sv == NULL)
				{
								fprintf( stderr, "Error: `%s'\n", strerror( errno));
								exit(-1);
				}

				if( port.i < 0 || port.i > MAXPORT)
				{
								serve = *getservbyname( port.c, NULL);
								strncpy( sv->portname, serve.s_name, MAXHOSTNAMELEN);
								fprintf( stderr, "byname: `%s' `%d'\n", sv->portname, ntohs(serve.s_port));
				}
				else
				{
								serve = *getservbyport( htons(port.i), NULL);
								strncpy( sv->portname, serve.s_name, MAXHOSTNAMELEN);
								fprintf( stderr, "byport: `%s' `%d'\n", sv->portname, ntohs(serve.s_port));
				}

				return sv;
}

int rbuf2stderr( x)
				int x;
{
				if( x)
								return(r_bufferout = 2);
				else
								return(r_bufferout = 0);
}

int rbuf2stdout( x)
				int x;
{
				if( x)
								return(r_bufferout = 1);
				else
								return(r_bufferout = 0);
}

#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				serv sv __ATTRIB(__unused__), sv2 __ATTRIB(__unused__);
				unsigned short fd __ATTRIB(__unused__);
				unsigned int sz __ATTRIB(__unused__) = sizeof( SAI);

				if(argc < 2 ) {
								rurl("ldap://plaperdie:10/p???uid=poekoe,userpassword=plaap");
								rurl("http://localhost/?user=poekoe&pass=plaap");
								rurl("pop3://poekoe:plaap@remotehost/");
				} else {
								rurl(argv[1]);
				}

# if 1
				sv = *rbind( NULL, (unsigned short)1025);
				rgetby( "127.0.0.1");
				rgetby( "localhost");
				rgetbyp( 80);
				rgetbyp( "http");

				sv2 = *rconnect( "localhost", 1025);
				write( sv2.sock, "test message", 12);
				write( sv2.sock, "test message", 12);

				while( (fd = accept( sv.sock, (SA *) &sv.sai, &sz)))
								if( !fork())
								{
												char buf[2];

												bzero( buf, 2);

												while( read( fd, buf, 1))
												{
#  if (DEBUG==0)
																fprintf( stderr, "read[%d]: `%s'\n", fd, buf);
#  else /* (DEBUG!=0) */
																fprintf( stderr, "%s", buf);
#  endif /* (DEBUG==0) */
																memset( buf, 0x00, 2);
												}
												close( fd);
								}
				//				else break;

				close( sv2.sock);
# endif /* 0 */

				return 0;
}
#endif /* DEBUG */

