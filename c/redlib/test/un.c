#include <stdio.h>

typedef union { int i; char c; } __attribute__((__transparent_union__)) UN;

UN poekoe( UN x);

int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				union { int i; char c;} p;

				p.i = 73;

				printf( "%c\n", p.c);

				printf("%c\n", poekoe(74));
				
				return 0;
}

UN poekoe( x)
				UN x;
{
				return x;
}
