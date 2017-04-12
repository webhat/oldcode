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
/* Last modified: Tue 26 Nov 2002 23:46:35 GMT
 */

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <linux/user.h>
#include <sys/syscall.h>

const int long_size = sizeof(long);

void reverse(char *str) {
		int i,j;
		char temp;
		for(i = 0, j = strlen(str) -2;
						i <= j; ++i, --j) {
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
		}
}

void getdata(pid_t child, long addr, char *str, int len) {
		char *laddr;
		int i, j;
		union u {
				long val;
				char chars[long_size];
		}data;

		i = 0;
		j = len/long_size;
		laddr = str;

		while(i < j) {
				data.val = ptrace(PTRACE_PEEKDATA,
								child, addr + i * 4,
								NULL);
				memcpy(laddr, data.chars, long_size);
				++i;
				laddr += long_size;
		}

		j = len % long_size;
		if(j != 0) {
				data.val = ptrace(PTRACE_PEEKDATA,
								child, addr + i * 4,
								NULL);
				memcpy(laddr, data.chars, j);
		}
		str[len] = '\0';
}

void putdata(pid_t child, long addr, char *str, int len) {
		char *laddr;
		int i, j;
		union u {
				long val;
				char chars[long_size];
		}data;

		i = 0;
		j = len/long_size;
		laddr = str;

		while(i < j) {
				memcpy(data.chars, laddr, long_size);
				ptrace(PTRACE_POKEDATA, child,
								addr + i * 4, data.val);
				++i;
				laddr += long_size;
		}

		j = len % long_size;
		if(j != 0) {
				memcpy(data.chars, laddr, j);
				ptrace(PTRACE_POKEDATA, child,
								addr + i * 4, data.val);
		}
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		pid_t child;

		child = fork();
		if(child == 0) {
				ptrace(PTRACE_TRACEME, 0, NULL, NULL);
				execl("/bin/ls", "ls", NULL);
		} else {
				long orig_eax;
				long params[3];
				int status;
				char *str, *laddr;
				int toggle = 0;

				while(1) {
						wait(&status);
						if(WIFEXITED(status))
								break;
						orig_eax = ptrace(PTRACE_PEEKUSER,
										child, 4 * ORIG_EAX, NULL);

						if(orig_eax == SYS_write) {
								if(toggle == 0) {
										toggle = 1;
										params[0] = ptrace(PTRACE_PEEKUSER,
														child, 4 * EBX,
														NULL);
										params[1] = ptrace(PTRACE_PEEKUSER,
														child, 4 * ECX,
														NULL);
										params[2] = ptrace(PTRACE_PEEKUSER,
														child, 4 * EDX,
														NULL);
										/*
										printf("Write called with "
														"%ld %ld %ld\n",
														params[0], params[1],
														params[2]);
														*/
										str = (char *) calloc((params[2]+1)
														* sizeof(char));
										getdata(child, params[1], str,
														params[2]);
										reverse(str);
										putdata(child, params[1], str,
														params[2]);
								} else {
										toggle = 0;
								}
						}
						ptrace(PTRACE_SYSCALL, child,
										NULL, NULL);
				}
		}
		return 0;
}
