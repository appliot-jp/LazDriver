/****************************************************************************************/
/**
	@file     ml7404.C

	@brief    RF LSI register information header file
	@version  V1.00
	@date     24. Jan. 202

	@copyright    Copyright (C) 2018 LAPIS Semiconductor Co., Ltd. All rights reserved.


 *******************************************************************************************/

#ifdef LAZURITE_IDE
#include <common.h>
//	#include <stddef.h>
//	#include <stdint.h>
#include "serial.h"
#else
#include <linux/stddef.h>
#include "../common-lzpi.h"
#include "../hwif/random-lzpi.h"
#endif

#include "../phy.h"
#include "ml7404.h"
#include "../hwif/hal.h"
#include "../errno.h"
#include "../endian.h"
#include "../common_subghz.h"

static const RADIO_PHY_SET_T ml7404_init[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_SPI_EXT_PA_CTRL_ADR       ,0x00},   /*!< [|SPIインタフェースIO /外部PA制御設定:SDO出力OpenDrain設定]  */
	{RADIO_CLK_SET2_ADR              ,0xC3}    /*!< [|クロック制御2:クロックソースの選択 (TCXO使用時)]  */
};
static const RADIO_PHY_SET_T ml7404_sleep_on[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_SLEEP_WU_SET_ADR          ,0x07}
};
static const RADIO_PHY_SET_T ml7404_sleep_off[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_SLEEP_WU_SET_ADR          ,0x06}
};
static const RADIO_PHY_SET_T init_920MHz_GFSK_50kbps[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_PKT_CTRL1_ADR             ,0x16},   /*!< [|パケットフォーマット設定1:Wi-SUN設定(Format C)]  */
	{RADIO_PKT_CTRL2_ADR             ,0x5D},   /*!< [|パケットフォーマット設定2:Wi-SUN設定(CRC16)]  */
	{RADIO_DRATE_SET_ADR             ,0xAA},   /*!< [|データレート設定:]  */
	{RADIO_ED_CTRL_ADR               ,0x83},   /*!< [|ED値平均回数設定数:]  */
	{RADIO_TXPR_LEN_L_ADR            ,0x3C},   /*!< [|送信プリアンブル長設定(下位バイト):Wi-SUN設定]  */
	{RADIO_MON_CTRL_ADR              ,0x00},   /*!< [|モニタ出力信号選択設定:]  */
	{RADIO_GPIO1_CTRL_ADR            ,0x00},   /*!< [|GPIO1端子(ピン#17)制御設定:]  */
	{RADIO_CHFIL_BW_ADR              ,0x02},   /*!< [|チャネルフィルタ帯域幅設定:]  */
	{RADIO_DC_FIL_ADJ_ADR            ,0x12},   /*!< [|DCオフセット調整フィルタ設定:]  */
	{RADIO_DEC_GAIN_ADR              ,0x15},   /*!< [|デシメーションゲイン設定:]  */
	{RADIO_IF_FREQ_ADR               ,0x11},   /*!< [|IF周波数選択:]  */
	{RADIO_PA_REG_ADJ_H_ADR          ,0x00},   /*!< [|PAレギュレータの出力電圧調整(上位ビット):]  */
	{RADIO_PA_REG_ADJ_L_ADR          ,0x89},   /*!< [|PAレギュレータの出力電圧調整(上位バイト):]  */
	{RADIO_DC_FIL_ADJ2_ADR           ,0x00},   /*!< [|DCオフセット調整フィルタ設定2:]  */
	{RADIO_BANK_SEL_ADR              ,0x22},   /*!< [|BANK切り替え:BANK1]  */
	{RADIO_TX_RATE_L_ADR             ,0x48},   /*!< [|送信データレート変換設定(下位バイト):]  */
	{RADIO_RX_RATE1_L_ADR            ,0x03},   /*!< [|受信データレート変換設定1(下位バイト):]  */
	{RADIO_RX_RATE2_ADR              ,0x78},   /*!< [|受信データレート変換設定2:]  */
	{RADIO_RSSI_STABLE_TIME_ADR      ,0x77},   /*!< [|RSSI安定化待ち時間設定:]  */
	{RADIO_RSSI_MAG_ADJ_ADR          ,0x0E},   /*!< [|ED変換用RSSI補正設定:]  */
	{RADIO_AFC_GC_CTRL_ADR           ,0x86},   /*!< [|AFC/ゲイン制御設定:]  */
	{RADIO_CRC_POLY3_ADR             ,0x00},   /*!< [|CRC生成多項式3:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CRC_POLY2_ADR             ,0x00},   /*!< [|CRC生成多項式2:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CRC_POLY1_ADR             ,0x08},   /*!< [|CRC生成多項式1:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CRC_POLY0_ADR             ,0x10},   /*!< [|CRC生成多項式0:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_TXFREQ_FM_ADR             ,0x27},   /*!< [|送信周波数Fカウンタ設定(中位8ビット):920.6MHz]  */
	{RADIO_TXFREQ_FL_ADR             ,0xD2},   /*!< [|送信周波数Fカウンタ設定(下位8ビット):920.6MHz]  */
	{RADIO_RXFREQ_FM_ADR             ,0x27},   /*!< [|受信周波数Fカウンタ設定(中位8ビット):920.6MHz]  */
	{RADIO_RXFREQ_FL_ADR             ,0xD2},   /*!< [|受信周波数Fカウンタ設定(下位8ビット):920.6MHz]  */
	{RADIO_CH_SPACE_H_ADR            ,0x16},   /*!< [|チャネル間隔設定(上位バイト):200kHz]  */
	{RADIO_CH_SPACE_L_ADR            ,0xC1},   /*!< [|チャネル間隔設定(下位バイト):200kHz]  */
	{RADIO_SYNC_WORD_LEN_ADR         ,0x10},   /*!< [|SYNC_WORD長設定:]  */
	{RADIO_SYNCWORD1_SET2_ADR        ,0x90},   /*!< [|SYNC_WORD1設定3:]  */
	{RADIO_SYNCWORD1_SET3_ADR        ,0x4E},   /*!< [|SYNC_WORD1設定4:]  */
	{RADIO_SYNCWORD2_SET2_ADR        ,0x7A},   /*!< [|SYNC_WORD2設定3:Wi-SUN設定]  */
	{RADIO_SYNCWORD2_SET3_ADR        ,0x0E},   /*!< [|SYNC_WORD2設定4:Wi-SUN設定]  */
	{RADIO_FSK_CTRL_ADR              ,0x00},   /*!< [|GFSK/FSK変調タイミング分解能設定:]  */
	{RADIO_GFSK_DEV_H_ADR            ,0x02},   /*!< [|GFSK時周波数偏位設定(上位6ビット):]  */
	{RADIO_GFSK_DEV_L_ADR            ,0xD8},   /*!< [|GFSK時周波数偏位設定(下位バイト):]  */
	{RADIO_FSK_DEV0_H_GFIL0_ADR      ,0x24},   /*!< [|FSK周波数偏位設定0/ガウシアンフィルタ係数設定1:]  */
	{RADIO_FSK_DEV0_L_GFIL1_ADR      ,0xD6},   /*!< [|FSK周波数偏位設定0/ガウシアンフィルタ係数設定2:]  */
	{RADIO_FSK_DEV1_H_GFIL2_ADR      ,0x19},   /*!< [|FSK周波数偏位設定1/ガウシアンフィルタ係数設定3:]  */
	{RADIO_FSK_DEV1_L_GFIL3_ADR      ,0x29},   /*!< [|FSK周波数偏位設定1/ガウシアンフィルタ係数設定4:]  */
	{RADIO_FSK_DEV2_H_GFIL4_ADR      ,0x3A},   /*!< [|FSK周波数偏位設定2/ガウシアンフィルタ係数設定5:]  */
	{RADIO_FSK_DEV2_L_GFIL5_ADR      ,0x48},   /*!< [|FSK周波数偏位設定2/ガウシアンフィルタ係数設定6:]  */
	{RADIO_FSK_DEV3_H_GFIL6_ADR      ,0x4C},   /*!< [|FSK周波数偏位設定3/ガウシアンフィルタ係数設定7:]  */
	{RADIO_VCO_CAL_MIN_FH_ADR        ,0x08},   /*!< [|VCO_CAL下限周波数Fカウンタ設定(上位6ビット):]  */
	{RADIO_VCO_CAL_MIN_FM_ADR        ,0xFA},   /*!< [|VCO_CAL下限周波数Fカウンタ設定(中位8ビット):]  */
	{RADIO_VCO_CAL_MIN_FL_ADR        ,0x4F},   /*!< [|VCO_CAL下限周波数Fカウンタ設定(下位8ビット):]  */
	{RADIO_VCO_CAL_MAX_N_ADR         ,0x04},   /*!< [|VCO_CAL_Max周波数設定:]  */
	{RADIO_DEMOD_SET6_ADR            ,0x15},   /*!< [|復調器設定6:]  */
	{RADIO_DEMOD_SET7_ADR            ,0x16},   /*!< [|復調器設定7:]  */
	{RADIO_DEMOD_SET8_ADR            ,0x03},   /*!< [|復調器設定8:]  */
	{RADIO_DEMOD_SET9_ADR            ,0xCD},   /*!< [|復調器設定9:]  */
	{RADIO_WHT_INIT_H_ADR            ,0x00},   /*!< [|Whitening初期状態設定(上位1ビット):Wi-SUN設定]  */
	{RADIO_WHT_INIT_L_ADR            ,0xF0},   /*!< [|Whitening初期状態設定(下位8ビット):Wi-SUN設定]  */
	{RADIO_WHT_CFG_ADR               ,0x10},   /*!< [|Whitening生成多項式設定:Wi-SUN設定]  */
	{RADIO_BANK_SEL_ADR              ,0x44},   /*!< [|BANK切り替え:BANK2]  */
	{RADIO_NONPUBLIC_B2_ADR0E        ,0x5B},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR16        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1A        ,0x6E},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1C        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR29        ,0x5F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2A        ,0x1F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2F        ,0xA7},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR32        ,0x4C},   /*!< [|予約:]  */
	{RADIO_GAIN_HHTH_ADR             ,0x8C},   /*!< [|高高ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOHH_ADR            ,0x3C},   /*!< [|高ゲインから高高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOM_ADR             ,0x8C},   /*!< [|高ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOH_ADR             ,0x3C},   /*!< [|中間ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOL_ADR             ,0x8C},   /*!< [|高ゲインから低ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_LTOM_ADR             ,0x3C},   /*!< [|低ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_RSSI_ADJ_H_ADR            ,0x2F},   /*!< [|高ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_M_ADR            ,0x55},   /*!< [|中間ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_L_B2_ADR         ,0x7F},   /*!< [|低ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x88},   /*!< [|BANK切り替え:BANK3]  */
	{RADIO_NONPUBLIC_B3_ADR0E        ,0x64},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B3_ADR26        ,0x33},   /*!< [|予約:]  */
	{RADIO_BANK_SEL_ADR              ,0x33},   /*!< [|BANK切り替え:BANK6]  */
	{RADIO_MOD_CTRL_ADR              ,0x00},   /*!< [|変調方式設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x55},   /*!< [|BANK切り替え:BANK7]  */
	{RADIO_DSSS_CTRL_ADR             ,0x00},   /*!< [|DSSS制御設定:]  */
	{RADIO_FEC_ENC_CTRL_ADR          ,0x00},   /*!< [|FECエンコーダ設定:]  */
	{RADIO_FEC_DEC_CTRL_ADR          ,0x00},   /*!< [|FECデコーダ設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x99},   /*!< [|BANK切り替え:BANK10]  */
	{RADIO_BPSK_STEP_CTRL_ADR        ,0x00},   /*!< [|BPSKステップ制御設定:]  */
	{RADIO_BPSK_STEP_SET0_ADR        ,0x24},   /*!< [|BPSKステップ制御設定0:]  */
	{RADIO_BPSK_STEP_SET1_ADR        ,0xD6},   /*!< [|BPSKステップ制御設定1:]  */
	{RADIO_BPSK_STEP_SET2_ADR        ,0x19},   /*!< [|BPSKステップ制御設定2:]  */
	{RADIO_BPSK_STEP_SET3_ADR        ,0x29},   /*!< [|BPSKステップ制御設定3:]  */
	{RADIO_BPSK_STEP_SET4_ADR        ,0x3A},   /*!< [|BPSKステップ制御設定4:]  */
	{RADIO_BPSK_STEP_SET5_ADR        ,0x48},   /*!< [|BPSKステップ制御設定5:]  */
	{RADIO_BPSK_STEP_SET6_ADR        ,0x4C},   /*!< [|BPSKステップ制御設定6:]  */
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|BANK切り替え:BANK0]  */
};

static const RADIO_PHY_SET_T init_920MHz_GFSK_100kbps[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_PKT_CTRL1_ADR             ,0x16},   /*!< [|パケットフォーマット設定1:Wi-SUN設定(Format C)]  */
	{RADIO_PKT_CTRL2_ADR             ,0x5D},   /*!< [|パケットフォーマット設定2:Wi-SUN設定(CRC16)]  */
	{RADIO_DRATE_SET_ADR             ,0xBB},   /*!< [|データレート設定:]  */
	{RADIO_ED_CTRL_ADR               ,0x83},   /*!< [|ED値平均回数設定数:]  */
	{RADIO_TXPR_LEN_L_ADR            ,0x3C},   /*!< [|送信プリアンブル長設定(下位バイト):Wi-SUN設定]  */
	{RADIO_MON_CTRL_ADR              ,0x00},   /*!< [|モニタ出力信号選択設定:]  */
	{RADIO_GPIO1_CTRL_ADR            ,0x00},   /*!< [|GPIO1端子(ピン#17)制御設定:]  */
	{RADIO_DC_FIL_ADJ_ADR            ,0x12},   /*!< [|DCオフセット調整フィルタ設定:]  */
	{RADIO_DEC_GAIN_ADR              ,0x17},   /*!< [|デシメーションゲイン設定:]  */
	{RADIO_PA_REG_ADJ_H_ADR          ,0x00},   /*!< [|PAレギュレータの出力電圧調整(上位ビット):]  */
	{RADIO_PA_REG_ADJ_L_ADR          ,0x89},   /*!< [|PAレギュレータの出力電圧調整(上位バイト):]  */
	{RADIO_CHFIL_BW_CCA_ADR          ,0x81},   /*!< [|CCA時チャネルフィルタ帯域幅設定:]  */
	{RADIO_DC_FIL_ADJ2_ADR           ,0x00},   /*!< [|DCオフセット調整フィルタ設定2:]  */
	{RADIO_BANK_SEL_ADR              ,0x22},   /*!< [|BANK切り替え:BANK1]  */
	{RADIO_TX_RATE_L_ADR             ,0x24},   /*!< [|送信データレート変換設定(下位バイト):]  */
	{RADIO_RX_RATE1_L_ADR            ,0x02},   /*!< [|受信データレート変換設定1(下位バイト):]  */
	{RADIO_RX_RATE2_ADR              ,0x5A},   /*!< [|受信データレート変換設定2:]  */
	{RADIO_RSSI_STABLE_TIME_ADR      ,0x77},   /*!< [|RSSI安定化待ち時間設定:]  */
	{RADIO_RSSI_MAG_ADJ_ADR          ,0x0D},   /*!< [|ED変換用RSSI補正設定:]  */
	{RADIO_AFC_GC_CTRL_ADR           ,0x86},   /*!< [|AFC/ゲイン制御設定:]  */
	{RADIO_CRC_POLY3_ADR             ,0x00},   /*!< [|CRC生成多項式3:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CRC_POLY2_ADR             ,0x00},   /*!< [|CRC生成多項式2:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CRC_POLY1_ADR             ,0x08},   /*!< [|CRC生成多項式1:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CRC_POLY0_ADR             ,0x10},   /*!< [|CRC生成多項式0:Wi-SUN設定(CRC16, x16+x12+x5+1)]  */
	{RADIO_CH_SPACE_H_ADR            ,0x16},   /*!< [|チャネル間隔設定(上位バイト):200kHz]  */
	{RADIO_CH_SPACE_L_ADR            ,0xC1},   /*!< [|チャネル間隔設定(下位バイト):200kHz]  */
	{RADIO_SYNC_WORD_LEN_ADR         ,0x10},   /*!< [|SYNC_WORD長設定:]  */
	{RADIO_SYNCWORD1_SET2_ADR        ,0x90},   /*!< [|SYNC_WORD1設定3:]  */
	{RADIO_SYNCWORD1_SET3_ADR        ,0x4E},   /*!< [|SYNC_WORD1設定4:]  */
	{RADIO_SYNCWORD2_SET2_ADR        ,0x7A},   /*!< [|SYNC_WORD2設定3:Wi-SUN設定]  */
	{RADIO_SYNCWORD2_SET3_ADR        ,0x0E},   /*!< [|SYNC_WORD2設定4:Wi-SUN設定]  */
	{RADIO_FSK_CTRL_ADR              ,0x00},   /*!< [|GFSK/FSK変調タイミング分解能設定:]  */
	{RADIO_FSK_DEV0_H_GFIL0_ADR      ,0x24},   /*!< [|FSK周波数偏位設定0/ガウシアンフィルタ係数設定1:]  */
	{RADIO_FSK_DEV0_L_GFIL1_ADR      ,0xD6},   /*!< [|FSK周波数偏位設定0/ガウシアンフィルタ係数設定2:]  */
	{RADIO_FSK_DEV1_H_GFIL2_ADR      ,0x19},   /*!< [|FSK周波数偏位設定1/ガウシアンフィルタ係数設定3:]  */
	{RADIO_FSK_DEV1_L_GFIL3_ADR      ,0x29},   /*!< [|FSK周波数偏位設定1/ガウシアンフィルタ係数設定4:]  */
	{RADIO_FSK_DEV2_H_GFIL4_ADR      ,0x3A},   /*!< [|FSK周波数偏位設定2/ガウシアンフィルタ係数設定5:]  */
	{RADIO_FSK_DEV2_L_GFIL5_ADR      ,0x48},   /*!< [|FSK周波数偏位設定2/ガウシアンフィルタ係数設定6:]  */
	{RADIO_FSK_DEV3_H_GFIL6_ADR      ,0x4C},   /*!< [|FSK周波数偏位設定3/ガウシアンフィルタ係数設定7:]  */
	{RADIO_VCO_CAL_MAX_N_ADR         ,0x04},   /*!< [|VCO_CAL_Max周波数設定:]  */
	{RADIO_DEMOD_SET6_ADR            ,0x15},   /*!< [|復調器設定6:]  */
	{RADIO_DEMOD_SET8_ADR            ,0x02},   /*!< [|復調器設定8:]  */
	{RADIO_DEMOD_SET9_ADR            ,0xCC},   /*!< [|復調器設定9:]  */
	{RADIO_WHT_INIT_H_ADR            ,0x00},   /*!< [|Whitening初期状態設定(上位1ビット):Wi-SUN設定]  */
	{RADIO_WHT_INIT_L_ADR            ,0xF0},   /*!< [|Whitening初期状態設定(下位8ビット):Wi-SUN設定]  */
	{RADIO_WHT_CFG_ADR               ,0x10},   /*!< [|Whitening生成多項式設定:Wi-SUN設定]  */
	{RADIO_BANK_SEL_ADR              ,0x44},   /*!< [|BANK切り替え:BANK2]  */
	{RADIO_NONPUBLIC_B2_ADR0E        ,0x5B},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR16        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1A        ,0x6E},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1C        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR29        ,0x5F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2A        ,0x1F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2F        ,0xA7},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR32        ,0x4C},   /*!< [|予約:]  */
	{RADIO_GAIN_HHTH_ADR             ,0x8C},   /*!< [|高高ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOM_ADR             ,0x8C},   /*!< [|高ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOL_ADR             ,0x8C},   /*!< [|高ゲインから低ゲインへの切り替え閾値設定:]  */
	{RADIO_RSSI_ADJ_H_ADR            ,0x2A},   /*!< [|高ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_M_ADR            ,0x52},   /*!< [|中間ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_L_B2_ADR         ,0x7F},   /*!< [|低ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x88},   /*!< [|BANK切り替え:BANK3]  */
	{RADIO_NONPUBLIC_B3_ADR26        ,0x33},   /*!< [|予約:]  */
	{RADIO_BANK_SEL_ADR              ,0x33},   /*!< [|BANK切り替え:BANK6]  */
	{RADIO_MOD_CTRL_ADR              ,0x00},   /*!< [|変調方式設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x55},   /*!< [|BANK切り替え:BANK7]  */
	{RADIO_DSSS_CTRL_ADR             ,0x00},   /*!< [|DSSS制御設定:]  */
	{RADIO_FEC_ENC_CTRL_ADR          ,0x00},   /*!< [|FECエンコーダ設定:]  */
	{RADIO_FEC_DEC_CTRL_ADR          ,0x00},   /*!< [|FECデコーダ設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x99},   /*!< [|BANK切り替え:BANK10]  */
	{RADIO_BPSK_STEP_CTRL_ADR        ,0x00},   /*!< [|BPSKステップ制御設定:]  */
	{RADIO_BPSK_STEP_SET0_ADR        ,0x24},   /*!< [|BPSKステップ制御設定0:]  */
	{RADIO_BPSK_STEP_SET1_ADR        ,0xD6},   /*!< [|BPSKステップ制御設定1:]  */
	{RADIO_BPSK_STEP_SET2_ADR        ,0x19},   /*!< [|BPSKステップ制御設定2:]  */
	{RADIO_BPSK_STEP_SET3_ADR        ,0x29},   /*!< [|BPSKステップ制御設定3:]  */
	{RADIO_BPSK_STEP_SET4_ADR        ,0x3A},   /*!< [|BPSKステップ制御設定4:]  */
	{RADIO_BPSK_STEP_SET5_ADR        ,0x48},   /*!< [|BPSKステップ制御設定5:]  */
	{RADIO_BPSK_STEP_SET6_ADR        ,0x4C},   /*!< [|BPSKステップ制御設定6:]  */
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|BANK切り替え:BANK0]  */
};

static const RADIO_PHY_SET_T init_920MHz_DSSS_50kcps[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_DRATE_SET_ADR             ,0xAA},   /*!< [|データレート設定:50kbps]  */
	{RADIO_ED_CTRL_ADR               ,0x83},   /*!< [|ED値平均回数設定数:]  */
	{RADIO_SYNC_CONDITION1_ADR       ,0x02},   /*!< [|受信プリアンブル設定:]  */
	{RADIO_SYNC_CONDITION3_ADR       ,0x01},   /*!< [|誤り許容設定:]  */
	{RADIO_MON_CTRL_ADR              ,0x00},   /*!< [|モニタ出力信号選択設定:]  */
	{RADIO_GPIO1_CTRL_ADR            ,0x00},   /*!< [|GPIO1端子(ピン#17)制御設定:]  */
	{RADIO_CHFIL_BW_ADR              ,0x04},   /*!< [|チャネルフィルタ帯域幅設定:]  */
	{RADIO_DC_FIL_ADJ_ADR            ,0x15},   /*!< [|DCオフセット調整フィルタ設定:]  */
	{RADIO_DEC_GAIN_ADR              ,0x0F},   /*!< [|デシメーションゲイン設定:]  */
	{RADIO_PA_REG_ADJ_H_ADR          ,0x00},   /*!< [|PAレギュレータの出力電圧調整(上位ビット):]  */
	{RADIO_PA_REG_ADJ_L_ADR          ,0x89},   /*!< [|PAレギュレータの出力電圧調整(上位バイト):]  */
	{RADIO_CHFIL_BW_CCA_ADR          ,0x81},   /*!< [|CCA時チャネルフィルタ帯域幅設定:]  */
	{RADIO_DEC_GAIN_CCA_ADR          ,0x15},   /*!< [|CCA時のデシメーションゲイン設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x22},   /*!< [|BANK切り替え:BANK1]  */
	{RADIO_TX_RATE_L_ADR             ,0x48},   /*!< [|送信データレート変換設定(下位バイト):]  */
	{RADIO_RX_RATE1_L_ADR            ,0x04},   /*!< [|受信データレート変換設定1(下位バイト):]  */
	{RADIO_RX_RATE2_ADR              ,0x78},   /*!< [|受信データレート変換設定2:]  */
	{RADIO_RSSI_STABLE_TIME_ADR      ,0x77},   /*!< [|RSSI安定化待ち時間設定:]  */
	{RADIO_RSSI_MAG_ADJ_ADR          ,0x15},   /*!< [|ED変換用RSSI補正設定:]  */
	{RADIO_AFC_GC_CTRL_ADR           ,0x01},   /*!< [|AFC/ゲイン制御設定:]  */
	{RADIO_CRC_POLY1_ADR             ,0x08},   /*!< [|CRC生成多項式1:]  */
	{RADIO_CRC_POLY0_ADR             ,0x10},   /*!< [|CRC生成多項式0:]  */
	{RADIO_FSK_CTRL_ADR              ,0x18},   /*!< [|GFSK/FSK変調タイミング分解能設定:]  */
	{RADIO_VCO_CAL_MAX_N_ADR         ,0x04},   /*!< [|VCO_CAL_Max周波数設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x44},   /*!< [|BANK切り替え:BANK2]  */
	{RADIO_NONPUBLIC_B2_ADR0E        ,0x24},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR16        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR19        ,0x0C},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1A        ,0x6E},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1C        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR29        ,0xE6},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2A        ,0x1F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2F        ,0xE7},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR32        ,0x4C},   /*!< [|予約:]  */
	{RADIO_GAIN_HHTH_ADR             ,0x6E},   /*!< [|高高ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOHH_ADR            ,0x1E},   /*!< [|高ゲインから高高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOM_ADR             ,0x6E},   /*!< [|高ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOH_ADR             ,0x1E},   /*!< [|中間ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOL_ADR             ,0x6E},   /*!< [|高ゲインから低ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_LTOM_ADR             ,0x1E},   /*!< [|低ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_RSSI_ADJ_H_ADR            ,0x2D},   /*!< [|高ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_M_ADR            ,0x53},   /*!< [|中間ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_L_B2_ADR         ,0x7F},   /*!< [|低ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x88},   /*!< [|BANK切り替え:BANK3]  */
	{RADIO_BANK_SEL_ADR              ,0x33},   /*!< [|BANK切り替え:BANK6]  */
	{RADIO_BANK_SEL_ADR              ,0x55},   /*!< [|BANK切り替え:BANK7]  */
	{RADIO_DSSS_CTRL_ADR             ,0x05},   /*!< [|DSSS制御設定:]  */
	{RADIO_DSSS_MODE_ADR             ,0x45},   /*!< [|DSSSモード設定:]  */
	{RADIO_FEC_ENC_CTRL_ADR          ,0x00},   /*!< [|FECエンコーダ設定:]  */
	{RADIO_FEC_DEC_CTRL_ADR          ,0x00},   /*!< [|FECデコーダ設定:]  */
	{RADIO_SS_AFC_RANGE_SYNC_ADR     ,0x0B},   /*!< [|DSSS AFCレンジ設定(同期時):]  */
	{RADIO_SS_AFC_RANGE_ADR          ,0x0B},   /*!< [|DSSS AFCレンジ設定(データ受信時):]  */
	{RADIO_DSSS_RATE_SYNC_H_ADR      ,0x01},   /*!< [|DSSS同期時受信チップレート設定(上位4ビット):]  */
	{RADIO_DSSS_RATE_SYNC_L_ADR      ,0x67},   /*!< [|DSSS同期時受信チップレート設定(下位バイト):]  */
	{RADIO_DSSS_RATE_H_ADR           ,0x01},   /*!< [|DSSSデータ受信時受信チップレート設定(上位4ビット):]  */
	{RADIO_DSSS_RATE_L_ADR           ,0x67},   /*!< [|DSSSデータ受信時受信データレート設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT8_GATE_H_ADR   ,0x02},   /*!< [|DSSS同期確立時相関閾値設定(上位3ビット):]  */
	{RADIO_SS_SYNC_BIT8_GATE_L_ADR   ,0x20},   /*!< [|DSSS同期確立時相関閾値設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT8_GATE2_H_ADR  ,0x02},   /*!< [|DSSS同期確立時相関閾値設定2(上位3ビット):]  */
	{RADIO_SS_SYNC_BIT8_GATE2_L_ADR  ,0x30},   /*!< [|DSSS同期確立時相関閾値設定2(下位バイト):]  */
	{RADIO_SS_SYNC_BIT_GATE_L_ADR    ,0xC0},   /*!< [|DSSS同期確立後相関閾値設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT4_GATE_L_ADR   ,0x4C},   /*!< [|予約:]  */
	{RADIO_SS_SYNC_LOST_GATE_ADR     ,0x14},   /*!< [|予約:]  */
	{RADIO_AGC_AVE_OFST_SYNC_ADR     ,0x2A},   /*!< [|予約:]  */
	{RADIO_AGC_AVE_OFST_ADR          ,0x9C},   /*!< [|予約:]  */
	{RADIO_AGC_IIR_SET0_ADR          ,0x44},   /*!< [|予約:]  */
	{RADIO_AGC_IIR_SET1_ADR          ,0x25},   /*!< [|予約:]  */
	{RADIO_BIT8_SPDET_TH_L_ADR       ,0xF4},   /*!< [|予約:]  */
	{RADIO_DSSS_SET6_ADR             ,0x34},   /*!< [|予約:]  */
	{RADIO_DSSS_SET7_ADR             ,0x14},   /*!< [|予約:]  */
	{RADIO_DSSS_SET8_ADR             ,0x32},   /*!< [|予約:]  */
	{RADIO_DSSS_SET9_ADR             ,0x25},   /*!< [|予約:]  */
	{RADIO_BANK_SEL_ADR              ,0x99},   /*!< [|BANK切り替え:BANK10]  */
	{RADIO_BPSK_STEP_CTRL_ADR        ,0x10},   /*!< [|BPSKステップ制御設定:]  */
	{RADIO_BPSK_STEP_CLK_SET_ADR     ,0x04},   /*!< [|BPSKステップ制御クロック設定:]  */
	{RADIO_BPSK_STEP_SET0_ADR        ,0x10},   /*!< [|BPSKステップ制御設定0:]  */
	{RADIO_BPSK_STEP_SET1_ADR        ,0x21},   /*!< [|BPSKステップ制御設定1:]  */
	{RADIO_BPSK_STEP_SET2_ADR        ,0x11},   /*!< [|BPSKステップ制御設定2:]  */
	{RADIO_BPSK_STEP_SET3_ADR        ,0x22},   /*!< [|BPSKステップ制御設定3:]  */
	{RADIO_BPSK_STEP_SET4_ADR        ,0x11},   /*!< [|BPSKステップ制御設定4:]  */
	{RADIO_BPSK_STEP_SET5_ADR        ,0x42},   /*!< [|BPSKステップ制御設定5:]  */
	{RADIO_BPSK_STEP_SET6_ADR        ,0x34},   /*!< [|BPSKステップ制御設定6:]  */
	{RADIO_BPSK_STEP_SET7_ADR        ,0x34},   /*!< [|BPSKステップ制御設定7:]  */
	{RADIO_BPSK_STEP_SET8_ADR        ,0x45},   /*!< [|BPSKステップ制御設定8:]  */
	{RADIO_BPSK_STEP_SET9_ADR        ,0x63},   /*!< [|BPSKステップ制御設定9:]  */
	{RADIO_BPSK_STEP_SET10_ADR       ,0x74},   /*!< [|BPSKステップ制御設定10:]  */
	{RADIO_BPSK_STEP_SET11_ADR       ,0x66},   /*!< [|BPSKステップ制御設定11:]  */
	{RADIO_BPSK_STEP_SET12_ADR       ,0x56},   /*!< [|BPSKステップ制御設定12:]  */
	{RADIO_BPSK_STEP_SET13_ADR       ,0x35},   /*!< [|BPSKステップ制御設定13:]  */
	{RADIO_BPSK_STEP_SET14_ADR       ,0x45},   /*!< [|BPSKステップ制御設定14:]  */
	{RADIO_BPSK_STEP_SET15_ADR       ,0x55},   /*!< [|BPSKステップ制御設定15:]  */
	{RADIO_BPSK_STEP_SET16_ADR       ,0x44},   /*!< [|BPSKステップ制御設定16:]  */
	{RADIO_BPSK_STEP_SET17_ADR       ,0x45},   /*!< [|BPSKステップ制御設定17:]  */
	{RADIO_BPSK_STEP_SET18_ADR       ,0x22},   /*!< [|BPSKステップ制御設定18:]  */
	{RADIO_BPSK_STEP_SET19_ADR       ,0x12},   /*!< [|BPSKステップ制御設定19:]  */
	{RADIO_BPSK_STEP_SET20_ADR       ,0x11},   /*!< [|BPSKステップ制御設定20:]  */
	{RADIO_BPSK_STEP_SET21_ADR       ,0x00},   /*!< [|BPSKステップ制御設定21:]  */
	{RADIO_BPSK_STEP_SET22_ADR       ,0x00},   /*!< [|BPSKステップ制御設定22:]  */
	{RADIO_BPSK_STEP_SET23_ADR       ,0x00},   /*!< [|BPSKステップ制御設定23:]  */
	{RADIO_BPSK_STEP_SET24_ADR       ,0x00},   /*!< [|BPSKステップ制御設定24:]  */
	{RADIO_BPSK_STEP_SET25_ADR       ,0x00},   /*!< [|BPSKステップ制御設定25:]  */
	{RADIO_BPSK_STEP_SET26_ADR       ,0x00},   /*!< [|BPSKステップ制御設定26:]  */
	{RADIO_BPSK_STEP_SET27_ADR       ,0x00},   /*!< [|BPSKステップ制御設定27:]  */
	{RADIO_BPSK_STEP_SET28_ADR       ,0x00},   /*!< [|BPSKステップ制御設定28:]  */
	{RADIO_BPSK_STEP_SET29_ADR       ,0x00},   /*!< [|BPSKステップ制御設定29:]  */
	{RADIO_BPSK_STEP_SET30_ADR       ,0x00},   /*!< [|BPSKステップ制御設定30:]  */
	{RADIO_BPSK_STEP_SET31_ADR       ,0x20},   /*!< [|BPSKステップ制御設定31:]  */
	{RADIO_BPSK_STEP_SET32_ADR       ,0x23},   /*!< [|BPSKステップ制御設定32:]  */
	{RADIO_BPSK_STEP_SET33_ADR       ,0x21},   /*!< [|BPSKステップ制御設定33:]  */
	{RADIO_BPSK_STEP_SET34_ADR       ,0x21},   /*!< [|BPSKステップ制御設定34:]  */
	{RADIO_BPSK_STEP_SET35_ADR       ,0x33},   /*!< [|BPSKステップ制御設定35:]  */
	{RADIO_BPSK_STEP_SET36_ADR       ,0x43},   /*!< [|BPSKステップ制御設定36:]  */
	{RADIO_BPSK_STEP_SET37_ADR       ,0x55},   /*!< [|BPSKステップ制御設定37:]  */
	{RADIO_BPSK_STEP_SET38_ADR       ,0x54},   /*!< [|BPSKステップ制御設定38:]  */
	{RADIO_BPSK_STEP_SET39_ADR       ,0x53},   /*!< [|BPSKステップ制御設定39:]  */
	{RADIO_BPSK_STEP_SET40_ADR       ,0x65},   /*!< [|BPSKステップ制御設定40:]  */
	{RADIO_BPSK_STEP_SET41_ADR       ,0x66},   /*!< [|BPSKステップ制御設定41:]  */
	{RADIO_BPSK_STEP_SET42_ADR       ,0x47},   /*!< [|BPSKステップ制御設定42:]  */
	{RADIO_BPSK_STEP_SET43_ADR       ,0x36},   /*!< [|BPSKステップ制御設定43:]  */
	{RADIO_BPSK_STEP_SET44_ADR       ,0x54},   /*!< [|BPSKステップ制御設定44:]  */
	{RADIO_BPSK_STEP_SET45_ADR       ,0x43},   /*!< [|BPSKステップ制御設定45:]  */
	{RADIO_BPSK_STEP_SET46_ADR       ,0x43},   /*!< [|BPSKステップ制御設定46:]  */
	{RADIO_BPSK_STEP_SET47_ADR       ,0x24},   /*!< [|BPSKステップ制御設定47:]  */
	{RADIO_BPSK_STEP_SET48_ADR       ,0x11},   /*!< [|BPSKステップ制御設定48:]  */
	{RADIO_BPSK_STEP_SET49_ADR       ,0x22},   /*!< [|BPSKステップ制御設定49:]  */
	{RADIO_BPSK_STEP_SET50_ADR       ,0x11},   /*!< [|BPSKステップ制御設定50:]  */
	{RADIO_BPSK_STEP_SET51_ADR       ,0x12},   /*!< [|BPSKステップ制御設定51:]  */
	{RADIO_BPSK_STEP_SET52_ADR       ,0x01},   /*!< [|BPSKステップ制御設定52:]  */
	{RADIO_BPSK_STEP_SET53_ADR       ,0x00},   /*!< [|BPSKステップ制御設定53:]  */
	{RADIO_BPSK_STEP_SET54_ADR       ,0x00},   /*!< [|BPSKステップ制御設定54:]  */
	{RADIO_BPSK_STEP_SET55_ADR       ,0x00},   /*!< [|BPSKステップ制御設定55:]  */
	{RADIO_BPSK_STEP_SET56_ADR       ,0x00},   /*!< [|BPSKステップ制御設定56:]  */
	{RADIO_BPSK_STEP_SET57_ADR       ,0x00},   /*!< [|BPSKステップ制御設定57:]  */
	{RADIO_BPSK_STEP_SET58_ADR       ,0x00},   /*!< [|BPSKステップ制御設定58:]  */
	{RADIO_BPSK_STEP_SET59_ADR       ,0x00},   /*!< [|BPSKステップ制御設定59:]  */
	{RADIO_PADRV_CTRL_ADR            ,0x63},   /*!< [|PAドライバ制御設定:]  */
	{RADIO_PADRV_ADJ1_ADR            ,0x03},   /*!< [|PAドライバ調整1:]  */
	{RADIO_PADRV_ADJ2_H_ADR          ,0x02},   /*!< [|PAドライバ調整1(上位バイト):]  */
	{RADIO_PADRV_ADJ2_L_ADR          ,0x00},   /*!< [|PAドライバ調整1(下位バイト):]  */
	{RADIO_PADRV_CLK_SET_L_ADR       ,0x03},   /*!< [|PAドライバ制御用クロック設定(下位バイト):]  */
	{RADIO_PADRV_UP_ADJ_ADR          ,0x01},   /*!< [|BPSKドライバ制御立上り開始時間設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|BANK切り替え:BANK0]  */
};

static const RADIO_PHY_SET_T init_920MHz_DSSS_100kcps[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
	{RADIO_DRATE_SET_ADR             ,0xBB},   /*!< [|データレート設定:]  */
	{RADIO_CH_SET_ADR                ,0x03},   /*!< [|RFチャネル設定:]  */
	{RADIO_ED_CTRL_ADR               ,0x83},   /*!< [|ED値平均回数設定数:]  */
	{RADIO_SYNC_CONDITION1_ADR       ,0x02},   /*!< [|受信プリアンブル設定:]  */
	{RADIO_SYNC_CONDITION3_ADR       ,0x01},   /*!< [|誤り許容設定:]  */
	{RADIO_MON_CTRL_ADR              ,0x00},   /*!< [|モニタ出力信号選択設定:]  */
	{RADIO_GPIO1_CTRL_ADR            ,0x00},   /*!< [|GPIO1端子(ピン#17)制御設定:]  */
	{RADIO_CHFIL_BW_ADR              ,0x02},   /*!< [|チャネルフィルタ帯域幅設定:]  */
	{RADIO_DEC_GAIN_ADR              ,0x15},   /*!< [|デシメーションゲイン設定:]  */
	{RADIO_PA_REG_ADJ_H_ADR          ,0x00},   /*!< [|PAレギュレータの出力電圧調整(上位ビット):]  */
	{RADIO_PA_REG_ADJ_L_ADR          ,0x89},   /*!< [|PAレギュレータの出力電圧調整(上位バイト):]  */
	{RADIO_CHFIL_BW_CCA_ADR          ,0x81},   /*!< [|CCA時チャネルフィルタ帯域幅設定:]  */
	{RADIO_DEC_GAIN_CCA_ADR          ,0x17},   /*!< [|CCA時のデシメーションゲイン設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x22},   /*!< [|BANK切り替え:BANK1]  */
	{RADIO_TX_RATE_L_ADR             ,0x24},   /*!< [|送信データレート変換設定(下位バイト):]  */
	{RADIO_RX_RATE1_L_ADR            ,0x04},   /*!< [|受信データレート変換設定1(下位バイト):]  */
	{RADIO_RX_RATE2_ADR              ,0x5A},   /*!< [|受信データレート変換設定2:]  */
	{RADIO_RSSI_MAG_ADJ_ADR          ,0x19},   /*!< [|ED変換用RSSI補正設定:]  */
	{RADIO_AFC_GC_CTRL_ADR           ,0x01},   /*!< [|AFC/ゲイン制御設定:]  */
	{RADIO_CRC_POLY1_ADR             ,0x08},   /*!< [|CRC生成多項式1:]  */
	{RADIO_CRC_POLY0_ADR             ,0x10},   /*!< [|CRC生成多項式0:]  */
	{RADIO_CH_SPACE_H_ADR            ,0x0B},   /*!< [|チャネル間隔設定(上位バイト):100kHz]  */
	{RADIO_CH_SPACE_L_ADR            ,0x61},   /*!< [|チャネル間隔設定(下位バイト):100kHz]  */
	{RADIO_VCO_CAL_MAX_N_ADR         ,0x04},   /*!< [|VCO_CAL_Max周波数設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x44},   /*!< [|BANK切り替え:BANK2]  */
	{RADIO_NONPUBLIC_B2_ADR0E        ,0x4F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR16        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR19        ,0x86},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1A        ,0x6E},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1C        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR29        ,0xC6},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2A        ,0x1F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2F        ,0xE7},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR32        ,0x4C},   /*!< [|予約:]  */
	{RADIO_GAIN_HHTH_ADR             ,0x8D},   /*!< [|高高ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOHH_ADR            ,0x3C},   /*!< [|高ゲインから高高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOM_ADR             ,0x8D},   /*!< [|高ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOH_ADR             ,0x3C},   /*!< [|中間ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOL_ADR             ,0x8D},   /*!< [|高ゲインから低ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_LTOM_ADR             ,0x3C},   /*!< [|低ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_RSSI_ADJ_H_ADR            ,0x2B},   /*!< [|高ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_M_ADR            ,0x4D},   /*!< [|中間ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_L_B2_ADR         ,0x7D},   /*!< [|低ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x88},   /*!< [|BANK切り替え:BANK3]  */
	{RADIO_BANK_SEL_ADR              ,0x33},   /*!< [|BANK切り替え:BANK6]  */
	{RADIO_BANK_SEL_ADR              ,0x55},   /*!< [|BANK切り替え:BANK7]  */
	{RADIO_DSSS_CTRL_ADR             ,0x05},   /*!< [|DSSS制御設定:]  */
	{RADIO_DSSS_MODE_ADR             ,0x45},   /*!< [|DSSSモード設定:]  */
	{RADIO_FEC_ENC_CTRL_ADR          ,0x00},   /*!< [|FECエンコーダ設定:]  */
	{RADIO_FEC_DEC_CTRL_ADR          ,0x00},   /*!< [|FECデコーダ設定:]  */
	{RADIO_SS_AFC_RANGE_SYNC_ADR     ,0x0A},   /*!< [|DSSS AFCレンジ設定(同期時):]  */
	{RADIO_SS_AFC_RANGE_ADR          ,0x0A},   /*!< [|DSSS AFCレンジ設定(データ受信時):]  */
	{RADIO_DSSS_RATE_SYNC_L_ADR      ,0xB3},   /*!< [|DSSS同期時受信チップレート設定(下位バイト):]  */
	{RADIO_DSSS_RATE_L_ADR           ,0xB3},   /*!< [|DSSSデータ受信時受信データレート設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT8_GATE_H_ADR   ,0x00},   /*!< [|DSSS同期確立時相関閾値設定(上位3ビット):]  */
	{RADIO_SS_SYNC_BIT8_GATE_L_ADR   ,0xF4},   /*!< [|DSSS同期確立時相関閾値設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT8_GATE2_L_ADR  ,0x04},   /*!< [|DSSS同期確立時相関閾値設定2(下位バイト):]  */
	{RADIO_SS_SYNC_BIT_GATE_H_ADR    ,0x00},   /*!< [|DSSS同期確立後相関閾値設定(上位3ビット:]  */
	{RADIO_SS_SYNC_BIT_GATE_L_ADR    ,0xEC},   /*!< [|DSSS同期確立後相関閾値設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT4_GATE_L_ADR   ,0x2C},   /*!< [|予約:]  */
	{RADIO_SS_SYNC_LOST_GATE_ADR     ,0x14},   /*!< [|予約:]  */
	{RADIO_AGC_AVE_OFST_SYNC_ADR     ,0x00},   /*!< [|予約:]  */
	{RADIO_AGC_AVE_OFST_ADR          ,0x00},   /*!< [|予約:]  */
	{RADIO_AGC_IIR_SET0_ADR          ,0x53},   /*!< [|予約:]  */
	{RADIO_AGC_IIR_SET1_ADR          ,0x25},   /*!< [|予約:]  */
	{RADIO_BIT8_SPDET_TH_L_ADR       ,0xF4},   /*!< [|予約:]  */
	{RADIO_DSSS_SET6_ADR             ,0x67},   /*!< [|予約:]  */
	{RADIO_DSSS_SET7_ADR             ,0x67},   /*!< [|予約:]  */
	{RADIO_DSSS_SET8_ADR             ,0x32},   /*!< [|予約:]  */
	{RADIO_DSSS_SET9_ADR             ,0x25},   /*!< [|予約:]  */
	{RADIO_BANK_SEL_ADR              ,0x99},   /*!< [|BANK切り替え:BANK10]  */
	{RADIO_BPSK_STEP_CTRL_ADR        ,0x10},   /*!< [|BPSKステップ制御設定:]  */
	{RADIO_BPSK_STEP_CLK_SET_ADR     ,0x02},   /*!< [|BPSKステップ制御クロック設定:]  */
	{RADIO_BPSK_STEP_SET0_ADR        ,0x10},   /*!< [|BPSKステップ制御設定0:]  */
	{RADIO_BPSK_STEP_SET1_ADR        ,0x21},   /*!< [|BPSKステップ制御設定1:]  */
	{RADIO_BPSK_STEP_SET2_ADR        ,0x11},   /*!< [|BPSKステップ制御設定2:]  */
	{RADIO_BPSK_STEP_SET3_ADR        ,0x22},   /*!< [|BPSKステップ制御設定3:]  */
	{RADIO_BPSK_STEP_SET4_ADR        ,0x11},   /*!< [|BPSKステップ制御設定4:]  */
	{RADIO_BPSK_STEP_SET5_ADR        ,0x42},   /*!< [|BPSKステップ制御設定5:]  */
	{RADIO_BPSK_STEP_SET6_ADR        ,0x34},   /*!< [|BPSKステップ制御設定6:]  */
	{RADIO_BPSK_STEP_SET7_ADR        ,0x34},   /*!< [|BPSKステップ制御設定7:]  */
	{RADIO_BPSK_STEP_SET8_ADR        ,0x45},   /*!< [|BPSKステップ制御設定8:]  */
	{RADIO_BPSK_STEP_SET9_ADR        ,0x63},   /*!< [|BPSKステップ制御設定9:]  */
	{RADIO_BPSK_STEP_SET10_ADR       ,0x74},   /*!< [|BPSKステップ制御設定10:]  */
	{RADIO_BPSK_STEP_SET11_ADR       ,0x66},   /*!< [|BPSKステップ制御設定11:]  */
	{RADIO_BPSK_STEP_SET12_ADR       ,0x56},   /*!< [|BPSKステップ制御設定12:]  */
	{RADIO_BPSK_STEP_SET13_ADR       ,0x35},   /*!< [|BPSKステップ制御設定13:]  */
	{RADIO_BPSK_STEP_SET14_ADR       ,0x45},   /*!< [|BPSKステップ制御設定14:]  */
	{RADIO_BPSK_STEP_SET15_ADR       ,0x55},   /*!< [|BPSKステップ制御設定15:]  */
	{RADIO_BPSK_STEP_SET16_ADR       ,0x44},   /*!< [|BPSKステップ制御設定16:]  */
	{RADIO_BPSK_STEP_SET17_ADR       ,0x45},   /*!< [|BPSKステップ制御設定17:]  */
	{RADIO_BPSK_STEP_SET18_ADR       ,0x22},   /*!< [|BPSKステップ制御設定18:]  */
	{RADIO_BPSK_STEP_SET19_ADR       ,0x12},   /*!< [|BPSKステップ制御設定19:]  */
	{RADIO_BPSK_STEP_SET20_ADR       ,0x11},   /*!< [|BPSKステップ制御設定20:]  */
	{RADIO_BPSK_STEP_SET21_ADR       ,0x00},   /*!< [|BPSKステップ制御設定21:]  */
	{RADIO_BPSK_STEP_SET22_ADR       ,0x00},   /*!< [|BPSKステップ制御設定22:]  */
	{RADIO_BPSK_STEP_SET23_ADR       ,0x00},   /*!< [|BPSKステップ制御設定23:]  */
	{RADIO_BPSK_STEP_SET24_ADR       ,0x00},   /*!< [|BPSKステップ制御設定24:]  */
	{RADIO_BPSK_STEP_SET25_ADR       ,0x00},   /*!< [|BPSKステップ制御設定25:]  */
	{RADIO_BPSK_STEP_SET26_ADR       ,0x00},   /*!< [|BPSKステップ制御設定26:]  */
	{RADIO_BPSK_STEP_SET27_ADR       ,0x00},   /*!< [|BPSKステップ制御設定27:]  */
	{RADIO_BPSK_STEP_SET28_ADR       ,0x00},   /*!< [|BPSKステップ制御設定28:]  */
	{RADIO_BPSK_STEP_SET29_ADR       ,0x00},   /*!< [|BPSKステップ制御設定29:]  */
	{RADIO_BPSK_STEP_SET30_ADR       ,0x00},   /*!< [|BPSKステップ制御設定30:]  */
	{RADIO_BPSK_STEP_SET31_ADR       ,0x20},   /*!< [|BPSKステップ制御設定31:]  */
	{RADIO_BPSK_STEP_SET32_ADR       ,0x23},   /*!< [|BPSKステップ制御設定32:]  */
	{RADIO_BPSK_STEP_SET33_ADR       ,0x21},   /*!< [|BPSKステップ制御設定33:]  */
	{RADIO_BPSK_STEP_SET34_ADR       ,0x21},   /*!< [|BPSKステップ制御設定34:]  */
	{RADIO_BPSK_STEP_SET35_ADR       ,0x33},   /*!< [|BPSKステップ制御設定35:]  */
	{RADIO_BPSK_STEP_SET36_ADR       ,0x43},   /*!< [|BPSKステップ制御設定36:]  */
	{RADIO_BPSK_STEP_SET37_ADR       ,0x55},   /*!< [|BPSKステップ制御設定37:]  */
	{RADIO_BPSK_STEP_SET38_ADR       ,0x54},   /*!< [|BPSKステップ制御設定38:]  */
	{RADIO_BPSK_STEP_SET39_ADR       ,0x53},   /*!< [|BPSKステップ制御設定39:]  */
	{RADIO_BPSK_STEP_SET40_ADR       ,0x65},   /*!< [|BPSKステップ制御設定40:]  */
	{RADIO_BPSK_STEP_SET41_ADR       ,0x66},   /*!< [|BPSKステップ制御設定41:]  */
	{RADIO_BPSK_STEP_SET42_ADR       ,0x47},   /*!< [|BPSKステップ制御設定42:]  */
	{RADIO_BPSK_STEP_SET43_ADR       ,0x36},   /*!< [|BPSKステップ制御設定43:]  */
	{RADIO_BPSK_STEP_SET44_ADR       ,0x54},   /*!< [|BPSKステップ制御設定44:]  */
	{RADIO_BPSK_STEP_SET45_ADR       ,0x43},   /*!< [|BPSKステップ制御設定45:]  */
	{RADIO_BPSK_STEP_SET46_ADR       ,0x43},   /*!< [|BPSKステップ制御設定46:]  */
	{RADIO_BPSK_STEP_SET47_ADR       ,0x24},   /*!< [|BPSKステップ制御設定47:]  */
	{RADIO_BPSK_STEP_SET48_ADR       ,0x11},   /*!< [|BPSKステップ制御設定48:]  */
	{RADIO_BPSK_STEP_SET49_ADR       ,0x22},   /*!< [|BPSKステップ制御設定49:]  */
	{RADIO_BPSK_STEP_SET50_ADR       ,0x11},   /*!< [|BPSKステップ制御設定50:]  */
	{RADIO_BPSK_STEP_SET51_ADR       ,0x12},   /*!< [|BPSKステップ制御設定51:]  */
	{RADIO_BPSK_STEP_SET52_ADR       ,0x01},   /*!< [|BPSKステップ制御設定52:]  */
	{RADIO_BPSK_STEP_SET53_ADR       ,0x00},   /*!< [|BPSKステップ制御設定53:]  */
	{RADIO_BPSK_STEP_SET54_ADR       ,0x00},   /*!< [|BPSKステップ制御設定54:]  */
	{RADIO_BPSK_STEP_SET55_ADR       ,0x00},   /*!< [|BPSKステップ制御設定55:]  */
	{RADIO_BPSK_STEP_SET56_ADR       ,0x00},   /*!< [|BPSKステップ制御設定56:]  */
	{RADIO_BPSK_STEP_SET57_ADR       ,0x00},   /*!< [|BPSKステップ制御設定57:]  */
	{RADIO_BPSK_STEP_SET58_ADR       ,0x00},   /*!< [|BPSKステップ制御設定58:]  */
	{RADIO_BPSK_STEP_SET59_ADR       ,0x00},   /*!< [|BPSKステップ制御設定59:]  */
	{RADIO_PADRV_CTRL_ADR            ,0x73},   /*!< [|PAドライバ制御設定:]  */
	{RADIO_PADRV_ADJ1_ADR            ,0x03},   /*!< [|PAドライバ調整1:]  */
	{RADIO_PADRV_ADJ2_L_ADR          ,0x00},   /*!< [|PAドライバ調整1(下位バイト):]  */
	{RADIO_PADRV_CLK_SET_L_ADR       ,0x01},   /*!< [|PAドライバ制御用クロック設定(下位バイト):]  */
	{RADIO_PADRV_UP_ADJ_ADR          ,0x02},   /*!< [|BPSKドライバ制御立上り開始時間設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|BANK切り替え:BANK0]  */
};

static const RADIO_PHY_SET_T init_920MHz_DSSS_200kcps[] = {
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|BANK切り替え:BANK0]  */
	{RADIO_CH_SET_ADR                ,0x03},   /*!< [|RFチャネル設定:]  */
	{RADIO_ED_CTRL_ADR               ,0x83},   /*!< [|ED値平均回数設定数:]  */
	{RADIO_SYNC_CONDITION1_ADR       ,0x02},   /*!< [|受信プリアンブル設定:]  */
	{RADIO_SYNC_CONDITION3_ADR       ,0x01},   /*!< [|誤り許容設定:]  */
	{RADIO_MON_CTRL_ADR              ,0x00},   /*!< [|モニタ出力信号選択設定:]  */
	{RADIO_GPIO1_CTRL_ADR            ,0x00},   /*!< [|GPIO1端子(ピン#17)制御設定:]  */
	{RADIO_DC_FIL_ADJ_ADR            ,0x15},   /*!< [|DCオフセット調整フィルタ設定:]  */
	{RADIO_PA_REG_ADJ_H_ADR          ,0x00},   /*!< [|PAレギュレータの出力電圧調整(上位ビット):]  */
	{RADIO_PA_REG_ADJ_L_ADR          ,0x89},   /*!< [|PAレギュレータの出力電圧調整(上位バイト):10dBm]  */
	{RADIO_CHFIL_BW_CCA_ADR          ,0x81},   /*!< [|CCA時チャネルフィルタ帯域幅設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x22},   /*!< [|BANK切り替え:BANK1]  */
	{RADIO_RX_RATE1_L_ADR            ,0x04},   /*!< [|受信データレート変換設定1(下位バイト):]  */
	{RADIO_RSSI_MAG_ADJ_ADR          ,0x19},   /*!< [|ED変換用RSSI補正設定:]  */
	{RADIO_AFC_GC_CTRL_ADR           ,0x01},   /*!< [|AFC/ゲイン制御設定:]  */
	{RADIO_CRC_POLY1_ADR             ,0x08},   /*!< [|CRC生成多項式1:]  */
	{RADIO_CRC_POLY0_ADR             ,0x10},   /*!< [|CRC生成多項式0:]  */
	{RADIO_CH_SPACE_H_ADR            ,0x0B},   /*!< [|チャネル間隔設定(上位バイト):100kHz]  */
	{RADIO_CH_SPACE_L_ADR            ,0x61},   /*!< [|チャネル間隔設定(下位バイト):100kHz]  */
	{RADIO_VCO_CAL_MAX_N_ADR         ,0x04},   /*!< [|VCO_CAL_Max周波数設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x44},   /*!< [|BANK切り替え:BANK2]  */
	{RADIO_NONPUBLIC_B2_ADR0E        ,0x52},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR16        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR19        ,0x08},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1A        ,0x6E},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR1C        ,0x55},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR29        ,0xC6},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2A        ,0x1F},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR2F        ,0xE7},   /*!< [|予約:]  */
	{RADIO_NONPUBLIC_B2_ADR32        ,0x4C},   /*!< [|予約:]  */
	{RADIO_GAIN_HHTH_ADR             ,0x8B},   /*!< [|高高ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOHH_ADR            ,0x3C},   /*!< [|高ゲインから高高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_HTOM_ADR             ,0x8B},   /*!< [|高ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOH_ADR             ,0x3C},   /*!< [|中間ゲインから高ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_MTOL_ADR             ,0x8B},   /*!< [|高ゲインから低ゲインへの切り替え閾値設定:]  */
	{RADIO_GAIN_LTOM_ADR             ,0x3C},   /*!< [|低ゲインから中間ゲインへの切り替え閾値設定:]  */
	{RADIO_RSSI_ADJ_H_ADR            ,0x2B},   /*!< [|高ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_M_ADR            ,0x4D},   /*!< [|中間ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_RSSI_ADJ_L_B2_ADR         ,0x7D},   /*!< [|低ゲイン動作時のRSSIオフセット値設定:]  */
	{RADIO_BANK_SEL_ADR              ,0x88},   /*!< [|BANK切り替え:BANK3]  */
	{RADIO_BANK_SEL_ADR              ,0x33},   /*!< [|BANK切り替え:BANK6]  */
	{RADIO_BANK_SEL_ADR              ,0x55},   /*!< [|BANK切り替え:BANK7]  */
	{RADIO_DSSS_CTRL_ADR             ,0x05},   /*!< [|DSSS制御設定:]  */
	{RADIO_DSSS_MODE_ADR             ,0x45},   /*!< [|DSSSモード設定:]  */
	{RADIO_FEC_ENC_CTRL_ADR          ,0x00},   /*!< [|FECエンコーダ設定:]  */
	{RADIO_FEC_DEC_CTRL_ADR          ,0x00},   /*!< [|FECデコーダ設定:]  */
	{RADIO_SS_AFC_RANGE_SYNC_ADR     ,0x04},   /*!< [|DSSS AFCレンジ設定(同期時):]  */
	{RADIO_SS_AFC_RANGE_ADR          ,0x04},   /*!< [|DSSS AFCレンジ設定(データ受信時):]  */
	{RADIO_SS_SYNC_BIT8_GATE_L_ADR   ,0x0C},   /*!< [|DSSS同期確立時相関閾値設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT8_GATE2_L_ADR  ,0x1C},   /*!< [|DSSS同期確立時相関閾値設定2(下位バイト):]  */
	{RADIO_SS_SYNC_BIT_GATE_H_ADR    ,0x00},   /*!< [|DSSS同期確立後相関閾値設定(上位3ビット:]  */
	{RADIO_SS_SYNC_BIT_GATE_L_ADR    ,0xD2},   /*!< [|DSSS同期確立後相関閾値設定(下位バイト):]  */
	{RADIO_SS_SYNC_BIT4_GATE_L_ADR   ,0x2C},   /*!< [|予約:]  */
	{RADIO_SS_SYNC_LOST_GATE_ADR     ,0x14},   /*!< [|予約:]  */
	{RADIO_AGC_AVE_OFST_SYNC_ADR     ,0x1A},   /*!< [|予約:]  */
	{RADIO_AGC_IIR_SET0_ADR          ,0x53},   /*!< [|予約:]  */
	{RADIO_AGC_IIR_SET1_ADR          ,0x25},   /*!< [|予約:]  */
	{RADIO_BIT8_SPDET_TH_L_ADR       ,0xF4},   /*!< [|予約:]  */
	{RADIO_DSSS_SET6_ADR             ,0x34},   /*!< [|予約:]  */
	{RADIO_DSSS_SET7_ADR             ,0x14},   /*!< [|予約:]  */
	{RADIO_DSSS_SET8_ADR             ,0x32},   /*!< [|予約:]  */
	{RADIO_DSSS_SET9_ADR             ,0x25},   /*!< [|予約:]  */
	{RADIO_BANK_SEL_ADR              ,0x99},   /*!< [|BANK切り替え:BANK10]  */
	{RADIO_BPSK_STEP_CTRL_ADR        ,0x10},   /*!< [|BPSKステップ制御設定:]  */
	{RADIO_BPSK_STEP_CLK_SET_ADR     ,0x01},   /*!< [|BPSKステップ制御クロック設定:]  */
	{RADIO_BPSK_STEP_SET0_ADR        ,0x20},   /*!< [|BPSKステップ制御設定0:]  */
	{RADIO_BPSK_STEP_SET1_ADR        ,0x11},   /*!< [|BPSKステップ制御設定1:]  */
	{RADIO_BPSK_STEP_SET2_ADR        ,0x21},   /*!< [|BPSKステップ制御設定2:]  */
	{RADIO_BPSK_STEP_SET3_ADR        ,0x21},   /*!< [|BPSKステップ制御設定3:]  */
	{RADIO_BPSK_STEP_SET4_ADR        ,0x21},   /*!< [|BPSKステップ制御設定4:]  */
	{RADIO_BPSK_STEP_SET5_ADR        ,0x51},   /*!< [|BPSKステップ制御設定5:]  */
	{RADIO_BPSK_STEP_SET6_ADR        ,0x43},   /*!< [|BPSKステップ制御設定6:]  */
	{RADIO_BPSK_STEP_SET7_ADR        ,0x34},   /*!< [|BPSKステップ制御設定7:]  */
	{RADIO_BPSK_STEP_SET8_ADR        ,0x44},   /*!< [|BPSKステップ制御設定8:]  */
	{RADIO_BPSK_STEP_SET9_ADR        ,0x54},   /*!< [|BPSKステップ制御設定9:]  */
	{RADIO_BPSK_STEP_SET10_ADR       ,0x65},   /*!< [|BPSKステップ制御設定10:]  */
	{RADIO_BPSK_STEP_SET11_ADR       ,0x66},   /*!< [|BPSKステップ制御設定11:]  */
	{RADIO_BPSK_STEP_SET12_ADR       ,0x66},   /*!< [|BPSKステップ制御設定12:]  */
	{RADIO_BPSK_STEP_SET13_ADR       ,0x34},   /*!< [|BPSKステップ制御設定13:]  */
	{RADIO_BPSK_STEP_SET14_ADR       ,0x36},   /*!< [|BPSKステップ制御設定14:]  */
	{RADIO_BPSK_STEP_SET15_ADR       ,0x55},   /*!< [|BPSKステップ制御設定15:]  */
	{RADIO_BPSK_STEP_SET16_ADR       ,0x35},   /*!< [|BPSKステップ制御設定16:]  */
	{RADIO_BPSK_STEP_SET17_ADR       ,0x36},   /*!< [|BPSKステップ制御設定17:]  */
	{RADIO_BPSK_STEP_SET18_ADR       ,0x23},   /*!< [|BPSKステップ制御設定18:]  */
	{RADIO_BPSK_STEP_SET19_ADR       ,0x21},   /*!< [|BPSKステップ制御設定19:]  */
	{RADIO_BPSK_STEP_SET20_ADR       ,0x01},   /*!< [|BPSKステップ制御設定20:]  */
	{RADIO_BPSK_STEP_SET21_ADR       ,0x00},   /*!< [|BPSKステップ制御設定21:]  */
	{RADIO_BPSK_STEP_SET22_ADR       ,0x00},   /*!< [|BPSKステップ制御設定22:]  */
	{RADIO_BPSK_STEP_SET23_ADR       ,0x00},   /*!< [|BPSKステップ制御設定23:]  */
	{RADIO_BPSK_STEP_SET24_ADR       ,0x00},   /*!< [|BPSKステップ制御設定24:]  */
	{RADIO_BPSK_STEP_SET25_ADR       ,0x00},   /*!< [|BPSKステップ制御設定25:]  */
	{RADIO_BPSK_STEP_SET26_ADR       ,0x00},   /*!< [|BPSKステップ制御設定26:]  */
	{RADIO_BPSK_STEP_SET27_ADR       ,0x00},   /*!< [|BPSKステップ制御設定27:]  */
	{RADIO_BPSK_STEP_SET28_ADR       ,0x00},   /*!< [|BPSKステップ制御設定28:]  */
	{RADIO_BPSK_STEP_SET29_ADR       ,0x00},   /*!< [|BPSKステップ制御設定29:]  */
	{RADIO_BPSK_STEP_SET30_ADR       ,0x00},   /*!< [|BPSKステップ制御設定30:]  */
	{RADIO_BPSK_STEP_SET31_ADR       ,0x20},   /*!< [|BPSKステップ制御設定31:]  */
	{RADIO_BPSK_STEP_SET32_ADR       ,0x22},   /*!< [|BPSKステップ制御設定32:]  */
	{RADIO_BPSK_STEP_SET33_ADR       ,0x21},   /*!< [|BPSKステップ制御設定33:]  */
	{RADIO_BPSK_STEP_SET34_ADR       ,0x22},   /*!< [|BPSKステップ制御設定34:]  */
	{RADIO_BPSK_STEP_SET35_ADR       ,0x32},   /*!< [|BPSKステップ制御設定35:]  */
	{RADIO_BPSK_STEP_SET36_ADR       ,0x53},   /*!< [|BPSKステップ制御設定36:]  */
	{RADIO_BPSK_STEP_SET37_ADR       ,0x55},   /*!< [|BPSKステップ制御設定37:]  */
	{RADIO_BPSK_STEP_SET38_ADR       ,0x63},   /*!< [|BPSKステップ制御設定38:]  */
	{RADIO_BPSK_STEP_SET39_ADR       ,0x43},   /*!< [|BPSKステップ制御設定39:]  */
	{RADIO_BPSK_STEP_SET40_ADR       ,0x66},   /*!< [|BPSKステップ制御設定40:]  */
	{RADIO_BPSK_STEP_SET41_ADR       ,0x66},   /*!< [|BPSKステップ制御設定41:]  */
	{RADIO_BPSK_STEP_SET42_ADR       ,0x56},   /*!< [|BPSKステップ制御設定42:]  */
	{RADIO_BPSK_STEP_SET43_ADR       ,0x45},   /*!< [|BPSKステップ制御設定43:]  */
	{RADIO_BPSK_STEP_SET44_ADR       ,0x44},   /*!< [|BPSKステップ制御設定44:]  */
	{RADIO_BPSK_STEP_SET45_ADR       ,0x43},   /*!< [|BPSKステップ制御設定45:]  */
	{RADIO_BPSK_STEP_SET46_ADR       ,0x34},   /*!< [|BPSKステップ制御設定46:]  */
	{RADIO_BPSK_STEP_SET47_ADR       ,0x15},   /*!< [|BPSKステップ制御設定47:]  */
	{RADIO_BPSK_STEP_SET48_ADR       ,0x12},   /*!< [|BPSKステップ制御設定48:]  */
	{RADIO_BPSK_STEP_SET49_ADR       ,0x12},   /*!< [|BPSKステップ制御設定49:]  */
	{RADIO_BPSK_STEP_SET50_ADR       ,0x12},   /*!< [|BPSKステップ制御設定50:]  */
	{RADIO_BPSK_STEP_SET51_ADR       ,0x11},   /*!< [|BPSKステップ制御設定51:]  */
	{RADIO_BPSK_STEP_SET52_ADR       ,0x02},   /*!< [|BPSKステップ制御設定52:]  */
	{RADIO_BPSK_STEP_SET53_ADR       ,0x00},   /*!< [|BPSKステップ制御設定53:]  */
	{RADIO_BPSK_STEP_SET54_ADR       ,0x00},   /*!< [|BPSKステップ制御設定54:]  */
	{RADIO_BPSK_STEP_SET55_ADR       ,0x00},   /*!< [|BPSKステップ制御設定55:]  */
	{RADIO_BPSK_STEP_SET56_ADR       ,0x00},   /*!< [|BPSKステップ制御設定56:]  */
	{RADIO_BPSK_STEP_SET57_ADR       ,0x00},   /*!< [|BPSKステップ制御設定57:]  */
	{RADIO_BPSK_STEP_SET58_ADR       ,0x00},   /*!< [|BPSKステップ制御設定58:]  */
	{RADIO_BPSK_STEP_SET59_ADR       ,0x00},   /*!< [|BPSKステップ制御設定59:]  */
	{RADIO_PADRV_CTRL_ADR            ,0x63},   /*!< [|PAドライバ制御設定:]  */
	{RADIO_PADRV_ADJ1_ADR            ,0x03},   /*!< [|PAドライバ調整1:]  */
	{RADIO_PADRV_ADJ2_H_ADR          ,0x02},   /*!< [|PAドライバ調整1(上位バイト):]  */
	{RADIO_PADRV_ADJ2_L_ADR          ,0x00},   /*!< [|PAドライバ調整1(下位バイト):]  */
	{RADIO_PADRV_CLK_SET_L_ADR       ,0x01},   /*!< [|PAドライバ制御用クロック設定(下位バイト):]  */
	{RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|BANK切り替え:BANK0]  */
};

struct rf_reg_set_s {
	const RADIO_PHY_SET_T *p;
	int16_t size;
};

typedef enum{
	PHY_ST_FORCE_TRXOFF=0x03,
	PHY_ST_RXON=0x06,
	PHY_ST_TXON=0x09,
	PHY_ST_TRXOFF=0x08
} PHY_TRX_STATE;

static const struct rf_reg_set_s rf_reg_set[] = {
	{ml7404_init,sizeof(ml7404_init)},
	{ml7404_sleep_on,sizeof(ml7404_sleep_on)/sizeof(RADIO_PHY_SET_T)},
	{ml7404_sleep_off,sizeof(ml7404_sleep_off)/sizeof(RADIO_PHY_SET_T)},
	{init_920MHz_GFSK_50kbps,sizeof(init_920MHz_GFSK_50kbps)/sizeof(RADIO_PHY_SET_T)},
	{init_920MHz_GFSK_100kbps,sizeof(init_920MHz_GFSK_100kbps)/sizeof(RADIO_PHY_SET_T)},
	{init_920MHz_DSSS_50kcps,sizeof(init_920MHz_DSSS_50kcps)/sizeof(RADIO_PHY_SET_T)},
	{init_920MHz_DSSS_100kcps,sizeof(init_920MHz_DSSS_100kcps)/sizeof(RADIO_PHY_SET_T)},
	{init_920MHz_DSSS_200kcps,sizeof(init_920MHz_DSSS_200kcps)/sizeof(RADIO_PHY_SET_T)}
};

typedef enum {
	PHY_INIT=0,
	PHY_SLEEP_ON,
	PHY_SLEEP_OFF,
	GFSK_50KBPS,
	GFSK_100KBPS,
	DSSS_50KCPS,
	DSSS_100KCPS,
	DSSS_200KCPS,
	MODE_MAX
} RF_PARAM_MODE;

#define BUFFER_SIZE	256
static struct {
	uint8_t bank;
	uint8_t tx[BUFFER_SIZE];
	uint8_t rx[BUFFER_SIZE];
	uint8_t data[65];
} reg;

static struct phy_param phy;
static struct{
	uint16_t mod_pages;
	uint8_t sf;
	uint8_t size;
} mod_params;

#define HW_EVENT_ALL     			0xFFFFFFL  /* Interrupt all mask */
#define HW_EVENT_VCO_CAL_DONE 0x000002L  /* VCO CAL DONE */
#define HW_EVENT_RF_STATE			0x000008L  /* VCO CAL DONE */

#define HW_EVENT_CCA_DONE     0x040000L  /* CCA DONE */
#define HW_EVENT_RF_STATUS    0x000400L  /* RF status */
#define HW_EVENT_TX_DONE      0x190000L  /* TX DONE */
#define HW_EVENT_TX_FIFO      0x190010L  /* TX FIFO */
#define HW_EVENT_RX_DONE      0x000B20L  /* RX DONE INT ENABLE */
#define HW_INT_FIFO_FULL      0x000020L  /* TX FIFO FULL*/
#define HW_INT_FIFO_EMPTY     0x000010L  /* TX FIFO EMPTY*/
#define HW_INT_RX_DONE        0x000100L  /* RX DONE */

static int regbank(uint8_t bank) {
	const char s0[] = "regbank error";
	uint8_t reg_data[2];
	uint8_t dummy;

	if(bank != reg.bank) {
		reg.bank  = bank;
		reg_data[0] = (RADIO_BANK_SEL_ADR << 1) + 0x01;
		switch(bank) {
			case 0:
				reg_data[1] = 0x11;
				break;
			case 1:
				reg_data[1] = 0x22;
				break;
			case 2:
				reg_data[1] = 0x44;
				break;
			case 3:
				reg_data[1] = 0x88;
				break;
			case 4:
				reg_data[1] = 0x88;
				break;
			case 6:
				reg_data[1] = 0x33;
				break;
			case 7:
				reg_data[1] = 0x55;
				break;
			case 8:
				reg_data[1] = 0x55;
				break;
			case 10:
				reg_data[1] = 0x77;
				break;
			case 0xFF:
				return STATUS_OK;
			default:
				alert(s0);
				return -EINVAL;
		}
		HAL_SPI_transfer(reg_data,2,&dummy,0);
	}
	return STATUS_OK;
}
static int reg_wr(uint8_t bank,uint8_t addr, int size) {
	int status = STATUS_OK;
	uint8_t dummy;
	if((size <= 1) || (size > 8)) {
		return -ENOMEM;
	}
	status = regbank(bank);
	if(status != STATUS_OK) {
		return status;
	}
	reg.data[0] = (uint8_t)((addr << 1) + 1);
	HAL_SPI_transfer(reg.data,size,&dummy,0);
	return STATUS_OK;
};
static int reg_rd(uint8_t bank,uint8_t addr, int size) {
	int status = STATUS_OK;
	uint8_t reg_addr;
	status = regbank(bank);
	if(status != STATUS_OK) {
		return status;
	}
	if(size > 65) return -ENOMEM;
	reg_addr = (uint8_t)((addr << 1) + 0);
	HAL_SPI_transfer(&reg_addr,1,reg.data,size);
	return STATUS_OK;
};

static int fifo_wr(int len) {
	uint8_t dummy;
	regbank(BANK_WR_TX_FIFO_ADR);
	reg.data[0] = (RADIO_WR_TX_FIFO_ADR << 1) + 1;
	HAL_SPI_transfer(reg.data,len,&dummy,0);
	return STATUS_OK;
}

static int fifo_rd(int len) {
	uint8_t reg_addr = (RADIO_RD_FIFO_ADR << 1) + 0;
	regbank(BANK_RD_FIFO_ADR);
	HAL_SPI_transfer(&reg_addr,1,reg.data,len);
	return STATUS_OK;
}

static void reg_block_wr(RF_PARAM_MODE mode) {
	const char s0[] = "reg_block error";
	const struct rf_reg_set_s *reg_set;
	uint8_t dummy;
	int i;
	if(mode >= MODE_MAX) {
		alert(s0);
		HAL_reset();
		return;
	}
	reg_set = &rf_reg_set[mode];
	for(i=0;i<reg_set->size;i++){
		reg.data[0] = (uint8_t)((reg_set->p[i].addr << 1) | 0x01);
		reg.data[1] = reg_set->p[i].val;
		HAL_SPI_transfer(reg.data,2,&dummy,0);
	}
	regbank(0xff);
}

void phy_reset(void) {
	HAL_GPIO_setValue(PHY_RESETN,LOW);
	HAL_delayMicroseconds(1000L);
	HAL_GPIO_setValue(PHY_RESETN,HIGH);
	HAL_delayMicroseconds(1000L);
}

/******************************************************************************/
/*! @brief Enable interrupt / Diseable interrupt
 * @detail Original function was REG_INTEN
 * @issue
 ******************************************************************************/
static void phy_inten(uint32_t inten)
{
	reg.data[1] = (uint8_t)((uint8_t)((inten) >>  0));
	reg.data[2] = (uint8_t)((uint8_t)((inten) >>  8));
	reg.data[3] = (uint8_t)((uint8_t)((inten) >> 16));
	reg_wr(BANK_INT_EN_GRP1_ADR,RADIO_INT_EN_GRP1_ADR,4);
}


/******************************************************************************/
/*! @brief Clear interrupt 
 * @detail Original function was REG_INTCLR
 * @issue
 ******************************************************************************/
static void phy_intclr(uint32_t intclr)
{
	reg.data[1] = (uint8_t)(~(uint8_t)((intclr) >>  0));
	reg.data[2] = (uint8_t)(~(uint8_t)((intclr) >>  8));
	reg.data[3] = (uint8_t)(~(uint8_t)((intclr) >> 16));
	reg_wr(BANK_INT_SOURCE_GRP1_ADR,RADIO_INT_SOURCE_GRP1_ADR, 4);
}
/******************************************************************************/
/*! @brief Clear interrupt 
 * @detail Original function was REG_INTCLR
 * @issue
 ******************************************************************************/
uint32_t phy_intsrc(void)
{
	uint32_t intsrc=0;
	reg_rd(BANK_INT_SOURCE_GRP1_ADR,RADIO_INT_SOURCE_GRP1_ADR, 3);
	memcpy(&intsrc,reg.data,3);
	return intsrc;
}

int phy_trx_state(PHY_TRX_STATE mode){
	reg.data[1] = (uint8_t)mode;
	reg_wr(BANK_RF_STATUS_ADR,RADIO_RF_STATUS_ADR,2);
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s %d %d\n",__func__,__LINE__,mode);
#endif
	return STATUS_OK;
}

struct phy_param *phy_init(void) {
	const char s0[] ="HAL_init error";
	struct hw_mode hwif;
	int status = -1;

	hwif.i2c_addr = 0x50;
	hwif.i2c_addr_bits = 16L;

	status = HAL_init(&hwif);

	if(status != 0){
		alert(s0);
		return NULL;
	}

	phy.id = 0;
	phy.in.size = BUFFER_SIZE;
	phy.in.data = reg.rx;
	phy.in.len = 0;
	phy.out.size = BUFFER_SIZE;
	phy.out.data = reg.tx;
	phy.out.len = 0;

	phy_sleep();

	return &phy;
}

/******************************************************************************/
/*! @brief Interrupt handler registration of the ML7396 module
 * @detail Handler of the interrupt that SINTN terminal generates at 'L' level
 ******************************************************************************/
int phy_sint_handler(void (*func)(void))
{
	HAL_GPIO_setInterrupt(func);
	return STATUS_OK;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int phy_timer_start(uint16_t msec,void (*func)(void))
{
	HAL_TIMER_start(msec, func);
	return STATUS_OK;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int phy_timer_stop(void)
{
	HAL_TIMER_stop();
	return STATUS_OK;
}

/* TODO: delete later */
int phy_setup(uint8_t page,uint8_t ch,uint8_t txPower,uint8_t antsw){
	const char s0[] = "phy_setup SINT LOCK";
	const char s1[] = "phy_setup VCO CAL LOCK";
	uint8_t data;
	uint32_t intsrc;
	int i;

	HAL_GPIO_getValue(PHY_REGPDIN,&data);
	if(data == HIGH) {
		HAL_GPIO_setValue(PHY_REGPDIN,LOW);
		HAL_delayMicroseconds(1000L);
	}
	HAL_GPIO_getValue(PHY_RESETN,&data);
	if(data == LOW) {
		HAL_GPIO_setValue(PHY_RESETN,HIGH);
		i=0;
		do {
			HAL_delayMicroseconds(1000L);
			HAL_GPIO_getValue(PHY_SINTN,&data);
			i++;
			if( i > 100) {
				alert(s0);
				phy_regdump();
				return -EDEADLK;
			}
		} while(data == 1);
		intsrc = phy_intsrc();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s %d %06x %d\n",__func__,__LINE__,intsrc,i);
		printk(KERN_INFO"%s %d %d %d\n",__func__,__LINE__,ch,page);
#endif

		reg_block_wr(PHY_INIT);
	} else {
		phy_trx_state(PHY_ST_FORCE_TRXOFF);
		phy_intclr(HW_EVENT_ALL);
		phy_inten(~HW_EVENT_ALL);
	}

	reg_rd(BANK_ID_CODE_ADR,RADIO_ID_CODE_ADR,1);
	if(reg.data[0] != 0x65) {
		phy_regdump();
		phy_sleep();
		return -EDEADLK;
	}

	mod_params.mod_pages += page;
	switch(mod_params.mod_pages) {
		case ((PHY_MODULATION_FSK << 8) + 1):					// GFSK 50kbps
#ifdef JP
			if((ch < 24) || (ch > 61)) { return -EINVAL;}
#else
			return -EINVAL;
#endif
			reg_block_wr(GFSK_50KBPS);
			reg.data[1] = (uint8_t)(ch-24),reg_wr(BANK_CH_SET_ADR,RADIO_CH_SET_ADR,2);
			phy.unit_backoff_period = 320;
			break;
		case ((PHY_MODULATION_FSK << 8) + 2):					// GFSK 100kbps
#ifdef JP
			if((ch < 24) || (ch > 60) || (ch == 32))  { return -EINVAL;}
#else
			return -EINVAL;
#endif
			reg_block_wr(GFSK_100KBPS);
			reg.data[1] = (uint8_t)(ch-24),reg_wr(BANK_CH_SET_ADR,RADIO_CH_SET_ADR,2);
			phy.unit_backoff_period = 320;
			break;
		case ((PHY_MODULATION_DSSS <<8) +1):					// DSSS 50kcps
#ifdef JP
			if((ch < 24) || (ch > 61)) { return -EINVAL;}
#else
			return -EINVAL;
#endif
			reg_block_wr(DSSS_50KCPS);
			reg.data[1] = (uint8_t)(ch-24),reg_wr(BANK_CH_SET_ADR,RADIO_CH_SET_ADR,2);
			switch(mod_params.sf) {
				case 32:
					data = 0x11;
					break;
				case 64:
					data = 0x22;
					break;
				default:
					return -EINVAL;
			}
			reg_wr(BANK_SF_CTRL_ADR,RADIO_SF_CTRL_ADR,2);
			phy.unit_backoff_period = 0;
			break;
		case ((PHY_MODULATION_DSSS <<8) +2):					// DSSS 100kcps
#ifdef JP
			if((ch < 24) || (ch > 60) || (ch == 32))  { return -EINVAL;}
#else
			return -EINVAL;
#endif
			reg_block_wr(DSSS_100KCPS);
			reg.data[1] = (uint8_t)(ch-24),reg_wr(BANK_CH_SET_ADR,RADIO_CH_SET_ADR,2);
			switch(mod_params.sf) {
				case 32:
					data = 0x11;
					break;
				case 64:
					data = 0x22;
					break;
				default:
					return -EINVAL;
			}
			reg_wr(BANK_SF_CTRL_ADR,RADIO_SF_CTRL_ADR,2);
			phy.unit_backoff_period = 0;
			break;
		case ((PHY_MODULATION_DSSS <<8) + 5):					// DSSS 200kcps
#ifdef JP
			if((ch<24) || ((ch >= 29) && (ch <=32)) || (ch > 57))  { return -EINVAL;}
#else
			return -EINVAL;
#endif
			reg_block_wr(DSSS_200KCPS);
			reg.data[1] = (uint8_t)((ch-24)*2+3), reg_wr(BANK_CH_SET_ADR,RADIO_CH_SET_ADR,2);
			switch(mod_params.sf) {
				case 32:
					reg.data[1] = 0x11;
					break;
				case 64:
					reg.data[1] = 0x22;
					break;
				default:
					return -EINVAL;
			}
			reg_wr(BANK_SF_CTRL_ADR,RADIO_SF_CTRL_ADR,2);

			phy.unit_backoff_period = 0;
			break;
		default:
			return -EINVAL;
	}

	// CCA時データ無効化
	reg.data[1] = 0x01;
	reg_wr(BANK_NONPUBLIC_B3_ADR2D,RADIO_NONPUBLIC_B3_ADR2D,2);
	// AUTO TRX OFF
	reg.data[1] = 0x00;
	reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
	// RX FIFO しきい値設定
	reg.data[1] = 0x80 | 0x20;
	reg.data[2] = 0x80 | 0x1F;
	reg_wr(BANK_RXFIFO_THRH_ADR,RADIO_RXFIFO_THRH_ADR,3);

	// set calibration parameters
	switch(txPower) {
		case 1:
			HAL_I2C_read((uint8_t)0x2B,reg.data+1,(uint8_t)2);
			break;
		case 20:
			HAL_I2C_read((uint8_t)0x29,reg.data+1,(uint8_t)2);
			break;
		default:
			return -EINVAL;
	}
	reg_wr(BANK_PA_REG_ADJ_H_ADR,RADIO_PA_REG_ADJ_H_ADR,3);

	HAL_I2C_read((uint8_t)0x81,reg.data+1,(uint8_t)2);
	reg_wr(BANK_FREQ_ADJ_H_ADR,RADIO_FREQ_ADJ_H_ADR,3);

	switch(mod_params.mod_pages) {
		case ((PHY_MODULATION_FSK << 8) + 1):					// GFSK 50kbps
		case ((PHY_MODULATION_DSSS <<8) +1):					// DSSS 50kcps
			HAL_I2C_read((uint8_t)0x8A,reg.data+1,(uint8_t)2);
			break;
		case ((PHY_MODULATION_FSK << 8) + 2):					// GFSK 100kbps
		case ((PHY_MODULATION_DSSS <<8) +2):					// DSSS 100kcps
			HAL_I2C_read((uint8_t)0x88,reg.data+1,(uint8_t)2);
			break;
		case ((PHY_MODULATION_DSSS <<8) + 5):					// DSSS 200kcps
			HAL_I2C_read((uint8_t)0x8C,reg.data+1,(uint8_t)2);
			break;
	}
	reg_wr(BANK_RSSI_ADJ_ADR,RADIO_RSSI_ADJ_ADR,2);
	reg.data[1] = reg.data[2];
	reg_wr(BANK_RSSI_MAG_ADJ_ADR,RADIO_RSSI_MAG_ADJ_ADR,2);

	phy_intclr(HW_EVENT_ALL);
	phy_inten(HW_EVENT_VCO_CAL_DONE);

	// VCO CAL
	reg.data[1] = 1;
	reg_wr(BANK_VCO_CAL_START_ADR,RADIO_VCO_CAL_START_ADR,2);
	i=0;

	do {
		HAL_delayMicroseconds(1000L);
		HAL_GPIO_getValue(PHY_SINTN,&data);
		i++;
		if( i > 100) {
			alert(s1);
			phy_regdump();
			return -EDEADLK;
		}
	} while(data == 1);
	intsrc = phy_intsrc();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s %d %06x %d\n",__func__,__LINE__,intsrc,i);
#endif

	return STATUS_OK;
}

int phy_setModulation(int8_t mod, int8_t sf) {
	int status = STATUS_OK;
	switch(mod) {
		case PHY_MODULATION_FSK:
			mod_params.mod_pages = ((uint16_t)mod)<<8;
			mod_params.sf = 0;
			mod_params.size = 0;
			break;
		case PHY_MODULATION_DSSS:
			if((sf != 32) && (sf != 64)) {
				status = -EINVAL;
			} else {
				mod_params.mod_pages = ((uint16_t)mod)<<8;
				mod_params.sf = sf;
			}
			break;
		default:
			status = -EINVAL;
			break;
	}

	return status;
}
int phy_getModulation(int8_t *mod, int8_t *sf) {
	*mod = (uint8_t)(mod_params.mod_pages >> 8 & 0x00FF);
	*sf = mod_params.sf;
	return STATUS_OK;
}

int phy_txpre(TX_MODE mode) {
	int status;
	switch(mode) {
		case AUTO_TX:
#if !defined(LAZURITE_IDE) && defined(DEBUG)
			printk(KERN_INFO"%s %d %06x\n",__func__,__LINE__,phy_intsrc());
#endif
			status = phy_txstart();
			break;
		case MANUAL_TX:
			status = STATUS_OK;
			break;
		default:
			status =-EINVAL;
			break;
	}

	return status;
}
int phy_ccaCtrl(uint32_t us){
	long d;
	int status;
	// data invalid setting during CCA
	d = map((long)us,1600L,4000L,92L,242L);

	if(d>1023) d = 1023;
	reg.data[1] = (uint8_t)((d>>8)&0x03);
	reg.data[2] = (uint8_t)(d&0xFF);
	reg_wr(BANK_IDLE_WAIT_H_ADR,RADIO_IDLE_WAIT_H_ADR,3);

	reg.data[1] = 0x50;
	reg_wr(BANK_CCA_CTRL_ADR,RADIO_CCA_CTRL_ADR,2);

	phy_intclr(HW_EVENT_ALL);
	phy_inten(HW_EVENT_CCA_DONE);
	status = phy_trx_state(PHY_ST_RXON);
	//if(status != STATUS_OK) return status;
	return STATUS_OK;
}
uint8_t phy_ccadone(void) {
	volatile uint8_t ccadone;
	phy_inten(~HW_EVENT_ALL);
	reg_rd(BANK_CCA_CTRL_ADR,RADIO_CCA_CTRL_ADR,1);
	ccadone = reg.data[0];
	if(ccadone & 0x10) {
		reg.data[1] = 0x80;
		reg_wr(BANK_CCA_CTRL_ADR,RADIO_CCA_CTRL_ADR,2);
		phy_trx_state(PHY_ST_FORCE_TRXOFF);
	}
	return ccadone;
}

int phy_txstart(void) {
	int len;
	int retry = 0;
	do {
		reg.data[1] = 0x81;
		reg_wr(BANK_STATE_CLR_ADR,RADIO_STATE_CLR_ADR,2);
		len = phy.out.len + 2;
		reg.data[1] = (uint8_t)((len >> 8) & 0xFF);
		reg.data[2] = (uint8_t)((len ) & 0xFF);
		reg_wr(BANK_TX_PKT_LEN_H_ADR,RADIO_TX_PKT_LEN_H_ADR,3);
		if(phy.out.len > 64) {
			reg.data[1] = 0x30;
			reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
			reg.data[1]= 0x80 | 0x21;
			reg.data[2]= 0x80 | 0x20;					// FIFO empty level = 32byte
			reg_wr(BANK_TXFIFO_THRH_ADR,RADIO_TXFIFO_THRH_ADR,3);
			memcpy(&reg.data[1],phy.out.data,64);
			phy.out_ptr = 64;
			fifo_wr(65);
			phy_intclr(HW_EVENT_ALL);
			phy_inten(HW_EVENT_TX_FIFO);
		} else {
			reg.data[1] = 0x10;
			reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
			reg.data[1]=0;
			reg.data[2]=0;
			reg_wr(BANK_TXFIFO_THRH_ADR,RADIO_TXFIFO_THRH_ADR,3);
			memcpy(&reg.data[1],phy.out.data,phy.out.len);
			fifo_wr(phy.out.len+1);
			phy.out_ptr = phy.out.len;
			phy_intclr(HW_EVENT_ALL);
			phy_inten(HW_EVENT_TX_DONE);
		}
		reg_rd(BANK_RF_STATUS_ADR,RADIO_RF_STATUS_ADR,1);
		if((reg.data[0] & 0x0F) == 0x09) {
			break;
		} else {
			retry++;
		}
	} while(retry <5 );
	return STATUS_OK;
}

FIFO_STATE phy_txfifo(void) {
	FIFO_STATE status = FIFO_CONT;
	uint32_t intsrc;
	int len;
	const char s0[] = "phy_txfifo error";
	intsrc = phy_intsrc();

	len = phy.out.len - phy.out_ptr;
	if(intsrc & 0x180000) {
		alert(s0);
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s %d %06x\n",__func__,__LINE__,intsrc);
#endif
		phy_intclr(HW_EVENT_ALL);
		phy_inten(~HW_EVENT_ALL);
		return CRC_ERROR;
	} else if(intsrc & 0x010000) {
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s %d %06x\n",__func__,__LINE__,intsrc);
#endif
		phy_intclr(HW_EVENT_ALL);
		phy_inten(~HW_EVENT_ALL);
		return FIFO_DONE;
	} else if (len <= 32) {
		reg.data[1]=0;
		reg.data[2]=0;
		reg_wr(BANK_TXFIFO_THRH_ADR,RADIO_TXFIFO_THRH_ADR,3);
		phy_inten(HW_EVENT_TX_DONE);
	} else {
		len = 32;
	}
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s %d %06x %d\n",__func__,__LINE__,intsrc,len);
#endif
	memcpy(&reg.data[1],phy.out.data+phy.out_ptr,len);
	fifo_wr(len+1);
	phy.out_ptr += len;
	phy_intclr(HW_INT_FIFO_EMPTY);
	return status;
}

void phy_txdone(void) {
	phy_inten(~HW_EVENT_ALL);
	return ;
}

void phy_rxstart(void) {
	phy.in_ptr=0;
	phy.in.len=0;
	reg.data[1] = 0x82;
	reg_wr(BANK_STATE_CLR_ADR,RADIO_STATE_CLR_ADR,2);
	phy_intclr(HW_EVENT_ALL);
	phy_inten(HW_EVENT_RX_DONE);
	phy_trx_state(PHY_ST_RXON);
}

FIFO_STATE phy_rxdone(void){
	uint32_t intsrc;
	int len;
	const char s0[]="rx data length over";
	const char s1[]="rx fifo over run";
	FIFO_STATE state=FIFO_DONE;

	intsrc = phy_intsrc();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s %d %06x\n",__func__,__LINE__,intsrc);
#endif
	if(intsrc & 0x000A00) {
		phy_intclr(HW_EVENT_ALL);
		phy_inten(~HW_EVENT_ALL);
		return CRC_ERROR;
	}
	if(phy.in.len == 0) {
		reg_rd(BANK_RX_PKT_LEN_H_ADR,RADIO_RX_PKT_LEN_H_ADR,2);
		phy.in.len = reg.data[0] & 0x07;
		phy.in.len = (phy.in.len << 8) + reg.data[1];
		if (phy.in.len > phy.in.size) {
			alert(s0);
			phy_intclr(HW_EVENT_ALL);
			phy_inten(~HW_EVENT_ALL);
			return CRC_ERROR;
		}
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s %d RX_PKT_LEN = %04x\n",__func__,__LINE__,phy.in.len);
#endif
	}
	if(intsrc&0x000100) {
		len = phy.in.len - phy.in_ptr;
		if(len > 64) {
			alert(s1);
			phy_intclr(HW_EVENT_ALL);
			phy_inten(~HW_EVENT_ALL);
			return CRC_ERROR;
		}
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s %d FIFO_DONE %d %d %d\n",__func__,__LINE__,phy.in.len,phy.in_ptr,len);
#endif
		fifo_rd(len);
		if(phy.in.size < phy.in_ptr+len) {
			phy_intclr(HW_EVENT_ALL);
			return CRC_ERROR;
		}
		memcpy(phy.in.data+phy.in_ptr,reg.data,len);
		reg_rd(BANK_ED_RSLT_ADR,RADIO_ED_RSLT_ADR,1);
		phy.in.data[phy.in.len-2] = reg.data[0];
		phy.in.len = phy.in.len-1;
		state=FIFO_DONE;
		phy_intclr(HW_EVENT_ALL);
		phy_inten(~HW_EVENT_ALL);
	} else {
		reg_rd(BANK_RX_FIFO_LAST_ADR,RADIO_RX_FIFO_LAST_ADR,1);
		len = reg.data[0];
		fifo_rd(len);
		memcpy(phy.in.data+phy.in_ptr,reg.data,len);
		phy.in_ptr += len;
		state=FIFO_CONT;
		phy_intclr(HW_INT_FIFO_FULL);
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s %d FIFO_CONT %d %d %d\n",__func__,__LINE__,phy.in.len,phy.in_ptr,len);
#endif
	}
	return state;
}
void phy_stop(void){
	phy_trx_state(PHY_ST_TRXOFF);
	phy_intclr(HW_EVENT_ALL);
	phy_inten(~HW_EVENT_ALL);
	return;
}
void phy_clrAddrFilt(void){
	return;
}
void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr) {
	return;
}

int phy_ed(int mode,uint8_t **data,int *size) {
	uint32_t *avr_p;
	uint8_t ch;
	int cycle;
	int islock;
	const uint8_t ch_num[2]={38,37};
	phy.in.len = 0;
	phy.out.len = 0;
	switch(mode) {
		case 1:
			avr_p = (uint32_t *) phy.in.data;
			memset(phy.out.data,0,1);
			memset(avr_p,0,sizeof(uint32_t));
			reg.data[1]=0x08, reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
			phy_inten(~HW_EVENT_ALL);

			reg.data[1]=0x83, reg_wr(BANK_ED_CTRL_ADR,RADIO_ED_CTRL_ADR,2);
			phy_trx_state(PHY_ST_RXON);

			for(islock = 0; islock < 100 ; islock++) {
				HAL_delayMicroseconds(100);
				reg_rd(BANK_ED_CTRL_ADR,RADIO_ED_CTRL_ADR,1);
				if(reg.data[0] & 0x10) break;
			}
			if(islock >= 100) return -EDEADLK;

			for(cycle = 0; cycle < 128; cycle ++) {
				HAL_delayMicroseconds(128);
				reg_rd(BANK_ED_RSLT_ADR,RADIO_ED_RSLT_ADR,1);
				if(phy.out.data[0]  < reg.data[0]) phy.out.data[0] = reg.data[0];
				avr_p[0] += reg.data[0];
			}
			avr_p[0] = avr_p[0]/128;
			phy.out.data[1] = (uint8_t)avr_p[0];
			phy.out.len = 2;

			reg.data[1]=0x00, reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
			reg.data[1]=0x83, reg_wr(BANK_ED_CTRL_ADR,RADIO_ED_CTRL_ADR,2);
			phy_trx_state(PHY_ST_TRXOFF);
			phy_intclr(HW_EVENT_ALL);
			break;
		case 2:
		case 3:
			avr_p = (uint32_t *) phy.in.data;
			memset(phy.out.data,0,ch_num[mode-2]);
			memset(avr_p,0,sizeof(uint32_t)*ch_num[mode-2]);
			reg.data[1]=0x08, reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
			reg.data[1]=0x83, reg_wr(BANK_ED_CTRL_ADR,RADIO_ED_CTRL_ADR,2);
			phy_inten(~HW_EVENT_ALL);

			phy_trx_state(PHY_ST_TRXOFF);
			phy_setup(mode-1,24, 20,0);
			for(cycle = 0; cycle < 128; cycle ++) {
				for(ch=0;ch<ch_num[mode-2];ch++) {
					reg.data[1] = ch,   reg_wr(BANK_CH_SET_ADR,RADIO_CH_SET_ADR,2);
					phy_trx_state(PHY_ST_RXON);
					for(islock = 0; islock < 100 ; islock++) {
						reg_rd(BANK_ED_CTRL_ADR,RADIO_ED_CTRL_ADR,1);
						if((reg.data[0] & 0x10) != 0) break;
					}
					if(islock >= 100) {
						return -EDEADLK;
					}
					HAL_delayMicroseconds(128);
					reg_rd(BANK_ED_RSLT_ADR,RADIO_ED_RSLT_ADR,1);
					if(phy.out.data[ch]  < reg.data[0]) phy.out.data[ch] = reg.data[0];
					avr_p[ch] += reg.data[0];
					phy_trx_state(PHY_ST_TRXOFF);
				}
			}
			for(ch=0;ch<ch_num[mode-2];ch++) {
				phy.out.data[ch_num[mode-2]+ch] = avr_p[ch]/128;
			}
			phy.out.len = ch_num[mode-2]*2;
			reg.data[1]=0x00, reg_wr(BANK_RF_STATUS_CTRL_ADR,RADIO_RF_STATUS_CTRL_ADR,2);
			reg.data[1]=0x83, reg_wr(BANK_ED_CTRL_ADR,RADIO_ED_CTRL_ADR,2);
			phy_intclr(HW_EVENT_ALL);
			break;
		default:
			return -EINVAL;
			break;
	}
	*data = phy.out.data;
	*size = phy.out.len;
	return STATUS_OK;
}

void phy_sleep() {
	HAL_GPIO_setValue(PHY_RESETN,LOW);
	HAL_delayMicroseconds(1000);
	HAL_GPIO_setValue(PHY_REGPDIN,HIGH);
	return;
}

// following function is for debug. and test.bin use it.
void phy_monitor(void) {
	uint32_t intsrc;
#ifdef LAZURITE_IDE
	const char s1[] = "PHY_MONITOR";
	const char s2[] = "INT SOURCE:: ";
	const char s3[] = ",";
	const char s4[] = "INT ENABLE:: ";
	const char s5[] = "RF STATUS:: ";
	const char s6[] = "RF CCA CNTL:: ";
	const char s7[] = "PACKET MODE SET:: ";
	const char s8[] = "PD DATA REQ:: ";
	const char s9[] = "PD DATA IND:: ";
	const char s10[] = "AUTO ACK SET: ";
#endif
	// READ INT SOURCE
	intsrc = phy_intsrc();
#ifndef LAZURITE_IDE
	printk(KERN_INFO"INT SOURCE:: %06x", intsrc);
#else
	delay(10);
	Serial.println(s1);
	Serial.print(s2);
	Serial.print_long(intsrc,HEX);
#endif

	// READ RF STATE
	reg_rd(BANK_RF_STATUS_ADR,RADIO_RF_STATUS_ADR, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"RF STATUS:: %x\n", reg.data[0]);
#else
	Serial.print(s5);
	Serial.println_long((long)reg.data[0],HEX);
#endif
	return;
}
int phy_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
	int status = -ENOMEM;
	if(size<=sizeof(reg.data)) {
		reg_rd(bank,addr,size);
		memcpy(data,reg.data,size);
		status = STATUS_OK;
	}
	return status;
}
int phy_regwrite(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
	int status = -ENOMEM;
	if(size<=sizeof(reg.data)-1) {
		reg.data[0] = addr;
		memcpy(reg.data+1,data,size);
		reg_wr(bank,addr,size+1);
		status = STATUS_OK;
	}
	return status;
}
void phy_regdump(void) {
	uint8_t bank,dump_cnt;
	const uint8_t bank_map[]={0,1,2,3,4,6,7,8,10};
#ifdef LAZURITE_IDE
	uint8_t i;
	const char s1[] = "-----------------/ bank";
	const char s2[] = " /---------------";
	const char s3[] = " ";
	const char s4[] = "0";
	const char s5[] = "";
#endif

	for(bank = 0; bank<sizeof(bank_map);bank++) {
#ifdef LAZURITE_IDE
		Serial.print(s1);
		Serial.print_long((long)(bank-8),DEC);
		Serial.println(s2);
#else
		printk(KERN_INFO"-----------------/ bank%d /---------------",bank_map[bank]);
#endif
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt+=16) {
			reg_rd(bank_map[bank], dump_cnt, 16);
#ifdef LAZURITE_IDE
			for(i=0;i<16;i++) {
				Serial.print(s3);
				if(reg.data[i] < 16) {
					Serial.print(s4);
				}
				Serial.print_long((long)reg.data[i],HEX);
			}
			Serial.println(s5);
#else
			printk(KERN_INFO"%02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X\n",
					reg.data[0],
					reg.data[1],
					reg.data[2],
					reg.data[3],
					reg.data[4],
					reg.data[5],
					reg.data[6],
					reg.data[7],
					reg.data[8],
					reg.data[9],
					reg.data[10],
					reg.data[11],
					reg.data[12],
					reg.data[13],
					reg.data[14],
					reg.data[15]
					);
#endif
		}
	}

	return;
}

