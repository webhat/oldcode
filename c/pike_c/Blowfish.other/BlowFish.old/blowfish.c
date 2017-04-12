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
				signed int state;
				unsigned char msg;
				BF_KEY key;
};


struct blower THIS;

static void decrypt(INT32 args)
{
  if(THIS.state)
  {
    /* ENCRYPTS STRING */
    BF_decrypt(THIS.msg, THIS.msg, &THIS.key);
  }

  if(args)
  {
    if(sp[-args].type != T_INT)
      error("Bad argument 1 to BlowFish->decrypt()\n");
    if(THIS.key)
    {
      error("Null key defined in BlowFish->key\n");
    }
  }

  pop_n_elems(args);
  }
}

