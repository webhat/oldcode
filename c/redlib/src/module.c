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

/* #define DEBUG */

/* don't forget to compile with -lbsd-compat*/
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

/* XXX:
 * 		The code, although marked reentrant everywhere, isn't
 * reentrant at all points. Although a lot of effort has been
 * put in to support reentrant code it may still fail for
 * reasons out of the control of this library.
 * 		For derivative code using this library, it is advised
 * that a threadpool, as implemented in another part of the
 * library, checks the individual threads. This because in
 * places where a none threaded application would abort(3)
 * or exit(3), pthread_exit(3) is called.
 */

/* TODO:
 * 		The reason that the module '0' isn't assigned is
 * because the whole module code is a virtual module
 * in list_modules[0].
 * 		This makes it possible to call through the normal
 * interface or through MODOPEN( 0, { "<module name>" } )
 * (FIXME: won't work!)
 */

#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#define R_EXTERN /* */
#include "module.h"

int errmod = 0;
char *module_dir = "";

static module **list_modules;
static int num_modules = 0;
static int max_modules = 10;

static const char *funcs[10] = {	"open",
																	"close",
																	"read",
																	"write",
																	"cmp",
																	"help",
																	F(6),			/* XXX: warning
																						 * 		The following creates
																						 * warnings when -Wtraditional
																						 * is set.
																						 * 'traditional C rejects
																						 * 				string concatenation'
																						 */
																	F(7),
																	F(8),
																	F(9)
};

int load_module( name, num)
				const char *name;
				int num;
{
				int			pos;
#ifdef _REENTRANT
				int			ret;
#endif /* _REENTRANT */
				char		*intr_name;

				/* fail if name is empty */
				if( name == NULL || name == "")
				{
#ifdef DEBUG
								fprintf( stderr, "Error: empty or (null) module name\n");
#endif /* DEBUG */
								errmod = EMOD_FAIL;
								return EMOD_FAIL;
				}

				/* fail if num exceeds MAX_MODULES */
				if( num >= MAX_MODULES || num > NUM_MODULES)
				{
#ifdef DEBUG
								fprintf( stderr, "Error: num exceeds maximum module count\n");
#endif /* DEBUG */
								errmod = EMOD_COUNT;
								return EMOD_COUNT;
				}

				/* replace old or new */
				if( num != 0)
								pos = num;
				else
								pos = NUM_MODULES;

				/* lock pos lock */
#ifdef _REENTRANT
				ret = pthread_mutex_trylock( &list_modules[pos]->lock);
				if( ret != 0)
				{
								if( ret == EBUSY)
								{
# ifdef DEBUG
												fprintf( stderr, "Error: mutex locked, try again later\n");
# endif /* DEBUG */
												errmod = EMOD_LOCK;
												return EMOD_LOCK;
								}  

								if( ret == EINVAL)
								{
												fprintf( stderr, "Failed: mutex not initialized\n");
# ifdef _REENTRANT
												pthread_exit( PTHREAD_CANCELED);
# else /* _REENTRANT */
												exit( EMOD_FAIL);
# endif /* _REENTRANT */
								}  
# ifdef DEBUG
								fprintf( stderr, "Error: unknown locking error\n");
# endif /* DEBUG */
								errmod = EMOD_LOCK;
								return EMOD_LOCK;
				}
#endif /* _REENTRANT */

				/* combine internal name */
				intr_name = calloc( 1,
												(((module_dir=="")?sizeof(MODULE_DIR):strlen(module_dir))
												 + sizeof( name)+ 4));
				if( intr_name == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}
				strncpy( intr_name,
												((module_dir=="")?MODULE_DIR:module_dir),
												((module_dir=="")?sizeof(MODULE_DIR):strlen(module_dir)));
				strncat( intr_name, "/", 1);
				strncat( intr_name, name, sizeof( name));
				strncat( intr_name, ".o", 2);

				/* actual loading of module */

				list_modules[pos]->handle = dlopen( intr_name, RTLD_NOW);
				if( list_modules[pos]->handle == NULL)
				{
#ifdef DEBUG
								fprintf( stderr, "Error: module (%s) not loaded '%s'\n", name, dlerror());
#endif /* DEBUG */
								free( intr_name);
#ifdef _REENTRANT
								ret = pthread_mutex_unlock( &list_modules[pos]->lock);
								if( ret != 0)
								{
# ifdef DEBUG
												fprintf( stderr, "Failed: mutex lost\n");
# endif /* DEBUG */
												pthread_exit( PTHREAD_CANCELED);
												/* exit( EMOD_FAIL); */
								}  
#endif /* _REENTRANT */
								errmod = EMOD_FAIL;
								return EMOD_FAIL;
				}

				list_modules[pos]->name = calloc( 1, sizeof( name));
				if( list_modules[pos]->name == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
												pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}

				strncpy( list_modules[pos]->name, name, sizeof( name));
				/* TODO: faking lambda
				 * 		There should be an easier way to do this, to make
				 * this neater. What I'd really like is to be able to
				 * forloop through the list, like I do with funcs[i].
				 * 		Perhaps a struct { int, func_t } would be good,
				 * or an internal map mod[0] to lmod[n]->open, mod[1] to
				 * lmod[n]->close, etc.
				 * 		Or linking the pointer:
				 * 				lmod[n]->open  to lmod->l[0]
				 * 				lmod[n]->close to lmod->l[1]
				 * 				etc...
				 */

				for( ; ; ) /* what no lambda dc: */
				{
								int			i = 0;
								char		*err;

								/* open */
								list_modules[pos]->open = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
												list_modules[pos]->open = module_default_symbol;
								}
								i++;

								/* close */
								list_modules[pos]->close = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
												list_modules[pos]->close = module_default_symbol;
								}
								i++;

								/* read */
								list_modules[pos]->read = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
												list_modules[pos]->read = module_default_symbol;
								}
								i++;

								/* write */
								list_modules[pos]->write = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
												list_modules[pos]->write = module_default_symbol;
								}
								i++;

								/* cmp */
								list_modules[pos]->cmp = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
												list_modules[pos]->cmp = module_default_symbol;
								}
								i++;

								/* help */
								list_modules[pos]->help = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
												list_modules[pos]->help = module_default_symbol;
								}
								i++;

								/* func6 */
								list_modules[pos]->func6 = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
#ifdef DEBUG
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
#endif /* DEBUG */
												list_modules[pos]->func6 = module_default_symbol;
								}
								i++;

								/* func7 */
								list_modules[pos]->func7 = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
#ifdef DEBUG
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
#endif /* DEBUG */
												list_modules[pos]->func7 = module_default_symbol;
								}
								i++;

								/* func8 */
								list_modules[pos]->func8 = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
#ifdef DEBUG
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
#endif /* DEBUG */
												list_modules[pos]->func8 = module_default_symbol;
								}
								i++;

								/* func9 */
								list_modules[pos]->func9 = (func_t) dlsym( list_modules[pos]->handle, funcs[i]);

								if( (err = dlerror()) != NULL)
								{
#ifdef DEBUG
												fprintf( stderr, "Error: module (%s) %s '%s'\n", name, funcs[i], err);
#endif /* DEBUG */
												list_modules[pos]->func9 = module_default_symbol;
								}

								break;
				}   

				/* unlock pos unlock */
#ifdef _REENTRANT
				ret = pthread_mutex_unlock( &list_modules[pos]->lock);
				if( ret != 0)
				{
								if( ret == EPERM)
								{
# ifdef DEBUG
												fprintf( stderr, "Error: permission denied\n");
# endif /* DEBUG */
												free( intr_name);
												errmod = EMOD_LOCK;
												return EMOD_LOCK;
								}

								if( ret == EINVAL)
								{
												fprintf( stderr, "Failed: mutex not initialized\n");
												free( intr_name);
#ifdef _REENTRANT
												pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
												exit( EMOD_FAIL);
#endif /* _REENTRANT */
								}
								free( intr_name);
								errmod = EMOD_LOCK;
								return EMOD_LOCK;
				}
#endif /* _REENTRANT */

				/* ready place for next module */
				/* TODO:
				 * 		The simple fact is that I don't check if the module count
				 * exceeded at this point. Although it isn't nice, an option
				 * should be available to load a final module in a naughty
				 * fashion.
				 * 		As you read above the first module 'list_modules[0]' is
				 * a reference to this virtual module. In init_module it is
				 * filled, with the correct code and the next place is inited.
				 * 
				 */

				/* old or new */
				if( num != 0)
								return 0;

				pos++;

				list_modules[pos] = calloc( 1, sizeof( module));
				if( list_modules[pos] == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
								free( intr_name);
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}
#ifdef _REENTRANT
				pthread_mutex_init( &list_modules[pos]->lock, NULL);
#endif /* _REENTRANT */

				free( intr_name);
				NUM_MODULES = pos;

				return (NUM_MODULES - 1);
}

int unload_module( name, num)
				const char *name;
				int num;
{
				char		*intr_name;
				char		*err;
				void		*handle;

				/* combine internal name */
				intr_name = calloc( 1,
												(((module_dir=="")?sizeof(MODULE_DIR):strlen(module_dir))
												 + sizeof( name)+ 4));
				if( intr_name == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}
				strncpy( intr_name,
												((module_dir=="")?MODULE_DIR:module_dir),
												((module_dir=="")?sizeof(MODULE_DIR):strlen(module_dir)));
				strncat( intr_name, "/", 1);
				strncat( intr_name, name, sizeof( name));
				strncat( intr_name, ".o", 2);

				/* actual unloading of module */
				/* TODO:
				 * 		Ok, so you've just seen the code below and thought:
				 * "That's cheating!" Well I'm sorry to say, it's faster
				 * than running code to init, sort, resort and search an
				 * internal magic table.
				 * 		True, it does mean that the memory isn't free'd,
				 * but as this is a maximum of 32 bytes you shouldn't
				 * worry.
				 */

				handle = dlopen( intr_name, RTLD_LAZY);
				if( handle == NULL)
				{
#ifdef DEBUG
								fprintf( stderr, "Error: module (%s) not loaded '%s'\n", name, dlerror());
#endif /* DEBUG */
								free( intr_name);
								errmod = EMOD_FAIL;
								return EMOD_FAIL;
				}

				dlclose( handle);
				if( (err = dlerror()) != NULL)
				{
#ifdef DEBUG
								fprintf( stderr, "Error: module(%s) unload failure '%s'\n", name, err);
#endif /* DEBUG */
								errmod = EMOD_FAIL;
								return EMOD_FAIL;
				}

				dlclose( handle);
				if( (err = dlerror()) != NULL)
				{
#ifdef DEBUG
								fprintf( stderr, "Error: module(%s) unload failure '%s'\n", name, err);
#endif /* DEBUG */
								errmod = EMOD_FAIL;
								return EMOD_FAIL;
				}
				return 0;
}

int module_default_symbol( y, x)
				int x;
				void *y;
{
#ifdef DEBUG
				fprintf( stderr, "Error: no symbol\n");
#endif /* DEBUG */
				return -1;
}

void _init_module() /* to be called from _init */
{
				list_modules = calloc( 1, sizeof( module));
				if( list_modules == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}

				list_modules[NUM_MODULES] = calloc( 1, sizeof( module));
				if( list_modules[NUM_MODULES] == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}

#ifdef _REENTRANT
				pthread_mutex_init( &list_modules[NUM_MODULES]->lock, NULL);
#endif /* _REENTRANT */

				list_modules[NUM_MODULES]->name = calloc( 1, 7);
				if( list_modules[NUM_MODULES]->name == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}

				strncpy( list_modules[NUM_MODULES]->name, "module", 6);

				list_modules[NUM_MODULES]->open  = (func_t) load_module;
				list_modules[NUM_MODULES]->close = (func_t) unload_module;
				list_modules[NUM_MODULES]->read  = module_default_symbol;
				list_modules[NUM_MODULES]->write = module_default_symbol;
				list_modules[NUM_MODULES]->cmp   = module_default_symbol;
				list_modules[NUM_MODULES]->help  = module_default_symbol;
				list_modules[NUM_MODULES]->func6 = module_default_symbol;
				list_modules[NUM_MODULES]->func7 = module_default_symbol;
				list_modules[NUM_MODULES]->func8 = module_default_symbol;
				list_modules[NUM_MODULES]->func9 = module_default_symbol;

				NUM_MODULES++;
				list_modules[NUM_MODULES] = calloc( 1, sizeof( module));
				if( list_modules[NUM_MODULES] == NULL)
				{
								fprintf( stderr, "Failed: %s\n", strerror( errno));
#ifdef _REENTRANT
								pthread_exit( PTHREAD_CANCELED);
#else /* _REENTRANT */
								exit( EMOD_FAIL);
#endif /* _REENTRANT */
				}
#ifdef _REENTRANT
				pthread_mutex_init( &list_modules[NUM_MODULES]->lock, NULL);
#endif /* _REENTRANT */
}

void _fini_module() /* to be called from _fini */
{
				int 	i;
				for( i = 0; i > NUM_MODULES; i++)
				{
								free( list_modules[i]->name);
								free( list_modules[i]);
				}
				free( list_modules);
}

const char *strerr_module( x)
				int 	x;
{
				if( x == EMOD_SUCCESS)
				{
								return "module: success";
				}
				if( x == EMOD_FAIL)
				{
								return "module: failed";
				}
				if( x == EMOD_LOCK)
				{
								return "module: failed to lock";
				}
				if( x == EMOD_COUNT)
				{
								return "module: count exceeded";
				}
				return "module: undefined error code";
}

int search( name)
				const char *name;
{
				int 	i;
				for( i = 0; i < NUM_MODULES; i++)
								if( !strcmp( list_modules[i]->name, name))
								{
												return i;
								}

				return EMOD_FAIL;
}

#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				_init_module();
				load_module("x", 0);
				load_module("c", 0);
				printf( "search(x) %d\n", search( "x"));
				(*list_modules[NUM_MODULES-1]->open)( NULL, 0);
				(*list_modules[NUM_MODULES-1]->func8)( NULL, 0);
				unload_module("x", 0);
				_fini_module();
				return 0;
}
#endif /* DEBUG */

