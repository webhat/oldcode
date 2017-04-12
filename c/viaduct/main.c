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

#define CVSVERSION "$Id: main.c,v 1.1.1.1 2000/07/14 20:13:48 webhat Exp $"

#include <config.h>
#include <headers.h>
#include <tao.h>

#ifndef HAVE_MAIN_H
  #include <main.h>
  #define HAVE_MAIN_H
#endif /* HAVE_MAIN_H */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int bind_on_interface( USHORT prt, UCHAR *src);

volatile int srcfd;
volatile int destfd;

int main ( int argc, char **argv) {
#ifdef PROCESS
				tao_opt *p;
				process_args( argc, argv, p);
				return 1;
#else

				UINT op;
				UINT port = 0;
				UINT Sser;
				UINT Dser;
				USHORT sorp = 0;
				USHORT dev = 0;
				char *dest_dev = "";
				char *src_dev = ALL_INTERFACES;
				verbose = 0;
				program_name = argv[0];

//FIXME: The getopt() library need to be sorted out and 'popt()' needs to be
//	used instead of the getopt() library.
//	
//	Maybe the getopt library needs to be used in conjunction with the popt()
//	library...

//FIXME: If you open a tty and don't want O_NOCTTY.

//FIXME: If you want to write to a file synchronously. ( O_SYNC / O_DSYNC / O_RSYNC )
//	Or using sync(2). (Although this is not prefered...)

				while ( (op = getopt ( argc, argv, "?ad:ep:s:t:vV") ) != EOF )
								switch (op) {
												case '?':
												case 'h':
																usage();
																break;
#ifdef DEBUG
												case 'a':
																verbose = 10;
																break;
#endif /* DEBUG */
												case 'd':
																dev++;
																dest_dev = (char*) optarg;
// FIXME: Add access(2) instead of file(3), as defined in tap.c
																if( !file( dest_dev)) {
// FIXME: fix the O_APPEND by adding mode to open(2)
																				destfd = open( dest_dev, O_RDWR|
																																	O_CREAT|
																																	O_APPEND|
																																	O_NOCTTY 
																																	);
																				if( chardev( destfd)) {
																								Dser++;
#ifdef DEBUG
																								debug( 1, "chardev dest");
#endif /* DEBUG */
																				}

																} else {
																				broke("No such file or directory");
																}
																break;
												case 'e':
																break;
												case 'p':
																sorp++;
																port = atoi( optarg);
																break;
												case 's':
																sorp++;
																src_dev = (char*) optarg;
																if( !file( src_dev)) {
																				srcfd = open( src_dev, O_RDONLY|
																																	O_NOCTTY );
																				if( chardev( srcfd)) {
																								Sser++;
#ifdef DEBUG
																								debug( 1, "chardev src");
#endif /* DEBUG */
																				}

																} else {
																				srcfd = (int) bind_on_interface( (USHORT) 2000, src_dev);
																			//	getbyname( src_dev, (USHORT) 0);
																}
																break;
												case 't':
#ifdef DEBUG
																debug( 9, "timer");
																timer( atoi( optarg) );
#endif /* DEBUG */
																break;
												case 'v':
																verbose++;
#ifdef DEBUG
																debug( 9, "verbose");
																debug( 9, "extra verbose");
#endif /* DEBUG */
																break;
												case 'V':
																fprintf( stdout, "%s\n", CVSVERSION); 
																exit(1);
												default:
																usage();
																break;
								}
				if ( !sorp || !dev ) {
				(void) fprintf( stderr, "required: %s [-s <src>|-p <port>] -d <dest>\n", program_name);
								usage();
				} else {
								if( src_dev && port ) {
												(void) fprintf( stderr, "%s:%d --> %s\n", src_dev, port, dest_dev);
								} else {
												(void) fprintf( stderr, "%s --> %s\n", src_dev, dest_dev);
												src2dest( srcfd, destfd);
								}
				}
				return 1;
#endif /* PROCESS */
}

int broke ( char* body) {
				(void) fprintf( stderr, "%s\n", body);
				exit(0);
}

int debug ( int lvl, char* body) {
				if ( verbose >= lvl ) {
								(void) fprintf( stderr, "%s\n", body);
				}
				return lvl;
}

void usage(void) {
				(void) fprintf(stderr, "%s [-vvv] [-ae] -d <dest> [-s <src>|-p <port>]\n", program_name);
				(void) fprintf(stderr, "\t-a\t\tshow all\n");
				(void) fprintf(stderr, "\t-d\t\t<dest>\tdestination\n");
				(void) fprintf(stderr, "\t-p\t\t<port>\tport\n");
				(void) fprintf(stderr, "\t-e\t\tunknown\n");
				(void) fprintf(stderr, "\t-s\t\t<src>\tsource\n");
				(void) fprintf(stderr, "\t-t\t\t<time>\ttime interval\n");
				(void) fprintf(stderr, "\t-v\t\tverbose\n");
				(void) fprintf(stderr, "\t-vv\t\textra verbose\n");
				(void) fprintf(stderr, "\t-vvv\t\teven more extra verbose\n");
				exit(-1);
}


