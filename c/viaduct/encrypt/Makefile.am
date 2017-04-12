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
# CVSVERSION: $Id: Makefile.am,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $

MAINT=@MAINT@
MAINTAINER_MODE_FALSE=@MAINTAINER_MODE_FALSE@
MAINTAINER_MODE_TRUE=@MAINTAINER_MODE_TRUE@

CFLAGS=@CFLAGS@ -Wall -I. -I..
LIBS=@LIBS@
PROGS = 
OBJS = encrypt.o
DIST_COMMON=COPYWRITE Makefile.in Makefile.am
SOURCES=encrypt.c

HOST=@host_os@

all: $(HOST) $(OBJS)

$(HOST):
	@case "$@" in \
		linux*) DFLAGS="-DLINUX -DDEBUG -DSERIAL"\
							;;\
		*) DFLAGS="-DDEBUG -DSERIAL"\
							;;\
	esac

encrypt.o: encrypt.c
	$(CC) -c $(CFLAGS) $(DFLAGS) -o $@ $<

clean:
	rm -f *.o core
