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

#ifndef HAVE_TAO_SOCKET_H
#define HAVE_TAO_SOCKET_H

#define USHORT unsigned short

#include <config.h>
#include <headers.h>

#ifndef HAVE_V_SOCK_H
  #include <socket/v_sock.h>
  #define HAVE_V_SOCK_H
#endif /* HAVE_V_SOCK_H */

struct tao_host {
	char cmd[15];
  char name[MAXHOSTNAMELEN];
  char addrs[8][24];
  struct in_addr iaddrs[8];
};
#define THOST struct tao_host

struct tao_port {
  char name[64];
  char anum[8];
  USHORT num;
};
#define TPORT struct tao_port

/* STOLEN FROM NETCAT */

/* Hmalloc :
   malloc up what I want, rounded up to *4, and pre-zeroed.  Either succeeds
   or bails out on its own, so that callers don't have to worry about it. */
/*
char * Hmalloc (size)
  unsigned int size;
{
  unsigned int s = (size + 4) & 0xfffffffc;
  char * p = malloc (s);
  if (p != NULL)
    memset (p, 0, s);
  else
    broke ("Hmalloc failed");
  return (p);
} */ /* Hmalloc */


#endif /* HAVE_TAO_SOCKET_H */
