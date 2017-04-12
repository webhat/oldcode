#define MEM_SAVE
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../include/file.h"
#include "../include/mem.h"

int main( int argc, char *argv[], char *envp[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				NEW_RFILE(file);
				char *str = calloc( 1, 4096);

				if(argc < 2) {
						printf("Usage: %s <file>\n", argv[0]);
						exit(-1);
				}

				file = ropen(argv[1], "r9");
				if( file == NULL)
				{
								printf( "Error (open): %s\n", strerror( errno));
								return -1;
				}

				if( rread( str, 1, 10, file) == -1)
				{
								printf( "Error (read): %s\n", strerror( errno));
								return -1;
				}

				printf( "'%s'\n", str);

				if( rclose( file))
				{
								printf( "Error (clos): %s\n", strerror( errno));
								return -1;
				}

				free( str);
				//free( file);

				return 0;
}
