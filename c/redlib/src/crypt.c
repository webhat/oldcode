/*
 *  Copyright (C) 1997-2001  Daniel W. Crompton <redhat@rphh.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
/* $Id: $ */

/* TODO:
 * - crypt: libmcrypt
 * 		/usr/local/doc/libmcrypt4-devel-2.4.15/example.c.gz
 * - crypt: libcrypto (ssl)
 * - crypt: libmix
 * - crypt: libica
 */

/* #define DEBUG */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

#define R_EXTERN /* */
#include "crypt.h"

//#if !defined(HAVE_CYPHERS_H)
// #error redlib: crypt lib won''t build, please run configure with
// #error redlib: --without-crypt or --with-crypt=no
//#endif /* HAVE_CYPHERS_H */

#include <ctype.h>
#include <errno.h>
#include <time.h>

/*
				switch( cyph)
				{
								case TDES:
												break;
								case TWAY:
												break;
								case ARCFOUR:
												/ * RC4 * /
												break;
								case BLOWFISH:
												break;
								case CAST:
												break;
								case DES:
												break;
								case ENIGMA:
												break;
								case GOST:
												break;
								case IDEA:
												break;
								case LOKI97:
												break;
								case MARS:
												break;
								case PANAMA:
												break;
								case RC2:
												break;
								case RC5:
												break;
								case RC6:
												break;
								case RIJNDAEL:
												break;
								case SAFER:
												break;
								case SAFERP:
												break;
								case SERPENT:
												break;
								case SKIPJACK:
												break;
								case TWOFISH:
												break;
								case WAKE:
												break;
								case XTEA:
												break;
								default:
				}
 */

const char *rcypher( cyph)
				int cyph;
{
				int i;

				if( cyph == 0)
								cyph = (int) DEFAULT_CYPHER;

				for( i = 0; i < sizeof(rcyphertable) ; i++ )
												rcyphertable[cyph] = 0;

				switch( cyph)
				{
								case TDES:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(TRIPLEDES);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case TWAY:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(THREEWAY);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case ARCFOUR:
												/* RC4*/
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(ARCFOUR);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case BLOWFISH:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(BLOWFISH);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case CAST:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(CAST-256);
#endif /* defined(HAVE_LIBMCRYPT) */
#if defined(HAVE_LIBMIX)
												do_rcypher(MIXCAST256);
												return "cast";
#endif
												break;
								case DES:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(DES);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case ENIGMA:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(ENIGMA);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case GOST:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(GOST);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case IDEA:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(IDEA); /* not in my libmcrypt */
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case LOKI97:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(LOKI97);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case MARS:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMIX)
												do_rcypher(MIXMARS);
												return "mars";
#endif
												break;
								case PANAMA:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(PANAMA);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case RC2:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(RC2);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case RC5:
												rcyphertable[cyph] = 1;
												break;
								case RC6:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(RC6); /* not in my libmcrypt */
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case RIJNDAEL:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(RIJNDAEL);
#endif /* defined(HAVE_LIBMCRYPT) */
#if defined(HAVE_LIBMIX)
												do_rcypher(MIXRIJNDAEL);
												return "rijndael";
#endif
												break;
								case SAFER:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(SAFER);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case SAFERP:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(SAFERPLUS);
#endif /* defined(HAVE_LIBMCRYPT) */
#if defined(HAVE_LIBMIX)
												do_rcypher(MIXSAFERP);
												return "saferplus";
#endif
												break;
								case SERPENT:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(SERPENT);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case SKIPJACK:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(SKIPJACK);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case TWOFISH:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(TWOFISH);
#endif /* defined(HAVE_LIBMCRYPT) */
#if defined(HAVE_LIBMIX)
												do_rcypher(MIXTWOFISH);
												return "twofish";
#endif
												break;
								case WAKE:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(WAKE);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								case XTEA:
												rcyphertable[cyph] = 1;
#if defined(HAVE_LIBMCRYPT)
												return do_rcypher(XTEA);
#endif /* defined(HAVE_LIBMCRYPT) */
												break;
								default:
												return (const char *)NULL;
				}
				return (const char *)NULL;
}

const char *rhash( buf, cyph)
				const char *buf;
				int cyph;
{
				if( cyph == 0)
				{
#if defined(HAVE_LIBMIX)
								cyph = SHA;
#else
								cyph = MD5;
#endif /* defined(HAVE_LIBMIX) */
				}

				switch( cyph)
				{
								case HMAC:
												break;
								case MD2:
												break;
								case MD4:
												break;
								case MD5:
												break;
								case MDC2:
												break;
								case PANAMA:
												break;
								case RIPEMD:
												break;
								case SHA:
#if defined(HAVE_LIBMIX)
												return (const char *)do_rhash( buf, cyph);
#endif /* defined(HAVE_LIBMIX) */
												break;
								default:
												return NULL;
				}      
				return NULL;
}

int get_rcypher()
{
				int i;

				for( i = 0; i < sizeof(rcyphertable) ; i++)
								if( rcyphertable[i])
												return i;

				return -1;
}

int rkeysize( size)
				int size;
{
				int cyph = get_rcypher();

				switch( cyph)
				{
								case DES:		/* 56b sz 7 */
												if( size != 7)
																return -1;
												rcyphertable[cyph] = 56;
												return rcyphertable[cyph];
								case TDES:	/* 168 sz 21 */
												if( size != 21)
																return -1;
												rcyphertable[cyph] = 168;
												return rcyphertable[cyph];
								case TWAY:	/* 96 sz 12 */
												if( size != 12)
																return -1;
												rcyphertable[cyph] = 96;
												return rcyphertable[cyph];
								case ARCFOUR: /* 8-2048 1-256 */
												/* RC4 */
												if( size < 1 && size > 256)
																return -1;
												rcyphertable[cyph] = (size*8);
												return rcyphertable[cyph];
								case BLOWFISH: /* 448 sz 56 */
												if( size != 56)
																return -1;
												rcyphertable[cyph] = 448;
												return rcyphertable[cyph];
								case CAST:	/* 128 sz 16 */
														/* 256 sz 32 */
												if( size == 16)
												{
																rcyphertable[cyph] = 128;
																return rcyphertable[cyph];
												}
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case ENIGMA: /* none */
												rcyphertable[cyph] = (int)NULL;
												return rcyphertable[cyph];
								case GOST: /* 256 sz 32 */
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case IDEA: /* 128 sz 16 */
												if( size != 16)
																return -1;
												rcyphertable[cyph] = 128;
												return rcyphertable[cyph];
								case LOKI97: /* 128 sz 16 */
													/* 192 sz 24 */
													/* 256 sz 32 */
												if( size == 16)
												{
																rcyphertable[cyph] = 128;
																return rcyphertable[cyph];
												}
												if( size == 24)
												{
																rcyphertable[cyph] = 196;
																return rcyphertable[cyph];
												}
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case MARS: /* 128 sz 16 */
												if( size != 16)
																return -1;
												rcyphertable[cyph] = 128;
												return rcyphertable[cyph];
								case PANAMA:
												rcyphertable[cyph] = (int)NULL;
												return rcyphertable[cyph];
								case RC2: /* 8-1024 sz 1-128 */
												if( size < 1 || size > 128)
																return -1;
												rcyphertable[cyph] = (size*8);
												return rcyphertable[cyph];
								case RC5: /* none */
												rcyphertable[cyph] = (int)NULL;
												return rcyphertable[cyph];
								case RC6: /* 128 sz 16 */
												  /* 192 sz 24 */
												  /* 256 sz 32 */
												if( size == 16)
												{
																rcyphertable[cyph] = 128;
																return rcyphertable[cyph];
												}
												if( size == 24)
												{
																rcyphertable[cyph] = 196;
																return rcyphertable[cyph];
												}
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case RIJNDAEL: /* 128 sz 16 */
												  /* 192 sz 24 */
												  /* 256 sz 32 */
												if( size == 16)
												{
																rcyphertable[cyph] = 128;
																return rcyphertable[cyph];
												}
												if( size == 24)
												{
																rcyphertable[cyph] = 196;
																return rcyphertable[cyph];
												}
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case SAFER: /* 64 sz 8 */
													/* 128 sz 16 */
												if( size == 8)
												{
																rcyphertable[cyph] = 64;
																return rcyphertable[cyph];
												}
												if( size != 16)
																return -1;
												rcyphertable[cyph] = 128;
												return rcyphertable[cyph];
								case SAFERP: /* 128 sz 16 */
													/* 192 sz 24 */
													/* 256 sz 32 */
												if( size == 16)
												{
																rcyphertable[cyph] = 128;
																return rcyphertable[cyph];
												}
												if( size == 24)
												{
																rcyphertable[cyph] = 196;
																return rcyphertable[cyph];
												}
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case SERPENT: /* 128 sz 16 */
												if( size != 16)
																return -1;
												rcyphertable[cyph] = 128;
												return rcyphertable[cyph];
								case SKIPJACK:
														/* 80 sz 10 */
												if( size != 10)
																return -1;
												rcyphertable[cyph] = 80;
												return rcyphertable[cyph];
								case TWOFISH: /* 128 sz 16 */
														/* 192 sz 24 */
														/* 256 sz 32 */
												if( size == 16)
												{
																rcyphertable[cyph] = 128;
																return rcyphertable[cyph];
												}
												if( size == 24)
												{
																rcyphertable[cyph] = 196;
																return rcyphertable[cyph];
												}
												if( size != 32)
																return -1;
												rcyphertable[cyph] = 256;
												return rcyphertable[cyph];
								case WAKE: /* none */
												rcyphertable[cyph] = (int)NULL;
												return rcyphertable[cyph];
								case XTEA:	/* 128 sz 16 */
												if( size != 16)
																return -1;
												rcyphertable[cyph] = 128;
												return rcyphertable[cyph];
								default:
												return -1;
				}
				return -1;
}

const char *rcmode( m)
				int m;
{
				/* XXX: temp function */
				/* cbc		0
				 * ecb		1
				 * cfb		2
				 * ofb		3
				 * nofb		4
				 * stream	5
				 */
				switch( m)
				{
								case 0:
												return (const char *) "cbc";
								case 1:
												return (const char *) "ecb";
								case 2:
												return (const char *) "cfb";
								case 3:
												return (const char *) "ofb";
								case 4:
												return (const char *) "nofb";
								case 5:
												return (const char *) "stream";
				}

				return do_rstream(m);
}

const char *rencrypt( buf, key)
				const char *buf;
				const char *key;
{
#if defined(HAVE_LIBMCRYPT)
				/* mcrypt */
				MCRYPT _mc;
				char *IV;
				int blk_sz;
				char *blk_buf;

				/* my own */
				int i;
				int cyph_i = get_rcypher();
				char *cyph;															/* XXX: not inited yet!!! */
				char *encout = calloc( 1, (strlen(buf) + 1));

				_mc = rmcrypt_module_open( cyph,
																NULL,
																(char *)rcmode(CFB),
																NULL);

				if( _mc == MCRYPT_FAILED)
								return NULL;

				IV = calloc( 1, rmcrypt_enc_get_iv_size( _mc));
				if( IV == NULL || encout == NULL)
				{
								printf("mcrypt: `%s'", strerror( errno));
								return NULL;
				}  

				srand( (unsigned int) time(NULL));

				for( i = 0; i < rmcrypt_enc_get_iv_size( _mc); i++ )
								IV[i] = rand();

				i = rmcrypt_generic_init( _mc,
																(void *)key,
																(rcyphertable[cyph_i]/8),
																(void *)IV); /* ignored by CBC */
				if( i < 0)
				{
								rmcrypt_perror( i);
								return NULL;
				}

				strncpy( encout, buf, strlen(buf));

				if( strncmp( rcmode(CFB), "cfb", 3)
								|| strncmp( rcmode(CFB), "ofb", 3))
				{
								blk_sz = 1;
				}
				else
								if( strncmp( rcmode(CFB), "cbc", 3)
												|| strncmp( rcmode(CFB), "ebc", 3)
												|| strncmp( rcmode(CFB), "nofb", 3))
								{
												blk_sz = rmcrypt_enc_get_block_size( _mc);
								}
								else
								{
												return NULL;
								}

				blk_buf = calloc( 1, (blk_sz + 1));
				if( blk_buf == NULL)
				{
								printf("mcrypt: `%s'", strerror( errno));
								return NULL;
				}  

				for( i = 0; i < (strlen( encout)/blk_sz); i = (i + blk_sz) )
				{
								strncpy( blk_buf, buf[i], blk_sz);
								rmcrypt_generic( _mc, (void *)blk_buf, blk_sz);
								strncat( encout, blk_buf, blk_sz);
				}

				rmcrypt_generic_deinit( _mc);

				return encout;

#endif /* defined(HAVE_LIBMCRYPT) */

#if defined(HAVE_LIBMIX)
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
				return do_rencrypt( buf, key); 
# else /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
				do_rencrypt( buf, key); 
# endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
#endif /* defined(HAVE_LIBMIX) */

				return NULL;
}

const char *rdecrypt( buf, key)
				const char *buf;
				const char *key;
{
#if defined(HAVE_LIBMCRYPT)
#endif /* defined(HAVE_LIBMCRYPT) */

#if defined(HAVE_LIBMIX)
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
				return do_rdecrypt( buf, key); 
# else /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
				do_rdecrypt( buf, key); 
# endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
#endif /* defined(HAVE_LIBMIX) */

				return NULL;
}

static char *strlower( buf)
				char *buf;
{
				int i;

				for( i = 0; i < strlen(buf) ; i++ )
								if( isupper(buf[i]))
												buf[i] = tolower( buf[i]);

				return buf;
}

#ifdef DEBUG
int main( int, char *[], char *[]);
int main( argc, argv, envp)
				int argc;
				char *argv[];
				char *envp[];
{
				return 0;
}
#endif /* DEBUG */

