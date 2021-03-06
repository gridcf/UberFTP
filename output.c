/*
 * University of Illinois/NCSA Open Source License
 *
 * Copyright (c) 2003-2012 NCSA.  All rights reserved.
 *
 * Developed by:
 *
 * Storage Enabling Technologies (SET)
 *
 * Nation Center for Supercomputing Applications (NCSA)
 *
 * http://dims.ncsa.uiuc.edu/set/uberftp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the .Software.),
 * to deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *    + Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimers.
 *
 *    + Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimers in the
 *      documentation and/or other materials provided with the distribution.
 *
 *    + Neither the names of SET, NCSA
 *      nor the names of its contributors may be used to endorse or promote
 *      products derived from this Software without specific prior written
 *      permission.
 *
 * THE SOFTWARE IS PROVIDED .AS IS., WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 */
#ifndef UBER_OUTPUT_H
#define UBER_OUTOUT_H

#include <stdarg.h>
#include <stdio.h>

#include "settings.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif /* DMALLOC */


void
o_printf(int dbglvl, char * format, ...)
{
	va_list ap;

	if (dbglvl > s_debug())
		return;

	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);

	fflush(stdout);
}

void
o_fprintf(FILE * str, int dbglvl, char * format, ...)
{
	va_list ap;

	if (dbglvl > s_debug())
		return;

	va_start(ap, format);
	vfprintf(str, format, ap);
	va_end(ap);

	fflush(str);
}

void
o_fwrite(FILE * fptr, int dbglvl, char * str, size_t len)
{
	if (dbglvl > s_debug())
		return;

	fwrite(str, sizeof(char), len, fptr);

	fflush(fptr);
}

#endif /* UBER_OUTPUT_H */
