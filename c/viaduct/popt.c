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

/* CVSVERSION: $Id: popt.c,v 1.1.1.1 2000/07/14 20:22:57 webhat Exp $ */

/* This file contains the sorter for argv and returns a struct containing
 * the arguments for use.
 */

#include <config.h>
#include <headers.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// viaduct's headers
#include <socket/t_socket.h>
#include "tao.h"

#ifndef HAVE_LIBPOPT
	#undef POSIXLY_CORRECT
#else
#include <popt.h>
#endif /* HAVE_LIBPOPT */

#ifndef HAVE_LIBPOPT
#else
#endif /* HAVE_LIBPOPT */

char * tmp;

void process_args( int argc, char **argv, tao_opt *ret) {
				//FIXME: As a quick hack to fill in the destination, argv[argc -1] is
				//	access(2)ed to check if it's an existing file or integer. If it
				//	isn't then the entire popt is run to determine the nature of the
				//	dst.

				UINT op;
				int sorp = 0;
				char *temp = "";
				char **tmp = (char **) malloc(8);

				//if( ret->dst.addr.port->num ) {
				if( strtol( argv[argc -1], (char **) NULL , 10) && argc >= 2) {
//FIXME: This simple string copy should be replaced by a getby function.
								strcpy( ret->dst.addr.host->cmd, argv[argc -2]);
								ret->dst.addr.port->num = strtol( argv[argc -1], tmp, 10);
				} else if ( access( argv[argc -1], R_OK|W_OK|F_OK) > -1 &&
												!strstr( argv[argc -1], "viaduct")) {
								//strncpy( ret->dst.file, argv[argc -1], 254);
					//			ret->dst.file = "plaap";//argv[argc -1];
				} else {
								usage();
				}
				free( tmp);

#ifndef HAVE_LIBPOPT

				while ( (op = getopt ( argc, argv, "?haep:s:t:vV") ) != EOF )
								switch (op) {
												case '?':
												case 'h':
																usage();
																break;
												case 'a':
#ifdef DEBUG
																ret->verbose = 9;
#endif /* DEBUG */
												case 'v':
																ret->verbose++;
																break;
												case 'e':
																break;
												case 'p':
																sorp++;
//FIXME: This simple int copy should be replaced by strtol function.
																ret->src.addr.port->num = atoi( optarg);
																break;
												case 's':
																if( 1 <= sorp) {
//FIXME: This simple string copy should be replaced by a getby function.
																				strncpy( ret->src.addr.host->cmd,
																												optarg,
																											 	sizeof( optarg)	); 
																}
																strncpy( temp, optarg, sizeof( temp));
#ifdef DEBUG
																debug( 1, "chardev src");
#endif /* DEBUG */
																break;
												case 't':
#ifdef DEBUG
																debug( 9, "timer");
#endif /* DEBUG */
//FIXME: This simple int copy should be replaced by strtol function.
																ret->timeout = atoi( optarg);
																break;
												case 'V':
																fprintf( stdout, "%s\n", version); 
																exit(1);
												default:
																usage();
																break;
								}

#else
				static struct poptOption options[] = {
							 	{ NULL, '\0', 0, NULL, 0 },
								{ "destination", 'd', POPT_ARG_STRING, &tmp, 0, "Another", "dst"},
							 	{ NULL, '\0', 0, NULL, 0 }
				};
#endif /* HAVE_LIBPOPT */

				return;
}

