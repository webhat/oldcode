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
/* CVSVERSION: $Id: $ */

/* Global includes: */
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Local includes: */
#include <global.h>
#include <config.h>

/* Fuctions */
void usage( char *msg) __attribute__ ((__noreturn__));

/* Global vars */

int main( int argc, char *argv[]) {
				unsigned int op;
#ifdef PKILL
				unsigned int nr = -1;
				unsigned int sig = 15;
				char sign[2];
#endif /* PKILL */
				char *name = malloc( 512);
#ifndef PKILL
				delim = malloc( 16);
				optarg = malloc( 16);
				form = 0;
				got_id = 0;
				type = f_not;

				if( delim == NULL)
								return 3;
				if( optarg == NULL)
								return 3;
				if( name == NULL)
								return 3;

				snprintf( delim, 16, "%s", " ");
#endif /* not PKILL */

				if( argc <= 1 ) usage( argv[0]);

				strncpy( name, argv[argc -1], 512);

				while( (op = getopt( argc, argv, "g:G:P:s:t:u:U:d:g:lh?123456789")) != EOF)
								switch(op) {
#ifndef PKILL
												case 'd':
																strncpy( delim, optarg, 16);
																break;
#endif /* not PKILL */
												case 'h':
												case '?':
																usage( argv[0]);
																break;
//enum id_types { f_not, f_uid, f_euid, f_pid, f_gid, f_ppid, f_sid, f_pgrp, f_tty} id_types;
												case 'g':
																type = f_pgrp;
																got_id = atoi( optarg);
																break;
												case 'G':
																type = f_gid;
																got_id = atoi( optarg);
																break;
												case 'P':
																type = f_ppid;
																got_id = atoi( optarg);
																break;
												case 's':
																type = f_sid;
																got_id = atoi( optarg);
																break;
												case 't':
																type = f_tty;
																got_id = atoi( optarg);
																break;
												case 'u':
																type = f_euid;
																got_id = atoi( optarg);
																break;
												case 'U':
																type = f_uid;
																got_id = atoi( optarg);
																break;
#ifndef PKILL
												case 'l':
																form = 1;
																break;
#endif /* not PKILL */
#ifdef PKILL
												case '1':
												case '2':
												case '3':
												case '4':
												case '5':
												case '6':
												case '7':
												case '8':
												case '9':
												case '0':
																nr++;
																if( 2 <= nr ) {
																				sig = atoi( sign);
																			 	break;
																}
																sign[nr] = op;
																break;
#endif /* PKILL */
												default:
																break;
																
								}
//printf("f_not(%d) f_uid(%d) f_euid(%d) f_pid(%d) f_gid(%d)\nf_ppid(%d) f_sid(%d) f_pgrp(%d) f_tty(%d)\n", f_not, f_uid, f_euid, f_pid, f_gid, f_ppid, f_sid, f_pgrp, f_tty);
				lookup_proc( name);

				free( name);

				PFUNC( sig);
				return 0;
}

void usage(char *msg) {
#ifdef PKILL
				char *sig ="[-SIGNAL] ";
#else
				char *sig ="[-l] [-d delim] ";
#endif /* PKILL */

				printf(	"%s (%s) pfunc package\n"
								"Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org>\n"
								"This program comes with ABSOLUTELY NO WARRANTY.\n"
								"This is free software, and you are welcome to redistribute it\n"
								"under certain conditions. See the file COPYING for details.\n",
								msg,
								version);
				printf("usage: %s %s [-g pgrp] [-G gid] [-P ppid] [-s sid] [-t tty] [-u euid] [-U uid] [-?h] pattern\n", msg, sig);
				exit(2);
}
