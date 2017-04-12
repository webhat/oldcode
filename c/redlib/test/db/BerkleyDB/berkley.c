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
/* Last modified: Fri 24 Jan 2003 03:13:08 GMT
 */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <db.h>
#include <BerkeleyDB/db.h>

#define FREE(X)			if((X)) { free((X)); (X) = NULL; }
#define ERROR(X,Y)	do { \
												db->err(db, (Y), (X)); \
												fprintf(stderr,"Error: %s `%s'(%d)\n",(X),db_strerror((Y)),(Y)); \
												fflush(file); \
												fclose(file); \
												exit(-1); \
										} while(0);


#define DBDIR "/home/redhat/devel/c/redlib/test/db/BerkleyDB/"

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		int ret = 0;
		DB *db;// = calloc(1, sizeof(DB_ENV));
		DBT index, value;
		FILE *file;

		DB_ENV *dbenv;// = calloc(1, sizeof(DB_ENV));

		if((ret = db_env_create(&dbenv, 0)))
				ERROR("DB env create",(ret));

		if((ret = db_create(&db, dbenv, 0)))
				ERROR("DB env create",(ret));

#if 0 /* DB_ENV */

		if((ret = dbenv->set_lg_dir(dbenv, "log")))
				ERROR("DB env log dir",(ret));

		if((ret = dbenv->set_data_dir(dbenv, "data")))
				ERROR("DB env data dir",(ret));

		if((ret = dbenv->set_tmp_dir(dbenv, "tmp")))
				ERROR("DB env tmp dir",(ret));

		if((ret = dbenv->open(db, DBDIR "dbs", DB_CREATE, 0664)))
				ERROR("DB env open",(ret));

//#else
		if((ret = db_create(&db, NULL, 0)))
				ERROR("DB env create",(ret));

#endif
		if((file = fopen("error.log","a+")) == NULL)
				ERROR("fopen", (errno));

		dbenv->set_errfile(dbenv,file);
		dbenv->set_errpfx(dbenv,"DBERROR");

		if((ret = db->open(db, DBDIR"database.db", NULL, DB_HASH, DB_CREATE, 0666)))
				ERROR("DB open",(ret));

		memset(&index,0,sizeof(index));
		memset(&value,0,sizeof(value));

		index.data = "index\0";
		index.size = sizeof("index\0");
		value.data = "value\0";
		value.size = sizeof("value\0");

		if((ret = db->put(db, NULL, &index, &value, DB_NOOVERWRITE)) == 0)
				printf("Stored: %s=%s\n", (char*)index.data, (char*)value.data);
		else {
				ERROR("DB put", (ret));
		}

/* CLOSE */
		if((ret = db->close(db, 0)))
				ERROR("DB close",(ret));

#if 0

		if((ret = dbenv->close(dbenv, 0)))
				ERROR("DB close",(ret));

#endif

		fflush(file);
		fclose(file);

		return 0;
}
