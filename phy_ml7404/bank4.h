/****************************************************************************************/
/**
   @file     bank4.h

   @brief    RF LSI register information header file
   @version  V1.00
   @date     26. Feb. 2018

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
#ifndef _bank4_H
#define _bank4_H

/**
    \addtogroup RF_REGISTER_BANK4
    \{
 */
 
/*［BANK4 Register Address Definitions｜BANK4レジスタアドレス定義］*/
#define RADIO_C_CHECK_CTRL_B4_ADR       (0x01u)     /*!< ［｜<in-house>*TODO*英訳｜C-fieldチェックイネーブル(@ref RADIO_C_CHECK_CTRL_B4_T 型でアクセス)］ */
#define RADIO_M_CHECK_CTRL_B4_ADR       (0x02u)     /*!< ［｜<in-house>*TODO*英訳｜M-fieldチェックイネーブル(@ref RADIO_M_CHECK_CTRL_B4_T 型でアクセス)］ */
#define RADIO_A_CHECK_CTRL2_ADR         (0x03u)     /*!< ［｜<in-house>*TODO*英訳｜A-fieldチェックイネーブル2(@ref RADIO_A_CHECK_CTRL2_T 型でアクセス)］ */
#define RADIO_A_CHECK_CTRL1_ADR         (0x04u)     /*!< ［｜<in-house>*TODO*英訳｜A-fieldチェックイネーブル1(@ref RADIO_A_CHECK_CTRL1_T 型でアクセス)］ */
#define RADIO_C_FIELD_WORD1_B4_ADR      (0x05u)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード1(@ref RADIO_C_FIELD_WORD1_B4_T 型でアクセス)］ */
#define RADIO_C_FIELD_WORD2_B4_ADR      (0x06u)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード2(@ref RADIO_C_FIELD_WORD2_B4_T 型でアクセス)］ */
#define RADIO_C_FIELD_WORD3_B4_ADR      (0x07u)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード3(@ref RADIO_C_FIELD_WORD3_B4_T 型でアクセス)］ */
#define RADIO_C_FIELD_WORD4_B4_ADR      (0x08u)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード4(@ref RADIO_C_FIELD_WORD4_B4_T 型でアクセス)］ */
#define RADIO_C_FIELD_WORD5_B4_ADR      (0x09u)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード5(@ref RADIO_C_FIELD_WORD5_B4_T 型でアクセス)］ */
#define RADIO_M_FIELD_WORD1_B4_ADR      (0x0Au)     /*!< ［｜<in-house>*TODO*英訳｜M-field 1stバイト設定コード1(@ref RADIO_M_FIELD_WORD1_B4_T 型でアクセス)］ */
#define RADIO_M_FIELD_WORD2_B4_ADR      (0x0Bu)     /*!< ［｜<in-house>*TODO*英訳｜M-field 1stバイト設定コード2(@ref RADIO_M_FIELD_WORD2_B4_T 型でアクセス)］ */
#define RADIO_M_FIELD_WORD3_B4_ADR      (0x0Cu)     /*!< ［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定コード1(@ref RADIO_M_FIELD_WORD3_B4_T 型でアクセス)］ */
#define RADIO_M_FIELD_WORD4_B4_ADR      (0x0Du)     /*!< ［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定コード2(@ref RADIO_M_FIELD_WORD4_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD1_B4_ADR      (0x0Eu)     /*!< ［｜<in-house>*TODO*英訳｜A-field 1stバイト設定(@ref RADIO_A_FIELD_WORD1_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD2_B4_ADR      (0x0Fu)     /*!< ［｜<in-house>*TODO*英訳｜A-field 2ndバイト設定(@ref RADIO_A_FIELD_WORD2_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD3_B4_ADR      (0x10u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 3rdバイト設定(@ref RADIO_A_FIELD_WORD3_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD4_B4_ADR      (0x11u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 4thバイト設定(@ref RADIO_A_FIELD_WORD4_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD5_B4_ADR      (0x12u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 5thバイト設定(@ref RADIO_A_FIELD_WORD5_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD6_B4_ADR      (0x13u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 6thバイト設定(@ref RADIO_A_FIELD_WORD6_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD7_B4_ADR      (0x14u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 7thバイト設定(@ref RADIO_A_FIELD_WORD7_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD8_B4_ADR      (0x15u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 8thバイト設定(@ref RADIO_A_FIELD_WORD8_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD9_B4_ADR      (0x16u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 9thバイト設定(@ref RADIO_A_FIELD_WORD9_B4_T 型でアクセス)］ */
#define RADIO_A_FIELD_WORD10_B4_ADR     (0x17u)     /*!< ［｜<in-house>*TODO*英訳｜A-field 10thバイト設定(@ref RADIO_A_FIELD_WORD10_B4_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B4_ADR18        (0x18u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR19        (0x19u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR1A        (0x1Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR1B        (0x1Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR1C        (0x1Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR1D        (0x1Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR1E        (0x1Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR1F        (0x1Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_CMA2_CHECK_CTRL1_ADR      (0x20u)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field2チェックイネーブル1(@ref RADIO_CMA2_CHECK_CTRL1_T 型でアクセス)］ */
#define RADIO_CMA2_CHECK_CTRL2_ADR      (0x21u)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field2チェックイネーブル2(@ref RADIO_CMA2_CHECK_CTRL2_T 型でアクセス)］ */
#define RADIO_C2_FIELD_WORD1_ADR        (0x22u)     /*!< ［｜<in-house>*TODO*英訳｜C-field2設定(@ref RADIO_C2_FIELD_WORD1_T 型でアクセス)］ */
#define RADIO_M2_FIELD_WORD1_ADR        (0x23u)     /*!< ［｜<in-house>*TODO*英訳｜M-field2 1stバイト設定(@ref RADIO_M2_FIELD_WORD1_T 型でアクセス)］ */
#define RADIO_M2_FIELD_WORD2_ADR        (0x24u)     /*!< ［｜<in-house>*TODO*英訳｜M-field2 2ndバイト設定(@ref RADIO_M2_FIELD_WORD2_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD1_ADR        (0x25u)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 1stバイト設定(@ref RADIO_A2_FIELD_WORD1_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD2_ADR        (0x26u)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 2ndバイト設定(@ref RADIO_A2_FIELD_WORD2_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD3_ADR        (0x27u)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 3rdバイト設定(@ref RADIO_A2_FIELD_WORD3_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD4_ADR        (0x28u)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 4thバイト設定(@ref RADIO_A2_FIELD_WORD4_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD5_ADR        (0x29u)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 5thバイト設定(@ref RADIO_A2_FIELD_WORD5_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD6_ADR        (0x2Au)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 6thバイト設定(@ref RADIO_A2_FIELD_WORD6_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD7_ADR        (0x2Bu)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 7thバイト設定(@ref RADIO_A2_FIELD_WORD7_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD8_ADR        (0x2Cu)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 8thバイト設定(@ref RADIO_A2_FIELD_WORD8_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD9_ADR        (0x2Du)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 9thバイト設定(@ref RADIO_A2_FIELD_WORD9_T 型でアクセス)］ */
#define RADIO_A2_FIELD_WORD10_ADR       (0x2Eu)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 10thバイト設定(@ref RADIO_A2_FIELD_WORD10_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B4_ADR2F        (0x2Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_CMA3_CHECK_CTRL1_ADR      (0x30u)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field3チェックイネーブル1(@ref RADIO_CMA3_CHECK_CTRL1_T 型でアクセス)］ */
#define RADIO_CMA3_CHECK_CTRL2_ADR      (0x31u)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field3チェックイネーブル2(@ref RADIO_CMA3_CHECK_CTRL2_T 型でアクセス)］ */
#define RADIO_C3_FIELD_WORD1_ADR        (0x32u)     /*!< ［｜<in-house>*TODO*英訳｜C-field3設定(@ref RADIO_C3_FIELD_WORD1_T 型でアクセス)］ */
#define RADIO_M3_FIELD_WORD1_ADR        (0x33u)     /*!< ［｜<in-house>*TODO*英訳｜M-field3 1stバイト設定(@ref RADIO_M3_FIELD_WORD1_T 型でアクセス)］ */
#define RADIO_M3_FIELD_WORD2_ADR        (0x34u)     /*!< ［｜<in-house>*TODO*英訳｜M-field3 2ndバイト設定(@ref RADIO_M3_FIELD_WORD2_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD1_ADR        (0x35u)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 1stバイト設定(@ref RADIO_A3_FIELD_WORD1_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD2_ADR        (0x36u)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 2ndバイト設定(@ref RADIO_A3_FIELD_WORD2_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD3_ADR        (0x37u)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 3rdバイト設定(@ref RADIO_A3_FIELD_WORD3_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD4_ADR        (0x38u)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 4thバイト設定(@ref RADIO_A3_FIELD_WORD4_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD5_ADR        (0x39u)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 5thバイト設定(@ref RADIO_A3_FIELD_WORD5_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD6_ADR        (0x3Au)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 6thバイト設定(@ref RADIO_A3_FIELD_WORD6_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD7_ADR        (0x3Bu)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 7thバイト設定(@ref RADIO_A3_FIELD_WORD7_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD8_ADR        (0x3Cu)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 8thバイト設定(@ref RADIO_A3_FIELD_WORD8_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD9_ADR        (0x3Du)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 9thバイト設定(@ref RADIO_A3_FIELD_WORD9_T 型でアクセス)］ */
#define RADIO_A3_FIELD_WORD10_ADR       (0x3Eu)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 10thバイト設定(@ref RADIO_A3_FIELD_WORD10_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B4_ADR3F        (0x3Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR40        (0x40u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR41        (0x41u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR42        (0x42u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR43        (0x43u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR44        (0x44u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR45        (0x45u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR46        (0x46u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR47        (0x47u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR48        (0x48u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR49        (0x49u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR4A        (0x4Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR4B        (0x4Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR4C        (0x4Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR4D        (0x4Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR4E        (0x4Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR4F        (0x4Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR50        (0x50u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR51        (0x51u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR52        (0x52u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR53        (0x53u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR54        (0x54u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR55        (0x55u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR56        (0x56u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR57        (0x57u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR58        (0x58u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR59        (0x59u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR5A        (0x5Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR5B        (0x5Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR5C        (0x5Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR5D        (0x5Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR5E        (0x5Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR5F        (0x5Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_TXFREQ_I_2G_ADR           (0x60u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Iカウンタ)(@ref RADIO_TXFREQ_I_2G_T 型でアクセス)］ */
#define RADIO_TXFREQ_FH_2G_ADR          (0x61u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Fカウンタ上位4ビット)(@ref RADIO_TXFREQ_FH_2G_T 型でアクセス)］ */
#define RADIO_TXFREQ_FM_2G_ADR          (0x62u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Fカウンタ中位8ビット)(@ref RADIO_TXFREQ_FM_2G_T 型でアクセス)］ */
#define RADIO_TXFREQ_FL_2G_ADR          (0x63u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Fカウンタ下位8ビット)(@ref RADIO_TXFREQ_FL_2G_T 型でアクセス)］ */
#define RADIO_RXFREQ_I_2G_ADR           (0x64u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Iカウンタ)(@ref RADIO_RXFREQ_I_2G_T 型でアクセス)］ */
#define RADIO_RXFREQ_FH_2G_ADR          (0x65u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Fカウンタ上位4ビット)(@ref RADIO_RXFREQ_FH_2G_T 型でアクセス)］ */
#define RADIO_RXFREQ_FM_2G_ADR          (0x66u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Fカウンタ中位8ビット)(@ref RADIO_RXFREQ_FM_2G_T 型でアクセス)］ */
#define RADIO_RXFREQ_FL_2G_ADR          (0x67u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Fカウンタ下位8ビット)(@ref RADIO_RXFREQ_FL_2G_T 型でアクセス)］ */
#define RADIO_CH_SPACE_H_2G_ADR         (0x68u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用チャネル間隔設定(上位バイト)(@ref RADIO_CH_SPACE_H_2G_T 型でアクセス)］ */
#define RADIO_CH_SPACE_L_2G_ADR         (0x69u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用チャネル間隔設定(下位バイト)(@ref RADIO_CH_SPACE_L_2G_T 型でアクセス)］ */
#define RADIO_GFSK_DEV_H_2G_ADR         (0x6Au)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用GFSK時の周波数偏位設定(上位6ビット)(@ref RADIO_GFSK_DEV_H_2G_T 型でアクセス)］ */
#define RADIO_GFSK_DEV_L_2G_ADR         (0x6Bu)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用GFSK時の周波数偏位設定(下位バイト)(@ref RADIO_GFSK_DEV_L_2G_T 型でアクセス)］ */
#define RADIO_PA_REG_ADJ_2G_ADR         (0x6Cu)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用PAレギュレータ出力電圧調整(@ref RADIO_PA_REG_ADJ_2G_T 型でアクセス)］ */
#define RADIO_IQ_MAG_ADJ_H_2G_ADR       (0x6Du)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ振幅バランス調整(上位4ビット)(@ref RADIO_IQ_MAG_ADJ_H_2G_T 型でアクセス)］ */
#define RADIO_IQ_MAG_ADJ_L_2G_ADR       (0x6Eu)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ振幅バランス調整(下位バイト)(@ref RADIO_IQ_MAG_ADJ_L_2G_T 型でアクセス)］ */
#define RADIO_IQ_PHASE_ADJ_H_2G_ADR     (0x6Fu)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ位相バランス調整(上位4ビット)(@ref RADIO_IQ_PHASE_ADJ_H_2G_T 型でアクセス)］ */
#define RADIO_IQ_PHASE_ADJ_L_2G_ADR     (0x70u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ位相バランス調整(下位バイト)(@ref RADIO_IQ_PHASE_ADJ_L_2G_T 型でアクセス)］ */
#define RADIO_GC_CTRL_2G_ADR            (0x71u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用ゲイン制御設定(@ref RADIO_GC_CTRL_2G_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_I_2G_ADR      (0x72u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Iカウンタ)(@ref RADIO_VCO_CAL_MIN_I_2G_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_FH_2G_ADR     (0x73u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Fカウンタ上位4ビット)(@ref RADIO_VCO_CAL_MIN_FH_2G_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_FM_2G_ADR     (0x74u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Fカウンタ中位8ビット)(@ref RADIO_VCO_CAL_MIN_FM_2G_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_FL_2G_ADR     (0x75u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Fカウンタ下位8ビット)(@ref RADIO_VCO_CAL_MIN_FL_2G_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MAX_N_2G_ADR      (0x76u)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーションの周波数範囲設定(@ref RADIO_VCO_CAL_MAX_N_2G_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B4_ADR77        (0x77u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR78        (0x78u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR79        (0x79u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR7A        (0x7Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR7B        (0x7Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR7C        (0x7Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR7D        (0x7Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR7E        (0x7Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B4_ADR7F        (0x7Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */

#define BANK_C_CHECK_CTRL_B4_ADR       (4)     /*!< ［｜<in-house>*TODO*英訳｜C-fieldチェックイネーブル(@ref RADIO_C_CHECK_CTRL_B4_T 型でアクセス)］ */
#define BANK_M_CHECK_CTRL_B4_ADR       (4)     /*!< ［｜<in-house>*TODO*英訳｜M-fieldチェックイネーブル(@ref RADIO_M_CHECK_CTRL_B4_T 型でアクセス)］ */
#define BANK_A_CHECK_CTRL2_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜A-fieldチェックイネーブル2(@ref RADIO_A_CHECK_CTRL2_T 型でアクセス)］ */
#define BANK_A_CHECK_CTRL1_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜A-fieldチェックイネーブル1(@ref RADIO_A_CHECK_CTRL1_T 型でアクセス)］ */
#define BANK_C_FIELD_WORD1_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード1(@ref RADIO_C_FIELD_WORD1_B4_T 型でアクセス)］ */
#define BANK_C_FIELD_WORD2_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード2(@ref RADIO_C_FIELD_WORD2_B4_T 型でアクセス)］ */
#define BANK_C_FIELD_WORD3_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード3(@ref RADIO_C_FIELD_WORD3_B4_T 型でアクセス)］ */
#define BANK_C_FIELD_WORD4_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード4(@ref RADIO_C_FIELD_WORD4_B4_T 型でアクセス)］ */
#define BANK_C_FIELD_WORD5_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード5(@ref RADIO_C_FIELD_WORD5_B4_T 型でアクセス)］ */
#define BANK_M_FIELD_WORD1_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field 1stバイト設定コード1(@ref RADIO_M_FIELD_WORD1_B4_T 型でアクセス)］ */
#define BANK_M_FIELD_WORD2_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field 1stバイト設定コード2(@ref RADIO_M_FIELD_WORD2_B4_T 型でアクセス)］ */
#define BANK_M_FIELD_WORD3_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定コード1(@ref RADIO_M_FIELD_WORD3_B4_T 型でアクセス)］ */
#define BANK_M_FIELD_WORD4_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定コード2(@ref RADIO_M_FIELD_WORD4_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD1_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 1stバイト設定(@ref RADIO_A_FIELD_WORD1_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD2_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 2ndバイト設定(@ref RADIO_A_FIELD_WORD2_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD3_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 3rdバイト設定(@ref RADIO_A_FIELD_WORD3_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD4_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 4thバイト設定(@ref RADIO_A_FIELD_WORD4_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD5_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 5thバイト設定(@ref RADIO_A_FIELD_WORD5_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD6_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 6thバイト設定(@ref RADIO_A_FIELD_WORD6_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD7_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 7thバイト設定(@ref RADIO_A_FIELD_WORD7_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD8_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 8thバイト設定(@ref RADIO_A_FIELD_WORD8_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD9_B4_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 9thバイト設定(@ref RADIO_A_FIELD_WORD9_B4_T 型でアクセス)］ */
#define BANK_A_FIELD_WORD10_B4_ADR     (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field 10thバイト設定(@ref RADIO_A_FIELD_WORD10_B4_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B4_ADR18        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR19        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR1A        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR1B        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR1C        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR1D        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR1E        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR1F        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_CMA2_CHECK_CTRL1_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field2チェックイネーブル1(@ref RADIO_CMA2_CHECK_CTRL1_T 型でアクセス)］ */
#define BANK_CMA2_CHECK_CTRL2_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field2チェックイネーブル2(@ref RADIO_CMA2_CHECK_CTRL2_T 型でアクセス)］ */
#define BANK_C2_FIELD_WORD1_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field2設定(@ref RADIO_C2_FIELD_WORD1_T 型でアクセス)］ */
#define BANK_M2_FIELD_WORD1_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field2 1stバイト設定(@ref RADIO_M2_FIELD_WORD1_T 型でアクセス)］ */
#define BANK_M2_FIELD_WORD2_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field2 2ndバイト設定(@ref RADIO_M2_FIELD_WORD2_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD1_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 1stバイト設定(@ref RADIO_A2_FIELD_WORD1_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD2_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 2ndバイト設定(@ref RADIO_A2_FIELD_WORD2_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD3_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 3rdバイト設定(@ref RADIO_A2_FIELD_WORD3_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD4_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 4thバイト設定(@ref RADIO_A2_FIELD_WORD4_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD5_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 5thバイト設定(@ref RADIO_A2_FIELD_WORD5_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD6_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 6thバイト設定(@ref RADIO_A2_FIELD_WORD6_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD7_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 7thバイト設定(@ref RADIO_A2_FIELD_WORD7_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD8_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 8thバイト設定(@ref RADIO_A2_FIELD_WORD8_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD9_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 9thバイト設定(@ref RADIO_A2_FIELD_WORD9_T 型でアクセス)］ */
#define BANK_A2_FIELD_WORD10_ADR       (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field2 10thバイト設定(@ref RADIO_A2_FIELD_WORD10_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B4_ADR2F        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_CMA3_CHECK_CTRL1_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field3チェックイネーブル1(@ref RADIO_CMA3_CHECK_CTRL1_T 型でアクセス)］ */
#define BANK_CMA3_CHECK_CTRL2_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜CMA-field3チェックイネーブル2(@ref RADIO_CMA3_CHECK_CTRL2_T 型でアクセス)］ */
#define BANK_C3_FIELD_WORD1_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜C-field3設定(@ref RADIO_C3_FIELD_WORD1_T 型でアクセス)］ */
#define BANK_M3_FIELD_WORD1_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field3 1stバイト設定(@ref RADIO_M3_FIELD_WORD1_T 型でアクセス)］ */
#define BANK_M3_FIELD_WORD2_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜M-field3 2ndバイト設定(@ref RADIO_M3_FIELD_WORD2_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD1_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 1stバイト設定(@ref RADIO_A3_FIELD_WORD1_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD2_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 2ndバイト設定(@ref RADIO_A3_FIELD_WORD2_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD3_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 3rdバイト設定(@ref RADIO_A3_FIELD_WORD3_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD4_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 4thバイト設定(@ref RADIO_A3_FIELD_WORD4_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD5_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 5thバイト設定(@ref RADIO_A3_FIELD_WORD5_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD6_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 6thバイト設定(@ref RADIO_A3_FIELD_WORD6_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD7_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 7thバイト設定(@ref RADIO_A3_FIELD_WORD7_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD8_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 8thバイト設定(@ref RADIO_A3_FIELD_WORD8_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD9_ADR        (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 9thバイト設定(@ref RADIO_A3_FIELD_WORD9_T 型でアクセス)］ */
#define BANK_A3_FIELD_WORD10_ADR       (4)     /*!< ［｜<in-house>*TODO*英訳｜A-field3 10thバイト設定(@ref RADIO_A3_FIELD_WORD10_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B4_ADR3F        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR40        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR41        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR42        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR43        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR44        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR45        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR46        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR47        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR48        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR49        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR4A        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR4B        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR4C        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR4D        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR4E        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR4F        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR50        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR51        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR52        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR53        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR54        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR55        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR56        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR57        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR58        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR59        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR5A        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR5B        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR5C        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR5D        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR5E        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR5F        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_TXFREQ_I_2G_ADR           (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Iカウンタ)(@ref RADIO_TXFREQ_I_2G_T 型でアクセス)］ */
#define BANK_TXFREQ_FH_2G_ADR          (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Fカウンタ上位4ビット)(@ref RADIO_TXFREQ_FH_2G_T 型でアクセス)］ */
#define BANK_TXFREQ_FM_2G_ADR          (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Fカウンタ中位8ビット)(@ref RADIO_TXFREQ_FM_2G_T 型でアクセス)］ */
#define BANK_TXFREQ_FL_2G_ADR          (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用送信周波数設定(Fカウンタ下位8ビット)(@ref RADIO_TXFREQ_FL_2G_T 型でアクセス)］ */
#define BANK_RXFREQ_I_2G_ADR           (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Iカウンタ)(@ref RADIO_RXFREQ_I_2G_T 型でアクセス)］ */
#define BANK_RXFREQ_FH_2G_ADR          (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Fカウンタ上位4ビット)(@ref RADIO_RXFREQ_FH_2G_T 型でアクセス)］ */
#define BANK_RXFREQ_FM_2G_ADR          (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Fカウンタ中位8ビット)(@ref RADIO_RXFREQ_FM_2G_T 型でアクセス)］ */
#define BANK_RXFREQ_FL_2G_ADR          (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用受信周波数設定(Fカウンタ下位8ビット)(@ref RADIO_RXFREQ_FL_2G_T 型でアクセス)］ */
#define BANK_CH_SPACE_H_2G_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用チャネル間隔設定(上位バイト)(@ref RADIO_CH_SPACE_H_2G_T 型でアクセス)］ */
#define BANK_CH_SPACE_L_2G_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用チャネル間隔設定(下位バイト)(@ref RADIO_CH_SPACE_L_2G_T 型でアクセス)］ */
#define BANK_GFSK_DEV_H_2G_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用GFSK時の周波数偏位設定(上位6ビット)(@ref RADIO_GFSK_DEV_H_2G_T 型でアクセス)］ */
#define BANK_GFSK_DEV_L_2G_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用GFSK時の周波数偏位設定(下位バイト)(@ref RADIO_GFSK_DEV_L_2G_T 型でアクセス)］ */
#define BANK_PA_REG_ADJ_2G_ADR         (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用PAレギュレータ出力電圧調整(@ref RADIO_PA_REG_ADJ_2G_T 型でアクセス)］ */
#define BANK_IQ_MAG_ADJ_H_2G_ADR       (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ振幅バランス調整(上位4ビット)(@ref RADIO_IQ_MAG_ADJ_H_2G_T 型でアクセス)］ */
#define BANK_IQ_MAG_ADJ_L_2G_ADR       (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ振幅バランス調整(下位バイト)(@ref RADIO_IQ_MAG_ADJ_L_2G_T 型でアクセス)］ */
#define BANK_IQ_PHASE_ADJ_H_2G_ADR     (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ位相バランス調整(上位4ビット)(@ref RADIO_IQ_PHASE_ADJ_H_2G_T 型でアクセス)］ */
#define BANK_IQ_PHASE_ADJ_L_2G_ADR     (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用IFのIQ位相バランス調整(下位バイト)(@ref RADIO_IQ_PHASE_ADJ_L_2G_T 型でアクセス)］ */
#define BANK_GC_CTRL_2G_ADR            (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用ゲイン制御設定(@ref RADIO_GC_CTRL_2G_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_I_2G_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Iカウンタ)(@ref RADIO_VCO_CAL_MIN_I_2G_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_FH_2G_ADR     (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Fカウンタ上位4ビット)(@ref RADIO_VCO_CAL_MIN_FH_2G_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_FM_2G_ADR     (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Fカウンタ中位8ビット)(@ref RADIO_VCO_CAL_MIN_FM_2G_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_FL_2G_ADR     (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーション下限周波数設定(Fカウンタ下位8ビット)(@ref RADIO_VCO_CAL_MIN_FL_2G_T 型でアクセス)］ */
#define BANK_VCO_CAL_MAX_N_2G_ADR      (4)     /*!< ［｜<in-house>*TODO*英訳｜2.4GHz用VCOキャリブレーションの周波数範囲設定(@ref RADIO_VCO_CAL_MAX_N_2G_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B4_ADR77        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR78        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR79        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR7A        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR7B        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR7C        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR7D        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR7E        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B4_ADR7F        (4)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */


/* ［RF register structures｜RFレジスタ構造体］ */
/** @brief ［Type definition for @ref RADIO_C_CHECK_CTRL_B4_ADR access｜@ref RADIO_C_CHECK_CTRL_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_en:         5;      /*!<［｜<in-house>*TODO*英訳｜コントロールフィールドパターン1~5チェックイネーブル R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t ca_int_ctrl:        1;      /*!<［｜<in-house>*TODO*英訳｜Fieldチェック割込み設定 R/W］*/
        uint8_t ca_rxd_clr:         1;      /*!<［｜<in-house>*TODO*英訳｜Field不一致時の受信データ処理設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_CHECK_CTRL_B4_T;

/** @brief ［Type definition for @ref RADIO_M_CHECK_CTRL_B4_ADR access｜@ref RADIO_M_CHECK_CTRL_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_word1_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン1チェックイネーブル R/W］*/
        uint8_t m_field_word2_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン2チェックイネーブル R/W］*/
        uint8_t m_field_word3_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン3チェックイネーブル R/W］*/
        uint8_t m_field_word4_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン4チェックイネーブル R/W］*/
        uint8_t rcv_cont_sel:       2;      /*!<［｜<in-house>*TODO*英訳｜動作継続タイマ満了時の受信継続条件設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_M_CHECK_CTRL_B4_T;
/** @brief ［Type definition for @ref RADIO_A_CHECK_CTRL1_ADR access｜@ref RADIO_A_CHECK_CTRL1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word9_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン9チェックイネーブル R/W］*/
        uint8_t a_field_word10_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン10チェックイネーブル R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_A_CHECK_CTRL1_T;

/** @brief ［Type definition for @ref RADIO_A_CHECK_CTRL2_ADR access｜@ref RADIO_A_CHECK_CTRL2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word1_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン1チェックイネーブル R/W］*/
        uint8_t a_field_word2_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン2チェックイネーブル R/W］*/
        uint8_t a_field_word3_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン3チェックイネーブル R/W］*/
        uint8_t a_field_word4_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン4チェックイネーブル R/W］*/
        uint8_t a_field_word5_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン5チェックイネーブル R/W］*/
        uint8_t a_field_word6_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン6チェックイネーブル R/W］*/
        uint8_t a_field_word7_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン7チェックイネーブル R/W］*/
        uint8_t a_field_word8_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン8チェックイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_CHECK_CTRL2_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_WORD1_B4_ADR access｜@ref RADIO_C_FIELD_WORD1_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_word1:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_WORD1_B4_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_WORD2_B4_ADR access｜@ref RADIO_C_FIELD_WORD2_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_word2:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field設定 コード#2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_WORD2_B4_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_WORD3_B4_ADR access｜@ref RADIO_C_FIELD_WORD3_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_word3:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#3 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_WORD3_B4_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_WORD4_B4_ADR access｜@ref RADIO_C_FIELD_WORD4_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_word4:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#4 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_WORD4_B4_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_WORD5_B4_ADR access｜@ref RADIO_C_FIELD_WORD5_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_word5:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#5 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_WORD5_B4_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_WORD1_B4_ADR access｜@ref RADIO_M_FIELD_WORD1_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_word1:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 1stバイト設定 コード#1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_WORD1_B4_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_WORD2_B4_ADR access｜@ref RADIO_M_FIELD_WORD2_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_word2:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 1stバイト設定 コード#2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_WORD2_B4_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_WORD3_B4_ADR access｜@ref RADIO_M_FIELD_WORD3_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_word3:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定 コード#1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_WORD3_B4_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_WORD4_B4_ADR access｜@ref RADIO_M_FIELD_WORD4_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_word4:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定 コード#2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_WORD4_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD1_B4_ADR access｜@ref RADIO_A_FIELD_WORD1_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word1:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(1バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD1_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD2_B4_ADR access｜@ref RADIO_A_FIELD_WORD2_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word2:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(2バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD2_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD3_B4_ADR access｜@ref RADIO_A_FIELD_WORD3_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word3:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(3バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD3_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD4_B4_ADR access｜@ref RADIO_A_FIELD_WORD4_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word4:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(4バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD4_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD5_B4_ADR access｜@ref RADIO_A_FIELD_WORD5_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word5:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(5バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD5_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD6_B4_ADR access｜@ref RADIO_A_FIELD_WORD6_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word6:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(6バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD6_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD7_B4_ADR access｜@ref RADIO_A_FIELD_WORD7_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word7:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(7バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD7_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD8_B4_ADR access｜@ref RADIO_A_FIELD_WORD8_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word8:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(8バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD8_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD9_B4_ADR access｜@ref RADIO_A_FIELD_WORD9_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word9:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(9バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD9_B4_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_WORD10_B4_ADR access｜@ref RADIO_A_FIELD_WORD10_B4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_word10:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(10バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_WORD10_B4_T;

/** @brief ［Type definition for @ref RADIO_CMA2_CHECK_CTRL1_ADR access｜@ref RADIO_CMA2_CHECK_CTRL1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word9_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン9チェックイネーブル R/W］*/
        uint8_t a2_field_word10_en: 1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン10チェックイネーブル R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t c2_field_word_en:   1;      /*!<［｜<in-house>*TODO*英訳｜コントロールフィールドパターン1チェックイネーブル R/W］*/
        uint8_t m2_field_word1_en:  1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン1チェックイネーブル R/W］*/
        uint8_t m2_field_word2_en:  1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン2チェックイネーブル R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_CMA2_CHECK_CTRL1_T;

/** @brief ［Type definition for @ref RADIO_CMA2_CHECK_CTRL2_ADR access｜@ref RADIO_CMA2_CHECK_CTRL2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word1_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン1チェックイネーブル R/W］*/
        uint8_t a2_field_word2_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン2チェックイネーブル R/W］*/
        uint8_t a2_field_word3_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン3チェックイネーブル R/W］*/
        uint8_t a2_field_word4_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン4チェックイネーブル R/W］*/
        uint8_t a2_field_word5_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン5チェックイネーブル R/W］*/
        uint8_t a2_field_word6_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン6チェックイネーブル R/W］*/
        uint8_t a2_field_word7_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン7チェックイネーブル R/W］*/
        uint8_t a2_field_word8_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン8チェックイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CMA2_CHECK_CTRL2_T;

/** @brief ［Type definition for @ref RADIO_C2_FIELD_WORD1_ADR access｜@ref RADIO_C2_FIELD_WORD1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c2_field_word1:     8;      /*!<［｜<in-house>*TODO*英訳｜C-field2 設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C2_FIELD_WORD1_T;

/** @brief ［Type definition for @ref RADIO_M2_FIELD_WORD1_ADR access｜@ref RADIO_M2_FIELD_WORD1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m2_field_word1:     8;      /*!<［｜<in-house>*TODO*英訳｜M-field2 1stバイト設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M2_FIELD_WORD1_T;

/** @brief ［Type definition for @ref RADIO_M2_FIELD_WORD2_ADR access｜@ref RADIO_M2_FIELD_WORD2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m2_field_word2:     8;      /*!<［｜<in-house>*TODO*英訳｜M-field2 2ndバイト設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M2_FIELD_WORD2_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD1_ADR access｜@ref RADIO_A2_FIELD_WORD1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word1:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(1バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD1_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD2_ADR access｜@ref RADIO_A2_FIELD_WORD2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word2:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(2バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD2_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD3_ADR access｜@ref RADIO_A2_FIELD_WORD3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word3:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(3バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD3_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD4_ADR access｜@ref RADIO_A2_FIELD_WORD4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word4:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(4バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD4_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD5_ADR access｜@ref RADIO_A2_FIELD_WORD5_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word5:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(5バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD5_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD6_ADR access｜@ref RADIO_A2_FIELD_WORD6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word6:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(6バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD6_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD7_ADR access｜@ref RADIO_A2_FIELD_WORD7_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word7:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(7バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD7_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD8_ADR access｜@ref RADIO_A2_FIELD_WORD8_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word8:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(8バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD8_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD9_ADR access｜@ref RADIO_A2_FIELD_WORD9_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word9:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(9バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD9_T;

/** @brief ［Type definition for @ref RADIO_A2_FIELD_WORD10_ADR access｜@ref RADIO_A2_FIELD_WORD10_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a2_field_word10:    8;      /*!<［｜<in-house>*TODO*英訳｜A-field2設定(10バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A2_FIELD_WORD10_T;

/** @brief ［Type definition for @ref RADIO_CMA3_CHECK_CTRL1_ADR access｜@ref RADIO_CMA3_CHECK_CTRL1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word9_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン9チェックイネーブル R/W］*/
        uint8_t a3_field_word10_en: 1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン10チェックイネーブル R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t c3_field_word_en:   1;      /*!<［｜<in-house>*TODO*英訳｜コントロールフィールド3パターンチェックイネーブル R/W］*/
        uint8_t m3_field_word1_en:  1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールド3パターン1チェックイネーブル R/W］*/
        uint8_t m3_field_word2_en:  1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールド3パターン2チェックイネーブル R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_CMA3_CHECK_CTRL1_T;

/** @brief ［Type definition for @ref RADIO_CMA3_CHECK_CTRL2_ADR access｜@ref RADIO_CMA3_CHECK_CTRL2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word1_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン1チェックイネーブル R/W］*/
        uint8_t a3_field_word2_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン2チェックイネーブル R/W］*/
        uint8_t a3_field_word3_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン3チェックイネーブル R/W］*/
        uint8_t a3_field_word4_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン4チェックイネーブル R/W］*/
        uint8_t a3_field_word5_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン5チェックイネーブル R/W］*/
        uint8_t a3_field_word6_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン6チェックイネーブル R/W］*/
        uint8_t a3_field_word7_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン7チェックイネーブル R/W］*/
        uint8_t a3_field_word8_en:  1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールド3パターン8チェックイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CMA3_CHECK_CTRL2_T;

/** @brief ［Type definition for @ref RADIO_C3_FIELD_WORD1_ADR access｜@ref RADIO_C3_FIELD_WORD1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c3_field_word1:     8;      /*!<［｜<in-house>*TODO*英訳｜C-field3 設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C3_FIELD_WORD1_T;

/** @brief ［Type definition for @ref RADIO_M3_FIELD_WORD1_ADR access｜@ref RADIO_M3_FIELD_WORD1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m3_field_word1:     8;      /*!<［｜<in-house>*TODO*英訳｜M-field3 1stバイト設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M3_FIELD_WORD1_T;

/** @brief ［Type definition for @ref RADIO_M3_FIELD_WORD2_ADR access｜@ref RADIO_M3_FIELD_WORD2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m3_field_word2:     8;      /*!<［｜<in-house>*TODO*英訳｜M-field3 2ndバイト設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M3_FIELD_WORD2_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD1_ADR access｜@ref RADIO_A3_FIELD_WORD1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word1:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field3設定(1バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD1_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD2_ADR access｜@ref RADIO_A3_FIELD_WORD2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word2:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field3設定(2バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD2_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD3_ADR access｜@ref RADIO_A3_FIELD_WORD3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word3:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field3設定(3バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD3_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD4_ADR access｜@ref RADIO_A3_FIELD_WORD4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word4:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field3設定(4バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD4_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD5_ADR access｜@ref RADIO_A3_FIELD_WORD5_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word5:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field3設定(5バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD5_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD6_ADR access｜@ref RADIO_A3_FIELD_WORD6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word6:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(6バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD6_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD7_ADR access｜@ref RADIO_A3_FIELD_WORD7_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word7:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(7バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD7_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD8_ADR access｜@ref RADIO_A3_FIELD_WORD8_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word8:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(8バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD8_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD9_ADR access｜@ref RADIO_A3_FIELD_WORD9_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word9:     8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(9バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD9_T;

/** @brief ［Type definition for @ref RADIO_A3_FIELD_WORD10_ADR access｜@ref RADIO_A3_FIELD_WORD10_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a3_field_word10:    8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(10バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A3_FIELD_WORD10_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_I_2G_ADR access｜@ref RADIO_TXFREQ_I_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_i_2g:        6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_I_2G_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_FH_2G_ADR access｜@ref RADIO_TXFREQ_FH_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_f_2g:        6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_FH_2G_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_FM_2G_ADR access｜@ref RADIO_TXFREQ_FM_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_f_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_FM_2G_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_FL_2G_ADR access｜@ref RADIO_TXFREQ_FL_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_f_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_FL_2G_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_I_2G_ADR access｜@ref RADIO_RXFREQ_I_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_i_2g:        6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_I_2G_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_FH_2G_ADR access｜@ref RADIO_RXFREQ_FH_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_f_2g:        6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_FH_2G_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_FM_2G_ADR access｜@ref RADIO_RXFREQ_FM_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_f_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_FM_2G_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_FL_2G_ADR access｜@ref RADIO_RXFREQ_FL_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_f_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_FL_2G_T;

/** @brief ［Type definition for @ref RADIO_CH_SPACE_H_2G_ADR access｜@ref RADIO_CH_SPACE_H_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ch_space_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CH_SPACE_H_2G_T;

/** @brief ［Type definition for @ref RADIO_CH_SPACE_L_2G_ADR access｜@ref RADIO_CH_SPACE_L_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ch_space_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CH_SPACE_L_2G_T;

/** @brief ［Type definition for @ref RADIO_GFSK_DEV_H_2G_ADR access｜@ref RADIO_GFSK_DEV_H_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gfsk_dev_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GFSK_DEV_H_2G_T;

/** @brief ［Type definition for @ref RADIO_GFSK_DEV_L_2G_ADR access｜@ref RADIO_GFSK_DEV_L_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gfsk_dev_2g:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GFSK_DEV_L_2G_T;

/** @brief ［Type definition for @ref RADIO_IQ_MAG_ADJ_H_2G_ADR access｜@ref RADIO_IQ_MAG_ADJ_H_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_mag_adj_h_2g:    4;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の振幅調整設定(上位4ビット) R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_MAG_ADJ_H_2G_T;

/** @brief ［Type definition for @ref RADIO_IQ_MAG_ADJ_L_2G_ADR access｜@ref RADIO_IQ_MAG_ADJ_L_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_mag_adj_l_2g:    8;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の振幅調整設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_MAG_ADJ_L_2G_T;

/** @brief ［Type definition for @ref RADIO_IQ_PHASE_ADJ_H_2G_ADR access｜@ref RADIO_IQ_PHASE_ADJ_H_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_phase_adj_h_2g:  3;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の位相調整設定(上位3ビット) R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t iq_phase_sign_2g:   1;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の位相調整符号ビット R/W］*/
        uint8_t reserved1:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_PHASE_ADJ_H_2G_T;

/** @brief ［Type definition for @ref RADIO_IQ_PHASE_ADJ_L_2G_ADR access｜@ref RADIO_IQ_PHASE_ADJ_L_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_phase_adj_l_2g:  8;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の位相調整設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_PHASE_ADJ_L_2G_T;

/** @brief ［Type definition for @ref RADIO_GC_CTRL_2G_ADR access｜@ref RADIO_GC_CTRL_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gc_mode_2g:         4;      /*!<［｜<in-house>*TODO*英訳｜2.4GHz用ゲイン制御モード設定 R/W］*/
        uint8_t gc_mode_cca_2g:     4;      /*!<［｜<in-house>*TODO*英訳｜2.4GHz用CCA時ゲイン制御モード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GC_CTRL_2G_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_I_2G_ADR access｜@ref RADIO_VCO_CAL_MIN_I_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_i_2g:   6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_I_2G_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_FH_2G_ADR access｜@ref RADIO_VCO_CAL_MIN_FH_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_f_2g:   6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_FH_2G_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_FM_2G_ADR access｜@ref RADIO_VCO_CAL_MIN_FM_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_f_2g:   8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_FM_2G_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_FL_2G_ADR access｜@ref RADIO_VCO_CAL_MIN_FL_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_f_2g:   8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_FL_2G_T;

/** @brief ［Type definition for @ref RADIO_VCAL_MAX_N_2G_ADR access｜@ref RADIO_VCAL_MAX_N_2G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_max_n_2g:   4;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MAX_N_2G_T;

/** \} */ /* End of group RF_REGISTER_BANK4 */
#endif
