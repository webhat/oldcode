/*
    Copyright (C) 1997-2000  Daniel W. Crompton <redhat@rphh.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef HAVE_CONFIG_H
#define HAVE_CONFIG_H
/* Have main.h */
#undef HAVE_MAIN_H
#include <tao.h>

/* Which OS used */
#undef SOLARIS
#undef LINUX
#undef BSD

/* Threads */
#undef _MIT_POSIX_THREADS

/* Random */
#ifdef HAVE_RANDOM
#define SRAND srandom
#define RAND random
#else
#define SRAND srand
#define RAND rand
#endif /* HAVE_RANDOM */

#define USHORT unsigned short
#define ULONG unsigned long
#define UINT unsigned int
#define UCHAR unsigned char

extern volatile int srcfd;
extern volatile int destfd;

extern void usage(void);
extern int debug( int lvl, char* body);
extern int broke( char* body);

/* timer.c */
extern int timer( int interval );

/* tap.c */
extern int file( char *name );
extern int chardev( int fd );
extern int tap( int fd );

/* crossfun.c */
extern void src2dest( int src, int dest );

/* popt.c */
extern void process_args( int argc, char **argv, tao_opt *ret);

/* serial.c */
extern int start_serial( int fd);
extern void serial_write( int fd, char *in);
extern void serial_read( int fd, char *out);

/* version.c */
extern char *version;

#endif /* HAVE_CONFIG_H */


