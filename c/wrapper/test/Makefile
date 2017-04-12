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

CC=gcc
CFLAGS+=
DFLAGS+=
LFLAGS+=-lz

all: gz

gz: gz.c
	@if test -f gz; then \
		rm gz; \
	fi;
	$(CC) -Wall $< $(CFLAGS) $(DFLAGS) $(LFLAGS) -o $@ 

clean:
	rm gz

.PHONY: gz.o all clean
