AC_INIT([amN3888_RefImpl], [1.0], [mikebmcl@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile N3888_RefImpl/Makefile N3888_RefImpl/src/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])
AX_CFLAGS_WARN_ALL
AX_CXXFLAGS_WARN_ALL
PKG_CHECK_MODULES([GTKCAIRO], [gtk+-3.0 >= 3.8.0 gmodule-2.0 gobject-2.0 cairo >= 1.12.16 x11])
AC_SUBST([DOLLAR_SIGN],[$])
AC_OUTPUT
