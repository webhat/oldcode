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
/* Last modified: Mon 23 Sep 2002 01:52:38 GMT
 */

#define DEBUG
#include "threadpool.h"

#include <time.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define error(X)		fprintf( stderr, "(error) %s\n", X)
#define ignore(X)		fprintf( stdout, "(ignore) %s\n", X)

typedef void (*runnable)( void *);

struct thread_item {
		int								active:2;
		runnable					function;
		void						 *arg;
		pthread_t				 *thread;
		pthread_mutex_t	 *l;
		thread_item			 *next;
};

void __attribute__((__constructor__)) _init_pool(void)
{
}

void __attribute__((__destructor__)) _fini_pool(void)
{
}

void __attribute__((__noreturn__)) *wait_on_interrupt(arg)
		void *arg;
{
		thread_item *this = (thread_item *) arg;

		while(!pthread_mutex_lock(this->l)) {
				this->active = 1;
				this->function(this);
				this->active = 0;
		}

		error("bail in thread");
		pthread_mutex_unlock(this->l);
		pthread_exit(PTHREAD_CANCELED);
}

thread_item *create_thread(thr)
		thread_item *thr;
{
		thread_item *new_thr;

		new_thr							= calloc( 1, sizeof(thread_item));
		new_thr->active			= 0;
		new_thr->function		= NULL;
		new_thr->thread			= calloc( 1, sizeof(pthread_t));
		new_thr->l					= calloc( 1, sizeof(pthread_mutex_t));
		new_thr->next				= NULL;

		pthread_mutex_init(new_thr->l, NULL);
		pthread_mutex_lock(new_thr->l);

		pthread_create(new_thr->thread, NULL, wait_on_interrupt, new_thr);

		if(thr != NULL)
				thr->next				= new_thr;
		else
				ignore("new pool");

		return new_thr;
}

int run_thr(thr,function,arg)
		thread_item	*thr;
		runnable		function;
		void			 *arg;
{
		if(!pthread_mutex_trylock(thr->l) && errno == EBUSY) {
				error("run: locked the thread, shouldn't happen.");
				return -1;
		}
		thr->function		= function;
		thr->arg				= arg;

		pthread_mutex_unlock(thr->l);
		return 0;
}

int run(thr,function,arg)
		thread_item	*thr;
		runnable		function;
		void			 *arg;
{
		int i = 0;
		thread_item *this;
		this = thr;

		do {
				printf("%3x: %d %p\n", ++i, this->active, this);
				if(this->active == 0) {
						error("X");
						break;
				}
				this = this->next;
		} while(this->next != NULL);
						
		return run_thr(this,function,arg);
}


#ifdef DEBUG
void *print_thread(arg)
		void *arg;
{
		printf("%d: ", (int)((thread_item*)arg)->arg);
		ignore("hehehe");
		sleep(2);
		ignore("end");
		return NULL;
}

void wait_on(void)
{
		pthread_mutex_t *l = calloc(1,sizeof(pthread_mutex_t));
		pthread_mutex_init(l, NULL);
		pthread_mutex_lock(l);
		pthread_mutex_lock(l);
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		thread_item *new	= create_thread(NULL);
		create_thread(
						create_thread(
								create_thread(new)
								)
						);

		run(new,print_thread,1);
		usleep(50000);
		run(new,print_thread,2);
		usleep(50000);
		run(new,print_thread,3);
		usleep(50000);
		run(new,print_thread,4);
		usleep(50000);
		run(new,print_thread,5);
		usleep(50000);
		run(new,print_thread,6);

		wait_on();

		return 0;
}
#endif /* DEBUG */
