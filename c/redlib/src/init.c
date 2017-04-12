/*
 *  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
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

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#include "file.h"
#include "mem.h"
#include "module.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void _init_fds(void);

void _init(void) __ATTRIB(__constructor__);
void _init()
{
				_init_fds();
				_init_module();
				_init_mem();
				_init_file();
}

void _fini(void) __ATTRIB(__destructor__);
void _fini()
{
				_fini_file();
				_fini_mem();
				_fini_module();
}

static void _init_fds()
{
/* XXX:
 * 		Check if the standard filedescriptors are open
 * before opening anything else.
 */
		int fd;
		struct stat st;

		for(fd = 0; fd < 3; fd++)
				if(fstat(fd,&st) == -1
								&& (close(fd), open("/dev/null",O_RDWR)) != fd) {
						printf("Error opening /dev/null: %s\n", strerror(errno));
						return;
				}
}

#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				return 0;
}
#endif /* DEBUG */

