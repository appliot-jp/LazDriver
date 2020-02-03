#include "lazurite.h"
#include "ml7404.h"

const RADIO_PHY_SET_T init_920MHz_GFSK_100kbps[] = {
    {RADIO_BANK_SEL_ADR              ,0x11},   /*!< [|RADIO_BANK_SEL_ADR              :BANK0]  */
    {RADIO_CLK_SET2_ADR              ,0xC3},   /*!< [|クロック制御2:クロックソースの選択 (TCXO使用時)]  */
    {RADIO_PKT_CTRL1_ADR             ,0x16},   /*!< [|パケットフォーマット設定1:Wi-SUN設定(Format C)]  */
    {RADIO_PKT_CTRL2_ADR             ,0x5D},   /*!< [|パケットフォーマット設定2:Wi-SUN設定(CRC16)]  */
    {RADIO_DRATE_SET_ADR             ,0xBB},   /*!< [|データレート設定:]  */
    {RADIO_ED_CTRL_ADR               ,0x83},   /*!< [|ED値平均回数設定数:]  */
    {RADIO_TXPR_LEN_L_ADR            ,0x3C},   /*!< [|送信プリアンブル長設定(下位バイト):Wi-SUN設定]  */
    {RADIO_MON_CTRL_ADR              ,0x00},   /*!< [|モニタ出力信号選択設定:]  */
    {RADIO_GPIO1_CTRL_ADR            ,0x00},   /*!< [|GPIO1端子(ピン#17)制御設定:]  */
    {RADIO_SPI_EXT_PA_CTRL_ADR       ,0x00},   /*!< [|SPIインタフェースIO /外部PA制御設定:SDO出力OpenDrain設定]  */
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
