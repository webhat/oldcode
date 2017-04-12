/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/* CVSVERSION: $Id: $ */
/* Last modified: Tue 03 Dec 2002 00:53:15 GMT
 */


#include <stdio.h>

#define _INFUNC(X)	int in() {							\
												printf("called\n");	\
												return 1;						\
										}												\
										in()

#define INFUNC(X)		do {										\
												printf("called\n");	\
										} while(0)


void out() {
		printf("before\n");
		INFUNC();
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		INFUNC();
		out();
		return 0;
}


