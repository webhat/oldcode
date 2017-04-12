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
/* Last modified: Fri 04 Oct 2002 02:29:58 GMT
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <error.h>

# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

#include <redlib/mem.h>
#include <redlib/net.h>

#include "main.h"

extern const char version[];

static void __ATTRIB(__constructor__) _init()
{
		arg.idev = NULL;
		arg.odev = NULL;
		arg.type = 0;
		arg.host = NULL;
		arg.port = 0;
		arg.bind = 0;
		arg.verbose = 0;
}

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		signed short fd;
		int opt, option_index = 0, sz = sizeof(SAI);
		struct stat *dev_stat = xcalloc( 1, sizeof(struct stat));
		serv *(*func)(const char *,unsigned int) = NULL;
		serv *file	= xcalloc(1, sizeof(serv));
		serv *net;

		if(argc < 2)
				usage(argv[0]);

		while((opt = getopt_long( argc,
										argv,
										option_string,
										option_list,
										&option_index)
								) != -1) {
				switch(opt) {
						case 'b':
								if(optarg) {
										arg.idev = xcalloc(1, strlen(optarg)+1);
										strncpy(arg.idev, optarg, strlen(optarg));
										arg.odev = VIADUCTDEV_B;
										arg.type = VIADUCT_BLOCK;
										if(lstat(arg.idev, dev_stat)) {
												fprintf( stderr, "Error: %s\n", strerror(errno));
												FREE(arg.idev);
												FREE(dev_stat);
												exit(-1);
										}
										if(!S_ISBLK(dev_stat->st_mode)) {
												fprintf( stderr, "Error: File is not a block device\n");
												FREE(arg.idev);
												FREE(dev_stat);
												exit(-1);
										}
								}
								break;
						case 'c':
								if(optarg) {
										arg.idev = xcalloc(1, strlen(optarg)+1);
										strncpy(arg.idev, optarg, strlen(optarg));
										arg.odev = VIADUCTDEV_B;
										arg.type = VIADUCT_BLOCK;
										if(lstat(arg.idev, dev_stat)) {
												fprintf( stderr, "Error: %s\n", strerror(errno));
												FREE(arg.idev);
												FREE(dev_stat);
												exit(-1);
										}
										if(!S_ISCHR(dev_stat->st_mode)) {
												fprintf( stderr, "Error: File is not a character device\n");
												FREE(arg.idev);
												FREE(dev_stat);
												exit(-1);
										}
								}
								break;
						case 'h':
								if(optarg) {
										if(MAXHOSTNAMELEN < strlen(optarg)) {
												FREE(dev_stat);
												fprintf( stderr, "Error: %s is longer than %d\n", optarg, MAXHOSTNAMELEN);
												exit(-1);
										}
										arg.host = xcalloc(1, strlen(optarg)+1);
										strncpy(arg.host, optarg, strlen(optarg));
								}
								break;
						case 'p':
								if(optarg) {
										arg.port = strtol(optarg, (char **)NULL, 10);
								}
								break;
						case 'l':
								if(!arg.bind) {
										arg.bind++;
										func = rbind;
								}
								break;
						case 'u':
								fprintf( stderr, "Error: UDP not implemented\n");
								exit(-1);
								break;
						case 'v':
								arg.verbose++;
								break;
						case 0:
						default:
								usage(argv[0]);
				}
		}
		/* detach from terminal */
#if 0
		if(fork())
				exit(0);
#endif

		if(!arg.bind) {
				func = &rconnect;
				file->sock = open(arg.odev, O_RDWR|O_NOCTTY);
		} else {
				file->sock = open(arg.idev, O_RDWR|O_NOCTTY);
		}

		if((net = func(arg.host, arg.port)) <= 0) {
				fprintf( stderr, "Error: %s\n", strerror(errno));
				exit(-1);
		}


		if(getsockname( net->sock, (SA *) &net->sai, &sz) < 0) {
				fprintf( stderr, "Error: %s\n", strerror(errno));
				exit(-1);
		}

		if(arg.verbose > 0)
				fprintf( stdout, "connecting to: %s:%d\n",
								inet_ntoa(net->sai.sin_addr),
								ntohs(net->sai.sin_port));

		if(arg.bind) {
				while((fd = accept( net->sock, (SA *) &net->sai, &sz)) > 0) {
						if(!fork()) {
								char buf[2];
								memset(buf, 0x00, 2);
								while(read(fd, buf, 1)) {
										fprintf( stdout, "%s", buf);
								}
								close(fd);
						}
				}
				printf("Error: %s\n", strerror(errno));
		}

		FREE(arg.idev);
		FREE(dev_stat);
		return 0;
}

static void __ATTRIB(__noreturn__) usage(prog)
		const char *prog;
{
		int i;
		printf( "%s\nUsage : %s %s\n"
						"",
						version,
						prog,
						option_string
						);
		for(i = 0; i < sizeof(option_list) && option_list[i].name != NULL; i++)
				printf( "  --%s%s\t%s\n",
								option_list[i].name,
								option_list[i].has_arg?" <arg>\t":"\t",
								option_help[i].help);
		exit(-1);
}


