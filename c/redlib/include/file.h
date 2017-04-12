
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
/* Last modified: Fri 19 Apr 2002 17:02:20 GMT
 */
/* $Id: $ */

#ifndef HAVE_FILE_H
# define HAVE_FILE_H

# include "default.h"

BEGIN_REDLIB_DECL

# include <stdio.h>
# include <stdlib.h>
# include <bzlib.h>
# include <zlib.h>

/* XXX: mem save over ease of use II
 * 		continued from file.c
 * 		Here below the user implementation of
 * MEM_SAVE and NO_MEM_SAVE. The first, as
 * stated above is saving memory by passing
 * a 'pure' pointer around. Which poses only
 * the problem of how to do allocation of
 * memory, which is discussed later.
 * 		The second has an advantage to the
 * first, as far as the programmer knowledge
 * of the type of stream used. However this
 * is also a disadvantage to user based
 * functions, causing the programmer to do
 * a lot of grunt work.
 */

#  define RTYPE_FAIL			-1
#  define RTYPE_DEFAULT		0
#  define RTYPE_PACK			1
#  define RTYPE_GZ				2
#  define RTYPE_FREEZE		3
#  define RTYPE_FREEZE2		4
#  define RTYPE_COMPRESS	5
#  define RTYPE_LZ				6
#  define RTYPE_BZ				7
#  define RTYPE_BZ2				8

# ifdef NO_MEM_SAVE
#  undef MEM_SAVE
typedef struct
{
				int type;
				FILE * file   __ATTRIB(__aligned__);
				gzFile gzip   __ATTRIB(__aligned__);
				BZFILE *bzip  __ATTRIB(__aligned__);
				BZFILE *bzip2 __ATTRIB(__aligned__);
} red_file;
#  define RFILE red_file*
# else /* MEM_SAVE */
#  define MEM_SAVE
#  define RFILE void*
# endif /* NO_MEM_SAVE */

/* XXX: NEW_RFILE(name)
 * 		When deciding whether to use this, it
 * is advised to remember that xcalloc is part
 * of the memory functonality from redlib. The
 * file mem.h MUST be included for this to work.
 */

# ifndef NEW_RFILE
#  define NEW_RFILE(X) RFILE X = xcalloc( 1, sizeof( RFILE))
# else
#  if defined(__GNUC__)
 #warning NEW_RFILE previously defined
#  endif /* defined(__GNUC__) */
# endif /* NEWFILE(X) */

R_EXTERN void _init_file(void);
R_EXTERN void _fini_file(void);

R_EXTERN int get_file_type(void);
R_EXTERN int set_file_type(int);
R_EXTERN int check_file_type( const char *path);
R_EXTERN int check_fd( int fd);

R_EXTERN RFILE ropen(const char *path, const char *mode);
R_EXTERN RFILE rdopen(int fd, const char *mode);
R_EXTERN RFILE rreopen(const char *path, const char *mode, RFILE stream);
R_EXTERN size_t rread(void *ptr, size_t sz, size_t nm, RFILE stream);
R_EXTERN size_t rwrite(void *ptr, size_t sz, size_t nm, RFILE stream);
R_EXTERN int rclose(RFILE);
R_EXTERN int rflush(RFILE);
R_EXTERN int reof(RFILE);

/* TODO:
 * 		I want some crypto options in here,
 * char *rencrypt( char *data, char *key) __ATTRIB(__weak__);
 * char *rdecrypt( char *data, char *key) __ATTRIB(__weak__);
 * and checks if crypto.h has een included. (If so then these
 * shouldn't be prototyped.
 */

END_REDLIB_DECL

#endif /* HAVE_FILE_H */

