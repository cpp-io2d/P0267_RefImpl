AC_INIT([P0267_RefImpl], [1.6], [mikebmcl@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_AR
LT_INIT([disable-shared])

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXX_C_O

AC_SUBST([LIBTOOL_DEPS])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile P0267_RefImpl/Makefile P0267_RefImpl/P0267_RefImpl/Makefile P0267_RefImpl/SampleApp/Makefile P0267_RefImpl/RocksInSpace/Makefile])

AC_LANG([C++])

dnl AX_CXX_COMPILE_STDCXX_14([noext], [mandatory])
dnl AX_CFLAGS_WARN_ALL
dnl AX_CXXFLAGS_WARN_ALL

AC_CHECK_HEADERS([filesystem],[],[],[AC_INCLUDES_DEFAULT])

dnl AC_CHECK_HEADERS([turbojpeg.h],[],[AC_MSG_ERROR(turbojpeg.h not found. Install libjpeg-turbo, called libturbojpeg on Ubuntu and possibly other distros)],[AC_INCLUDES_DEFAULT])

AC_SEARCH_LIBS([zlibVersion],[z],[],[AC_MSG_ERROR(zlib not found. Install zlib)],[-lm])

dnl AC_SEARCH_LIBS([png_access_version_number],[png],[],[AC_MSG_ERROR(libpng not found. Install libpng)],[-lz -lm])

dnl AC_SEARCH_LIBS([tjInitCompress],[jpeg turbojpeg],[],[AC_MSG_ERROR(libjpeg-turbo not found. Install libjpeg-turbo, called libturbojpeg on Ubuntu and possibly other distros)],[-lz -lm])

AC_CHECK_PROG([graphmag], [GraphicsMagick-config], [true], [false])
AS_IF([test x$graphmag = xfalse], [AC_MSG_ERROR(GraphicsMagick not found. Install GraphicsMagick)])
AC_DEFINE([HAS_GRAPHICKS_MAGICK], [1], [Define if GraphicsMagick is available])
dnl GRAPHMAG_CPPFLAGS =           `GraphicsMagick-config --cppflags`
dnl GRAPHMAG_LDFLAGS =            `GraphicsMagick-config --ldflags`
dnl GRAPHMAG_LIBS =              `GraphicsMagick-config --libs`
AC_SUBST([GRAPHMAG_CPPFLAGS], ["`GraphicsMagick-config --cppflags`"])
AC_SUBST([GRAPHMAG_LDFLAGS], ["`GraphicsMagick-config --ldflags`"])
AC_SUBST([GRAPHMAG_LIBS], ["`GraphicsMagick-config --libs`"])

PKG_CHECK_MODULES([CAIRO], [cairo >= 1.12.16])
PKG_CHECK_MODULES([X11], [x11])
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
