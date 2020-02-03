/****************************************************************************************/
/**
   @file     bank10.h

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
#ifndef _bank10_H
#define _bank10_H

/**
    \addtogroup RF_REGISTER_BANK10
    \{
*/
 
/*［BANK10 Register Address Definitions｜BANK10レジスタアドレス定義］*/
#define RADIO_BPSK_STEP_CTRL_ADR        (0x01u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定(@ref RADIO_BPSK_STEP_CTRL_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_CLK_SET_ADR     (0x02u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御クロック設定(@ref RADIO_BPSK_STEP_CLK_SET_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B10_ADR03       (0x03u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_BPSK_STEP_SET0_ADR        (0x04u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定0(@ref RADIO_BPSK_STEP_SET0_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET1_ADR        (0x05u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定1(@ref RADIO_BPSK_STEP_SET1_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET2_ADR        (0x06u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定2(@ref RADIO_BPSK_STEP_SET2_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET3_ADR        (0x07u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定3(@ref RADIO_BPSK_STEP_SET3_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET4_ADR        (0x08u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定4(@ref RADIO_BPSK_STEP_SET4_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET5_ADR        (0x09u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定5(@ref RADIO_BPSK_STEP_SET5_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET6_ADR        (0x0Au)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定6(@ref RADIO_BPSK_STEP_SET6_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET7_ADR        (0x0Bu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定7(@ref RADIO_BPSK_STEP_SET7_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET8_ADR        (0x0Cu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定8(@ref RADIO_BPSK_STEP_SET8_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET9_ADR        (0x0Du)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定9(@ref RADIO_BPSK_STEP_SET9_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET10_ADR       (0x0Eu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定10(@ref RADIO_BPSK_STEP_SET10_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET11_ADR       (0x0Fu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定11(@ref RADIO_BPSK_STEP_SET11_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET12_ADR       (0x10u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定12(@ref RADIO_BPSK_STEP_SET12_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET13_ADR       (0x11u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定13(@ref RADIO_BPSK_STEP_SET13_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET14_ADR       (0x12u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定14(@ref RADIO_BPSK_STEP_SET14_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET15_ADR       (0x13u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定15(@ref RADIO_BPSK_STEP_SET15_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET16_ADR       (0x14u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定16(@ref RADIO_BPSK_STEP_SET16_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET17_ADR       (0x15u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定17(@ref RADIO_BPSK_STEP_SET17_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET18_ADR       (0x16u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定18(@ref RADIO_BPSK_STEP_SET18_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET19_ADR       (0x17u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定19(@ref RADIO_BPSK_STEP_SET19_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET20_ADR       (0x18u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定20(@ref RADIO_BPSK_STEP_SET20_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET21_ADR       (0x19u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定21(@ref RADIO_BPSK_STEP_SET21_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET22_ADR       (0x1Au)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定22(@ref RADIO_BPSK_STEP_SET22_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET23_ADR       (0x1Bu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定23(@ref RADIO_BPSK_STEP_SET23_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET24_ADR       (0x1Cu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定24(@ref RADIO_BPSK_STEP_SET24_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET25_ADR       (0x1Du)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定25(@ref RADIO_BPSK_STEP_SET25_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET26_ADR       (0x1Eu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定26(@ref RADIO_BPSK_STEP_SET26_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET27_ADR       (0x1Fu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定27(@ref RADIO_BPSK_STEP_SET27_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET28_ADR       (0x20u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定28(@ref RADIO_BPSK_STEP_SET28_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET29_ADR       (0x21u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定29(@ref RADIO_BPSK_STEP_SET29_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET30_ADR       (0x22u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定30(@ref RADIO_BPSK_STEP_SET30_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET31_ADR       (0x23u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定31(@ref RADIO_BPSK_STEP_SET31_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET32_ADR       (0x24u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定32(@ref RADIO_BPSK_STEP_SET32_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET33_ADR       (0x25u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定33(@ref RADIO_BPSK_STEP_SET33_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET34_ADR       (0x26u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定34(@ref RADIO_BPSK_STEP_SET34_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET35_ADR       (0x27u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定35(@ref RADIO_BPSK_STEP_SET35_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET36_ADR       (0x28u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定36(@ref RADIO_BPSK_STEP_SET36_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET37_ADR       (0x29u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定37(@ref RADIO_BPSK_STEP_SET37_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET38_ADR       (0x2Au)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定38(@ref RADIO_BPSK_STEP_SET38_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET39_ADR       (0x2Bu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定39(@ref RADIO_BPSK_STEP_SET39_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET40_ADR       (0x2Cu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定40(@ref RADIO_BPSK_STEP_SET40_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET41_ADR       (0x2Du)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定41(@ref RADIO_BPSK_STEP_SET41_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET42_ADR       (0x2Eu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定42(@ref RADIO_BPSK_STEP_SET42_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET43_ADR       (0x2Fu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定43(@ref RADIO_BPSK_STEP_SET43_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET44_ADR       (0x30u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定44(@ref RADIO_BPSK_STEP_SET44_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET45_ADR       (0x31u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定45(@ref RADIO_BPSK_STEP_SET45_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET46_ADR       (0x32u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定46(@ref RADIO_BPSK_STEP_SET46_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET47_ADR       (0x33u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定47(@ref RADIO_BPSK_STEP_SET47_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET48_ADR       (0x34u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定48(@ref RADIO_BPSK_STEP_SET48_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET49_ADR       (0x35u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定49(@ref RADIO_BPSK_STEP_SET49_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET50_ADR       (0x36u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定50(@ref RADIO_BPSK_STEP_SET50_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET51_ADR       (0x37u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定51(@ref RADIO_BPSK_STEP_SET51_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET52_ADR       (0x38u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定52(@ref RADIO_BPSK_STEP_SET52_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET53_ADR       (0x39u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定53(@ref RADIO_BPSK_STEP_SET53_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET54_ADR       (0x3Au)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定54(@ref RADIO_BPSK_STEP_SET54_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET55_ADR       (0x3Bu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定55(@ref RADIO_BPSK_STEP_SET55_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET56_ADR       (0x3Cu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定56(@ref RADIO_BPSK_STEP_SET56_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET57_ADR       (0x3Du)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定57(@ref RADIO_BPSK_STEP_SET57_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET58_ADR       (0x3Eu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定58(@ref RADIO_BPSK_STEP_SET58_T 型でアクセス)］ */
#define RADIO_BPSK_STEP_SET59_ADR       (0x3Fu)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定59(@ref RADIO_BPSK_STEP_SET59_T 型でアクセス)］ */
#define RADIO_PADRV_CTRL_ADR            (0x40u)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ制御設定(@ref RADIO_PADRV_CTRL_T 型でアクセス)］ */
#define RADIO_PADRV_ADJ1_ADR            (0x41u)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ調整1(@ref RADIO_PADRV_ADJ1_T 型でアクセス)］ */
#define RADIO_PADRV_ADJ2_H_ADR          (0x42u)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ調整1(上位バイト)(@ref RADIO_PADRV_ADJ2_H_T 型でアクセス)］ */
#define RADIO_PADRV_ADJ2_L_ADR          (0x43u)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ調整1(下位バイト)(@ref RADIO_PADRV_ADJ2_L_T 型でアクセス)］ */
#define RADIO_PADRV_CLK_SET_H_ADR       (0x44u)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ制御用クロック設定(上位バイト)(@ref RADIO_PADRV_CLK_SET_H_T 型でアクセス)］ */
#define RADIO_PADRV_CLK_SET_L_ADR       (0x45u)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ制御用クロック設定(下位バイト)(@ref RADIO_PADRV_CLK_SET_L_T 型でアクセス)］ */
#define RADIO_PADRV_UP_ADJ_ADR          (0x46u)     /*!< ［｜<in-house>*TODO*英訳｜BPSKドライバ制御立上り開始時間設定(@ref RADIO_PADRV_UP_ADJ_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B10_ADR47       (0x47u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR48       (0x48u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR49       (0x49u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR4A       (0x4Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR4B       (0x4Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR4C       (0x4Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR4D       (0x4Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR4E       (0x4Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR4F       (0x4Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR50       (0x50u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR51       (0x51u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR52       (0x52u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR53       (0x53u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR54       (0x54u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR55       (0x55u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR56       (0x56u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR57       (0x57u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR58       (0x58u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR59       (0x59u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR5A       (0x5Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR5B       (0x5Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR5C       (0x5Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR5D       (0x5Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR5E       (0x5Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR5F       (0x5Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR60       (0x60u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR61       (0x61u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR62       (0x62u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR63       (0x63u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR64       (0x64u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR65       (0x65u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR66       (0x66u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR67       (0x67u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR68       (0x68u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR69       (0x69u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR6A       (0x6Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR6B       (0x6Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR6C       (0x6Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR6D       (0x6Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR6E       (0x6Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR6F       (0x6Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR70       (0x70u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR71       (0x71u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR72       (0x72u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR73       (0x73u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR74       (0x74u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR75       (0x75u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR76       (0x76u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR77       (0x77u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR78       (0x78u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR79       (0x79u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR7A       (0x7Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR7B       (0x7Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR7C       (0x7Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR7D       (0x7Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR7E       (0x7Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B10_ADR7F       (0x7Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */

#define BANK_BPSK_STEP_CTRL_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定(@ref RADIO_BPSK_STEP_CTRL_T 型でアクセス)］ */
#define BANK_BPSK_STEP_CLK_SET_ADR     (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御クロック設定(@ref RADIO_BPSK_STEP_CLK_SET_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B10_ADR03       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_BPSK_STEP_SET0_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定0(@ref RADIO_BPSK_STEP_SET0_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET1_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定1(@ref RADIO_BPSK_STEP_SET1_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET2_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定2(@ref RADIO_BPSK_STEP_SET2_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET3_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定3(@ref RADIO_BPSK_STEP_SET3_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET4_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定4(@ref RADIO_BPSK_STEP_SET4_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET5_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定5(@ref RADIO_BPSK_STEP_SET5_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET6_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定6(@ref RADIO_BPSK_STEP_SET6_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET7_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定7(@ref RADIO_BPSK_STEP_SET7_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET8_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定8(@ref RADIO_BPSK_STEP_SET8_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET9_ADR        (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定9(@ref RADIO_BPSK_STEP_SET9_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET10_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定10(@ref RADIO_BPSK_STEP_SET10_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET11_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定11(@ref RADIO_BPSK_STEP_SET11_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET12_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定12(@ref RADIO_BPSK_STEP_SET12_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET13_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定13(@ref RADIO_BPSK_STEP_SET13_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET14_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定14(@ref RADIO_BPSK_STEP_SET14_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET15_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定15(@ref RADIO_BPSK_STEP_SET15_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET16_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定16(@ref RADIO_BPSK_STEP_SET16_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET17_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定17(@ref RADIO_BPSK_STEP_SET17_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET18_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定18(@ref RADIO_BPSK_STEP_SET18_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET19_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定19(@ref RADIO_BPSK_STEP_SET19_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET20_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定20(@ref RADIO_BPSK_STEP_SET20_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET21_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定21(@ref RADIO_BPSK_STEP_SET21_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET22_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定22(@ref RADIO_BPSK_STEP_SET22_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET23_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定23(@ref RADIO_BPSK_STEP_SET23_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET24_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定24(@ref RADIO_BPSK_STEP_SET24_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET25_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定25(@ref RADIO_BPSK_STEP_SET25_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET26_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定26(@ref RADIO_BPSK_STEP_SET26_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET27_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定27(@ref RADIO_BPSK_STEP_SET27_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET28_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定28(@ref RADIO_BPSK_STEP_SET28_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET29_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定29(@ref RADIO_BPSK_STEP_SET29_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET30_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定30(@ref RADIO_BPSK_STEP_SET30_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET31_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定31(@ref RADIO_BPSK_STEP_SET31_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET32_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定32(@ref RADIO_BPSK_STEP_SET32_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET33_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定33(@ref RADIO_BPSK_STEP_SET33_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET34_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定34(@ref RADIO_BPSK_STEP_SET34_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET35_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定35(@ref RADIO_BPSK_STEP_SET35_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET36_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定36(@ref RADIO_BPSK_STEP_SET36_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET37_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定37(@ref RADIO_BPSK_STEP_SET37_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET38_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定38(@ref RADIO_BPSK_STEP_SET38_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET39_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定39(@ref RADIO_BPSK_STEP_SET39_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET40_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定40(@ref RADIO_BPSK_STEP_SET40_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET41_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定41(@ref RADIO_BPSK_STEP_SET41_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET42_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定42(@ref RADIO_BPSK_STEP_SET42_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET43_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定43(@ref RADIO_BPSK_STEP_SET43_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET44_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定44(@ref RADIO_BPSK_STEP_SET44_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET45_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定45(@ref RADIO_BPSK_STEP_SET45_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET46_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定46(@ref RADIO_BPSK_STEP_SET46_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET47_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定47(@ref RADIO_BPSK_STEP_SET47_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET48_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定48(@ref RADIO_BPSK_STEP_SET48_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET49_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定49(@ref RADIO_BPSK_STEP_SET49_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET50_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定50(@ref RADIO_BPSK_STEP_SET50_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET51_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定51(@ref RADIO_BPSK_STEP_SET51_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET52_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定52(@ref RADIO_BPSK_STEP_SET52_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET53_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定53(@ref RADIO_BPSK_STEP_SET53_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET54_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定54(@ref RADIO_BPSK_STEP_SET54_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET55_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定55(@ref RADIO_BPSK_STEP_SET55_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET56_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定56(@ref RADIO_BPSK_STEP_SET56_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET57_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定57(@ref RADIO_BPSK_STEP_SET57_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET58_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定58(@ref RADIO_BPSK_STEP_SET58_T 型でアクセス)］ */
#define BANK_BPSK_STEP_SET59_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKステップ制御設定59(@ref RADIO_BPSK_STEP_SET59_T 型でアクセス)］ */
#define BANK_PADRV_CTRL_ADR            (10)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ制御設定(@ref RADIO_PADRV_CTRL_T 型でアクセス)］ */
#define BANK_PADRV_ADJ1_ADR            (10)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ調整1(@ref RADIO_PADRV_ADJ1_T 型でアクセス)］ */
#define BANK_PADRV_ADJ2_H_ADR          (10)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ調整1(上位バイト)(@ref RADIO_PADRV_ADJ2_H_T 型でアクセス)］ */
#define BANK_PADRV_ADJ2_L_ADR          (10)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ調整1(下位バイト)(@ref RADIO_PADRV_ADJ2_L_T 型でアクセス)］ */
#define BANK_PADRV_CLK_SET_H_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ制御用クロック設定(上位バイト)(@ref RADIO_PADRV_CLK_SET_H_T 型でアクセス)］ */
#define BANK_PADRV_CLK_SET_L_ADR       (10)     /*!< ［｜<in-house>*TODO*英訳｜PAドライバ制御用クロック設定(下位バイト)(@ref RADIO_PADRV_CLK_SET_L_T 型でアクセス)］ */
#define BANK_PADRV_UP_ADJ_ADR          (10)     /*!< ［｜<in-house>*TODO*英訳｜BPSKドライバ制御立上り開始時間設定(@ref RADIO_PADRV_UP_ADJ_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B10_ADR47       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR48       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR49       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR4A       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR4B       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR4C       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR4D       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR4E       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR4F       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR50       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR51       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR52       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR53       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR54       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR55       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR56       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR57       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR58       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR59       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR5A       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR5B       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR5C       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR5D       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR5E       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR5F       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR60       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR61       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR62       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR63       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR64       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR65       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR66       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR67       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR68       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR69       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR6A       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR6B       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR6C       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR6D       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR6E       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR6F       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR70       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR71       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR72       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR73       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR74       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR75       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR76       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR77       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR78       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR79       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR7A       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR7B       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR7C       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR7D       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR7E       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B10_ADR7F       (10)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */


/* ［RF register structures｜RFレジスタ構造体］ */

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_CTRL_ADR access｜@ref RADIO_BPSK_STEP_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_clk_set:       1;      /*!<［｜<in-house>*TODO*英訳｜ステップ制御クロック周期設定 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t bpsk_step_en:       1;      /*!<［｜<in-house>*TODO*英訳｜ステップ制御イネーブル設定 R/W］*/
        uint8_t bpsk_step_sel:      1;      /*!<［｜<in-house>*TODO*英訳｜ステップ制御機能選択設定 R/W］*/
        uint8_t bpsk_clk_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜ステップ制御クロック選択設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_CTRL_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_CLK_SET_ADR access｜@ref RADIO_BPSK_STEP_CLK_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bpsk_clk_set:       8;      /*!<［｜<in-house>*TODO*英訳｜ステップ制御クロック周期設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_CLK_SET_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET0_ADR access｜@ref RADIO_BPSK_STEP_SET0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step0:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御0 R/W］*/
        uint8_t step1:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET0_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET1_ADR access｜@ref RADIO_BPSK_STEP_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step2:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御2 R/W］*/
        uint8_t step3:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御3 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET1_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET2_ADR access｜@ref RADIO_BPSK_STEP_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step4:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御4 R/W］*/
        uint8_t step5:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御5 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET2_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET3_ADR access｜@ref RADIO_BPSK_STEP_SET3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step6:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御6 R/W］*/
        uint8_t step7:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御7 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET3_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET4_ADR access｜@ref RADIO_BPSK_STEP_SET4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step8:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御8 R/W］*/
        uint8_t step9:              4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御9 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET4_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET5_ADR access｜@ref RADIO_BPSK_STEP_SET5_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step10:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御10 R/W］*/
        uint8_t step11:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御11 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET5_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET6_ADR access｜@ref RADIO_BPSK_STEP_SET6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step12:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御12 R/W］*/
        uint8_t step13:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御13 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET6_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET7_ADR access｜@ref RADIO_BPSK_STEP_SET7_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step14:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御14 R/W］*/
        uint8_t step15:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御15 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET7_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET8_ADR access｜@ref RADIO_BPSK_STEP_SET8_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step16:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御16 R/W］*/
        uint8_t step17:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御17 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET8_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET9_ADR access｜@ref RADIO_BPSK_STEP_SET9_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step18:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御18 R/W］*/
        uint8_t step19:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御19 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET9_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET10_ADR access｜@ref RADIO_BPSK_STEP_SET10_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step20:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御20 R/W］*/
        uint8_t step21:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御21 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET10_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET11_ADR access｜@ref RADIO_BPSK_STEP_SET11_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step22:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御22 R/W］*/
        uint8_t step23:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御23 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET11_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET12_ADR access｜@ref RADIO_BPSK_STEP_SET12_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step24:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御24 R/W］*/
        uint8_t step25:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御25 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET12_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET13_ADR access｜@ref RADIO_BPSK_STEP_SET13_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step26:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御26 R/W］*/
        uint8_t step27:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御27 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET13_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET14_ADR access｜@ref RADIO_BPSK_STEP_SET14_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step28:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御28 R/W］*/
        uint8_t step29:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御29 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET14_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET15_ADR access｜@ref RADIO_BPSK_STEP_SET15_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step30:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御30 R/W］*/
        uint8_t step31:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御31 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET15_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET16_ADR access｜@ref RADIO_BPSK_STEP_SET16_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step32:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御32 R/W］*/
        uint8_t step33:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御33 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET16_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET17_ADR access｜@ref RADIO_BPSK_STEP_SET17_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step34:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御34 R/W］*/
        uint8_t step35:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御35 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET17_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET18_ADR access｜@ref RADIO_BPSK_STEP_SET18_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step36:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御36 R/W］*/
        uint8_t step37:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御37 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET18_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET19_ADR access｜@ref RADIO_BPSK_STEP_SET19_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step38:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御38 R/W］*/
        uint8_t step39:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御39 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET19_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET20_ADR access｜@ref RADIO_BPSK_STEP_SET20_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step40:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御40 R/W］*/
        uint8_t step41:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御41 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET20_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET21_ADR access｜@ref RADIO_BPSK_STEP_SET21_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step42:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御42 R/W］*/
        uint8_t step43:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御43 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET21_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET22_ADR access｜@ref RADIO_BPSK_STEP_SET22_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step44:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御44 R/W］*/
        uint8_t step45:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御45 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET22_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET23_ADR access｜@ref RADIO_BPSK_STEP_SET23_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step46:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御46 R/W］*/
        uint8_t step47:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御47 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET23_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET24_ADR access｜@ref RADIO_BPSK_STEP_SET24_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step48:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御48 R/W］*/
        uint8_t step49:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御49 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET24_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET25_ADR access｜@ref RADIO_BPSK_STEP_SET25_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step50:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御50 R/W］*/
        uint8_t step51:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御51 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET25_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET26_ADR access｜@ref RADIO_BPSK_STEP_SET26_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step52:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御52 R/W］*/
        uint8_t step53:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御53 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET26_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET27_ADR access｜@ref RADIO_BPSK_STEP_SET27_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step54:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御54 R/W］*/
        uint8_t step55:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御55 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET27_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET28_ADR access｜@ref RADIO_BPSK_STEP_SET28_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step56:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御56 R/W］*/
        uint8_t step57:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御57 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET28_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET29_ADR access｜@ref RADIO_BPSK_STEP_SET29_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step58:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御58 R/W］*/
        uint8_t step59:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御59 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET29_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET30_ADR access｜@ref RADIO_BPSK_STEP_SET30_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step60:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御60 R/W］*/
        uint8_t step61:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御61 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET30_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET31_ADR access｜@ref RADIO_BPSK_STEP_SET31_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step62:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御62 R/W］*/
        uint8_t step63:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御63 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET31_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET32_ADR access｜@ref RADIO_BPSK_STEP_SET32_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step64:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御64 R/W］*/
        uint8_t step65:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御65 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET32_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET33_ADR access｜@ref RADIO_BPSK_STEP_SET33_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step66:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御66 R/W］*/
        uint8_t step67:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御67 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET33_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET34_ADR access｜@ref RADIO_BPSK_STEP_SET34_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step68:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御68 R/W］*/
        uint8_t step69:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御69 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET34_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET35_ADR access｜@ref RADIO_BPSK_STEP_SET35_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step70:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御70 R/W］*/
        uint8_t step71:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御71 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET35_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET36_ADR access｜@ref RADIO_BPSK_STEP_SET36_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step72:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御72 R/W］*/
        uint8_t step73:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御73 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET36_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET37_ADR access｜@ref RADIO_BPSK_STEP_SET37_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step74:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御74 R/W］*/
        uint8_t step75:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御75 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET37_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET38_ADR access｜@ref RADIO_BPSK_STEP_SET38_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step76:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御76 R/W］*/
        uint8_t step77:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御77 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET38_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET39_ADR access｜@ref RADIO_BPSK_STEP_SET39_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step78:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御78 R/W］*/
        uint8_t step79:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御79 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET39_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET40_ADR access｜@ref RADIO_BPSK_STEP_SET40_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step80:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御80 R/W］*/
        uint8_t step81:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御81 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET40_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET41_ADR access｜@ref RADIO_BPSK_STEP_SET41_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step82:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御82 R/W］*/
        uint8_t step83:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御83 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET41_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET42_ADR access｜@ref RADIO_BPSK_STEP_SET42_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step84:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御84 R/W］*/
        uint8_t step85:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御85 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET42_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET43_ADR access｜@ref RADIO_BPSK_STEP_SET43_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step86:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御86 R/W］*/
        uint8_t step87:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御87 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET43_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET44_ADR access｜@ref RADIO_BPSK_STEP_SET44_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step88:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御88 R/W］*/
        uint8_t step89:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御89 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET44_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET45_ADR access｜@ref RADIO_BPSK_STEP_SET45_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step90:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御90 R/W］*/
        uint8_t step91:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御91 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET45_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET46_ADR access｜@ref RADIO_BPSK_STEP_SET46_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step92:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御92 R/W］*/
        uint8_t step93:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御93 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET46_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET47_ADR access｜@ref RADIO_BPSK_STEP_SET47_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step94:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御94 R/W］*/
        uint8_t step95:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御95 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET47_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET48_ADR access｜@ref RADIO_BPSK_STEP_SET48_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step96:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御96 R/W］*/
        uint8_t step97:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御97 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET48_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET49_ADR access｜@ref RADIO_BPSK_STEP_SET49_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step98:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御98 R/W］*/
        uint8_t step99:             4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御99 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET49_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET50_ADR access｜@ref RADIO_BPSK_STEP_SET50_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step100:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御100 R/W］*/
        uint8_t step101:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御101 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET50_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET51_ADR access｜@ref RADIO_BPSK_STEP_SET51_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step102:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御102 R/W］*/
        uint8_t step103:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御103 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET51_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET52_ADR access｜@ref RADIO_BPSK_STEP_SET52_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step104:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御104 R/W］*/
        uint8_t step105:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御105 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET52_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET53_ADR access｜@ref RADIO_BPSK_STEP_SET53_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step106:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御106 R/W］*/
        uint8_t step107:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御107 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET53_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET54_ADR access｜@ref RADIO_BPSK_STEP_SET54_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step108:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御108 R/W］*/
        uint8_t step109:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御109 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET54_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET55_ADR access｜@ref RADIO_BPSK_STEP_SET55_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step110:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御110 R/W］*/
        uint8_t step111:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御111 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET55_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET56_ADR access｜@ref RADIO_BPSK_STEP_SET56_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step112:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御112 R/W］*/
        uint8_t step113:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御113 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET56_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET57_ADR access｜@ref RADIO_BPSK_STEP_SET57_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step114:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御114 R/W］*/
        uint8_t step115:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御115 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET57_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET58_ADR access｜@ref RADIO_BPSK_STEP_SET58_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step116:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御116 R/W］*/
        uint8_t step117:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御117 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET58_T;

/** @brief ［Type definition for @ref RADIO_BPSK_STEP_SET59_ADR access｜@ref RADIO_BPSK_STEP_SET59_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t step118:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御118 R/W］*/
        uint8_t step119:            4;      /*!<［｜<in-house>*TODO*英訳｜BPSKステップ制御119 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BPSK_STEP_SET59_T;

/** @brief ［Type definition for @ref RADIO_PADRV_CTRL_ADR access｜@ref RADIO_PADRV_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_ctrl_en:      1;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ制御イネーブル R/W］*/
        uint8_t padrv_ctrl_sel:     1;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ制御機能選択設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t padrv_dly:          4;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ制御遅延設定(設定範囲: 2～15) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_CTRL_T;

/** @brief ［Type definition for @ref RADIO_PADRV_ADJ1_ADR access｜@ref RADIO_PADRV_ADJ1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_adj1:         3;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ調整1 R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_ADJ1_T;

/** @brief ［Type definition for @ref RADIO_PADRV_ADJ2_H_ADR access｜@ref RADIO_PADRV_ADJ2_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_adj2_h:       1;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ調整2 R/W］*/
        uint8_t padrv_inc:          1;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ線形制御用カウンタインクリメント・デクリメント設定 R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_ADJ2_H_T;

/** @brief ［Type definition for @ref RADIO_PADRV_ADJ2_L_ADR access｜@ref RADIO_PADRV_ADJ2_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_adj2_l:       8;      /*!<［｜<in-house>*TODO*英訳｜PAドライバ調整2(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_ADJ2_L_T;

/** @brief ［Type definition for @ref RADIO_PADRV_CLK_SET_H_ADR access｜@ref RADIO_PADRV_CLK_SET_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_clk_set_h:    1;      /*!<［｜<in-house>*TODO*英訳｜PA ドライバ制御クロック周期設定 R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t padrv_clk_step:     1;      /*!<［｜<in-house>*TODO*英訳｜PA ドライバ線形制御クロック周波数選択設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_CLK_SET_H_T;

/** @brief ［Type definition for @ref RADIO_PADRV_CLK_SET_L_ADR access｜@ref RADIO_PADRV_CLK_SET_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_clk_set_l:    8;      /*!<［｜<in-house>*TODO*英訳｜PA ドライバ制御クロック周期設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_CLK_SET_L_T;

/** @brief ［Type definition for @ref RADIO_PADRV_UP_ADJ_ADR access｜@ref RADIO_PADRV_UP_ADJ_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t padrv_up_adj:       6;      /*!<［｜<in-house>*TODO*英訳｜PA ドライバ制御立上り開始時間設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_PADRV_UP_ADJ_T;

/** \} */ /* End of group RF_REGISTER_BANK10 */

#endif
