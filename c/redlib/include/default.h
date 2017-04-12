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
/* Last modified: Wed 27 Nov 2002 22:41:16 GMT
 */
/* $Id: $ */

#ifndef HAVE_DEFAULT_H
# define HAVE_DEFAULT_H

# if defined(REDLIB_SRC)
#  include "config.h"
# endif /* defined(REDLIB_SRC) */

# include <features.h>

# define R_FUNC(func) (func)

# ifdef __GNUC__
#  define __ATTRIB(X) __attribute__ ((X))
# else
#  define __ATTRIB(X) ()
# endif /* __GNUC__ */
# ifndef R_EXTERN
#  define R_EXTERN extern
# endif /* R_EXTERN */

# ifdef __cplusplus
#  define BEGIN_REDLIB_DECL extern "C" {
#  define END_REDLIB_DECL }
#  if defined(__GNUG__)
#  endif /* defined(__GNUG__) */
# else
#  define BEGIN_REDLIB_DECL
#  define END_REDLIB_DECL
# endif /* __cplusplus */

# define FREE(x) if(x) { free((x)); x = NULL; }

# ifndef _REENTRANT /* consolidate various implied forms of _REENTRANT */
#  if defined(_THREAD_SAFE) || defined(THREAD_SAFE) || \
      defined(REENTRANT) || defined(_POSIX_THREAD_SAFE_FUNCTIONS) || \
      defined(_MIT_POSIX_THREADS)
#   define _REENTRANT
#  endif
# endif

/* prepopulate locale */
# ifndef LOCALEDIR
#  define LOCALEDIR "."
# endif /* LOCALEDIR */

# ifndef PACKAGE
#  define PACKAGE "redlib"
# endif /* PACKAGE */

#endif /* HAVE_DEFAULT_H */

