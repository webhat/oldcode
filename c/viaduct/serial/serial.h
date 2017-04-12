/*
    Copyright (C) 1997-2000  Daniel W. Crompton <redhat@rphh.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* CVSVERSION: $Id: serial.h,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

#ifdef HAVE_SERIAL_H
#include <config.h>
#include <headers.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <term.h>

#include <asm/termbits.h>
#include <asm/termios.h>

#define TERMI struct termios

#define HAVE_SERIAL_H
#endif /* HAVE_SERIAL_H */
