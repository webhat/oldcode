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
/* Last modified: Wed 27 Nov 2002 01:32:47 GMT
 */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <linux/user.h>
#include <dlfcn.h>

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		pid_t child;
		//long orig_eax;
		//char *str;
		struct user_regs_struct regs;

		child = fork();
		if(child == 0) {
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				execl("/bin/ls", "ls", NULL);
		} else {
				/*
				wait(NULL);
				orig_eax = ptrace(PTRACE_PEEKUSER,
								child, 4 * ORIG_EAX,
								NULL);
				printf("The child made a "
								"system call %ld\n", orig_eax);
				ptrace(PTRACE_GETREGS, child, NULL, &regs);
				regs.eax = 4L;
				ptrace(PTRACE_SETREGS, child, NULL, &regs);
				ptrace(PTRACE_POKEUSER,
								child, 4 * EBX,
								1L);
				str = (char*)ptrace(PTRACE_PEEKUSER,
								child, 4 * EBX,
								NULL);
				ptrace(PTRACE_POKEUSER,
								child, 4 * ECX,
								str);
				ptrace(PTRACE_POKEUSER,
								child, 4 * EDX,
								2L);
				*/
				int status = 0;
				long ins;
				while(1) {
						wait(&status);
						if(WIFEXITED(status))
								break;
						ptrace(PTRACE_GETREGS, child, NULL, &regs);
						ins = ptrace(PTRACE_PEEKTEXT, child, regs.eip, NULL);
						fprintf(stderr, "eip: 0x%lx\t", regs.eip);
						//ptrace(PTRACE_POKETEXT, child, regs.eip + 1, 0L);
						//ptrace(PTRACE_POKETEXT, child, regs.eip , 0x903c); /* ret */
						/* pop %ebp */
						//ptrace(PTRACE_POKETEXT, child, regs.eip , 0x8955c35d);
						/* push %ebp */
						//ptrace(PTRACE_POKETEXT, child, regs.eip , 0x83e58955);
						//ptrace(PTRACE_POKETEXT, child, regs.esp + sizeof(long), ins);
						fprintf(stderr, "esp: 0x%lx\n", regs.esp);
						fprintf(stderr, "ins: 0x%lx\n", ins);
		//			fprintf(stderr, "ptr: 0x%lx\t", (long)dlsym((void*)-1L, "execl"));
		//			fprintf(stderr, "ptr: 0x%lx\n", (long)dlsym((void*)-1L, "execve"));
						while(getchar() == 0);
						ptrace(PTRACE_SYSCALL, child, NULL, NULL);
				}
		}
		return 0;
}


