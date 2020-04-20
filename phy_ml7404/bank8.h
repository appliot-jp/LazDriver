/****************************************************************************************/
/**
   @file     bank8.h

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
#ifndef _bank8_H
#define _bank8_H

/**
    \addtogroup RF_REGISTER_BANK8
    \{
 */
 
/*［BANK8 Register Address Definitions｜BANK8レジスタアドレス定義］*/
#define RADIO_SEARCH_CH_SET_ADR         (0x01u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH_SET_T 型でアクセス)］ */
#define RADIO_SEARCH_CH_EN_ADR          (0x02u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH_EN_T 型でアクセス)］ */
#define RADIO_SEARCH_CH0_ADR            (0x03u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH0_T 型でアクセス)］ */
#define RADIO_SEARCH_CH1_ADR            (0x04u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH1_T 型でアクセス)］ */
#define RADIO_SEARCH_CH2_ADR            (0x05u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH2_T 型でアクセス)］ */
#define RADIO_SEARCH_CH3_ADR            (0x06u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH3_T 型でアクセス)］ */
#define RADIO_SEARCH_CH4_ADR            (0x07u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH4_T 型でアクセス)］ */
#define RADIO_SEARCH_CH5_ADR            (0x08u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH5_T 型でアクセス)］ */
#define RADIO_SEARCH_CH6_ADR            (0x09u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH6_T 型でアクセス)］ */
#define RADIO_SEARCH_CH7_ADR            (0x0Au)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH7_T 型でアクセス)］ */
#define RADIO_SRCH_ED_TH_ADR            (0x0Bu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_ED_TH_T 型でアクセス)］ */
#define RADIO_PLL_WAIT_TIMER_ADR        (0x0Cu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_PLL_WAIT_TIMER_T 型でアクセス)］ */
#define RADIO_ED_WAIT_TIMER_ADR         (0x0Du)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_ED_WAIT_TIMER_T 型でアクセス)］ */
#define RADIO_SYNC_WAIT_TIMER_ADR       (0x0Eu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SYNC_WAIT_TIMER_T 型でアクセス)］ */
#define RADIO_SYNC_WAIT_TIMER2_ADR      (0x0Fu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SYNC_WAIT_TIMER2_T 型でアクセス)］ */
#define RADIO_SRCH_ED_ANT1_ADR          (0x10u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_ED_ANT1_T 型でアクセス)］ */
#define RADIO_SRCH_ED_ANT2_ADR          (0x11u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_ED_ANT2_T 型でアクセス)］ */
#define RADIO_SRCH_CH_ADR               (0x12u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_CH_T 型でアクセス)］ */
#define RADIO_SRCH_STATE_ADR            (0x13u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_STATE_T 型でアクセス)］ */
#define RADIO_FH_SET_ADR                (0x14u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_FH_SET_T 型でアクセス)］ */
#define RADIO_FH_MAX_CH_ADR             (0x15u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_FH_MAX_CH_T 型でアクセス)］ */
#define RADIO_RANDOM_CH_DISP_ADR        (0x16u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_RANDOM_CH_DISP_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B8_ADR17        (0x17u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR18        (0x18u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR19        (0x19u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR1A        (0x1Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR1B        (0x1Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR1C        (0x1Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR1D        (0x1Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR1E        (0x1Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR1F        (0x1Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR20        (0x20u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR21        (0x21u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR22        (0x22u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR23        (0x23u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR24        (0x24u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR25        (0x25u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR26        (0x26u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR27        (0x27u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR28        (0x28u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR29        (0x29u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR2A        (0x2Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR2B        (0x2Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR2C        (0x2Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR2D        (0x2Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR2E        (0x2Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR2F        (0x2Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR30        (0x30u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR31        (0x31u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR32        (0x32u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR33        (0x33u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR34        (0x34u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR35        (0x35u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR36        (0x36u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR37        (0x37u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR38        (0x38u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR39        (0x39u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR3A        (0x3Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR3B        (0x3Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR3C        (0x3Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR3D        (0x3Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR3E        (0x3Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR3F        (0x3Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR40        (0x40u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR41        (0x41u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR42        (0x42u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR43        (0x43u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR44        (0x44u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR45        (0x45u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR46        (0x46u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR47        (0x47u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR48        (0x48u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR49        (0x49u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR4A        (0x4Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR4B        (0x4Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR4C        (0x4Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR4D        (0x4Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR4E        (0x4Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR4F        (0x4Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR50        (0x50u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR51        (0x51u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR52        (0x52u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR53        (0x53u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR54        (0x54u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR55        (0x55u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR56        (0x56u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR57        (0x57u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR58        (0x58u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR59        (0x59u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR5A        (0x5Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR5B        (0x5Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR5C        (0x5Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR5D        (0x5Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR5E        (0x5Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR5F        (0x5Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR60        (0x60u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR61        (0x61u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR62        (0x62u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR63        (0x63u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR64        (0x64u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR65        (0x65u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR66        (0x66u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR67        (0x67u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR68        (0x68u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR69        (0x69u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR6A        (0x6Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR6B        (0x6Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR6C        (0x6Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR6D        (0x6Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR6E        (0x6Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR6F        (0x6Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR70        (0x70u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR71        (0x71u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR72        (0x72u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR73        (0x73u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR74        (0x74u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR75        (0x75u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR76        (0x76u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR77        (0x77u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR78        (0x78u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR79        (0x79u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR7A        (0x7Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR7B        (0x7Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR7C        (0x7Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR7D        (0x7Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR7E        (0x7Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B8_ADR7F        (0x7Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */

#define BANK_SEARCH_CH_SET_ADR         (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH_SET_T 型でアクセス)］ */
#define BANK_SEARCH_CH_EN_ADR          (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH_EN_T 型でアクセス)］ */
#define BANK_SEARCH_CH0_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH0_T 型でアクセス)］ */
#define BANK_SEARCH_CH1_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH1_T 型でアクセス)］ */
#define BANK_SEARCH_CH2_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH2_T 型でアクセス)］ */
#define BANK_SEARCH_CH3_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH3_T 型でアクセス)］ */
#define BANK_SEARCH_CH4_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH4_T 型でアクセス)］ */
#define BANK_SEARCH_CH5_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH5_T 型でアクセス)］ */
#define BANK_SEARCH_CH6_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH6_T 型でアクセス)］ */
#define BANK_SEARCH_CH7_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SEARCH_CH7_T 型でアクセス)］ */
#define BANK_SRCH_ED_TH_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_ED_TH_T 型でアクセス)］ */
#define BANK_PLL_WAIT_TIMER_ADR        (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_PLL_WAIT_TIMER_T 型でアクセス)］ */
#define BANK_ED_WAIT_TIMER_ADR         (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_ED_WAIT_TIMER_T 型でアクセス)］ */
#define BANK_SYNC_WAIT_TIMER_ADR       (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SYNC_WAIT_TIMER_T 型でアクセス)］ */
#define BANK_SYNC_WAIT_TIMER2_ADR      (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SYNC_WAIT_TIMER2_T 型でアクセス)］ */
#define BANK_SRCH_ED_ANT1_ADR          (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_ED_ANT1_T 型でアクセス)］ */
#define BANK_SRCH_ED_ANT2_ADR          (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_ED_ANT2_T 型でアクセス)］ */
#define BANK_SRCH_CH_ADR               (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_CH_T 型でアクセス)］ */
#define BANK_SRCH_STATE_ADR            (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SRCH_STATE_T 型でアクセス)］ */
#define BANK_FH_SET_ADR                (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_FH_SET_T 型でアクセス)］ */
#define BANK_FH_MAX_CH_ADR             (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_FH_MAX_CH_T 型でアクセス)］ */
#define BANK_RANDOM_CH_DISP_ADR        (8)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_RANDOM_CH_DISP_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B8_ADR17        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR18        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR19        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR1A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR1B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR1C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR1D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR1E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR1F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR20        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR21        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR22        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR23        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR24        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR25        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR26        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR27        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR28        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR29        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR2A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR2B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR2C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR2D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR2E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR2F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR30        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR31        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR32        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR33        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR34        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR35        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR36        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR37        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR38        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR39        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR3A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR3B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR3C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR3D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR3E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR3F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR40        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR41        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR42        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR43        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR44        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR45        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR46        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR47        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR48        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR49        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR4A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR4B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR4C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR4D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR4E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR4F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR50        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR51        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR52        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR53        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR54        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR55        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR56        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR57        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR58        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR59        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR5A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR5B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR5C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR5D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR5E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR5F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR60        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR61        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR62        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR63        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR64        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR65        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR66        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR67        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR68        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR69        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR6A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR6B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR6C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR6D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR6E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR6F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR70        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR71        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR72        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR73        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR74        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR75        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR76        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR77        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR78        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR79        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR7A        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR7B        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR7C        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR7D        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR7E        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B8_ADR7F        (8)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */


/* ［RF register structures｜RFレジスタ構造体］ */

/** @brief ［Type definition for @ref RADIO_SEARCH_CH_SET_ADR access｜@ref RADIO_SEARCH_CH_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ch_srch_en:         1;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチイネーブル設定 R/W］*/
        uint8_t ch_srch_mode:       2;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチモード R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t srch_ed_avg:        3;      /*!<［｜<in-house>*TODO*英訳｜ED値算出時の平均回数設定 R/W］*/
        uint8_t srch_time_res:      1;      /*!<［｜<in-house>*TODO*英訳｜同期検出待ち時間分解能設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH_SET_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH_EN_ADR access｜@ref RADIO_SEARCH_CH_EN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch0_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#0イネーブル R/W］*/
        uint8_t srch_ch1_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#1イネーブル R/W］*/
        uint8_t srch_ch2_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#2イネーブル R/W］*/
        uint8_t srch_ch3_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#3イネーブル R/W］*/
        uint8_t srch_ch4_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#4イネーブル R/W］*/
        uint8_t srch_ch5_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#5イネーブル R/W］*/
        uint8_t srch_ch6_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#6イネーブル R/W］*/
        uint8_t srch_ch7_en:        1;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#7イネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH_EN_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH0_ADR access｜@ref RADIO_SEARCH_CH0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch0:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#0のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH0_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH1_ADR access｜@ref RADIO_SEARCH_CH1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch1:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#1のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH1_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH2_ADR access｜@ref RADIO_SEARCH_CH2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch2:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#2のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH2_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH3_ADR access｜@ref RADIO_SEARCH_CH3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch3:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#3のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH3_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH4_ADR access｜@ref RADIO_SEARCH_CH4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch4:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#4のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH4_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH5_ADR access｜@ref RADIO_SEARCH_CH5_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch5:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#5のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH5_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH6_ADR access｜@ref RADIO_SEARCH_CH6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch6:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#6のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH6_T;

/** @brief ［Type definition for @ref RADIO_SEARCH_CH7_ADR access｜@ref RADIO_SEARCH_CH7_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch7:           8;      /*!<［｜<in-house>*TODO*英訳｜サーチチャネル#7のチャネル番号 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SEARCH_CH7_T;

/** @brief ［Type definition for @ref RADIO_SRCH_ED_TH_ADR access｜@ref RADIO_SRCH_ED_TH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ed_th:         8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時のED値閾値設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SRCH_ED_TH_T;

/** @brief ［Type definition for @ref RADIO_PLL_WAIT_TIMER_ADR access｜@ref RADIO_PLL_WAIT_TIMER_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pll_wait_timer:     8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時のPLL収束待ち時間設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PLL_WAIT_TIMER_T;

/** @brief ［Type definition for @ref RADIO_ED_WAIT_TIMER_ADR access｜@ref RADIO_ED_WAIT_TIMER_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ed_wait_timer:      8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時のED値収束待ち時間設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_ED_WAIT_TIMER_T;

/** @brief ［Type definition for @ref RADIO_SYNC_WAIT_TIMER_ADR access｜@ref RADIO_SYNC_WAIT_TIMER_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_wait_timer:    8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時の同期検出待ち時間設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_WAIT_TIMER_T;

/** @brief ［Type definition for @ref RADIO_SYNC_WAIT_TIMER2_ADR access｜@ref RADIO_SYNC_WAIT_TIMER2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_wait_timer2:   8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時の同期検出待ち時間設定2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_WAIT_TIMER2_T;

/** @brief ［Type definition for @ref RADIO_SRCH_ED_ANT1_ADR access｜@ref RADIO_SRCH_ED_ANT1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ed_ant1:       8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時ED値取得値表示(ANT1) R］*/
    }bits;
    uint8_t byte;
}RADIO_SRCH_ED_ANT1_T;

/** @brief ［Type definition for @ref RADIO_SRCH_ED_ANT2_ADR access｜@ref RADIO_SRCH_ED_ANT2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ed_ant2:       8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ時ED値取得値表示(ANT2) R］*/
    }bits;
    uint8_t byte;
}RADIO_SRCH_ED_ANT2_T;

/** @brief ［Type definition for @ref RADIO_SRCH_CH_ADR access｜@ref RADIO_SRCH_CH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_ch:            8;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチ完了後のチャネル番号表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_SRCH_CH_T;

/** @brief ［Type definition for @ref RADIO_SRCH_STATE_ADR access｜@ref RADIO_SRCH_STATE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t srch_state:         3;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチステート表示 R］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SRCH_STATE_T;

/** @brief ［Type definition for @ref RADIO_FH_SET_ADR access｜@ref RADIO_FH_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fh_ch_srch_en:      1;      /*!<［｜<in-house>*TODO*英訳｜周波数ホッピングチャネルサーチ設定 R/W］*/
        uint8_t random_ch_en:       1;      /*!<［｜<in-house>*TODO*英訳｜ランダムチャネル番号生成設定 R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FH_SET_T;

/** @brief ［Type definition for @ref RADIO_FH_MAX_CH_ADR access｜@ref RADIO_FH_MAX_CH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fh_max_ch:          8;      /*!<［｜<in-house>*TODO*英訳｜周波数ホッピング最大チャネル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FH_MAX_CH_T;

/** @brief ［Type definition for @ref RADIO_RANDOM_CH_DISP_ADR access｜@ref RADIO_RANDOM_CH_DISP_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t random_ch_disp:     8;      /*!<［｜<in-house>*TODO*英訳｜ランダムチャネル番号表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_RANDOM_CH_DISP_T;

/** \} */ /* End of group RF_REGISTER_BANK8 */
#endif
