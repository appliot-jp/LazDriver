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

// similar to htons, htonl, ntohs, ntohl
// byte order of IEEE802154e is little endian
#ifdef LITTLE_ENDIAN
#define H2LS(s)		(unsigned short)s
#define H2LL(l)		(unsigned long)l
#define L2HS(s)		(unsigned short)s
#define L2HL(l)		(unsigned long)l
#define H2BLS(b,s)	memcpy(&b,&s,sizeof(unsigned short))
#define H2BLL(b,l)	memcpy(&b,&l,sizeof(unsigned long))
#define BL2HS(s,b)	memcpy(&s,&b,sizeof(unsigned short))
#define BL2HL(l,b)	memcpy(&l,&b,sizeof(unsigned long))
#endif
#ifdef BIG_ENDIAN
#define H2LS(s)		(((unsigned short)s&0x00FF) << 8) | (((unsigned short)s&0xFF00) >> 8)
#define H2LL(l)		(((unsigned long)l&0x000000FF) << 24) |\
					(((unsigned long)l&0x0000FF00) <<8)|\
					(((unsigned long)l&0x00FF0000) >> 8) |\
					(((unsigned long)l&0xFF000000) >> 24) 
#define L2HBS(s) 	(((unsigned short)s&0x00FF) << 8) | (((unsigned short)s&0xFF00) >> 8)
#define L2HBS(l)		(((unsigned long)l&0x000000FF) << 24) |\
					(((unsigned long)l&0x0000FF00) <<8)|\
					(((unsigned long)l&0x00FF0000) >> 8) |\
					(((unsigned long)l&0xFF000000) >> 24) 
#define H2BLS(b,s)	memcpy(&b,&H2LS(s),sizeof(unsigned short))
#define H2BLL(b,l)	memcpy(&b,&H2LL(l),sizeof(unsigned long))
#define BL2HS(s,b)	memcpy(&s,&L2HS(s),sizeof(unsigned short))
#define BL2HL(l,b)	memcpy(&l,&L2HL(l),sizeof(unsigned long))
#endif

#endif
