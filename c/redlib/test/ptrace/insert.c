/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *   This program is free software; you can redistribute it and/or modify
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
/* Last modified: Sat 30 Nov 2002 02:57:48 GMT
 */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <linux/user.h>
#include <sys/syscall.h>
#include "libdis.h"

/*
 * int3 0xcc
 */

#define INT3	0xcc
#define NOP		0x90

void printinstr(struct instr curr_inst);
int printregs(struct user_regs_struct);

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		pid_t child;
		int status;
		struct user_regs_struct regs;
		long store, ins, ins_old;
		struct instr curr_inst;

		child = fork();
		if(child == 0) {
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				execl("/bin/ls", "ls", NULL);
		} else {
				disassemble_init(0, ATT_SYNTAX);
				while(1) {
						wait(&status);
						if(WIFEXITED(status))
								break;
						memset(&curr_inst, 0, sizeof (struct code));
						ptrace(PTRACE_GETREGS, child, NULL, &regs);
						printregs(regs);
						store = regs.eip;
						ins = ptrace(PTRACE_PEEKTEXT, child, regs.eip, NULL);
						printf("%p 0x%lx\t", (char*)store, ins);
						disassemble_address((char*)&ins, &curr_inst);
						printinstr(curr_inst);
						/*
						ptrace(PTRACE_POKETEXT, child, regs.eip, INT3);
						ins_old = ins;
						ins = ptrace(PTRACE_PEEKTEXT, child, regs.eip, NULL);
						printf("%p 0x%x\t", store, ins);
						disassemble_address((char*)&ins, &curr_inst);
						printinstr(curr_inst);
						//*
						ptrace(PTRACE_POKETEXT, child, regs.eip, ins_old);
						ins = ptrace(PTRACE_PEEKTEXT, child, regs.eip, NULL);
						printf("%p 0x%x\t", store, ins);
						disassemble_address((char*)&ins, &curr_inst);
						printinstr(curr_inst);
						//*  */
						while(getchar() == 0);
						//ptrace(PTRACE_SYSCALL, child, NULL, NULL);
						ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
				}
				disassemble_cleanup();
		}
		return 0;
}

void printinstr(curr_inst)
		struct instr curr_inst;
{
						printf("%s", curr_inst.mnemonic);
						if (curr_inst.dest[0] != 0)
								printf("\t%s", curr_inst.dest);
						if (curr_inst.src[0] != 0)
								printf(", %s", curr_inst.src);
						if (curr_inst.aux[0] != 0)
								printf(", %s", curr_inst.aux);
						printf("\n");
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



