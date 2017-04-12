/*
 *  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
/* $Id: $ */

/* TODO:
 *	This is supposed to become a thread pool.
 */

/* TODO:
 * 	Add defines for _GNU, _BSD & _SYSV...
 */

#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

typedef void (*routine)( void *);
typedef void (*sig_handle)( int);
void (*signal(int signum, void (*sighandler)(int)))(int);

typedef struct single_thread
{
				int no;								/* place in pool												*/
				routine function;
				void * arg;
				pthread_t *thread;
				pthread_mutex_t lock;
				int free;
} single_thread;

typedef struct function_stack function_stack;
struct function_stack {
				int accept;
				function_stack *next;
				routine function;
				pthread_mutex_t lock;
				void *arg;
};

extern void hangup_signal( int) __attribute__((__weak__));
void hangup_signal( signum)
				int signum;
{
				printf("Hangup signal: %d\n", signum);
}

extern void ignore_signal( int) __attribute__((__weak__));
void ignore_signal( signum)
				int signum;
{
				printf("Ignored signal: %d\n", signum);
}

extern void *wait_on_thread( void *) __attribute__((__noreturn__));
void *wait_on_thread( arg)
				void *arg;
{
				single_thread *cmd = (single_thread *) arg;
				pthread_mutex_init( &cmd->lock, NULL);
				pthread_mutex_lock( &cmd->lock);
				while(1)
				{
								printf( "Thread[%d] waiting for unlock\n", cmd->no);
								pthread_mutex_lock( &cmd->lock);
								cmd->free = 0;
								cmd->function( cmd->arg);
								cmd->free = 1;
				}
				pthread_exit( PTHREAD_CANCELED);
}

static single_thread **pool_single_thread;
static single_thread *stack_queue;
static function_stack *stack;
static function_stack *end;

static void *check_stack( void *arg) __attribute__((__noreturn__));
static void *check_stack( arg)
				void *arg;
{
				int i;
				while(1)
				{
								if( stack != NULL)
												if( stack != end)
																if( stack->accept == 1)
																{
																				function_stack *old;
																				old = stack;
																				old->next = NULL;
																				printf("%s\n", stack->arg);
																				for( i = 0; i < stack_queue->no; i++)
																				{
																								if( pool_single_thread[i]->free)
																								{
																												pool_single_thread[i]->function = stack->function;
																												pool_single_thread[i]->arg = stack->arg;
																								}
																				}
																				stack = stack->next;
																				free( old);
																}

				}
				pthread_exit( PTHREAD_CANCELED);
}

extern int init_pool( pthread_t **thread, int size);
int init_pool( thread, size)
				pthread_t **thread;
				int size;
{
				int i;

				errno = 0;

				/* stack */
				stack = ( function_stack *) malloc( sizeof( function_stack *));
				if( stack == NULL)
				{
								printf( "stack error in init_pool: `%s'\n", strerror( errno));
								exit(-1);
				}
				pthread_mutex_init( &stack->lock, NULL);
				stack->accept = 1;
				stack->next = NULL;
				end = stack;

				/* pool_single_thread */
				pool_single_thread = (single_thread **)calloc( 1, sizeof( single_thread));
				if( pool_single_thread == NULL)
				{
								printf( "Allocation error in init_pool: `%s'\n", strerror( errno));
								exit(-1);
				}

				printf( "Init %i thread(s)\n", size);
				for( i = 0; i < size; i++)
				{
								pool_single_thread[i] = (single_thread *)calloc( 1, sizeof( single_thread));
								if( pool_single_thread[i] == NULL)
								{
												printf( "Thread[%d] in init_pool: `%s'\n", i,strerror( errno));
												exit(-1);
								}
								/* XXX:
								 * 		Sometimes we coredump if we don't allocate thread,
								 * 	mostly we don't. Guess pthread_create doesn't allocate
								 * 	the space used by pthread_t.
								 */
								pool_single_thread[i]->thread = calloc( 1, sizeof( pthread_t));
								pool_single_thread[i]->no = i;
								pool_single_thread[i]->free = 1;
								if( pthread_create( pool_single_thread[i]->thread,
																				NULL,
																				wait_on_thread,
																				pool_single_thread[i])
									)
								{
												printf( "Thread[%d] in init_pool: `%s'\n", i,strerror( errno));
												exit(-1);
								}
#if (DEBUG==2)
								printf( "Thread[%d] created\n", i);
#endif /* (DEBUG==2) */
				}

				/* stack_queue */
				stack_queue = (single_thread *)calloc( 1, sizeof( single_thread));
				if( stack_queue == NULL)
				{
								printf( "stack_queue error in init_pool: `%s'\n", strerror( errno));
								exit(-1);
				}
				stack_queue->thread = calloc( 1, sizeof( pthread_t));
				stack_queue->free = 1;
				stack_queue->no = size;
				if( pthread_create( stack_queue->thread, NULL, check_stack, stack_queue))
				{
								printf( "stack_queue in init_pool: `%s'\n", strerror( errno));
								exit(-1);
				}

				return 0;
}

int queue( routine function, void *arg);
int queue( function, arg)
				routine function;
				void *arg;
{
				function_stack *new;

				while( end->next != NULL)
								end = end->next;

				end->next = (function_stack *) calloc( 1, sizeof( function_stack *));
				if( end->next == NULL)
				{
								printf("queue: %s\n", strerror( errno));
								exit( -1 );
				}
				printf( "%s\n", (char *)arg);
				new = end;
				end = end->next;
				end->next = NULL;
				end->accept = 0;

				pthread_mutex_init( &new->lock, NULL);
				new->function = function;
				new->arg = arg;
				new->accept = 1;

				return 0;
}


#if 1
void *test( arg)
				void *arg;
{
				printf( "test function: `%s'[%p]\n", (char *) arg, arg);
				return NULL;
}

int main( argc, argv)
				int argc;
				char *argv[];
{
				int no_thr;
				signal( SIGALRM, ignore_signal);
				signal( SIGQUIT, ignore_signal);
				signal( SIGINT, ignore_signal);
				signal( SIGTERM, ignore_signal);
				signal( SIGSTOP, ignore_signal);
				signal( SIGHUP, hangup_signal);
				init_pool( NULL, 6);
				queue( (routine) test, (char *) "a");
				queue( (routine) test, (char *) "b");
/*
				queue( (routine) test, (char *) "c");
				queue( (routine) test, (char *) "d");
				queue( (routine) test, (char *) "e");
				queue( (routine) test, (char *) "f");
				queue( (routine) test, (char *) "g");
				queue( (routine) test, (char *) "h");
				queue( (routine) test, (char *) "i");
				queue( (routine) test, (char *) "j");
				queue( (routine) test, (char *) "k");
				queue( (routine) test, (char *) "l");
 */
				no_thr = stack_queue->no;
				printf("no_thr: %i\n", no_thr);
				while(1);
				return 0;
}
#endif /* 0 */
#if 0
				end = ( function_stack *) malloc( sizeof( function_stack *));
				if( stack == NULL)
				{
								printf( "stack error in init_pool: `%s'\n", strerror( errno));
								exit(-1);
				}
				pthread_mutex_init( &end->lock, NULL);
				end->accept = 1;
				end->next = NULL;
#endif
