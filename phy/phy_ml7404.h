/* phy_ml7404.h -ML7404 register address header file 
 * 
 * Copyright (c) 2017  Communication Technology Inc.,
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

#ifndef _INCLUDE_ML7404_REG_H
#define _INCLUDE_ML7404_REG_H


//#ifdef LAZURITE_IDE
//	include <common.h>
//#endif

/** Register map
 */
/*      name                   bank, address */
#define REG_ADR_RST_SET           0, 0x01  /* Software reset setting */
#define REG_ADR_CLK_SET1          0, 0x02  /* new */
#define REG_ADR_CLK_SET2          0, 0x03  /* new */
#define REG_ADR_PKT_CTRL1         0, 0x04  /* new */
#define REG_ADR_PKT_CTRL2         0, 0x05  /* new */
#define REG_ADR_DRATE_SET         0, 0x06  /* new */
#define REG_ADR_DATA_SET1         0, 0x07  /* new */
#define REG_ADR_DATA_SET2         0, 0x08  /* new */
#define REG_ADR_CH_SET            0, 0x09  /* RF channel setting */
#define REG_ADR_RF_STATUS_CTRL    0, 0x0A  /* new */
#define REG_ADR_RF_STATUS         0, 0x0B  /* RFstate setting and status indication */
#define REG_ADR_DIO_SET           0, 0x0C  /* new */
#define REG_ADR_INT_SOURCE_GRP1   0, 0x0D  /* FIFO clear setting and interrupt status for INT00 to INT05 */
#define REG_ADR_INT_SOURCE_GRP2   0, 0x0E  /* Interrupt status for INT08 to INT15 */
#define REG_ADR_INT_SOURCE_GRP3   0, 0x0F  /* Interrupt status for INT16 to INT23 */
#define REG_ADR_INT_EN_GRP1       0, 0x10  /* Interrupt mask for INT00 to INT05 */
#define REG_ADR_INT_EN_GRP2       0, 0x11  /* Interrupt mask for INT08 to INT15 */
#define REG_ADR_INT_EN_GRP3       0, 0x12  /* Interrupt mask for INT16 to INT23 */
#define REG_ADR_CRC_ERR_H         0, 0x13  /* new */
#define REG_ADR_CRC_ERR_M         0, 0x14  /* new */
#define REG_ADR_CRC_ERR_L         0, 0x15  /* new */
#define REG_ADR_STATE_CLR         0, 0x16  /* new */
#define REG_ADR_TXFIFO_THRH       0, 0x17  /* new */
#define REG_ADR_TXFIFO_THRL       0, 0x18  /* new */
#define REG_ADR_RXFIFO_THRH       0, 0x19  /* new */
#define REG_ADR_RXFIFO_THRL       0, 0x1A  /* new */
#define REG_ADR_C_CHECK_CTRL      0, 0x1B  /* new */
#define REG_ADR_M_CHECK_CTRL      0, 0x1C  /* new */
#define REG_ADR_A_CHECK_CTRL      0, 0x1D  /* new */
#define REG_ADR_C_FIELD_CODE1     0, 0x1E  /* new */
#define REG_ADR_C_FIELD_CODE2     0, 0x1F  /* new */
#define REG_ADR_C_FIELD_CODE3     0, 0x20  /* new */
#define REG_ADR_C_FIELD_CODE4     0, 0x21  /* new */
#define REG_ADR_C_FIELD_CODE5     0, 0x22  /* new */
#define REG_ADR_M_FIELD_CODE1     0, 0x23  /* new */
#define REG_ADR_M_FIELD_CODE2     0, 0x24  /* new */
#define REG_ADR_M_FIELD_CODE3     0, 0x25  /* new */
#define REG_ADR_M_FIELD_CODE4     0, 0x26  /* new */
#define REG_ADR_A_FIELD_CODE1     0, 0x27  /* new */
#define REG_ADR_A_FIELD_CODE2     0, 0x28  /* new */
#define REG_ADR_A_FIELD_CODE3     0, 0x29  /* new */
#define REG_ADR_A_FIELD_CODE4     0, 0x2A  /* new */
#define REG_ADR_A_FIELD_CODE5     0, 0x2B  /* new */
#define REG_ADR_A_FIELD_CODE6     0, 0x2C  /* new */
#define REG_ADR_SLEEP_WU_SET      0, 0x2D  /* new */
#define REG_ADR_WUT_CLK_SET       0, 0x2E  /* new */
#define REG_ADR_WUT_INTERVAL_H    0, 0x2F  /* new */
#define REG_ADR_WUT_INTERVAL_L    0, 0x30  /* new */
#define REG_ADR_WU_DURAION        0, 0x31  /* new */
#define REG_ADR_GT_SET            0, 0x32  /* new */
#define REG_ADR_GT_CLK_SET        0, 0x33  /* new */
#define REG_ADR_GT1_TIMER         0, 0x34  /* new */
#define REG_ADR_GT2_TIMER         0, 0x35  /* new */
#define REG_ADR_CCA_IGNORE_LEVEL  0, 0x36  /* ED threshold level setting for excluding CCA judgement */
#define REG_ADR_CCA_LEVEL         0, 0x37  /* CCA threshold level setting */
#define REG_ADR_CCA_ABORT         0, 0x38  /* Timing setting for forced termincation of CCA operation */
#define REG_ADR_CCA_CNTRL         0, 0x39  /* CCA control setting and result indication */
#define REG_ADR_ED_RSLT           0, 0x3A  /* ED (Energy Detection) value indication */
#define REG_ADR_IDLE_WAIT_H       0, 0x3B  /* IDLE detection period setting during CCA (high 2bits) */
#define REG_ADR_IDLE_WAIT_L       0, 0x3C  /* IDLE detection period setting during CCA (low 8bits) */
#define REG_ADR_CCA_PROG_H        0, 0x3D  /* IDLE judgement elapsed time indication during CCA (high 2bits) */
#define REG_ADR_CCA_PROG_L        0, 0x3E  /* IDLE judgement elapsed time indication during CCA (low byte) */
#define REG_ADR_PREAMBLE_SET      0, 0x3F  /* Preamble pattern setting */
#define REG_ADR_VCO_VTRSLT        0, 0x40  /* new */
#define REG_ADR_ED_CNTRL          0, 0x41  /* ED detection control setting */
#define REG_ADR_TXPR_LEN_H        0, 0x42  /* new */
#define REG_ADR_TXPR_LEN_L        0, 0x43  /* new */
#define REG_ADR_POSTAMBLE_SET     0, 0x44  /* new */
#define REG_ADR_SYNC_CONDITION1   0, 0x45  /* new */
#define REG_ADR_SYNC_CONDITION2   0, 0x46  /* new */
#define REG_ADR_SYNC_CONDITION3   0, 0x47  /* new */
#define REG_ADR_2DIV_CNTRL        0, 0x48  /* 2 diversity setting */
#define REG_ADR_2DIV_RSLT         0, 0x49  /* 2 diversity resurt indication and forced antenna control setting */
#define REG_ADR_ANT1_ED           0, 0x4A  /* Acquired ED value by antenna 1 */
#define REG_ADR_ANT2_ED           0, 0x4B  /* Acquired ED value by antenna 2 */
#define REG_ADR_ANT_CTRL          0, 0x4C  /* new */
#define REG_ADR_MON_CTRL          0, 0x4D  /* new */
#define REG_ADR_GPIO0_CTRL        0, 0x4E  /* new */
#define REG_ADR_GPIO1_CTRL        0, 0x4F  /* new */
#define REG_ADR_GPIO2_CTRL        0, 0x50  /* new */
#define REG_ADR_GPIO3_CTRL        0, 0x51  /* new */
#define REG_ADR_EXTCLK_CTRL       0, 0x52  /* new */
#define REG_ADR_SPI_EXT_PA_CTRL   0, 0x53  /* new */
#define REG_ADR_CHFIL_BW          0, 0x54  /* new */
#define REG_ADR_DC_I_ADJ_H        0, 0x55  /* new */
#define REG_ADR_DC_I_ADJ_L        0, 0x56  /* new */
#define REG_ADR_DC_Q_ADJ_H        0, 0x57  /* new */
#define REG_ADR_DC_Q_ADJ_L        0, 0x58  /* new */
#define REG_ADR_DC_FIL_ADJ        0, 0x59  /* new */
#define REG_ADR_IQ_MAG_ADJ_H      0, 0x5A  /* new */
#define REG_ADR_IQ_MAG_ADJ_L      0, 0x5B  /* new */
#define REG_ADR_IQ_PHASE_ADJ_H    0, 0x5C  /* new */
#define REG_ADR_IQ_PHASE_ADJ_L    0, 0x5D  /* new */
#define REG_ADR_IQ_ADJ_WAIT       0, 0x5E  /* new */
#define REG_ADR_IQ_ADJ_TARGET     0, 0x5F  /* new */
#define REG_ADR_IQ_DEC_GAIN       0, 0x60  /* new */
#define REG_ADR_IF_FREQ           0, 0x61  /* new */
#define REG_ADR_OSC_ADJ1          0, 0x62  /* new */
#define REG_ADR_OSC_ADJ2          0, 0x63  /* new */
//                                0, 0x64  /* reserved */
#define REG_ADR_OSC_ADJ4          0, 0x65  /* new */
#define REG_ADR_RSSI_ADJ          0, 0x66  /* new */
#define REG_ADR_PA_REG_ADJ_H      0, 0x67  /* new */
#define REG_ADR_PA_REG_ADJ_L      0, 0x68  /* new */
//                                0, 0x69  /* reserved */
#define REG_ADR_CHFIL_BW_CCA      0, 0x6A  /* new */
#define REG_ADR_CHFIL_BW_OPTION   0, 0x6B  /* new */
#define REG_ADR_DC_FIL_ADJ2       0, 0x6C  /* new */
#define REG_ADR_DEC_GAIN_CCA      0, 0x6D  /* eng */
#define REG_ADR_VCO_CAL           0, 0x6E  /* VCO_CAL VCO calibration value indication and setting */
#define REG_ADR_VCO_CAL_START     0, 0x6F  /* VCO calibration execution */
#define REG_ADR_CLK_CAL_SET       0, 0x70  /* new */
#define REG_ADR_CLK_CAL_TIME      0, 0x71  /* new */
#define REG_ADR_CLK_CAL_H         0, 0x72  /* new */
#define REG_ADR_CLK_CAL_L         0, 0x73  /* new */
//                                0, 0x74  /* reserved */
#define REG_ADR_SLEEP_INT_CLR     0, 0x75  /* new */
#define REG_ADR_RF_TEST_MODE      0, 0x76  /* TX test pattern setting */
#define REG_ADR_STM_STATE         0, 0x77  /* new */
#define REG_ADR_FIFO_SET          0, 0x78  /* new */
#define REG_ADR_RD_FIFO_LAST      0, 0x79  /* FIFO remaining size or FIFO address indication */
#define REG_ADR_TX_PKT_LEN_H      0, 0x7A  /* new */
#define REG_ADR_TX_PKT_LEN_L      0, 0x7B  /* new */
#define REG_ADR_WR_TX_FIFO        0, 0x7C  /* TX FIFO */
#define REG_ADR_RX_PKT_LEN_H      0, 0x7D  /* new */
#define REG_ADR_RX_PKT_LEN_L      0, 0x7E  /* new */
#define REG_ADR_RD_RX_FIFO        0, 0x7F  /* RX FIFO */

#define REG_ADR_CLKOUT            1, 0x01  /* CLKOUT frequency setting */
#define REG_ADR_TX_RATE_H         1, 0x02  /* new */
#define REG_ADR_TX_RATE_L         1, 0x03  /* new */
#define REG_ADR_RX_RATE1_H        1, 0x04  /* new */
#define REG_ADR_RX_RATE1_L        1, 0x05  /* new */
#define REG_ADR_RX_RATE2          1, 0x06  /* new */
#define REG_ADR_REGULATOR_CTRL    1, 0x07  /* new */
#define REG_ADR_OSC_W_SEL         1, 0x08  /* new */
#define REG_ADR_RFIF_TEST         1, 0x09  /* eng */
#define REG_ADR_DC_TEST           1, 0x0A  /* eng */
#define REG_ADR_PLL_LOCK_DETECT   1, 0x0B  /* PLL lock detection configuration */
//                                1, 0x0C-0D  /* reserved */
#define REG_ADR_GAIN_HOLD         1, 0x0E  /* new */
#define REG_ADR_RSSI_STABLE_RES   1, 0x0F  /* eng */
#define REG_ADR_GC_CTRL_DIV       1, 0x10  /* new */
//                                1, 0x11  /* reserved */
#define REG_ADR_RSSI_STABLE_TIME  1, 0x12  /* Time parameter for RSSI value become stable after gain switch */
#define REG_ADR_RSSI_MAG_ADJ      1, 0x13  /* new */
#define REG_ADR_RSSI_VAL          1, 0x14  /* eng */
#define REG_ADR_AFC_GC_CTRL       1, 0x15  /* new */
#define REG_ADR_CRC_POLY3         1, 0x16  /* new */
#define REG_ADR_CRC_POLY2         1, 0x17  /* new */
#define REG_ADR_CRC_POLY1         1, 0x18  /* new */
#define REG_ADR_CRC_POLY0         1, 0x19  /* new */
#define REG_ADR_PLL_DIV_SET       1, 0x1A  /* new */
#define REG_ADR_TXFREQ_I          1, 0x1B  /* new */
#define REG_ADR_TXFREQ_FH         1, 0x1C  /* new */
#define REG_ADR_TXFREQ_FM         1, 0x1D  /* new */
#define REG_ADR_TXFREQ_FL         1, 0x1E  /* new */
#define REG_ADR_RXFREQ_I          1, 0x1F  /* new */
#define REG_ADR_RXFREQ_FH         1, 0x20  /* new */
#define REG_ADR_RXFREQ_FM         1, 0x21  /* new */
#define REG_ADR_RXFREQ_FL         1, 0x22  /* new */
#define REG_ADR_CH_SPACE_H        1, 0x23  /* Channel space setting (high byte) */
#define REG_ADR_CH_SPACE_L        1, 0x24  /* Channel space setting (low byte) */
#define REG_ADR_SYNC_WORD_LEN     1, 0x25  /* new */
#define REG_ADR_SYNC_WORD_EN      1, 0x26  /* new */
#define REG_ADR_SYNCWORD1_SET0    1, 0x27  /* new */
#define REG_ADR_SYNCWORD1_SET1    1, 0x28  /* new */
#define REG_ADR_SYNCWORD1_SET2    1, 0x29  /* new */
#define REG_ADR_SYNCWORD1_SET3    1, 0x2A  /* new */
#define REG_ADR_SYNCWORD2_SET0    1, 0x2B  /* new */
#define REG_ADR_SYNCWORD2_SET1    1, 0x2C  /* new */
#define REG_ADR_SYNCWORD2_SET2    1, 0x2D  /* new */
#define REG_ADR_SYNCWORD2_SET3    1, 0x2E  /* new */
#define REG_ADR_FSK_CTRL          1, 0x2F  /* new */
#define REG_ADR_GFSK_DEV_H        1, 0x30  /* new */
#define REG_ADR_GFSK_DEV_L        1, 0x31  /* new */
#define REG_ADR_FSK_DEV0_H_GFIL0  1, 0x32  /* new */
#define REG_ADR_FSK_DEV0_L_GFIL1  1, 0x33  /* new */
#define REG_ADR_FSK_DEV1_H_GFIL2  1, 0x34  /* new */
#define REG_ADR_FSK_DEV1_L_GFIL3  1, 0x35  /* new */
#define REG_ADR_FSK_DEV2_H_GFIL4  1, 0x36  /* new */
#define REG_ADR_FSK_DEV2_L_GFIL5  1, 0x37  /* new */
#define REG_ADR_FSK_DEV3_H_GFIL6  1, 0x38  /* new */
#define REG_ADR_FSK_DEV3_L        1, 0x39  /* new */
#define REG_ADR_FSK_DEV4_H        1, 0x3A  /* new */
#define REG_ADR_FSK_DEV4_L        1, 0x3B  /* new */
#define REG_ADR_FSK_TIM_ADJ4      1, 0x3C  /* new */
#define REG_ADR_FSK_TIM_ADJ3      1, 0x3D  /* new */
#define REG_ADR_FSK_TIM_ADJ2      1, 0x3E  /* new */
#define REG_ADR_FSK_TIM_ADJ1      1, 0x3F  /* new */
#define REG_ADR_FSK_TIM_ADJ0      1, 0x40  /* new */
#define REG_ADR_4FSK_DATA_MAP     1, 0x41  /* new */
#define REG_ADR_FREQ_ADJ_H        1, 0x42  /* new */
#define REG_ADR_FREQ_ADJ_L        1, 0x43  /* new */
#define REG_ADR_RSSI_VAL2         1, 0x44  /* eng */
#define REG_ADR_RSSI_VAL3         1, 0x45  /* eng */
#define REG_ADR_RSSI_DET1         1, 0x46  /* eng */
#define REG_ADR_RSSI_DET2         1, 0x47  /* eng */
#define REG_ADR_2DIV_MODE         1, 0x48  /* new */
#define REG_ADR_2DIV_SEARCH1      1, 0x49  /* new */
#define REG_ADR_2DIV_SEARCH2      1, 0x4A  /* new */
#define REG_ADR_2DIV_FAST_LV      1, 0x4B  /* ED threshold level setting during 2 diversity FAST mode */
#define REG_ADR_2DIV_PB_TH        1, 0x4C  /* eng */
#define REG_ADR_VCO_CAL_MIN_I     1, 0x4D  /* new */
#define REG_ADR_VCO_CAL_MIN_FH    1, 0x4E  /* VCO calibration low limit frequency setting (high 4bits) */
#define REG_ADR_VCO_CAL_MIN_FM    1, 0x4F  /* VCO calibration low limit frequency setting (middle byte) */
#define REG_ADR_VCO_CAL_MIN_FL    1, 0x50  /* VCO calibration low limit frequency setting (low byte) */
#define REG_ADR_VCO_CAL_MAX_N     1, 0x51  /* VCO calibration upper limit frequency setting */
#define REG_ADR_VCO_CAL_MIN       1, 0x52  /* VCO calibration low limit value indication and setting */
#define REG_ADR_VCO_CAL_MAX       1, 0x53  /* VCO calibration upper limit value indication and setting */
//                                1, 0x54-55  /* reserved */
#define REG_ADR_DEMOD_SET0        1, 0x56  /* new */
#define REG_ADR_DEMOD_SET1        1, 0x57  /* new */
#define REG_ADR_DEMOD_SET2        1, 0x58  /* new */
#define REG_ADR_DEMOD_SET3        1, 0x59  /* new */
#define REG_ADR_RX_IQ_SEL         1, 0x5A  /* eng */
//                                1, 0x5B  /* reserved */
#define REG_ADR_DEMOD_SET6        1, 0x5C  /* new */
#define REG_ADR_DEMOD_SET7        1, 0x5D  /* new */
#define REG_ADR_DEMOD_SET8        1, 0x5E  /* new */
#define REG_ADR_DEMOD_SET9        1, 0x5F  /* new */
#define REG_ADR_DEMOD_SET10       1, 0x60  /* new */
#define REG_ADR_DEMOD_SET11       1, 0x61  /* new */
#define REG_ADR_ADDR_CHK_CTR_H    1, 0x62  /* new */
#define REG_ADR_ADDR_CHK_CTR_L    1, 0x63  /* new */
#define REG_ADR_WHT_INIT_H        1, 0x64  /* new */
#define REG_ADR_WHT_INIT_L        1, 0x65  /* new */
#define REG_ADR_WHT_CFG           1, 0x66  /* new */
#define REG_ADR_SYNC_TIMER_SET    1, 0x67  /* eng */
#define REG_ADR_SYNC_TIMER_DIFF_H 1, 0x68  /* eng */
#define REG_ADR_SYNC_TIMER_DIFF_M 1, 0x69  /* eng */
#define REG_ADR_SYNC_TIMER_DIFF_L 1, 0x6A  /* eng */
#define REG_ADR_SYNC_TIMER_ADJ    1, 0x6B  /* eng */
//                                1, 0x6C-0x7A  /* reserved */
#define REG_ADR_TX_RATE2_EN       1, 0x7B  /* new */
#define REG_ADR_TX_RATE2_H        1, 0x7C  /* new */
#define REG_ADR_TX_RATE2_L        1, 0x7D  /* new */
#define REG_ADR_RFM_STATE         1, 0x7E  /* eng */
#define REG_ADR_ID_CODE           1, 0x7F /* ID code indication */

//                                2, 0x01-0x75  /* reserved */
#define REG_ADR_PLL_TIM_ADJ       2, 0x01  /* eng */
#define REG_ADR_TX_OFF_TIM_ADJ    2, 0x02  /* eng */
#define REG_ADR_PA_TIM_ADJ        2, 0x03  /* eng */
#define REG_ADR_DAT_IN_ADJ        2, 0x04  /* eng */
#define REG_ADR_RX_TIM_ADJ        2, 0x05  /* eng */
#define REG_ADR_TIM_PAREF_RXON2   2, 0x06  /* eng */
#define REG_ADR_TIM_TX_ON2        2, 0x07  /* eng */
#define REG_ADR_PLLRST_MASK       2, 0x08  /* eng */
#define REG_ADR_PRCH_ADJ          2, 0x09  /* eng */
#define REG_ADR_VCO_CAL_ADJ       2, 0x0A  /* eng */
#define REG_ADR_TIMEOUT_ADJ       2, 0x0B  /* eng */
#define REG_ADR_TX_ON_TIM_ADJ     2, 0x0C  /* eng */
#define REG_ADR_PRCH_RX_ADJ       2, 0x0D  /* eng */
#define REG_ADR_RSSI_ADJ2         2, 0x0E  /* eng */
#define REG_ADR_RSSI_ADJ_TRIM     2, 0x0F  /* eng */
#define REG_ADR_AAF_FREQ_ADJ      2, 0x10  /* eng */
#define REG_ADR_AAF_ADJ           2, 0x11  /* new */
#define REG_ADR_DSM_DELAY_ADJ     2, 0x12  /* eng */
#define REG_ADR_OSC_ADJ3          2, 0x13  /* eng */
#define REG_ADR_IRCV_RSSI_OFST    2, 0x14  /* eng */
//                                2, 0x15  /* reserved */
#define REG_ADR_PLL_CP_ADJ2       2, 0x16  /* eng */
//                                2, 0x17  /* reserved */
#define REG_ADR_PA_MODE_CTRL      2, 0x18  /* eng */
#define REG_ADR_BPSK_DLY_ADJ      2, 0x19  /* eng */
#define REG_ADR_PA_CURR           2, 0x1A  /* eng */
#define REG_ADR_PA_RAMP_TRF       2, 0x1B  /* eng */
#define REG_ADR_PLL_CP_ADJ        2, 0x1C  /* eng */
#define REG_ADR_PLL_CP_CTRL       2, 0x1D  /* eng */
#define REG_ADR_PLL_PFD_CTRL      2, 0x1E  /* eng */
#define REG_ADR_PLL_LO_CTRL       2, 0x1F  /* eng */
#define REG_ADR_PLL_SDM_LD        2, 0x20  /* eng */
#define REG_ADR_PLL_CLK_SEL       2, 0x21  /* eng */
#define REG_ADR_OVR_PLL           2, 0x22  /* eng */
#define REG_ADR_VCO_I_CTRL_INIT   2, 0x23  /* eng */
#define REG_ADR_VCO_I_CTRL        2, 0x24  /* new */
#define REG_ADR_VCO_VAR_SEL       2, 0x25  /* eng */
#define REG_ADR_VCO_CAL_SET       2, 0x26  /* eng */
//                                2, 0x27  /* reserved */
#define REG_ADR_LNA_GAIN1         2, 0x28  /* eng */
#define REG_ADR_LNA_RESERVE       2, 0x29  /* eng */
#define REG_ADR_IFAMP_GAIN        2, 0x2A  /* eng */
#define REG_ADR_LOWGAIN_TRIM      2, 0x2B  /* eng */
#define REG_ADR_LO_BIAS           2, 0x2C  /* eng */
#define REG_ADR_LNA_I_TRIM        2, 0x2D  /* eng */
//                                2, 0x2E  /* reserved */
#define REG_ADR_PAREG_OLR2        2, 0x2F  /* eng */
#define REG_ADR_OVR_MOD           2, 0x30  /* eng */
#define REG_ADR_RF_7345_RSV1      2, 0x31  /* eng */
#define REG_ADR_RF_7345_RSV2      2, 0x32  /* eng */
#define REG_ADR_RF_7345_RSV3      2, 0x33  /* eng */
#define REG_ADR_RF_7345_RSV4      2, 0x34  /* eng */
#define REG_ADR_RCOSC_ADJ         2, 0x35  /* eng */
#define REG_ADR_SREG_TRIM         2, 0x36  /* eng */
//                                2, 0x37  /* reserved */
#define REG_ADR_VBG_TRIM          2, 0x38  /* eng */
#define REG_ADR_BIAS_T_TRIM       2, 0x39  /* eng */
#define REG_ADR_PTAT_TRIM         2, 0x3A  /* eng */
#define REG_ADR_IBG_TRIM          2, 0x3B  /* eng */
#define REG_ADR_OVR_ON            2, 0x3C  /* eng */
#define REG_ADR_OVR_PLLON         2, 0x3D  /* eng */
//                                2, 0x3E-0x3F  /* reserved */
#define REG_ADR_OVR_PRCH          2, 0x40  /* eng */
#define REG_ADR_OVR_REG_B1        2, 0x41  /* eng */
#define REG_ADR_OVR_REG_D1        2, 0x42  /* eng */
#define REG_ADR_OVR_REG_PLL1      2, 0x43  /* eng */
#define REG_ADR_OVR_REG_RX        2, 0x44  /* eng */
#define REG_ADR_TEST_SW1          2, 0x45  /* eng */
#define REG_ADR_TEST_SW2          2, 0x46  /* eng */
#define REG_ADR_TEST_SW3          2, 0x47  /* eng */
#define REG_ADR_TEST_SW4          2, 0x48  /* eng */
#define REG_ADR_TEST_SW5          2, 0x49  /* eng */
//                                2, 0x4A-0x4C  /* reserved */
#define REG_ADR_VTUNE_COMP_TH     2, 0x4D  /* eng */
#define REG_ADR_RFRX_SET1         2, 0x4E  /* eng */
#define REG_ADR_LOBUF_I_ADJ       2, 0x4F  /* eng */
#define REG_ADR_LF_ENABLE         2, 0x50  /* eng */
#define REG_ADR_FUSE_SET          2, 0x51  /* eng */
#define REG_ADR_FUSE1             2, 0x52  /* eng */
#define REG_ADR_FUSE2             2, 0x53  /* eng */
#define REG_ADR_FUSE3             2, 0x54  /* eng */
#define REG_ADR_FUSE4             2, 0x55  /* eng */
#define REG_ADR_FUSE5             2, 0x56  /* eng */
#define REG_ADR_FUSE6             2, 0x57  /* eng */
#define REG_ADR_FUSE7             2, 0x58  /* eng */
//                                2, 0x59-0x5C  /* reserved */
#define REG_ADR_FUSE12            2, 0x5D  /* eng */
#define REG_ADR_FUSE13            2, 0x5E  /* eng */
//                                2, 0x5F-0x61  /* reserved */
#define REG_ADR_RF_7404_RSV1      2, 0x62  /* eng */
#define REG_ADR_RF_7404_RSV2      2, 0x63  /* eng */
//                                2, 0x64-0x75  /* reserved */
#define REG_ADR_GAIN_HHTH         2, 0x76  /* new */
#define REG_ADR_GAIN_HTOHH        2, 0x77  /* new */
#define REG_ADR_GAIN_HTOM         2, 0x78  /* Gain update setting and threshold level setting for switching high gain to middle gain */
#define REG_ADR_GAIN_MTOH         2, 0x79  /* GAIN_MtoH Threshold level setting for switching middle gain to high gain */
#define REG_ADR_GAIN_MTOL         2, 0x7A  /* Threshold level setting for switching middle gain to low gain */
#define REG_ADR_GAIN_LTOM         2, 0x7B  /* Threshold level setting for switching low gain to middle gain */
#define REG_ADR_RSSI_ADJ_H        2, 0x7C  /* new */
#define REG_ADR_RSSI_ADJ_M        2, 0x7D  /* RSSI offset value setting during middle gain operation */
#define REG_ADR_RSSI_ADJ_L        2, 0x7E  /* RSSI offset value setting during low gain operation */
//                                2, 0x7F  /* reserved */

//                                3, 0x01-0x22  /* reserved */
#define REG_ADR_DEMSET12          3, 0x01  /* eng */
#define REG_ADR_DEMSET13          3, 0x02  /* eng */
#define REG_ADR_DEMSET14          3, 0x03  /* eng */
#define REG_ADR_DEMSET15          3, 0x04  /* eng */
#define REG_ADR_DEMSET16          3, 0x05  /* eng */
#define REG_ADR_DEMSET17          3, 0x06  /* eng */
#define REG_ADR_DEMSET18          3, 0x07  /* eng */
#define REG_ADR_DEMSET19          3, 0x08  /* eng */
#define REG_ADR_DEMSET20          3, 0x09  /* eng */
#define REG_ADR_DEMSET21          3, 0x0A  /* eng */
#define REG_ADR_DEMSET22          3, 0x0B  /* eng */
#define REG_ADR_DEMSET23          3, 0x0C  /* eng */
#define REG_ADR_DEMSET24          3, 0x0D  /* eng */
#define REG_ADR_DEMSET25          3, 0x0E  /* eng */
#define REG_ADR_DEMSET26          3, 0x0F  /* eng */
#define REG_ADR_DEMSET27          3, 0x10  /* eng */
#define REG_ADR_DEMSET28          3, 0x11  /* eng */
#define REG_ADR_DEMSET29          3, 0x12  /* eng */
#define REG_ADR_DEMSET30          3, 0x13  /* eng */
#define REG_ADR_DEMSET31          3, 0x14  /* eng */
#define REG_ADR_DEMSET32          3, 0x15  /* eng */
#define REG_ADR_DEMSET33          3, 0x16  /* eng */
#define REG_ADR_DEMSET34          3, 0x17  /* eng */
#define REG_ADR_DEMSET35          3, 0x18  /* eng */
#define REG_ADR_DEMSET36          3, 0x19  /* eng */
#define REG_ADR_DEMSET37          3, 0x1A  /* eng */
#define REG_ADR_DEMSET38          3, 0x1B  /* eng */
#define REG_ADR_DEMSET39          3, 0x1C  /* eng */
#define REG_ADR_DEMSET40          3, 0x1D  /* eng */
#define REG_ADR_DEMSET41          3, 0x1E  /* eng */
#define REG_ADR_DEMSET42          3, 0x1F  /* eng */
#define REG_ADR_RFM_CTRL          3, 0x20  /* eng */
#define REG_ADR_VST_CTRL          3, 0x21  /* eng */
#define REG_ADR_PHY_MON_SEL       3, 0x22  /* eng */
#define REG_ADR_2MODE_DET         3, 0x23  /* new */
#define REG_ADR_DEMSET44          3, 0x24  /* eng */
#define REG_ADR_DEMSET45          3, 0x25  /* eng */
#define REG_ADR_DIF_SET0          3, 0x26  /* eng */
#define REG_ADR_DIF_SET1          3, 0x27  /* eng */
#define REG_ADR_DIF_SET2          3, 0x28  /* eng */
#define REG_ADR_BER_CFG           3, 0x29  /* eng */
#define REG_ADR_BER_COUNT_H       3, 0x2A  /* eng */
#define REG_ADR_BER_COUNT_L       3, 0x2B  /* eng */
#define REG_ADR_RSSI_SEL          3, 0x2C  /* new */
#define REG_ADR_CCA_SYNC_OFF      3, 0x2D  /* eng */
//                                3, 0x2E  /* reserved */
#define REG_ADR_MOD_MONITOR       3, 0x2F  /* eng */
//                                3, 0x30-0x40  /* reserved */
#define REG_ADR_RAMP_CTRL1        3, 0x41  /* new */
#define REG_ADR_RAMP_CTRL2        3, 0x42  /* new */
#define REG_ADR_RAMP_CTRL3        3, 0x43  /* new */
#define REG_ADR_LOWBAT_DET_CTRL1  3, 0x44  /* eng */
#define REG_ADR_LOWBAT_DET_CTRL2  3, 0x45  /* eng */
//                                3, 0x46-0x4F  /* reserved */
#define REG_ADR_EXT_WU_CTRL       3, 0x50  /* new */
#define REG_ADR_EXT_WU_INTERVAL   3, 0x51  /* new */
//                                3, 0x52-0x7F  /* reserved */

#define REG_ADR_MOD_CTRL          6, 0x01  /* new */
//                                6, 0x02-0x2B  /* reserved */
// #define REG_ADR_4FSK_DATA_MAP     1, 0x41  /* new */
//                                6, 0x2D-0x2E  /* reserved */
// #define REG_ADR_FSK_CTRL          1, 0x2F  /* new */
// #define REG_ADR_GFSK_DEV_H        1, 0x30  /* new */
// #define REG_ADR_GFSK_DEV_L        1, 0x31  /* new */
// #define REG_ADR_FSK_DEV0_H_GFIL0  1, 0x32  /* new */
// #define REG_ADR_FSK_DEV0_L_GFIL1  1, 0x33  /* new */
// #define REG_ADR_FSK_DEV1_H_GFIL2  1, 0x34  /* new */
// #define REG_ADR_FSK_DEV1_L_GFIL3  1, 0x35  /* new */
// #define REG_ADR_FSK_DEV2_H_GFIL4  1, 0x36  /* new */
// #define REG_ADR_FSK_DEV2_L_GFIL5  1, 0x37  /* new */
// #define REG_ADR_FSK_DEV3_H_GFIL6  1, 0x38  /* new */
// #define REG_ADR_FSK_DEV3_L        1, 0x39  /* new */
// #define REG_ADR_FSK_DEV4_H        1, 0x3A  /* new */
// #define REG_ADR_FSK_DEV4_L        1, 0x3B  /* new */
#define REG_ADR_PA_AMP5_H         6, 0x3C  /* new */
#define REG_ADR_PA_AMP5_L         6, 0x3D  /* new */
#define REG_ADR_PA_AMP6_H         6, 0x3E  /* new */
#define REG_ADR_PA_AMP6_L         6, 0x3F  /* new */
#define REG_ADR_PA_AMP7_H         6, 0x40  /* new */
#define REG_ADR_PA_AMP7_L         6, 0x41  /* new */
#define REG_ADR_PA_AMP8_H         6, 0x42  /* new */
#define REG_ADR_PA_AMP8_L         6, 0x43  /* new */
#define REG_ADR_PA_AMP9_H         6, 0x44  /* new */
#define REG_ADR_PA_AMP9_L         6, 0x45  /* new */
#define REG_ADR_PA_AMP10_H        6, 0x46  /* new */
#define REG_ADR_PA_AMP10_L        6, 0x47  /* new */
#define REG_ADR_PA_AMP11_H        6, 0x48  /* new */
#define REG_ADR_PA_AMP11_L        6, 0x49  /* new */
#define REG_ADR_PA_AMP12_H        6, 0x4A  /* new */
#define REG_ADR_PA_AMP12_L        6, 0x4B  /* new */
#define REG_ADR_PA_AMP13_H        6, 0x4C  /* new */
#define REG_ADR_PA_AMP13_L        6, 0x4D  /* new */
#define REG_ADR_PA_AMP14_H        6, 0x4E  /* new */
#define REG_ADR_PA_AMP14_L        6, 0x4F  /* new */
#define REG_ADR_PA_AMP15_H        6, 0x50  /* new */
#define REG_ADR_PA_AMP15_L        6, 0x51  /* new */
//                                6, 0x52-0x61  /* reserved */
// #define REG_ADR_FSK_TIM_ADJ4      1, 0x3C  /* new */
// #define REG_ADR_FSK_TIM_ADJ3      1, 0x3D  /* new */
// #define REG_ADR_FSK_TIM_ADJ2      1, 0x3E  /* new */
// #define REG_ADR_FSK_TIM_ADJ1      1, 0x3F  /* new */
// #define REG_ADR_FSK_TIM_ADJ0      1, 0x40  /* new */
#define REG_ADR_FSK_TIM_ADJ5      6, 0x67  /* new */
#define REG_ADR_FSK_TIM_ADJ6      6, 0x68  /* new */
#define REG_ADR_FSK_TIM_ADJ7      6, 0x69  /* new */
#define REG_ADR_FSK_TIM_ADJ8      6, 0x6A  /* new */
#define REG_ADR_FSK_TIM_ADJ9      6, 0x6B  /* new */
#define REG_ADR_FSK_TIM_ADJ10     6, 0x6C  /* new */
#define REG_ADR_FSK_TIM_ADJ11     6, 0x6D  /* new */
#define REG_ADR_FSK_TIM_ADJ12     6, 0x6E  /* new */
#define REG_ADR_FSK_TIM_ADJ13     6, 0x6F  /* new */
#define REG_ADR_FSK_TIM_ADJ14     6, 0x70  /* new */
//                                6, 0x71-0x72  /* reserved */
#define REG_ADR_BPSK_LUD_CTRL     6, 0x73  /* new */
#define REG_ADR_BPSK_LUP_CTRL     6, 0x74  /* new */
#define REG_ADR_BPSK_LDWN_CTRL    6, 0x75  /* new */
#define REG_ADR_PAREG_CTRL        6, 0x76  /* new */
#define REG_ADR_BPSK_PAREG_START_H   6, 0x77  /* new */
#define REG_ADR_BPSK_PAREG_START_L   6, 0x78  /* new */
#define REG_ADR_BPSK_PAREG_HOLD_H 6, 0x79  /* new */
#define REG_ADR_BPSK_PAREG_HOLD_L 6, 0x7A  /* new */
#define REG_ADR_BPSK_PLL_CTRL     6, 0x7B  /* new */
#define REG_ADR_BPSK_P_START_H    6, 0x7C  /* new */
#define REG_ADR_BPSK_P_START_L    6, 0x7D  /* new */
#define REG_ADR_BPSK_P_HOLD_H     6, 0x7E  /* new */
#define REG_ADR_BPSK_P_HOLD_L     6, 0x7F  /* new */

#define REG_ADR_DSSS_CTRL         7, 0x01  /* new */
#define REG_ADR_DSSS_MODE         7, 0x02  /* new */
#define REG_ADR_FEC_ENC_CTRL      7, 0x03  /* new */
#define REG_ADR_FEC_INIT_STATE    7, 0x04  /* eng */
#define REG_ADR_FEC_DEC_CTRL      7, 0x05  /* new */
#define REG_ADR_SF_CTRL           7, 0x06  /* new */
#define REG_ADR_SHR_GOLD_SEED3    7, 0x07  /* new */
#define REG_ADR_SHR_GOLD_SEED2    7, 0x08  /* new */
#define REG_ADR_SHR_GOLD_SEED1    7, 0x09  /* new */
#define REG_ADR_SHR_GOLD_SEED0    7, 0x0A  /* new */
#define REG_ADR_PSDU_GOLD_SEED3   7, 0x0B  /* new */
#define REG_ADR_PSDU_GOLD_SEED2   7, 0x0C  /* new */
#define REG_ADR_PSDU_GOLD_SEED1   7, 0x0D  /* new */
#define REG_ADR_PSDU_GOLD_SEED0   7, 0x0E  /* new */
#define REG_ADR_DSSS_PREAMBLE3    7, 0x0F  /* new */
#define REG_ADR_DSSS_PREAMBLE2    7, 0x10  /* new */
#define REG_ADR_DSSS_PREAMBLE1    7, 0x11  /* new */
#define REG_ADR_DSSS_PREAMBLE0    7, 0x12  /* new */
#define REG_ADR_SS_DOWN_SIZE      7, 0x13  /* new */
#define REG_ADR_SS_AFC_RANGE_SYNC 7, 0x14  /* new */
#define REG_ADR_SS_AFC_RANGE      7, 0x15  /* new */
//                                7, 0x16  /* reserved */
#define REG_ADR_DSSS_RATE_SYNC_H  7, 0x17  /* new */
#define REG_ADR_DSSS_RATE_SYNC_L  7, 0x18  /* new */
#define REG_ADR_DSSS_RATE_H       7, 0x19  /* new */
#define REG_ADR_DSSS_RATE_L       7, 0x1A  /* new */
#define REG_ADR_SS_SYNC_BIT8_GATE_H   7, 0x1B  /* new */
#define REG_ADR_SS_SYNC_BIT8_GATE_L   7, 0x1C  /* new */
#define REG_ADR_SS_SYNC_BIT8_GATE2_H  7, 0x1D  /* new */
#define REG_ADR_SS_SYNC_BIT8_GATE2_L  7, 0x1E  /* new */
#define REG_ADR_SS_SYNC_BIT_GATE_H    7, 0x1F  /* new */
#define REG_ADR_SS_SYNC_BIT_GATE_L    7, 0x20  /* new */
#define REG_ADR_SS_SYNC_BIT4_GATE_H   7, 0x21  /* eng */
#define REG_ADR_SS_SYNC_BIT4_GATE_L   7, 0x22  /* eng */
#define REG_ADR_SS_SYNC_LOST_GATE     7, 0x23  /* eng */
#define REG_ADR_SS_BIT8_MAX_ACC_H     7, 0x24  /* eng */
#define REG_ADR_SS_BIT8_MAX_ACC_L     7, 0x25  /* eng */
#define REG_ADR_SS_SYNC_GATE2_PLUS    7, 0x26  /* eng */
#define REG_ADR_AGC_AVE_OFST_SYNC     7, 0x27  /* eng */
#define REG_ADR_AGC_AVE_OFST      7, 0x28  /* eng */
#define REG_ADR_AGC_IIR_SET0      7, 0x29  /* eng */
#define REG_ADR_AGC_IIR_SET1      7, 0x2A  /* eng */
//                                7, 0x2B  /* reserved */
#define REG_ADR_DSSS_SET1         7, 0x2C  /* eng */
#define REG_ADR_DSSS_SET2         7, 0x2D  /* eng */
#define REG_ADR_DSSS_SET3         7, 0x2E  /* eng */
#define REG_ADR_DSSS_SET4         7, 0x2F  /* eng */
#define REG_ADR_DSSS_SET5         7, 0x30  /* eng */
#define REG_ADR_SS_AFC_OUT        7, 0x31  /* new */
#define REG_ADR_SS_AFC_FIX_EN     7, 0x32  /* new */
#define REG_ADR_SS_AFC_FIX        7, 0x33  /* new */
#define REG_ADR_DSSS_MON_SEL      7, 0x34  /* eng */
#define REG_ADR_BIT8_SPDET_TH_H   7, 0x35  /* eng */
#define REG_ADR_BIT8_SPDET_TH_L   7, 0x36  /* eng */
#define REG_ADR_DSSS_SET6         7, 0x37  /* eng */
#define REG_ADR_DSSS_SET7         7, 0x38  /* eng */
#define REG_ADR_DSSS_SET8         7, 0x39  /* eng */
#define REG_ADR_DSSS_SET9         7, 0x3A  /* eng */
#define REG_ADR_DSSS_SET10        7, 0x3B  /* eng */
//                                7, 0x3C-0x7F  /* reserved */

#define REG_ADR_BPSK_STEP_CTRL   10, 0x01  /* eng */
#define REG_ADR_BPSK_STEP_CLK_SET    10, 0x02  /* eng */
//                               10, 0x03  /* reserved */
#define REG_ADR_BPSK_STEP_SET0   10, 0x04  /* eng */
#define REG_ADR_BPSK_STEP_SET1   10, 0x05  /* eng */
#define REG_ADR_BPSK_STEP_SET2   10, 0x06  /* eng */
#define REG_ADR_BPSK_STEP_SET3   10, 0x07  /* eng */
#define REG_ADR_BPSK_STEP_SET4   10, 0x08  /* eng */
#define REG_ADR_BPSK_STEP_SET5   10, 0x09  /* eng */
#define REG_ADR_BPSK_STEP_SET6   10, 0x0A  /* eng */
#define REG_ADR_BPSK_STEP_SET7   10, 0x0B  /* eng */
#define REG_ADR_BPSK_STEP_SET8   10, 0x0C  /* eng */
#define REG_ADR_BPSK_STEP_SET9   10, 0x0D  /* eng */
#define REG_ADR_BPSK_STEP_SET10  10, 0x0E  /* eng */
#define REG_ADR_BPSK_STEP_SET11  10, 0x0F  /* eng */
#define REG_ADR_BPSK_STEP_SET12  10, 0x10  /* eng */
#define REG_ADR_BPSK_STEP_SET13  10, 0x11  /* eng */
#define REG_ADR_BPSK_STEP_SET14  10, 0x12  /* eng */
#define REG_ADR_BPSK_STEP_SET15  10, 0x13  /* eng */
#define REG_ADR_BPSK_STEP_SET16  10, 0x14  /* eng */
#define REG_ADR_BPSK_STEP_SET17  10, 0x15  /* eng */
#define REG_ADR_BPSK_STEP_SET18  10, 0x16  /* eng */
#define REG_ADR_BPSK_STEP_SET19  10, 0x17  /* eng */
#define REG_ADR_BPSK_STEP_SET20  10, 0x18  /* eng */
#define REG_ADR_BPSK_STEP_SET21  10, 0x19  /* eng */
#define REG_ADR_BPSK_STEP_SET22  10, 0x1A  /* eng */
#define REG_ADR_BPSK_STEP_SET23  10, 0x1B  /* eng */
#define REG_ADR_BPSK_STEP_SET24  10, 0x1C  /* eng */
#define REG_ADR_BPSK_STEP_SET25  10, 0x1D  /* eng */
#define REG_ADR_BPSK_STEP_SET26  10, 0x1E  /* eng */
#define REG_ADR_BPSK_STEP_SET27  10, 0x1F  /* eng */
#define REG_ADR_BPSK_STEP_SET28  10, 0x20  /* eng */
#define REG_ADR_BPSK_STEP_SET29  10, 0x21  /* eng */
#define REG_ADR_BPSK_STEP_SET30  10, 0x22  /* eng */
#define REG_ADR_BPSK_STEP_SET31  10, 0x23  /* eng */
#define REG_ADR_BPSK_STEP_SET32  10, 0x24  /* eng */
#define REG_ADR_BPSK_STEP_SET33  10, 0x25  /* eng */
#define REG_ADR_BPSK_STEP_SET34  10, 0x26  /* eng */
#define REG_ADR_BPSK_STEP_SET35  10, 0x27  /* eng */
#define REG_ADR_BPSK_STEP_SET36  10, 0x28  /* eng */
#define REG_ADR_BPSK_STEP_SET37  10, 0x29  /* eng */
#define REG_ADR_BPSK_STEP_SET38  10, 0x2A  /* eng */
#define REG_ADR_BPSK_STEP_SET39  10, 0x2B  /* eng */
#define REG_ADR_BPSK_STEP_SET40  10, 0x2C  /* eng */
#define REG_ADR_BPSK_STEP_SET41  10, 0x2D  /* eng */
#define REG_ADR_BPSK_STEP_SET42  10, 0x2E  /* eng */
#define REG_ADR_BPSK_STEP_SET43  10, 0x2F  /* eng */
#define REG_ADR_BPSK_STEP_SET44  10, 0x30  /* eng */
#define REG_ADR_BPSK_STEP_SET45  10, 0x31  /* eng */
#define REG_ADR_BPSK_STEP_SET46  10, 0x32  /* eng */
#define REG_ADR_BPSK_STEP_SET47  10, 0x33  /* eng */
#define REG_ADR_BPSK_STEP_SET48  10, 0x34  /* eng */
#define REG_ADR_BPSK_STEP_SET49  10, 0x35  /* eng */
#define REG_ADR_BPSK_STEP_SET50  10, 0x36  /* eng */
#define REG_ADR_BPSK_STEP_SET51  10, 0x37  /* eng */
#define REG_ADR_BPSK_STEP_SET52  10, 0x38  /* eng */
#define REG_ADR_BPSK_STEP_SET53  10, 0x39  /* eng */
#define REG_ADR_BPSK_STEP_SET54  10, 0x3A  /* eng */
#define REG_ADR_BPSK_STEP_SET55  10, 0x3B  /* eng */
#define REG_ADR_BPSK_STEP_SET56  10, 0x3C  /* eng */
#define REG_ADR_BPSK_STEP_SET57  10, 0x3D  /* eng */
#define REG_ADR_BPSK_STEP_SET58  10, 0x3E  /* eng */
#define REG_ADR_BPSK_STEP_SET59  10, 0x3F  /* eng */
#define REG_ADR_BPSK_PADRV_CTRL  10, 0x40  /* eng */
#define REG_ADR_BPSK_PADRV_ADJ1  10, 0x41  /* eng */
#define REG_ADR_BPSK_PADRV_ADJ2_H    10, 0x42  /* eng */
#define REG_ADR_BPSK_PADRV_ADJ2_L    10, 0x43  /* eng */
#define REG_ADR_BPSK_PADRV_CLK_SET_H 10, 0x44  /* eng */
#define REG_ADR_BPSK_PADRV_CLK_SET_L 10, 0x45  /* eng */
#define REG_ADR_BPSK_PADRV_UP_ADJ    10, 0x46  /* eng */
//                               10, 0x47-0x7F  /* reserved */

#define REG_ADR_WRITE_BIT         0x01     /* SPI light bit */

/** Public function
 */
#define PHY_IDCODE_ES1          ( 0x64 )
#define PHY_IDCODE_ES2          ( 0x65 )

#define PHY_DSSS_SIZE_16        ( 0x00 )
#define PHY_DSSS_SIZE_24        ( 0x10 )
#define PHY_DSSS_SIZE_32        ( 0x20 )
#define PHY_DSSS_SIZE_FREE      ( 0x30 )

#define PHY_DSSS_SF_8         ( 0x03 )
#define PHY_DSSS_SF_16        ( 0x00 )
#define PHY_DSSS_SF_32        ( 0x01 )
#define PHY_DSSS_SF_64        ( 0x02 )
#endif  /* #ifndef _INCLUDE_ML7404_REG_H */

