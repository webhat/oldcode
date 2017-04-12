/*
    Copyright (C) 1997-1999  Daniel W. Crompton <redhat@rphh.org>

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

RCSID("$Id: blowfish.c,v 1.15 2000/01/17 16:51:42 redhat exp $");

#ifndef HEADER_BLOWFISH_H
#include "blowfish.h"
#include "bf_locl.h"
#include "bf_pi.h"
#endif /* HEADER_BLOWFISH_H */

struct blower {
};


#undef THIS
#define THIS ((struct blower *)(fp->current_storage))

static void decrypt(INT32 args)
{
  int level=Z_DEFAULT_COMPRESSION;

  if(THIS->Blow.state)
  {
    /* ENCRYPTS STRING */
    BF_decrypt(THIS->Blow.msg, THIS->Blow.msg, &THIS->Blow.decrypt);
  }

  if(args)
  {
    if(sp[-args].type != T_INT)
      error("Bad argument 1 to BlowFish->decrypt()\n");
    if(THIS->Blow->key)
    {
      error("Null key defined in BlowFish->key\n");
    }
  }

  pop_n_elems(args);
  level=deflateInit(&THIS->gz, level);
  switch(level)
  {
  case Z_OK:
    return;

  case Z_VERSION_ERROR:
    error("libz not compatible with zlib.h!!!\n");
    break;

  default:
    if(THIS->gz.msg)
      error("Failed to decrypt BlowFish->decrypt( %s )\n",THIS->Blow.msg);
    else
      error("Failed to decrypt NULL value\n");
  }
}

static int do_deflate(dynamic_buffer *buf,
		      struct zipper *this,
		      int flush)
{
  int fail=0;

  THREADS_ALLOW();
  mt_lock(& this->lock);
  THREADS_DISALLOW();
  if(!this->gz.state)
  {
    fail=Z_STREAM_ERROR;
  }else{
    do
    {
      char *loc;
      int ret;
      loc=low_make_buf_space(BUF,buf);
      this->gz.next_out=(Bytef *)loc;
      this->gz.avail_out=BUF;
      while (1) {
        THREADS_ALLOW();
        ret=deflate(& this->gz, flush);
        THREADS_DISALLOW();
	if ((ret != Z_BUF_ERROR) || (this->gz.avail_out > MAX_BUF)) {
	  break;
	}
	low_make_buf_space(BUF, buf);
	this->gz.avail_out += BUF;
      } 
      low_make_buf_space(-this->gz.avail_out,buf);
      if(ret != Z_OK)
      {
	fail=ret;
	break;
      }
    } while(!this->gz.avail_out || flush==Z_FINISH || this->gz.avail_in);
  }

  mt_unlock(& this->lock);
  return fail;
}

static void gz_deflate(INT32 args)
{
  struct pike_string *data;
  int flush, fail;
  struct zipper *this=THIS;
  dynamic_buffer buf;

  if(!THIS->gz.state)
    error("gz_deflate not initialized or destructed\n");

  initialize_buf(&buf);

  if(args<1)
    error("Too few arguments to gz_deflate->deflate()\n");

  if(sp[-args].type != T_STRING)
    error("Bad argument 1 to gz_deflate->deflate()\n");

  data=sp[-args].u.string;

  if(args>1)
  {
    if(sp[1-args].type != T_INT)
      error("Bad argument 2 to gz_deflate->deflate()\n");
    
    flush=sp[1-args].u.integer;

    switch(flush)
    {
    case Z_PARTIAL_FLUSH:
    case Z_FINISH:
    case Z_SYNC_FLUSH:
    case Z_NO_FLUSH:
      break;

    default:
      error("Argument 2 to gz_deflate->deflate() out of range.\n");
    }
  }else{
    flush=Z_FINISH;
  }

  this->gz.next_in=(Bytef *)data->str;
  this->gz.avail_in=data->len;

  fail=do_deflate(&buf,this,flush);
  pop_n_elems(args);

  if(fail != Z_OK && fail != Z_STREAM_END)
  {
    free(buf.s.str);
    if(THIS->gz.msg)
      error("Error in gz_deflate->deflate(): %s\n",THIS->gz.msg);
    else
      error("Error in gz_deflate->deflate(): %d\n",fail);
  }

  push_string(low_free_buf(&buf));
}


static void init_gz_deflate(struct object *o)
{
  mt_init(& THIS->lock);
  MEMSET(& THIS->gz, 0, sizeof(THIS->gz));
  THIS->gz.zalloc=Z_NULL;
  THIS->gz.zfree=Z_NULL;
  THIS->gz.opaque=(void *)THIS;
  deflateInit(& THIS->gz, Z_DEFAULT_COMPRESSION);
}

static void exit_gz_deflate(struct object *o)
{
/*   mt_lock(& THIS->lock); */
  deflateEnd(&THIS->gz);
/*   mt_unlock(& THIS->lock); */
  mt_destroy( & THIS->lock );
}

/*******************************************************************/


static void gz_inflate_create(INT32 args)
{
  int tmp;
  if(THIS->gz.state)
  {
/*     mt_lock(& THIS->lock); */
    inflateEnd(&THIS->gz);
/*     mt_unlock(& THIS->lock); */
  }


  THIS->gz.zalloc=Z_NULL;
  THIS->gz.zfree=Z_NULL;
  THIS->gz.opaque=(void *)THIS;

  pop_n_elems(args);
/*    mt_lock(& THIS->lock);  */
  tmp=inflateInit(& THIS->gz);
/*    mt_unlock(& THIS->lock); */
  switch(tmp)
  {
  case Z_OK:
    return;

  case Z_VERSION_ERROR:
    error("libz not compatible with zlib.h!!!\n");
    break;

  default:
    if(THIS->gz.msg)
      error("Failed to initialize gz_inflate: %s\n",THIS->gz.msg);
    else
      error("Failed to initialize gz_inflate\n");
  }
}

static int do_inflate(dynamic_buffer *buf,
		      struct zipper *this,
		      int flush)
{
  int fail=0;
  THREADS_ALLOW();
  mt_lock(& this->lock);
  THREADS_DISALLOW();
  if(!this->gz.state)
  {
    fail=Z_STREAM_ERROR;
  }else{
    do
    {
      char *loc;
      int ret;
      loc=low_make_buf_space(BUF,buf);
      THREADS_ALLOW();
      this->gz.next_out=(Bytef *)loc;
      this->gz.avail_out=BUF;
      ret=inflate(& this->gz, flush);
      THREADS_DISALLOW();
      low_make_buf_space(-this->gz.avail_out,buf);
      if(ret != Z_OK)
      {
	fail=ret;
	break;
      }
    } while(!this->gz.avail_out || flush==Z_FINISH || this->gz.avail_in);
  }
  mt_unlock(& this->lock);
  return fail;
}

static void gz_inflate(INT32 args)
{
  struct pike_string *data;
  int fail;
  struct zipper *this=THIS;
  dynamic_buffer buf;

  if(!THIS->gz.state)
    error("gz_inflate not initialized or destructed\n");

  initialize_buf(&buf);

  if(args<1)
    error("Too few arguments to gz_inflate->inflate()\n");

  if(sp[-args].type != T_STRING)
    error("Bad argument 1 to gz_inflate->inflate()\n");

  data=sp[-args].u.string;

  this->gz.next_in=(Bytef *)data->str;
  this->gz.avail_in=data->len;

  fail=do_inflate(&buf,this,Z_PARTIAL_FLUSH);
  pop_n_elems(args);

  if(fail != Z_OK && fail != Z_STREAM_END)
  {
    free(buf.s.str);
    if(THIS->gz.msg)
      error("Error in gz_inflate->inflate(): %s\n",THIS->gz.msg);
    else
      error("Error in gz_inflate->inflate(): %d\n",fail);
  }
  push_string(low_free_buf(&buf));
  if(fail != Z_STREAM_END && fail!=Z_OK && !sp[-1].u.string->len)
  {
    pop_stack();
    push_int(0);
  }
}

static void init_gz_inflate(struct object *o)
{
  mt_init(& THIS->lock);
  MEMSET(& THIS->gz, 0, sizeof(THIS->gz));
  THIS->gz.zalloc=Z_NULL;
  THIS->gz.zfree=Z_NULL;
  THIS->gz.opaque=0;
  inflateInit(&THIS->gz);
  inflateEnd(&THIS->gz);
}

static void exit_gz_inflate(struct object *o)
{
/*   mt_lock(& THIS->lock); */
  inflateEnd(& THIS->gz);
/*   mt_unlock(& THIS->lock); */
  mt_destroy( & THIS->lock );
}


static void gz_crc32(INT32 args)
{
   unsigned INT32 crc;
   if (!args ||
       sp[-args].type!=T_STRING)
      error("Gz.crc32: illegal or missing argument 1 (expected string)\n");

   if (args>1) {
      if (sp[1-args].type!=T_INT)
	 error("Gz.crc32: illegal argument 2 (expected integer)\n");
      else
	 crc=(unsigned INT32)sp[1-args].u.integer;
   } else
      crc=0;
	 
   crc=crc32(crc,
	     (unsigned char*)sp[-args].u.string->str,
	     sp[-args].u.string->len);

   pop_n_elems(args);
   push_int((INT32)crc);
}


void pike_module_exit(void) {}

void pike_module_init(void)
{
#ifdef HAVE_ZLIB_H
  start_new_program();
  add_storage(sizeof(struct zipper));
  
  add_function("create",gz_deflate_create,"function(int|void:void)",0);
  add_function("deflate",gz_deflate,"function(string,int|void:string)",0);

  add_integer_constant("NO_FLUSH",Z_NO_FLUSH,0);
  add_integer_constant("PARTIAL_FLUSH",Z_PARTIAL_FLUSH,0);
  add_integer_constant("SYNC_FLUSH",Z_SYNC_FLUSH,0);
  add_integer_constant("FINISH",Z_FINISH,0);

  set_init_callback(init_gz_deflate);
  set_exit_callback(exit_gz_deflate);

  end_class("deflate",0);

  start_new_program();
  add_storage(sizeof(struct zipper));
  
  add_function("create",gz_inflate_create,"function(int|void:void)",0);
  add_function("inflate",gz_inflate,"function(string:string)",0);

  add_integer_constant("NO_FLUSH",Z_NO_FLUSH,0);
  add_integer_constant("PARTIAL_FLUSH",Z_PARTIAL_FLUSH,0);
  add_integer_constant("SYNC_FLUSH",Z_SYNC_FLUSH,0);
  add_integer_constant("FINISH",Z_FINISH,0);

  set_init_callback(init_gz_inflate);
  set_exit_callback(exit_gz_inflate);

  end_class("inflate",0);

  add_integer_constant("NO_FLUSH",Z_NO_FLUSH,0);
  add_integer_constant("PARTIAL_FLUSH",Z_PARTIAL_FLUSH,0);
  add_integer_constant("SYNC_FLUSH",Z_SYNC_FLUSH,0);
  add_integer_constant("FINISH",Z_FINISH,0);

  add_function("crc32",gz_crc32,
	       "function(string,void|int:int)",
	       OPT_TRY_OPTIMIZE);

#endif
}

#if defined(HAVE___VTBL__9TYPE_INFO) || defined(HAVE___T_9__NOTHROW)
/* Super-special kluge for IRIX 6.3 */
#ifdef HAVE___VTBL__9TYPE_INFO
extern void __vtbl__9type_info(void);
#endif /* HAVE___VTBL__9TYPE_INFO */
#ifdef HAVE___T_9__NOTHROW
extern void __T_9__nothrow(void);
#endif /* HAVE___T_9__NOTHROW */
/* Don't even think of calling this one
 * Not static, so the compiler can't optimize it away totally.
 */
void zlibmod_strap_kluge(void)
{
#ifdef HAVE___VTBL__9TYPE_INFO
  __vtbl__9type_info();
#endif /* HAVE___VTBL__9TYPE_INFO */
#ifdef HAVE___T_9__NOTHROW
  __T_9__nothrow();
#endif /* HAVE___T_9__NOTHROW */
}
#endif /* HAVE___VTBL__9TYPE_INFO || HAVE___T_9__NOTHROW */
