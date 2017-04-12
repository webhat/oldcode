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
/* Last modified: Tue 30 Jul 2002 01:37:12 GMT
 */

#include "java.h"
#include "mem.h"
#include "file.h"
#include <stdio.h>

/* #define DEBUG */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/* don't forget to compile with -lbsd-compat */
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1
#define _SVID_SOURCE 1

#ifdef _THREAD_SAFE
# define _REENTRANT
#endif /* _THREAD_SAFE */

/* globals */
struct CompressFileElem {
				jint	hashCode;
				RFILE	file;
				CompressFileElem *next;
};

static CompressFileElem *CompressFileList = NULL;

static void ThrowExceptionFromC(JNIEnv *, jobject, char *);

/* functions */
JNIEXPORT jcharArray JNICALL Java_redlib_RFILE_CompressFile_read(env, obj, sz)
				JNIEnv *env;
				jobject obj;
				jint sz;
{
				CompressFileElem	*mine;
				jchar							*field = xcalloc( 1, sz+1);
				int								nmemb, i;
				jcharArray				out;
				/* info */
				jclass		cls = (*env)->GetObjectClass( env, obj);
				jmethodID	mid = (*env)->GetMethodID( env, cls, "hashCode", "()I");
				jint			hc;

				hc = (*env)->CallIntMethod( env, obj, mid);

				mine = CompressFileList->next;
				while( mine != NULL) {
								if( (hc-mine->hashCode) == 0)
												break;
								mine = mine->next;
				}

				if( mine == NULL)
								ThrowExceptionFromC(env,obj,"Cannot read file, not open");

				nmemb = rread( field, 1, sz, mine->file);

				printf("Read:  %s\n", (char*)field);
				
				out = (*env)->NewCharArray( env, nmemb);
				(*env)->SetCharArrayRegion( env, out, 0, nmemb, field);

				printf("Read:  %s:\n", (char*)out);

				return out;

}

JNIEXPORT jint JNICALL Java_redlib_RFILE_CompressFile_write(env, obj, string)
				JNIEnv *env;
				jobject obj;
				jcharArray string;
{
				CompressFileElem	*mine;
				int								i;
				/* info */
				jclass		cls = (*env)->GetObjectClass( env, obj);
				jmethodID	mid = (*env)->GetMethodID( env, cls, "hashCode", "()I");
				jint			hc;

				/* string argument */
				jsize jstringsz			= (*env)->GetArrayLength( env, string);
				jchar *jstringname	= (*env)->GetCharArrayElements( env, string, 0);
				char	*cstringname	= xcalloc( 1, jstringsz+1);

				hc = (*env)->CallIntMethod( env, obj, mid);

				mine = CompressFileList->next;
				while( mine != NULL) {
								if( (hc-mine->hashCode) == 0)
												break;
								mine = mine->next;
				}

				if( mine == NULL)
								ThrowExceptionFromC(env,obj,"Cannot write file, not open");

				for( i = 0; i < jstringsz ; i++)
								cstringname[i] = jstringname[i];

				printf( "Write: %s\n", cstringname);
				rwrite( cstringname, 1, jstringsz, mine->file);

				return 0;
}

JNIEXPORT jint JNICALL Java_redlib_RFILE_CompressFile_flush(env, obj)
				JNIEnv *env;
				jobject obj;
{
				CompressFileElem *mine;
				/* info */
				jclass		cls = (*env)->GetObjectClass( env, obj);
				jmethodID	mid = (*env)->GetMethodID( env, cls, "hashCode", "()I");
				jint			hc;

				hc = (*env)->CallIntMethod( env, obj, mid);

				mine = CompressFileList->next;
				while( mine != NULL) {
								if( (hc-mine->hashCode) == 0)
												break;
								mine = mine->next;
				}

				if( mine == NULL)
								ThrowExceptionFromC(env,obj,"Cannot flush file, not open");

				return rflush(mine->file);
}

JNIEXPORT void JNICALL Java_redlib_RFILE_CompressFile_open(env, obj, file, mode)
				JNIEnv *env;
				jobject obj;
				jcharArray file;
				jcharArray mode;
{
				int i;
				CompressFileElem *mine;
				/* info */
				jclass		cls = (*env)->GetObjectClass( env, obj);
				jmethodID	mid = (*env)->GetMethodID( env, cls, "hashCode", "()I");
				jint			hc;

				/* file argument */
				jsize jfilesz			= (*env)->GetArrayLength( env, file);
				jchar *jfilename	= (*env)->GetCharArrayElements( env, file, 0);
				char	*cfilename	= xcalloc( 1, jfilesz+1);

				/* mode argument */
				jsize jmodesz			= (*env)->GetArrayLength( env, mode);
				jchar *jmodename	= (*env)->GetCharArrayElements( env, mode, 0);
				char	*cmodename	= xcalloc( 1, jmodesz+1);

				for( i = 0; i < jfilesz ; i++)
								cfilename[i] = jfilename[i];

				for( i = 0; i < jmodesz ; i++)
								cmodename[i] = jmodename[i];

				/*
				printf("length of %s: %d\n", cfilename, jfilesz);
				printf("length of %s: %d\n", cmodename, jmodesz);
				 */

				if(mid == 0) {
								/*
								printf("Couldn't find methode `hashCode'\n");
								 */

								(*env)->ReleaseCharArrayElements( env, file, jfilename, 0);
								(*env)->ReleaseCharArrayElements( env, mode, jmodename, 0);

								xfree(cfilename);
								xfree(cmodename);

								return;
				}

				hc = (*env)->CallIntMethod( env, obj, mid);

				if( CompressFileList == NULL) {
								CompressFileList =
												(CompressFileElem*)xcalloc( 1, sizeof(CompressFileElem));
								CompressFileList->next = NULL;
				}

				/* traverse linked list */
				mine = CompressFileList;
				while( mine->next != NULL) {
								mine = mine->next;
				}
				mine->next	= (CompressFileElem*)xcalloc( 1, sizeof(CompressFileElem));
				mine				= mine->next;
				mine->next	= NULL;

				mine->hashCode	= hc;
				mine->file			= ropen(cfilename,cmodename);
				
				if( mine->file == NULL)
								ThrowExceptionFromC(env,obj,"Failed to open file");

				(*env)->ReleaseCharArrayElements( env, file, jfilename, 0);
				(*env)->ReleaseCharArrayElements( env, mode, jmodename, 0);

				xfree(cfilename);
				xfree(cmodename);
}

JNIEXPORT void JNICALL Java_redlib_RFILE_CompressFile_close(env, obj)
				JNIEnv *env;
				jobject obj;
{
				CompressFileElem *mine;
				/* info */
				jclass		cls = (*env)->GetObjectClass( env, obj);
				jmethodID	mid = (*env)->GetMethodID( env, cls, "hashCode", "()I");
				jint			hc;

				hc = (*env)->CallIntMethod( env, obj, mid);

				mine = CompressFileList->next;
				while( mine != NULL) {
								if( (hc-mine->hashCode) == 0)
												break;
								mine = mine->next;
				}

				if( mine == NULL)
								ThrowExceptionFromC(env,obj,"Cannot close file, not open");

				if( rclose(mine->file))
								ThrowExceptionFromC(env,obj,"Failed to close file");
}

static void ThrowExceptionFromC(env, obj, msg)
				JNIEnv *env;
				jobject obj;
				char *msg;
{
				jclass newException =
								(*env)->FindClass( env, "redlib/RFILE/CompressFileException");

				if( newException == 0) {
								printf("error: `redlib.RFILE.CompressFileException' not found");
								return;
				}

				(*env)->ThrowNew( env, newException, msg);
}


				// printf("version: %d\n", (*env)->GetVersion(env));
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

