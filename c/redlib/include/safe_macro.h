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
/* Last modified: Fri 17 May 2002 01:57:55 GMT
 */

#ifndef HAVE_SAFE_MACRO_H
# define HAVE_SAFE_MACRO_H

# ifdef DO_VA_LIST
#  define __DO_VA_LIST
# endif /* DO_VA_LIST */

# ifdef DO_SYSLOG
#  define __DO_SYSLOG
# endif /* DO_SYSLOG */

# include <string.h>

# ifdef __DO_SYSLOG
#  undef __DO_SYSLOG

#  include <sys/types.h>
#  include <unistd.h>
#  include <syslog.h>

#  define error(X) syslog( LOG_WARNING, X "pid(%d) by(%d)", getpid(), getuid())

# else

#  include <stdio.h>
#  include <sys/types.h>
#  include <unistd.h>

#  define error(X) fprintf( stderr, X "pid(%d) by(%d)", getpid(), getuid())

# endif /* __DO_SYSLOG */

# define ERROR_MESSAGE	"Warning: possible buffer overflow!!!!"

# define strcpy(X,Y)		if(strlen(X) >= strlen(Y)) { strncpy(X,Y,strlen(Y)); } \
												else { error( ERROR_MESSAGE); strncpy(X,Y,strlen(Y)); }

# define strcpy(X,Y)		if(strlen(X) >= strlen(Y)) { strncat(X,Y,strlen(Y)); } \
												else { error( ERROR_MESSAGE); strncat(X,Y,strlen(Y)); }

# define gets(X)				fgets(X,strlen(X),stdin); error( ERROR_MESSAGE)

/* Unpatched warning only */
# ifdef __DO_VA_LIST
#  undef __DO_VA_LIST
#  define fscanf					error( ERROR_MESSAGE); fscanf
#  define sscanf					error( ERROR_MESSAGE); sscanf

/* XXX: below could be vsnprintf's*/
#  define sprintf					error( ERROR_MESSAGE); sprintf
#  define vsprintf				error( ERROR_MESSAGE); vsprintf
# endif /* __DO_VA_LIST */

# define index(X,Y)			index(X,Y); error( ERROR_MESSAGE)
# define rindex(X,Y)		rindex(X,Y); error( ERROR_MESSAGE)
# define realpath(X,Y)	realpath(X,Y); error( ERROR_MESSAGE) 
# define getopt(X,Y,Z)	getopt(X,Y,Z); error( ERROR_MESSAGE) 
# define getpass(X)			getpass(X); error( ERROR_MESSAGE) 

/* TODO:
 * 		The following don't add \0 to the end
 * if src is larger than dest:
 *
 * 		fread
 * 		read
 * 		readv
 * 		pread
 * 		memcpy
 * 		memmove
 * 		bcopy
 * 		gethostname
 * 		strncat
 * 		strncpy
 */

#endif /* HAVE_SAFE_MACRO_H */


