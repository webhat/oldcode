dnl AM_PATH_MODULE_H

AC_DEFUN(AM_PATH_MODULE_H,
[AC_MSG_CHECKING([module install dir])
	MODULE_CONFIG_DIR=""

	if test x$prefix = "xNONE"; then
		MODULE_CONFIG_DIR=$ac_default_prefix/redlib/module/
	else
		MODULE_CONFIG_DIR=$prefix/redlib/module/
	fi
	AC_MSG_RESULT($MODULE_CONFIG_DIR)
	AC_SUBST(MODULE_CONFIG_DIR)
])
