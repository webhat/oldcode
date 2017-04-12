
#  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# $Id: $

LIBS=@LIBS@
DIST_SOURCES=crypt.c curses.c db.c error.c file.c init.c mem.c misc.c module.c net.c shm.c sort.c test.c wrapper.c x11.c str.c java.c colour.c ptrace.c l18n.c qt.c
CFLAGS=-Wall -ggdb3 @CFLAGS@ -I. -I../include -I/usr/include -I.. -fPIC
DFLAGS=-D_REENTRANT -DREDLIB_SRC
LDFLAGS=-ldl -lbsd-compat -lpthread -lz -lbz2# -lc
LFLAGS=-shared -Wl,-soname,libred.so.0
TFLAGS=-nostdlib
OBJS=module.o mem.o curses.o crypt.o shm.o \
			sort.o wrapper.o error.o db.o file.o \
			misc.o net.o x11.o str.o qt.c\
			init.o java.o colour.o ptrace.o l18n.o
NAME=libred
PROG=$(NAME).so.0.0


all: $(OBJS) $(PROG) #clean

$(PROG): shared static
	@echo finished making $@

shared:
	$(CC) -o $(NAME).so.0.0 $(LDFLAGS) $(LFLAGS) $(TFLAGS) $(OBJS)
	ln -sf $(NAME).so.0.0 $(NAME).so.0
	ln -sf $(NAME).so.0 $(NAME).so

static:
	$(AR) cru $(NAME).a $(OBJS)
	$(RANLIB) $(NAME).a
	
crypt.o: crypt.c
	@if [ -z $(CERTIFIED_GNOMIE) ] ; then \
		DFLAGS+= -DCERTIFIED_GNOMIE ;       \
	fi
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) core*

distclean: clean
	rm -f $(NAME).*

.PHONY: all clean test shared static
