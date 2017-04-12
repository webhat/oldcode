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
/* Last modified: Tue 25 Jun 2002 22:40:43 GMT
 */

//#include "zwerg.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <termios.h>

#define error(X)	fprintf( stderr, "Error: %s\n", X);


int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				int fd;
				char c = 0;
				size_t sz;
				char *buf = calloc(1,2048);
				struct termios *term	= calloc(1, sizeof(struct termios));

				if( (fd = open("/dev/ttyS1", O_NOCTTY|O_RDWR)) < 0)
				{
								error("unable to open `/dev/ttyS1'");
								exit(-1);
				}  

				tcgetattr( fd, term);

				printf("read:\n");
				while( (sz = read( fd, buf, 1)) < 0)
								printf("%s", buf);
				printf(":%i\n", sz);

				printf("write:\n");
				while( (sz = write( fd, &c, 1)) != -1) {
								printf("%c", c);
								if( read( fd, buf, 1) != -1)
												printf("%s", buf);
				}
				printf(":%c", c);
				printf(":%i\n", sz);

				close(fd);

				return 0;
}


