
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

main()
{
	FILE *file;// = malloc( sizeof( FILE *));
	int fd = 0;

#if 0
	fd = open( "fopen_test_file", O_CREAT|O_RDWR| umask(644));

	if( fd == -1)
	{
					printf( "error: %s\n", strerror( errno));
					return;
	}

	printf( "%i\n", fd);

	file = fdopen( fd, "crw");

	write( fd, "p", 1);

	fflush( file);

	printf( "%i\n", fd);
#else /* 0 */
	file = fopen( "fopen_test_file", "crw");
#endif /* 0 */

//	fwrite( "m", 1, sizeof( const char *), file);

	fflush( file);


	while(1)
		printf("");
}
