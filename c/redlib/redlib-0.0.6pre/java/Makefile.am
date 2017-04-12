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

SRC=CompressFileException.java CompressFile.java 
OBJ=CompressFileException.class CompressFile.class 
PACKAGE=redlib.RFILE.
CLASSDIR=classes
INCLUDEDIR=../include
CLASSPATH=.:$(CLASSDIR)
DIST_SOURCES=Makefile.am Makefile.in $(SRC)

all: $(CLASSDIR) $(OBJ)

$(CLASSDIR):
	mkdir -p $(CLASSDIR)

.java.class:
	$(JAVA_BIN)javac -classpath $(CLASSPATH) -d $(CLASSDIR) -O $<
	$(JAVA_BIN)javah -classpath $(CLASSPATH) -d $(INCLUDEDIR) -jni $(PACKAGE)`echo $@ |sed 's/\.class//'`

clean:
	rm -rf $(CLASSDIR)
	rm -f $(INCLUDEDIR)/redlib_RFILE_*.h core* hs_err_pid*

distclean: clean


