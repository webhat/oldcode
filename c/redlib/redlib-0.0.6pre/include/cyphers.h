/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */
/*
 *  This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
/* Last modified: Fri 19 Apr 2002 17:00:10 GMT
 */
/* CVSVERSION: $Id: $ */

#ifndef HAVE_CYPHERS_H
# define HAVE_CYPHERS_H

/* cypher */
# define TDES 0x01
# define TWAY 0x02
# define ARCFOUR 0x03
# define RC4 0x03
# define BLOWFISH 0x04
# define CAST 0x05
# define DES 0x06
# define ENIGMA 0x07
# define GOST 0x08
/* # define non 0x09 */
# define IDEA 0x0a
# define LOKI97 0x0b
# define MARS 0x0c
# define PANAMA 0x0d
# define RC2 0x0e
/* # define non 0x0f */
# define RC5 0x10
# define RC6 0x11
# define RIJNDAEL 0x12
# define SAFER 0x13
# define SAFERP 0x14
# define SERPENT 0x15
# define SKIPJACK 0x16
# define TWOFISH 0x17
# define WAKE 0x18
# define XTEA 0x19
# define DEFAULT_CYPHER RIJNDAEL

/* blocks */
# define STREAM 0x81
# define ECB 0x82
# define CBC 0x83
# define CFB 0x84
# define OFB 0x85
# define nOFB 0x86
# define NOFB 0x86

/* public/private */
# define DH 0xa1
# define DSA 0xa2
# define RSA 0xa3

/* hash */
# define MD2 0xc1
# define MD4 0xc2
# define MD5 0xc3
# define MDC2 0xc4
# define RIPEMD 0xc5
# define SHA 0xc6
# define HMAC 0xc7

BEGIN_REDLIB_DECL

int rcyphertable[0x20];

END_REDLIB_DECL

#endif /* HAVE_CYPHERS_H */
