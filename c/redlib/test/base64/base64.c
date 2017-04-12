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
/* Last modified: Sun 19 Jan 2003 23:15:35 GMT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERROR(X) fprintf(stderr,"Error %s: `%s'\n",X,strerror(errno))

char *base64encode(const u_char*);
char *base64decode(const u_char*);

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		int cnt = 2;
		char *str = calloc(1,cnt);
		char buf[2];

		if(str == NULL) {
				ERROR("");
				return -1;
		}

		memset(buf, 0, sizeof(buf));

		while((buf[0] = getchar()) != EOF) {
				str = realloc( str, strlen(str)+1);
				strncat(str,buf,1);
		}

		fflush(stdout);
		fflush(stderr);

		str = base64encode(str);
		printf("encode:\n %s\n", str);
		str = base64decode(str);
		printf("decode:\n %s\n", str);

		return 0;
}

static const char base64chars[64] = {
		'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','z',
		'0','1','2','3','4','5','6','7','8','9','+','/'
};

char base64padchar = '=';


char *base64encode(input)
		const u_char *input;
{
		int i;
		u_char output[4];

		memset(output, 0, sizeof(output));

		return output;
}

char *base64decode(input)
		const u_char *input;
{
		int i;
		u_char output[4];

		memset(output, 0, sizeof(output));

		return output;
}

