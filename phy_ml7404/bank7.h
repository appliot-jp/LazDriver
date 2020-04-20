/****************************************************************************************/
/**
   @file     bank7.h

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
#ifndef _bank7_H
#define _bank7_H

/**
    \addtogroup RF_REGISTER_BANK7
    \{
*/
 
/*［BANK7 Register Address Definitions｜BANK7レジスタアドレス定義］*/
#define RADIO_DSSS_CTRL_ADR             (0x01u)     /*!< ［｜<in-house>*TODO*英訳｜DSSS制御設定(@ref RADIO_DSSS_CTRL_T 型でアクセス)］ */
#define RADIO_DSSS_MODE_ADR             (0x02u)     /*!< ［｜<in-house>*TODO*英訳｜DSSSモード設定(@ref RADIO_DSSS_MODE_T 型でアクセス)］ */
#define RADIO_FEC_ENC_CTRL_ADR          (0x03u)     /*!< ［｜<in-house>*TODO*英訳｜FECエンコーダ設定(@ref RADIO_FEC_ENC_CTRL_T 型でアクセス)］ */
#define RADIO_FEC_INIT_STATE_ADR        (0x04u)     /*!< ［｜<in-house>*TODO*英訳｜FECの初期化状態(@ref RADIO_FEC_INIT_STATE_T 型でアクセス)］ */
#define RADIO_FEC_DEC_CTRL_ADR          (0x05u)     /*!< ［｜<in-house>*TODO*英訳｜FECデコーダ設定(@ref RADIO_FEC_DEC_CTRL_T 型でアクセス)］ */
#define RADIO_SF_CTRL_ADR               (0x06u)     /*!< ［｜<in-house>*TODO*英訳｜拡散率設定(@ref RADIO_SF_CTRL_T 型でアクセス)］ */
#define RADIO_SHR_GOLD_SEED3_ADR        (0x07u)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定3(@ref RADIO_SHR_GOLD_SEED3_T 型でアクセス)］ */
#define RADIO_SHR_GOLD_SEED2_ADR        (0x08u)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定2(@ref RADIO_SHR_GOLD_SEED2_T 型でアクセス)］ */
#define RADIO_SHR_GOLD_SEED1_ADR        (0x09u)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定1(@ref RADIO_SHR_GOLD_SEED1_T 型でアクセス)］ */
#define RADIO_SHR_GOLD_SEED0_ADR        (0x0Au)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定0(@ref RADIO_SHR_GOLD_SEED0_T 型でアクセス)］ */
#define RADIO_PSDU_GOLD_SEED3_ADR       (0x0Bu)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定3(@ref RADIO_PSDU_GOLD_SEED3_T 型でアクセス)］ */
#define RADIO_PSDU_GOLD_SEED2_ADR       (0x0Cu)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定2(@ref RADIO_PSDU_GOLD_SEED2_T 型でアクセス)］ */
#define RADIO_PSDU_GOLD_SEED1_ADR       (0x0Du)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定1(@ref RADIO_PSDU_GOLD_SEED1_T 型でアクセス)］ */
#define RADIO_PSDU_GOLD_SEED0_ADR       (0x0Eu)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定0(@ref RADIO_PSDU_GOLD_SEED0_T 型でアクセス)］ */
#define RADIO_DSSS_PREAMBLE3_ADR        (0x0Fu)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定3(@ref RADIO_DSSS_PREAMBLE3_T 型でアクセス)］ */
#define RADIO_DSSS_PREAMBLE2_ADR        (0x10u)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定2(@ref RADIO_DSSS_PREAMBLE2_T 型でアクセス)］ */
#define RADIO_DSSS_PREAMBLE1_ADR        (0x11u)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定1(@ref RADIO_DSSS_PREAMBLE1_T 型でアクセス)］ */
#define RADIO_DSSS_PREAMBLE0_ADR        (0x12u)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定0(@ref RADIO_DSSS_PREAMBLE0_T 型でアクセス)］ */
#define RADIO_SS_DOWN_SIZE_ADR          (0x13u)     /*!< ［｜<in-house>*TODO*英訳｜DSSSダウンサンプル設定(@ref RADIO_SS_DOWN_SIZE_T 型でアクセス)］ */
#define RADIO_SS_AFC_RANGE_SYNC_ADR     (0x14u)     /*!< ［｜<in-house>*TODO*英訳｜DSSS(@ref RADIO_SS_AFC_RANGE_SYNC_T 型でアクセス)］ */
#define RADIO_SS_AFC_RANGE_ADR          (0x15u)     /*!< ［｜<in-house>*TODO*英訳｜DSSS(@ref RADIO_SS_AFC_RANGE_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B7_ADR16        (0x16u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_DSSS_RATE_SYNC_H_ADR      (0x17u)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期時受信チップレート設定(上位4ビット)(@ref RADIO_DSSS_RATE_SYNC_H_T 型でアクセス)］ */
#define RADIO_DSSS_RATE_SYNC_L_ADR      (0x18u)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期時受信チップレート設定(下位バイト)(@ref RADIO_DSSS_RATE_SYNC_L_T 型でアクセス)］ */
#define RADIO_DSSS_RATE_H_ADR           (0x19u)     /*!< ［｜<in-house>*TODO*英訳｜DSSSデータ受信時受信チップレート設定(上位4ビット)(@ref RADIO_DSSS_RATE_H_T 型でアクセス)］ */
#define RADIO_DSSS_RATE_L_ADR           (0x1Au)     /*!< ［｜<in-house>*TODO*英訳｜DSSSデータ受信時受信データレート設定(下位バイト)(@ref RADIO_DSSS_RATE_L_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT8_GATE_H_ADR   (0x1Bu)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定(上位3ビット)(@ref RADIO_SS_SYNC_BIT8_GATE_H_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT8_GATE_L_ADR   (0x1Cu)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定(下位バイト)(@ref RADIO_SS_SYNC_BIT8_GATE_L_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT8_GATE2_H_ADR  (0x1Du)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定2(上位3ビット)(@ref RADIO_SS_SYNC_BIT8_GATE2_H_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT8_GATE2_L_ADR  (0x1Eu)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定2(下位バイト)(@ref RADIO_SS_SYNC_BIT8_GATE2_L_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT_GATE_H_ADR    (0x1Fu)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立後相関閾値設定(上位3ビット(@ref RADIO_SS_SYNC_BIT_GATE_H_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT_GATE_L_ADR    (0x20u)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立後相関閾値設定(下位バイト)(@ref RADIO_SS_SYNC_BIT_GATE_L_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT4_GATE_H_ADR   (0x21u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_BIT4_GATE_H_T 型でアクセス)］ */
#define RADIO_SS_SYNC_BIT4_GATE_L_ADR   (0x22u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_BIT4_GATE_L_T 型でアクセス)］ */
#define RADIO_SS_SYNC_LOST_GATE_ADR     (0x23u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_LOST_GATE_T 型でアクセス)］ */
#define RADIO_SS_BIT8_MAX_ACC_H_ADR     (0x24u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_BIT8_MAX_ACC_H_T 型でアクセス)］ */
#define RADIO_SS_BIT8_MAX_ACC_L_ADR     (0x25u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_BIT8_MAX_ACC_L_T 型でアクセス)］ */
#define RADIO_SS_SYNC_GATE2_PLUS_ADR    (0x26u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_GATE2_PLUS_T 型でアクセス)］ */
#define RADIO_AGC_AVE_OFST_SYNC_ADR     (0x27u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_AVE_OFST_SYNC_T 型でアクセス)］ */
#define RADIO_AGC_AVE_OFST_ADR          (0x28u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_AVE_OFST_T 型でアクセス)］ */
#define RADIO_AGC_IIR_SET0_ADR          (0x29u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_IIR_SET0_T 型でアクセス)］ */
#define RADIO_AGC_IIR_SET1_ADR          (0x2Au)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_IIR_SET1_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B7_ADR2B        (0x2Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_DSSS_SET1_ADR             (0x2Cu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET1_T 型でアクセス)］ */
#define RADIO_DSSS_SET2_ADR             (0x2Du)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET2_T 型でアクセス)］ */
#define RADIO_DSSS_SET3_ADR             (0x2Eu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET3_T 型でアクセス)］ */
#define RADIO_DSSS_SET4_ADR             (0x2Fu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET4_T 型でアクセス)］ */
#define RADIO_DSSS_SET5_ADR             (0x30u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET5_T 型でアクセス)］ */
#define RADIO_SS_AFC_OUT_ADR            (0x31u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_AFC_OUT_T 型でアクセス)］ */
#define RADIO_SS_AFC_FIX_EN_ADR         (0x32u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_AFC_FIX_EN_T 型でアクセス)］ */
#define RADIO_SS_AFC_FIX_ADR            (0x33u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_AFC_FIX_T 型でアクセス)］ */
#define RADIO_DSSS_MON_SEL_ADR          (0x34u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_MON_SEL_T 型でアクセス)］ */
#define RADIO_BIT8_SPDET_TH_H_ADR       (0x35u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_BIT8_SPDET_TH_H_T 型でアクセス)］ */
#define RADIO_BIT8_SPDET_TH_L_ADR       (0x36u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_BIT8_SPDET_TH_L_T 型でアクセス)］ */
#define RADIO_DSSS_SET6_ADR             (0x37u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET6_T 型でアクセス)］ */
#define RADIO_DSSS_SET7_ADR             (0x38u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET7_T 型でアクセス)］ */
#define RADIO_DSSS_SET8_ADR             (0x39u)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET8_T 型でアクセス)］ */
#define RADIO_DSSS_SET9_ADR             (0x3Au)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET9_T 型でアクセス)］ */
#define RADIO_DSSS_SET10_ADR            (0x3Bu)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET10_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B7_ADR3C        (0x3Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR3D        (0x3Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR3E        (0x3Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR3F        (0x3Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR40        (0x40u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR41        (0x41u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR42        (0x42u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR43        (0x43u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR44        (0x44u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR45        (0x45u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR46        (0x46u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR47        (0x47u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR48        (0x48u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR49        (0x49u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR4A        (0x4Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR4B        (0x4Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR4C        (0x4Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR4D        (0x4Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR4E        (0x4Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR4F        (0x4Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR50        (0x50u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR51        (0x51u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR52        (0x52u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR53        (0x53u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR54        (0x54u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR55        (0x55u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR56        (0x56u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR57        (0x57u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR58        (0x58u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR59        (0x59u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR5A        (0x5Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR5B        (0x5Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR5C        (0x5Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR5D        (0x5Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR5E        (0x5Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR5F        (0x5Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR60        (0x60u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR61        (0x61u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR62        (0x62u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR63        (0x63u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR64        (0x64u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR65        (0x65u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR66        (0x66u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR67        (0x67u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR68        (0x68u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR69        (0x69u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR6A        (0x6Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR6B        (0x6Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR6C        (0x6Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR6D        (0x6Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR6E        (0x6Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR6F        (0x6Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR70        (0x70u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR71        (0x71u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR72        (0x72u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR73        (0x73u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR74        (0x74u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR75        (0x75u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR76        (0x76u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR77        (0x77u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR78        (0x78u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR79        (0x79u)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR7A        (0x7Au)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR7B        (0x7Bu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR7C        (0x7Cu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR7D        (0x7Du)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR7E        (0x7Eu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B7_ADR7F        (0x7Fu)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */

#define BANK_DSSS_CTRL_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS制御設定(@ref RADIO_DSSS_CTRL_T 型でアクセス)］ */
#define BANK_DSSS_MODE_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSモード設定(@ref RADIO_DSSS_MODE_T 型でアクセス)］ */
#define BANK_FEC_ENC_CTRL_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜FECエンコーダ設定(@ref RADIO_FEC_ENC_CTRL_T 型でアクセス)］ */
#define BANK_FEC_INIT_STATE_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜FECの初期化状態(@ref RADIO_FEC_INIT_STATE_T 型でアクセス)］ */
#define BANK_FEC_DEC_CTRL_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜FECデコーダ設定(@ref RADIO_FEC_DEC_CTRL_T 型でアクセス)］ */
#define BANK_SF_CTRL_ADR               (7)     /*!< ［｜<in-house>*TODO*英訳｜拡散率設定(@ref RADIO_SF_CTRL_T 型でアクセス)］ */
#define BANK_SHR_GOLD_SEED3_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定3(@ref RADIO_SHR_GOLD_SEED3_T 型でアクセス)］ */
#define BANK_SHR_GOLD_SEED2_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定2(@ref RADIO_SHR_GOLD_SEED2_T 型でアクセス)］ */
#define BANK_SHR_GOLD_SEED1_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定1(@ref RADIO_SHR_GOLD_SEED1_T 型でアクセス)］ */
#define BANK_SHR_GOLD_SEED0_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定0(@ref RADIO_SHR_GOLD_SEED0_T 型でアクセス)］ */
#define BANK_PSDU_GOLD_SEED3_ADR       (7)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定3(@ref RADIO_PSDU_GOLD_SEED3_T 型でアクセス)］ */
#define BANK_PSDU_GOLD_SEED2_ADR       (7)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定2(@ref RADIO_PSDU_GOLD_SEED2_T 型でアクセス)］ */
#define BANK_PSDU_GOLD_SEED1_ADR       (7)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定1(@ref RADIO_PSDU_GOLD_SEED1_T 型でアクセス)］ */
#define BANK_PSDU_GOLD_SEED0_ADR       (7)     /*!< ［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定0(@ref RADIO_PSDU_GOLD_SEED0_T 型でアクセス)］ */
#define BANK_DSSS_PREAMBLE3_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定3(@ref RADIO_DSSS_PREAMBLE3_T 型でアクセス)］ */
#define BANK_DSSS_PREAMBLE2_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定2(@ref RADIO_DSSS_PREAMBLE2_T 型でアクセス)］ */
#define BANK_DSSS_PREAMBLE1_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定1(@ref RADIO_DSSS_PREAMBLE1_T 型でアクセス)］ */
#define BANK_DSSS_PREAMBLE0_ADR        (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定0(@ref RADIO_DSSS_PREAMBLE0_T 型でアクセス)］ */
#define BANK_SS_DOWN_SIZE_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSダウンサンプル設定(@ref RADIO_SS_DOWN_SIZE_T 型でアクセス)］ */
#define BANK_SS_AFC_RANGE_SYNC_ADR     (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS(@ref RADIO_SS_AFC_RANGE_SYNC_T 型でアクセス)］ */
#define BANK_SS_AFC_RANGE_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS(@ref RADIO_SS_AFC_RANGE_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B7_ADR16        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_DSSS_RATE_SYNC_H_ADR      (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期時受信チップレート設定(上位4ビット)(@ref RADIO_DSSS_RATE_SYNC_H_T 型でアクセス)］ */
#define BANK_DSSS_RATE_SYNC_L_ADR      (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期時受信チップレート設定(下位バイト)(@ref RADIO_DSSS_RATE_SYNC_L_T 型でアクセス)］ */
#define BANK_DSSS_RATE_H_ADR           (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSデータ受信時受信チップレート設定(上位4ビット)(@ref RADIO_DSSS_RATE_H_T 型でアクセス)］ */
#define BANK_DSSS_RATE_L_ADR           (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSSデータ受信時受信データレート設定(下位バイト)(@ref RADIO_DSSS_RATE_L_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT8_GATE_H_ADR   (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定(上位3ビット)(@ref RADIO_SS_SYNC_BIT8_GATE_H_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT8_GATE_L_ADR   (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定(下位バイト)(@ref RADIO_SS_SYNC_BIT8_GATE_L_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT8_GATE2_H_ADR  (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定2(上位3ビット)(@ref RADIO_SS_SYNC_BIT8_GATE2_H_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT8_GATE2_L_ADR  (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定2(下位バイト)(@ref RADIO_SS_SYNC_BIT8_GATE2_L_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT_GATE_H_ADR    (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立後相関閾値設定(上位3ビット(@ref RADIO_SS_SYNC_BIT_GATE_H_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT_GATE_L_ADR    (7)     /*!< ［｜<in-house>*TODO*英訳｜DSSS同期確立後相関閾値設定(下位バイト)(@ref RADIO_SS_SYNC_BIT_GATE_L_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT4_GATE_H_ADR   (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_BIT4_GATE_H_T 型でアクセス)］ */
#define BANK_SS_SYNC_BIT4_GATE_L_ADR   (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_BIT4_GATE_L_T 型でアクセス)］ */
#define BANK_SS_SYNC_LOST_GATE_ADR     (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_LOST_GATE_T 型でアクセス)］ */
#define BANK_SS_BIT8_MAX_ACC_H_ADR     (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_BIT8_MAX_ACC_H_T 型でアクセス)］ */
#define BANK_SS_BIT8_MAX_ACC_L_ADR     (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_BIT8_MAX_ACC_L_T 型でアクセス)］ */
#define BANK_SS_SYNC_GATE2_PLUS_ADR    (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_SYNC_GATE2_PLUS_T 型でアクセス)］ */
#define BANK_AGC_AVE_OFST_SYNC_ADR     (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_AVE_OFST_SYNC_T 型でアクセス)］ */
#define BANK_AGC_AVE_OFST_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_AVE_OFST_T 型でアクセス)］ */
#define BANK_AGC_IIR_SET0_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_IIR_SET0_T 型でアクセス)］ */
#define BANK_AGC_IIR_SET1_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_AGC_IIR_SET1_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B7_ADR2B        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_DSSS_SET1_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET1_T 型でアクセス)］ */
#define BANK_DSSS_SET2_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET2_T 型でアクセス)］ */
#define BANK_DSSS_SET3_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET3_T 型でアクセス)］ */
#define BANK_DSSS_SET4_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET4_T 型でアクセス)］ */
#define BANK_DSSS_SET5_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET5_T 型でアクセス)］ */
#define BANK_SS_AFC_OUT_ADR            (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_AFC_OUT_T 型でアクセス)］ */
#define BANK_SS_AFC_FIX_EN_ADR         (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_AFC_FIX_EN_T 型でアクセス)］ */
#define BANK_SS_AFC_FIX_ADR            (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_SS_AFC_FIX_T 型でアクセス)］ */
#define BANK_DSSS_MON_SEL_ADR          (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_MON_SEL_T 型でアクセス)］ */
#define BANK_BIT8_SPDET_TH_H_ADR       (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_BIT8_SPDET_TH_H_T 型でアクセス)］ */
#define BANK_BIT8_SPDET_TH_L_ADR       (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_BIT8_SPDET_TH_L_T 型でアクセス)］ */
#define BANK_DSSS_SET6_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET6_T 型でアクセス)］ */
#define BANK_DSSS_SET7_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET7_T 型でアクセス)］ */
#define BANK_DSSS_SET8_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET8_T 型でアクセス)］ */
#define BANK_DSSS_SET9_ADR             (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET9_T 型でアクセス)］ */
#define BANK_DSSS_SET10_ADR            (7)     /*!< ［｜<in-house>*TODO*英訳｜*TODO*TBD(@ref RADIO_DSSS_SET10_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B7_ADR3C        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR3D        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR3E        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR3F        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR40        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR41        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR42        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR43        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR44        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR45        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR46        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR47        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR48        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR49        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR4A        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR4B        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR4C        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR4D        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR4E        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR4F        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR50        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR51        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR52        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR53        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR54        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR55        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR56        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR57        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR58        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR59        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR5A        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR5B        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR5C        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR5D        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR5E        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR5F        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR60        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR61        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR62        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR63        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR64        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR65        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR66        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR67        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR68        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR69        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR6A        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR6B        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR6C        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR6D        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR6E        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR6F        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR70        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR71        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR72        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR73        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR74        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR75        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR76        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR77        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR78        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR79        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR7A        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR7B        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR7C        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR7D        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR7E        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B7_ADR7F        (7)     /*!< ［｜<in-house>*TODO*英訳｜非公開］ */


/* ［RF register structures｜RFレジスタ構造体］ */

/** @brief ［Type definition for @ref RADIO_DSSS_CTRL_ADR access｜@ref RADIO_DSSS_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_en:            1;      /*!<［｜<in-house>*TODO*英訳｜DSSSイネーブル設定 R/W］*/
        uint8_t fec_en:             1;      /*!<［｜<in-house>*TODO*英訳｜FECイネーブル設定 R/W］*/
        uint8_t diff_enc_en:        1;      /*!<［｜<in-house>*TODO*英訳｜差動符号化イネーブル設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t psdu_size:          2;      /*!<［｜<in-house>*TODO*英訳｜DSSS時のPSDU長設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t sf_off:             1;      /*!<［｜<in-house>*TODO*英訳｜拡散OFF設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_CTRL_T;

/** @brief ［Type definition for @ref RADIO_DSSS_MODE_ADR access｜@ref RADIO_DSSS_MODE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_lc_sync:       2;      /*!<［｜<in-house>*TODO*英訳｜DSSS復調回路クロック設定(同期時) R/W］*/
        uint8_t dsss_lc_rcv:        2;      /*!<［｜<in-house>*TODO*英訳｜DSSS復調回路クロック設定(データ受信時) R/W］*/
        uint8_t sync_corr_gate:     2;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t fec_clk_sel:        2;      /*!<［｜<in-house>*TODO*英訳｜FECデコード時のデコーダ動作クロック設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_MODE_T;

/** @brief ［Type definition for @ref RADIO_FEC_ENC_CTRL_ADR access｜@ref RADIO_FEC_ENC_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t intlv_en:           1;      /*!<［｜<in-house>*TODO*英訳｜インタリーブイネーブル設定 R/W］*/
        uint8_t enc_init_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜FECエンコーダ初期状態選択設定 R/W］*/
        uint8_t enc_byte_msb:       1;      /*!<［｜<in-house>*TODO*英訳｜FECエンコーダバイト送出順設定 R/W］*/
        uint8_t enc_bit_msb:        1;      /*!<［｜<in-house>*TODO*英訳｜FECエンコーダビット送出順設定 R/W］*/
        uint8_t intlv_byte_msb:     1;      /*!<［｜<in-house>*TODO*英訳｜インタリーブバイト送出順設定 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FEC_ENC_CTRL_T;

/** @brief ［Type definition for @ref RADIO_FEC_INIT_STATE_ADR access｜@ref RADIO_FEC_INIT_STATE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fec_init_state:     6;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FEC_INIT_STATE_T;

/** @brief ［Type definition for @ref RADIO_FEC_DEC_CTRL_ADR access｜@ref RADIO_FEC_DEC_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t deintlv_en:         1;      /*!<［｜<in-house>*TODO*英訳｜デインタリーブイネーブル設定 R/W］*/
        uint8_t dec_init_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜FECデコーダ復号選択設定 R/W］*/
        uint8_t dec_byte_msb:       1;      /*!<［｜<in-house>*TODO*英訳｜FECデコーダデータ出力順設定 R/W］*/
        uint8_t dec_bit_msb:        1;      /*!<［｜<in-house>*TODO*英訳｜FECデコーダデータ入力順設定 R/W］*/
        uint8_t deintlv_byte_msb:   1;      /*!<［｜<in-house>*TODO*英訳｜デインタリーブデータ出力順設定 R/W］*/
        uint8_t fec_crc_area_sel:   1;      /*!<［｜<in-house>*TODO*英訳｜FEC受信時のCRC範囲設定 R/W］*/
        uint8_t fec_crc_lf_en:      1;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FEC_DEC_CTRL_T;

/** @brief ［Type definition for @ref RADIO_SF_CTRL_ADR access｜@ref RADIO_SF_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t shr_sf:             2;      /*!<［｜<in-house>*TODO*英訳｜SHR拡散率設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t psdu_sf:            2;      /*!<［｜<in-house>*TODO*英訳｜PSDU拡散率設定 R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SF_CTRL_T;

/** @brief ［Type definition for @ref RADIO_SHR_GOLD_SEED3_ADR access｜@ref RADIO_SHR_GOLD_SEED3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t shr_gold_seed3:     1;      /*!<［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定3 R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SHR_GOLD_SEED3_T;

/** @brief ［Type definition for @ref RADIO_SHR_GOLD_SEED2_ADR access｜@ref RADIO_SHR_GOLD_SEED2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t shr_gold_seed2:     8;      /*!<［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SHR_GOLD_SEED2_T;

/** @brief ［Type definition for @ref RADIO_SHR_GOLD_SEED1_ADR access｜@ref RADIO_SHR_GOLD_SEED1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t shr_gold_seed1:     8;      /*!<［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SHR_GOLD_SEED1_T;

/** @brief ［Type definition for @ref RADIO_SHR_GOLD_SEED0_ADR access｜@ref RADIO_SHR_GOLD_SEED0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t shr_gold_seed0:     8;      /*!<［｜<in-house>*TODO*英訳｜SHRゴールド符号シード設定0 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SHR_GOLD_SEED0_T;

/** @brief ［Type definition for @ref RADIO_PSDU_GOLD_SEED3_ADR access｜@ref RADIO_PSDU_GOLD_SEED3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t psdu_gold_seed3:    1;      /*!<［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定3 R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_PSDU_GOLD_SEED3_T;

/** @brief ［Type definition for @ref RADIO_PSDU_GOLD_SEED2_ADR access｜@ref RADIO_PSDU_GOLD_SEED2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t psdu_gold_seed2:    8;      /*!<［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PSDU_GOLD_SEED2_T;

/** @brief ［Type definition for @ref RADIO_PSDU_GOLD_SEED1_ADR access｜@ref RADIO_PSDU_GOLD_SEED1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t psdu_gold_seed1:    8;      /*!<［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PSDU_GOLD_SEED1_T;

/** @brief ［Type definition for @ref RADIO_PSDU_GOLD_SEED0_ADR access｜@ref RADIO_PSDU_GOLD_SEED0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t psdu_gold_seed0:    8;      /*!<［｜<in-house>*TODO*英訳｜PSDUゴールド符号シード設定0 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PSDU_GOLD_SEED0_T;

/** @brief ［Type definition for @ref RADIO_DSSS_PREAMBLE3_ADR access｜@ref RADIO_DSSS_PREAMBLE3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_preamble3:     8;      /*!<［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定3 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_PREAMBLE3_T;

/** @brief ［Type definition for @ref RADIO_DSSS_PREAMBLE2_ADR access｜@ref RADIO_DSSS_PREAMBLE2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_preamble2:     8;      /*!<［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_PREAMBLE2_T;

/** @brief ［Type definition for @ref RADIO_DSSS_PREAMBLE1_ADR access｜@ref RADIO_DSSS_PREAMBLE1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_preamble1:     8;      /*!<［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_PREAMBLE1_T;

/** @brief ［Type definition for @ref RADIO_DSSS_PREAMBLE0_ADR access｜@ref RADIO_DSSS_PREAMBLE0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_preamble0:     8;      /*!<［｜<in-house>*TODO*英訳｜DSSSプリアンブルパターン設定0 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_PREAMBLE0_T;

/** @brief ［Type definition for @ref RADIO_SS_DOWN_SIZE_ADR access｜@ref RADIO_SS_DOWN_SIZE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_down_size:       7;      /*!<［｜<in-house>*TODO*英訳｜DSSSダウンサンプル設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_DOWN_SIZE_T;

/** @brief ［Type definition for @ref RADIO_SS_AFC_RANGE_SYNC_ADR access｜@ref RADIO_SS_AFC_RANGE_SYNC_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afc_range_sync:  7;      /*!<［｜<in-house>*TODO*英訳｜DSSS AFCレンジ設定(同期時) R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_AFC_RANGE_SYNC_T;

/** @brief ［Type definition for @ref RADIO_SS_AFC_RANGE_ADR access｜@ref RADIO_SS_AFC_RANGE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afc_range:       7;      /*!<［｜<in-house>*TODO*英訳｜DSSS AFCレンジ設定(データ受信時) R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_AFC_RANGE_T;

/** @brief ［Type definition for @ref RADIO_DSSS_RATE_SYNC_H_ADR access｜@ref RADIO_DSSS_RATE_SYNC_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_rate_sync_h:   4;      /*!<［｜<in-house>*TODO*英訳｜DSSS同期時受信チップレート設定(上位4ビット) R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_RATE_SYNC_H_T;

/** @brief ［Type definition for @ref RADIO_DSSS_RATE_SYNC_L_ADR access｜@ref RADIO_DSSS_RATE_SYNC_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_rate_sync_l:   8;      /*!<［｜<in-house>*TODO*英訳｜DSSS同期時受信チップレート設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_RATE_SYNC_L_T;

/** @brief ［Type definition for @ref RADIO_DSSS_RATE_H_ADR access｜@ref RADIO_DSSS_RATE_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_rate_h:        4;      /*!<［｜<in-house>*TODO*英訳｜DSSSデータ受信時受信チップレート設定(上位4ビット) R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_RATE_H_T;

/** @brief ［Type definition for @ref RADIO_DSSS_RATE_L_ADR access｜@ref RADIO_DSSS_RATE_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_rate_l:        8;      /*!<［｜<in-house>*TODO*英訳｜DSSSデータ受信時受信チップレート設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_RATE_L_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT8_GATE_H_ADR access｜@ref RADIO_SS_SYNC_BIT8_GATE_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit8_gate_h:3;      /*!<［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定(上位3ビット) R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT8_GATE_H_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT8_GATE_L_ADR access｜@ref RADIO_SS_SYNC_BIT8_GATE_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit8_gate_l:8;      /*!<［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT8_GATE_L_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT8_GATE2_H_ADR access｜@ref RADIO_SS_SYNC_BIT8_GATE2_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit8_gate2_h:   3;  /*!<［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定2(上位3ビット) R/W］*/
        uint8_t reserved0:              5;  /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT8_GATE2_H_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT8_GATE2_L_ADR access｜@ref RADIO_SS_SYNC_BIT8_GATE2_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit8_gate2_l:   8;  /*!<［｜<in-house>*TODO*英訳｜DSSS同期確立時相関閾値設定2(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT8_GATE2_L_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT_GATE_H_ADR access｜@ref RADIO_SS_SYNC_BIT_GATE_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit_gate_h:     3;  /*!<［｜<in-house>*TODO*英訳｜DSSS同期確立後相関閾値設定(上位3ビット) R/W］*/
        uint8_t reserved0:              5;  /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT_GATE_H_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT_GATE_L_ADR access｜@ref RADIO_SS_SYNC_BIT_GATE_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit_gate_l:     8;  /*!<［｜<in-house>*TODO*英訳｜DSSS同期確立後相関閾値設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT_GATE_L_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT4_GATE_H_ADR access｜@ref RADIO_SS_SYNC_BIT4_GATE_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit4_gate:  3;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT4_GATE_H_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_BIT4_GATE_L_ADR access｜@ref RADIO_SS_SYNC_BIT4_GATE_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_bit4_gate:  8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_BIT4_GATE_L_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_LOST_GATE_ADR access｜@ref RADIO_SS_SYNC_LOST_GATE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_lost_gate:  5;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_LOST_GATE_T;

/** @brief ［Type definition for @ref RADIO_SS_BIT8_MAX_ACC_H_ADR access｜@ref RADIO_SS_BIT8_MAX_ACC_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_bit8_max_acc:    4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_BIT8_MAX_ACC_H_T;

/** @brief ［Type definition for @ref RADIO_SS_BIT8_MAX_ACC_L_ADR access｜@ref RADIO_SS_BIT8_MAX_ACC_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_bit8_max_acc:    8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_BIT8_MAX_ACC_L_T;

/** @brief ［Type definition for @ref RADIO_SS_SYNC_GATE2_PLUS_ADR access｜@ref RADIO_SS_SYNC_GATE2_PLUS_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_sync_gate2_plus: 8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SS_SYNC_GATE2_PLUS_T;

/** @brief ［Type definition for @ref RADIO_AGC_AVE_OFST_SYNC_ADR access｜@ref RADIO_AGC_AVE_OFST_SYNC_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_ave_ofst_sync:  7;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_AGC_AVE_OFST_SYNC_T;

/** @brief ［Type definition for @ref RADIO_AGC_AVE_OFST_ADR access｜@ref RADIO_AGC_AVE_OFST_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_ave_ofst_:      8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_AGC_AVE_OFST_T;

/** @brief ［Type definition for @ref RADIO_AGC_IIR_SET0_ADR access｜@ref RADIO_AGC_IIR_SET0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_iir_wgt_f:      3;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t agc_iir_wgt_m:      3;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_AGC_IIR_SET0_T;

/** @brief ［Type definition for @ref RADIO_AGC_IIR_SET1_ADR access｜@ref RADIO_AGC_IIR_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_iir_wgt_s:      3;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t agc_ave_fix:        1;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t afcx_len_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_AGC_IIR_SET1_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET1_ADR access｜@ref RADIO_DSSS_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_bit8_synch_cnt:  4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t ss_bit8_chk_len:    4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET1_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET2_ADR access｜@ref RADIO_DSSS_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_corr_mode:       8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET2_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET3_ADR access｜@ref RADIO_DSSS_SET3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bit8_sp_cnt_max:    4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET3_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET4_ADR access｜@ref RADIO_DSSS_SET4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_pb_ref_sel:      5;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET4_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET5_ADR access｜@ref RADIO_DSSS_SET5_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_corr_mode2:      8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET5_T;

/** @brief ［Type definition for @ref RADIO_SS_AFC_OUT_ADR access｜@ref RADIO_SS_AFC_OUT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afc_out:         8;      /*!<［｜<in-house>*TODO*英訳｜DSSS AFC値表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_AFC_OUT_T;

/** @brief ［Type definition for @ref RADIO_SS_AFC_FIX_EN_ADR access｜@ref RADIO_SS_AFC_FIX_EN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afc_fix_en:      1;      /*!<［｜<in-house>*TODO*英訳｜DSSS AFC固定イネーブル R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SS_AFC_FIX_EN_T;

/** @brief ［Type definition for @ref RADIO_SS_AFC_FIX_ADR access｜@ref RADIO_SS_AFC_FIX_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afc_fix:         8;      /*!<［｜<in-house>*TODO*英訳｜DSSS AFC固定設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SS_AFC_FIX_T;

/** @brief ［Type definition for @ref RADIO_DSSS_MON_SEL_ADR access｜@ref RADIO_DSSS_MON_SEL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dsss_mon_sel2:      8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_MON_SEL_T;

/** @brief ［Type definition for @ref RADIO_BIT8_SPDET_TH_H_ADR access｜@ref RADIO_BIT8_SPDET_TH_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bit8_spdet_th:      3;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_BIT8_SPDET_TH_H_T;

/** @brief ［Type definition for @ref RADIO_BIT8_SPDET_TH_L_ADR access｜@ref RADIO_BIT8_SPDET_TH_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bit8_spdet_th:      8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BIT8_SPDET_TH_L_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET6_ADR access｜@ref RADIO_DSSS_SET6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afcx2_len_h:     4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t ss_afcx6_len_h:     4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET6_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET7_ADR access｜@ref RADIO_DSSS_SET7_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ss_afcx2_len_l:     4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t ss_afcx6_len_l:     4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET7_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET8_ADR access｜@ref RADIO_DSSS_SET8_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_ave_th_h:       8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET8_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET9_ADR access｜@ref RADIO_DSSS_SET9_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_ave_th_l:       8;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET9_T;

/** @brief ［Type definition for @ref RADIO_DSSS_SET10_ADR access｜@ref RADIO_DSSS_SET10_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t SS_CORR_MODE3:      4;      /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜*予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DSSS_SET10_T;

/** \} */ /* End of group RF_REGISTER_BANK7 */

#endif
