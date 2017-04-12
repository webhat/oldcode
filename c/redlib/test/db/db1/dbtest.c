/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *   This program is free software; you can redistribute it and/or modify
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
/* Last modified: Mon 20 Jan 2003 00:44:55 GMT
 */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <db1/db.h>
#include <errno.h>

#define FREE(X) if(!X) { free(X); X = NULL; }

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		HASHINFO tweak;

		DBT *index = calloc(1, sizeof(DBT));
		DBT *field = calloc(1, sizeof(DBT));
		DBT *out = calloc(1, sizeof(DBT));
		DB *db;// = calloc(1, sizeof(DB));

		struct flock lock;
		int lock_fd = -1;
		const char filename[] = "testfile\0";
		int flags = O_CREAT|O_RDWR;

		if(argc < 2)
				return 0;

		/* TWEAK */
		memset((char*) &tweak, 0, sizeof(tweak));
		tweak.nelem = 4096;
		tweak.cachesize = (1024 * 1024);

#if 0
		if((lock_fd = open(filename, flags, 0644)) < 0) {
				printf("error (open)  : %s\n", strerror(errno));
				return -1;
		}

# if 1
		memset((char*) &lock, 0, sizeof(lock));
		lock.l_type = F_RDLCK|F_WRLCK;

		if(fcntl(lock_fd,F_SETLK,&lock) < 0) {
				printf("error (lock)  : %s\n", strerror(errno));
				return -1;
		}
# else
		if(flock(lock_fd,LOCK_SH) < 0) {
				printf("error (lock)  : %s\n", strerror(errno));
				return -1;
		}
# endif
#endif

		if((db = dbopen(filename, flags, 0644, DB_HASH, &tweak)) == NULL) {
				printf("error (dbopen): %s\n", strerror(errno));
				return -1;
		}

		if( db->sync(db,R_SETCURSOR) == -1)
				printf("error (sync)  : %s\n", strerror(errno));

#define LEN 6
		index->data = calloc(1,LEN);
		strncpy(index->data,"index\0",LEN);
		index->size = LEN;

		field->data = calloc(1,6);
		strncpy(field->data,"field\0",LEN);
		field->size = LEN;

		if( db->seq(db,index,field,R_NEXT) == -1)
				printf("error (seq)   : %s\n", strerror(errno));

		printf("index: `%s' %d\n", (char*)index->data, index->size);
		printf("field: `%s' %d\n", (char*)field->data, field->size);

		if( db->put(db,index,field,R_CURSOR) == -1)
				printf("error (put)   : %s\n", strerror(errno));

		printf("index: `%s' %d\n", (char*)index->data, index->size);
		printf("field: `%s' %d\n", (char*)field->data, field->size);

		FREE(field);

		if( db->get(db,index,out,R_CURSOR) == -1)
				printf("error (get)   : %s\n", strerror(errno));

		printf("index: `%s' %d\n", (char*)index->data, index->size);
		printf("out:   `%s' %d\n", (char*)out->data, out->size);

		FREE(out);
		FREE(index);

		if( db->sync(db,R_CURSOR) == -1)
				printf("error (sync)  : %s\n", strerror(errno));

		if(db->close(db) == -1)
				printf("error (close) : %s\n", strerror(errno));

		FREE(db);

		return 0;
}



