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

#ifndef HAVE_MODULE_H
# define HAVE_MODULE_H

# include "default.h"

BEGIN_REDLIB_DECL

typedef int (*func_t)( void *, int);
# define F(X) "func" #X

typedef struct
{
				func_t open;
				func_t close;
				func_t read;
				func_t write;
				func_t cmp;
				func_t help;
								/* XXX:
								 * 		Although these following functions have been added
								 * for user defined additions, there is no guaranty that
								 * these will be inplace in later versions of this
								 * library.
								 * 		It is therefor advised that rather than implementing
								 * functions using these purposely undocumented parts of
								 * the library, one should contact the authors to ask
								 * if the function name could be added.
								 * 		Of course general function names are prefered,
								 * unless they can be created with the above functions.
								 * 	example:
								 * A getchar() like function could be created by writing
								 * a macro which requests only one char from read().
								 *
								 * TODO: dup()
								 * 		A dup function couple be added at a later state,
								 * but as all the information passed to the module is
								 * user accessable it would be easier for te user to
								 * call LOAD_MODULE() twice with the same values, rather
								 * than searching the module list.
								 */
				func_t func6;
				func_t func7;
				func_t func8;
				func_t func9;
# ifdef _REENTRANT
				pthread_mutex_t lock;
# endif /* _REENTRANT */
				char *name __attribute__ ((__aligned__(16)));
				void *handle;
} module;

# define NUM_MODULES num_modules
# define MAX_MODULES max_modules

/* return failures */
R_EXTERN int errmod;							/* 		this is used like errno with the
																 * function strerr_module(int)
																 * TODO:
																 * 		In later implementations this will
																 * be replaced with errno(3). Even then
																 * errmod and strerr_module will be retained
																 * to keep backwards compatibility.
																 */
# define EMOD_SUCCESS   0				/* (un)load successful */
# define EMOD_FAIL     -1				/* (un)load failed */
# define EMOD_LOCK     -2				/* (un)load failed no lock acquired */
# define EMOD_COUNT    -3				/* (un)load failed module count exceeded */

R_EXTERN void _init_module(void);
R_EXTERN void _fini_module(void);
R_EXTERN int load_module( const char *, int);
R_EXTERN int unload_module( const char *, int);
R_EXTERN const char *strerr_module( int);
R_EXTERN int search( const char *);		/* XXX: search()
															 * 		As the load_module function returns the
															 * entrypoint (-1) for the module, it would be
															 * senseless to write any qsort enabled search.
															 * 		The library itself doesn't use this
															 * function, as it uses an internal magic table
															 * to keep track of the loaded modules, although
															 * it keeps track of a lot more than just the
															 * names of the modules for debugging purposes.
															 * 		In a future release the search may be
															 * enabled with this magic table, luckily
															 * this has not been necessary as the average
															 * number of modules that are loaded are 3, plus
															 * one virtual module, in synchronous use and 5,
															 * plus one virtual module, asynchronously.
															 */

# ifdef __GNUC__
#  define replace_module(X,Y)	({	int ret;												\
																	int z = unload_module( X, Y);			\
																	if( z < 0) ret = z							\
																	else ret = load_module( X, Y);	\
																	ret;														\
																})
# else /* __GNUC__ */
#  define replace_module(X,Y)	unload_module( X); 					\
															load_module( X, Y);
# endif /* __GNUC__ */

R_EXTERN int module_default_symbol( void *, int) __attribute__ ((__weak__));

# define MODOPEN(X,Y)		(*list_module[X]->open)( X, Y)	/*  */
# define MODCLOSE(X,Y)	(*list_module[X]->close)( X, Y)	/*  */
# define MODREAD(X,Y)		(*list_module[X]->read)( X, Y)	/*  */
# define MODWRITE(X,Y)	(*list_module[X]->write)( X, Y)	/*  */
# define MODCMP(X,Y)		(*list_module[X]->cmp)( X, Y)		/*  */
# define MODHELP(X,Y)		(*list_module[X]->help)( X, Y)	/*  */


# ifdef DEBUG
#  define MODULE_DIR   "/usr/local/src/redlib/test"
# else /* DEBUG */
#  define MODULE_DIR   "/usr/local/redlib/module/"
# endif /* DEBUG */
R_EXTERN char *module_dir;				/* TODO:
																 * 		write function to check which dir
																 * to use, (mod=="")?mod:MOD
																 */

END_REDLIB_DECL

#endif /* HAVE_MODULE_H */
