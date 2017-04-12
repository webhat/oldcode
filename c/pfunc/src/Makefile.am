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
# CVSVERSION: $Id: Makefile.in,v 1.5 2000/03/06 10:10:13 webhat Exp $

VERSION=@VERSION@
PACKAGE=@PACKAGE@

CFLAGS=-Wall -ggdb3 -I. -I.. -I../include
DIST=@bindir@
INSTALL=@INSTALL@
LIBS=@LIBS@

PROGS = pgrep	pkill
OBJS = pgrep.o pids.o version.o
SUBOBJ = pkill.o pkids.o version.o
SOURCES= pfunc.c pids.c version.c

all: $(PROGS)

pgrep: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

pkill: $(SUBOBJ)
	$(CC) -o $@ $^ $(LIBS)

pkill.o: pfunc.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -DPKILL -o $@ $<

pgrep.o: pfunc.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -DPGREP -o $@ $<

pkids.o: pids.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -DPKILL -o $@ $<

pids.o: pids.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -DPGREP -o $@ $<

version.o: version.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -DVERSION="\"@VERSION@\"" -o $@ $<

install: all 
	sh ../mkinstalldirs $(DIST)
	@for prog in $(PROGS); do \
		$(INSTALL) --mode=755 --strip $$prog $(DIST)/; \
		echo $$prog; \
	done

clean: clean
	rm -f *.o core

