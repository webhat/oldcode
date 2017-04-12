/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *   This program is free software; you can redistribute it and/or modify
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
/* Last modified: Wed 09 Apr 2003 14:19:16 GMT
 */

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <redlib/net.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		serv sv, sv2;
		unsigned short fd;
		unsigned int sz = sizeof(SAI);
		int retval, bigs;
		struct timeval tv;
		fd_set rfds;

		memset(&sv,0x00,sizeof(serv));
		memset(&sv2,0x00,sizeof(serv));
		memset(&tv,0x00,sizeof(struct timeval));

		sv	= *rbind(NULL,8080);

		while((fd = accept(sv.sock, (SA*)&sv.sai, &sz)))
		{
				if(fork())
				{
						sv2	= *rconnect("169.254.66.182",6588);

						do {
								FD_ZERO(&rfds);
								FD_SET(fd, &rfds);
								FD_SET(sv2.sock, &rfds);
								bigs = fd>sv2.sock?fd:sv2.sock;
								bigs++;

								//fprintf(stderr,"%d?%d:%d\n",bigs,fd,sv2.sock);

								fcntl(fd,F_SETFL,O_NONBLOCK);
								fcntl(sv2.sock,F_SETFL,O_NONBLOCK);

								tv.tv_sec = 5;
								tv.tv_usec = 0;

								/*
								while(!(retval = select(bigs, &rfds, NULL, NULL,&tv))) {
										tv.tv_sec = 5;
										tv.tv_usec = 0;
										//fprintf(stderr,"s(%d)\n",tv.tv_sec);
								}
								*/

								/*
								if(retval < 0)
								{
										//fprintf(stderr,"Error: %s\n",strerror(errno));
										exit(1);
								}
								*/

								//if(FD_ISSET(fd, &rfds))
								{
										char buf[2];
										//fprintf(stderr,"sv  R\n");
										memset(buf, 0x00, 2);
										while(read(fd,buf,1) > 0)
										{
												write(sv2.sock,buf,1);
												printf("%s",buf);
												memset(buf, 0x00, 2);
										}
								}

								//if(FD_ISSET(sv2.sock, &rfds))
								{
										char buf[2];
										//fprintf(stderr,"sv2 R\n");
										memset(buf, 0x00, 2);
										while(read(sv2.sock,buf,1) > 0)
										{
												write(fd,buf,1);
												printf("%s",buf);
												memset(buf, 0x00, 2);
										}
								}
								//fprintf(stderr,"cont\n");
						} while(1);

						break;
				}
				break; /* FIXME:one connection */
		}     
		return 0;

}
