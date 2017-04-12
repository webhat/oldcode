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
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>

#ifdef DEBUG
//  #include <assert.h>
#endif /* DEBUG */

/* Local includes: */
#include <global.h>
#include <config.h>

/* Variables */
char *list[65535];
int cntr;

/* Functions */
int write_pidlist();
int kill_pidlist( int sig);
int lookup_proc(char *name);
int testdir( char *name, char *file);
int testtype( char *name);

int lookup_proc( char *name) {
				int cnt = 0;
				char **tmp;
				DIR *directory;
				struct dirent *dir = malloc(512);

				cntr = 0;

				directory = opendir( "/proc/");

				while( (dir = readdir( directory)) ) {
								if( strtol( dir->d_name, tmp, 10))
												if( testdir( (char *) dir->d_name, name)) {
																cnt++;
																list[cnt] = (char *) malloc(64);
#ifdef DEBUG
# if 0
																assert(list[cnt] != NULL);
# endif /* 0 */
#endif /* DEBUG */
#ifdef DEBUG
																printf("%s(%d) :\n", name, type);
#endif /* DEBUG */
																if( type != f_not && !testtype(dir->d_name))
																				continue;
																strncpy( (char *) list[cnt],
																				dir->d_name,
																				8);
//																				sizeof( dir->d_name));
#ifndef PKILL
																if( cnt != 1)
																{
																				if( form ==0)
																				{
																								printf( "%s", delim );
																				}
																				else
																				{
																								if( !strstr( delim, " "))
																												printf( "%s", delim );
																				}
																}

																if( form == 1)
																				printf("%s ", name);
																printf( "%s", (char *) list[cnt]);
																if( form == 1)
																				printf("\n");
#endif /* PKILL */
																cntr = cnt;
												}
				}
				closedir( directory);

#ifndef PKILL
				if( form != 1)
								printf( "\n");
#endif /* PKILL */

				free(dir);

				return 0;
}

int testdir( char *name, char *file) {
				char *path = (char *) malloc(64);
				char *buf = (char *) malloc(64);
				char *hay = (char *) malloc(64);
				int fd;

				if( path == NULL || buf == NULL || hay == NULL)
								exit(3);

#ifdef DEBUG
				(void) printf( "/proc/%s/stat\n", name);
#endif /* DEBUG */
				(void) snprintf( path, 64, "/proc/%s/stat", name);
				fd = open( path, O_RDONLY);

				if( read( fd, buf, 64)) {
								sscanf( buf, "%*d %s %*s", hay);
#ifdef DEBUG
								(void) printf("%s\n", hay);
#endif /* DEBUG */
								if( strstr( hay, file) ) {
												close( fd);
												free( hay);
												free( buf);
												free( path);
											 	return 1;
								}
				}
				
				close( fd);
				free( hay);
				free( buf);
				free( path);
				return 0;
}


int testtype( char *name)
{
				char *path = malloc(64);
				char *buf = malloc(200);
				char *tmp = malloc(200);
				FILE *file = malloc( sizeof( FILE *));
				int fd;
				char *u1 = malloc(8), *u2 = malloc(8), *u3 = malloc(8), *u4 = malloc(8);

				if( type == f_not)
				{
								free( buf);
								free( tmp);
								free( path);
								free( file);
								return 0;
				}

#ifdef DEBUG
				printf("(%d)\n", type);
#endif /* DEBUG */

				if( type >= f_ppid) /* 
														 * /proc/%s/stat  < ppid pgrp session tty
														 */
				{
#ifdef DEBUG
								(void) printf( "/proc/%s/stat\n", name);
#endif /* DEBUG */
								(void) snprintf( path, 64, "/proc/%s/stat", name);
								fd = open( path, O_RDONLY);
								if( read( fd, buf, 64))
								{
												sscanf( buf, "%*d %*s %*c %s %s %s", u4, u1, tmp);
												sscanf( tmp, "%s %s", u2, buf);
												sscanf( buf, "%s %*s", u3);
												if( type == f_pgrp && atoi(u4) == got_id) /* 5 */
												{
#ifdef DEBUG
																printf("%s(%d) - %s:\n", name, type, u4);
#endif /* DEBUG */
																close( fd);
																free( buf);
																free( tmp);
																free( path);
																free( file);
																return 1;
												}
												if( type == f_pgrp && atoi(u1) == got_id) /* 7 */
												{
#ifdef DEBUG
																printf("%s(%d) - %s:\n", name, type, u1);
#endif /* DEBUG */
																close( fd);
																free( buf);
																free( tmp);
																free( path);
																free( file);
																return 1;
												}
												if( type == f_sid && atoi(u2) == got_id) /* 6 */
												{
#ifdef DEBUG
																printf("%s(%d) - %s:\n", name, type, u2);
#endif /* DEBUG */
																close( fd);
																free( buf);
																free( tmp);
																free( path);
																free( file);
																return 1;
												}
												if( type == f_tty && atoi(u3) == got_id) /* 8 */
												{
#ifdef DEBUG
																printf("%s(%d) - %s:\n", name, type, u3);
#endif /* DEBUG */
																close( fd);
																free( buf);
																free( tmp);
																free( path);
																free( file);
																return 1;
												}
								}
//enum id_types { f_not, f_uid, f_euid, f_pid, f_gid, f_ppid, f_sid, f_pgrp, f_tty} id_types;
#ifdef DEBUG
								printf("%s(%d) - %s|%s|%s|%s:\n", name, type, u1, u2, u3, u4);
#endif /* DEBUG */
								close( fd);
								free( buf);
								free( tmp);
								free( path);
								free( file);
								return 0;
				}

#ifdef DEBUG
				(void) printf( "/proc/%s/status\n", name);
#endif /* DEBUG */
				(void) snprintf( path, 64, "/proc/%s/status", name);
				file = fopen( path, "r");
				fgets( tmp, 40, file);
				fgets( tmp, 40, file);
				fgets( tmp, 40, file);
				if( type == f_pid)  /* 3 */
								sscanf( tmp, "Pid:\t%s\n", u1);
				fgets( tmp, 40, file);
				fgets( tmp, 40, file);
				if( type == f_uid || type == f_euid)  /* 1 || 2 */
								sscanf( tmp, "Uid:\t%s\t%s\t%s\t%s\n", u1, u2, u3, u4);
				fgets( tmp, 40, file);
				if( type == f_gid)  /* 4 */
								sscanf( tmp, "Gid:\t%s\t%s\t%s\t%s\n", u1, u2, u3, u4);

				if( atoi(u1) == got_id
												|| atoi(u2) == got_id
												|| atoi(u3) == got_id
												|| atoi(u4) == got_id)
				{
								printf("true: %s(%d) - %s|%s|%s|%s:\n", name, type, u1, u2, u3, u4);
								fclose( file);
								free( buf);
								free( tmp);
								free( path);
				/* FIXME: malloc error!!! */
//								free( file);
								return 1;
				}

				printf("fail: %s(%d) - %s|%s|%s|%s:\n", name, type, u1, u2, u3, u4);

				fclose( file);
				free( buf);
				free( tmp);
				free( path);
				/* FIXME: malloc error!!! */
//				free( file);
				return 0;
}

int write_pidlist( ) {
				return 0;
}

int kill_pidlist( int sig) {
					int pid;
				for( ; list[cntr] ; cntr --) {
								pid = atoi( list[cntr]);
#ifdef DEBUG
								printf("-%s-\n", list[cntr]);
#endif /* DEBUG */
								kill( pid, sig );
				}
				return 0;
}
