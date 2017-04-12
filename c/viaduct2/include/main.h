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
/* Last modified: Fri 04 Oct 2002 01:18:10 GMT
 */

#ifndef HAVE_MAIN_H
# define HAVE_MAIN_H

#include "default.h"

# define VIADUCTDEV_B "/dev/viaductb"
# define VIADUCTDEV_C "/dev/viaductc"
# define VIADUCT_BLOCK	S_IFBLK
# define VIADUCT_CHAR		S_IFCHR

static struct option option_list[] = {
		{ "block",		required_argument,			NULL, 'b' },
		{ "char",			required_argument,			NULL, 'c' },
		{ "host",			required_argument,			NULL, 'h' },
		{ "port",			required_argument,			NULL, 'p' },
		{ "bind",						no_argument,			NULL, 'l' },
		{ "udp",						no_argument,			NULL, 'u' },
		{ "verbose",				no_argument,			NULL, 'v' },
//		{ "test1",			no_argument,	NULL, 0 },
//		{ "test2",			required_argument,	NULL, 0 },
//		{ "test3",			optional_argument,	NULL, 0 },
		{ NULL,					0,									0,		0 }
};

static const char option_string[] = "b:c:h:p:luv";

static const struct option_help_text {
		char *name;
		char *help;
}	option_help[] = {
		{ "block",		"block device" },
		{ "char",			"character device" },
		{ "host",			"hostname or ip (if unused then reverts to 0.0.0.0)" },
		{ "port",			"port" },
		{ "bind",			"bind" },
		{ "udp",			"\tudp" },
		{ "verbose",	"verbose" },
		{ NULL,				NULL	}
};

struct arguments {
		char *idev;
		char *odev;
		int type;
		char *host;
		unsigned port;
		unsigned bind;
		unsigned verbose;
} arg;

static void __ATTRIB(__noreturn__) usage(const char *prog);

#endif /* HAVE_MAIN_H */


