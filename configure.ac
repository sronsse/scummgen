m4_define(scummgen_version_major, 0)
m4_define(scummgen_version_minor, 1)
m4_define(scummgen_version_micro, 0)

AC_INIT([ScummGEN], scummgen_version_major.scummgen_version_minor.scummgen_version_micro)
AC_CONFIG_AUX_DIR([build])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CXX
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_LIBTOOL

PKG_CHECK_MODULES(XML, [libxml-2.0])
AC_SUBST(XML_CFLAGS)
AC_SUBST(XML_LIBS)

AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.hpp])
AC_CONFIG_FILES([Makefile \
                 src/Makefile \
                 src/blocks/Makefile \
                 src/grammar/Makefile \
                 src/types/Makefile \
                 src/util/Makefile])

AC_OUTPUT
