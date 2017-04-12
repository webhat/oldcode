
#include <stdio.h>

struct {
				signed int a:1;
				unsigned int b:1;
				unsigned int c:2;
} tmp;

int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				tmp.a = 0;
				printf("sint tmp.a = 0: %d\n", tmp.a);
				tmp.a = 1;
				printf("sint tmp.a = 1: %d\n", tmp.a);
				tmp.b = 0;
				printf("uint tmp.b = 0: %d\n", tmp.b);
				tmp.b = 1;
				printf("uint tmp.b = 1: %d\n", tmp.b);

				printf("\n");
				tmp.c = 0;
				printf("uint tmp.c = 0: %d\n", tmp.c);
				tmp.c = 1;
				printf("uint tmp.c = 1: %d\n", tmp.c);
				tmp.c = 2;
				printf("uint tmp.c = 2: %d\n", tmp.c);
				tmp.c = 3;
				printf("uint tmp.c = 3: %d\n", tmp.c);
				tmp.c = 4;
				printf("uint tmp.c = 4: %d\n", tmp.c);
				return 0;
}
