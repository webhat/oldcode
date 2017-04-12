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
/* Last modified: Tue 26 Nov 2002 23:55:04 GMT
 */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/user.h>

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		pid_t child;
		long orig_eax;

		child = fork();
		if(child == 0) {
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				execl("/bin/ls", "ls", NULL);
		} else {
				wait(NULL);
				orig_eax = ptrace(PTRACE_PEEKUSER,
								child, 4 * ORIG_EAX,
								NULL);
				printf("The child made a "
								"system call %ld\n", orig_eax);
				ptrace(PTRACE_CONT, child, NULL, NULL);
		}
		return 0;
}


