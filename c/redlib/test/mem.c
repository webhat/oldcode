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
/* Last modified: Wed 15 May 2002 01:39:18 GMT
 */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#include <redlib/mem.h>

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>

#define __MEMORY_AREA 2048
//#define DEBUG 1

#ifdef DEBUG
# include <sys/stat.h>
# include <fcntl.h>
#endif /* DEBUG */

static void _start(void)			__attribute__((__constructor__));
static void _end(void)				__attribute__((__destructor__));
void *rmalloc(size_t )				__attribute__((__malloc__));
void rfree(void *);

static void *_memory					__attribute__((__aligned__(__MEMORY_AREA),
																						 __section__("__redlibmem__"))) = NULL;
static struct {
				volatile unsigned long t __attribute__((__mode__(__pointer__)));
				volatile unsigned long o __attribute__((__mode__(__pointer__)));
				unsigned int  x:1;
} _list;

static size_t _memmap[__MEMORY_AREA];

static int _fd = 0;

void _start()
{
				int i;
#ifdef DEBUG
				_fd = open("/tmp/memorymap", O_CREAT|O_RDWR);
				if( _fd == -1)
				{
								fprintf( stderr, "Error _start: %s\n", strerror(errno));
								exit(-1);
				}  
#endif /* DEBUG */
#if 0
				if(!getuid() || !geteuid())
								_memory = mmap( NULL,
																(__MEMORY_AREA),
																PROT_READ|PROT_EXEC|PROT_WRITE,
#if !defined(DEBUG)
																MAP_ANONYMOUS|
#endif /* DEBUG */
																MAP_LOCKED|MAP_SHARED,
																_fd,
																0);
				else
#endif /* if 0 */
								/* TODO:
								 * 		There should be an option to make the heap
								 * not executable, to prevent heap-based overflows.
								 */
								_memory = mmap( NULL,
																(__MEMORY_AREA),
																PROT_READ|PROT_EXEC|PROT_WRITE,
#if !defined(DEBUG)
																MAP_ANONYMOUS|
#endif /* DEBUG */
																MAP_SHARED,
																_fd,
																0);

				if( (caddr_t)_memory == MAP_FAILED)
				{
								fprintf( stderr, "Error _start: %s\n", strerror(errno));
								exit(-1);
				}
				memset( _memory, 0x00, __MEMORY_AREA);
				for( i = 0; i < __MEMORY_AREA; i++)
				{
								_memmap[i] = 0UL;
				}   
				_list.t = (unsigned long)_memory;
				_list.o = (unsigned long)_memory + __MEMORY_AREA;
				_list.x = 0;

#ifdef DEBUG
				msync( _memory, __MEMORY_AREA, MS_SYNC);
#endif /* DEBUG */
}

void _end()
{
#ifdef DEBUG
				msync( _memory, __MEMORY_AREA, MS_SYNC);
#endif /* DEBUG */

				if( munmap( _memory, (__MEMORY_AREA + 1)))
				{
								fprintf( stderr, "Error _end: %s\n", strerror(errno));
#ifdef DEBUG
								close(_fd);
#endif /* DEBUG */
								_exit(-1);
				}
#ifdef DEBUG
				close(_fd);
#endif /* DEBUG */
}

void *rmalloc( size)
				size_t size;
{
#if defined(_POSIX_MAPPED_FILES)
				register void *ptr;
				size_t num = 0;

				if( (_list.t + size) < _list.o)
				{
								ptr = (void *)_list.t;
								_memmap[(unsigned int)(_list.t-(unsigned int)_memory)] = size;
								_list.t = (_list.t + size);
								return ptr;
				}

				if( _list.o == (unsigned long)_memory + __MEMORY_AREA)
								_list.t = (unsigned long)_memory;

				do {
								sleep(1);
								num = _memmap[(unsigned int)(_list.t-(unsigned int)_memory)];
								if( num )
								{
												_list.t = _list.t + num;
								}  
								else
								{
												_list.o = _list.t;
				do {
#ifdef DEBUG
								fprintf( stderr, "%d\n", (_list.o-(unsigned int)_memory));
#endif /* DEBUG */
								if((size-1) == (unsigned int)(_list.o-(unsigned long)_memory))
								{
												ptr = (void *)_list.t;
								_memmap[(unsigned int)(_list.t-(unsigned long)_memory)] = size;
												//_list.t = (_list.t + size);
												_list.t = (unsigned long)_memory;
												return ptr;
								}
				}     while( ++_list.o < (unsigned long)_memory + __MEMORY_AREA
				&& !_memmap[(unsigned int)(_list.o-(unsigned long)_memory)]);
												_list.t = _list.o;
												if( _list.o >= (unsigned long)_memory + __MEMORY_AREA)
												{
																_list.o == (unsigned long)_memory + __MEMORY_AREA;
																break;
												}
												num = size;
								}
				} while( num != 0);

				errno = ENOMEM;

				return NULL;
#else /* defined(_POSIX_MAPPED_FILES) */
				return xmalloc( size);
#endif /* defined(_POSIX_MAPPED_FILES) */
}

void rfree( ptr)
				void *ptr;
{
				if( ptr == NULL)
								return;
#if defined(_POSIX_MAPPED_FILES)
#if (DEBUG > 1)
				fprintf( stderr, "rfree: freed size = %d\n", _memmap[(unsigned int)(ptr-(unsigned long)_memory)]);
#endif /* DEBUG */
				memset( ptr, 0x00, _memmap[(unsigned int)(ptr-(unsigned long)_memory)]);
				_memmap[(unsigned int)(ptr-(unsigned long)_memory)] = (size_t) 0;
				return;
#else /* defined(_POSIX_MAPPED_FILES) */
				return xfree( ptr);
#endif /* defined(_POSIX_MAPPED_FILES) */
}

int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				char *p = rmalloc( 16);
				char *q = rmalloc( 2030);
				char *o;

				memset( p, 'p', 16);
				memset( q, 'q', 2030);

				strncpy( p, "12345678901234567890", 17);
				printf( "p = %s\nq = %s\n", p, q);

				rfree(p);

				o = rmalloc( 16);
				if( o == NULL)
				{
								fprintf( stderr, "Error main: %s\n", strerror(errno));
								printf( "WARNING: o == NULL\n");
				}
				memset( o, 'o', 16);
				rfree(o);

				p = rmalloc( 16);
				if( p == NULL)
				{
								fprintf( stderr, "Error main: %s\n", strerror(errno));
								printf( "WARNING: p == NULL\n");
				}

				printf( "p = %s\no = %s\n", p, o);

				return 0;
}

