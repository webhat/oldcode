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
/* stdin */

FILE *fopen(const char *p, const char *m);
FILE *fdopen(int fd, const char *m);
FILE *freopen(const char *p, const char *m, FILE *s);
int fflush(FILE *s);
size_t fread(void *ptr, size_t sz, size_t nm, FILE *s);
size_t fwrite(const void *ptr, size_t sz, size_t nm, FILE *s);
int fclose(FILE *s);

int open(const char *pathname, int flags, mode_t m);
size_t read(int fd, char *buf, size_t count);
size_t write(int fd, char *buf, size_t count);
int close(int fd);
