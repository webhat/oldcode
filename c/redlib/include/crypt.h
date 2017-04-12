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
/* Last modified: Tue 28 Jan 2003 20:37:04 GMT
 */
/* $Id: $ */

#ifndef HAVE_CRYPT_H
# define HAVE_CRYPT_H

# include "default.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

BEGIN_REDLIB_DECL

/* XXX:
 * 		When adding a new crypto you must
 * check if _SKIP_CRYPT is defined
 */

# if defined(HAVE_LIBMCRYPT)  /* may need to be fixed */
#  define _SKIP_CRYPT
/* XXX: libmcrypt mcrypt(3)
 * 		This is the wrapper for libmcrypt.
 * It is possible to use mcrypt itself, all
 * this library module does is make it easier
 * to use different crypt libraries. (As the
 * crypto's `should' be interchangable.)
 *
 * cypher:
 * - des
 * - 3des
 * - cast (128/256)
 * - xTEA
 * - 3-way
 * - skipjack
 * - blowfish
 * - twofish
 * - loki97
 * - arcfour (rc4)
 * - rc6
 * - rijndael (128/192/256)
 * - mars
 * - panama
 * - wake
 * - serpent
 * - idea
 * - enigma
 * - gost
 * - safer (SK-64/SK-128)
 * - safer+
 *
 * 		Examine: doc/magic.gz
 *
 * can use LIBMCRYPT22 or LIBMCRYPT24
 */

END_REDLIB_DECL

#   include <mcrypt.h>
#  if (MCRYPT_API_VERSION <= 19991015)
/* XXX:
 * 		Damned, should I even support this old version?
 * Probably not, but if I can get round to it I probably
 * will. If nobody has send me a patch by then.
 */
#   define MCRYPT int
#   define rmcrypt_module_open(W,X,Y,Z)	(X)
#   define rmcrypt_module_close(X)				mcrypt_generic_deinit(X)
#   define rmcrypt_generic_init(W,X,Y,Z)	mcrypt_generic_init(W,X,Y,Z)
#   define rmcrypt_generic_deinit(X)			(X)
#   define rmcrypt_generic(X)             mcrypt_generic(X)
#   define rmdecrypt_generic(X,Y,Z)				mdecrypt_generic(X,Y,Z)
#   define rmcrypt_enc_get_block_size(X)	mcrypt_get_block_size(X)
#   define rmcrypt_enc_get_vi_size(X)			mcrypt_get_block_size(X)
/* XXX: finish this !!! */
 #  error redlib: currently unsupported 
#  else /* (MCRYPT_API_VERSION <= 19991015) */
#   if (MCRYPT_API_VERSION >= 20010201)
/* XXX:
 * 		This is my current version...
 */
#   define rmcrypt_module_open(W,X,Y,Z)		mcrypt_module_open(W,X,Y,Z)
#   define rmcrypt_module_close(X)				mcrypt_module_close(X)
#   define rmcrypt_generic_init(W,X,Y,Z)	mcrypt_generic_init(W,X,Y,Z)
#   define rmcrypt_generic_deinit(X)			mcrypt_generic_deinit(X)
#   define rmcrypt_generic(X,Y,Z)					mcrypt_generic(X,Y,Z)
#   define rmdecrypt_generic(X,Y,Z)				mdecrypt_generic(X,Y,Z)
#   define rmcrypt_perror(X)							mcrypt_perror(X)
#   define rmcrypt_enc_get_block_size(X)	mcrypt_enc_get_block_size(X)
#   define rmcrypt_enc_get_iv_size(X)			mcrypt_enc_get_iv_size(X)
/* XXX: finish this !!! */
#   else
#    if (MCRYPT_API_VERSION > 19991015) && (MCRYPT_API_VERSION < 20010201)
 #   error redlib: currently unsupported (may be mistake)
#    endif /* (MCRYPT_API_VERSION > 19991015) && (MCRYPT_API_VERSION < 20010201) */
#   endif /* (MCRYPT_API_VERSION >= 20010201) */
#  endif /* (MCRYPT_API_VERSION <= 19991015) */
/* #  include <mhash.h> gone??? */
#  include <cyphers.h>

BEGIN_REDLIB_DECL

static char *strlower( char *buf);
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   define do_rstream(X) ({ char str[7]; switch (X){												\
																case STREAM:	strcpy(str,"stream"); break;\
																case ECB:			strcpy(str,"ecb"); break;		\
																case CBC:			strcpy(str,"cbc"); break;		\
																case CFB:			strcpy(str,"cfb"); break;		\
																case OFB:			strcpy(str,"ofb"); break;		\
																case nOFB:		strcpy(str,"nofb"); break;	\
																default:			strcpy(str,"cfb"); }							\
																str; })
#  else /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
#   define do_rstream(X) strlower((char *)(#X))
#  endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
#  define do_rcypher(X) strlower((char *)(#X))

# endif /* HAVE_LIBMCRYPT */

# if defined(HAVE_LIBCRYPTO) && defined(HAVE_LIBSSL) && !defined(_SKIP_CRYPT)
#  define _SKIP_CRYPT
/* XXX: libcrypto crypto(3)
 * 		This is the wrapper for openssl's
 * libcrypto.
 *
 * cypher:
 * - blowfish
 * - cast
 * - des
 * - idea
 * - rc2
 * - rc4
 * - rc5
 *
 * public:
 * - dsa
 * - dh
 * - rsa
 *
 * hash:
 * - hmac
 * - md2
 * - md4
 * - md5
 * - mdc2
 * - ripemd
 * - sha
 */
END_REDLIB_DECL

#  include <cyphers.h>

BEGIN_REDLIB_DECL

#  if defined(HAVE_LIBMIX)
/* FIXME:
 * 		Actually I don't want to redefine anything,
 * all that's needed is to check if there are
 * any cyphers defined that I don't have yet.
 */
#   undef _SKIP_CRYPT
#  endif /* defined(HAVE_LIBMIX) */
# else
#  if defined(HAVE_LIBCRYPTO) && !defined(HAVE_LIBSSL) && !defined(_SKIP_CRYPT)
#   if defined(__GNUC__) && !defined(__STRICT_ANSI__)
 #   warning redlib: libcrypto unknown component not part of libssl
#   else /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
 #   error redlib: libcrypto unknown component not part of libssl
#   endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
#  endif /* defined(HAVE_LIBCRYPTO) && !defined(HAVE_LIBSSL) */
# endif /* HAVE_LIBCRYPTO  && HAVE_LIBSSL */

# if defined(HAVE_LIBICA) && !defined(_SKIP_CRYPT)
#  define _SKIP_CRYPT
/* XXX: libica
 * 		This is the wrapper for IBM
 * eServer Cryptographic Accelerator
 * (ICA).
 *
 * cypher:
 * - des
 * - 3des
 *
 * public:
 * - rsa
 *
 * hash:
 * - sha
 */
 # error redlib: currently not supported

END_REDLIB_DECL

#  include <cyphers.h>

BEGIN_REDLIB_DECL

/* 		Ok, and because the library I have is like
 * three years old (1999). If you have an ICA and
 * don't need it, please send it my way.
 * 		And any other crypto boards you aren't
 * using.
 */
#  if defined(HAVE_LIBMIX)
#   undef _SKIP_CRYPT
/* FIXME:
 * 		see above
 */
#  endif /* defined(HAVE_LIBMIX) */
# endif /* HAVE_LIBICA */

# if defined(HAVE_LIBMIX) && !defined(_SKIP_CRYPT)
#  define _SKIP_CRYPT
/* XXX: libmix
 * 		This is the wrapper for mixter's
 * aes modules.
 *
 * 		libmix is a block cypher (ECB), as
 * far as I can tell.
 *
 * cypher:
 * - cast-256		(CAST256	0x01)
 * - mars				(MARS			0x02)
 * - safer+			(SAFERP		0x03)
 * - twofish		(TWOFISH	0x04)
 * - rijndael		(RIJNDAEL	0x05)
 *
 * hash:
 * - md5
 */

END_REDLIB_DECL

#  include <mix/mix.h>
#  undef CAST256
#  undef MARS
#  undef SAFERP
#  undef TWOFISH
#  undef RIJNDAEL
#  include <cyphers.h>

BEGIN_REDLIB_DECL

#  define MIXCAST256	0x01
#  define MIXMARS			0x02
#  define MIXSAFERP		0x03
#  define MIXTWOFISH	0x04
#  define MIXRIJNDAEL	0x05
#  define do_rcypher(X) alg = X
#  define do_rset_key(X) aes_key( (const char *) (X))
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   define do_rencrypt(X,Y) ({ int len = strlen((X));				\
															aes_key( (const char *) (Y));	\
															aes_encrypt( (const u1byte *)(X), &len); })
#   define do_rdecrypt(X,Y) ({ int len = strlen((X));				\
															aes_key( (const char *) (Y));	\
															aes_decrypt( (const u1byte *)(X), len); })
#  else /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
/* XXX:
 * 		02 Dec 2002:
 * 	Perhaps this should be a
 * 			do {
 * 					 code
 * 			} while(0)
 *
 * 	Or a nested function, although
 * gcc -pedantic says:
 * 		-	ISO C forbids nested functions
 * 		-	ISO C89 forbids mixed declarations and code
 * and only single use in a function.
 *
 * 		Either solution to comply with ansi are
 * not satisfactory. Thankfully I'm the only one
 * who calls these macros.
 */
#   define do_rencrypt(X,Y) 	int len = strlen((X));				\
															aes_key( (const char *) (Y));	\
															return (const char *)aes_encrypt( (const u1byte *)(X), &len)
#   define do_rdecrypt(X,Y) 	int len = strlen((X));				\
															aes_key( (const char *) (Y));	\
															return (const char *)aes_decrypt( (const u1byte *)(X), len)
#  endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */
#  define do_rhash(X,Y) aes_hash( (const s1byte *) (X))
#  define do_rstream(X) ()
# endif /* HAVE_LIBMIX */

# ifdef HAVE_GNUPG
END_REDLIB_DECL
BEGIN_REDLIB_DECL
# endif /* HAVE_GNUPG */

# if defined(HAVE_GNOMEPGP)
#  if defined(CERTIFIED_GNOMIE)
				/* XXX: certified gnomie
				 * 		So you're a certified gnomie, eh? Sworn
				 * of the evil's of KDE... (c; You've probably
				 * read the rest of the source, so what's to
				 * say...?
				 * 		This is where the gnome pgp interface
				 * will come... I know, bonobo something...
				 * And probably some nice C/C++ wrappers for the
				 */
#  endif /* CERTIFIED_GNOMIE */
				
END_REDLIB_DECL

#  include <gpgp/gpgp.h> /* /usr/include/gpgp/gpgp.h */

BEGIN_REDLIB_DECL

# endif /* HAVE_GNOMEPGP */

# if !defined(_SKIP_CRYPT)
#  define _SKIP_CRYPT
END_REDLIB_DECL
#  include <cyphers.h>
static char *strlower( char *buf) __ATTRIB(__unused__);
BEGIN_REDLIB_DECL
# endif /* !defined(_SKIP_CRYPT) */

# if !defined(rsrand) || !defined(rrand)
#  define rrand rand
#  define rsrand srand
# endif /* defined(rsrand) || defined(rrand) */

R_EXTERN int rkeysize( int);
R_EXTERN int get_rcypher( void);
R_EXTERN const char *rcypher( int);
R_EXTERN const char *rhash( const char *, int);
R_EXTERN const char *rencrypt( const char *, const char *);
R_EXTERN const char *rdecrypt( const char *, const char *);
R_EXTERN const char *rcmode( int);

END_REDLIB_DECL

#endif /* HAVE_CRYPT_H */
