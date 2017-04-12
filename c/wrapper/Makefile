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

#CC=gcc-2.96
CC=gcc
CFLAGS+=-ggdb3 -Wall -ansi -pedantic
DFLAGS+=-D_REENTRANT 
LFLAGS+=-lbsd-compat -lmcheck
all: wrapper.o gzwrapper.o threadpool

gzwrapper.o: gzwrapper.c
	$(CC) -shared -O3 -fomit-frame-pointer $(LFLAGS) -ldl $(CFLAGS) -DWITH_ZLIB $(DFLAGS) -o $@ $<

wrapper.o: wrapper.c
	$(CC) -shared -O3 -fomit-frame-pointer $(LFLAGS) -ldl $(CFLAGS) $(DFLAGS) -o $@ $<

threadpool: threadpool.c
	$(CC) $(CFLAGS) $(LDFLAGS) -lpthread $(DFLAGS) -o $@ $< 

clean:
	rm -f wrapper.o gzwrapper.o threadpool core*
