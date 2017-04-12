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

/* fsync */
/* fcntl */
/* lseek */
/* seek */
/* flock */

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/types.h>
#include "wrapper.h"

#ifdef WITH_ZLIB
# define ZLIB_WHERE "/usr/lib/libz.so"
# define ZLIB_LVL	9
#endif /* WITH_ZLIB */

#ifdef DEBUG
#endif /* DEBUG */

/* FILE directives
 */

FILE *fopen( p, m)
				const char *p;
				const char *m;
{
				typedef FILE * (*type_t)( const char *, const char *);
				static FILE * (*external)(const char *, const char *);

/* ZEXTERN gzFile ZEXPORT gzopen  OF((const char *path, const char *mode)); */
				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( \"%s\", \"%s\")\n", external, __PRETTY_FUNCTION__, p, m);
#endif /* DEBUG */

				return external( p, m);
}

FILE *fdopen( fd, m)
				int fd;
				const char *m;
{
				typedef FILE * (*type_t)( int, const char *);
				static FILE * (*external)(int, const char *);

/* ZEXTERN gzFile ZEXPORT gzdopen  OF((int fd, const char *mode)); */
				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %i, \"%s\")\n", external, __PRETTY_FUNCTION__, fd, m);
#endif /* DEBUG */

				return external( fd, m);
}

FILE *freopen( p, m, s)
				const char *p;
				const char *m;
				FILE *s;
{
				typedef FILE * (*type_t)( const char *, const char *, FILE *);
				static FILE * (*external)(const char *, const char *, FILE *);

				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( \"%s\", \"%s\", %p)\n", external, __PRETTY_FUNCTION__, p, m, s);
#endif /* DEBUG */

				return external( p, m, s);
}

int fflush( s)
				FILE *s;
{
				typedef int (*type_t)( FILE *);
				static int (*external)(FILE *);

/* ZEXTERN int ZEXPORT    gzflush OF((gzFile file, int flush)); */
				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %p)\n", external, __PRETTY_FUNCTION__, s);
#endif /* DEBUG */

				return external( s);
}


size_t fread( ptr, sz, nm, s)
				void *ptr;
				size_t sz;
				size_t nm;
				FILE *s;
{
				typedef size_t (*type_t)( void *, size_t, size_t, FILE *);
				static size_t (*external)(void *, size_t, size_t, FILE *);

/* ZEXTERN int ZEXPORT    gzread  OF((gzFile file, voidp buf, unsigned len)); */
				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %p, %i, %i, %p)\n", external, __PRETTY_FUNCTION__, ptr, sz, nm, s);
#endif /* DEBUG */

				return external( ptr, sz, nm, s);
}

size_t fwrite( ptr, sz, nm, s)
				const void *ptr;
				size_t sz;
				size_t nm;
				FILE *s;
{
				typedef size_t (*type_t)( const void *, size_t, size_t, FILE *);
				static size_t (*external)(const void *, size_t, size_t, FILE *);

/* ZEXTERN int ZEXPORT    gzwrite OF((gzFile file, const voidp buf, unsigned len)); */
				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %p, %i, %i, %p)\n", external, __PRETTY_FUNCTION__, ptr, sz, nm, s);
#endif /* DEBUG */

				return external( ptr, sz, nm, s);
}

#if 1
int fclose( s)
				FILE *s;
{
				typedef int (*type_t)( FILE *);
				static int (*external)(FILE *);

				if( s == (void *)0x401162c0)
								printf("SIGSEV???");

/* ZEXTERN int ZEXPORT    gzclose OF((gzFile file)); */
				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %p)\n", external, __PRETTY_FUNCTION__, s);
#endif /* DEBUG */

				return external( s);
}
#endif

int open( pathname, flags, m)
				const char *pathname;
				int flags;
				mode_t m;
{
				typedef int (*type_t)( const char *, int, mode_t);
				static int (*external)(const char *, int, mode_t);

				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( \"%s\", \"%s\", %i)\n", external, __PRETTY_FUNCTION__, pathname, flags, m);
#endif /* DEBUG */

				/* TODO:
				 * 		Should mode_t be 0644? 'umask(022)'
				 */

				return external( pathname, flags, m);
}

size_t read( fd, buf, count)
				int fd;
				char *buf;
				size_t count;
{
				typedef size_t (*type_t)( int, char *, size_t);
				static size_t (*external)(int, char *, size_t);

				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %i, %s, %i)\n", external, __PRETTY_FUNCTION__, fd, buf, count);
#endif /* DEBUG */

				return external( fd, buf, count);
}

size_t write( fd, buf, count)
				int fd;
				char *buf;
				size_t count;
{
				typedef size_t (*type_t)( int, char *, size_t);
				static size_t (*external)(int, char *, size_t);

				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %i, %s, %i)\n", external, __PRETTY_FUNCTION__, fd, buf, count);
#endif /* DEBUG */

				return external( fd, buf, count);
}

int close( fd)
				int fd;
{
				typedef int (*type_t)( int);
				static int (*external)(int);

				external = (type_t) dlsym( ((void *) -1L), __PRETTY_FUNCTION__);

#ifdef DEBUG
				printf("\n[%p]: %s( %i)\n", external, __PRETTY_FUNCTION__, fd);
#endif /* DEBUG */

				return external( fd);
}

/* XXX: peter says:
 */
#if 0
static void * file_replace_handle = NULL;

int fclose( FILE * s) {
 char * error;
 int (*ext)( FILE *);
 if ( file_replace_handle == NULL) {
  fprintf( stderr, "No replacement module loaded!\n");
  exit(1);
 }
 ext = (int (*)( FILE *))dlsym( file_replace_handle, "fclose");
 if ( (error = dlerror()) != NULL) {
  fprintf( stderr, "%s\n", error);
  exit(1);
 }
 return ext( s);
}

int set_replace_module( const char * filename) {
 if ( file_replace_handle)
  dlclose( file_replace_handle);

 file_replace_handle = dlopen( filename, RTLD_LAZY);
 if ( file_replace_handle == NULL) {
  fprintf( stderr, "Failed to load module: %s\n", filename);
  exit(1);
 }

 return 0;
}
#endif /* 0 */
