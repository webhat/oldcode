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
/* Last modified: Mon 02 Dec 2002 22:18:37 GMT
 */

#ifndef HAVE_PTRACE_H
# define HAVE_PTRACE_H

# include <linux/user.h>
# include <sys/types.h>

# define INT3		0xcc
# define NOP		0x90

void traceme(void);
void singlestep(pid_t);
int printregs(struct user_regs_struct);

#endif /* HAVE_PTRACE_H */


