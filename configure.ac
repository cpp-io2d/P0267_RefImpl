AC_INIT([amN3888_RefImpl], [1.4], [mikebmcl@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile N3888_RefImpl/Makefile N3888_RefImpl/src/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG([C++])
dnl AX_CXX_COMPILE_STDCXX_14([noext], [mandatory])
dnl AX_CFLAGS_WARN_ALL
dnl AX_CXXFLAGS_WARN_ALL
dnl AC_CHECK_HEADERS([turbojpeg.h],[],[AC_MSG_ERROR(turbojpeg.h not found. Install libjpeg-turbo)], [AC_INCLUDES_DEFAULT])
dnl AC_SEARCH_LIBS([tjInitCompress],[libturbojpeg],[],[AC_MSG_ERROR(libjpeg-turbo not found. Install libjpeg-turbo)],[-lz -lm])
PKG_CHECK_MODULES([GTKCAIRO], [cairo >= 1.12.16 x11])
PKG_PROG_PKG_CONFIG
AC_ARG_ENABLE([xcb],
[  --enable-xcb       Build with Xcb],
[case "${enableval}" in
  yes) xcb=true && PKG_CHECK_MODULES([xcb], [xcb]) ;;
  no)  xcb=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --with-xcb]) ;;
esac],[xcb=false])
AM_CONDITIONAL([USE_XCB], [test x$xcb = xtrue])
AM_CONDITIONAL([USE_XLIB], [test x$xcb = xfalse])
AC_SUBST([DOLLAR_SIGN],[$])
AC_OUTPUT
