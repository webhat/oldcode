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
/* Last modified: Sun 22 Dec 2002 02:11:32 GMT
 */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1
 
#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>


int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		printf("%p\n", printf);
		printf("%p\n", dlsym((void*)-1L,"printf"));
		printf("%p\n", malloc);
		printf("%p\n", dlsym((void*)-1L,"malloc"));

		return 0;
}


