/*
    Copyright (C) 1997-2000  Daniel W. Crompton <redhat@rphh.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* CVSVERSION: $Id: cross.h,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

#include <config.h>
#include <headers.h>

#ifndef HAVE_CROSS_H

  #ifndef _MIT_POSIX_THREADS
  	/* Added by punisher */
//  	#include <bits/pthreadtypes.h>
  	#include <sched.h>
  	#include <pthread.h>
  	#include <unistd.h>
  	#define _MIT_POSIX_THREADS
  #endif /* _MIT_POSIX_THREADS */

	#include <string.h>

  #define HAVE_CROSS_H
#endif /* HAVE_CROSS_H */
