dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------
AC_INIT([libadevs], [3.3])
AC_CONFIG_SRCDIR([include/adevs.h])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------
AM_INIT_AUTOMAKE

dnl --------------------------------
dnl Checks for programs.
dnl --------------------------------
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AX_OPENMP

dnl -----------------------------------------------
dnl Checks for libraries
dnl -----------------------------------------------
# Check for X11
AC_PATH_X
AC_PATH_XTRA

X_CFLAGS="-I$x_includes"
X_LIBS="-L$x_libraries -lXll"

AC_SUBST(X__CFLAGS)
AC_SUBST(X__LIBS)

dnl -----------------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------------
AC_OUTPUT(Makefile \
	  pkgconfig/adevs.pc \
	  src/Makefile
)

