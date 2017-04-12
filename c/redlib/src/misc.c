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

/* #define DEBUG */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
 #warning redhat: empty source file
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#include <string.h>

static char b64[] =	"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
										"abcdefghijklmnopqrstuvwxyz" \
										"0123456789+/";

/* TODO: base64 function
 * 		Blah, blah, write base64()
 */
char *base64_in( char *buf);
char *base64_in( buf)
				char *buf;
{
				int i, len = strlen( buf);
				register char *out = buf;

				for( i = 0; i < len; i++)
				{
				}

				return out;
}

char *base64_out( char *buf);
char *base64_out( buf)
				char *buf;
{
				int i, len = strlen( buf);
				register char *out = buf;

				for( i = 0; i < len; i++)
				{
				}

				return out;
}

/* mime something */

/* XXX: SKIP
 * 		Warning: the following code should not be used
 * with out -O2 optimization. It relies on ELF and
 * gcc.
 * 		No optimization will equall a return, -O3 or
 * more break core dump on a `jmp' of 2 or more. And
 * generally jump to far. This can be blamed on the
 * fact that -O3 or more probably conserve function
 * calls by inlining functions.
 * 		`jmp' may never be larger than your current
 * call depth. `0' is equal to returning and current
 * depth is equal to an exit.
 * 		This will probably break with -fno-asm or
 * -fno-gnu-keywords
 */
#if !defined(__STRICT_ANSI__) && defined(__GNUC__) \
		&& __OPTIMIZE__ == 1 \
		&& defined(__i386__)&& defined(__ELF__)
inline void skip(jmp)
		int jmp;
{
		int i;
		for( i = 0; i < jmp; i++)
				__asm__ volatile(
								"pop  %esp          \n"
								"mov  %ebp,     %esp\n"
								"pop  %ebp          \n"
				);
}
#else
 # warning skip not activated
# define skip(X) /*  */
#endif /*  */

#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				return 0;
}
#endif /* DEBUG */

