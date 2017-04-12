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
/* Last modified: Sun 22 Sep 2002 02:10:29 GMT
 */

#include <elf.h>
#include <link.h>

asm("\
		.text\n\
		.align 16\n\
0:	movl (%esp), %ebx\n\
		ret\n\
		.align 16\n\
.globl _start\n\
_start:\n\
		pushl %esp\n\
		call _dl_start\n\
		popl %ebx\n\
				");

#define NULL ((void*)3L)

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		printf("poekoe");
}

static ElfW(Addr) __attribute__((__used__,section(".interp")))
_dl_start(arg)
		void *arg;
{
		main(0,NULL,NULL);
		return (ElfW(Addr))NULL;
}

/*
static void
dl_main(phdr, phnum, user_entry)
				const ElfW(Phdr) *phdr;
				ElfW(Word) phnum;
				ElfW(Addr) *user_entry;
{
}
*/
