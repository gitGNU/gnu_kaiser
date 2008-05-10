/*
 * errno.h - define various errors and macros to manipulate them
 *
 * Copyright (C) 2008 John 'Ykstort' Doyle
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __ERRNO_H__
#define __ERRNO_H__
#define ENOMEM	12
#define EINVAL	22
#ifndef __ASM__
/*
 * @PTR_ERR(x)		- returns an error pointer calculated from x
 *			- read as PTR from ERR
 * @PTR_ISERR(x)	- checks if x is an error pointer
 * @ERR_PTR(x)		- unpacks the error value from error pointer x
 * 			- read as ERR from PTR
 */
#define PTR_ERR(x)	((-((unsigned int)x))&0xfeffffff)
#define PTR_ISERR(x)	((((unsigned int)x)&0xffff0000) == 0xfeff0000)
#define ERR_PTR(x)	(-(((unsigned int)x)|0x01000000))
#endif /* __ASM__ */
#endif /* __ERRNO_H__ */
