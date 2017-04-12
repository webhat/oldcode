#
#    Copyright (C) 1997-2000  Daniel W. Crompton <redhat@rphh.org>
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# CVSVERSION: $Id: $

CFLAGS=-Wall -ggdb3 -I. -I../include
DFLAGS=-D_REENTRANT
LDFLAGS=-L/usr/lib/ -ldl -lbsd-compat -lpthread -lform -lmenu -lpanel -lncurses #-lgpm
TFLAGS=-shared -nostdlib

all: clean gc #curses #x.o tester
	
tester: ../src/module.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(DFLAGS) -DDEBUG -o $@ $<

x.o: template.c
	$(CC) $(CFLAGS) $(TFLAGS) -o $@ $<

bz: bz.c
	@if test -f $@; then \
		rm -f $@; \
	fi;
	$(CC) -Wall $< $(CFLAGS) $(DFLAGS) $(LDFLAGS) -lbz2 -o $@ 

gz: gz.c
	@if test -f $@; then \
		rm -f $@; \
	fi;
	$(CC) -Wall $< $(CFLAGS) $(DFLAGS) $(LDFLAGS) -lz -o $@ 

curses: curses.c
	$(CC) -Wall $< $(CFLAGS) $(DFLAGS) $(LDFLAGS) -lz -o $@ 

gc: gc.c
	$(CC) -Wall $< $(CFLAGS) $(OPT) -o $@ 

clean:
	rm -f tester core* gz bz x.o config.* tja.c curses gc

.PHONY: gz.o all clean
