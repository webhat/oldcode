
main(argc, argv)
				int argc;
				char **argv;
{
				unsigned int i = 0;
				int cnt;

				if(argc != 2)
								return;

				cnt=atoi(argv[1]);

				for( i=0; i<cnt; i++)
								printf("echo disas \ndisas name%i\n", i);
				printf("quit\n");
}
