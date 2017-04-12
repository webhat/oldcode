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

/* CVSVERSION: $Id: timer.c,v 1.1.1.1 2000/07/14 20:13:45 webhat Exp $ */

#include <config.h>
#include <headers.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#ifndef _MIT_POSIX_THREADS
	/* Added by punisher */
	#include <bits/pthreadtypes.h>
	#include <sched.h>
	#include <pthread.h>
	#include <unistd.h>
	#define _MIT_POSIX_THREADS
#endif /* _MIT_POSIX_THREADS */

char *debugmsg;

void test( void * args );

extern int debug( int lvl, char* body);

int timer ( int interval ) {
				struct timespec tv;
				struct __sched_param shed;

				size_t i = 8;
				char threads[i];

				pthread_t *thr = 0;
				pthread_attr_t thread;

				shed.sched_priority = 1;
				pthread_attr_init( &thread);

				thread.__detachstate = 1;
				thread.__schedpolicy = 1;
				thread.__schedparam = shed;
				thread.__inheritsched = 1;
				thread.__scope = 1;
				thread.__guardsize = (size_t) 1;
				thread.__stackaddr_set = 1;
				thread.__stacksize = (size_t) 1;
			

#ifndef DEBUG
				for( i=i ; i <= 0; i--) {
#endif /* DEBUG */
								threads[i] = pthread_create( thr, 
																&thread,
																(void *) test,
																NULL );
#ifndef DEBUG
				}
#endif /* DEBUG */

#ifdef DEBUG
				debugmsg = "interval set";
				debug ( 9, debugmsg);
#endif /* DEBUG */

				tv.tv_sec = interval;
				tv.tv_nsec = 0;

				nanosleep( &tv, NULL);

				return 0;
}

void test( void * args ) {
				debug( 9,"thread created");
				fork();
				pthread_exit( NULL );
				return; // NULL;
}



