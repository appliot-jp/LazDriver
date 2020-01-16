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

#if ((!defined(LITTLE_ENDIAN)) & (!defined(BIG_ENDIAN)))
#define LITTLE_ENDIAN
// #define BIG_ENDIAN
#endif

// similar to htons, htonl, ntohs, ntohl
// Little endian's byte buffer to host's endian
// Host's endian to Little endian's byte buffer
#ifdef LITTLE_ENDIAN
#define H2LS(s)		(uint16_t)s
#define H2LL(l)		(uint32_t)l
#define L2HS(s)		(uint16_t)s
#define L2HL(l)		(uint32_t)l
#define H2LBS(b,s)	memcpy(&b,&s,sizeof(uint16_t))
#define H2LBL(b,l)	memcpy(&b,&l,sizeof(uint32_t))
#define LB2HS(s,b)	memcpy(&s,&b,sizeof(uint16_t))
#define LB2HL(l,b)	memcpy(&l,&b,sizeof(uint32_t))
#endif
#ifdef BIG_ENDIAN
#define H2LS(s)		(((uint16_t)s&0x00FF) << 8) | (((uint16_t)s&0xFF00) >> 8)
#define H2LL(l)		(((uint32_t)l&0x000000FF) << 24) |\
					(((uint32_t)l&0x0000FF00) <<8)|\
					(((uint32_t)l&0x00FF0000) >> 8) |\
					(((uint32_t)l&0xFF000000) >> 24) 
#define L2HBS(s) 	(((uint16_t)s&0x00FF) << 8) | (((uint16_t)s&0xFF00) >> 8)
#define L2HBS(l)		(((uint32_t)l&0x000000FF) << 24) |\
					(((uint32_t)l&0x0000FF00) <<8)|\
					(((uint32_t)l&0x00FF0000) >> 8) |\
					(((uint32_t)l&0xFF000000) >> 24) 
#define H2LBS(b,s)	memcpy(&b,&H2LS(s),sizeof(uint16_t))
#define H2LBL(b,l)	memcpy(&b,&H2LL(l),sizeof(uint32_t))
#define LB2HS(s,b)	memcpy(&s,&L2HS(s),sizeof(uint16_t))
#define LB2HL(l,b)	memcpy(&l,&L2HL(l),sizeof(uint32_t))
#endif

#endif
