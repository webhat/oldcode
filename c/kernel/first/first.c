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
/* Last modified: Mon 01 Jul 2002 00:23:59 GMT
 */

/* compile with 'gcc -c <file>' */

#define __KERNEL__
#define MODULE

#define VERSION_CODE(vers,rel,seq) (((vers)<<16)|((rel)<<8)|(seq))

#if __DEBUG__
# define DEBUG(STR) printk("<1>" #STR "\n")
#else /* __DEBUG__ */
#define DEBUG(STR) /* none */
#endif /* __DEBUG__ */

#define MODNAME					my_first_module
#define MODCHAR					"my_first_module"
#define MODFUNC(TYPE)		my_first_module_ ## TYPE

/* #define __NO_VERSION__ */

#include <linux/module.h>

int init_module(void)
{
				DEBUG(init_module);
				return 0;
}

void cleanup_module(void)
{
				DEBUG(fini_module);
}

static const char *MODFUNC(start)()
{
				return MODCHAR;
}

MODULE_LICENSE("GPL");

