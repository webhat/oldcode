/*\
||| This file a part of Pike, and is copyright by Daniel Crompton
||| Pike is distributed as GPL (General Public License)
||| See the files COPYING and DISCLAIMER for more information.
||| Substitute Daniel Crompton for Fredrik Hubinette
\*/
#include "global.h"
RCSID("$Id: blow.c,v 1.1 1999/06/10 20:08:47 redhat Exp $");

#include "interpret.h"
#include "svalue.h"
#include "stralloc.h"
#include "array.h"
#include "pike_macros.h"
#include "program.h"
#include "stralloc.h"
#include "object.h"
#include "pike_types.h"
#include "threads.h"
#include "dynamic_buffer.h"
#include "module_support.h"
#include "blowfish.h"

#define BF_ENCRYPT	1
#define BF_DECRYPT	0

extern void BF_set_key(BF_KEY *key,
								int len,
								unsigned char *data);
extern void BF_ecb_encrypt(unsigned char *in,
								unsigned char *out,
								BF_KEY *key,
								int encrypt);
extern void BF_encrypt(BF_LONG *data,
								BF_KEY *key,
								int encrypt);
extern void BF_cbc_encrypt(unsigned char *in,
								unsigned char *out,
								long length, BF_KEY *ks,
								unsigned char *iv,
								int encrypt);
extern void BF_cfb64_encrypt(unsigned char *in,
								unsigned char *out,
								long length,
								BF_KEY *schedule,
								unsigned char *ivec,
								int *num,
								int encrypt);
extern void BF_ofb64_encrypt(unsigned char *in,
								unsigned char *out,
								long length,
								BF_KEY *schedule,
								unsigned char *ivec,
								int *num);
extern char *BF_options(void);


struct program *blowfish_program = NULL;

struct blower {
				struct blows {
								BF_KEY key;
								BF_LONG data;
								unsigned char *in;
								unsigned char out[256];
//								unsigned char out[256];
//								struct pike_string *pike_out;
								unsigned long len;
				} blowz;
#ifdef _REENTRANT
//				DEFINE_MUTEX(lock);
#endif /* _REENTRANT */
};

#define BUF 32768
#define MAX_BUF	(64*BUF)

#undef THIS
#define THIS ((struct blower *)(fp->current_storage))

static void BF_create(INT32 args) {
  if(args) {
    if(sp[-args].type != T_STRING)
      error("Bad argument 1 to blowz->create()\n");
    BF_set_key(			&THIS->blowz.key,
										sizeof(sp[-args].u.string),
										(char *) sp[-args].u.string	);
  }

  pop_n_elems(args);
}

static void BF_ecb_decrypt_data(INT32 args) {
	PCHARP dest;
  struct blower *this=THIS;

	bzero( &this->blowz.in, sizeof(this->blowz.in));
	bzero( &this->blowz.out, sizeof(this->blowz.out));

  if(!THIS->blowz.key.P)
    error("No blowfish key defined\n");

  if(sp[-args].type != T_STRING)
    error("Bad argument 1 to blowz->decrypt()\n");

	this->blowz.in = strdup( (unsigned char *) sp[-args].u.string->str);


	BF_ecb_encrypt( this->blowz.in,
									this->blowz.out,
									&this->blowz.key,
									BF_DECRYPT );

  pop_n_elems(args);

  push_string( make_shared_string( this->blowz.out));
}

/********** EXTRA COMMANDS, BROKEN ************************************
 * unsigned char data_out[256];
 * memset (dest.ptr, 0, strlen(dest.ptr));
 * this->blowz.out = NULL;
 * pike_string_cpy( dest, sp[-args].u.string);
 * strcpy( this->blowz.in, (unsigned char *) sp[-args].u.string->str);
 * data_in = EXTRACT_PCHARP(dest);
 * this->blowz.in = strdup( dest.ptr);
 * strcpy( &this->blowz.out, data_out);
 * push_string( make_shared_binary_string( this->blowz.out));
 **********************************************************************/

static void BF_ecb_encrypt_data(INT32 args) {
	PCHARP dest;
  struct blower *this=THIS;

	bzero( &this->blowz.in, sizeof(this->blowz.in));
	bzero( &this->blowz.out, sizeof(this->blowz.out));

  if(!THIS->blowz.key.P)
    error("No blowfish key defined\n");

  if(sp[-args].type != T_STRING)
    error("Bad argument 1 to blowz->decrypt()\n");

	this->blowz.in = strdup( (unsigned char *) sp[-args].u.string->str);


	BF_ecb_encrypt( this->blowz.in,
									this->blowz.out,
									&this->blowz.key,
									BF_ENCRYPT );

  pop_n_elems(args);

  push_string( make_shared_string( this->blowz.out));
}

static void BF_cbc_encrypt_data(INT32 args) {
	unsigned char *ivsec;
	PCHARP dest;
  struct blower *this=THIS;

	ivsec = malloc( (size_t) 256);

	bzero( &this->blowz.in, sizeof(this->blowz.in));
	bzero( &this->blowz.out, sizeof(this->blowz.out));

  if(!THIS->blowz.key.P)
    error("No blowfish key defined\n");

  if(sp[-args].type != T_STRING)
    error("Bad argument 1 to blowz->cbc_decrypt()\n");

	this->blowz.in = strdup( (unsigned char *) sp[-args].u.string->str);
	
	BF_cbc_encrypt( this->blowz.in,
									this->blowz.out,
									(long) 256,
									&this->blowz.key,
									ivsec,
									BF_ENCRYPT );

  pop_n_elems(args);

  push_string( make_shared_string( this->blowz.out));
}

static void BF_cbc_decrypt_data(INT32 args) {
	unsigned char *ivsec;
	PCHARP dest;
  struct blower *this=THIS;

	ivsec = malloc( (size_t) 256);

	bzero( &this->blowz.in, sizeof(this->blowz.in));
	bzero( &this->blowz.out, sizeof(this->blowz.out));
	//bzero( &this->blowz.in, 8);
	//bzero( &this->blowz.out, 8);
	//free( &this->blowz.out);

  if(!THIS->blowz.key.P)
    error("No blowfish key defined\n");

  if(sp[-args].type != T_STRING)
    error("Bad argument 1 to blowz->cbc_decrypt()\n");

	this->blowz.in = strdup( (unsigned char *) sp[-args].u.string->str);
	
//	if( ( sizeof(*this->blowz.in)%8 )) {
//		printf( "size: '%d'\n", sizeof(this->blowz.out)); 
	/*
			object BF = Blowfish.blowz("12345678");
			string enc = BF->cbc_encrypt("1234567812345678");
			string dec = BF->cbc_decrypt( enc);
	 */
//	if( ( 8%8 )) 
//    error("Input must be multiples of 8 bytes!\n");
//	}

	BF_cbc_encrypt( this->blowz.in,
									this->blowz.out,
									(long) 256,
									&this->blowz.key,
									ivsec,
									BF_DECRYPT );

  pop_n_elems(args);

  //push_string( make_shared_string( ivsec));
  push_string( make_shared_string( this->blowz.out));
}

static void BF_cfb64_encrypt_data(INT32 args) {
  pop_n_elems(args);
}

static void BF_cfb64_decrypt_data(INT32 args) {
  pop_n_elems(args);
}

static void BF_ofb64_encrypt_data(INT32 args) {
  pop_n_elems(args);
}

static void BF_ofb64_decrypt_data(INT32 args) {
  pop_n_elems(args);
}

void pike_module_exit(void) {}

void pike_module_init(void)
{
  /*
   * start_new_program();
   *
   * add_storage();
   *
   * add_function();
   * add_function();
   * ...
   *
   * set_init_callback();
   * set_exit_callback();
   *
   * program = end_c_program();
   * program->refs++;
   *
   * program = end_program();
   *
   */

  start_new_program();
  add_storage(sizeof(struct blower));

  add_function("create",BF_create,"function(void|string:void)",0);
  add_function("set_key",BF_create,"function(void|string:void)",0);
  add_function("decrypt",BF_ecb_decrypt_data,"function(string:string)",0);
  add_function("encrypt",BF_ecb_encrypt_data,"function(string:string)",0);

	/*********** IMPLEMENTED FUNCTIONS ********/

  add_function("ebc_decrypt",BF_ecb_decrypt_data,"function(string:string)",0);
  add_function("ebc_encrypt",BF_ecb_encrypt_data,"function(string:string)",0);
  add_function("cbc_decrypt",BF_cbc_decrypt_data,"function(string:string)",0);
  add_function("cbc_encrypt",BF_cbc_encrypt_data,"function(string:string)",0);
  add_function("cfb64_decrypt",BF_cfb64_decrypt_data,"function(string:string)",0);
  add_function("cfb64_encrypt",BF_cfb64_encrypt_data,"function(string:string)",0);
  add_function("ofb64_decrypt",BF_ofb64_decrypt_data,"function(string:string)",0);
  add_function("ofb64_encrypt",BF_ofb64_encrypt_data,"function(string:string)",0);

	blowfish_program = end_program();
	add_program_constant("blowz", blowfish_program, 0);

}

