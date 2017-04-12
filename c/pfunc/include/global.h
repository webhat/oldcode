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
/* CVSVERSION: $Id: $ */

#ifndef HAVE_GLOBALS_H
# define HAVE_GLOBALS_H

/* Filesystem Layer */
extern int lookup_proc(char *name);

/* Communication Layer */
extern int broke(char *msg);
extern int debug(char *msg);

# ifndef DEBUG
//#  define DEBUG(X)
# else
#  define DEBUG(X) debug(X)
# endif /* DEBUG(X) */

/* User Layer */
extern int kill_pidlist( int sig);
extern int write_pidlist();

# ifdef PKILL
#  define PFUNC(X)	kill_pidlist(X)
# else
#  define PFUNC(X)	write_pidlist()
# endif

const char *version;
char *delim;
int form;

typedef enum id_types { f_not, f_uid, f_euid, f_pid, f_gid, f_ppid, f_sid, f_pgrp, f_tty} id_types;

id_types type;

int got_id;

#endif /* HAVE_GLOBALS_H */
