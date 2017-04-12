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

/* CVSVERSION: $Id: serial.c,v 1.1.1.1 2000/07/14 20:24:34 webhat Exp $ */

#include <config.h>
#include <headers.h>

#ifdef SERIAL

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <term.h>

//#include <asm/termbits.h>
//#include <asm/termios.h>

#define TERMI struct termios

TERMI oldterm;

#endif /* SERIAL */

#define TRUE 1
#define FALSE 0

#define BAUDRATE 9600

//FIXME: Change all these functions; so they are compatible with the glibc
//	functions.

int start_serial ( int fd) {
#ifdef SERIAL

				TERMI newterm;

				tcgetattr( fd, &oldterm);
				bzero( &newterm, sizeof( newterm));

				newterm.c_cflag        = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
				newterm.c_iflag        = IGNPAR | ICRNL;
				newterm.c_oflag        = 0;
				newterm.c_lflag        = ICANON;
				newterm.c_cc[VINTR]    = 0;
				newterm.c_cc[VQUIT]    = 0;
				newterm.c_cc[VERASE]   = 0;
				newterm.c_cc[VKILL]    = 0;
				newterm.c_cc[VEOF]     = 4;
				newterm.c_cc[VTIME]    = 0;
				newterm.c_cc[VMIN]     = 1;
				newterm.c_cc[VSWTC]    = 0;
				newterm.c_cc[VSTART]   = 0;
				newterm.c_cc[VSTOP]    = 0;
				newterm.c_cc[VSUSP]    = 0;
				newterm.c_cc[VEOL]     = 0;
				newterm.c_cc[VREPRINT] = 0;
				newterm.c_cc[VDISCARD] = 0;
				newterm.c_cc[VWERASE]  = 0;
				newterm.c_cc[VLNEXT]   = 0;
				newterm.c_cc[VEOL2]    = 0;

				tcflush( fd, TCIFLUSH);
				tcsetattr( fd, TCSANOW, &newterm);

				return fd;
#else
				debug( 0, "No serial component installed");
				return 0;
#endif
}


/*
 * Put other functions in between here.
 */

void serial_write( int fd, char *in ) {
#ifdef SERIAL
				write( fd, &in, sizeof( in ));
#else
#endif /* SERIAL */
				return;
}

void serial_read( int fd, char *out ) {
				char buf[255];
				int res;
#ifdef SERIAL
				volatile int STOP=FALSE;

				bzero( &out, sizeof( out));

				while ( STOP == FALSE ) {
								res = read( fd, buf, 255);
								strncat( out, buf, res);
								if (buf[0]=='z') STOP=TRUE;
				}

#else
#endif /* SERIAL */
				return;
}

void serial_reset( int fd ) {
#ifdef SERIAL
				tcsetattr( fd, TCSANOW, &oldterm);
				close( fd );
#else
#endif /* SERIAL */
				return;
}
