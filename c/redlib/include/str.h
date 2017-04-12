
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

/* Last modified: Tue 23 Apr 2002 21:14:20 GMT
 */
/* CVSVERSION: $Id: $ */

#ifndef HAVE_STR_H
# define HAVE_STR_H

# include "default.h"


R_EXTERN char *strupper( char *buf);
R_EXTERN char *strlower( char *buf);
R_EXTERN int strptrlen( const char **buf);

#endif /* HAVE_STR_H */

