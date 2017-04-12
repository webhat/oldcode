dnl AM_JNI_H

AC_DEFUN(AM_JNI_H,
[AC_ARG_WITH(jni-prefix,
	[  --with-jni-prefix=PFX   Prefix where jni is located (optional)],
	jni_config_prefix="$withval", jni_config_prefix="")
AC_MSG_CHECKING([checking for java])
	REDLIB_JNI_DIR="/usr /usr/local"
	REDLIB_JAVA_INSTALL_DIR="/java/*/include"
	REDLIB_JNI_SUB_DIR="/ /mozilla /kaffe"
	REDLIB_SUB="/"

	test -f $jni_config_prefix/jni.h &&
		REDLIB_DIR="$jni_config_prefix" &&
			ac_status=$?
	test -f $jni_config_prefix/include/jni.h &&
		REDLIB_DIR="$jni_config_prefix" &&
			ac_status=$?

	REDLIB_TMP="$REDLIB_DIR"
	for REDLIB_DIR in $REDLIB_JNI_DIR; do
		test $ac_status -lt 1 && REDLIB_DIR="$REDLIB_TMP" && break
		for REDLIB_SUB in $REDLIB_JNI_SUB_DIR; do
			test -f $REDLIB_DIR/include/$REDLIB_SUB/jni.h || break
			cat > conftest_jni.$ac_ext <<_ACEOF
#line 11 "jni_h"
#include <jni.h>

int
main()
{ 
return 0;
}

_ACEOF
			rm -f conftest_jni
			$CC -o conftest_jni -I$REDLIB_DIR/$REDLIB_SUB/include conftest_jni.$ac_ext 2>&1 >> /dev/null
			ac_status=$?
			test $ac_status -lt 1 && break
		done
		test $ac_status -lt 1 && break
	done
	REDLIB_TMP="$REDLIB_DIR"
	for REDLIB_DIR in $REDLIB_JNI_DIR; do
		test $ac_status -lt 1 && REDLIB_DIR="$REDLIB_TMP" && break
		for REDLIB_SUB in $REDLIB_JAVA_INSTALL_DIR; do
			test -f $REDLIB_DIR/include/$REDLIB_SUB/jni.h || break
			cat > conftest_jni.$ac_ext <<_ACEOF
#line 11 "jni_h"
#include <jni.h>

int
main()
{ 
return 0;
}

_ACEOF
			rm -f conftest_jni
			$CC -o conftest_jni -I$REDLIB_DIR/$REDLIB_SUB/include conftest_jni.$ac_ext
			ac_status=$?
			test $ac_status -lt 1 && break
		done
		test $ac_status -lt 1 && break
	done
	ac_save_CFLAGS="$CFLAGS"
	JAVA_BIN="$REDLIB_DIR/$REDLIB_SUB/bin/"
	CFLAGS="$CFLAGS -I$REDLIB_DIR/$REDLIB_SUB/include"
	CFLAGS="$CFLAGS -I$REDLIB_DIR/$REDLIB_SUB/include/linux"
	CFLAGS="$CFLAGS -I$REDLIB_DIR/$REDLIB_SUB/include/$target_os"

	AC_MSG_RESULT($JAVA_BIN)
	AC_SUBST(JAVA_BIN)
	AC_MSG_CHECKING([checking for jni.h])
	AC_MSG_RESULT($REDLIB_DIR/$REDLIB_SUB/include)
	AC_SUBST(CFLAGS)
])
