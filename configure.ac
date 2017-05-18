AC_INIT([amP0267_RefImpl], [1.5], [mikebmcl@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT([disable-shared])

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_RANLIB

AC_SUBST([LIBTOOL_DEPS])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile N3888_RefImpl/Makefile N3888_RefImpl/src/Makefile])

AC_LANG([C++])

dnl AX_CXX_COMPILE_STDCXX_14([noext], [mandatory])
dnl AX_CFLAGS_WARN_ALL
dnl AX_CXXFLAGS_WARN_ALL

AC_CHECK_HEADERS([filesystem],[],[],[AC_INCLUDES_DEFAULT])

AC_CHECK_HEADERS([turbojpeg.h],[],[AC_MSG_ERROR(turbojpeg.h not found. Install libjpeg-turbo, called libturbojpeg on Ubuntu and possibly other distros)],[AC_INCLUDES_DEFAULT])

AC_SEARCH_LIBS([zlibVersion],[z],[],[AC_MSG_ERROR(zlib not found. Install zlib)],[-lm])

AC_SEARCH_LIBS([png_access_version_number],[png],[],[AC_MSG_ERROR(libpng not found. Install libpng)],[-lz -lm])

AC_SEARCH_LIBS([tjInitCompress],[jpeg turbojpeg],[],[AC_MSG_ERROR(libjpeg-turbo not found. Install libjpeg-turbo, called libturbojpeg on Ubuntu and possibly other distros)],[-lz -lm])

PKG_CHECK_MODULES([CAIRO], [cairo >= 1.12.16 x11])
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
