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
/* Last modified: Fri 19 Apr 2002 17:01:58 GMT
 */
/* $Id: $ */

#ifndef HAVE_ERROR_H
# define HAVE_ERROR_H

# include "default.h"

BEGIN_REDLIB_DECL

# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
# endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

# ifdef __GNUC__
# else /* __GNUC__ */
# endif /* __GNUC__ */

extern void xwrite(const char *out);
extern void xerror(const char *err);
extern char *xread(const char *fmt);

END_REDLIB_DECL

#endif /* HAVE_ERROR_H */
