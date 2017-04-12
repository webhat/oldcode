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
/* Last modified: Sun 22 Dec 2002 00:29:45 GMT
 */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/user.h>
#include <sys/syscall.h>


#define ZZ(X) printf("%s: %s\n", __PRETTY_FUNCTION__, #X);

void func1(void);
void func2(void);
void func3(void);

void func1()
{
		ZZ(in);
		func2();
		ZZ(out);
}

void func2()
{
		ZZ(in);
		func3();
		ZZ(out);
}

void func3()
{
		char *xx = calloc(1,2);
		strcat(xx,"x");
		printf("%s\n", xx);
		ZZ(out);
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		long orig_eax;
		pid_t child;
		int status;
		int insyscall = 0;

		child = fork();
		if(child == 0) {
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				func1();
		} else {
				while(1) {
						wait(&status);
						if(WIFEXITED(status))
								break;
						orig_eax = ptrace(PTRACE_PEEKUSER,
										child, 4 * ORIG_EAX, NULL);
						switch(orig_eax) {
								case SYS_mmap:
										insyscall = 1;
										printf("mmap:   \n");
										break;
										/*
								case SYS_mmap2:
										insyscall = 1;
										printf("mmap2:  \n");
										break;
										*/
								case SYS_mremap:
										insyscall = 1;
										printf("mremap: \n");
										break;
								case SYS_munmap:
										insyscall = 1;
										printf("munmap: \n");
										break;
								default:
										insyscall = 0;
						}
				}
				exit(0);
		}

		return 0;
}


