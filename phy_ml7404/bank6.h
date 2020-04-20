/****************************************************************************************/
/**
   @file     bank6.h

   @brief    RF LSI register information header file
   @version  V1.00
   @date     22. Feb. 2018

   @copyright    Copyright (C) 2018 LAPIS Semiconductor Co., Ltd. All rights reserved.

   @par  
        This software is provided "as is" and any expressed or implied
         warranties, including, but not limited to, the implied warranties of
         merchantability and fitness for a particular purpose are disclaimed.
         LAPIS Semiconductor shall not be liable for any direct, indirect, consequential or 
         incidental damages arising from using or modifying this software.
         You (customer) can modify and use this software in whole or part on
         your own responsibility, only for the purpose of developing the software
         for use with microcontroller manufactured by LAPIS Semiconductor.
    
*******************************************************************************************/
#ifndef _bank6_H
#define _bank6_H

/**
    \addtogroup RF_REGISTER_BANK6
    \{
*/
 
/*［BANK6 Register Address Definitions｜BANK6レジスタアドレス定義］*/
#define RADIO_MOD_CTRL_ADR              (0x01u)     /*!< ［｜<in-house>*TODO*英訳｜変調方式設定(@ref RADIO_MOD_CTRL_T 型でアクセス)］ */
#define RADIO_FEC_CTRL_MRR_ADR          (0x02u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_FEC_CTRL_MRR_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B6_ADR03        (0x03u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR04        (0x04u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR05        (0x05u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR06        (0x06u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR07        (0x07u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR08        (0x08u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR09        (0x09u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR0A        (0x0Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR0B        (0x0Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR0C        (0x0Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR0D        (0x0Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR0E        (0x0Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR0F        (0x0Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR10        (0x10u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR11        (0x11u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR12        (0x12u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR13        (0x13u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR14        (0x14u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR15        (0x15u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR16        (0x16u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR17        (0x17u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR18        (0x18u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR19        (0x19u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR1A        (0x1Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR1B        (0x1Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR1C        (0x1Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR1D        (0x1Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR1E        (0x1Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR1F        (0x1Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR20        (0x20u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR21        (0x21u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR22        (0x22u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR23        (0x23u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR24        (0x24u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR25        (0x25u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR26        (0x26u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR27        (0x27u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR28        (0x28u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR29        (0x29u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR2A        (0x2Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR2B        (0x2Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR2C        (0x2Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR2D        (0x2Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR2E        (0x2Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR2F        (0x2Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR30        (0x30u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR31        (0x31u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR32        (0x32u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR33        (0x33u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR34        (0x34u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR35        (0x35u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR36        (0x36u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR37        (0x37u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR38        (0x38u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR39        (0x39u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR3A        (0x3Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR3B        (0x3Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR3C        (0x3Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR3D        (0x3Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR3E        (0x3Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR3F        (0x3Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR40        (0x40u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR41        (0x41u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR42        (0x42u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR43        (0x43u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR44        (0x44u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR45        (0x45u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR46        (0x46u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR47        (0x47u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR48        (0x48u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR49        (0x49u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR4A        (0x4Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR4B        (0x4Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR4C        (0x4Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR4D        (0x4Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR4E        (0x4Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR4F        (0x4Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR50        (0x50u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR51        (0x51u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR52        (0x52u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR53        (0x53u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR54        (0x54u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR55        (0x55u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR56        (0x56u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR57        (0x57u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR58        (0x58u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR59        (0x59u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR5A        (0x5Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR5B        (0x5Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR5C        (0x5Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR5D        (0x5Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR5E        (0x5Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR5F        (0x5Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR60        (0x60u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR61        (0x61u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR62        (0x62u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR63        (0x63u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR64        (0x64u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR65        (0x65u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR66        (0x66u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR67        (0x67u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR68        (0x68u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR69        (0x69u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR6A        (0x6Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR6B        (0x6Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR6C        (0x6Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR6D        (0x6Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR6E        (0x6Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR6F        (0x6Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR70        (0x70u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR71        (0x71u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR72        (0x72u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR73        (0x73u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR74        (0x74u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR75        (0x75u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR76        (0x76u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR77        (0x77u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR78        (0x78u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR79        (0x79u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B6_ADR7A        (0x7Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_BPSK_PLL_CTRL_ADR         (0x7Bu)     /*!< ［｜<in-house>*TODO*英訳｜BPSK方式設定(@ref RADIO_BPSK_PLL_CTRL_T 型でアクセス)］ */
#define RADIO_BPSK_P_START_H_ADR        (0x7Cu)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位開始時間設定(上位3ビット)(@ref RADIO_BPSK_P_START_H_T 型でアクセス)］ */
#define RADIO_BPSK_P_START_L_ADR        (0x7Du)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位開始時間設定(下位バイト)(@ref RADIO_BPSK_P_START_L_T 型でアクセス)］ */
#define RADIO_BPSK_P_HOLD_H_ADR         (0x7Eu)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位保持時間設定(上位4ビット)(@ref RADIO_BPSK_P_HOLD_H_T 型でアクセス)］ */
#define RADIO_BPSK_P_HOLD_L_ADR         (0x7Fu)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位保持時間設定(下位バイト)(@ref RADIO_BPSK_P_HOLD_L_T 型でアクセス)］ */

#define BANK_MOD_CTRL_ADR              (6)     /*!< ［｜<in-house>*TODO*英訳｜変調方式設定(@ref RADIO_MOD_CTRL_T 型でアクセス)］ */
#define BANK_FEC_CTRL_MRR_ADR          (6)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_FEC_CTRL_MRR_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B6_ADR03        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR04        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR05        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR06        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR07        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR08        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR09        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR0A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR0B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR0C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR0D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR0E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR0F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR10        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR11        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR12        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR13        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR14        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR15        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR16        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR17        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR18        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR19        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR1A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR1B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR1C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR1D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR1E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR1F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR20        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR21        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR22        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR23        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR24        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR25        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR26        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR27        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR28        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR29        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR2A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR2B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR2C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR2D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR2E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR2F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR30        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR31        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR32        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR33        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR34        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR35        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR36        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR37        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR38        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR39        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR3A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR3B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR3C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR3D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR3E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR3F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR40        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR41        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR42        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR43        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR44        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR45        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR46        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR47        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR48        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR49        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR4A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR4B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR4C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR4D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR4E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR4F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR50        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR51        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR52        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR53        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR54        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR55        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR56        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR57        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR58        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR59        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR5A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR5B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR5C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR5D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR5E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR5F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR60        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR61        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR62        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR63        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR64        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR65        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR66        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR67        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR68        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR69        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR6A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR6B        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR6C        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR6D        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR6E        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR6F        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR70        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR71        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR72        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR73        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR74        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR75        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR76        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR77        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR78        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR79        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B6_ADR7A        (6)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_BPSK_PLL_CTRL_ADR         (6)     /*!< ［｜<in-house>*TODO*英訳｜BPSK方式設定(@ref RADIO_BPSK_PLL_CTRL_T 型でアクセス)］ */
#define BANK_BPSK_P_START_H_ADR        (6)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位開始時間設定(上位3ビット)(@ref RADIO_BPSK_P_START_H_T 型でアクセス)］ */
#define BANK_BPSK_P_START_L_ADR        (6)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位開始時間設定(下位バイト)(@ref RADIO_BPSK_P_START_L_T 型でアクセス)］ */
#define BANK_BPSK_P_HOLD_H_ADR         (6)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位保持時間設定(上位4ビット)(@ref RADIO_BPSK_P_HOLD_H_T 型でアクセス)］ */
#define BANK_BPSK_P_HOLD_L_ADR         (6)     /*!< ［｜<in-house>*TODO*英訳｜BPSK周波数制御時の周波数偏位保持時間設定(下位バイト)(@ref RADIO_BPSK_P_HOLD_L_T 型でアクセス)］ */


/* ［RF register structures｜RFレジスタ構造体］ */

/** @brief ［Type definition for @ref RADIO_MOD_CTRL_ADR access｜@ref RADIO_MOD_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t mod_type:           2;      /*!<［｜<in-house>*TODO*英訳｜変調方式設定 R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_MOD_CTRL_T;

/** @brief ［Type definition for @ref RADIO_FEC_CTRL_MRR_ADR access｜@ref RADIO_FEC_CTRL_MRR_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fec_en:             1;      /*!<［｜<in-house>*TODO*英訳｜FEC設定 R/W］*/
        uint8_t fec_scheme:         1;      /*!<［｜<in-house>*TODO*英訳｜FEC方式設定 R/W］*/
        uint8_t intlv_en:           1;      /*!<［｜<in-house>*TODO*英訳｜インターリーブ設定 R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FEC_CTRL_MRR_T;

/** @brief ［Type definition for @ref RADIO_BPSK_PLL_CTRL_ADR access｜@ref RADIO_BPSK_PLL_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_pll_ctrl:      1;      /*!<［｜<in-house>*TODO*英訳｜BPSK方式選択設定 R/W］*/
        uint8_t bpsk_p_clksel:      1;      /*!<［｜<in-house>*TODO*英訳｜BPSK PLL制御時の周波数偏位時間算出用クロック選択 R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_PLL_CTRL_T;

/** @brief ［Type definition for @ref RADIO_BPSK_P_START_H_ADR access｜@ref RADIO_BPSK_P_START_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_p_start_h:     3;      /*!<［｜<in-house>*TODO*英訳｜BPSK 周波数制御時の周波数偏位開始時間(上位3ビット) R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_P_START_H_T;

/** @brief ［Type definition for @ref RADIO_BPSK_P_START_L_ADR access｜@ref RADIO_BPSK_P_START_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_p_start_l:     8;      /*!<［｜<in-house>*TODO*英訳｜BPSK 周波数制御時の周波数偏位開始時間(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_P_START_L_T;

/** @brief ［Type definition for @ref RADIO_BPSK_P_HOLD_H_ADR access｜@ref RADIO_BPSK_P_HOLD_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_p_hold_h:      4;      /*!<［｜<in-house>*TODO*英訳｜BPSK 周波数制御時の周波数偏位保持時間(上位4ビット) R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_P_HOLD_H_T;

/** @brief ［Type definition for @ref RADIO_BPSK_P_HOLD_L_ADR access｜@ref RADIO_BPSK_P_HOLD_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_p_hold_l:      8;      /*!<［｜<in-house>*TODO*英訳｜BPSK 周波数制御時の周波数偏位保持時間(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_P_HOLD_L_T;

/** \} */ /* End of group RF_REGISTER_BANK6 */
#endif
