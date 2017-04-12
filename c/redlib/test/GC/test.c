
#include <stdio.h>
#include <linux/linkage.h>

static unsigned long sp_ptr = 0L;

static void __init(void) __attribute__((constructor));

extern asmlinkage void alloc_stub();

asmlinkage unsigned int poekoe(unsigned long);
int plaap();
int boelie();

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		printf("%p=%p\n", *poekoe, printf);
		boelie();
		printf("end\n");

		return 0;
}

asmlinkage unsigned int poekoe(unsigned long i) {
		printf("%s\n",__PRETTY_FUNCTION__);
		if(i)	asm volatile(
						".globl alloc_stub  \n"
						".align 4,0x90      \n"
						"pop  %esp          \n"
						"mov  %ebp,     %esp\n"
						"pop  %ebp          \n"
						);
}

int plaap() {
		int i = 10;
		i=i;
		printf("%s\n",__PRETTY_FUNCTION__);
		return 0;
}

static void __init(void) {
		/*
		asm volatile (
						"movl   $poekoe,      %%eax\n"
						"push   $0x00000000        \n"
						"call   *%%eax             \n"
						"sub    $0x18,        %%ebp\n"
						"movl   %%ebp,        %%eax\n"
						"add    $0x18,        %%ebp\n"
						: "=p" (sp_ptr)
						: // empty
						);
		printf("I:%p\n", (void*)sp_ptr);
		/*  */
}

/*
 * 0x8048500 <boelie>:     push   %ebp
 * 0x8048501 <boelie+1>:   mov    %esp,%ebp
 * 0x8048503 <boelie+3>:   mov    $0x0,%eax
 * 0x8048508 <boelie+8>:   pop    %ebp
 * 0x8048509 <boelie+9>:   ret
 */

/*
 * call   0x8048520
 * 0xe8 0x9c 0xfe 0xff 0xff
 *
 * ret
 * 0xc3
 */

char str[] = "%p=%p\n";//\xc3";

int boelie() {
		unsigned long bp = 0L;
		asm volatile (
	//		 "mov    $0x0,         %%eax\n"
	//		 "pop    %%eax              \n"
	//		 "sub    $0x4,         %%esp\n"
				 "movl   $poekoe,  -4(%%ebp)\n"
	//		 "push   -4(%%ebp)          \n"
	//		 "push   %%esp              \n"
				 "mov    -4(%%ebp),    %%eax\n"
				 "push   $0x00000001        \n"
				 "call   *%%eax             \n"
				 "push   %%ebp              \n"
				 "sub    $0x08,        %%ebp\n"

			/********************************
			 * printf(str, %ebp, -4(%%ebp)) *
			 ********************************/
	//		 "push   -4(%%ebp)          \n"
	//		 "push   %%ebp              \n"
	//		 "push   $str               \n"
	//		 "call   0x804833c          \n"

	//		 "mov    $0x0,         %%eax\n"
				 "mov    %%ebp,        %%esp\n"
				 "mov    %%ebp,        %%eax\n"
	//		 "add    $0x08,        %%esp\n"  /* uncommented the following lines */
	//		 "pop    %%ebp              \n"  /* ignore the 2nd call to $poekoe */
	//		 "int    $0x03              \n"  /* interrupt (breakpoint trap) */
				 "                          \n"
				: "=p" (bp)/* empty */
				: //"a" (&poekoe)
		);
		printf("X:%p\n", (void*)bp);
}

