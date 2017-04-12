/*
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

/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */
/* CVSVERSION: $Id: $ */

#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "timemgr.h"

#if 1 /*def DEBUG */
# define MALLOC_TRACE
# include <mcheck.h>
#endif /* DEBUG */

#define RCFILE ".timemgrrc"
/* #define RCFILE "/etc/timemgrrc" */
#define SHMKEY 0xfeef

#define EMPTY_JOB { NULL, 0, 0, 0 }
static job *jobs[] = EMPTY_JOB;
static int total_jobs;
#define SHMMEM(X) ( sizeof( job) * (X))


static void swap( void *, void *, int);
static void swap( o1, o2, sz)
				void *o1;
				void *o2;
				int sz;
{
				void *tmp = calloc( 1, sz);
				if( tmp == NULL)
				{
								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
								exit(-1);
				}


				memmove( tmp, o1, sz);
				memmove( o1, o2, sz);
				memmove( o2, tmp, sz);

				free( tmp);
}

int sort( job_list, sz)
				job *job_list[];
				int sz;
{
				int i;
				int f;
				int size = sz;
#ifdef DEBUG
				int cnt = 0;
#endif /* DEBUG */

				for( i = ((float)size/(float)2) +0.5, f = 0; size > 0; )
				{
#ifdef DEBUG
								cnt++;
								fprintf( stderr, "%s ? %s ", job_list[i]->job, job_list[f]->job);
#endif /* DEBUG */
								if( memcmp(job_list[i]->job, job_list[f]->job, 4) < 0)
								{
#ifdef DEBUG
												fprintf( stderr, "<\n");
#endif /* DEBUG */
												swap( job_list[i], job_list[f], sizeof( job *));
												continue;
								}
#ifdef DEBUG
								else
												fprintf( stderr, ">\n");
#endif /* DEBUG */
								f++;
								if( f >= size)
								{
#ifdef DEBUG
												fprintf( stderr,"%s\n", job_list[i]->job);
#endif /* DEBUG */
												swap( job_list[i], job_list[f-1], sizeof( job *));
												f = 0;
												size--;
												i = ((float)i/(float)2) +0.5;
								}
				}
#ifdef DEBUG
				fprintf( stderr,"iterations: %d\n", cnt);
#endif /* DEBUG */

				return 0;
}

int read_config()
{
				int i = 0;
				int b = 0;
				char c = '\0';
				FILE *file = malloc( sizeof( FILE *));
				char *buf = 0;
#ifdef DEBUG
				int cnt;
#endif /* DEBUG */
				
				if( file == NULL)
				{
								fprintf( stderr, "Error reading file: %s\n", strerror( errno));
								exit(-1);
				}

#if 0
				struct stat *st;
				st = calloc( 1, sizeof( struct stat *) +1);
				if( st == NULL)
				{
								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
								exit(-1);
				}

				if( stat( RCFILE, st))
				{
								fprintf( stderr, "Error reading file: %s\n", strerror( errno));
								exit(-1);
				}
				free( st);
#endif

				file = fopen( RCFILE, "r");
				if( file == NULL)
				{
								fprintf( stderr, "Error reading file: %s\n", strerror( errno));
								exit(-1);
				}

				/* jobs = calloc( 1, SHMMEM(1)); */
				
				while( (c = getc( file)) != EOF)
				{
								if( c == EOF)
												return 0;

#ifdef DEBUG
								fprintf( stderr,"%c", c);
#endif /* DEBUG */

								if( c == '\n')
								{
												if( b != 0)
												{
																buf[b] = '\0';
																if( !strcmp( "type", strsep( &buf, "=")))
																{
																				jobs[i] = calloc( 1, ( sizeof( job *)));
																				if( jobs[i] == NULL)
																				{
																								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
																								exit(-1);
																				}
																				jobs[i]->job = (char *)calloc( 1, (b + 1));
																				if( jobs[i]->job == NULL)
																				{
																								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
																								exit(-1);
																				}
																				strncpy( jobs[i]->job,
																												(char *) strsep( &buf, "="),
																												(b + 1));
#ifdef DEBUG
																				fprintf( stderr,"%s\n", jobs[i]->job);
#endif /* DEBUG */
																				jobs[i]->time =      (time_t)0;
																				jobs[i]->starttime = (time_t)0;
																				jobs[i]->stoptime =  (time_t)0;
																				i++;
																}
												}
												b = 0;
								}
								else
								{
												buf = (char *) realloc( buf, b + 1);
												buf[b++] = c;
								}
				}

				sort( jobs, i);
#ifdef DEBUG
				for(cnt = 0 ; cnt < i ; cnt++)										\
				{																									\
								fprintf( stderr,"%d: %s\n", cnt, jobs[cnt]->job);	\
				}
#endif /* DEBUG */ 

				total_jobs = i;

				return 0;
}


int save_config()
{
				int shmid = 0;
				struct shmid_ds *shm;
				void *shmptr;

				shmid = shmget( SHMKEY, SHMMEM(10), IPC_CREAT|O_RDWR);
				if( shmid <= 0)
				{
								fprintf( stderr, "Failed shmget: %s\n", strerror( errno));
								_exit(-1);
				}

				shm = calloc( 1, sizeof( struct shmid_ds*));
				if( shm == NULL)
				{
								fprintf( stderr, "Error: %s\n", strerror( errno));
								exit(-1);
				}

				if( shmctl( shmid, IPC_STAT, shm) == -1)
				{
								fprintf( stderr, "Failed shmctl STAT: %s\n", strerror( errno));
								_exit(-1);
				}

				shm->shm_perm.mode = 0660;
				
				if( shmctl( shmid, IPC_SET, shm) == -1)
				{
								fprintf( stderr, "Failed shmctl SET: %s\n", strerror( errno));
								exit(-1);
				}

				shmptr = shmat( shmid, 0, O_RDWR|SHM_RND);
				if( (int)shmptr == -1)
				{
								fprintf( stderr, "Failed shmat: %s\n", strerror( errno));
								exit(-1);
				}

				memcpy( shmptr, jobs, SHMMEM(10));

				shmdt( shmptr);

				return 0;
}

job *search( name, job_list, sz)
				const char *name;
				job *job_list[];
				int sz;
{
				int c, i;

				if( sz == 0)
				{
								return (job *) NULL;
				}
				else if( sz == 1)
				{
								return job_list[0];
				}

				for( i = (sz/2), c = 0; c < sizeof( name) && i > -1 && i < sz; )
				{
#ifdef DEBUG
								fprintf( stderr,"sz is %d\ni = %d\nc = %d\n", sz, i, c);
								/* XXX:	appended "x!"
								 * 		Here it seams that "x!" is appended to %s, this
								 * could be an unterminated char ptr.
								 * 		Looks solved, changed comment from fix to note.
								 *
								 * 		When X in SHMMEM(X) is large, iow >= 11 (???)
								 * the pointer for name is overwritten. Even though
								 * it is const. Not very ANSI of gcc, it will have
								 * to be compiled with:
								 * 		'-ansi -fno-writable-strings -Wwrite-strings'
								 * to enforce non-writable strings.
								 * 		Naughty gcc! That seems not to work, why doesn't
								 * memcpy enforce no-writeable-strings. It seems
								 * to ignore -fno-writable-strings and overwrite
								 * name.
								 */
								fprintf( stderr,"job is %s\n", job_list[i]->job);
#endif /* DEBUG */
								/* if( !memcmp(name, job_list[i]->job, c)) */
								if( name[c] == job_list[i]->job[c])
								{
												c++;
												continue;
								}
								/* else if( memcmp(name, job_list[i]->job, c) > 0) */
								else if( name[c] > job_list[i]->job[c])
												i = (i + ((float)i/(float)2) + 0.5);
								else
												i = (i - ((float)i/(float)2) - 0.5);

								c = 0;
				}

				if( i < 0 || i >= sz)
				{
#ifdef DEBUG
								fprintf( stderr,"Failed to find: %s\n", name);
#endif /* DEBUG */
								return NULL;
				}

#ifdef DEBUG
				fprintf( stderr,"ending\nsz is %d\ni = %d\nc = %d\n", sz, i, c);
				fprintf( stderr,"job is %s\n", job_list[i]->job);
#endif /* DEBUG */
				return job_list[i];
}

int update_time( const char *name);
int update_time( name)
				const char *name;
{
				int shmid = 0;
				void *shmptr;
				job *cur;
				time_t *t;
				job **tmpjobs;
				/* job *tmpjobs[] = EMPTY_JOB; */

				t = calloc( 1, sizeof(time_t));
				if( t == NULL)
				{
								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
								exit(-1);
				}  

				if( name == NULL || !strcmp( name, ""))
				{
								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
								exit(-1);
				}

				shmid = shmget( SHMKEY, SHMMEM(10), O_RDWR);
				if( shmid <= 0)
				{
								fprintf( stderr, "Failed shmget: %s\n", strerror( errno));
								exit(-1);
				}

				shmptr = shmat( shmid, 0, O_RDWR);
				if( (int)shmptr == -1)
				{
								fprintf( stderr, "Failed shmat in getmem: %s\n", strerror( errno));
								exit(-1);
				}

				tmpjobs = (job **) calloc( 10, SHMMEM(1));

				memcpy( tmpjobs, shmptr, SHMMEM(10));

#ifdef DEBUG
				fprintf( stderr,"%i\n", sizeof(tmpjobs)/sizeof(*tmpjobs));
				fprintf( stderr,"%s\n", tmpjobs[0]->job);
				fprintf( stderr,"%s\n", tmpjobs[1]->job);
				fprintf( stderr,"%s\n", tmpjobs[2]->job);
				fprintf( stderr,"%s\n", tmpjobs[3]->job);
#endif /* DEBUG */

				cur = search( name, tmpjobs, total_jobs);
				if( cur == NULL )
								return -1;

				cur->stoptime = time(t);
				cur->time = ( cur->stoptime - cur->starttime);
				printf("start: %ld\n", cur->starttime);

				/* FIXME: SIGSEGV here.
				 * 		I think that the sigsegv here is cause by the fact
				 * that I change cur->(val) without placing it back into
				 * shmptr. This would be a good reason for a sigsegv if
				 * you think about it.
				 * 		Ofcourse a misaligned or NULL pointer could also
				 * be a problem when loading this data.
				 *
				 * 		The following doesn't seem to fix it, so perhaps I
				 * should neatly place the cur pointer back into the list.
				 */

				memcpy( shmptr, tmpjobs, SHMMEM(10));

				shmdt( shmptr);

				free( tmpjobs);

				return 0;
}

int start_time( const char *name);
int start_time( name)
				const char *name;
{
				int shmid = 0;
				void *shmptr;
				job *cur;
				time_t *t;
				job **tmpjobs;
				/* job *tmpjobs[] = EMPTY_JOB; */

				t = calloc( 1, sizeof(time_t));
				if( t == NULL)
				{
								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
								exit(-1);
				}  

				if( name == NULL || !strcmp( name, ""))
				{
								fprintf( stderr, "Error: %s\n", strerror( EBADMSG));
								exit(-1);
				}

				shmid = shmget( SHMKEY, SHMMEM(10), O_RDWR);
				if( shmid == -1)
				{
								fprintf( stderr, "Failed shmget: %s\n", strerror( errno));
								exit(-1);
				}

				shmptr = shmat( shmid, 0, O_RDWR);
				if( (int)shmptr == -1)
				{
								fprintf( stderr, "Failed shmat in getmem: %s\n", strerror( errno));
								exit(-1);
				}

				tmpjobs = (job **) calloc( 10, SHMMEM(1));

				memcpy( tmpjobs, shmptr, SHMMEM(10));

				cur = search( name, tmpjobs, total_jobs);
				if( cur == NULL )
								return -1;

				cur->starttime = time(t);

				memcpy( shmptr, tmpjobs, SHMMEM(10));

				shmdt( shmptr);

				free( tmpjobs);

				return 0;
}


int get_info(void);
int get_info()
{
				int i;
				int shmid = 0;
				void *shmptr;
				job **tmpjobs;
				job *cur;

				shmid = shmget( SHMKEY, SHMMEM(10), O_RDONLY);
				if( shmid == -1)
				{
								fprintf( stderr, "Failed shmget: %s\n", strerror( errno));
								exit(-1);
				}

				shmptr = shmat( shmid, 0, O_RDWR);
				if( (int)shmptr == -1)
				{
								fprintf( stderr, "Failed shmat in getmem: %s\n", strerror( errno));
								exit(-1);
				}

				/* tmpjobs = (job **) calloc( 10, SHMMEM(1)); */

				tmpjobs = (job **) calloc( 10, SHMMEM(1));

				memcpy( tmpjobs, shmptr, SHMMEM(10));

				for( i = 0; i < total_jobs; i++)
				{
								/* FIXME:
								 * 		Currently breaks here!
								 */

#if 0
								fprintf( stderr, "%d: %s\n", i, tmpjobs[i]->job);
#else /* 0 */
								struct tm *timeptr;
								time_t *t = calloc( 1, sizeof( time_t *));
								cur = tmpjobs[i];
								*t = cur->time;
								timeptr = gmtime( t);
								fprintf( stderr,"project:\t%s\t\t%02d:%02d:%02d\n",	\
																cur->job,							\
																timeptr->tm_hour,			\
																timeptr->tm_min,			\
																timeptr->tm_sec);
#endif
				}

				memcpy( shmptr, tmpjobs, SHMMEM(10));

				shmdt( shmptr);

				return 0;
}

#ifdef DEBUG
static void die( int) __attribute__ ((__noreturn__,__unused__));
static void die( x)
				int x;
{
				abort();
}
#endif /* DEBUG */

int main( int argc, char * argv[]);
int main( argc, argv)
				int argc;
				char * argv[];
{
				const char name[] = "home";
#ifdef DEBUG
#if 0
				mcheck(die);
				name = calloc( 1, 20);				/* temp */
				strncpy( name, "home\0", 5);
#else
				mcheck(0);
#endif /* 0 */
				mtrace();
#endif /* DEBUG */


				read_config();
				save_config();
				start_time( name);
				sleep(10);
				update_time( name);
				get_info();

#ifdef DEBUG
				muntrace();
#endif /* DEBUG */

				_exit(0);
				return 0;
}

