/*
    Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>

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
/* $Id: $ */

#include <dlfcn.h>
#include "plib.h"

int open(const char *pathname, int flags)
{
				void *gz_handle = dlopen("/usr/lib/libz.so", RTLD_LAZY);
				void *io_handle = dlopen("/usr/lib/libc.so", RTLD_LAZY);


				void (*gzopen)( const char *path, const char *mode) = dlsym( gz_handle, "gzopen");
				gzopen( pathname, flags);


				(void) io_handle;
				return 0;
}

#ifdef DEBUG
#define O_APPEND					02000
#define O_TRUNC						01000


int main( void)
{
				open( "plaap.gz", O_APPEND|O_TRUNC);
				return 0;
}
#endif /* DEBUG */

