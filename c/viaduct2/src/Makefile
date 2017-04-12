
CFLAGS=-Wall -ggdb3 -I../include/
LDFLAGS=
OBJ=main.o version.o /home/redhat/devel/c/redlib/src/net.o /home/redhat/devel/c/redlib/src/mem.o
CC=gcc

all: clean main

version.o: version.c
	$(CC) $(CFLAGS) $< -o $@ -c

main.o: main.c
	$(CC) $(CFLAGS) $< -o $@ -c

main: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

clean:
	rm -f core* *.o main

