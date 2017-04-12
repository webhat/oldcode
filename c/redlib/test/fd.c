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
/* Last modified: Sun 19 Jan 2003 19:36:20 GMT
 */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

/* XXX:
 * 		Check if the standard filedescriptors are open
 * before opening anything else.
 */
int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		int fd;
		struct stat st;

		for(fd = 0; fd < 3; fd++)
				if(fstat(fd,&st) == -1
								&& (close(fd), open("/dev/null",O_RDWR)) != fd) {
						printf("Error opening /dev/null: %s\n", strerror(errno));
						return -1;
				}
		return 0;
}
