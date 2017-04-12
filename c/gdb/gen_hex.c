
main(argc, argv)
				int argc;
				char **argv;
{
				int i = 0;
				int j = 0;
				int k = 0;
				int l = 0;
				char *head = (char *) malloc(32);
				char *tail = (char *) malloc(32);
				char *outa = (char *) malloc(32);
				char *outb = (char *) malloc(32);
				char *outc = (char *) malloc(32);
				int cnt = 0;
				int start = 0;

				if( argc == 1)
								return;

				if( argc == 2)
				{
								start = 0;
								cnt = atoi(argv[1]);
				}

				if( argc == 3)
				{
								start = atoi(argv[1]);
								cnt = atoi(argv[2]);
				}

				if( argc > 3)
								return;

				for( i=start; i<=cnt; i++)
				{
#if 0
								printf("char *name%i = \"", i);
								printf("\\x00\\x00\\x00");
								if(i < 0x10)
												printf( "\\x0%x", i);
								else
												printf( "\\x%x", i);
								printf("\";\n");
#else /* 0 */
								sprintf( tail, "\";\n");
								if(i < 0x10)
												sprintf( outa,"\\x0%x", i);
								else
												sprintf( outa,"\\x%x", i);
								for( j=start; j<=cnt; j++)
								{
												if(j < 0x10)
																sprintf( outb,"\\x0%x", j);
												else
																sprintf( outb,"\\x%x", j);
												for( k=start; k<=cnt; k++)
												{
																if(k < 0x10)
																				sprintf( outc,"\\x0%x", k);
																else
																				sprintf( outc,"\\x%x", k);
																for( l=start; l<=cnt; l++)
																{
																				sprintf( head, "char *name_%i_%i_%i_%i = \"", i, j, k, l);
																				if(l < 0x10)
																								printf("%s%s%s%s\\x0%x%s", head, outa, outb, outc, l, tail);
																				else
																								printf("%s%s%s%s\\x%x%s", head, outa, outb, outc, l, tail);
																}
												}
								}
#endif /* 0 */
				}
}
