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
PROGS= 
OBJS=
TEX= plaap
MAN= viaduct.1
DIST_COMMON=Makefile.am ethertap.html Makefile.in plaap.tex viaduct.1 viaduct.1.bz2

HOST=@host_os@

all: $(MAN) doc

dvi:
	@for texfile in $(TEX); do \
		tex $$texfile; \
	done

ps:
	@for texfile in $(TEX); do \
		dvips $$texfile; \
	done

doc: dvi ps

$(MAN):
	@for manfile in $(MAN); do \
		if [ -f /usr/bin/bzip2 ]; then \
			bzip2 $$manfile.bz2 \
			bunzip2 -c < ../man/man1/$$manfile.bz2 |groff -man > $$manfile.ps; \
		fi \
	done

clean:
	rm -f *.o core
	@for texfile in $(TEX); do \
		rm -f $$texfile.log; \
		rm -f $$texfile.dvi; \
		rm -f $$texfile.ps; \
	done;

.PHONY: viaduct.1.bz2
