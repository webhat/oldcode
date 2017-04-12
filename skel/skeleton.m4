##  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
##
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation; either version 2 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##
##  $Id: $
##  Last modified: 

dnl AM_PROG_REPLACETHIS
dnl Looking for replacethisname
AC_DEFUN(AM_PROG_REPLACETHIS,
[missing_dir=ifelse([$1],,`cd $ac_aux_dir && pwd`,$1)
	AC_MSG_CHECKING([for replacethisname])
	AC_MSG_RESULT(no)
	AC_SUBST(REPLACETHIS)
])

