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
/* Last modified: Mon 20 Jan 2003 01:38:43 GMT
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
#define ERROR(X) do { \
										fprintf(stderr,"Error: %s `%s'\n",X,strerror(errno)); \
												return -1; \
								} while(0)


int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		HASHINFO tweak;
		DB *db;
		DBT idx;
		DBT fld;
		int x, flags = O_CREAT|O_RDWR;
		char filename[] = "testfile";

		/* TWEAK */
		memset((char*) &tweak, 0, sizeof(tweak));
		tweak.nelem = 4096;
		tweak.cachesize = (1024 * 1024);

		if((db = dbopen(filename,flags,0644,DB_HASH,&tweak)) == NULL)
				ERROR("open");

		if(db->sync(db,0) == -1)
				ERROR("sync");

		memset(&idx, 0, sizeof(idx));
		memset(&fld, 0, sizeof(fld));

		idx.data = calloc(1, 256);
		fld.data = calloc(1, 256);

		for(x = 0; x < 5; x++) {
				sprintf( (char*)idx.data, "index%d\0",x);
				sprintf( (char*)fld.data, "field%d\0",x);
				//fld.data = "field1\0";
				idx.size = strlen(idx.data)+1;
				fld.size = strlen(fld.data)+1;

				if(db->put(db,&idx,&fld,R_NOOVERWRITE) == -1)
						ERROR("put");
		}
		printf("PUT DONE...\n");


		//memset(&idx, 0, sizeof(idx));
		for(x = 0; x < 5; x++) {
				memset(&fld, 0, sizeof(fld));
				sprintf( (char*)idx.data, "index%d\0",x);
				idx.size = strlen(idx.data)+1;

				if(db->get(db,&idx,&fld,NULL) == -1)
						ERROR("get");
				printf("%s=%s\n",idx.data,fld.data);
		}
		printf("GET DONE...\n");

		FREE(fld.data);
		FREE(idx.data);

		if(db->close(db) == -1)
				ERROR("close");

		return 0;
}
