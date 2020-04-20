/****************************************************************************************/
/**
   @file     bank1.h

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
#ifndef _bank1_H
#define _bank1_H

/**
    \addtogroup RF_REGISTER_BANK1
    \{
 */
 
/*［BANK1 Register Address Definitions｜BANK1レジスタアドレス定義］*/
#define RADIO_CLK_OUT_ADR               (0x01u)      /*!< ［｜<in-house>*TODO*英訳｜CLK_OUT(GPIOn)(@ref RADIO_CLK_OUT_T 型でアクセス)］ */
#define RADIO_TX_RATE_H_ADR             (0x02u)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート変換設定(上位バイト)(@ref RADIO_TX_RATE_H_T 型でアクセス)］ */
#define RADIO_TX_RATE_L_ADR             (0x03u)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート変換設定(下位バイト)(@ref RADIO_TX_RATE_L_T 型でアクセス)］ */
#define RADIO_RX_RATE1_H_ADR            (0x04u)      /*!< ［｜<in-house>*TODO*英訳｜受信データレート変換設定1(上位バイト)(@ref RADIO_RX_RATE1_H_T 型でアクセス)］ */
#define RADIO_RX_RATE1_L_ADR            (0x05u)      /*!< ［｜<in-house>*TODO*英訳｜受信データレート変換設定1(下位バイト)(@ref RADIO_RX_RATE1_L_T 型でアクセス)］ */
#define RADIO_RX_RATE2_ADR              (0x06u)      /*!< ［｜<in-house>*TODO*英訳｜受信データレート変換設定2(@ref RADIO_RX_RATE2_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR07        (0x07u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_OSC_W_SEL_ADR             (0x08u)      /*!< ［｜<in-house>*TODO*英訳｜クロック安定化待ち時間設定(@ref RADIO_OSC_W_SEL_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR09        (0x09u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR0A        (0x0Au)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_PLL_LOCK_DETECT_ADR       (0x0Bu)      /*!< ［｜<in-house>*TODO*英訳｜PLLロック判定設定(@ref RADIO_PLL_LOCK_DETECT_T 型でアクセス)］ */
#define RADIO_GAIN_HTOL_ADR             (0x0Cu)      /*!< ［｜<in-house>*TODO*英訳｜高ゲインから低ゲインへの切り替え閾値設定(@ref RADIO_GAIN_HTOL_T 型でアクセス)］ */
#define RADIO_GAIN_LTOH_ADR             (0x0Du)      /*!< ［｜<in-house>*TODO*英訳｜低ゲインから高ゲインへの切り替え閾値設定(@ref RADIO_GAIN_LTOH_T 型でアクセス)］ */
#define RADIO_GAIN_HOLD_ADR             (0x0Eu)      /*!< ［｜<in-house>*TODO*英訳｜ゲイン切り替え設定(@ref RADIO_GAIN_HOLD_T 型でアクセス)］ */
#define RADIO_RSSI_STABLE_RES_ADR       (0x0Fu)      /*!< ［｜<in-house>*TODO*英訳｜RSSI安定化待ち時間分解能設定(@ref RADIO_RSSI_STABLE_RES_T 型でアクセス)］ */
#define RADIO_GC_CTRL_DIV_ADR           (0x10u)      /*!< ［｜<in-house>*TODO*英訳｜ダイバーシティ時のゲイン制御設定(@ref RADIO_GC_CTRL_DIV_T 型でアクセス)］ */
#define RADIO_RSSI_ADJ_L_ADR            (0x11u)      /*!< ［｜<in-house>*TODO*英訳｜低ゲイン動作時のRSSIオフセット値設定(@ref RADIO_RSSI_ADJ_L_T 型でアクセス)］ */
#define RADIO_RSSI_STABLE_TIME_ADR      (0x12u)      /*!< ［｜<in-house>*TODO*英訳｜RSSI安定化待ち時間設定(@ref RADIO_RSSI_STABLE_TIME_T 型でアクセス)］ */
#define RADIO_RSSI_MAG_ADJ_ADR          (0x13u)      /*!< ［｜<in-house>*TODO*英訳｜ED変換用RSSI補正設定(@ref RADIO_RSSI_MAG_ADJ_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR14        (0x14u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_AFC_GC_CTRL_ADR           (0x15u)      /*!< ［｜<in-house>*TODO*英訳｜AFC/ゲイン制御設定(@ref RADIO_AFC_GC_CTRL_T 型でアクセス)］ */
#define RADIO_CRC_POLY3_ADR             (0x16u)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式3(@ref RADIO_CRC_POLY3_T 型でアクセス)］ */
#define RADIO_CRC_POLY2_ADR             (0x17u)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式2(@ref RADIO_CRC_POLY2_T 型でアクセス)］ */
#define RADIO_CRC_POLY1_ADR             (0x18u)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式1(@ref RADIO_CRC_POLY1_T 型でアクセス)］ */
#define RADIO_CRC_POLY0_ADR             (0x19u)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式0(@ref RADIO_CRC_POLY0_T 型でアクセス)］ */
#define RADIO_PLL_DIV_SET_ADR           (0x1Au)      /*!< ［｜<in-house>*TODO*英訳｜PLL出力2分周切り替え設定(@ref RADIO_PLL_DIV_SET_T 型でアクセス)］ */
#define RADIO_TXFREQ_I_ADR              (0x1Bu)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Iカウンタ設定(@ref RADIO_TXFREQ_I_T 型でアクセス)］ */
#define RADIO_TXFREQ_FH_ADR             (0x1Cu)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Fカウンタ設定(上位4ビット)(@ref RADIO_TXFREQ_FH_T 型でアクセス)］ */
#define RADIO_TXFREQ_FM_ADR             (0x1Du)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Fカウンタ設定(中位8ビット)(@ref RADIO_TXFREQ_FM_T 型でアクセス)］ */
#define RADIO_TXFREQ_FL_ADR             (0x1Eu)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Fカウンタ設定(下位8ビット)(@ref RADIO_TXFREQ_FL_T 型でアクセス)］ */
#define RADIO_RXFREQ_I_ADR              (0x1Fu)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Iカウンタ設定(@ref RADIO_RXFREQ_I_T 型でアクセス)］ */
#define RADIO_RXFREQ_FH_ADR             (0x20u)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Fカウンタ設定(上位4ビット)(@ref RADIO_RXFREQ_FH_T 型でアクセス)］ */
#define RADIO_RXFREQ_FM_ADR             (0x21u)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Fカウンタ設定(中位8ビット)(@ref RADIO_RXFREQ_FM_T 型でアクセス)］ */
#define RADIO_RXFREQ_FL_ADR             (0x22u)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Fカウンタ設定(下位8ビット)(@ref RADIO_RXFREQ_FL_T 型でアクセス)］ */
#define RADIO_CH_SPACE_H_ADR            (0x23u)      /*!< ［｜<in-house>*TODO*英訳｜チャネル間隔設定(上位バイト)(@ref RADIO_CH_SPACE_H_T 型でアクセス)］ */
#define RADIO_CH_SPACE_L_ADR            (0x24u)      /*!< ［｜<in-house>*TODO*英訳｜チャネル間隔設定(下位バイト)(@ref RADIO_CH_SPACE_L_T 型でアクセス)］ */
#define RADIO_SYNC_WORD_LEN_ADR         (0x25u)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD長設定(@ref RADIO_SYNC_WORD_LEN_T 型でアクセス)］ */
#define RADIO_SYNC_WORD_EN_ADR          (0x26u)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORDイネーブル設定(@ref RADIO_SYNC_WORD_EN_T 型でアクセス)］ */
#define RADIO_SYNCWORD1_SET0_ADR        (0x27u)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定1(@ref RADIO_SYNCWORD1_SET0_T 型でアクセス)］ */
#define RADIO_SYNCWORD1_SET1_ADR        (0x28u)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定2(@ref RADIO_SYNCWORD1_SET1_T 型でアクセス)］ */
#define RADIO_SYNCWORD1_SET2_ADR        (0x29u)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定3(@ref RADIO_SYNCWORD1_SET2_T 型でアクセス)］ */
#define RADIO_SYNCWORD1_SET3_ADR        (0x2Au)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定4(@ref RADIO_SYNCWORD1_SET3_T 型でアクセス)］ */
#define RADIO_SYNCWORD2_SET0_ADR        (0x2Bu)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定1(@ref RADIO_SYNCWORD2_SET0_T 型でアクセス)］ */
#define RADIO_SYNCWORD2_SET1_ADR        (0x2Cu)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定2(@ref RADIO_SYNCWORD2_SET1_T 型でアクセス)］ */
#define RADIO_SYNCWORD2_SET2_ADR        (0x2Du)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定3(@ref RADIO_SYNCWORD2_SET2_T 型でアクセス)］ */
#define RADIO_SYNCWORD2_SET3_ADR        (0x2Eu)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定4(@ref RADIO_SYNCWORD2_SET3_T 型でアクセス)］ */
#define RADIO_FSK_CTRL_ADR              (0x2Fu)      /*!< ［｜<in-house>*TODO*英訳｜GFSK/FSK変調タイミング分解能設定(@ref RADIO_FSK_CTRL_T 型でアクセス)］ */
#define RADIO_GFSK_DEV_H_ADR            (0x30u)      /*!< ［｜<in-house>*TODO*英訳｜GFSK時周波数偏位設定(上位6ビット)(@ref RADIO_GFSK_DEV_H_T 型でアクセス)］ */
#define RADIO_GFSK_DEV_L_ADR            (0x31u)      /*!< ［｜<in-house>*TODO*英訳｜GFSK時周波数偏位設定(下位バイト)(@ref RADIO_GFSK_DEV_L_T 型でアクセス)］ */
#define RADIO_FSK_DEV0_H_GFIL0_ADR      (0x32u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定0/ガウシアンフィルタ係数設定1(@ref RADIO_FSK_DEV0_H_GFIL0_T 型でアクセス)］ */
#define RADIO_FSK_DEV0_L_GFIL1_ADR      (0x33u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定0/ガウシアンフィルタ係数設定2(@ref RADIO_FSK_DEV0_L_GFIL1_T 型でアクセス)］ */
#define RADIO_FSK_DEV1_H_GFIL2_ADR      (0x34u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定1/ガウシアンフィルタ係数設定3(@ref RADIO_FSK_DEV1_H_GFIL2_T 型でアクセス)］ */
#define RADIO_FSK_DEV1_L_GFIL3_ADR      (0x35u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定1/ガウシアンフィルタ係数設定4(@ref RADIO_FSK_DEV1_L_GFIL3_T 型でアクセス)］ */
#define RADIO_FSK_DEV2_H_GFIL4_ADR      (0x36u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定2/ガウシアンフィルタ係数設定5(@ref RADIO_FSK_DEV2_H_GFIL4_T 型でアクセス)］ */
#define RADIO_FSK_DEV2_L_GFIL5_ADR      (0x37u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定2/ガウシアンフィルタ係数設定6(@ref RADIO_FSK_DEV2_L_GFIL5_T 型でアクセス)］ */
#define RADIO_FSK_DEV3_H_GFIL6_ADR      (0x38u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定3/ガウシアンフィルタ係数設定7(@ref RADIO_FSK_DEV3_H_GFIL6_T 型でアクセス)］ */
#define RADIO_FSK_DEV3_L_ADR            (0x39u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定3(@ref RADIO_FSK_DEV3_L_T 型でアクセス)］ */
#define RADIO_FSK_DEV4_H_ADR            (0x3Au)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定4(@ref RADIO_FSK_DEV4_H_T 型でアクセス)］ */
#define RADIO_FSK_DEV4_L_ADR            (0x3Bu)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定4(@ref RADIO_FSK_DEV4_L_T 型でアクセス)］ */
#define RADIO_FSK_TIM_ADJ4_ADR          (0x3Cu)      /*!< ［｜<in-house>*TODO*英訳｜FSK第4周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ4_T 型でアクセス)］ */
#define RADIO_FSK_TIM_ADJ3_ADR          (0x3Du)      /*!< ［｜<in-house>*TODO*英訳｜FSK第3周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ3_T 型でアクセス)］ */
#define RADIO_FSK_TIM_ADJ2_ADR          (0x3Eu)      /*!< ［｜<in-house>*TODO*英訳｜FSK第2周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ2_T 型でアクセス)］ */
#define RADIO_FSK_TIM_ADJ1_ADR          (0x3Fu)      /*!< ［｜<in-house>*TODO*英訳｜FSK第1周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ1_T 型でアクセス)］ */
#define RADIO_FSK_TIM_ADJ0_ADR          (0x40u)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数無偏位（キャリア周波数）の保持時間設定(@ref RADIO_FSK_TIM_ADJ0_T 型でアクセス)］ */
#define RADIO_4FSK_DATA_MAP_ADR         (0x41u)      /*!< ［｜<in-house>*TODO*英訳｜4FSK時のデータマッピング(@ref RADIO_4FSK_DATA_MAP_T 型でアクセス)］ */
#define RADIO_FREQ_ADJ_H_ADR            (0x42u)      /*!< ［｜<in-house>*TODO*英訳｜送受信周波数微調整設定（上位バイト）(@ref RADIO_FREQ_ADJ_H_T 型でアクセス)］ */
#define RADIO_FREQ_ADJ_L_ADR            (0x43u)      /*!< ［｜<in-house>*TODO*英訳｜送受信周波数微調整設定（下位バイト）(@ref RADIO_FREQ_ADJ_L_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR44        (0x44u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR45        (0x45u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR46        (0x46u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR47        (0x47u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_2DIV_MODE_ADR             (0x48u)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティモード設定(@ref RADIO_2DIV_MODE_T 型でアクセス)］ */
#define RADIO_2DIV_SEARCH1_ADR          (0x49u)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティサーチ時間設定(@ref RADIO_2DIV_SEARCH1_T 型でアクセス)］ */
#define RADIO_2DIV_SEARCH2_ADR          (0x4Au)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティサーチ時間設定(@ref RADIO_2DIV_SEARCH2_T 型でアクセス)］ */
#define RADIO_2DIV_FAST_LVL_ADR         (0x4Bu)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティFASTモードのED閾値設定(@ref RADIO_2DIV_FAST_LVL_T 型でアクセス)］ */
#define RADIO_2DIV_PB_TH_ADR            (0x4Cu)      /*!< ［｜<in-house>*TODO*英訳｜(@ref RADIO_2DIV_PB_TH_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_I_ADR         (0x4Du)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Iカウンタ設定(@ref RADIO_VCO_CAL_MIN_I_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_FH_ADR        (0x4Eu)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Fカウンタ設定(上位6ビット)(@ref RADIO_VCO_CAL_MIN_FH_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_FM_ADR        (0x4Fu)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Fカウンタ設定(中位8ビット)(@ref RADIO_VCO_CAL_MIN_FM_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MIN_FL_ADR        (0x50u)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Fカウンタ設定(下位8ビット)(@ref RADIO_VCO_CAL_MIN_FL_T 型でアクセス)］ */
#define RADIO_VCO_CAL_MAX_N_ADR         (0x51u)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL_Max周波数設定(@ref RADIO_VCO_CAL_MAX_N_T 型でアクセス)］ */
#define RADIO_FVCAL_MIN_ADR             (0x52u)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション下限値(@ref RADIO_FVCAL_MIN_T 型でアクセス)］ */
#define RADIO_FVCAL_MAX_ADR             (0x53u)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション上限値(@ref RADIO_FVCAL_MAX_T 型でアクセス)］ */
#define RADIO_VCO_ACAL_ADR              (0x54u)      /*!< ［｜<in-house>*TODO*英訳｜VCO振幅キャリブレーション値表示と設定(@ref RADIO_VCO_ACAL_T 型でアクセス)］ */
#define RADIO_VCO_ACAL_WR_EN_ADR        (0x55u)      /*!< ［｜<in-house>*TODO*英訳｜VCO振幅キャリブレーション上書き設定(@ref RADIO_VCO_ACAL_WR_EN_T 型でアクセス)］ */
#define RADIO_DEMOD_SET0_ADR            (0x56u)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定0(@ref RADIO_DEMOD_SET0_T 型でアクセス)］ */
#define RADIO_DEMOD_SET1_ADR            (0x57u)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定1(@ref RADIO_DEMOD_SET1_T 型でアクセス)］ */
#define RADIO_DEMOD_SET2_ADR            (0x58u)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定2(@ref RADIO_DEMOD_SET2_T 型でアクセス)］ */
#define RADIO_DEMOD_SET3_ADR            (0x59u)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定3(@ref RADIO_DEMOD_SET3_T 型でアクセス)］ */
#define RADIO_RX_IQ_SEL_ADR             (0x5Au)      /*!< ［｜<in-house>*TODO*英訳｜受信時IQ選択設定(@ref RADIO_RX_IQ_SEL_T 型でアクセス) ］ */
#define RADIO_DEMOD_SET5_ADR            (0x5Bu)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_DEMOD_SET6_ADR            (0x5Cu)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定6(@ref RADIO_DEMOD_SET6_T 型でアクセス)］ */
#define RADIO_DEMOD_SET7_ADR            (0x5Du)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定7(@ref RADIO_DEMOD_SET7_T 型でアクセス)］ */
#define RADIO_DEMOD_SET8_ADR            (0x5Eu)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定8(@ref RADIO_DEMOD_SET8_T 型でアクセス)］ */
#define RADIO_DEMOD_SET9_ADR            (0x5Fu)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定9(@ref RADIO_DEMOD_SET9_T 型でアクセス)］ */
#define RADIO_DEMOD_SET10_ADR           (0x60u)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定10(@ref RADIO_DEMOD_SET10_T 型でアクセス)］ */
#define RADIO_DEMOD_SET11_ADR           (0x61u)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定11(@ref RADIO_DEMOD_SET11_T 型でアクセス)］ */
#define RADIO_ADDR_CHK_CTR_H_ADR        (0x62u)      /*!< ［｜<in-house>*TODO*英訳｜アドレスチェックカウンタ表示(上位3ビット)(@ref RADIO_ADDR_CHK_CTR_H_T 型でアクセス)］ */
#define RADIO_ADDR_CHK_CTR_L_ADR        (0x63u)      /*!< ［｜<in-house>*TODO*英訳｜アドレスチェックカウンタ表示(下位バイト)(@ref RADIO_ADDR_CHK_CTR_L_T 型でアクセス)］ */
#define RADIO_WHT_INIT_H_ADR            (0x64u)      /*!< ［｜<in-house>*TODO*英訳｜Whitening初期状態設定(上位1ビット)(@ref RADIO_WHT_INIT_H_T 型でアクセス)］ */
#define RADIO_WHT_INIT_L_ADR            (0x65u)      /*!< ［｜<in-house>*TODO*英訳｜Whitening初期状態設定(下位8ビット)(@ref RADIO_WHT_INIT_L_T 型でアクセス)］ */
#define RADIO_WHT_CFG_ADR               (0x66u)      /*!< ［｜<in-house>*TODO*英訳｜Whitening生成多項式設定(@ref RADIO_WHT_CFG_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR67        (0x67u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR68        (0x68u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR69        (0x69u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR6A        (0x6Au)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR6B        (0x6Bu)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR6C        (0x6Cu)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_GPIO5_CTRL_ADR            (0x6Du)      /*!< ［｜<in-house>*TODO*英訳｜GPIO5端子制御(@ref RADIO_GPIO5_CTRL_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR6E        (0x6Eu)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR6F        (0x6Fu)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_DCDC_CTRL_ADR             (0x70u)      /*!< ［｜<in-house>*TODO*英訳｜DCDCコンバータ制御(@ref RADIO_DCDC_CTRL_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR71        (0x71u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR72        (0x72u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR73        (0x73u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_VCO_FCAL_MIN_2P4G_ADR     (0x74u)      /*!< ［｜<in-house>*TODO*英訳｜下限側VCO周波数キャリブレーション値表示と設定(2.4GHz TX用)(@ref RADIO_VCO_FCAL_MIN_2P4G_T 型でアクセス)］ */
#define RADIO_VCO_FCAL_MAX_2P4G_ADR     (0x75u)      /*!< ［｜<in-house>*TODO*英訳｜上限側VCO周波数キャリブレーション値表示と設定(2.4GHz TX用)(@ref RADIO_VCO_FCAL_MAX_2P4G_T 型でアクセス)］ */
#define RADIO_VCO_FCAL_MIN_2P4G_RX_ADR  (0x76u)      /*!< ［｜<in-house>*TODO*英訳｜下限側VCO周波数キャリブレーション値表示と設定(2.4GHz RX用)(@ref RADIO_VCO_FCAL_MIN_2P4G_T 型でアクセス)］ */
#define RADIO_VCO_FCAL_MAX_2P4G_RX_ADR  (0x77u)      /*!< ［｜<in-house>*TODO*英訳｜上限側VCO周波数キャリブレーション値表示と設定(2.4GHz RX用)(@ref RADIO_VCO_FCAL_MAX_2P4G_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR78        (0x78u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR79        (0x79u)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_NONPUBLIC_B1_ADR7A        (0x7Au)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_TX_RATE2_EN_ADR           (0x7Bu)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート設定イネーブル(@ref RADIO_TX_RATE2_EN_T 型でアクセス)］ */
#define RADIO_TX_RATE2_H_ADR            (0x7Cu)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート設定2（上位バイト）(@ref RADIO_TX_RATE2_H_T 型でアクセス)］ */
#define RADIO_TX_RATE2_L_ADR            (0x7Du)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート設定2（下位バイト）(@ref RADIO_TX_RATE2_L_T 型でアクセス)］ */
#define RADIO_NONPUBLIC_B1_ADR7E        (0x7Eu)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define RADIO_ID_CODE_ADR               (0x7Fu)      /*!< ［｜<in-house>*TODO*英訳｜IDコード表示(@ref RADIO_ID_CODE_T 型でアクセス)］ */

#define BANK_CLK_OUT_ADR               (1)      /*!< ［｜<in-house>*TODO*英訳｜CLK_OUT(GPIOn)(@ref RADIO_CLK_OUT_T 型でアクセス)］ */
#define BANK_TX_RATE_H_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート変換設定(上位バイト)(@ref RADIO_TX_RATE_H_T 型でアクセス)］ */
#define BANK_TX_RATE_L_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート変換設定(下位バイト)(@ref RADIO_TX_RATE_L_T 型でアクセス)］ */
#define BANK_RX_RATE1_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜受信データレート変換設定1(上位バイト)(@ref RADIO_RX_RATE1_H_T 型でアクセス)］ */
#define BANK_RX_RATE1_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜受信データレート変換設定1(下位バイト)(@ref RADIO_RX_RATE1_L_T 型でアクセス)］ */
#define BANK_RX_RATE2_ADR              (1)      /*!< ［｜<in-house>*TODO*英訳｜受信データレート変換設定2(@ref RADIO_RX_RATE2_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR07        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_OSC_W_SEL_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜クロック安定化待ち時間設定(@ref RADIO_OSC_W_SEL_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR09        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR0A        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_PLL_LOCK_DETECT_ADR       (1)      /*!< ［｜<in-house>*TODO*英訳｜PLLロック判定設定(@ref RADIO_PLL_LOCK_DETECT_T 型でアクセス)］ */
#define BANK_GAIN_HTOL_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜高ゲインから低ゲインへの切り替え閾値設定(@ref RADIO_GAIN_HTOL_T 型でアクセス)］ */
#define BANK_GAIN_LTOH_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜低ゲインから高ゲインへの切り替え閾値設定(@ref RADIO_GAIN_LTOH_T 型でアクセス)］ */
#define BANK_GAIN_HOLD_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜ゲイン切り替え設定(@ref RADIO_GAIN_HOLD_T 型でアクセス)］ */
#define BANK_RSSI_STABLE_RES_ADR       (1)      /*!< ［｜<in-house>*TODO*英訳｜RSSI安定化待ち時間分解能設定(@ref RADIO_RSSI_STABLE_RES_T 型でアクセス)］ */
#define BANK_GC_CTRL_DIV_ADR           (1)      /*!< ［｜<in-house>*TODO*英訳｜ダイバーシティ時のゲイン制御設定(@ref RADIO_GC_CTRL_DIV_T 型でアクセス)］ */
#define BANK_RSSI_ADJ_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜低ゲイン動作時のRSSIオフセット値設定(@ref RADIO_RSSI_ADJ_L_T 型でアクセス)］ */
#define BANK_RSSI_STABLE_TIME_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜RSSI安定化待ち時間設定(@ref RADIO_RSSI_STABLE_TIME_T 型でアクセス)］ */
#define BANK_RSSI_MAG_ADJ_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜ED変換用RSSI補正設定(@ref RADIO_RSSI_MAG_ADJ_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR14        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_AFC_GC_CTRL_ADR           (1)      /*!< ［｜<in-house>*TODO*英訳｜AFC/ゲイン制御設定(@ref RADIO_AFC_GC_CTRL_T 型でアクセス)］ */
#define BANK_CRC_POLY3_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式3(@ref RADIO_CRC_POLY3_T 型でアクセス)］ */
#define BANK_CRC_POLY2_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式2(@ref RADIO_CRC_POLY2_T 型でアクセス)］ */
#define BANK_CRC_POLY1_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式1(@ref RADIO_CRC_POLY1_T 型でアクセス)］ */
#define BANK_CRC_POLY0_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜CRC生成多項式0(@ref RADIO_CRC_POLY0_T 型でアクセス)］ */
#define BANK_PLL_DIV_SET_ADR           (1)      /*!< ［｜<in-house>*TODO*英訳｜PLL出力2分周切り替え設定(@ref RADIO_PLL_DIV_SET_T 型でアクセス)］ */
#define BANK_TXFREQ_I_ADR              (1)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Iカウンタ設定(@ref RADIO_TXFREQ_I_T 型でアクセス)］ */
#define BANK_TXFREQ_FH_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Fカウンタ設定(上位4ビット)(@ref RADIO_TXFREQ_FH_T 型でアクセス)］ */
#define BANK_TXFREQ_FM_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Fカウンタ設定(中位8ビット)(@ref RADIO_TXFREQ_FM_T 型でアクセス)］ */
#define BANK_TXFREQ_FL_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜送信周波数Fカウンタ設定(下位8ビット)(@ref RADIO_TXFREQ_FL_T 型でアクセス)］ */
#define BANK_RXFREQ_I_ADR              (1)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Iカウンタ設定(@ref RADIO_RXFREQ_I_T 型でアクセス)］ */
#define BANK_RXFREQ_FH_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Fカウンタ設定(上位4ビット)(@ref RADIO_RXFREQ_FH_T 型でアクセス)］ */
#define BANK_RXFREQ_FM_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Fカウンタ設定(中位8ビット)(@ref RADIO_RXFREQ_FM_T 型でアクセス)］ */
#define BANK_RXFREQ_FL_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜受信周波数Fカウンタ設定(下位8ビット)(@ref RADIO_RXFREQ_FL_T 型でアクセス)］ */
#define BANK_CH_SPACE_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜チャネル間隔設定(上位バイト)(@ref RADIO_CH_SPACE_H_T 型でアクセス)］ */
#define BANK_CH_SPACE_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜チャネル間隔設定(下位バイト)(@ref RADIO_CH_SPACE_L_T 型でアクセス)］ */
#define BANK_SYNC_WORD_LEN_ADR         (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD長設定(@ref RADIO_SYNC_WORD_LEN_T 型でアクセス)］ */
#define BANK_SYNC_WORD_EN_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORDイネーブル設定(@ref RADIO_SYNC_WORD_EN_T 型でアクセス)］ */
#define BANK_SYNCWORD1_SET0_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定1(@ref RADIO_SYNCWORD1_SET0_T 型でアクセス)］ */
#define BANK_SYNCWORD1_SET1_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定2(@ref RADIO_SYNCWORD1_SET1_T 型でアクセス)］ */
#define BANK_SYNCWORD1_SET2_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定3(@ref RADIO_SYNCWORD1_SET2_T 型でアクセス)］ */
#define BANK_SYNCWORD1_SET3_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD1設定4(@ref RADIO_SYNCWORD1_SET3_T 型でアクセス)］ */
#define BANK_SYNCWORD2_SET0_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定1(@ref RADIO_SYNCWORD2_SET0_T 型でアクセス)］ */
#define BANK_SYNCWORD2_SET1_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定2(@ref RADIO_SYNCWORD2_SET1_T 型でアクセス)］ */
#define BANK_SYNCWORD2_SET2_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定3(@ref RADIO_SYNCWORD2_SET2_T 型でアクセス)］ */
#define BANK_SYNCWORD2_SET3_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜SYNC_WORD2設定4(@ref RADIO_SYNCWORD2_SET3_T 型でアクセス)］ */
#define BANK_FSK_CTRL_ADR              (1)      /*!< ［｜<in-house>*TODO*英訳｜GFSK/FSK変調タイミング分解能設定(@ref RADIO_FSK_CTRL_T 型でアクセス)］ */
#define BANK_GFSK_DEV_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜GFSK時周波数偏位設定(上位6ビット)(@ref RADIO_GFSK_DEV_H_T 型でアクセス)］ */
#define BANK_GFSK_DEV_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜GFSK時周波数偏位設定(下位バイト)(@ref RADIO_GFSK_DEV_L_T 型でアクセス)］ */
#define BANK_FSK_DEV0_H_GFIL0_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定0/ガウシアンフィルタ係数設定1(@ref RADIO_FSK_DEV0_H_GFIL0_T 型でアクセス)］ */
#define BANK_FSK_DEV0_L_GFIL1_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定0/ガウシアンフィルタ係数設定2(@ref RADIO_FSK_DEV0_L_GFIL1_T 型でアクセス)］ */
#define BANK_FSK_DEV1_H_GFIL2_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定1/ガウシアンフィルタ係数設定3(@ref RADIO_FSK_DEV1_H_GFIL2_T 型でアクセス)］ */
#define BANK_FSK_DEV1_L_GFIL3_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定1/ガウシアンフィルタ係数設定4(@ref RADIO_FSK_DEV1_L_GFIL3_T 型でアクセス)］ */
#define BANK_FSK_DEV2_H_GFIL4_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定2/ガウシアンフィルタ係数設定5(@ref RADIO_FSK_DEV2_H_GFIL4_T 型でアクセス)］ */
#define BANK_FSK_DEV2_L_GFIL5_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定2/ガウシアンフィルタ係数設定6(@ref RADIO_FSK_DEV2_L_GFIL5_T 型でアクセス)］ */
#define BANK_FSK_DEV3_H_GFIL6_ADR      (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定3/ガウシアンフィルタ係数設定7(@ref RADIO_FSK_DEV3_H_GFIL6_T 型でアクセス)］ */
#define BANK_FSK_DEV3_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定3(@ref RADIO_FSK_DEV3_L_T 型でアクセス)］ */
#define BANK_FSK_DEV4_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定4(@ref RADIO_FSK_DEV4_H_T 型でアクセス)］ */
#define BANK_FSK_DEV4_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数偏位設定4(@ref RADIO_FSK_DEV4_L_T 型でアクセス)］ */
#define BANK_FSK_TIM_ADJ4_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK第4周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ4_T 型でアクセス)］ */
#define BANK_FSK_TIM_ADJ3_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK第3周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ3_T 型でアクセス)］ */
#define BANK_FSK_TIM_ADJ2_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK第2周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ2_T 型でアクセス)］ */
#define BANK_FSK_TIM_ADJ1_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK第1周波数偏位の保持時間設定(@ref RADIO_FSK_TIM_ADJ1_T 型でアクセス)］ */
#define BANK_FSK_TIM_ADJ0_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜FSK周波数無偏位（キャリア周波数）の保持時間設定(@ref RADIO_FSK_TIM_ADJ0_T 型でアクセス)］ */
#define BANK_4FSK_DATA_MAP_ADR         (1)      /*!< ［｜<in-house>*TODO*英訳｜4FSK時のデータマッピング(@ref RADIO_4FSK_DATA_MAP_T 型でアクセス)］ */
#define BANK_FREQ_ADJ_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜送受信周波数微調整設定（上位バイト）(@ref RADIO_FREQ_ADJ_H_T 型でアクセス)］ */
#define BANK_FREQ_ADJ_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜送受信周波数微調整設定（下位バイト）(@ref RADIO_FREQ_ADJ_L_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR44        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR45        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR46        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR47        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_2DIV_MODE_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティモード設定(@ref RADIO_2DIV_MODE_T 型でアクセス)］ */
#define BANK_2DIV_SEARCH1_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティサーチ時間設定(@ref RADIO_2DIV_SEARCH1_T 型でアクセス)］ */
#define BANK_2DIV_SEARCH2_ADR          (1)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティサーチ時間設定(@ref RADIO_2DIV_SEARCH2_T 型でアクセス)］ */
#define BANK_2DIV_FAST_LVL_ADR         (1)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティFASTモードのED閾値設定(@ref RADIO_2DIV_FAST_LVL_T 型でアクセス)］ */
#define BANK_2DIV_PB_TH_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜(@ref RADIO_2DIV_PB_TH_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_I_ADR         (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Iカウンタ設定(@ref RADIO_VCO_CAL_MIN_I_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_FH_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Fカウンタ設定(上位6ビット)(@ref RADIO_VCO_CAL_MIN_FH_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_FM_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Fカウンタ設定(中位8ビット)(@ref RADIO_VCO_CAL_MIN_FM_T 型でアクセス)］ */
#define BANK_VCO_CAL_MIN_FL_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL下限周波数Fカウンタ設定(下位8ビット)(@ref RADIO_VCO_CAL_MIN_FL_T 型でアクセス)］ */
#define BANK_VCO_CAL_MAX_N_ADR         (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO_CAL_Max周波数設定(@ref RADIO_VCO_CAL_MAX_N_T 型でアクセス)］ */
#define BANK_FVCAL_MIN_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション下限値(@ref RADIO_FVCAL_MIN_T 型でアクセス)］ */
#define BANK_FVCAL_MAX_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション上限値(@ref RADIO_FVCAL_MAX_T 型でアクセス)］ */
#define BANK_VCO_ACAL_ADR              (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO振幅キャリブレーション値表示と設定(@ref RADIO_VCO_ACAL_T 型でアクセス)］ */
#define BANK_VCO_ACAL_WR_EN_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜VCO振幅キャリブレーション上書き設定(@ref RADIO_VCO_ACAL_WR_EN_T 型でアクセス)］ */
#define BANK_DEMOD_SET0_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定0(@ref RADIO_DEMOD_SET0_T 型でアクセス)］ */
#define BANK_DEMOD_SET1_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定1(@ref RADIO_DEMOD_SET1_T 型でアクセス)］ */
#define BANK_DEMOD_SET2_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定2(@ref RADIO_DEMOD_SET2_T 型でアクセス)］ */
#define BANK_DEMOD_SET3_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定3(@ref RADIO_DEMOD_SET3_T 型でアクセス)］ */
#define BANK_RX_IQ_SEL_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜受信時IQ選択設定(@ref RADIO_RX_IQ_SEL_T 型でアクセス) ］ */
#define BANK_DEMOD_SET5_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_DEMOD_SET6_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定6(@ref RADIO_DEMOD_SET6_T 型でアクセス)］ */
#define BANK_DEMOD_SET7_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定7(@ref RADIO_DEMOD_SET7_T 型でアクセス)］ */
#define BANK_DEMOD_SET8_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定8(@ref RADIO_DEMOD_SET8_T 型でアクセス)］ */
#define BANK_DEMOD_SET9_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定9(@ref RADIO_DEMOD_SET9_T 型でアクセス)］ */
#define BANK_DEMOD_SET10_ADR           (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定10(@ref RADIO_DEMOD_SET10_T 型でアクセス)］ */
#define BANK_DEMOD_SET11_ADR           (1)      /*!< ［｜<in-house>*TODO*英訳｜復調器設定11(@ref RADIO_DEMOD_SET11_T 型でアクセス)］ */
#define BANK_ADDR_CHK_CTR_H_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜アドレスチェックカウンタ表示(上位3ビット)(@ref RADIO_ADDR_CHK_CTR_H_T 型でアクセス)］ */
#define BANK_ADDR_CHK_CTR_L_ADR        (1)      /*!< ［｜<in-house>*TODO*英訳｜アドレスチェックカウンタ表示(下位バイト)(@ref RADIO_ADDR_CHK_CTR_L_T 型でアクセス)］ */
#define BANK_WHT_INIT_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜Whitening初期状態設定(上位1ビット)(@ref RADIO_WHT_INIT_H_T 型でアクセス)］ */
#define BANK_WHT_INIT_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜Whitening初期状態設定(下位8ビット)(@ref RADIO_WHT_INIT_L_T 型でアクセス)］ */
#define BANK_WHT_CFG_ADR               (1)      /*!< ［｜<in-house>*TODO*英訳｜Whitening生成多項式設定(@ref RADIO_WHT_CFG_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR67        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR68        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR69        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR6A        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR6B        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR6C        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_GPIO5_CTRL_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜GPIO5端子制御(@ref RADIO_GPIO5_CTRL_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR6E        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR6F        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_DCDC_CTRL_ADR             (1)      /*!< ［｜<in-house>*TODO*英訳｜DCDCコンバータ制御(@ref RADIO_DCDC_CTRL_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR71        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR72        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR73        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_VCO_FCAL_MIN_2P4G_ADR     (1)      /*!< ［｜<in-house>*TODO*英訳｜下限側VCO周波数キャリブレーション値表示と設定(2.4GHz TX用)(@ref RADIO_VCO_FCAL_MIN_2P4G_T 型でアクセス)］ */
#define BANK_VCO_FCAL_MAX_2P4G_ADR     (1)      /*!< ［｜<in-house>*TODO*英訳｜上限側VCO周波数キャリブレーション値表示と設定(2.4GHz TX用)(@ref RADIO_VCO_FCAL_MAX_2P4G_T 型でアクセス)］ */
#define BANK_VCO_FCAL_MIN_2P4G_RX_ADR  (1)      /*!< ［｜<in-house>*TODO*英訳｜下限側VCO周波数キャリブレーション値表示と設定(2.4GHz RX用)(@ref RADIO_VCO_FCAL_MIN_2P4G_T 型でアクセス)］ */
#define BANK_VCO_FCAL_MAX_2P4G_RX_ADR  (1)      /*!< ［｜<in-house>*TODO*英訳｜上限側VCO周波数キャリブレーション値表示と設定(2.4GHz RX用)(@ref RADIO_VCO_FCAL_MAX_2P4G_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR78        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR79        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_NONPUBLIC_B1_ADR7A        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_TX_RATE2_EN_ADR           (1)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート設定イネーブル(@ref RADIO_TX_RATE2_EN_T 型でアクセス)］ */
#define BANK_TX_RATE2_H_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート設定2（上位バイト）(@ref RADIO_TX_RATE2_H_T 型でアクセス)］ */
#define BANK_TX_RATE2_L_ADR            (1)      /*!< ［｜<in-house>*TODO*英訳｜送信データレート設定2（下位バイト）(@ref RADIO_TX_RATE2_L_T 型でアクセス)］ */
#define BANK_NONPUBLIC_B1_ADR7E        (1)      /*!< ［｜<in-house>*TODO*英訳｜非公開］ */
#define BANK_ID_CODE_ADR               (1)      /*!< ［｜<in-house>*TODO*英訳｜IDコード表示(@ref RADIO_ID_CODE_T 型でアクセス)］ */

/* ［RF register structures｜RFレジスタ構造体］ */
/** @brief ［Type definition for @ref RADIO_CLK_OUT_ADR access｜@ref RADIO_CLK_OUT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk_div:            8;      /*!<［｜<in-house>*TODO*英訳｜出力クロック周波数設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_OUT_T;

/** @brief ［Type definition for @ref RADIO_TX_RATE_H_ADR access｜@ref RADIO_TX_RATE_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_rate_h:          8;      /*!<［｜<in-house>*TODO*英訳｜送信データレート変換設定(上位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TX_RATE_H_T;

/** @brief ［Type definition for @ref RADIO_TX_RATE_L_ADR access｜@ref RADIO_TX_RATE_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_rate_l:          8;      /*!<［｜<in-house>*TODO*英訳｜送信データレート変換設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TX_RATE_L_T;

/** @brief ［Type definition for @ref RADIO_RX_RATE1_H_ADR access｜@ref RADIO_RX_RATE1_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_rate1_h:         8;      /*!<［｜<in-house>*TODO*英訳｜受信データレート変換設定(上位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RX_RATE1_H_T;

/** @brief ［Type definition for @ref RADIO_RX_RATE1_L_ADR access｜@ref RADIO_RX_RATE1_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_rate1_l:         8;      /*!<［｜<in-house>*TODO*英訳｜受信データレート変換設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RX_RATE1_L_T;

/** @brief ［Type definition for @ref RADIO_RX_RATE2_ADR access｜@ref RADIO_RX_RATE2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_rate2:           7;      /*!<［｜<in-house>*TODO*英訳｜受信データレート変換設定2(設定範囲: 30～127) R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RX_RATE2_T;

/** @brief ［Type definition for @ref RADIO_OSC_W_SEL_ADR access｜@ref RADIO_OSC_W_SEL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t osc_w_sel:          3;      /*!<［｜<in-house>*TODO*英訳｜クロック安定化待ち時間設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_OSC_W_SEL_T;

/** @brief ［Type definition for @ref RADIO_PLL_LOCK_DETECT_ADR access｜@ref RADIO_PLL_LOCK_DETECT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tim_pll_ld:         7;      /*!<［｜<in-house>*TODO*英訳｜PLLロック判定時間調整 R/W］*/
        uint8_t pll_ld_en:          1;      /*!<［｜<in-house>*TODO*英訳｜送信時のPLLロック外れ検出後の状態設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PLL_LOCK_DETECT_T;

/** @brief ［Type definition for @ref RADIO_GAIN_HTOL_ADR access｜@ref RADIO_GAIN_HTOL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_th_hl:          8;      /*!<［｜<in-house>*TODO*英訳｜ゲイン切り替え閾値(高ゲイン⇒低ゲイン) R］*/
    }bits;
    uint8_t byte;
}RADIO_GAIN_HTOL_T;

/** @brief ［Type definition for @ref RADIO_GAIN_LTOH_ADR access｜@ref RADIO_GAIN_LTOH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t agc_th_lh:          8;      /*!<［｜<in-house>*TODO*英訳｜ゲイン切り替え閾値(低ゲイン⇒高ゲイン) R］*/
    }bits;
    uint8_t byte;
}RADIO_GAIN_LTOH_T;

/** @brief ［Type definition for @ref RADIO_GAIN_HOLD_ADR access｜@ref RADIO_GAIN_HOLD_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t gain_sync_hold:     1;      /*!<［｜<in-house>*TODO*英訳｜ゲイン切り替え設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GAIN_HOLD_T;

/** @brief ［Type definition for @ref RADIO_RSSI_STABLE_RES_ADR access｜@ref RADIO_RSSI_STABLE_RES_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rssi_stable_res:    1;      /*!<［｜<in-house>*TODO*英訳｜RSSI安定待ち時間分解能設定 R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_RSSI_STABLE_RES_T;

/** @brief ［Type definition for @ref RADIO_GC_CTRL_DIV_ADR access｜@ref RADIO_GC_CTRL_DIV_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gc_mode_div:        4;      /*!<［｜<in-house>*TODO*英訳｜ダイバーシティ時のゲイン制御モード設定 R/W］*/
        uint8_t gc_mode_cca:        4;      /*!<［｜<in-house>*TODO*英訳｜CCA時のゲイン制御モード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GC_CTRL_DIV_T;

/** @brief ［Type definition for @ref RADIO_RSSI_ADJ_L_ADR access｜@ref RADIO_RSSI_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rssi_gcadd:         7;      /*!<［｜<in-house>*TODO*英訳｜低ゲイン動作時のRSSIオフセット値 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RSSI_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_RSSI_STABLE_TIME_ADR access｜@ref RADIO_RSSI_STABLE_TIME_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rssi_stable:        3;      /*!<［｜<in-house>*TODO*英訳｜ゲイン切替後のRSSI安定待ち時間設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t rssi_stable2:       3;      /*!<［｜<in-house>*TODO*英訳｜高速電波チェック時ゲイン切替後のRSSI安定待ち時間設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RSSI_STABLE_TIME_T;

/** @brief ［Type definition for @ref RADIO_RSSI_MAG_ADJ_ADR access｜@ref RADIO_RSSI_MAG_ADJ_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rssi_val_trim:      5;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RSSI_MAG_ADJ_T;

/** @brief ［Type definition for @ref RADIO_AFC_GC_CTRL_ADR access｜@ref RADIO_AFC_GC_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gc_mode:            4;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t pll_afc_update_sel: 2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t pll_afc_update_en:  1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t pll_afc_en:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_AFC_GC_CTRL_T;

/** @brief ［Type definition for @ref RADIO_CRC_POLY3_ADR access｜@ref RADIO_CRC_POLY3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_poly:           7;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_POLY3_T;

/** @brief ［Type definition for @ref RADIO_CRC_POLY2_ADR access｜@ref RADIO_CRC_POLY2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_poly:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_POLY2_T;

/** @brief ［Type definition for @ref RADIO_CRC_POLY1_ADR access｜@ref RADIO_CRC_POLY1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_poly:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_POLY1_T;

/** @brief ［Type definition for @ref RADIO_CRC_POLY0_ADR access｜@ref RADIO_CRC_POLY0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_poly:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_POLY0_T;

/** @brief ［Type definition for @ref RADIO_PLL_DIV_SET_ADR access｜@ref RADIO_PLL_DIV_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pll_div_sel:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t pll_out_div:        3;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t rx_div_sel:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_PLL_DIV_SET_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_I_ADR access｜@ref RADIO_TXFREQ_I_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_i:           6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_I_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_FH_ADR access｜@ref RADIO_TXFREQ_FH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_f:           6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_FH_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_FM_ADR access｜@ref RADIO_TXFREQ_FM_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_f:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_FM_T;

/** @brief ［Type definition for @ref RADIO_TXFREQ_FL_ADR access｜@ref RADIO_TXFREQ_FL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfreq_f:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXFREQ_FL_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_I_ADR access｜@ref RADIO_RXFREQ_I_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_i:           6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_I_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_FH_ADR access｜@ref RADIO_RXFREQ_FH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_f:           6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_FH_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_FM_ADR access｜@ref RADIO_RXFREQ_FM_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_f:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_FM_T;

/** @brief ［Type definition for @ref RADIO_RXFREQ_FL_ADR access｜@ref RADIO_RXFREQ_FL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxfreq_f:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RXFREQ_FL_T;

/** @brief ［Type definition for @ref RADIO_CH_SPACE_H_ADR access｜@ref RADIO_CH_SPACE_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ch_space:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CH_SPACE_H_T;

/** @brief ［Type definition for @ref RADIO_CH_SPACE_L_ADR access｜@ref RADIO_CH_SPACE_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ch_space:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CH_SPACE_L_T;

/** @brief ［Type definition for @ref RADIO_SYNC_WORD_LEN_ADR access｜@ref RADIO_SYNC_WORD_LEN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word_len:      6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_WORD_LEN_T;

/** @brief ［Type definition for @ref RADIO_SYNC_WORD_EN_ADR access｜@ref RADIO_SYNC_WORD_EN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word_en0:      1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t sync_word_en1:      1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t sync_word_en2:      1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t sync_word_en3:      1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_WORD_EN_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD1_SET0_ADR access｜@ref RADIO_SYNCWORD1_SET0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word1:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD1_SET0_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD1_SET1_ADR access｜@ref RADIO_SYNCWORD1_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word1:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD1_SET1_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD1_SET2_ADR access｜@ref RADIO_SYNCWORD1_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word1:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD1_SET2_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD1_SET3_ADR access｜@ref RADIO_SYNCWORD1_SET3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word1:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD1_SET3_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD2_SET0_ADR access｜@ref RADIO_SYNCWORD2_SET0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word2:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD2_SET0_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD2_SET1_ADR access｜@ref RADIO_SYNCWORD2_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word2:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD2_SET1_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD2_SET2_ADR access｜@ref RADIO_SYNCWORD2_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word2:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD2_SET2_T;

/** @brief ［Type definition for @ref RADIO_SYNCWORD2_SET3_ADR access｜@ref RADIO_SYNCWORD2_SET3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_word2:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNCWORD2_SET3_T;

/** @brief ［Type definition for @ref RADIO_FSK_CTRL_ADR access｜@ref RADIO_FSK_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_clk_set:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gfsk_clkx2:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gfsk_clkx4:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gfsk_clkx8:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t bt_sel:             2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_CTRL_T;

/** @brief ［Type definition for @ref RADIO_GFSK_DEV_H_ADR access｜@ref RADIO_GFSK_DEV_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gfsk_dev:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GFSK_DEV_H_T;

/** @brief ［Type definition for @ref RADIO_GFSK_DEV_L_ADR access｜@ref RADIO_GFSK_DEV_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gfsk_dev:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GFSK_DEV_L_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV0_H_GFIL0_ADR access｜@ref RADIO_FSK_DEV0_H_GFIL0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev0:           6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gfil0:              2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV0_H_GFIL0_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV0_L_GFIL1_ADR access｜@ref RADIO_FSK_DEV0_L_GFIL1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev0:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV0_L_GFIL1_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV1_H_GFIL2_ADR access｜@ref RADIO_FSK_DEV1_H_GFIL2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev1:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV1_H_GFIL2_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV1_L_GFIL3_ADR access｜@ref RADIO_FSK_DEV1_L_GFIL3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev1:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV1_L_GFIL3_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV2_H_GFIL4_ADR access｜@ref RADIO_FSK_DEV2_H_GFIL4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev2:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV2_H_GFIL4_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV2_L_GFIL5_ADR access｜@ref RADIO_FSK_DEV2_L_GFIL5_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev2:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV2_L_GFIL5_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV3_H_GFIL6_ADR access｜@ref RADIO_FSK_DEV3_H_GFIL6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev3:           6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gfil6:              2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV3_H_GFIL6_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV3_L_ADR access｜@ref RADIO_FSK_DEV3_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev3:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV3_L_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV4_H_ADR access｜@ref RADIO_FSK_DEV4_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev4:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV4_H_T;

/** @brief ［Type definition for @ref RADIO_FSK_DEV4_L_ADR access｜@ref RADIO_FSK_DEV4_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk_dev4:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_DEV4_L_T;

/** @brief ［Type definition for @ref RADIO_FSK_TIM_ADJ4_ADR access｜@ref RADIO_FSK_TIM_ADJ4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t mod_tim04:          8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_TIM_ADJ4_T;

/** @brief ［Type definition for @ref RADIO_FSK_TIM_ADJ3_ADR access｜@ref RADIO_FSK_TIM_ADJ3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t mod_tim03:          8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_TIM_ADJ3_T;

/** @brief ［Type definition for @ref RADIO_FSK_TIM_ADJ2_ADR access｜@ref RADIO_FSK_TIM_ADJ2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t mod_tim02:          8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_TIM_ADJ2_T;

/** @brief ［Type definition for @ref RADIO_FSK_TIM_ADJ1_ADR access｜@ref RADIO_FSK_TIM_ADJ1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t mod_tim01:          8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_TIM_ADJ1_T;

/** @brief ［Type definition for @ref RADIO_FSK_TIM_ADJ0_ADR access｜@ref RADIO_FSK_TIM_ADJ0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t mod_tim00:          8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FSK_TIM_ADJ0_T;

/** @brief ［Type definition for @ref RADIO_4FSK_DATA_MAP_ADR access｜@ref RADIO_4FSK_DATA_MAP_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fsk4_freq0:         2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t fsk4_freq1:         2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t fsk4_freq2:         2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t fsk4_freq3:         2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_4FSK_DATA_MAP_T;

/** @brief ［Type definition for @ref RADIO_FREQ_ADJ_H_ADR access｜@ref RADIO_FREQ_ADJ_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t freq_adj:           2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t freq_adj_sign:      1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FREQ_ADJ_H_T;

/** @brief ［Type definition for @ref RADIO_FREQ_ADJ_L_ADR access｜@ref RADIO_FREQ_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t freq_adj:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FREQ_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_2DIV_MODE_ADR access｜@ref RADIO_2DIV_MODE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t div_ed_avg:         3;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t search_mode:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t sthold_en:          1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t sync_chk_off:       1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t div_gc_en:          1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_MODE_T;

/** @brief ［Type definition for @ref RADIO_2DIV_SEARCH1_ADR access｜@ref RADIO_2DIV_SEARCH1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t search_time1:       7;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t search_time_set:    1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_SEARCH1_T;

/** @brief ［Type definition for @ref RADIO_2DIV_SEARCH2_ADR access｜@ref RADIO_2DIV_SEARCH2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t search_time2:       7;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_SEARCH2_T;

/** @brief ［Type definition for @ref RADIO_2DIV_FAST_LVL_ADR access｜@ref RADIO_2DIV_FAST_LVL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t two_div_fast_lvl:    8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_FAST_LVL_T;

/** @brief ［Type definition for @ref RADIO_2DIV_PB_TH_ADR access｜@ref RADIO_2DIV_PB_TH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t two_div_pb_th:      5;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_PB_TH_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_I_ADR access｜@ref RADIO_VCO_CAL_MIN_I_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_i:      6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_I_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_FH_ADR access｜@ref RADIO_VCO_CAL_MIN_FH_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_f:      6;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_FH_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_FM_ADR access｜@ref RADIO_VCO_CAL_MIN_FM_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_f:      8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_FM_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_MIN_FL_ADR access｜@ref RADIO_VCO_CAL_MIN_FL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_f:      8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MIN_FL_T;

/** @brief ［Type definition for @ref RADIO_FVCAL_MAX_ADR access｜@ref RADIO_FVCAL_MAX_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_max_n:      4;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          4;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_MAX_N_T;

/** @brief ［Type definition for @ref RADIO_FVCAL_MIN_ADR access｜@ref RADIO_FVCAL_MIN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FVCAL_MIN_T;

/** @brief ［Type definition for @ref RADIO_FVCAL_MAX_ADR access｜@ref RADIO_FVCAL_MAX_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_max:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FVCAL_MAX_T;

/** @brief ［Type definition for @ref RADIO_VCO_ACAL_ADR access｜@ref RADIO_VCO_ACAL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_acal:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_ACAL_T;

/** @brief ［Type definition for @ref RADIO_VCO_ACAL_WR_EN_ADR access｜@ref RADIO_VCO_ACAL_WR_EN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_acal_wr_en:     1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_ACAL_WR_EN_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET0_ADR access｜@ref RADIO_DEMOD_SET0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t afc_off:            1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t afc_hold_on:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t afc_lim_off:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t str_hold_on:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t str_lim_on:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t iq_inv:             1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t chfil_wide_sync:    1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET0_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET1_ADR access｜@ref RADIO_DEMOD_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dem_fil:            3;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t dem_fil2:           2;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET1_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET2_ADR access｜@ref RADIO_DEMOD_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dem_gain:           3;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET2_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET3_ADR access｜@ref RADIO_DEMOD_SET3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dem_4fsk_th:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET3_T;

/** @brief ［Type definition for @ref RADIO_RX_IQ_SEL_ADR access｜@ref RADIO_RX_IQ_SEL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_iq_sel_norm:     1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t rx_iq_sel_fast_en:  1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t rx_iq_sel_fast:     1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t rx_iq_sel_sync_en:  1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t rx_iq_sel_sync:     1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_RX_IQ_SEL_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET6_ADR access｜@ref RADIO_DEMOD_SET6_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxdev_range:        8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET6_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET7_ADR access｜@ref RADIO_DEMOD_SET7_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t afc_limit:          8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET7_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET8_ADR access｜@ref RADIO_DEMOD_SET8_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pll_afc_shift:      3;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET8_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET9_ADR access｜@ref RADIO_DEMOD_SET9_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pll_afc_co:         8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET9_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET10_ADR access｜@ref RADIO_DEMOD_SET10_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t str_pb_len:         5;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t bit_sync_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET10_T;

/** @brief ［Type definition for @ref RADIO_DEMOD_SET11_ADR access｜@ref RADIO_DEMOD_SET11_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t str_pb_len_div:     5;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_DEMOD_SET11_T;

/** @brief ［Type definition for @ref RADIO_ADDR_CHK_CTR_H_ADR access｜@ref RADIO_ADDR_CHK_CTR_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t addr_chk_ctr:       3;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_ADDR_CHK_CTR_H_T;

/** @brief ［Type definition for @ref RADIO_ADDR_CHK_CTR_L_ADR access｜@ref RADIO_ADDR_CHK_CTR_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t addr_chk_ctr:       8;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_ADDR_CHK_CTR_L_T;

/** @brief ［Type definition for @ref RADIO_WHT_INIT_H_ADR access｜@ref RADIO_WHT_INIT_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t wht_init:           1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_WHT_INIT_H_T;

/** @brief ［Type definition for @ref RADIO_WHT_INIT_L_ADR access｜@ref RADIO_WHT_INIT_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t wht_init:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_WHT_INIT_L_T;

/** @brief ［Type definition for @ref RADIO_WHT_CFG_ADR access｜@ref RADIO_WHT_CFG_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t wht_cfg:            8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_WHT_CFG_T;

/** @brief ［Type definition for @ref RADIO_GPIO5_CTRL_ADR access｜@ref RADIO_GPIO5_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gpio5_ctrl:         4;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gpio5_fout_en:      1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gpio5_fout:         1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gpio5_od:           1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t gpio5_inv:          1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GPIO5_CTRL_T;

/** @brief ［Type definition for @ref RADIO_DCDC_CTRL_ADR access｜@ref RADIO_DCDC_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t low_vdd_mode:       1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_DCDC_CTRL_T;

/** @brief ［Type definition for @ref RADIO_VCO_FCAL_MIN_2P4G_ADR access｜@ref RADIO_VCO_FCAL_MIN_2P4G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_2p4g:   8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_FCAL_MIN_2P4G_T;

/** @brief ［Type definition for @ref RADIO_VCO_FCAL_MAX_2P4G_ADR access｜@ref RADIO_VCO_FCAL_MAX_2P4G_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_max_2p4g:   8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_FCAL_MAX_2P4G_T;

/** @brief ［Type definition for @ref RADIO_VCO_FCAL_MIN_2P4G_RX_ADR access｜@ref RADIO_VCO_FCAL_MIN_2P4G_RX_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_min_2p4g_rx: 8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_FCAL_MIN_2P4G_RX_T;

/** @brief ［Type definition for @ref RADIO_VCO_FCAL_MAX_2P4G_RX_ADR access｜@ref RADIO_VCO_FCAL_MAX_2P4G_RX_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_max_2p4g_rx: 8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_FCAL_MAX_2P4G_RX_T;

/** @brief ［Type definition for @ref RADIO_TX_RATE2_EN_ADR access｜@ref RADIO_TX_RATE2_EN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_rate2_en:        1;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
        uint8_t reserved0:          7;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_TX_RATE2_EN_T;

/** @brief ［Type definition for @ref RADIO_TX_RATE2_H_ADR access｜@ref RADIO_TX_RATE2_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_rate2:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TX_RATE2_H_T;

/** @brief ［Type definition for @ref RADIO_TX_RATE2_L_ADR access｜@ref RADIO_TX_RATE2_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_rate2:           8;      /*!<［｜<in-house>*TODO*英訳｜ R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TX_RATE2_L_T;

/** @brief ［Type definition for @ref RADIO_ID_CODE_ADR access｜@ref RADIO_ID_CODE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t id:                 8;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_ID_CODE_T;

/** \} */ /* End of group RF_REGISTER_BANK1 */

#endif
