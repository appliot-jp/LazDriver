/* aes.h
 *
 * Copyright (c) 2016  Lapis Semiconductor Co.,Ltd.
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

#ifndef _AES_H_
#define _AES_H_

#ifdef LAZURITE_IDE
#include <lazurite.h>
#else
#include <linux/kernel.h>
#endif


// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES128 encryption in CBC-mode of operation and handles 0-padding.
// ECB enables the basic ECB 16-byte block algorithm. Both can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
  #define CBC 1
#endif

#ifndef ECB
  #define ECB 1
#endif



#if defined(ECB) && ECB

void AES128_ECB_encrypt(uint8_t* input, const uint8_t* key, uint8_t *output);
void AES128_ECB_decrypt(uint8_t* input, const uint8_t* key, uint8_t *output);

#endif // #if defined(ECB) && ECB


#if defined(CBC) && CBC

//void AES128_CBC_encrypt_buffer(uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, const uint8_t* iv);
//void AES128_CBC_decrypt_buffer(uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, const uint8_t* iv);
void AES128_CBC_encrypt_buffer(uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, uint8_t* iv);
void AES128_CBC_decrypt_buffer(uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, uint8_t* iv);

#endif // #if defined(CBC) && CBC

// 2016.11.15 Eiichi Saito AES
uint8_t AES128_CBC_encrypt (uint8_t* output, uint8_t* input, uint32_t length, uint8_t index);
uint8_t AES128_CBC_decrypt (uint8_t* output, uint8_t* input, uint32_t length, uint8_t index);
void AES128_setAes(uint8_t *key, uint8_t *workspace);
uint8_t AES128_getStatus(void);


#endif //_AES_H_
