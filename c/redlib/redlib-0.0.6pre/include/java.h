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

/* CVSVERSION: $Id: $ */
/* Last modified: Tue 30 Jul 2002 00:18:53 GMT
 */

#ifndef HAVE_JAVA_H
# define HAVE_JAVA_H

# include "redlib_RFILE_CompressFile.h"

/* sun jdk */
# ifdef _JAVASOFT_JNI_H_
#  if defined(JNI_VERSION_1_1) 
#  endif /* defined(JNI_VERSION_1_1) */

#  if defined(JNI_VERSION_1_2) 
#  endif /* defined(JNI_VERSION_1_2) */

#  if defined(JNI_VERSION_1_4) 
#  endif /* defined(JNI_VERSION_1_4) */
# endif /* _JAVASOFT_JNI_H_ */

/* gcj */
# if defined(__GCJ_JNI_H__)
#  if defined(JNI_VERSION_1_1) 
#  endif /* defined(JNI_VERSION_1_1) */

#  if defined(JNI_VERSION_1_2) 
#  endif /* defined(JNI_VERSION_1_2) */
# endif /* defined(__GCJ_JNI_H__) */

/* kaffe */
# if defined(__jni_h)
#  if defined(JNI_VERSION_1_1) 
#  endif /* defined(JNI_VERSION_1_1) */

#  if defined(JNI_VERSION_1_2) 
#  endif /* defined(JNI_VERSION_1_2) */
# endif /* defined(__jni_h) */

/* mozilla */
# if defined(JNI_H)
# endif /* defined(JNI_H) */

typedef struct CompressFileElem CompressFileElem;

#endif /* HAVE_JAVA_H */


