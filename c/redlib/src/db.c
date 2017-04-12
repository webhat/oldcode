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
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
 #warning redhat: empty source file
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#include <lber.h>
#include <ldap.h>

#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

