/*  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
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
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>

#include "ptrace.h"

void traceme()
{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
}

void singletrace(child)
		pid_t child;
{
		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
}

int printregs(regs)
				struct user_regs_struct regs;
{
		return printf(
		/* long ebx, ecx, edx, esi, edi, ebp, eax; */
						"eax 0x%lx\n"
						"ebx 0x%lx\n"
						"ecx 0x%lx\n"
						"edx 0x%lx\n"
						"esi 0x%lx\n"
						"edi 0x%lx\n"
						"ebp 0x%lx\n"
		/* unsigned short ds, __ds, es, __es; */
						" ds 0x%x\t"
						"_ds 0x%x\n"
						" es 0x%x\t"
						"_es 0x%x\n"
		/* unsigned short fs, __fs, gs, __gs; */
						" fs 0x%x\t"
						"_fs 0x%x\n"
						" gs 0x%x\t"
						"_gs 0x%x\n"
		/* long orig_eax, eip; */
						"eax 0x%lx (original)\n"
						"eip 0x%lx\n"
		/* unsigned short cs, __cs; */
						" cs 0x%x\t"
						"_cs 0x%x\n"
		/* long eflags, esp; */
						"flg 0x%lx\n"
						"esp 0x%lx\n"
		/* unsigned short ss, __ss; */
						" ss 0x%x\t"
						"_ss 0x%x\n",
						regs.eax,
						regs.ebx,
						regs.ecx,
						regs.edx,
						regs.esi,
						regs.edi,
						regs.ebp,
						regs.ds,
						regs.__ds,
						regs.es,
						regs.__es,
						regs.fs,
						regs.__fs,
						regs.gs,
						regs.__gs,
						regs.orig_eax,
						regs.eip,
						regs.cs,
						regs.__cs,
						regs.eflags,
						regs.esp,
						regs.ss,
						regs.__ss
						);
						
}

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

