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

#include <dlfcn.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void *load ( name)
				const char *name;
{
				void *dl = dlopen ( name, RTLD_LAZY|RTLD_GLOBAL);
				if (dl == NULL)
								error ( EXIT_FAILURE, errno, "cannot load `%s'", name);
				return dl;
}

int unload( handle)
				void *handle;
{
				return dlclose( handle);
}

const char *lookup( sym)
				void *sym;
{
				Dl_info info;

				return ( dladdr( sym, info) ? NULL : info.dli_sname);
}
