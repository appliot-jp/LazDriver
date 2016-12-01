/* endian.h
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */


#ifndef	_ENDIAN_H_
#define _ENDIAN_H_

#define LITTLE_ENDIAN
// #define BIG_ENDIAN

#ifdef LITTLE_ENDIAN
#define htons(s)  s
#define htonl(l)  l
#define ntohs(s)  s
#define ntohl(l)  l
#endif
#ifdef BIG_ENDIAN
#define htons(s)  s
#define htonl(l)  l
#define ntohs(s)  s
#define ntohl(l)  l
#endif

#endif
