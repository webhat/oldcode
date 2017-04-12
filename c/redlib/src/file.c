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

/* TODO: todolist
 * -	rerror(): 
 * 				- ferror(FILE*)
 * 				- gzerror(gzFile,int*)
 * 				- BZ2bzerror(BZFILE*,int*)
 * - crypt: libmcrypt
 * 		/usr/local/doc/libmcrypt4-devel-2.4.15/example.c.gz
 */

/* #define DEBUG */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#if 1
# define MEM_SAVE
#else /* 0 */
# define NO_MEM_SAVE
#endif /* 0 */
#define R_EXTERN /* */
#include "file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* XXX: /usr/share/magic/magic
 * 		Thanks to the compilers of the magic file.
 */

/* TODO: file_types defines
 * 		I need to check if the system can modify the
 * file_type I want, otherwise it's useless compiling
 * them.
 * 		I also probably need to look at the checks
 * provided for, but unknown.
 */

#define TYPE(X,Y) { #X, #Y }

typedef struct
{
				const char *type __ATTRIB(__aligned__(16));
				const char *head __ATTRIB(__aligned__(16));
}
file_types;

file_types types[] =
{
				TYPE(none,\000\000),
				TYPE(pack,\037\036),		/* byte by byte */
				TYPE(gzip,\037\213),
				TYPE(freeze,\037\236),	/* frozen file 1.0 (or gzip 0.5) */
				TYPE(freeze,\037\237),	/* frozen file 2.1 */
				TYPE(compress,\037\240),		/* SCO compress -H (LZH) */
#if defined(__STRICT_ANSI__)
				TYPE(lzop,\x89\x4c\x5a\x4f\x00\x0d\x0a\x1a\x0a),
#else /* defined(__STRICT_ANSI__) */
				TYPE(lzop,0x89 0x4c 0x5a 0x4f 0x00 0x0d 0x0a 0x1a 0x0a),
#endif /* defined(__STRICT_ANSI__) */
																/* lzop compressed data */
				TYPE(bzip,BZ),					/* block-sorting file compressor */
				TYPE(bzip2,BZh),				/* block-sorting file compressor */
				TYPE(NULL,NULL)
};

/* XXX: mem save over ease of use I
 * 		Here a decision made was between a void ptr
 * or a struct containing all the types of file
 * compression struct. Whether it be void* (gz),
 * BZ_stream* (bz), FILE* (stdio), or any other.
 * 		The choice is plainly between usability and
 * memory space. So if that choice has to be made,
 * perhaps it would be wise for the user to make
 * that choice over the programmer.
 * 		continued in file.h
 */

static int file_type;

void _init_file()
{
				file_type = -1;
}


void _fini_file()
{
				return;
}


int get_file_type()
{
				return file_type;
}


int set_file_type( type)
				int type;
{
				file_type = type;

				return file_type;
}


int check_file_type( path)
				const char *path;
{
				int fd;

				if( (fd = open( path, O_RDONLY)) < 0)
								return RTYPE_FAIL;

				return check_fd( fd);
}

int check_fd( fd)
				int fd;
{
				int i = 0;
				char *buf;

				buf = calloc( 1, 2);
				if( read( fd, buf, 1) < 0)
				{
								close( fd);
								return RTYPE_FAIL;
				}

				switch( buf[0])
				{
								case '\000':
												close( fd);
												set_file_type( RTYPE_DEFAULT);
												return RTYPE_DEFAULT;
								case '\037':
												i = 1;
												break;
#if defined(__STRICT_ANSI__)
								case '\x89':
#else /* defined(__STRICT_ANSI__) */
								case (char)0x89:
#endif /* defined(__STRICT_ANSI__) */
												i = 2;
												break;
								case 'B':
												i = 4;
												break;
								default:
												close( fd);
												set_file_type( RTYPE_DEFAULT);
												return RTYPE_DEFAULT;
				}

				if( read( fd, buf, 1) < 0)
								return RTYPE_FAIL;

				switch( buf[0])
				{
								case '\036':
												close( fd);
												if( i == 1)
												{
																set_file_type( RTYPE_PACK);
																return RTYPE_PACK;
												}
												break;
								case '\213':
												close( fd);
												if( i == 1)
												{
																set_file_type( RTYPE_GZ);
																return RTYPE_GZ;
												}
												break;
								case '\236':
												close( fd);
												if( i == 1)
												{
																set_file_type( RTYPE_FREEZE);
																return RTYPE_FREEZE;
												}
												break;
								case '\237':
												close( fd);
												if( i == 1)
												{
																set_file_type( RTYPE_FREEZE2);
																return RTYPE_FREEZE2;
												}
												break;
								case '\240':
												close( fd);
												if( i == 1)
												{
																set_file_type( RTYPE_COMPRESS);
																return RTYPE_COMPRESS;
												}
												break;
#if defined(__STRICT_ANSI__)
								case '\x4c':
#else /* defined(__STRICT_ANSI__) */
								case (char)0x4c:
#endif /* defined(__STRICT_ANSI__) */
												close( fd);
												if( i == 2)
												{
																set_file_type( RTYPE_LZ);
																return RTYPE_LZ;
												}
												break;
								case 'Z':
												if( read( fd, buf, 1) < 0)
																return RTYPE_FAIL;
												close( fd);
												if( buf[0] == 'h')
												{
																set_file_type( RTYPE_BZ2);
																return RTYPE_BZ2;
												}
												set_file_type( RTYPE_BZ);
												return RTYPE_BZ;
												break;
								default:
												close( fd);
												set_file_type( RTYPE_DEFAULT);
												return RTYPE_DEFAULT;
				}
				return RTYPE_FAIL;
}


#if 0 /* RTYPE switch */
				switch( ft)
				{
								case RTYPE_FAIL:
												return NULL;
								case RTYPE_DEFAULT:
												break;
								case RTYPE_PACK:
								case RTYPE_GZ:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								case RTYPE_BZ:
								case RTYPE_BZ2:
								default:
				}
#endif /* 0 */


RFILE ropen( path, mode)
				const char *path;
				const char *mode;
{
				int ft = check_file_type( path);

				if( ft == RTYPE_FAIL)
								ft = get_file_type();

#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return NULL;
								case RTYPE_DEFAULT:
												return fopen( path, mode);
								case RTYPE_GZ:
												return gzopen( path, mode);
								case RTYPE_BZ2:
												return BZ2_bzopen( path, mode);
								case RTYPE_BZ:
												/* return BZ_bzopen( path, mode); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return NULL;
				}
#endif /* NO_MEM_SAVE */

				return NULL;
}


RFILE rdopen( fd, mode)
				int fd;
				const char *mode;
{
				int ft = check_fd( fd);

				if( ft == RTYPE_FAIL)
								ft = get_file_type();

#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return NULL;
								case RTYPE_DEFAULT:
												return fdopen( fd, mode);
								case RTYPE_GZ:
												return gzdopen( fd, mode);
								case RTYPE_BZ2:
												return BZ2_bzdopen( fd, mode);
								case RTYPE_BZ:
												/* return BZ_bzdopen( fd, mode); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return NULL;
				}
#endif /* NO_MEM_SAVE */

				return NULL;
}


RFILE rreopen( path, mode, stream)
				const char *path;
				const char *mode;
				RFILE stream;
{
				int ft = check_file_type( path);

				if( ft == RTYPE_FAIL)
								ft = get_file_type();

#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return NULL;
								case RTYPE_DEFAULT:
												return freopen( path, mode, stream);
								case RTYPE_GZ:
												gzclose( stream);
												stream = gzopen( path, mode);
												return stream;
								case RTYPE_BZ2:
												BZ2_bzclose( stream);
												stream = BZ2_bzopen( path, mode);
												return stream;
								case RTYPE_BZ:
												/* return BZ_bzopen( path, mode); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return NULL;
				}
#endif /* NO_MEM_SAVE */

				return NULL;
}


size_t rread( ptr, sz, nm, stream)
				void *ptr;
				size_t sz;
				size_t nm;
				RFILE stream;
{
				int ft __ATTRIB(__unused__) = get_file_type();
				
#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return 0;
								case RTYPE_DEFAULT:
												return fread( ptr, sz, nm, stream);
								case RTYPE_GZ:
												return gzread( stream, ptr, (sz * nm));
								case RTYPE_BZ2:
												return BZ2_bzread( stream, ptr, (sz * nm));
								case RTYPE_BZ:
												/* return BZ_bzread( stream, ptr, (sz * nm)); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return 0;
				}
#endif /* NO_MEM_SAVE */

				return 0;
}


size_t rwrite( ptr, sz, nm, stream)
				void *ptr;
				size_t sz;
				size_t nm;
				RFILE stream;
{
				int ft __ATTRIB(__unused__) = get_file_type();
				
#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return 0;
								case RTYPE_DEFAULT:
												return fwrite( ptr, sz, nm, stream);
								case RTYPE_GZ:
												return gzwrite( stream, ptr, (sz * nm));
								case RTYPE_BZ2:
												return BZ2_bzwrite( stream, ptr, (sz * nm));
								case RTYPE_BZ:
												/* return BZ_bzwrite( stream, ptr, (sz * nm)); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return 0;
				}
#endif /* NO_MEM_SAVE */

				return 0;
}


int rclose( stream)
				RFILE stream;
{
				int ft __ATTRIB(__unused__) = get_file_type();

#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return -1;
								case RTYPE_DEFAULT:
												return fclose( stream);
								case RTYPE_GZ:
												return gzclose( stream);
								case RTYPE_BZ2:
												BZ2_bzclose( stream);
												return 0;
								case RTYPE_BZ:
												/* return BZ_bzclose( stream); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return -1;
				}
#endif /* NO_MEM_SAVE */

				return -1;
}


int rflush( stream)
				RFILE stream;
{
				int ft __ATTRIB(__unused__) = get_file_type();

#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return EOF;
								case RTYPE_DEFAULT:
												return fflush( stream);
								case RTYPE_GZ:
												return gzflush( stream, Z_SYNC_FLUSH);
								case RTYPE_BZ2:
												return BZ2_bzflush( stream);
								case RTYPE_BZ:
												/* return BZ_bzflush( stream); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return EOF;
				}
#endif /* NO_MEM_SAVE */

				return EOF;
}

int reof( stream)
				RFILE stream;
{
				int ft __ATTRIB(__unused__) = get_file_type();

#ifndef NO_MEM_SAVE
				switch( ft)
				{
								case RTYPE_FAIL:
												return EOF;
								case RTYPE_DEFAULT:
												return feof( stream);
								case RTYPE_GZ:
												return gzeof( stream);
								case RTYPE_BZ2:
												/* return BZ2_bzeof( stream); */
								case RTYPE_BZ:
												/* return BZ_bzeof( stream); */
								case RTYPE_PACK:
								case RTYPE_FREEZE:
								case RTYPE_FREEZE2:
								case RTYPE_COMPRESS:
								case RTYPE_LZ:
								default:
												return 1;
				}
#endif /* NO_MEM_SAVE */

				return 1;
}


/* 
 * ferror
 * fileno
 */


#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				_init_file();
				_fini_file();
				return 0;
}
#endif /* DEBUG */

