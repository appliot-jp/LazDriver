/****************************************************************************************/
/**
   @file     bank0.h

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
#ifndef _bank0_H
#define _bank0_H

/**
    \addtogroup RF_REGISTER_BANK0
    \{
*/

/*［BANK0 Register Address Definitions｜BANK0レジスタアドレス定義］*/
#define RADIO_BANK_SEL_ADR              (0x00u)      /*!< ［｜<in-house>*TODO*英訳｜BANK切り替え(@ref RADIO_BANK_SEL_T 型でアクセス)］ */
#define RADIO_RST_SET_ADR               (0x01u)      /*!< ［｜<in-house>*TODO*英訳｜リセット制御(@ref RADIO_RST_SET_T 型でアクセス)］ */
#define RADIO_CLK_SET1_ADR              (0x02u)      /*!< ［｜<in-house>*TODO*英訳｜クロック制御1(@ref RADIO_CLK_SET1_T 型でアクセス)］ */
#define RADIO_CLK_SET2_ADR              (0x03u)      /*!< ［｜<in-house>*TODO*英訳｜クロック制御2(@ref RADIO_CLK_SET2_T 型でアクセス)］ */
#define RADIO_PKT_CTRL1_ADR             (0x04u)      /*!< ［｜<in-house>*TODO*英訳｜パケットフォーマット設定1(@ref RADIO_PKT_CTRL1_T 型でアクセス)］ */
#define RADIO_PKT_CTRL2_ADR             (0x05u)      /*!< ［｜<in-house>*TODO*英訳｜パケットフォーマット設定2(@ref RADIO_PKT_CTRL2_T 型でアクセス)］ */
#define RADIO_DRATE_SET_ADR             (0x06u)      /*!< ［｜<in-house>*TODO*英訳｜データレート設定(@ref RADIO_DRATE_SET_T 型でアクセス)］ */
#define RADIO_DATA_SET1_ADR             (0x07u)      /*!< ［｜<in-house>*TODO*英訳｜送受信データ各種設定1(@ref RADIO_DATA_SET1_T 型でアクセス)］ */
#define RADIO_DATA_SET2_ADR             (0x08u)      /*!< ［｜<in-house>*TODO*英訳｜送受信データ各種設定2(@ref RADIO_DATA_SET2_T 型でアクセス)］ */
#define RADIO_CH_SET_ADR                (0x09u)      /*!< ［｜<in-house>*TODO*英訳｜RFチャネル設定(@ref RADIO_CH_SET_T 型でアクセス)］ */
#define RADIO_RF_STATUS_CTRL_ADR        (0x0Au)      /*!< ［｜<in-house>*TODO*英訳｜RF状態変更設定(@ref RADIO_RF_STATUS_CTRL_T 型でアクセス)］ */
#define RADIO_RF_STATUS_ADR             (0x0Bu)      /*!< ［｜<in-house>*TODO*英訳｜RF状態設定(@ref RADIO_RF_STATUS_T 型でアクセス)］ */
#define RADIO_DIO_SET_ADR               (0x0Cu)      /*!< ［｜<in-house>*TODO*英訳｜DIO設定(@ref RADIO_DIO_SET_T 型でアクセス)］ */
#define RADIO_INT_SOURCE_GRP1_ADR       (0x0Du)      /*!< ［｜<in-house>*TODO*英訳｜割り込み表示1(@ref RADIO_INT_SOURCE_GRP1_T 型でアクセス)］ */
#define RADIO_INT_SOURCE_GRP2_ADR       (0x0Eu)      /*!< ［｜<in-house>*TODO*英訳｜割り込み表示2(@ref RADIO_INT_SOURCE_GRP2_T 型でアクセス)］ */
#define RADIO_INT_SOURCE_GRP3_ADR       (0x0Fu)      /*!< ［｜<in-house>*TODO*英訳｜割り込み表示3(@ref RADIO_INT_SOURCE_GRP3_T 型でアクセス)］ */
#define RADIO_INT_EN_GRP1_ADR           (0x10u)      /*!< ［｜<in-house>*TODO*英訳｜割り込み通知イネーブル1(@ref RADIO_INT_EN_GRP1_T 型でアクセス)］ */
#define RADIO_INT_EN_GRP2_ADR           (0x11u)      /*!< ［｜<in-house>*TODO*英訳｜割り込み通知イネーブル2(@ref RADIO_INT_EN_GRP2_T 型でアクセス)］ */
#define RADIO_INT_EN_GRP3_ADR           (0x12u)      /*!< ［｜<in-house>*TODO*英訳｜割り込み通知イネーブル3(@ref RADIO_INT_EN_GRP3_T 型でアクセス)］ */
#define RADIO_CRC_ERR_H_ADR             (0x13u)      /*!< ［｜<in-house>*TODO*英訳｜CRCエラー表示1(@ref RADIO_CRC_ERR_H_T 型でアクセス)］ */
#define RADIO_CRC_ERR_M_ADR             (0x14u)      /*!< ［｜<in-house>*TODO*英訳｜CRCエラー表示2(@ref RADIO_CRC_ERR_M_T 型でアクセス)］ */
#define RADIO_CRC_ERR_L_ADR             (0x15u)      /*!< ［｜<in-house>*TODO*英訳｜CRCエラー表示3(@ref RADIO_CRC_ERR_L_T 型でアクセス)］ */
#define RADIO_STATE_CLR_ADR             (0x16u)      /*!< ［｜<in-house>*TODO*英訳｜状態クリア制御(@ref RADIO_STATE_CLR_T 型でアクセス)］ */
#define RADIO_TXFIFO_THRH_ADR           (0x17u)      /*!< ［｜<in-house>*TODO*英訳｜送信FIFO-Full閾値(@ref RADIO_TXFIFO_THRH_T 型でアクセス)］ */
#define RADIO_TXFIFO_THRL_ADR           (0x18u)      /*!< ［｜<in-house>*TODO*英訳｜送信FIFO-Empty閾値、FAST_TXイネーブル時の閾値(@ref RADIO_TXFIFO_THRL_T 型でアクセス)］ */
#define RADIO_RXFIFO_THRH_ADR           (0x19u)      /*!< ［｜<in-house>*TODO*英訳｜受信FIFO-Full閾値(@ref RADIO_RXFIFO_THRH_T 型でアクセス)］ */
#define RADIO_RXFIFO_THRL_ADR           (0x1Au)      /*!< ［｜<in-house>*TODO*英訳｜受信FIFO-Empty閾値(@ref RADIO_RXFIFO_THRL_T 型でアクセス)］ */
#define RADIO_C_CHECK_CTRL_B0_ADR       (0x1Bu)      /*!< ［｜<in-house>*TODO*英訳｜C-fieldチェックイネーブル(@ref RADIO_C_CHECK_CTRL_B0_T 型でアクセス)］ */
#define RADIO_M_CHECK_CTRL_B0_ADR       (0x1Cu)      /*!< ［｜<in-house>*TODO*英訳｜M-fieldチェックイネーブル(@ref RADIO_M_CHECK_CTRL_B0_T 型でアクセス)］ */
#define RADIO_A_CHECK_CTRL_B0_ADR       (0x1Du)      /*!< ［｜<in-house>*TODO*英訳｜A-fieldチェックイネーブル(@ref RADIO_A_CHECK_CTRL_B0_T 型でアクセス)］ */
#define RADIO_C_FIELD_CODE1_B0_ADR      (0x1Eu)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード1(@ref RADIO_C_FIELD_CODE1_B0_T 型でアクセス)］ */
#define RADIO_C_FIELD_CODE2_B0_ADR      (0x1Fu)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード2(@ref RADIO_C_FIELD_CODE2_B0_T 型でアクセス)］ */
#define RADIO_C_FIELD_CODE3_B0_ADR      (0x20u)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード3(@ref RADIO_C_FIELD_CODE3_B0_T 型でアクセス)］ */
#define RADIO_C_FIELD_CODE4_B0_ADR      (0x21u)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード4(@ref RADIO_C_FIELD_CODE4_B0_T 型でアクセス)］ */
#define RADIO_C_FIELD_CODE5_B0_ADR      (0x22u)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード5(@ref RADIO_C_FIELD_CODE5_B0_T 型でアクセス)］ */
#define RADIO_M_FIELD_CODE1_B0_ADR      (0x23u)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE1_B0_T 型でアクセス)］ */
#define RADIO_M_FIELD_CODE2_B0_ADR      (0x24u)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE2_B0_T 型でアクセス)］ */
#define RADIO_M_FIELD_CODE3_B0_ADR      (0x25u)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE3_B0_T 型でアクセス)］ */
#define RADIO_M_FIELD_CODE4_B0_ADR      (0x26u)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE4_B0_T 型でアクセス)］ */
#define RADIO_A_FIELD_CODE1_B0_ADR      (0x27u)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE1_B0_T 型でアクセス)］ */
#define RADIO_A_FIELD_CODE2_B0_ADR      (0x28u)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE2_B0_T 型でアクセス)］ */
#define RADIO_A_FIELD_CODE3_B0_ADR      (0x29u)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE3_B0_T 型でアクセス)］ */
#define RADIO_A_FIELD_CODE4_B0_ADR      (0x2Au)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE4_B0_T 型でアクセス)］ */
#define RADIO_A_FIELD_CODE5_B0_ADR      (0x2Bu)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE5_B0_T 型でアクセス)］ */
#define RADIO_A_FIELD_CODE6_B0_ADR      (0x2Cu)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE6_B0_T 型でアクセス)］ */
#define RADIO_SLEEP_WU_SET_ADR          (0x2Du)      /*!< ［｜<in-house>*TODO*英訳｜SLEEP/WakeUPタイマ設定(@ref RADIO_SLEEP_WU_SET_T 型でアクセス)］ */
#define RADIO_WUT_CLK_SET_ADR           (0x2Eu)      /*!< ［｜<in-house>*TODO*英訳｜WakeUPタイマ用クロック分周設定(@ref RADIO_WUT_CLK_SET_T 型でアクセス)］ */
#define RADIO_WUT_INTERVAL_H_ADR        (0x2Fu)      /*!< ［｜<in-house>*TODO*英訳｜WakeUPタイマインターバル設定(上位バイト)(@ref RADIO_WUT_INTERVAL_H_T 型でアクセス)］ */
#define RADIO_WUT_INTERVAL_L_ADR        (0x30u)      /*!< ［｜<in-house>*TODO*英訳｜WakeUPタイマインターバル設定(下位バイト)(@ref RADIO_WUT_INTERVAL_L_T 型でアクセス)］ */
#define RADIO_WU_DURATION_ADR           (0x31u)      /*!< ［｜<in-house>*TODO*英訳｜WakeUP後の動作継続タイマ稼働時間設定(@ref RADIO_WU_DURATION_T 型でアクセス)］ */
#define RADIO_GT_SET_ADR                (0x32u)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ設定(@ref RADIO_GT_SET_T 型でアクセス)］ */
#define RADIO_GT_CLK_SET_ADR            (0x33u)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ用クロック分周設定(@ref RADIO_GT_CLK_SET_T 型でアクセス)］ */
#define RADIO_GT1_TIMER_ADR             (0x34u)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ1タイマ設定(@ref RADIO_GT1_TIMER_T 型でアクセス)］ */
#define RADIO_GT2_TIMER_ADR             (0x35u)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ2タイマ設定(@ref RADIO_GT2_TIMER_T 型でアクセス)］ */
#define RADIO_CCA_IGNORE_LVL_ADR        (0x36u)      /*!< ［｜<in-house>*TODO*英訳｜CCAの判定除外ED値設定(@ref RADIO_CCA_IGNORE_LVL_T 型でアクセス)］ */
#define RADIO_CCA_LVL_ADR               (0x37u)      /*!< ［｜<in-house>*TODO*英訳｜CCA(@ref RADIO_CCA_LVL_T 型でアクセス)］ */
#define RADIO_CCA_ABORT_ADR             (0x38u)      /*!< ［｜<in-house>*TODO*英訳｜CCA(@ref RADIO_CCA_ABORT_T 型でアクセス)］ */
#define RADIO_CCA_CTRL_ADR              (0x39u)      /*!< ［｜<in-house>*TODO*英訳｜CCA制御設定(@ref RADIO_CCA_CTRL_T 型でアクセス)］ */
#define RADIO_ED_RSLT_ADR               (0x3Au)      /*!< ［｜<in-house>*TODO*英訳｜ED値表示(@ref RADIO_ED_RSLT_T 型でアクセス)］ */
#define RADIO_IDLE_WAIT_H_ADR           (0x3Bu)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間設定(上位バイト)(@ref RADIO_IDLE_WAIT_H_T 型でアクセス)］ */
#define RADIO_IDLE_WAIT_L_ADR           (0x3Cu)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間設定(下位バイト)(@ref RADIO_IDLE_WAIT_L_T 型でアクセス)］ */
#define RADIO_CCA_PROG_H_ADR            (0x3Du)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間結果表示(上位バイト)(@ref RADIO_CCA_PROG_H_T 型でアクセス)］ */
#define RADIO_CCA_PROG_L_ADR            (0x3Eu)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間結果表示(下位バイト)(@ref RADIO_CCA_PROG_L_T 型でアクセス)］ */
#define RADIO_PREAMBLE_SET_ADR          (0x3Fu)      /*!< ［｜<in-house>*TODO*英訳｜プリアンブルパターン設定(@ref RADIO_PREAMBLE_SET_T 型でアクセス)］ */
#define RADIO_VCO_VTRSLT_ADR            (0x40u)      /*!< ［｜<in-house>*TODO*英訳｜VCO調整電圧結果表示(@ref RADIO_VCO_VTRSLT_T 型でアクセス)］ */
#define RADIO_ED_CTRL_ADR               (0x41u)      /*!< ［｜<in-house>*TODO*英訳｜ED値平均回数設定数(@ref RADIO_ED_CTRL_T 型でアクセス)］ */
#define RADIO_TXPR_LEN_H_ADR            (0x42u)      /*!< ［｜<in-house>*TODO*英訳｜送信プリアンブル長設定(上位バイト)(@ref RADIO_TXPR_LEN_H_T 型でアクセス)］ */
#define RADIO_TXPR_LEN_L_ADR            (0x43u)      /*!< ［｜<in-house>*TODO*英訳｜送信プリアンブル長設定(下位バイト)(@ref RADIO_TXPR_LEN_L_T 型でアクセス)］ */
#define RADIO_POSTAMBLE_SET_ADR         (0x44u)      /*!< ［｜<in-house>*TODO*英訳｜ポストアンブル設定(@ref RADIO_POSTAMBLE_SET_T 型でアクセス)］ */
#define RADIO_SYNC_CONDITION1_ADR       (0x45u)      /*!< ［｜<in-house>*TODO*英訳｜受信プリアンブル設定(@ref RADIO_SYNC_CONDITION1_T 型でアクセス)］ */
#define RADIO_SYNC_CONDITION2_ADR       (0x46u)      /*!< ［｜<in-house>*TODO*英訳｜同期検出時のED閾値(@ref RADIO_SYNC_CONDITION2_T 型でアクセス)］ */
#define RADIO_SYNC_CONDITION3_ADR       (0x47u)      /*!< ［｜<in-house>*TODO*英訳｜誤り許容設定(@ref RADIO_SYNC_CONDITION3_T 型でアクセス)］ */
#define RADIO_2DIV_CTRL_ADR             (0x48u)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティ設定(@ref RADIO_2DIV_CTRL_T 型でアクセス)］ */
#define RADIO_2DIV_RSLT_ADR             (0x49u)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティ結果表示(@ref RADIO_2DIV_RSLT_T 型でアクセス)］ */
#define RADIO_ANT1_ED_ADR               (0x4Au)      /*!< ［｜<in-house>*TODO*英訳｜アンテナ1の取得ED値表示(@ref RADIO_ANT1_ED_T 型でアクセス)］ */
#define RADIO_ANT2_ED_ADR               (0x4Bu)      /*!< ［｜<in-house>*TODO*英訳｜アンテナ2の取得ED値表示(@ref RADIO_ANT2_ED_T 型でアクセス)］ */
#define RADIO_ANT_CTRL_ADR              (0x4Cu)      /*!< ［｜<in-house>*TODO*英訳｜送受信時のアンテナ強制設定(@ref RADIO_ANT_CTRL_T 型でアクセス)］ */
#define RADIO_MON_CTRL_ADR              (0x4Du)      /*!< ［｜<in-house>*TODO*英訳｜モニタ出力信号選択設定(@ref RADIO_MON_CTRL_T 型でアクセス)］ */
#define RADIO_GPIO0_CTRL_ADR            (0x4Eu)      /*!< ［｜<in-house>*TODO*英訳｜GPIO0端子制御設定(@ref RADIO_GPIO0_CTRL_T 型でアクセス)］ */
#define RADIO_GPIO1_CTRL_ADR            (0x4Fu)      /*!< ［｜<in-house>*TODO*英訳｜GPIO1端子制御設定(@ref RADIO_GPIO1_CTRL_T 型でアクセス)］ */
#define RADIO_GPIO2_CTRL_ADR            (0x50u)      /*!< ［｜<in-house>*TODO*英訳｜GPIO2端子制御設定(@ref RADIO_GPIO2_CTRL_T 型でアクセス)］ */
#define RADIO_GPIO3_CTRL_ADR            (0x51u)      /*!< ［｜<in-house>*TODO*英訳｜GPIO3端子制御設定(@ref RADIO_GPIO3_CTRL_T 型でアクセス)］ */
#define RADIO_GPIO4_CTRL_ADR            (0x52u)      /*!< ［｜<in-house>*TODO*英訳｜GPIO4端子制御設定(@ref RADIO_GPIO4_CTRL_T 型でアクセス)］ */
#define RADIO_EXTCLK_CTRL_ADR           (0x52u)      /*!< ［｜<in-house>*TODO*英訳｜EXT_CLK端子制御設定( @ref RADIO_EXTCLK_CTRL_T 型でアクセス)］ */
#define RADIO_SPI_EXT_PA_CTRL_ADR       (0x53u)      /*!< ［｜<in-house>*TODO*英訳｜SPIインタフェースIO(@ref RADIO_SPI_EXT_PA_CTRL_T 型でアクセス)］ */
#define RADIO_CHFIL_BW_ADR              (0x54u)      /*!< ［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅設定(@ref RADIO_CHFIL_BW_T 型でアクセス)］ */
#define RADIO_DC_I_ADJ_H_ADR            (0x55u)      /*!< ［｜<in-house>*TODO*英訳｜I相DCオフセット調整設定(上位6ビット)(@ref RADIO_DC_I_ADJ_H_T 型でアクセス)］ */
#define RADIO_DC_I_ADJ_L_ADR            (0x56u)      /*!< ［｜<in-house>*TODO*英訳｜I相DCオフセット調整設定(下位バイト)(@ref RADIO_DC_I_ADJ_L_T 型でアクセス)］ */
#define RADIO_DC_Q_ADJ_H_ADR            (0x57u)      /*!< ［｜<in-house>*TODO*英訳｜Q相DCオフセット調整設定(上位6ビット)(@ref RADIO_DC_Q_ADJ_H_T 型でアクセス)］ */
#define RADIO_DC_Q_ADJ_L_ADR            (0x58u)      /*!< ［｜<in-house>*TODO*英訳｜Q相DCオフセット調整設定(下位バイト)(@ref RADIO_DC_Q_ADJ_L_T 型でアクセス)］ */
#define RADIO_DC_FIL_ADJ_ADR            (0x59u)      /*!< ［｜<in-house>*TODO*英訳｜DCオフセット調整フィルタ設定(@ref RADIO_DC_FIL_ADJ_T 型でアクセス)］ */
#define RADIO_IQ_MAG_ADJ_H_ADR          (0x5Au)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ振幅バランス調整（上位4ビット）(@ref RADIO_IQ_MAG_ADJ_H_T 型でアクセス)］ */
#define RADIO_IQ_MAG_ADJ_L_ADR          (0x5Bu)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ振幅バランス調整（下位バイト）(@ref RADIO_IQ_MAG_ADJ_L_T 型でアクセス)］ */
#define RADIO_IQ_PHASE_ADJ_H_ADR        (0x5Cu)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ位相バランス調整（上位4ビット）(@ref RADIO_IQ_PHASE_ADJ_H_T 型でアクセス)］ */
#define RADIO_IQ_PHASE_ADJ_L_ADR        (0x5Du)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ位相バランス調整（下位バイト）(@ref RADIO_IQ_PHASE_ADJ_L_T 型でアクセス)］ */
#define RADIO_IQ_ADJ_WAIT_ADR           (0x5Eu)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ自動調整用RSSI取得ウェイト時間(@ref RADIO_IQ_ADJ_WAIT_T 型でアクセス)］ */
#define RADIO_IQ_ADJ_TARGET_ADR         (0x5Fu)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ自動調整用RSSI判定閾値(@ref RADIO_IQ_ADJ_TARGET_T 型でアクセス)］ */
#define RADIO_DEC_GAIN_ADR              (0x60u)      /*!< ［｜<in-house>*TODO*英訳｜デシメーションゲイン設定(@ref RADIO_DEC_GAIN_T 型でアクセス)］ */
#define RADIO_IF_FREQ_ADR               (0x61u)      /*!< ［｜<in-house>*TODO*英訳｜IF周波数選択(@ref RADIO_IF_FREQ_T 型でアクセス)］ */
#define RADIO_OSC_ADJ1_ADR              (0x62u)      /*!< ［｜<in-house>*TODO*英訳｜発振回路制御(粗調）(@ref RADIO_OSC_ADJ1_T 型でアクセス)］ */
#define RADIO_OSC_ADJ2_ADR              (0x63u)      /*!< ［｜<in-house>*TODO*英訳｜発振回路制御(微調）(@ref RADIO_OSC_ADJ2_T 型でアクセス)］ */
#define RADIO_FIELD_CHECK_RSLT_ADR      (0x64u)      /*!< ［｜<in-house>*TODO*英訳｜フィールドチェック結果表示 (@ref RADIO_FIELD_CHECK_RSLT_T 型でアクセス)］ */
#define RADIO_OSC_ADJ4_ADR              (0x65u)      /*!< ［｜<in-house>*TODO*英訳｜高速起動時発振回路バイアス設定(@ref RADIO_OSC_ADJ4_T 型でアクセス)］ */
#define RADIO_RSSI_ADJ_ADR              (0x66u)      /*!< ［｜<in-house>*TODO*英訳｜RSSI値の調整(@ref RADIO_RSSI_ADJ_T 型でアクセス)］ */
#define RADIO_PA_MODE_ADR               (0x67u)      /*!< ［｜<in-house>*TODO*英訳｜PAモード設定/PAレギュレータ調整(@ref RADIO_B0_ADR67_T 型でアクセス)］ */
#define RADIO_PA_REG_ADJ_H_ADR          (0x67u)      /*!< ［｜<in-house>*TODO*英訳｜PAレギュレータ調整(上位バイト)(@ref RADIO_B0_ADR67_T 型でアクセス)］ */
#define RADIO_PA_REG_FINE_ADJ_L_ADR     (0x68u)      /*!< ［｜<in-house>*TODO*英訳｜PAレギュレータ微調整(@ref RADIO_B0_ADR68_T 型でアクセス)］ */
#define RADIO_PA_REG_ADJ_L_ADR          (0x68u)      /*!< ［｜<in-house>*TODO*英訳｜PAレギュレータ調整(下位バイト)(@ref RADIO_B0_ADR68_T 型でアクセス)］ */
#define RADIO_PA_ADJ_ADR                (0x69u)      /*!< ［｜<in-house>*TODO*英訳｜PAパワー調整設定(@ref RADIO_PA_ADJ_T 型でアクセス)］ */
#define RADIO_CHFIL_BW_CCA_ADR          (0x6Au)      /*!< ［｜<in-house>*TODO*英訳｜CCA時チャネルフィルタ帯域幅設定(@ref RADIO_CHFIL_BW_CCA_T 型でアクセス)］ */
#define RADIO_CHFIL_BW_OPTION_ADR       (0x6Bu)      /*!< ［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅オプション設定(@ref RADIO_CHFIL_BW_OPTION_T 型でアクセス)］ */
#define RADIO_DC_FIL_ADJ2_ADR           (0x6Cu)      /*!< ［｜<in-house>*TODO*英訳｜DCオフセット調整フィルタ設定2(@ref RADIO_DC_FIL_ADJ2_T 型でアクセス)］ */
#define RADIO_DEC_GAIN_CCA_ADR          (0x6Du)      /*!< ［｜<in-house>*TODO*英訳｜CCA時のデシメーションゲイン設定(@ref RADIO_DEC_GAIN_CCA_T 型でアクセス)］ */
#define RADIO_VCO_CAL_ADR               (0x6Eu)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション値表示または設定(@ref RADIO_VCO_CAL_T 型でアクセス)］ */
#define RADIO_VCO_CAL_START_ADR         (0x6Fu)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション実行(@ref RADIO_VCO_CAL_START_T 型でアクセス)］ */
#define RADIO_CLK_CAL_SET_ADR           (0x70u)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション制御(@ref RADIO_CLK_CAL_SET_T 型でアクセス)］ */
#define RADIO_CLK_CAL_TIME_ADR          (0x71u)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション時間設定(@ref RADIO_CLK_CAL_TIME_T 型でアクセス)］ */
#define RADIO_CLK_CAL_H_ADR             (0x72u)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション値表示(上位バイト)(@ref RADIO_CLK_CAL_H_T 型でアクセス)］ */
#define RADIO_CLK_CAL_L_ADR             (0x73u)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション値表示(下位バイト)(@ref RADIO_CLK_CAL_L_T 型でアクセス)］ */
#define RADIO_FEC_CTRL_ADR              (0x74u)      /*!< ［｜<in-house>*TODO*英訳｜FEC設定(@ref RADIO_FEC_CTRL_T 型でアクセス)］ */
#define RADIO_SLEEP_INT_CLR_ADR         (0x75u)      /*!< ［｜<in-house>*TODO*英訳｜SLEEP時割込みクリア設定(@ref RADIO_SLEEP_INT_CLR_T 型でアクセス)］ */
#define RADIO_RF_TEST_MODE_ADR          (0x76u)      /*!< ［｜<in-house>*TODO*英訳｜送信テストパターン設定(@ref RADIO_RF_TEST_MODE_T 型でアクセス)］ */
#define RADIO_STM_STATE_ADR             (0x77u)      /*!< ［｜<in-house>*TODO*英訳｜ステートマシン状態表示(@ref RADIO_STM_STATE_T 型でアクセス)］ */
#define RADIO_FIFO_SET_ADR              (0x78u)      /*!< ［｜<in-house>*TODO*英訳｜FIFOリード設定(@ref RADIO_FIFO_SET_T 型でアクセス)］ */
#define RADIO_RX_FIFO_LAST_ADR          (0x79u)      /*!< ［｜<in-house>*TODO*英訳｜受信時FIFO使用量表示(@ref RADIO_RX_FIFO_LAST_T 型でアクセス)］ */
#define RADIO_TX_PKT_LEN_H_ADR          (0x7Au)      /*!< ［｜<in-house>*TODO*英訳｜送信パケット長設定(@ref RADIO_TX_PKT_LEN_H_T 型でアクセス)］ */
#define RADIO_TX_PKT_LEN_L_ADR          (0x7Bu)      /*!< ［｜<in-house>*TODO*英訳｜送信パケット長設定(@ref RADIO_TX_PKT_LEN_L_T 型でアクセス)］ */
#define RADIO_WR_TX_FIFO_ADR            (0x7Cu)      /*!< ［｜<in-house>*TODO*英訳｜送信FIFO(@ref RADIO_WR_TX_FIFO_T 型でアクセス)］ */
#define RADIO_RX_PKT_LEN_H_ADR          (0x7Du)      /*!< ［｜<in-house>*TODO*英訳｜受信パケット長表示(@ref RADIO_RX_PKT_LEN_H_T 型でアクセス)］ */
#define RADIO_RX_PKT_LEN_L_ADR          (0x7Eu)      /*!< ［｜<in-house>*TODO*英訳｜受信パケット長表示(@ref RADIO_RX_PKT_LEN_L_T 型でアクセス)］ */
#define RADIO_RD_FIFO_ADR               (0x7Fu)      /*!< ［｜<in-house>*TODO*英訳｜FIFOリード(@ref RADIO_RD_FIFO_T 型でアクセス)］ */

#define BANK_RST_SET_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜リセット制御(@ref RADIO_RST_SET_T 型でアクセス)］ */
#define BANK_CLK_SET1_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜クロック制御1(@ref RADIO_CLK_SET1_T 型でアクセス)］ */
#define BANK_CLK_SET2_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜クロック制御2(@ref RADIO_CLK_SET2_T 型でアクセス)］ */
#define BANK_PKT_CTRL1_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜パケットフォーマット設定1(@ref RADIO_PKT_CTRL1_T 型でアクセス)］ */
#define BANK_PKT_CTRL2_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜パケットフォーマット設定2(@ref RADIO_PKT_CTRL2_T 型でアクセス)］ */
#define BANK_DRATE_SET_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜データレート設定(@ref RADIO_DRATE_SET_T 型でアクセス)］ */
#define BANK_DATA_SET1_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜送受信データ各種設定1(@ref RADIO_DATA_SET1_T 型でアクセス)］ */
#define BANK_DATA_SET2_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜送受信データ各種設定2(@ref RADIO_DATA_SET2_T 型でアクセス)］ */
#define BANK_CH_SET_ADR                (0)      /*!< ［｜<in-house>*TODO*英訳｜RFチャネル設定(@ref RADIO_CH_SET_T 型でアクセス)］ */
#define BANK_RF_STATUS_CTRL_ADR        (0)      /*!< ［｜<in-house>*TODO*英訳｜RF状態変更設定(@ref RADIO_RF_STATUS_CTRL_T 型でアクセス)］ */
#define BANK_RF_STATUS_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜RF状態設定(@ref RADIO_RF_STATUS_T 型でアクセス)］ */
#define BANK_DIO_SET_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜DIO設定(@ref RADIO_DIO_SET_T 型でアクセス)］ */
#define BANK_INT_SOURCE_GRP1_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜割り込み表示1(@ref RADIO_INT_SOURCE_GRP1_T 型でアクセス)］ */
#define BANK_INT_SOURCE_GRP2_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜割り込み表示2(@ref RADIO_INT_SOURCE_GRP2_T 型でアクセス)］ */
#define BANK_INT_SOURCE_GRP3_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜割り込み表示3(@ref RADIO_INT_SOURCE_GRP3_T 型でアクセス)］ */
#define BANK_INT_EN_GRP1_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜割り込み通知イネーブル1(@ref RADIO_INT_EN_GRP1_T 型でアクセス)］ */
#define BANK_INT_EN_GRP2_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜割り込み通知イネーブル2(@ref RADIO_INT_EN_GRP2_T 型でアクセス)］ */
#define BANK_INT_EN_GRP3_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜割り込み通知イネーブル3(@ref RADIO_INT_EN_GRP3_T 型でアクセス)］ */
#define BANK_CRC_ERR_H_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜CRCエラー表示1(@ref RADIO_CRC_ERR_H_T 型でアクセス)］ */
#define BANK_CRC_ERR_M_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜CRCエラー表示2(@ref RADIO_CRC_ERR_M_T 型でアクセス)］ */
#define BANK_CRC_ERR_L_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜CRCエラー表示3(@ref RADIO_CRC_ERR_L_T 型でアクセス)］ */
#define BANK_STATE_CLR_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜状態クリア制御(@ref RADIO_STATE_CLR_T 型でアクセス)］ */
#define BANK_TXFIFO_THRH_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜送信FIFO-Full閾値(@ref RADIO_TXFIFO_THRH_T 型でアクセス)］ */
#define BANK_TXFIFO_THRL_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜送信FIFO-Empty閾値、FAST_TXイネーブル時の閾値(@ref RADIO_TXFIFO_THRL_T 型でアクセス)］ */
#define BANK_RXFIFO_THRH_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜受信FIFO-Full閾値(@ref RADIO_RXFIFO_THRH_T 型でアクセス)］ */
#define BANK_RXFIFO_THRL_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜受信FIFO-Empty閾値(@ref RADIO_RXFIFO_THRL_T 型でアクセス)］ */
#define BANK_C_CHECK_CTRL_B0_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜C-fieldチェックイネーブル(@ref RADIO_C_CHECK_CTRL_B0_T 型でアクセス)］ */
#define BANK_M_CHECK_CTRL_B0_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜M-fieldチェックイネーブル(@ref RADIO_M_CHECK_CTRL_B0_T 型でアクセス)］ */
#define BANK_A_CHECK_CTRL_B0_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜A-fieldチェックイネーブル(@ref RADIO_A_CHECK_CTRL_B0_T 型でアクセス)］ */
#define BANK_C_FIELD_CODE1_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード1(@ref RADIO_C_FIELD_CODE1_B0_T 型でアクセス)］ */
#define BANK_C_FIELD_CODE2_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード2(@ref RADIO_C_FIELD_CODE2_B0_T 型でアクセス)］ */
#define BANK_C_FIELD_CODE3_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード3(@ref RADIO_C_FIELD_CODE3_B0_T 型でアクセス)］ */
#define BANK_C_FIELD_CODE4_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード4(@ref RADIO_C_FIELD_CODE4_B0_T 型でアクセス)］ */
#define BANK_C_FIELD_CODE5_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜C-field設定コード5(@ref RADIO_C_FIELD_CODE5_B0_T 型でアクセス)］ */
#define BANK_M_FIELD_CODE1_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE1_B0_T 型でアクセス)］ */
#define BANK_M_FIELD_CODE2_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE2_B0_T 型でアクセス)］ */
#define BANK_M_FIELD_CODE3_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE3_B0_T 型でアクセス)］ */
#define BANK_M_FIELD_CODE4_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜M-field(@ref RADIO_M_FIELD_CODE4_B0_T 型でアクセス)］ */
#define BANK_A_FIELD_CODE1_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE1_B0_T 型でアクセス)］ */
#define BANK_A_FIELD_CODE2_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE2_B0_T 型でアクセス)］ */
#define BANK_A_FIELD_CODE3_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE3_B0_T 型でアクセス)］ */
#define BANK_A_FIELD_CODE4_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE4_B0_T 型でアクセス)］ */
#define BANK_A_FIELD_CODE5_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE5_B0_T 型でアクセス)］ */
#define BANK_A_FIELD_CODE6_B0_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜A-field(@ref RADIO_A_FIELD_CODE6_B0_T 型でアクセス)］ */
#define BANK_SLEEP_WU_SET_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜SLEEP/WakeUPタイマ設定(@ref RADIO_SLEEP_WU_SET_T 型でアクセス)］ */
#define BANK_WUT_CLK_SET_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜WakeUPタイマ用クロック分周設定(@ref RADIO_WUT_CLK_SET_T 型でアクセス)］ */
#define BANK_WUT_INTERVAL_H_ADR        (0)      /*!< ［｜<in-house>*TODO*英訳｜WakeUPタイマインターバル設定(上位バイト)(@ref RADIO_WUT_INTERVAL_H_T 型でアクセス)］ */
#define BANK_WUT_INTERVAL_L_ADR        (0)      /*!< ［｜<in-house>*TODO*英訳｜WakeUPタイマインターバル設定(下位バイト)(@ref RADIO_WUT_INTERVAL_L_T 型でアクセス)］ */
#define BANK_WU_DURATION_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜WakeUP後の動作継続タイマ稼働時間設定(@ref RADIO_WU_DURATION_T 型でアクセス)］ */
#define BANK_GT_SET_ADR                (0)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ設定(@ref RADIO_GT_SET_T 型でアクセス)］ */
#define BANK_GT_CLK_SET_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ用クロック分周設定(@ref RADIO_GT_CLK_SET_T 型でアクセス)］ */
#define BANK_GT1_TIMER_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ1タイマ設定(@ref RADIO_GT1_TIMER_T 型でアクセス)］ */
#define BANK_GT2_TIMER_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜汎用タイマ2タイマ設定(@ref RADIO_GT2_TIMER_T 型でアクセス)］ */
#define BANK_CCA_IGNORE_LVL_ADR        (0)      /*!< ［｜<in-house>*TODO*英訳｜CCAの判定除外ED値設定(@ref RADIO_CCA_IGNORE_LVL_T 型でアクセス)］ */
#define BANK_CCA_LVL_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜CCA(@ref RADIO_CCA_LVL_T 型でアクセス)］ */
#define BANK_CCA_ABORT_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜CCA(@ref RADIO_CCA_ABORT_T 型でアクセス)］ */
#define BANK_CCA_CTRL_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜CCA制御設定(@ref RADIO_CCA_CTRL_T 型でアクセス)］ */
#define BANK_ED_RSLT_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜ED値表示(@ref RADIO_ED_RSLT_T 型でアクセス)］ */
#define BANK_IDLE_WAIT_H_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間設定(上位バイト)(@ref RADIO_IDLE_WAIT_H_T 型でアクセス)］ */
#define BANK_IDLE_WAIT_L_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間設定(下位バイト)(@ref RADIO_IDLE_WAIT_L_T 型でアクセス)］ */
#define BANK_CCA_PROG_H_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間結果表示(上位バイト)(@ref RADIO_CCA_PROG_H_T 型でアクセス)］ */
#define BANK_CCA_PROG_L_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜IDLE検出期間結果表示(下位バイト)(@ref RADIO_CCA_PROG_L_T 型でアクセス)］ */
#define BANK_PREAMBLE_SET_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜プリアンブルパターン設定(@ref RADIO_PREAMBLE_SET_T 型でアクセス)］ */
#define BANK_VCO_VTRSLT_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜VCO調整電圧結果表示(@ref RADIO_VCO_VTRSLT_T 型でアクセス)］ */
#define BANK_ED_CTRL_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜ED値平均回数設定数(@ref RADIO_ED_CTRL_T 型でアクセス)］ */
#define BANK_TXPR_LEN_H_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜送信プリアンブル長設定(上位バイト)(@ref RADIO_TXPR_LEN_H_T 型でアクセス)］ */
#define BANK_TXPR_LEN_L_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜送信プリアンブル長設定(下位バイト)(@ref RADIO_TXPR_LEN_L_T 型でアクセス)］ */
#define BANK_POSTAMBLE_SET_ADR         (0)      /*!< ［｜<in-house>*TODO*英訳｜ポストアンブル設定(@ref RADIO_POSTAMBLE_SET_T 型でアクセス)］ */
#define BANK_SYNC_CONDITION1_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜受信プリアンブル設定(@ref RADIO_SYNC_CONDITION1_T 型でアクセス)］ */
#define BANK_SYNC_CONDITION2_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜同期検出時のED閾値(@ref RADIO_SYNC_CONDITION2_T 型でアクセス)］ */
#define BANK_SYNC_CONDITION3_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜誤り許容設定(@ref RADIO_SYNC_CONDITION3_T 型でアクセス)］ */
#define BANK_2DIV_CTRL_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティ設定(@ref RADIO_2DIV_CTRL_T 型でアクセス)］ */
#define BANK_2DIV_RSLT_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜アンテナダイバーシティ結果表示(@ref RADIO_2DIV_RSLT_T 型でアクセス)］ */
#define BANK_ANT1_ED_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜アンテナ1の取得ED値表示(@ref RADIO_ANT1_ED_T 型でアクセス)］ */
#define BANK_ANT2_ED_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜アンテナ2の取得ED値表示(@ref RADIO_ANT2_ED_T 型でアクセス)］ */
#define BANK_ANT_CTRL_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜送受信時のアンテナ強制設定(@ref RADIO_ANT_CTRL_T 型でアクセス)］ */
#define BANK_MON_CTRL_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜モニタ出力信号選択設定(@ref RADIO_MON_CTRL_T 型でアクセス)］ */
#define BANK_GPIO0_CTRL_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜GPIO0端子制御設定(@ref RADIO_GPIO0_CTRL_T 型でアクセス)］ */
#define BANK_GPIO1_CTRL_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜GPIO1端子制御設定(@ref RADIO_GPIO1_CTRL_T 型でアクセス)］ */
#define BANK_GPIO2_CTRL_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜GPIO2端子制御設定(@ref RADIO_GPIO2_CTRL_T 型でアクセス)］ */
#define BANK_GPIO3_CTRL_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜GPIO3端子制御設定(@ref RADIO_GPIO3_CTRL_T 型でアクセス)］ */
#define BANK_GPIO4_CTRL_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜GPIO4端子制御設定(@ref RADIO_GPIO4_CTRL_T 型でアクセス)］ */
#define BANK_EXTCLK_CTRL_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜EXT_CLK端子制御設定( @ref RADIO_EXTCLK_CTRL_T 型でアクセス)］ */
#define BANK_SPI_EXT_PA_CTRL_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜SPIインタフェースIO(@ref RADIO_SPI_EXT_PA_CTRL_T 型でアクセス)］ */
#define BANK_CHFIL_BW_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅設定(@ref RADIO_CHFIL_BW_T 型でアクセス)］ */
#define BANK_DC_I_ADJ_H_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜I相DCオフセット調整設定(上位6ビット)(@ref RADIO_DC_I_ADJ_H_T 型でアクセス)］ */
#define BANK_DC_I_ADJ_L_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜I相DCオフセット調整設定(下位バイト)(@ref RADIO_DC_I_ADJ_L_T 型でアクセス)］ */
#define BANK_DC_Q_ADJ_H_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜Q相DCオフセット調整設定(上位6ビット)(@ref RADIO_DC_Q_ADJ_H_T 型でアクセス)］ */
#define BANK_DC_Q_ADJ_L_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜Q相DCオフセット調整設定(下位バイト)(@ref RADIO_DC_Q_ADJ_L_T 型でアクセス)］ */
#define BANK_DC_FIL_ADJ_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜DCオフセット調整フィルタ設定(@ref RADIO_DC_FIL_ADJ_T 型でアクセス)］ */
#define BANK_IQ_MAG_ADJ_H_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ振幅バランス調整（上位4ビット）(@ref RADIO_IQ_MAG_ADJ_H_T 型でアクセス)］ */
#define BANK_IQ_MAG_ADJ_L_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ振幅バランス調整（下位バイト）(@ref RADIO_IQ_MAG_ADJ_L_T 型でアクセス)］ */
#define BANK_IQ_PHASE_ADJ_H_ADR        (0)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ位相バランス調整（上位4ビット）(@ref RADIO_IQ_PHASE_ADJ_H_T 型でアクセス)］ */
#define BANK_IQ_PHASE_ADJ_L_ADR        (0)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ位相バランス調整（下位バイト）(@ref RADIO_IQ_PHASE_ADJ_L_T 型でアクセス)］ */
#define BANK_IQ_ADJ_WAIT_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ自動調整用RSSI取得ウェイト時間(@ref RADIO_IQ_ADJ_WAIT_T 型でアクセス)］ */
#define BANK_IQ_ADJ_TARGET_ADR         (0)      /*!< ［｜<in-house>*TODO*英訳｜IFのIQ自動調整用RSSI判定閾値(@ref RADIO_IQ_ADJ_TARGET_T 型でアクセス)］ */
#define BANK_DEC_GAIN_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜デシメーションゲイン設定(@ref RADIO_DEC_GAIN_T 型でアクセス)］ */
#define BANK_IF_FREQ_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜IF周波数選択(@ref RADIO_IF_FREQ_T 型でアクセス)］ */
#define BANK_OSC_ADJ1_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜発振回路制御(粗調）(@ref RADIO_OSC_ADJ1_T 型でアクセス)］ */
#define BANK_OSC_ADJ2_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜発振回路制御(微調）(@ref RADIO_OSC_ADJ2_T 型でアクセス)］ */
#define BANK_FIELD_CHECK_RSLT_ADR      (0)      /*!< ［｜<in-house>*TODO*英訳｜フィールドチェック結果表示 (@ref RADIO_FIELD_CHECK_RSLT_T 型でアクセス)］ */
#define BANK_OSC_ADJ4_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜高速起動時発振回路バイアス設定(@ref RADIO_OSC_ADJ4_T 型でアクセス)］ */
#define BANK_RSSI_ADJ_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜RSSI値の調整(@ref RADIO_RSSI_ADJ_T 型でアクセス)］ */
#define BANK_PA_MODE_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜PAモード設定/PAレギュレータ調整(@ref RADIO_B0_ADR67_T 型でアクセス)］ */
#define BANK_PA_REG_ADJ_H_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜PAレギュレータ調整(上位バイト)(@ref RADIO_B0_ADR67_T 型でアクセス)］ */
#define BANK_PA_REG_FINE_ADJ_L_ADR     (0)      /*!< ［｜<in-house>*TODO*英訳｜PAレギュレータ微調整(@ref RADIO_B0_ADR68_T 型でアクセス)］ */
#define BANK_PA_REG_ADJ_L_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜PAレギュレータ調整(下位バイト)(@ref RADIO_B0_ADR68_T 型でアクセス)］ */
#define BANK_PA_ADJ_ADR                (0)      /*!< ［｜<in-house>*TODO*英訳｜PAパワー調整設定(@ref RADIO_PA_ADJ_T 型でアクセス)］ */
#define BANK_CHFIL_BW_CCA_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜CCA時チャネルフィルタ帯域幅設定(@ref RADIO_CHFIL_BW_CCA_T 型でアクセス)］ */
#define BANK_CHFIL_BW_OPTION_ADR       (0)      /*!< ［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅オプション設定(@ref RADIO_CHFIL_BW_OPTION_T 型でアクセス)］ */
#define BANK_DC_FIL_ADJ2_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜DCオフセット調整フィルタ設定2(@ref RADIO_DC_FIL_ADJ2_T 型でアクセス)］ */
#define BANK_DEC_GAIN_CCA_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜CCA時のデシメーションゲイン設定(@ref RADIO_DEC_GAIN_CCA_T 型でアクセス)］ */
#define BANK_VCO_CAL_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション値表示または設定(@ref RADIO_VCO_CAL_T 型でアクセス)］ */
#define BANK_VCO_CAL_START_ADR         (0)      /*!< ［｜<in-house>*TODO*英訳｜VCOキャリブレーション実行(@ref RADIO_VCO_CAL_START_T 型でアクセス)］ */
#define BANK_CLK_CAL_SET_ADR           (0)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション制御(@ref RADIO_CLK_CAL_SET_T 型でアクセス)］ */
#define BANK_CLK_CAL_TIME_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション時間設定(@ref RADIO_CLK_CAL_TIME_T 型でアクセス)］ */
#define BANK_CLK_CAL_H_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション値表示(上位バイト)(@ref RADIO_CLK_CAL_H_T 型でアクセス)］ */
#define BANK_CLK_CAL_L_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション値表示(下位バイト)(@ref RADIO_CLK_CAL_L_T 型でアクセス)］ */
#define BANK_FEC_CTRL_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜FEC設定(@ref RADIO_FEC_CTRL_T 型でアクセス)］ */
#define BANK_SLEEP_INT_CLR_ADR         (0)      /*!< ［｜<in-house>*TODO*英訳｜SLEEP時割込みクリア設定(@ref RADIO_SLEEP_INT_CLR_T 型でアクセス)］ */
#define BANK_RF_TEST_MODE_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜送信テストパターン設定(@ref RADIO_RF_TEST_MODE_T 型でアクセス)］ */
#define BANK_STM_STATE_ADR             (0)      /*!< ［｜<in-house>*TODO*英訳｜ステートマシン状態表示(@ref RADIO_STM_STATE_T 型でアクセス)］ */
#define BANK_FIFO_SET_ADR              (0)      /*!< ［｜<in-house>*TODO*英訳｜FIFOリード設定(@ref RADIO_FIFO_SET_T 型でアクセス)］ */
#define BANK_RX_FIFO_LAST_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜受信時FIFO使用量表示(@ref RADIO_RX_FIFO_LAST_T 型でアクセス)］ */
#define BANK_TX_PKT_LEN_H_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜送信パケット長設定(@ref RADIO_TX_PKT_LEN_H_T 型でアクセス)］ */
#define BANK_TX_PKT_LEN_L_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜送信パケット長設定(@ref RADIO_TX_PKT_LEN_L_T 型でアクセス)］ */
#define BANK_WR_TX_FIFO_ADR            (0)      /*!< ［｜<in-house>*TODO*英訳｜送信FIFO(@ref RADIO_WR_TX_FIFO_T 型でアクセス)］ */
#define BANK_RX_PKT_LEN_H_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜受信パケット長表示(@ref RADIO_RX_PKT_LEN_H_T 型でアクセス)］ */
#define BANK_RX_PKT_LEN_L_ADR          (0)      /*!< ［｜<in-house>*TODO*英訳｜受信パケット長表示(@ref RADIO_RX_PKT_LEN_L_T 型でアクセス)］ */
#define BANK_RD_FIFO_ADR               (0)      /*!< ［｜<in-house>*TODO*英訳｜FIFOリード(@ref RADIO_RD_FIFO_T 型でアクセス)］ */

/* ［RF register structures｜RFレジスタ構造体］ */
/** @brief ［Type definition for @ref RADIO_BANK_SEL_ADR access｜@ref RADIO_BANK_SEL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t bank:               4;      /*!<［｜<in-house>*TODO*英訳｜BANK切り替え R/W］*/
        uint8_t bank_acen:          4;      /*!<［｜<in-house>*TODO*英訳｜レジスタアクセスイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_BANK_SEL_T;


/** @brief ［Type definition for @ref RADIO_RST_SET_ADR access｜@ref RADIO_RST_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rst_0:              1;      /*!<［｜<in-house>*TODO*英訳｜コンフィグレーション機能リセット R/W］*/
        uint8_t rst_1:              1;      /*!<［｜<in-house>*TODO*英訳｜MODEM機能リセット R/W］*/
        uint8_t rst_2:              1;      /*!<［｜<in-house>*TODO*英訳｜RF状態制御機能リセット R/W］*/
        uint8_t rst_3:              1;      /*!<［｜<in-house>*TODO*英訳｜PHY機能リセット R/W］*/
        uint8_t rst0_en:            1;      /*!<［｜<in-house>*TODO*英訳｜リセット0イネーブル設定 R/W］*/
        uint8_t rst1_en:            1;      /*!<［｜<in-house>*TODO*英訳｜リセット1イネーブル設定 R/W］*/
        uint8_t rst2_en:            1;      /*!<［｜<in-house>*TODO*英訳｜リセット2イネーブル設定 R/W］*/
        uint8_t rst3_en:            1;      /*!<［｜<in-house>*TODO*英訳｜リセット3イネーブル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RST_SET_T;

/** @brief ［Type definition for @ref RADIO_CLK_SET1_ADR access｜@ref RADIO_CLK_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk0_en:            1;      /*!<［｜<in-house>*TODO*英訳｜PHY機能のクロック制御 R/W］*/
        uint8_t clk1_en:            1;      /*!<［｜<in-house>*TODO*英訳｜受信機能(DEMOD)のクロック制御 R/W］*/
        uint8_t clk2_en:            1;      /*!<［｜<in-house>*TODO*英訳｜送信機能(MOD)のクロック制御 R/W］*/
        uint8_t clk3_en:            1;      /*!<［｜<in-house>*TODO*英訳｜RF機能(RF状態制御)のクロック制御 R/W］*/
        uint8_t clk4_en:            1;      /*!<［｜<in-house>*TODO*英訳｜ADCのクロック制御 R/W］*/
        uint8_t mstr_clk_sel1:      1;      /*!<［｜<in-house>*TODO*英訳｜マスタークロック周波数選択設定1 R/W］*/
        uint8_t mstr_clk_sel2:      1;      /*!<［｜<in-house>*TODO*英訳｜マスタークロック周波数選択設定2 R/W］*/
        uint8_t clk_done:           1;      /*!<［｜<in-house>*TODO*英訳｜クロック安定化完了フラグ R］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_SET1_T;

/** @brief ［Type definition for @ref RADIO_CLK_SET2_ADR access｜@ref RADIO_CLK_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t low_rate_en:        1;      /*!<［｜<in-house>*TODO*英訳｜受信部クロック低速化設定 R/W］*/
        uint8_t reg_pa_enb:         1;      /*!<［｜<in-house>*TODO*英訳｜PAレギュレータ制御 R/W］*/
        uint8_t ext_bank_sel_en:    1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t rc32k_en:           1;      /*!<［｜<in-house>*TODO*英訳｜内蔵RC発振回路制御 R/W］*/
        uint8_t xtal_en:            1;      /*!<［｜<in-house>*TODO*英訳｜水晶発振回路制御 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t tcxo_en:            1;      /*!<［｜<in-house>*TODO*英訳｜TCXO入力制御 R/W］*/
        uint8_t mstr_clk_en:        1;      /*!<［｜<in-house>*TODO*英訳｜ロジック領域クロック供給制御 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_SET2_T;

/** @brief ［Type definition for @ref RADIO_PKT_CTRL1_ADR access｜@ref RADIO_PKT_CTRL1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pkt_format:         2;      /*!<［｜<in-house>*TODO*英訳｜パケットフォーマット設定 R/W］*/
        uint8_t ieee4g_en:          1;      /*!<［｜<in-house>*TODO*英訳｜IEEE802.15.4gモード設定 R/W］*/
        uint8_t rx_extpkt_off:      1;      /*!<［｜<in-house>*TODO*英訳｜受信時パケット拡張モードオフ設定(Wireless M-Bus対応) R/W］*/
        uint8_t dat_lf_en:          1;      /*!<［｜<in-house>*TODO*英訳｜データ領域送出順設定 R/W］*/
        uint8_t len_lf_en:          1;      /*!<［｜<in-house>*TODO*英訳｜Length領域送出順設定 R/W］*/
        uint8_t ext_pkt_mode:       2;      /*!<［｜<in-house>*TODO*英訳｜パケット拡張モード設定(Wireless M-Bus対応) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PKT_CTRL1_T;

/** @brief ［Type definition for @ref RADIO_PKT_CTRL2_ADR access｜@ref RADIO_PKT_CTRL2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t length_mode:        2;      /*!<［｜<in-house>*TODO*英訳｜Lengthフィールド長設定 R/W］*/
        uint8_t tx_crc_en:          1;      /*!<［｜<in-house>*TODO*英訳｜送信CRC設定 R/W］*/
        uint8_t rx_crc_en:          1;      /*!<［｜<in-house>*TODO*英訳｜受信CRC設定 R/W］*/
        uint8_t crc_len:            2;      /*!<［｜<in-house>*TODO*英訳｜CRC長設定 R/W］*/
        uint8_t crc_comp_off:       1;      /*!<［｜<in-house>*TODO*英訳｜CRC補数出力OFF設定 R/W］*/
        uint8_t crc_init_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜CRC演算初期値選択設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PKT_CTRL2_T;

/** @brief ［Type definition for @ref RADIO_DRATE_SET_ADR access｜@ref RADIO_DRATE_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_drate:           4;      /*!<［｜<in-house>*TODO*英訳｜送信データレート設定 R/W］*/
        uint8_t rx_drate:           4;      /*!<［｜<in-house>*TODO*英訳｜受信データレート設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DRATE_SET_T;

/** @brief ［Type definition for @ref RADIO_DATA_SET1_ADR access｜@ref RADIO_DATA_SET1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_dec_scheme:      2;      /*!<［｜<in-house>*TODO*英訳｜送信符号化モード設定 R/W］*/
        uint8_t rx_dec_scheme:      2;      /*!<［｜<in-house>*TODO*英訳｜受信符号化モード設定 R/W］*/
        uint8_t gfsk_en:            1;      /*!<［｜<in-house>*TODO*英訳｜ガウシアンフィルタ設定 R/W］*/
        uint8_t rx_fsk_pol:         1;      /*!<［｜<in-house>*TODO*英訳｜受信データ極性設定 R/W］*/
        uint8_t tx_fsk_pol:         1;      /*!<［｜<in-house>*TODO*英訳｜送信データ極性設定 R/W］*/
        uint8_t pb_pat:             1;      /*!<［｜<in-house>*TODO*英訳｜送受信極性設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DATA_SET1_T;

/** @brief ［Type definition for @ref RADIO_DATA_SET2_ADR access｜@ref RADIO_DATA_SET2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t wht_set:            1;      /*!<［｜<in-house>*TODO*英訳｜Whitening設定 R/W］*/
        uint8_t man_pol:            1;      /*!<［｜<in-house>*TODO*英訳｜マンチェスタ極性設定 R/W］*/
        uint8_t two_pb_det_en:      1;      /*!<［｜<in-house>*TODO*英訳｜受信プリアンブル2面待ち設定 R/W］*/
        uint8_t two_sw_det_en:      1;      /*!<［｜<in-house>*TODO*英訳｜SyncWord2面待ち設定 R/W］*/
        uint8_t syncword_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜同期ワードパターン選択設定 R/W］*/
        uint8_t fsk_sel:            1;      /*!<［｜<in-house>*TODO*英訳｜FSK多値化設定 R/W］*/
        uint8_t ext_pkt_mode2:      2;      /*!<［｜<in-house>*TODO*英訳｜パケット拡張モード設定2(Wireless M-Bus2013対応) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DATA_SET2_T;

/** @brief ［Type definition for @ref RADIO_CH_SET_ADR access｜@ref RADIO_CH_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rf_ch:              8;      /*!<［｜<in-house>*TODO*英訳｜送受信チャネル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CH_SET_T;

/** @brief ［Type definition for @ref RADIO_RF_STATUS_CTRL_ADR access｜@ref RADIO_RF_STATUS_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txdone_mode:        2;      /*!<［｜<in-house>*TODO*英訳｜パケット送信完了後のRF状態設定 R/W］*/
        uint8_t rxdone_mode:        2;      /*!<［｜<in-house>*TODO*英訳｜パケット受信完了後のRF状態設定 R/W］*/
        uint8_t auto_tx_en:         1;      /*!<［｜<in-house>*TODO*英訳｜自動送信設定 R/W］*/
        uint8_t fast_tx_en:         1;      /*!<［｜<in-house>*TODO*英訳｜FAST_TXモード設定 R/W］*/
        uint8_t auto_data_req:      1;      /*!<［｜<in-house>*TODO*英訳｜自動送信要求設定 R/W］*/
        uint8_t infinite_tx:        1;      /*!<［｜<in-house>*TODO*英訳｜繰り返し送信モード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RF_STATUS_CTRL_T;

/** @brief ［Type definition for @ref RADIO_RF_STATUS_ADR access｜@ref RADIO_RF_STATUS_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t set_trx:            4;      /*!<［｜<in-house>*TODO*英訳｜RF部動作状態設定 R/W］*/
        uint8_t get_trx:            4;      /*!<［｜<in-house>*TODO*英訳｜RF部動作状態表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_RF_STATUS_T;

/** @brief ［Type definition for @ref RADIO_DIO_SET_ADR access｜@ref RADIO_DIO_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dio_start:          1;      /*!<［｜<in-house>*TODO*英訳｜DIO受信データ出力開始設定 R/W］*/
        uint8_t dio_iodir_set_en:   1;      /*!<［｜<in-house>*TODO*英訳｜DIO時のIO入出力方向設定イネーブル R/W］*/
        uint8_t dio_rx_complete:    1;      /*!<［｜<in-house>*TODO*英訳｜DIO受信完了設定 R/W］*/
        uint8_t dio_iodir_set:      1;      /*!<［｜<in-house>*TODO*英訳｜DIO時のIO入出力方向設定 R/W］*/
        uint8_t txdio_ctrl:         2;      /*!<［｜<in-house>*TODO*英訳｜送信DIOモード設定 R/W］*/
        uint8_t rxdio_ctrl:         2;      /*!<［｜<in-house>*TODO*英訳｜受信DIOモード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DIO_SET_T;


/** @brief ［Type definition for @ref RADIO_INT_SOURCE_GRP1_ADR access｜@ref RADIO_INT_SOURCE_GRP1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk_done:           1;      /*!<［｜<in-house>*TODO*英訳｜クロック安定化完了割込み R/W ］*/
        uint8_t vco_cal_cmp:        1;      /*!<［｜<in-house>*TODO*英訳｜VCO キャリブレーション完了割込み R/W ］*/
        uint8_t pll_ld:             1;      /*!<［｜<in-house>*TODO*英訳｜PLL ロック外れ割込み R/W ］*/
        uint8_t rf_state_cmp:       1;      /*!<［｜<in-house>*TODO*英訳｜RF 状態遷移完了割込み R/W ］*/
        uint8_t fifo_empty:         1;      /*!<［｜<in-house>*TODO*英訳｜FIFO-Empty 割込み R/W ］*/
        uint8_t fifo_full:          1;      /*!<［｜<in-house>*TODO*英訳｜FIFO-Full 割込み R/W ］*/
        uint8_t wakeup:             1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップ割込み R/W ］*/
        uint8_t clk_cal:            1;      /*!<［｜<in-house>*TODO*英訳｜クロックキャリブレーション完了割込み R/W ］*/
    }bits;
    uint8_t byte;
}RADIO_INT_SOURCE_GRP1_T;

/** @brief ［Type definition for @ref RADIO_INT_SOURCE_GRP2_ADR access｜@ref RADIO_INT_SOURCE_GRP2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_cmp:             1;      /*!<［｜<in-house>*TODO*英訳｜受信完了割込み  R/W ］*/
        uint8_t crc_err:            1;      /*!<［｜<in-house>*TODO*英訳｜CRC エラー割込み R/W ］*/
        uint8_t diversity_cmp:      1;      /*!<［｜<in-house>*TODO*英訳｜ダイバーシティサーチ完了割込み R/W ］*/
        uint8_t rx_len_err:         1;      /*!<［｜<in-house>*TODO*英訳｜受信 Length エラー割込み R/W ］*/
        uint8_t rx_fifo_err:        1;      /*!<［｜<in-house>*TODO*英訳｜受信 FIFO アクセスエラー割込み R/W ］*/
        uint8_t sync_word:          1;      /*!<［｜<in-house>*TODO*英訳｜SyncWord 検出割込み R/W ］*/
        uint8_t cma_field:          1;      /*!<［｜<in-house>*TODO*英訳｜Field チェック割込み R/W ］*/
        uint8_t sync_err:           1;      /*!<［｜<in-house>*TODO*英訳｜Sync エラー割込み R/W ］*/
    }bits;
    uint8_t byte;
}RADIO_INT_SOURCE_GRP2_T;

/** @brief ［Type definition for @ref RADIO_INT_SOURCE_GRP3_ADR access｜@ref RADIO_INT_SOURCE_GRP3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct{
        uint8_t tx_cmp:             1;      /*!<［｜<in-house>*TODO*英訳｜送信完了割込み  R/W ］*/
        uint8_t tx_fifo_w_cmp:      1;      /*!<［｜<in-house>*TODO*英訳｜データ送信要求受付完了割込み R/W ］*/
        uint8_t cca_cmp:            1;      /*!<［｜<in-house>*TODO*英訳｜CCA 完了割込み R/W ］*/
        uint8_t tx_len_err:         1;      /*!<［｜<in-house>*TODO*英訳｜送信 Length エラー割込み R/W ］*/
        uint8_t tx_firo_err:        1;      /*!<［｜<in-house>*TODO*英訳｜送信 FIFO アクセスエラー割込み R/W ］*/
        uint8_t ch_srch_err:        1;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチエラー割込み R/W ］*/
        uint8_t gt1:                1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ1割込み R/W ］*/
        uint8_t gt2:                1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ2割込み R/W ］*/
    }bits;
    uint8_t byte;
}RADIO_INT_SOURCE_GRP3_T;

/**
 *  @brief ［Type definition for @ref RADIO_INT_SOURCE_GRP1_ADR , @ref RADIO_INT_SOURCE_GRP2_ADR , @ref RADIO_INT_SOURCE_GRP3_ADR access｜
 *          @ref RADIO_INT_SOURCE_GRP1_ADR , @ref RADIO_INT_SOURCE_GRP2_ADR , @ref RADIO_INT_SOURCE_GRP3_ADR レジスタアクセス用 型定義 ］ 
*/
typedef struct{
    RADIO_INT_SOURCE_GRP1_T grp1;           /*!<［｜<in-house>*TODO*英訳｜割込み表示  ］*/
    RADIO_INT_SOURCE_GRP2_T grp2;           /*!<［｜<in-house>*TODO*英訳｜割込み表示(受信関連) ］*/
    RADIO_INT_SOURCE_GRP3_T grp3;           /*!<［｜<in-house>*TODO*英訳｜割込み表示(送信関連) ］*/
}RADIO_INT_SOURCE_ALL_T;

/** @brief ［Type definition for @ref RADIO_INT_EN_GRP1_ADR access｜@ref RADIO_INT_EN_GRP1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct{
        uint8_t clk_done_en:        1;      /*!<［｜<in-house>*TODO*英訳｜クロック安定化完了割込み許可設定 R/W ］*/
        uint8_t vco_cal_cmp_en:     1;      /*!<［｜<in-house>*TODO*英訳｜VCO キャリブレーション完了割込み許可設定 R/W ］*/
        uint8_t pll_ld_en:          1;      /*!<［｜<in-house>*TODO*英訳｜PLL ロック外れ割込み許可設定 R/W ］*/
        uint8_t rf_state_cmp_en:    1;      /*!<［｜<in-house>*TODO*英訳｜RF 状態遷移完了割込み許可設定 R/W ］*/
        uint8_t fifo_empty_en:      1;      /*!<［｜<in-house>*TODO*英訳｜FIFO-Empty 割込み許可設定 R/W ］*/
        uint8_t fifo_full_en:       1;      /*!<［｜<in-house>*TODO*英訳｜FIFO-Full 割込み許可設定 R/W ］*/
        uint8_t wakeup_en:          1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップ割込み許可設定 R/W ］*/
        uint8_t clk_cal_en:         1;      /*!<［｜<in-house>*TODO*英訳｜クロックキャリブレーション完了割込み許可設定 R/W ］*/
    }bits;
    uint8_t byte;
}RADIO_INT_EN_GRP1_T;

/** @brief ［Type definition for @ref RADIO_INT_EN_GRP2_ADR access｜@ref RADIO_INT_EN_GRP2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_cmp_en:          1;      /*!<［｜<in-house>*TODO*英訳｜受信完了割込み許可設定  R/W ］*/
        uint8_t crc_err_en:         1;      /*!<［｜<in-house>*TODO*英訳｜CRC エラー割込み許可設定 R/W ］*/
        uint8_t diversity_cmp_en:   1;      /*!<［｜<in-house>*TODO*英訳｜ダイバーシティサーチ完了割込み許可設定 R/W ］*/
        uint8_t rx_len_err_en:      1;      /*!<［｜<in-house>*TODO*英訳｜受信 Length エラー割込み許可設定 R/W ］*/
        uint8_t rx_fifo_err_en:     1;      /*!<［｜<in-house>*TODO*英訳｜受信 FIFO アクセスエラー割込み許可設定 R/W ］*/
        uint8_t sync_word_en:       1;      /*!<［｜<in-house>*TODO*英訳｜SyncWord 検出割込み許可設定 R/W ］*/
        uint8_t cma_field_en:       1;      /*!<［｜<in-house>*TODO*英訳｜Field チェック割込み許可設定 R/W ］*/
        uint8_t sync_err_en:        1;      /*!<［｜<in-house>*TODO*英訳｜Sync エラー割込み許可設定 R/W ］*/
    }bits;
    uint8_t byte;
}RADIO_INT_EN_GRP2_T;

/** @brief ［Type definition for @ref RADIO_INT_EN_GRP3_ADR access｜@ref RADIO_INT_EN_GRP3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_cmp_en:          1;      /*!<［｜<in-house>*TODO*英訳｜送信完了割込み許可設定 R/W ］*/
        uint8_t tx_fifo_w_cmp_en:   1;      /*!<［｜<in-house>*TODO*英訳｜データ送信要求受付完了割込み許可設定 R/W ］*/
        uint8_t cca_cmp_en:         1;      /*!<［｜<in-house>*TODO*英訳｜CCA 完了割込み許可設定 R/W ］*/
        uint8_t tx_len_err_en:      1;      /*!<［｜<in-house>*TODO*英訳｜送信 Length エラー割込み許可設定 R/W ］*/
        uint8_t tx_firo_err_en:     1;      /*!<［｜<in-house>*TODO*英訳｜送信 FIFO アクセスエラー割込み許可設定 R/W ］*/
        uint8_t ch_srch_err_en:     1;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチエラー割り込み許可設定 R/W ］*/
        uint8_t gt1_en:             1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ1割込み許可設定 R/W ］*/
        uint8_t gt2_en:             1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ2割込み許可設定 R/W ］*/
    }bits;
    uint8_t byte;
}RADIO_INT_EN_GRP3_T;

/** @brief ［Type definition for @ref RADIO_CRC_ERR_H_ADR access｜@ref RADIO_CRC_ERR_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_error_h:        1;      /*!<［｜<in-house>*TODO*英訳｜17th CRCエラー表示 R］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t crc_int_set:        1;      /*!<［｜<in-house>*TODO*英訳｜CRCチェック割込み選択設定 R/W］*/
        uint8_t crc_len2:           2;      /*!<［｜<in-house>*TODO*英訳｜CRC長設定2 R/W］*/
        uint8_t crc_len2_en:        1;      /*!<［｜<in-house>*TODO*英訳｜CRC長設定2イネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_ERR_H_T;

/** @brief ［Type definition for @ref RADIO_CRC_ERR_M_ADR access｜@ref RADIO_CRC_ERR_M_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_error_m:        8;      /*!<［｜<in-house>*TODO*英訳｜9~16th CRCエラー表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_ERR_M_T;

/** @brief ［Type definition for @ref RADIO_CRC_ERR_L_ADR access｜@ref RADIO_CRC_ERR_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t crc_error_l:        8;      /*!<［｜<in-house>*TODO*英訳｜1~8th CRCエラー表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_CRC_ERR_L_T;

/** @brief ［Type definition for @ref RADIO_STATE_CLR_ADR access｜@ref RADIO_STATE_CLR_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t state_clr_0:        1;      /*!<［｜<in-house>*TODO*英訳｜送信FIFOポインタクリア R/W］*/
        uint8_t state_clr_1:        1;      /*!<［｜<in-house>*TODO*英訳｜受信FIFOポインタクリア R/W］*/
        uint8_t state_clr_2:        1;      /*!<［｜<in-house>*TODO*英訳｜PHYステートクリア R/W］*/
        uint8_t state_clr_3:        1;      /*!<［｜<in-house>*TODO*英訳｜ダイバーシティステートクリア R/W］*/
        uint8_t state_clr_4:        1;      /*!<［｜<in-house>*TODO*英訳｜アドレスチェックカウンタクリア R/W］*/
        uint8_t state_clr_5:        1;      /*!<［｜<in-house>*TODO*英訳｜チャネルサーチステートクリア R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t state_clr_en:       1;      /*!<［｜<in-house>*TODO*英訳｜ステートクリアイネーブル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_STATE_CLR_T;

/** @brief ［Type definition for @ref RADIO_TXFIFO_THRH_ADR access｜@ref RADIO_TXFIFO_THRH_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t txfifo_thrh:        6;      /*!<［｜<in-house>*TODO*英訳｜送信FIFOのFullレベル設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t txfifo_thrh_en:     1;      /*!<［｜<in-house>*TODO*英訳｜送信FIFOのFullレベルイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXFIFO_THRH_T;

/** @brief ［Type definition for @ref RADIO_TXFIFO_THRL_ADR access｜@ref RADIO_TXFIFO_THRL_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t txfifo_thrl:        6;      /*!<［｜<in-house>*TODO*英訳｜送信FIFOのEmptyレベル設定およびFAST_TXモード時の送信トリガレベル設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t txfifo_thrl_en:     1;      /*!<［｜<in-house>*TODO*英訳｜送信FIFOのEmptyレベルイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXFIFO_THRL_T;

/** @brief ［Type definition for @ref RADIO_RXFIFO_THRH_ADR access｜@ref RADIO_RXFIFO_THRH_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t rxfifo_thrh:        6;      /*!<［｜<in-house>*TODO*英訳｜受信FIFOのFullレベル設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t rxfifo_thrh_en:     1;      /*!<［｜<in-house>*TODO*英訳｜受信FIFOのFullレベルイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RXFIFO_THRH_T;

/** @brief ［Type definition for @ref RADIO_RXFIFO_THRL_ADR access｜@ref RADIO_RXFIFO_THRL_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t rxfifo_thrl:        6;      /*!<［｜<in-house>*TODO*英訳｜受信FIFOのEmptyレベル設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t rxfifo_thrl_en:     1;      /*!<［｜<in-house>*TODO*英訳｜受信FIFOのEmptyレベルイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RXFIFO_THRL_T;

/** @brief ［Type definition for @ref RADIO_C_CHECK_CTRL_B0_ADR access｜@ref RADIO_C_CHECK_CTRL_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_en:         5;      /*!<［｜<in-house>*TODO*英訳｜コントロールフィールドパターン1~5チェックイネーブル R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t ca_int_ctrl:        1;      /*!<［｜<in-house>*TODO*英訳｜Fieldチェック割込み設定 R/W］*/
        uint8_t ca_rxd_clr:         1;      /*!<［｜<in-house>*TODO*英訳｜Field不一致時の受信データ処理設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_CHECK_CTRL_B0_T;

/** @brief ［Type definition for @ref RADIO_M_CHECK_CTRL_B0_ADR access｜@ref RADIO_M_CHECK_CTRL_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_code1_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン1チェックイネーブル R/W］*/
        uint8_t m_field_code2_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン2チェックイネーブル R/W］*/
        uint8_t m_field_code3_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン3チェックイネーブル R/W］*/
        uint8_t m_field_code4_en:   1;      /*!<［｜<in-house>*TODO*英訳｜マニュファクチャーIDフィールドパターン4チェックイネーブル R/W］*/
        uint8_t rcv_cont_sel:       2;      /*!<［｜<in-house>*TODO*英訳｜動作継続タイマ満了時の受信継続条件設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_M_CHECK_CTRL_B0_T;

/** @brief ［Type definition for @ref RADIO_A_CHECK_CTRL_B0_ADR access｜@ref RADIO_A_CHECK_CTRL_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code1_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン1チェックイネーブル R/W］*/
        uint8_t a_field_code2_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン2チェックイネーブル R/W］*/
        uint8_t a_field_code3_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン3チェックイネーブル R/W］*/
        uint8_t a_field_code4_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン4チェックイネーブル R/W］*/
        uint8_t a_field_code5_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン5チェックイネーブル R/W］*/
        uint8_t a_field_code6_en:   1;      /*!<［｜<in-house>*TODO*英訳｜アドレスフィールドパターン6チェックイネーブル R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_CHECK_CTRL_B0_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_CODE1_B0_ADR access｜@ref RADIO_C_FIELD_CODE1_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_code1:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_CODE1_B0_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_CODE2_B0_ADR access｜@ref RADIO_C_FIELD_CODE2_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_code2:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_CODE2_B0_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_CODE3_B0_ADR access｜@ref RADIO_C_FIELD_CODE3_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_code3:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field 設定 コード#3 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_CODE3_B0_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_CODE4_B0_ADR access｜@ref RADIO_C_FIELD_CODE4_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_code4:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field設定 コード#4 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_CODE4_B0_T;

/** @brief ［Type definition for @ref RADIO_C_FIELD_CODE5_B0_ADR access｜@ref RADIO_C_FIELD_CODE5_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t c_field_code5:      8;      /*!<［｜<in-house>*TODO*英訳｜C-field設定 コード#5 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_C_FIELD_CODE5_B0_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_CODE1_B0_ADR access｜@ref RADIO_M_FIELD_CODE1_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_code1:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 1stバイト設定 コード#1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_CODE1_B0_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_CODE2_B0_ADR access｜@ref RADIO_M_FIELD_CODE2_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_code2:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 1stバイト設定 コード#2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_CODE2_B0_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_CODE3_B0_ADR access｜@ref RADIO_M_FIELD_CODE3_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_code3:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定 コード#1 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_CODE3_B0_T;

/** @brief ［Type definition for @ref RADIO_M_FIELD_CODE4_B0_ADR access｜@ref RADIO_M_FIELD_CODE4_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t m_field_code4:      8;      /*!<［｜<in-house>*TODO*英訳｜M-field 2ndバイト設定 コード#2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_M_FIELD_CODE4_B0_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_CODE1_B0_ADR access｜@ref RADIO_A_FIELD_CODE1_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code1:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(1バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_CODE1_B0_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_CODE2_B0_ADR access｜@ref RADIO_A_FIELD_CODE2_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code2:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(2バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_CODE2_B0_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_CODE3_B0_ADR access｜@ref RADIO_A_FIELD_CODE3_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code3:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(3バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_CODE3_B0_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_CODE4_B0_ADR access｜@ref RADIO_A_FIELD_CODE4_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code4:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(4バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_CODE4_B0_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_CODE5_B0_ADR access｜@ref RADIO_A_FIELD_CODE5_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code5:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(5バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_CODE5_B0_T;

/** @brief ［Type definition for @ref RADIO_A_FIELD_CODE6_B0_ADR access｜@ref RADIO_A_FIELD_CODE6_B0_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t a_field_code6:      8;      /*!<［｜<in-house>*TODO*英訳｜A-field設定(6バイト目) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_A_FIELD_CODE6_B0_T;

/** @brief ［Type definition for @ref RADIO_SLEEP_WU_SET_ADR access｜@ref RADIO_SLEEP_WU_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sleep_en:           1;      /*!<［｜<in-house>*TODO*英訳｜SLEEPモード制御 R/W］*/
        uint8_t pdn_en:             1;      /*!<［｜<in-house>*TODO*英訳｜SLEEP時の電源制御イネーブル R/W］*/
        uint8_t wut_clk_source:     1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップタイマ用クロックソース設定 R/W］*/
        uint8_t rcosc_mode:         1;      /*!<［｜<in-house>*TODO*英訳｜RC発振回路動作モード設定 R/W］*/
        uint8_t wakeup_en:          1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップイネーブル R/W］*/
        uint8_t wu_duration_en:     1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップ後の動作継続タイマイネーブル設定 R/W］*/
        uint8_t wakeup_mode:        1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップ後の動作設定 R/W］*/
        uint8_t wut_1shot_mode:     1;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップタイマ動作モード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SLEEP_WU_SET_T;

/** @brief ［Type definition for @ref RADIO_WUT_CLK_SET_ADR access｜@ref RADIO_WUT_CLK_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t wut_clk_set:        4;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップタイマ分周設定 R/W］*/
        uint8_t wud_clk_set:        4;      /*!<［｜<in-house>*TODO*英訳｜動作継続タイマ分周設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_WUT_CLK_SET_T;

/** @brief ［Type definition for @ref RADIO_WUT_INTERVAL_H_ADR access｜@ref RADIO_WUT_INTERVAL_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t timer_interval_h:   8;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップタイマ間隔設定(上位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_WUT_INTERVAL_H_T;

/** @brief ［Type definition for @ref RADIO_WUT_INTERVAL_L_ADR access｜@ref RADIO_WUT_INTERVAL_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t timer_interval_l:   8;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップタイマ間隔設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_WUT_INTERVAL_L_T;

/** @brief ［Type definition for @ref RADIO_WU_DURATION_ADR access｜@ref RADIO_WU_DURATION_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t wu_duration:        8;      /*!<［｜<in-house>*TODO*英訳｜ウェイクアップ後の動作継続タイマ設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_WU_DURATION_T;

/** @brief ［Type definition for @ref RADIO_GT_SET_ADR access｜@ref RADIO_GT_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gt1_start:          1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ1実行設定 R/W］*/
        uint8_t gt1_clk_source:     1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ1クロックソース設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t gt2_start:          1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ2実行設定 R/W］*/
        uint8_t gt2_clk_source:     1;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ2クロックソース設定 R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_GT_SET_T;

/** @brief ［Type definition for @ref RADIO_GT_CLK_SET_ADR access｜@ref RADIO_GT_CLK_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gt1_clk_set:        4;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ用クロック1分周設定 R/W］*/
        uint8_t gt2_clk_set:        4;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ用クロック2分周設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GT_CLK_SET_T;

/** @brief ［Type definition for @ref RADIO_GT1_TIMER_ADR access｜@ref RADIO_GT1_TIMER_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gt1_interval:       8;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ1間隔設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GT1_TIMER_T;

/** @brief ［Type definition for @ref RADIO_GT2_TIMER_ADR access｜@ref RADIO_GT2_TIMER_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gt2_interval:       8;      /*!<［｜<in-house>*TODO*英訳｜汎用タイマ2間隔設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GT2_TIMER_T;

/** @brief ［Type definition for @ref RADIO_CCA_IGNORE_LVL_ADR access｜@ref RADIO_CCA_IGNORE_LVL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_th_h:           8;      /*!<［｜<in-house>*TODO*英訳｜CCAの移動平均判定から除外するEDレベル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CCA_IGNORE_LVL_T;

/** @brief ［Type definition for @ref RADIO_CCA_LVL_ADR access｜@ref RADIO_CCA_LVL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_th:             8;      /*!<［｜<in-house>*TODO*英訳｜CCA閾値レベル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CCA_LVL_T;

/** @brief ［Type definition for @ref RADIO_CCA_ABORT_ADR access｜@ref RADIO_CCA_ABORT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_abort:          8;      /*!<［｜<in-house>*TODO*英訳｜CCA強制終了時間設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CCA_ABORT_T;

/** @brief ［Type definition for @ref RADIO_CCA_CTRL_ADR access｜@ref RADIO_CCA_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_rslt:           2;      /*!<［｜<in-house>*TODO*英訳｜CCA結果 R］*/
        uint8_t cca_abort_en:       1;      /*!<［｜<in-house>*TODO*英訳｜CCA強制終了設定 R/W］*/
        uint8_t fast_det_mode_en:   1;      /*!<［｜<in-house>*TODO*英訳｜高速電波チェックモード設定 R/W］*/
        uint8_t cca_en:             1;      /*!<［｜<in-house>*TODO*英訳｜CCA実行命令 R/W］*/
        uint8_t cca_cpu_en:         1;      /*!<［｜<in-house>*TODO*英訳｜CCA無限実行モード設定 R/W］*/
        uint8_t cca_idle_en:        1;      /*!<［｜<in-house>*TODO*英訳｜CCAアイドル検出モード設定 R/W］*/
        uint8_t cca_stop:           1;      /*!<［｜<in-house>*TODO*英訳｜CCA無限実行終了設定(1で停止します) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CCA_CTRL_T;

/** @brief ［Type definition for @ref RADIO_ED_RSLT_ADR access｜@ref RADIO_ED_RSLT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ed_value:           8;      /*!<［｜<in-house>*TODO*英訳｜ED値表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_ED_RSLT_T;

/** @brief ［Type definition for @ref RADIO_IDLE_WAIT_H_ADR access｜@ref RADIO_IDLE_WAIT_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_idle_cnt_i_h:   2;      /*!<［｜<in-house>*TODO*英訳｜IDLE判定の最大待ち時間設定(上位バイト) R/W］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_IDLE_WAIT_H_T;

/** @brief ［Type definition for @ref RADIO_IDLE_WAIT_L_ADR access｜@ref RADIO_IDLE_WAIT_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_idle_cnt_i_l:   8;      /*!<［｜<in-house>*TODO*英訳｜IDLE判定の最大待ち時間設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IDLE_WAIT_L_T;

/** @brief ［Type definition for @ref RADIO_CCA_PROG_H_ADR access｜@ref RADIO_CCA_PROG_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_idle_cnt_h:     2;      /*!<［｜<in-house>*TODO*英訳｜CCA時のIDLE判定経過時間表示(上位バイト) R］*/
        uint8_t reserved0:          6;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_CCA_PROG_H_T;

/** @brief ［Type definition for @ref RADIO_CCA_PROG_L_ADR access｜@ref RADIO_CCA_PROG_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t cca_idle_cnt_l:     8;      /*!<［｜<in-house>*TODO*英訳｜CCA時のIDLE判定経過時間表示(下位バイト) R］*/
    }bits;
    uint8_t byte;
}RADIO_CCA_PROG_L_T;

/** @brief ［Type definition for @ref RADIO_PREAMBLE_SET_ADR access｜@ref RADIO_PREAMBLE_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pr_pat:             4;      /*!<［｜<in-house>*TODO*英訳｜プリアンブルパターン設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t cca_int_sel:        2;      /*!<［｜<in-house>*TODO*英訳｜CCA割り込み選択設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PREAMBLE_SET_T;

/** @brief ［Type definition for @ref RADIO_VCO_VTRSLT_ADR access｜@ref RADIO_VCO_VTRSLT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vtune_comp_l:       1;      /*!<［｜<in-house>*TODO*英訳｜VCO調整電圧下限閾値比較結果表示 R］*/
        uint8_t vtune_comp_h:       1;      /*!<［｜<in-house>*TODO*英訳｜VCO調整電圧上限閾値比較結果表示 R］*/
        uint8_t vtune_int_enb:      1;      /*!<［｜<in-house>*TODO*英訳｜VCO調整電圧範囲外検出割込み通知設定 R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_VTRSLT_T;

/** @brief ［Type definition for @ref RADIO_ED_CTRL_ADR access｜@ref RADIO_ED_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ed_avg:             3;      /*!<［｜<in-house>*TODO*英訳｜ED値算出時の平均回数設定 R/W］*/
        uint8_t ed_sel:             1;      /*!<［｜<in-house>*TODO*英訳｜ED表示設定 R/W］*/
        uint8_t ed_done:         1;      /*!<［｜<in-house>*TODO*英訳｜ED値算出完了フラグ R］*/
        uint8_t cca_ed_sel:         1;      /*!<［｜<in-house>*TODO*英訳｜高速電波チェック時のED値算出信号選択設定 R/W］*/
        uint8_t ccadone_mode:       1;      /*!<［｜<in-house>*TODO*英訳｜高速電波チェック時のRF状態設定 R/W］*/
        uint8_t ed_calc_en:         1;      /*!<［｜<in-house>*TODO*英訳｜ED値算出イネーブル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_ED_CTRL_T;

/** @brief ［Type definition for @ref RADIO_TXPR_LEN_H_ADR access｜@ref RADIO_TXPR_LEN_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txpr_len_h:         8;      /*!<［｜<in-house>*TODO*英訳｜送信プリアンブル長設定(上位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXPR_LEN_H_T;

/** @brief ［Type definition for @ref RADIO_TXPR_LEN_L_ADR access｜@ref RADIO_TXPR_LEN_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txpr_len_l:         8;      /*!<［｜<in-house>*TODO*英訳｜送信プリアンブル長設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TXPR_LEN_L_T;

/** @brief ［Type definition for @ref RADIO_POSTAMBLE_SET_ADR access｜@ref RADIO_POSTAMBLE_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t postamble_en:       1;      /*!<［｜<in-house>*TODO*英訳｜ポストアンブルイネーブル R/W］*/
        uint8_t postamble_pat:      3;      /*!<［｜<in-house>*TODO*英訳｜ポストアンブルパターン設定 R/W］*/
        uint8_t postamble_len:      3;      /*!<［｜<in-house>*TODO*英訳｜ポストアンブル長設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_POSTAMBLE_SET_T;

/** @brief ［Type definition for @ref RADIO_SYNC_CONDITION1_ADR access｜@ref RADIO_SYNC_CONDITION1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rxpr_len:           6;      /*!<［｜<in-house>*TODO*英訳｜受信時のプリアンブル比較長設定(設定範囲:0～32、単位:ビット) R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t sync_ed_en:         1;      /*!<［｜<in-house>*TODO*英訳｜ED値を使用した同期判定のイネーブル R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_CONDITION1_T;

/** @brief ［Type definition for @ref RADIO_SYNC_CONDITION2_ADR access｜@ref RADIO_SYNC_CONDITION2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sync_ed_th:         8;      /*!<［｜<in-house>*TODO*英訳｜同期判定時のED閾値設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_CONDITION2_T;

/** @brief ［Type definition for @ref RADIO_SYNC_CONDITION3_ADR access｜@ref RADIO_SYNC_CONDITION3_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pb_rcv:             4;      /*!<［｜<in-house>*TODO*英訳｜SyncWord検出時の誤り許容ビット数設定(設定範囲0～15) R/W］*/
        uint8_t sw_rcv:             4;      /*!<［｜<in-house>*TODO*英訳｜プリアンブル検出時の誤り許容ビット数設定(設定範囲0～15) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SYNC_CONDITION3_T;

/** @brief ［Type definition for @ref RADIO_2DIV_CTRL_ADR access｜@ref RADIO_2DIV_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t two_div_en:         1;      /*!<［｜<in-house>*TODO*英訳｜アンテナダイバーシティ設定 R/W］*/
        uint8_t two_port_sw:        1;      /*!<［｜<in-house>*TODO*英訳｜アンテナスイッチ設定 R/W］*/
        uint8_t inv_trx_sw:         1;      /*!<［｜<in-house>*TODO*英訳｜TRX_SW極性設定 R/W］*/
        uint8_t inv_ant_sw:         1;      /*!<［｜<in-house>*TODO*英訳｜ANT_SW極性設定 R/W］*/
        uint8_t ant_ctrl0:          1;      /*!<［｜<in-house>*TODO*英訳｜ANT制御ビット0 R/W］*/
        uint8_t ant_ctrl1:          1;      /*!<［｜<in-house>*TODO*英訳｜ANT制御ビット1 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_CTRL_T;

/** @brief ［Type definition for @ref RADIO_2DIV_RSLT_ADR access｜@ref RADIO_2DIV_RSLT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t two_div_rslt:       2;      /*!<［｜<in-house>*TODO*英訳｜アンテナダイバーシティ結果表示 R］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
        uint8_t two_div_done:       1;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_2DIV_RSLT_T;

/** @brief ［Type definition for @ref RADIO_ANT1_ED_ADR access｜@ref RADIO_ANT1_ED_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ant1_ed:            8;      /*!<［｜<in-house>*TODO*英訳｜アンテナ1の取得ED値 R］*/
    }bits;
    uint8_t byte;
}RADIO_ANT1_ED_T;

/** @brief ［Type definition for @ref RADIO_ANT2_ED_ADR access｜@ref RADIO_ANT2_ED_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ant2_ed:            8;      /*!<［｜<in-house>*TODO*英訳｜アンテナ2の取得ED値 R］*/
    }bits;
    uint8_t byte;
}RADIO_ANT2_ED_T;

/** @brief ［Type definition for @ref RADIO_ANT_CTRL_ADR access｜@ref RADIO_ANT_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_ant_en:          1;      /*!<［｜<in-house>*TODO*英訳｜送信時のアンテナ設定イネーブル R/W］*/
        uint8_t tx_ant:             1;      /*!<［｜<in-house>*TODO*英訳｜送信時のアンテナ設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t rx_ant_en:          1;      /*!<［｜<in-house>*TODO*英訳｜受信時のアンテナ設定イネーブル R/W］*/
        uint8_t rx_ant:             1;      /*!<［｜<in-house>*TODO*英訳｜受信時のアンテナ設定 R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_ANT_CTRL_T;

/** @brief ［Type definition for @ref RADIO_MON_CTRL_ADR access｜@ref RADIO_MON_CTRL_ADR レジスタアクセス用  型定義］*/
typedef union{
    struct {
        uint8_t dmon_set:           4;      /*!<［｜<in-house>*TODO*英訳｜デジタルモニタ出力信号選択設定 R/W］*/
        uint8_t dmon_set2:          2;      /*!<［｜<in-house>*TODO*英訳｜デジタルモニタ出力信号選択設定 R/W］*/
        uint8_t fifomode_mon:       1;      /*!<［｜<in-house>*TODO*英訳｜FIFOモードモニタ設定 R/W］*/
        uint8_t ber_mode:           1;      /*!<［｜<in-house>*TODO*英訳｜BER測定モード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_MON_CTRL_T;

/** @brief ［Type definition for @ref RADIO_GPIO0_CTRL_ADR access｜@ref RADIO_GPIO0_CTRL_ADR レジスタアクセス用  型定義］*/
typedef union{
    struct {
        uint8_t gpio0_ctrl:         4;      /*!<［｜<in-house>*TODO*英訳｜GPIO0入出力信号選択設定 R/W］*/
        uint8_t gpio0_fout_en:      1;      /*!<［｜<in-house>*TODO*英訳｜GPIO0強制出力イネーブル R/W］*/
        uint8_t gpio0_fout:         1;      /*!<［｜<in-house>*TODO*英訳｜GPIO0強制出力設定 R/W］*/
        uint8_t gpio0_od:           1;      /*!<［｜<in-house>*TODO*英訳｜GPIO0 出力OpenDrain設定 R/W］*/
        uint8_t gpio0_inv:          1;      /*!<［｜<in-house>*TODO*英訳｜GPIO0 出力信号極性設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GPIO0_CTRL_T;

/** @brief ［Type definition for @ref RADIO_GPIO1_CTRL_ADR access｜@ref RADIO_GPIO1_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gpio1_ctrl:         4;      /*!<［｜<in-house>*TODO*英訳｜GPIO1入出力信号選択設定 R/W］*/
        uint8_t gpio1_fout_en:      1;      /*!<［｜<in-house>*TODO*英訳｜GPIO1強制出力イネーブル R/W］*/
        uint8_t gpio1_fout:         1;      /*!<［｜<in-house>*TODO*英訳｜GPIO1強制出力設定 R/W］*/
        uint8_t gpio1_od:           1;      /*!<［｜<in-house>*TODO*英訳｜GPIO1 出力OpenDrain設定 R/W］*/
        uint8_t gpio1_inv:          1;      /*!<［｜<in-house>*TODO*英訳｜GPIO1 出力信号極性設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GPIO1_CTRL_T;

/** @brief ［Type definition for @ref RADIO_GPIO2_CTRL_ADR access｜@ref RADIO_GPIO2_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gpio2_ctrl:         4;      /*!<［｜<in-house>*TODO*英訳｜GPIO2入出力信号選択設定 R/W］*/
        uint8_t gpio2_fout_en:      1;      /*!<［｜<in-house>*TODO*英訳｜GPIO2強制出力イネーブル R/W］*/
        uint8_t gpio2_fout:         1;      /*!<［｜<in-house>*TODO*英訳｜GPIO2強制出力設定 R/W］*/
        uint8_t gpio2_od:           1;      /*!<［｜<in-house>*TODO*英訳｜GPIO2 出力OpenDrain設定 R/W］*/
        uint8_t gpio2_inv:          1;      /*!<［｜<in-house>*TODO*英訳｜GPIO2 出力信号極性設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GPIO2_CTRL_T;

/** @brief ［Type definition for @ref RADIO_GPIO3_CTRL_ADR access｜@ref RADIO_GPIO3_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gpio3_ctrl:         4;      /*!<［｜<in-house>*TODO*英訳｜GPIO3 出力信号極性設定 R/W］*/
        uint8_t gpio3_fout_en:      1;      /*!<［｜<in-house>*TODO*英訳｜GPIO3 出力OpenDrain設定 R/W］*/
        uint8_t gpio3_fout:         1;      /*!<［｜<in-house>*TODO*英訳｜GPIO3強制出力設定 R/W］*/
        uint8_t gpio3_od:           1;      /*!<［｜<in-house>*TODO*英訳｜GPIO3強制出力イネーブル R/W］*/
        uint8_t gpio3_inv:          1;      /*!<［｜<in-house>*TODO*英訳｜GPIO3入出力信号選択設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GPIO3_CTRL_T;

/** @brief ［Type definition for @ref RADIO_EXTCLK_CTRL_ADR access｜@ref RADIO_EXTCLK_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t extclk_ctrl:        4;      /*!<［｜<in-house>*TODO*英訳｜EXT_CLK入出力信号選択設定 R/W］*/
        uint8_t extclk_fout_en:     1;      /*!<［｜<in-house>*TODO*英訳｜EXT_CLK強制出力イネーブル R/W］*/
        uint8_t extclk_fout:        1;      /*!<［｜<in-house>*TODO*英訳｜EXT_CLK強制出力値設定 R/W］*/
        uint8_t extclk_od:          1;      /*!<［｜<in-house>*TODO*英訳｜EXT_CLK出力OpenDrain設定 R/W］*/
        uint8_t extclk_inv:         1;      /*!<［｜<in-house>*TODO*英訳｜EXT_CLK出力信号極性設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_EXTCLK_CTRL_T;

/** @brief ［Type definition for @ref RADIO_GPIO4_CTRL_ADR access｜@ref RADIO_GPIO4_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t gpio4_ctrl:         4;      /*!<［｜<in-house>*TODO*英訳｜GPIO4入出力信号選択設定 R/W］*/
        uint8_t gpio4_fout_en:      1;      /*!<［｜<in-house>*TODO*英訳｜GPIO4強制出力イネーブル R/W］*/
        uint8_t gpio4_fout:         1;      /*!<［｜<in-house>*TODO*英訳｜GPIO4強制出力値設定 R/W］*/
        uint8_t gpio4_od:           1;      /*!<［｜<in-house>*TODO*英訳｜GPIO4出力OpenDrain設定 R/W］*/
        uint8_t gpio4_inv:          1;      /*!<［｜<in-house>*TODO*英訳｜GPIO4出力信号極性設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_GPIO4_CTRL_T;

/** @brief ［Type definition for @ref RADIO_SPI_EXT_PA_CTRL_ADR access｜@ref RADIO_SPI_EXT_PA_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t ext_pa_en:          1;      /*!<［｜<in-house>*TODO*英訳｜外部PA制御信号の制御設定イネーブル R/W］*/
        uint8_t ext_pa_cnt:         1;      /*!<［｜<in-house>*TODO*英訳｜外部PA制御信号の制御タイミング設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t sdi_cfg:            1;      /*!<［｜<in-house>*TODO*英訳｜SDI端子(ピン#15)の入出力信号選択設定 R/W］*/
        uint8_t sdo_cfg:            1;      /*!<［｜<in-house>*TODO*英訳｜SDO端子(ピン#12)の入出力信号選択設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t sdo_od:             1;      /*!<［｜<in-house>*TODO*英訳｜SDO出力OpenDrain設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_SPI_EXT_PA_CTRL_T;

/** @brief ［Type definition for @ref RADIO_CHFIL_BW_ADR access｜@ref RADIO_CHFIL_BW_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t chfil_bw:           7;      /*!<［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅調整設定 R/W］*/
        uint8_t chfil_wide_set:     1;      /*!<［｜<in-house>*TODO*英訳｜チャネルフィルタ広帯域設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CHFIL_BW_T;

/** @brief ［Type definition for @ref RADIO_DC_I_ADJ_H_ADR access｜@ref RADIO_DC_I_ADJ_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dc_i_adj_h:         6;      /*!<［｜<in-house>*TODO*英訳｜I相DCオフセット調整設定 R/W］*/
        uint8_t dc_adj_hold:        1;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット補正ホールド設定 R/W］*/
        uint8_t dc_adj_set:         1;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット補正設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DC_I_ADJ_H_T;

/** @brief ［Type definition for @ref RADIO_DC_I_ADJ_L_ADR access｜@ref RADIO_DC_I_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dc_i_adj_l:         8;      /*!<［｜<in-house>*TODO*英訳｜I相DCオフセット調整設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DC_I_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_DC_Q_ADJ_H_ADR access｜@ref RADIO_DC_Q_ADJ_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dc_q_adj_h:         6;      /*!<［｜<in-house>*TODO*英訳｜Q相DCオフセット調整設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜ R］*/
    }bits;
    uint8_t byte;
}RADIO_DC_Q_ADJ_H_T;

/** @brief ［Type definition for @ref RADIO_DC_Q_ADJ_L_ADR access｜@ref RADIO_DC_Q_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dc_q_adj_l:         8;      /*!<［｜<in-house>*TODO*英訳｜Q相DCオフセット調整設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DC_Q_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_DC_FIL_ADJ_ADR access｜@ref RADIO_DC_FIL_ADJ_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dc_fil_sel:         3;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット調整用フィルタ設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t dc_fil_on:          1;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット調整フィルタイネーブル設定 R/W］*/
        uint8_t dc_fil_mode:        1;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット調整フィルタモード設定 R/W］*/
        uint8_t dc_fil_adj2:        2;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット調整用フィルタ設定2 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_DC_FIL_ADJ_T;

/** @brief ［Type definition for @ref RADIO_IQ_MAG_ADJ_H_ADR access｜@ref RADIO_IQ_MAG_ADJ_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_mag_adj_h:       4;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の振幅調整設定(上位4ビット) R/W］*/
        uint8_t iq_adj_start:       1;      /*!<［｜<in-house>*TODO*英訳｜IQ自動調整実行 R/W］*/
        uint8_t local_sel:          1;      /*!<［｜<in-house>*TODO*英訳｜受信ローカル周波数設定 R/W］*/
        uint8_t iq_adj_rslt:        1;      /*!<［｜<in-house>*TODO*英訳｜IQ自動調整ステータス表示 R］*/
        uint8_t iq_adj_done:        1;      /*!<［｜<in-house>*TODO*英訳｜IQ自動調整完了表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_MAG_ADJ_H_T;

/** @brief ［Type definition for @ref RADIO_IQ_MAG_ADJ_L_ADR access｜@ref RADIO_IQ_MAG_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_mag_adj_l:       8;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の振幅調整設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_MAG_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_IQ_PHASE_ADJ_H_ADR access｜@ref RADIO_IQ_PHASE_ADJ_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_phase_adj_h:     3;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の位相調整設定(上位3ビット) R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t iq_phase_sign:      1;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の位相調整符号ビット R/W］*/
        uint8_t reserved1:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_PHASE_ADJ_H_T;

/** @brief ［Type definition for @ref RADIO_IQ_PHASE_ADJ_L_ADR access｜@ref RADIO_IQ_PHASE_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_phase_adj_l:     8;      /*!<［｜<in-house>*TODO*英訳｜IQ信号の位相調整設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_PHASE_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_IQ_ADJ_WAIT_ADR access｜@ref RADIO_IQ_ADJ_WAIT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_adj_wait:        2;      /*!<［｜<in-house>*TODO*英訳｜IQ自動調整用RSSI取得ウェイト時間設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t iq_adj_mode:        1;      /*!<［｜<in-house>*TODO*英訳｜IQ自動調整モード設定 R/W］*/
        uint8_t reserved1:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_ADJ_WAIT_T;

/** @brief ［Type definition for @ref RADIO_IQ_ADJ_TARGET_ADR access｜@ref RADIO_IQ_ADJ_TARGET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t iq_adj_target:      8;      /*!<［｜<in-house>*TODO*英訳｜IQ自動調整用RSSI判定閾値 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IQ_ADJ_TARGET_T;

/** @brief ［Type definition for @ref RADIO_DEC_GAIN_ADR access｜@ref RADIO_DEC_GAIN_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dec_gain:           5;      /*!<［｜<in-house>*TODO*英訳｜デシメーションゲイン設定 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DEC_GAIN_T;

/** @brief ［Type definition for @ref RADIO_IF_FREQ_ADR access｜@ref RADIO_IF_FREQ_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t if_freq:            4;      /*!<［｜<in-house>*TODO*英訳｜IF周波数選択 R/W］*/
        uint8_t if_freq_cca:        4;      /*!<［｜<in-house>*TODO*英訳｜CCA時のIF周波数選択 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_IF_FREQ_T;

/** @brief ［Type definition for @ref RADIO_OSC_ADJ1_ADR access｜@ref RADIO_OSC_ADJ1_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t osc_adj_corse_xi:   4;      /*!<［｜<in-house>*TODO*英訳｜XI容量負荷粗調整 約0.7pF/step R/W］*/
        uint8_t osc_adj_corse_xo:   4;      /*!<［｜<in-house>*TODO*英訳｜XO容量負荷粗調整 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_OSC_ADJ1_T;

/** @brief ［Type definition for @ref RADIO_OSC_ADJ2_ADR access｜@ref RADIO_OSC_ADJ2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t osc_adj_fine:       8;      /*!<［｜<in-house>*TODO*英訳｜容量負荷微調整 約0.02pF/step (調整範囲 0x00～0xFF) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_OSC_ADJ2_T;

/** @brief ［Type definition for @ref RADIO_FIELD_CHECK_RSLT_ADR access｜@ref RADIO_FIELD_CHECK_RSLT_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t field_check_rslt1:  1;      /*!<［｜<in-house>*TODO*英訳｜フィールドチェック結果(パターン 1)表示 R］*/
        uint8_t field_check_rslt2:  1;      /*!<［｜<in-house>*TODO*英訳｜フィールドチェック結果(パターン 2)表示 R］*/
        uint8_t field_check_rslt3:  1;      /*!<［｜<in-house>*TODO*英訳｜フィールドチェック結果(パターン 3)表示 R］*/
        uint8_t ack_req_det:        1;      /*!<［｜<in-house>*TODO*英訳｜IEEE802.15.4g パケット受信の ACK 要求ビット検出表示 R］*/
        uint8_t reserved:           4;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FIELD_CHECK_RSLT_T;

/** @brief ［Type definition for @ref RADIO_OSC_ADJ4_ADR access｜@ref RADIO_OSC_ADJ4_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t osc_start_set:      1;      /*!<［｜<in-house>*TODO*英訳｜OSC起動モード設定 R/W］*/
        uint8_t reserved1:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_OSC_ADJ4_T;

/** @brief ［Type definition for @ref RADIO_RSSI_ADJ_ADR access｜@ref RADIO_RSSI_ADJ_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rssi_adj:           6;      /*!<［｜<in-house>*TODO*英訳｜RSSI補正値設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
        uint8_t rssi_add:           1;      /*!<［｜<in-house>*TODO*英訳｜RSSI調整 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RSSI_ADJ_T;

/** @brief ［Type definition for @ref RADIO_PA_REG_ADJ_H_ADR access｜@ref RADIO_PA_REG_ADJ_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pa_reg_adj_h:       1;      /*!<［｜<in-house>*TODO*英訳｜PAレギュレータの出力電圧調整設定 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t pa_sel:             1;      /*!<［｜<in-house>*TODO*英訳｜PA出力選択設定 R/W］*/
        uint8_t pa_vdd:             1;      /*!<［｜<in-house>*TODO*英訳｜PA用電源供給源選択設定 R/W］*/
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t pareg_adj_sel:      1;      /*!<［｜<in-house>*TODO*英訳｜PAレギュレータの出力電圧調整イネーブル設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PA_REG_ADJ_H_T;

/** @brief ［Type definition for @ref RADIO_PA_MODE_ADR access｜@ref RADIO_PA_MODE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pa_reg:             4;      /*!<［｜<in-house>*TODO*英訳｜PAレギュレータの出力電圧調整 R/W］*/
        uint8_t pa_mode:            2;      /*!<［｜<in-house>*TODO*英訳｜PAモード設定 R］*/
        uint8_t pa_ramp_sel:        1;      /*!<［｜<in-house>*TODO*英訳｜PAランプ制御選択設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_PA_MODE_T;

typedef union{
    RADIO_PA_REG_ADJ_H_T radio_pa_reg_adj_h;
    RADIO_PA_MODE_T radio_pa_mode;
}RADIO_B0_ADR67_T;

/** @brief ［Type definition for @ref RADIO_PA_REG_FINE_ADJ_L_ADR access｜@ref RADIO_PA_REG_FINE_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pa_reg_fine_adj:    5;      /*!<［｜<in-house>*TODO*英訳｜PAレギュレータの出力電圧調整設定 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PA_REG_FINE_ADJ_L_T;

/** @brief ［Type definition for @ref RADIO_PA_REG_ADJ_L_ADR access｜@ref RADIO_PA_REG_ADJ_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pa_reg_adj_l:       8;      /*!<［｜<in-house>*TODO*英訳｜PAレギュレータの出力電圧調整設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PA_REG_ADJ_L_T;

typedef union{
    RADIO_PA_REG_ADJ_L_T radio_pa_reg_adj_l;
    RADIO_PA_REG_FINE_ADJ_L_T radio_pa_reg_fine_adj_l;
}RADIO_B0_ADR68_T;

/** @brief ［Type definition for @ref RADIO_PA_ADJ_ADR access｜@ref RADIO_PA_ADJ_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t pa_adj:             4;      /*!<［｜<in-house>*TODO*英訳｜PA出力アンプゲイン調整 R/W］*/
        uint8_t pa_adj4:            1;      /*!<［｜<in-house>*TODO*英訳｜PA出力アンプゲイン調整 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_PA_ADJ_T;

/** @brief ［Type definition for @ref RADIO_CHFIL_BW_CCA_ADR access｜@ref RADIO_CHFIL_BW_CCA_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t chfil_bw_adj_cca:   7;      /*!<［｜<in-house>*TODO*英訳｜CCA時チャネルフィルタ帯域幅調整設定 R/W］*/
        uint8_t chfil_wide_en_cca:  1;      /*!<［｜<in-house>*TODO*英訳｜CCA 時チャネルフィルタ広帯域設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CHFIL_BW_CCA_T;

/** @brief ［Type definition for @ref RADIO_CHFIL_BW_OPTION_ADR access｜@ref RADIO_CHFIL_BW_OPTION_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t chfil_bw_option:    3;      /*!<［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅オプション設定 R/W］*/
        uint8_t reserved0:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t chfil_bw:           2;      /*!<［｜<in-house>*TODO*英訳｜チャネルフィルタ帯域幅調整設定(上位2ビット) R/W］*/
        uint8_t chfil_bw_cca:       2;      /*!<［｜<in-house>*TODO*英訳｜CCA時チャネルフィルタ帯域幅調整設定(上位2ビット) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CHFIL_BW_OPTION_T;

/** @brief ［Type definition for @ref RADIO_DC_FIL_ADJ2_ADR access｜@ref RADIO_DC_FIL_ADJ2_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dc_fil_sel_2st:     3;      /*!<［｜<in-house>*TODO*英訳｜DCオフセット引込み用フィルタ設定 R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DC_FIL_ADJ2_T;

/** @brief ［Type definition for @ref RADIO_DEC_GAIN_CCA_ADR access｜@ref RADIO_DEC_GAIN_CCA_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t dec_gain_cca:       5;      /*!<［｜<in-house>*TODO*英訳｜CCA時デシメーションゲイン設定 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_DEC_GAIN_CCA_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_ADR access｜@ref RADIO_VCO_CAL_ADR レジスタアクセス用 型定義］*/
/** @note ［｜<in-house>*TODO*英訳｜ML7421では本レジスタをビットアクセスしないこと］ */
typedef union{
    struct {
        uint8_t vco_cal:            7;      /*!<［｜<in-house>*TODO*英訳｜現在のVCO周波数キャリブレーション値 R/W］*/
        uint8_t cal_wr_en:          1;      /*!<［｜<in-house>*TODO*英訳｜VCOキャリブレーションモード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_T;

/** @brief ［Type definition for @ref RADIO_VCO_CAL_START_ADR access｜@ref RADIO_VCO_CAL_START_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t vco_cal_start:      1;      /*!<［｜<in-house>*TODO*英訳｜VCOキャリブレーション実行 R/W］*/
        uint8_t vco_acal_en:        1;      /*!<［｜<in-house>*TODO*英訳｜VCO振幅キャリブレーション設定 R/W］*/
        uint8_t vco_fcal_en:        1;      /*!<［｜<in-house>*TODO*英訳｜VCO周波数キャリブレーション設定 R/W］*/
        uint8_t auto_vco_cal_chchg_en:1;    /*!<［｜<in-house>*TODO*英訳｜*TODO*TBD R/W］*/
        uint8_t auto_vco_cal_en:     1;     /*!<［｜<in-house>*TODO*英訳｜自動VCOキャリブレーション実行設定 R/W］*/
        uint8_t ondemand_fcal_mode:  1;     /*!［｜<in-house>*TODO*英訳｜<オンデマンドVCO周波数キャリブレーションモード設定 R/W］*/
        uint8_t auto_vco_fcal_en:   1;      /*!［｜<in-house>*TODO*英訳｜<自動VCO周波数キャリブレーション設定 R/W］*/
        uint8_t cal_wr_en:          1;      /*!<［｜<in-house>*TODO*英訳｜VCO周波数キャリブレーションモード設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_VCO_CAL_START_T;

/** @brief ［Type definition for @ref RADIO_CLK_CAL_SET_ADR access｜@ref RADIO_CLK_CAL_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk_cal_start:      1;      /*!<［｜<in-house>*TODO*英訳｜低速クロックキャリブレーション実行 R/W］*/
        uint8_t reserved0:          3;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t clk_cal_div:        4;      /*!<［｜<in-house>*TODO*英訳｜キャリブレーション用クロック分周設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_CAL_SET_T;

/** @brief ［Type definition for @ref RADIO_CLK_CAL_TIME_ADR access｜@ref RADIO_CLK_CAL_TIME_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk_cal_time:       6;      /*!<［｜<in-house>*TODO*英訳｜クロックキャリブレーション時間設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_CAL_TIME_T;

/** @brief ［Type definition for @ref RADIO_CLK_CAL_H_ADR access｜@ref RADIO_CLK_CAL_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk_cal_h:          8;      /*!<［｜<in-house>*TODO*英訳｜クロックキャリブレーション(上位バイト) R］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_CAL_H_T;

/** @brief ［Type definition for @ref RADIO_CLK_CAL_L_ADR access｜@ref RADIO_CLK_CAL_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t clk_cal_l:          8;      /*!<［｜<in-house>*TODO*英訳｜クロックキャリブレーション(下位バイト) R］*/
    }bits;
    uint8_t byte;
}RADIO_CLK_CAL_L_T;

/** @brief ［Type definition for @ref RADIO_FEC_CTRL_ADR access｜@ref RADIO_FEC_CTRL_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t fec_en:             1;      /*!<［｜<in-house>*TODO*英訳｜FEC設定 R/W］*/
        uint8_t fec_scheme:         1;      /*!<［｜<in-house>*TODO*英訳｜FEC方式設定 R/W］*/
        uint8_t intlv_en:           1;      /*!<［｜<in-house>*TODO*英訳｜インターリーブ設定 R/W］*/
        uint8_t reserved0:          5;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_FEC_CTRL_T;

/** @brief ［Type definition for @ref RADIO_SLEEP_INT_CLR_ADR access｜@ref RADIO_SLEEP_INT_CLR_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t sleep_int_clr:      1;      /*!<［｜<in-house>*TODO*英訳｜SLEEP時割込みクリア設定 R/W］*/
        uint8_t auto_sleep_int_clr: 1;      /*!<［｜<in-house>*TODO*英訳｜自動SLEEP時割り込みクリア設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
        uint8_t mstr_clk_sel3:      3;      /*!<［｜<in-house>*TODO*英訳｜FREF選択設定3 */
        uint8_t reserved1:          1;      /*!<［｜<in-house>*TODO*英訳｜予約 R］*/
    }bits;
    uint8_t byte;
}RADIO_SLEEP_INT_CLR_T;

/** @brief ［Type definition for @ref RADIO_RF_TEST_MODE_ADR access｜@ref RADIO_RF_TEST_MODE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t test_en0:           1;      /*!<［｜<in-house>*TODO*英訳｜テストモードイネーブル制御 R/W］*/
        uint8_t test_en1:           1;      /*!<［｜<in-house>*TODO*英訳｜PN9出力設定 R/W］*/
        uint8_t test_en2:           1;      /*!<［｜<in-house>*TODO*英訳｜ALL”1”出力設定 R/W］*/
        uint8_t test_en3:           1;      /*!<［｜<in-house>*TODO*英訳｜ALL”0”出力設定 R/W］*/
        uint8_t test_en4:           1;      /*!<［｜<in-house>*TODO*英訳｜“01”パターン出力設定 R/W］*/
        uint8_t test_en5:           1;      /*!<［｜<in-house>*TODO*英訳｜CW出力設定 R/W］*/
        uint8_t reserved0:          2;      /*!<［｜<in-house>*TODO*英訳｜予約 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_RF_TEST_MODE_T;

/** @brief ［Type definition for @ref RADIO_STM_STATE_ADR access｜@ref RADIO_STM_STATE_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t phy_state:          5;      /*!<［｜<in-house>*TODO*英訳｜ステートマシン状態表示 R］*/
        uint8_t sw_det_rslt:        1;      /*!<［｜<in-house>*TODO*英訳｜SyncWord検出状態表示 R］*/
        uint8_t sync_state:         1;      /*!<［｜<in-house>*TODO*英訳｜受信同期検出状態表示 R］*/
        uint8_t mode_det_rslt:      1;      /*!<［｜<in-house>*TODO*英訳｜Mode T/C受信結果表示 R］*/
    }bits;
    uint8_t byte;
}RADIO_STM_STATE_T;

/** @brief ［Type definition for @ref RADIO_FIFO_SET_ADR access｜@ref RADIO_FIFO_SET_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t txfifo_read_en:     1;      /*!<［｜<in-house>*TODO*英訳｜FIFOリード設定 R/W］*/
        uint8_t fast_cca_lc:        1;      /*!<［｜<in-house>*TODO*英訳｜高速電波チェック時の低消費電力モード設定 R/W］*/
        uint8_t clkinit_trx_en:     1;      /*!<［｜<in-house>*TODO*英訳｜クロック安定後 RF 状態設定イネーブル R/W］*/
        uint8_t clkinit_trx_set:    1;      /*!<［｜<in-house>*TODO*英訳｜クロック安定後 RF 状態設定 R/W］*/
        uint8_t wht_calc_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜Whitening 適用範囲選択設定 R/W］*/
        uint8_t crc_calc_sel:       1;      /*!<［｜<in-house>*TODO*英訳｜CRC 演算範囲選択設定 R/W］*/
        uint8_t length_sel:         1;      /*!<［｜<in-house>*TODO*英訳｜Length 範囲選択設定 R/W］*/
        uint8_t wht_lf_en:          1;      /*!<［｜<in-house>*TODO*英訳｜Whitening 演算 LSB/MSB 選択設定 R/W］*/
    }bits;
    uint8_t byte;
}RADIO_FIFO_SET_T;

/** @brief ［Type definition for @ref RADIO_RX_FIFO_LAST_ADR access｜@ref RADIO_RX_FIFO_LAST_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_ram_last:        8;      /*!<［｜<in-house>*TODO*英訳｜受信時FIFOデータ使用量表示(表示範囲0～255) R］*/
    }bits;
    uint8_t byte;
}RADIO_RX_FIFO_LAST_T;

/** @brief ［Type definition for @ref RADIO_TX_PKT_LEN_H_ADR access｜@ref RADIO_TX_PKT_LEN_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_pkt_len_h:       8;      /*!<［｜<in-house>*TODO*英訳｜送信パケットLength値設定(上位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TX_PKT_LEN_H_T;

/** @brief ［Type definition for @ref RADIO_TX_PKT_LEN_L_ADR access｜@ref RADIO_TX_PKT_LEN_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_pkt_len_l:       8;      /*!<［｜<in-house>*TODO*英訳｜設定パケットLength値設定(下位バイト) R/W］*/
    }bits;
    uint8_t byte;
}RADIO_TX_PKT_LEN_L_T;

/** @brief ［Type definition for @ref RADIO_WR_TX_FIFO_ADR access｜@ref RADIO_WR_TX_FIFO_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t tx_fifo:            8;      /*!<［｜<in-house>*TODO*英訳｜送信FIFO W］*/
    }bits;
    uint8_t byte;
}RADIO_WR_TX_FIFO_T;

/** @brief ［Type definition for @ref RADIO_RX_PKT_LEN_H_ADR access｜@ref RADIO_RX_PKT_LEN_H_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_pkt_len_h:       8;      /*!<［｜<in-house>*TODO*英訳｜受信パケットLength値設定/表示(上位バイト) R］*/
    }bits;
    uint8_t byte;
}RADIO_RX_PKT_LEN_H_T;

/** @brief ［Type definition for @ref RADIO_RX_PKT_LEN_L_ADR access｜@ref RADIO_RX_PKT_LEN_L_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rx_pkt_len_l:       8;      /*!<［｜<in-house>*TODO*英訳｜受信パケットLength値設定/表示(下位バイト) R］*/
    }bits;
    uint8_t byte;
}RADIO_RX_PKT_LEN_L_T;

/** @brief ［Type definition for @ref RADIO_RD_FIFO_ADR access｜@ref RADIO_RD_FIFO_ADR レジスタアクセス用 型定義］*/
typedef union{
    struct {
        uint8_t rd_fifo:            8;      /*!<［｜<in-house>*TODO*英訳｜FIFOリード R］*/
    }bits;
    uint8_t byte;
}RADIO_RD_FIFO_T;

/** \} */ /* End of group RF_REGISTER_BANK0 */

#endif
