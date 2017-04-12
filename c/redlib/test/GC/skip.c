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
/* Last modified: Sun 01 Sep 2002 03:58:25 GMT
 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/linkage.h>

#define __F __PRETTY_FUNCTION__

void skip(int);
void firstcall();
void secondcall();
void thirdcall();
void fourthcall();
void fifthcall();
void sixthcall();
void sevnthcall();
void eighthcall();

unsigned int jmpcnt;

inline void skip(jmp)
		int jmp;
{
		int i;
		for( i = 0; i < jmp; i++)
				asm volatile(
								"pop  %esp          \n"
								"mov  %ebp,     %esp\n"
								"pop  %ebp          \n"
				);
}

void eighthcall()
{
		printf("start %s\n", __F);
		skip(jmpcnt);
		printf("end   %s\n", __F);
}

void seventhcall()
{
		printf("start %s\n", __F);
		eighthcall();
		printf("end   %s\n", __F);
}

void sixthcall()
{
		printf("start %s\n", __F);
		seventhcall();
		printf("end   %s\n", __F);
}

void fifthcall()
{
		printf("start %s\n", __F);
		sixthcall();
		printf("end   %s\n", __F);
}

void fourthcall()
{
		printf("start %s\n", __F);
		fifthcall();
		printf("end   %s\n", __F);
}

void thirdcall()
{
		printf("start %s\n", __F);
		fourthcall();
		printf("end   %s\n", __F);
}

void secondcall()
{
		printf("start %s\n", __F);
		thirdcall();
		printf("end   %s\n", __F);
}

void firstcall()
{
		printf("start %s\n", __F);
		secondcall();
		printf("end   %s\n", __F);
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		if(argc > 1)
				jmpcnt = atoi(argv[1]);
		else
				jmpcnt = 1;

		printf("start %d\n",__OPTIMIZE__);
		firstcall();
		printf("end\n");
}
