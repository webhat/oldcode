#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if 1
typedef struct
{
				char *f __attribute__((__aligned__(16)));
				char *s __attribute__((__aligned__(16)));
				char *t __attribute__((__aligned__(16)));
} it;
#else
typedef struct
{
				char f[16];
				char s[16];
				char t[16];
} it;
#endif

int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				it *tmp = calloc( 1, sizeof( it));
				int i;
				void *ptr;
				ptr = tmp;
#if 1
				tmp->f = calloc( 1, sizeof( 16));
				tmp->s = calloc( 1, sizeof( 16));
				tmp->t = calloc( 1, sizeof( 16));
#endif

				strcpy( tmp->f, "A");
				strcpy( tmp->s, "B");
				strcpy( tmp->t, "C");

				for( i = 0; i < 19 ; i++ )
				{
								printf( "%s\n", *(tmp++));
				}


				return 0;
}
