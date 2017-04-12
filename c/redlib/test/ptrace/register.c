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
/* Last modified: Tue 26 Nov 2002 23:05:48 GMT
 */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/user.h>
#include <sys/syscall.h>

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		pid_t child;
		long orig_eax, eax;
		//long params[3];
		int status;
		int insyscall = 0;
		struct user_regs_struct regs;

		child = fork();
		if(child == 0) {
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				execl("/bin/ls", "ls", NULL);
		} else {
				while(1) {
						wait(&status);
						if(WIFEXITED(status))
								break;
						orig_eax = ptrace(PTRACE_PEEKUSER,
										child, 4 * ORIG_EAX, NULL);
						if(orig_eax == SYS_write) {
								if(insyscall == 0) {
										insyscall = 1;
										ptrace(PTRACE_GETREGS, child,
														NULL, &regs);
										printf("Write called with "
														"%ld %ld %ld\n",
														regs.ebx, regs.ecx,
														regs.edx);
								} else {
										eax = ptrace(PTRACE_PEEKUSER,
														child, 4 * EAX,
														NULL);
										printf("Write returned "
														"with %ld\n", eax);
										insyscall = 0;
								}
						}
						ptrace(PTRACE_SYSCALL, child,
										NULL, NULL);
				}
		}
		return 0;
}
