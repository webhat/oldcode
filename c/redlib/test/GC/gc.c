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
/* Last modified: Sun 18 Aug 2002 14:20:31 GMT
 */

/* XXX: Garbage collect demo
 * 		The idea is that the allocation pop's it's own return addr
 * of the stack, it then puts the return addr for the free(gc on
 * the stack. Then it pop's it's own ret addr onto the stack then
 * it returns.
 *
 * 		- allocate {
 * 				- pop RET to $RET
 * 				- allocate $PTR
 * 				- push $PTR
 * 				- push @FREE
 * 				- push $RET
 * 				- return
 * 		}
 */

#include <stdio.h>

/*
 * 0x80486c0 <xfree>:      push   %ebp
 * 0x80486c1 <xfree+1>:    mov    %esp,%ebp
 * 0x80486c3 <xfree+3>:    sub    $0x8,%esp
 * 0x80486c6 <xfree+6>:    sub    $0x8,%esp
 * 0x80486c9 <xfree+9>:    pushl  0x8(%ebp)
 * 0x80486cc <xfree+12>:   push   $0x8048798
 * 0x80486d1 <xfree+17>:   call   0x8048578 <printf>
 * 0x80486d6 <xfree+22>:   add    $0x10,%esp
 * 0x80486d9 <xfree+25>:   mov    %ebp,%esp
 * 0x80486db <xfree+27>:   pop    %ebp
 * 0x80486dc <xfree+28>:   ret
 */

int xfree()
{
		printf("=0x%x\n", 1);
		return 88;
}

/*
 * 0x80486e0 <function>:   push   %ebp
 * 0x80486e1 <function+1>: mov    %esp,%ebp
 * 0x80486e3 <function+3>: mov    0xc(%ebp),%eax
 * 0x80486e6 <function+6>: add    0x8(%ebp),%eax
 * 0x80486e9 <function+9>: add    0x10(%ebp),%eax
 * 0x80486ec <function+12>:        pop    %ebp
 * 0x80486ed <function+13>:        ret
 */

/*
 * 0x80484b0 <function>:     push   %ebp
 * 0x80484b1 <function+1>:   mov    %esp,%ebp
 * 0x80484b3 <function+3>:   push   %ebx
 * 0x80484b4 <function+4>:   sub    $0x4,%esp
 * 0x80484b7 <function+7>:   mov    0x10(%ebp),%ebx
 * 0x80484ba <function+10>:  sub    $0x8,%esp
 * 0x80484bd <function+13>:  pushl  0xfffffff8(%ebp)
 * 0x80484c0 <function+16>:  push   $0x80485be
 * 0x80484c5 <function+21>:  call   0x804833c <printf>
 * 0x80484ca <function+26>:  add    $0x10,%esp
 * 0x80484cd <function+29>:  popl   0xfffffff8(%ebp)
 * 0x80484d0 <function+32>:  push   %ebx
 * 0x80484d1 <function+33>:  push   $0x8048480
 * 0x80484d6 <function+38>:  pushl  0xfffffff8(%ebp)
 * 0x80484d9 <function+41>:  sub    $0x8,%esp
 * 0x80484dc <function+44>:  pushl  0xfffffff8(%ebp)
 * 0x80484df <function+47>:  push   $0x80485be
 * 0x80484e4 <function+52>:  call   0x804833c <printf>
 * 0x80484e9 <function+57>:  add    $0x10,%esp
 * 0x80484ec <function+60>:  sub    $0x8,%esp
 * 0x80484ef <function+63>:  push   $0x8048480
 * 0x80484f4 <function+68>:  push   $0x80485be
 * 0x80484f9 <function+73>:  call   0x804833c <printf>
 * 0x80484fe <function+78>:  add    $0x10,%esp
 * 0x8048501 <function+81>:  mov    0xc(%ebp),%eax
 * 0x8048504 <function+84>:  add    0x8(%ebp),%eax
 * 0x8048507 <function+87>:  add    %ebx,%eax
 * 0x8048509 <function+89>:  mov    0xfffffffc(%ebp),%ebx
 * 0x804850c <function+92>:  mov    %ebp,%esp
 * 0x804850e <function+94>:  pop    %ebp
 * 0x804850f <function+95>:  ret
 */

typedef int (*func_t)();

int function( x, y, z)
		int x;
		int y;
		int z;
{
		unsigned long eax = (unsigned long)NULL;
		void *val = NULL;
		printf("val\t\t%p\n", val);
		__asm__ __volatile__(
						//"add %1,%0"
						"popl %%eax\n\t"
						"pushl %1\n\t"
						"pushl %2\n\t"
						"pushl $xfree\n\t"
						"pushl %%eax\n\t"
						"mov %%ebp, %%eax\n"
						/* */
						: "=p" (val), "=a" (eax)
						: "g" (z) , "g" ((func_t *)(xfree))
						);
		/* */
		printf("val\t\t%p\n", val);
		printf("xfree\t\t%p\n", ((func_t *)(xfree)));
		printf("eax 0x%08lx\t%p\n", eax, &eax);

		return (x+y+z);
}

/*
 * 0x80486f0 <main>:       push   %ebp
 * 0x80486f1 <main+1>:     mov    %esp,%ebp
 * 0x80486f3 <main+3>:     sub    $0x8,%esp
 * 0x80486f6 <main+6>:     and    $0xfffffff0,%esp
 * 0x80486f9 <main+9>:     sub    $0x4,%esp
 * 0x80486fc <main+12>:    push   $0x3
 * 0x80486fe <main+14>:    push   $0x2
 * 0x8048700 <main+16>:    push   $0x1
 * 0x8048702 <main+18>:    call   0x80486e0 <function>
 * 0x8048707 <main+23>:    add    $0x10,%esp
 * 0x804870a <main+26>:    mov    %eax,0xfffffffc(%ebp)
 * 0x804870d <main+29>:    mov    $0x0,%eax
 * 0x8048712 <main+34>:    mov    %ebp,%esp
 * 0x8048714 <main+36>:    pop    %ebp
 * 0x8048715 <main+37>:    ret
 */

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		int i = function( 1, 2, 3);

		unsigned long eax = (unsigned long)NULL;
		unsigned long ebx = (unsigned long)NULL;
		unsigned long ecx = (unsigned long)NULL;
		unsigned long edx = (unsigned long)NULL;

		asm(
						"mov %%esp,%%eax\n"
						: "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
						: /* no vals */
			 );
		printf("eax 0x%08lx\t%p\n", eax, &eax);
		printf("ebx 0x%08lx\t%p\n", ebx, &ebx);
		printf("ecx 0x%08lx\t%p\n", ecx, &ecx);
		printf("edx 0x%08lx\t%p\n", edx, &edx);

		i = i;

		return 0;
}

