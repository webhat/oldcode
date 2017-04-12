SOURCES=trace.c writetrace.c register.c reverse.c insert_trace.c insert.c
OBJECTS=trace writetrace register reverse insert_trace insert
CFLAGS=-Wall -ggdb3 -Ilibdisasm_src-0.16/src/arch/i386/libdisasm/
LDFLAGS=-ldl -L. -ldisasm
CC=colorgcc-3.0.1

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)
