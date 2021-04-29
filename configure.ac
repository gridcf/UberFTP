dnl
dnl  University of Illinois/NCSA Open Source License
dnl
dnl  Copyright (c) 2003-2014, NCSA.  All rights reserved.
dnl
dnl  Developed by:
dnl
dnl  Storage Enabling Technologies (SET)
dnl
dnl  Nation Center for Supercomputing Applications (NCSA)
dnl
dnl  http://dims.ncsa.uiuc.edu/set/uberftp
dnl
dnl  Permission is hereby granted, free of charge, to any person obtaining a
dnl  copy of this software and associated documentation files (the .Software.),
dnl  to deal with the Software without restriction, including without limitation
dnl  the rights to use, copy, modify, merge, publish, distribute, sublicense,
dnl  and/or sell copies of the Software, and to permit persons to whom the
dnl  Software is furnished to do so, subject to the following conditions:
dnl
dnl     + Redistributions of source code must retain the above copyright notice,
dnl       this list of conditions and the following disclaimers.
dnl
dnl     + Redistributions in binary form must reproduce the above copyright
dnl       notice, this list of conditions and the following disclaimers in the
dnl       documentation and/or other materials provided with the distribution.
dnl
dnl     + Neither the names of SET, NCSA
dnl       nor the names of its contributors may be used to endorse or promote
dnl       products derived from this Software without specific prior written
dnl       permission.
dnl
dnl  THE SOFTWARE IS PROVIDED .AS IS., WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
dnl  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
dnl  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
dnl  THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
dnl  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
dnl  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
dnl  DEALINGS WITH THE SOFTWARE.
dnl

dnl Process this file with autoconf to produce a configure script.
# First [] is used as the prompt
# Last [] is used for the version information
AC_INIT(UberFTP (2.9 Beta), [2.9-Beta], [Grid Community Forum <discuss@gridcf.org>],[uberftp-client])
AM_INIT_AUTOMAKE([foreign]) 

# Check for C compiler and pre-processor
AC_PROG_CC
AC_PROG_CPP

# Check for an MSSFTP build
AC_ARG_ENABLE(mssftp,
	[  --enable-mssftp              enable mssftp support ],
	[  mssftp="$enableval" ],
	[  mssftp="no" ]
)

if test "x$mssftp" == "xyes" ; then
	AC_DEFINE(MSSFTP, 1, [ Whether to build in mssftp functionality ])
fi

AC_ARG_ENABLE(msshost,
	[  --enable-msshost=HOSTNAME    set the MSS host to connect to ],
	[  msshost="$enableval"  ],
	[  msshost="mss.ncsa.uiuc.edu"  ]
)
AC_DEFINE_UNQUOTED(MSSHOST, "$msshost", [ MSS to connect to ])

AC_ARG_ENABLE(mssftp-gsi-service,
	[  --enable-mssftp-gsi-service  mssftp will use a GSI service cert ],
	[  msssrvc="$enableval" ],
	[  msssrvc="no" ]
)

if test "x$msssrvc" == "xyes" ; then
	AC_DEFINE(MSSFTP_GSI_SERVICE, 1, [ mssftp will use a GSI service cert ])
fi

# Default TPC Window Sizing
AC_ARG_ENABLE(tcp-window,
	[  --enable-tcp-window=value    default value for TCP Windows ],
	[  default_tcp_window="$enableval" ],
	[  default_tcp_window=0 ]
)
AC_DEFINE_UNQUOTED(DEFAULT_TCP_BUFFER_SIZE, $default_tcp_window, [ Setting the default TCP window settings ])

# Default Internal Buffer sizing
AC_ARG_ENABLE(blksize,
	[  --enable-blksize=value       default size of internal buffers ],
	[  default_blksize="$enableval" ],
	[  default_blksize=1048576 ]
)
AC_DEFINE_UNQUOTED(DEFAULT_BLKSIZE, $default_blksize, [ Setting the default buffer size ])


# Tru64 fix
AC_CHECK_FUNCS(strtoll)

#
# Globus Setup
#

AC_ARG_WITH(globus,
	[  --with-globus=value     location of Globus installation, defaults to /usr],
	[  globus_location="$withval" ],
	[  globus_location="GLOBUS_DEFAULT_LOCATION" ]
)

#
# globus_common.h depends on globus_config.h, so do it first
#

if test "x$globus_location" == "xGLOBUS_DEFAULT_LOCATION" ; then
	# Using defaults, check pkg-config first
	PKG_CHECK_MODULES([GLOBUS_COMMON], [globus-common], have_globus_common=yes, have_globus_common=no)
	if test "x$have_globus_common" == "xyes" ;then
		# We're using pkg-config, check also for other modules
		PKG_CHECK_MODULES([GLOBUS_GSSAPI_GSI], [globus-gssapi-gsi],
				  [],
				  [AC_MSG_ERROR([missing globus-gssapi-gsi])])
		CPPFLAGS="$GLOBUS_COMMON_CFLAGS $GLOBUS_GSSAPI_GSI_CFLAGS $CPPFLAGS"
		LDFLAGS="$GLOBUS_COMMON_LIBS $GLOBUS_GSSAPI_GSI_LIBS $LDFLAGS"
	else
		# Manually check installation in default (RPM) location
		CPPFLAGS="$CPPFLAGS -I/usr/include/globus"
		AC_CHECK_HEADERS([globus_config.h globus_common.h],
				 [], 
				 [AC_MSG_ERROR([globus header files not found, install globus-common])])
		LDFLAGS="$LDFLAGS -L/usr/lib64/ -L/usr/lib"
	fi
else
	# Installation using specified location
	CPPFLAGS="-I$globus_location/include $CPPFLAGS"
	AC_CHECK_HEADERS([globus_config.h globus_common.h],
	                 [], 
	                 [AC_MSG_ERROR([globus header files not found in $globus_location])])
	LDFLAGS="-L$globus_location/lib64/ -L$globus_location/lib/ $LDFLAGS"
fi

#
# Find the needed Globus libraries
#
AC_CHECK_LIB([globus_common],
             [globus_module_activate], 
             [], 
             [AC_MSG_ERROR([libglobus_common.so not found])])

AC_CHECK_LIB([globus_gssapi_gsi], 
             [gss_wrap], 
             [], 
             [AC_MSG_ERROR([libglobus_gssapi_gsi.so not found])])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
