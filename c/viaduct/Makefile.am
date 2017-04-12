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

MAINT=@MAINT@
MAINTAINER_MODE_FALSE=@MAINTAINER_MODE_FALSE@
MAINTAINER_MODE_TRUE=@MAINTAINER_MODE_TRUE@

CFLAGS=@CFLAGS@ -Wall -I.
LIBS=@LIBS@
bin_PROGRAMS=viaduct
PROGS=viaduct
OBJS= main.o tap.o timer.o version.o popt.o
SOURCES=main.c popt.c tap.c test.c timer.c version.c.in config.h.in main.h tao.h headers.h
EXTRA_DIST=viaduct.spec man/man1/viaduct.1.bz2
DIST_COMMON=COPYWRITE Makefile.in Makefile.am AUTHORS COMMENTS COPYING \
						ChangeLog INSTALL NEWS README TODO VERSION aclocal.m4 config.guess \
						config.h.in config.sub configure configure.in install-sh missing \
						mkinstalldirs
SUBDIRS=serial cross socket encrypt docs
SUBOBJ=encrypt/encrypt.o cross/crossfun.o serial/serial.o socket/bind.o socket/getby.o
DISTDIR=@bindir@
MANDIR=@mandir@

SPEC_FILE=viaduct.spec

HOST=@host_os@

all: $(HOST) $(PROGS)

$(HOST):
	case "$@" in \
		linux*) DFLAGS="-DLINUX -DDEBUG -DSERIAL"\
							;;\
		*) DFLAGS="-DDEBUG -DSERIAL"\
							;;\
	esac

$(PROGS): $(OBJS)
	$(CC) -o $@ $^ $(SUBOBJ) $(LIBS) $(CFLAGS) $(DFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

timer.o: timer.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

tap.o: tap.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

popt.o: popt.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

version.c:
	cat $@.in | sed "s/VERSION/$(VERSION)/g" > $@

version.o: version.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

$(PACKAGE)-$(VERSION).tar.gz: dist

rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/RPM/SOURCES
	rpm -ba $(SPEC_FILE) # --sign

clean: 
	rm -f version.c *.o core

install: all
	$(INSTALL) -D --mode=755 --strip $(PROGS) $(DISTDIR)
	$(INSTALL) -D --mode=644 man/man1/viaduct.1.bz2 $(MANDIR)/man1/

rphh: $(MAINT) rpm
	$(MAINT) 	echo plaap

