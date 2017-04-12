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
/* Last modified: Wed 29 Sep 2004 02:27:54 GMT
 */

#include "default.h"
#include "colour.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/* #define DEBUG */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
 //#warning redhat: empty source file
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

typedef union {
		int i:3;
		unsigned int u:3;
} hbyte;

inline void rcolour(void)
{
		hbyte i = (hbyte)rand();
		hbyte j = (hbyte)rand();
#if 0
		printf("col: %u %d\n", i.u, i.i);
		printf("col: %u %d\n", j.u, j.i);
#endif
		while( i.u == j.u)
				j = (hbyte)rand();
		printf(COLSTR, i.u+30, j.u+40);
#if defined(DEBUG)
		printf("test value");
		COLOUR_RESET;
		printf("\n");
#endif /* DEBUG */
}

void rcolor(void)
{
		return rcolour();
}

int getcolumns(void)
{
		int i;
		char val[4];
		char *env;
		env = getenv("COLUMNS");
		if(env == NULL)
				return 80;

		for(i=0; i < 4; i++)
				val[i] = env[i];

		return (int)strtoul(val, NULL, 10);
}

#define BLANK ' '


/** TODO: Flashing words
 *		Add codes for flashing words etc...
 */

int rmarque(str, fg, bg, start, end, delay)
		char *str;
		unsigned int fg;
		unsigned int bg;
		unsigned int start;
		unsigned int end;
		double delay;
{
		unsigned int i, j = 0, k;
		unsigned int len = (end-start);
		char output[len+1];
		char line[start+1];

		if(fg == 0 && bg == 0) {
				fg = PLAIN;
				bg = BG_RED;
		}

		memset(output, '\0', len+1);
		memset(line, '\0', start+1);
		memset(line, ' ', start);

		while( j <= len+strlen(str)) {
				printf("%s", line);
				printf(COLSTR, fg, bg);
				for(i = 0; i < len-j && j < len; i++)
						output[i] = BLANK;
				for(k = j<len?0:j-len; i < len && k < strlen(str); i++, k++)
						output[i] = str[k];
				for(i=i; i < len; i++)
						output[i] = BLANK;
				printf("%s", output);
				COLOUR_RESET;
				printf("\r");
				fflush(stdout);
				usleep(delay*100000);
				++j; 
		}
		return 0;
}


int lmarque(str, fg, bg, start, end, delay)
		char *str;
		unsigned int fg;
		unsigned int bg;
		unsigned int start;
		unsigned int end;
		double delay;
{
		unsigned int i, j = 0, k;
		unsigned int len = (end-start);
		unsigned int _strlen = strlen(str);
		char output[len+1];
		char line[start+1];

		if(fg == 0 && bg == 0) {
				fg = PLAIN;
				bg = BG_RED;
		}

		memset(output, '\0', len+1);
		memset(line, '\0', start+1);
		memset(line, ' ', start);

		while( j <= len+_strlen) {
				printf("%d-%s", j,line);
				printf(COLSTR, fg, bg);
				/* y */
				for(i = 0; i < len; i++)
						output[i] = 'B';
				for(i = j; i < len; i++)
						output[i] = 'x';
				for(k = 0, i = j-1; k < _strlen && i < len; i++, k++)
								output[i] = str[k];
				for(i = 0; i < j && i < len; i++)
						output[i] = 'y';
				printf("%s", output);
				COLOUR_RESET;
				printf("\r\n");
				fflush(stdout);
				//usleep(delay*100000);
				++j; 
		}
		return 0;
}


int tmarque(str, fg, bg, start, end, delay)
		char *str;
		unsigned int fg;
		unsigned int bg;
		unsigned int start;
		unsigned int end;
		double delay;
{
		unsigned int i, j = 0, k;
		unsigned int len = (end-start);
		char output[len+1];
		char line[start+1];

		if(fg == 0 && bg == 0) {
				fg = PLAIN;
				bg = BG_RED;
		}

		memset(output, '\0', len+1);
		memset(line, '\0', start+1);
		memset(line, ' ', start);

		while( j <= len+strlen(str)) {
				printf("%s", line);
				printf(COLSTR, fg, bg);
				for(i = 0; i < len-j && j < len; i++)
						output[i] = BLANK;
				for(k = j<len?0:j-len; i < len && k < strlen(str); i++, k++)
						output[i] = str[k];
				for(i=i; i < len; i++)
						output[i] = BLANK;
				printf(TITLE, output);
				COLOUR_RESET;
				printf("\r");
				fflush(stdout);
				usleep(delay*100000);
				++j; 
		}
		return 0;
}


#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				int i, j, x;
				srand(time(NULL));
				printf(CLEAR);
				for(i = 30; i < 49; i++) {
								COLOUR_RESET;
								if(i%10 == 0) {
												printf("   ");
												for(x = 0; x < 20; x++)
																printf("%2d",x);
												for(x = 21; x < 24; x++)
																printf("%2d",x);
												printf("\n");
								}
								printf("%02d ", i);
								for(j = 0; j < 20; j++) {
												COLOUR_RESET;
												printf("\033[%d;%dm",	j,i);
												printf(" %%");
								}
								COLOUR_RESET;
								for(j = 21; j < 24; j++) {
												COLOUR_RESET;
												printf("\033[%d;%dm",	j,i);
												printf(" %%");
								}
								COLOUR_RESET;
								printf("\n");
				}
				COLOUR_RESET;
				rcolor();
				printf(TOP);
				rmarque("Eat At Joe's!", 31, 1, getcolumns()/2-10, getcolumns()/2+10, 1);
				rmarque("Eat At Joe's!", 5, 41, getcolumns()/2-10, getcolumns()/2+10, 1);
				rmarque("Eat At Joe's!", 31, 7, getcolumns()/2-10, getcolumns()/2+10, 1);
				rmarque("Eat At Joe's!", 7, 41, getcolumns()/2-10, getcolumns()/2+10, 1);
				return 0;
}
#endif /* DEBUG */

