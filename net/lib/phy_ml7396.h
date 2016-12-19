/* ml7396_reg.h -ML7396 register address header file 
 * 
 * Copyright (c) 2015  Communication Technology Inc.,
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

#ifndef _INCLUDE_ML7396_REG_H
#define _INCLUDE_ML7396_REG_H


#ifdef LAZURITE_IDE
#include <stdint.h>
#endif

/** Register map
 */
/*      name                   bank, address */
#define REG_ADR_RST_SET           0, 0x01  /* Software reset setting */
#define REG_ADR_CLK_SET           0, 0x02  /* Clock configuration */
#define REG_ADR_CLKOUT            0, 0x03  /* CLKOUT frequency setting */
#define REG_ADR_RATE_SET1         0, 0x04  /* Data rate conversion setting 1 */
#define REG_ADR_RATE_SET2         0, 0x05  /* Data rate conversion setting 2 */
#define REG_ADR_ADC_CLK_SET       0+8, 0x08  /* RSSI ADC clock frequency setting */
#define REG_ADR_OSC_ADJ2          0+8, 0x0a  /* Load capacitor adjustment for oscillation circuit (fough) */
#define REG_ADR_OSC_ADJ           0+8, 0x0b  /* Load capacitor adjustment for oscillation circuit (fine) */
#define REG_ADR_RF_TEST_MODE      0+8, 0x0c  /* TX test pattern setting */
#define REG_ADR_PHY_STATE         0+8, 0x0f  /* PHY status indication */
#define REG_ADR_FIFO_BANK         0+8, 0x10  /* FIFO bank indication */
#define REG_ADR_PLL_LOCK_DETECT   0+8, 0x11  /* PLL lock detection configuration */
#define REG_ADR_CCA_IGNORE_LEVEL  0, 0x12    /* ED threshold level setting for excluding CCA judgement */
#define REG_ADR_CCA_LEVEL         0, 0x13  /* CCA threshold level setting */
#define REG_ADR_CCA_ABORT         0, 0x14  /* Timing setting for forced termincation of CCA operation */
#define REG_ADR_CCA_CNTRL         0, 0x15  /* CCA control setting and result indication */
#define REG_ADR_ED_RSLT           0, 0x16  /* ED (Energy Detection) value indication */
#define REG_ADR_IDLE_WAIT_L       0, 0x17  /* IDLE detection period setting during CCA (low 8bits) */
#define REG_ADR_IDLE_WAIT_H       0, 0x18  /* IDLE detection period setting during CCA (high 2bits) */
#define REG_ADR_CCA_PROG_L        0, 0x19  /* IDLE judgement elapsed time indication during CCA (low byte) */
#define REG_ADR_CCA_PROG_H        0, 0x1a  /* IDLE judgement elapsed time indication during CCA (high 2bits) */
#define REG_ADR_ED_CNTRL          0, 0x1b  /* ED detection control setting */
#define REG_ADR_GAIN_MtoL         0, 0x1c  /* Threshold level setting for switching middle gain to low gain */
#define REG_ADR_GAIN_LtoM         0, 0x1d  /* Threshold level setting for switching low gain to middle gain */
#define REG_ADR_GAIN_HtoM         0, 0x1e  /* Gain update setting and threshold level setting for switching high gain to middle gain */
#define REG_ADR_GAIN_MtoH         0, 0x1f  /* GAIN_MtoH Threshold level setting for switching middle gain to high gain */

#define REG_ADR_RSSI_ADJ_M        0, 0x20  /* RSSI offset value setting during middle gain operation */
#define REG_ADR_RSSI_ADJ_L        0, 0x21  /* RSSI offset value setting during low gain operation */
#define REG_ADR_RSSI_STABLE_TIME  0, 0x22  /* Time parameter for RSSI value become stable after gain switch */
#define REG_ADR_RSSI_VAL_ADJ      0, 0x23  /* RSSI scale factor setting for ED value conversion */
#define REG_ADR_INT_SOURCE_GRP1   0, 0x24  /* FIFO clear setting and interrupt status for INT00 to INT05 */
#define REG_ADR_INT_SOURCE_GRP2   0, 0x25  /* Interrupt status for INT08 to INT15 */
#define REG_ADR_INT_SOURCE_GRP3   0, 0x26  /* Interrupt status for INT16 to INT23 */
#define REG_ADR_INT_SOURCE_GRP4   0, 0x27  /* Interrupt status for INT24 and INT25 */
#define REG_ADR_PD_DATA_REQ       0, 0x28  /* Data transmission request status indication */
#define REG_ADR_PD_DATA_IND       0, 0x29  /* Data reception status indication */
#define REG_ADR_INT_EN_GRP1       0, 0x2a  /* Interrupt mask for INT00 to INT05 */
#define REG_ADR_INT_EN_GRP2       0, 0x2b  /* Interrupt mask for INT08 to INT15 */
#define REG_ADR_INT_EN_GRP3       0, 0x2c  /* Interrupt mask for INT16 to INT23 */
#define REG_ADR_INT_EN_GRP4       0, 0x2d  /* Interrupt mask for INT24 and INT25 */
#define REG_ADR_CH_EN_L           0, 0x2e  /* RF channel enable setting for low 8ch */
#define REG_ADR_CH_EN_H           0, 0x2f  /* RF channel enable setting for high 8ch */
#define REG_ADR_IF_FREQ_AFC_H     0, 0x30  /* IF frequency setting during AFC operation (high byte) */
#define REG_ADR_IF_FREQ_AFC_L     0, 0x31  /* IF frequency setting during AFC operation (low byte) */
#define REG_ADR_BPF_AFC_ADJ_H     0, 0x32  /* Bandpass filter capacitance adjustment during AFC operation (high 2bits) */
#define REG_ADR_BPF_AFC_ADJ_L     0, 0x33  /* Bandpass filter capacitance adjustment during AFC operation (low byte) */
#define REG_ADR_AFC_CNTRL         0, 0x34  /* AFC control setting */
#define REG_ADR_TX_ALARM_LH       0, 0x35  /* TX FIFO full level setting */
#define REG_ADR_TX_ALARM_HL       0, 0x36  /* TX FIFO empty level setting */
#define REG_ADR_RX_ALARM_LH       0, 0x37  /* RX FIFO full level setting */
#define REG_ADR_RX_ALARM_HL       0, 0x38  /* RX FIFO empty level setting */
#define REG_ADR_PREAMBLE_SET      0, 0x39  /* Preamble pattern setting */
#define REG_ADR_SFD1_SET1         0, 0x3a  /* SFD pattern #1 1st byte setting (max 4byte) */
#define REG_ADR_SFD1_SET2         0, 0x3b  /* SFD pattern #1 2nd byte setting (max 4byte) */
#define REG_ADR_SFD1_SET3         0, 0x3c  /* SFD pattern #1 3rd byte setting (max 4byte) */
#define REG_ADR_SFD1_SET4         0, 0x3d  /* SFD pattern #1 4th byte setting (max 4byte) */
#define REG_ADR_SFD2_SET1         0, 0x3e  /* SFD pattern #2 1st byte setting (max 4byte) */
#define REG_ADR_SFD2_SET2         0, 0x3f  /* SFD pattern #2 2nd byte setting (max 4byte) */
#define REG_ADR_SFD2_SET3         0, 0x40  /* SFD pattern #2 3rd byte setting (max 4byte) */
#define REG_ADR_SFD2_SET4         0, 0x41  /* SFD pattern #2 4th byte setting (max 4byte) */
#define REG_ADR_TX_PR_LEN         0, 0x42  /* TX preamble length setting */
#define REG_ADR_RX_PR_LEN_SFD_LEN 0, 0x43  /* RX preamble setting and SFD length setting */
#define REG_ADR_SYNC_CONDITION    0, 0x44  /* Bit error tolerance setting in RX preamble and SFD detection */
#define REG_ADR_PACKET_MODE_SET   0, 0x45  /* Packet configuration */
#define REG_ADR_FEC_CRC_SET       0, 0x46  /* FEC and CRC configuration */
#define REG_ADR_DATA_SET          0, 0x47  /* Data configuration */
#define REG_ADR_CH0_FL            0, 0x48  /* Channel #0 frequency (F-counter) setting (low byte) */
#define REG_ADR_CH0_FM            0, 0x49  /* Channel #0 frequency (F-counter) setting (middle byte) */
#define REG_ADR_CH0_FH            0, 0x4a  /* Channel #0 frequency (F-counter) setting (high 4bits) */
#define REG_ADR_CH0_NA            0, 0x4b  /* Channel #0 frequency (N-counter and A-counter) setting */
#define REG_ADR_CH_SPACE_L        0, 0x4c  /* Channel space setting (low byte) */
#define REG_ADR_CH_SPACE_H        0, 0x4d  /* Channel space setting (high byte) */
#define REG_ADR_F_DEV_L           0, 0x4e  /* GFSK frequency deviation setting (low byte ) */
#define REG_ADR_F_DEV_H           0, 0x4f  /* GFSK frequency deviation setting (high byte) */
#define REG_ADR_ACK_TIMER_L       0, 0x50  /* Ack timer setting (low byte) */
#define REG_ADR_ACK_TIMER_H       0, 0x51  /* Ack timer setting (high byte) */
#define REG_ADR_ACK_TIMER_EN      0, 0x52  /* Ack timer control setting */
#define REG_ADR_ACK_FRAME1        0, 0x53  /* Ack Frame Control Field (2bytes) setting (low byte) */
#define REG_ADR_ACK_FRAME2        0, 0x54  /* Ack Frame Control Field (2bytes) setting (high byte) */
#define REG_ADR_AUTO_ACK_SET      0, 0x55  /* Auto_Ack function setting */
#define REG_ADR_GFIL00_FSK_FDEV1  0, 0x59  /* Gaussian filter coefficient setting 1 / FSK 1st frequency deviation setting */
#define REG_ADR_GFIL01_FSK_FDEV2  0, 0x5a  /* Gaussian filter coefficient setting 2 / FSK 2nd frequency deviation setting */
#define REG_ADR_GFIL02_FSK_FDEV3  0, 0x5b  /* Gaussian filter coefficient setting 3 / FSK 3rd frequency deviation setting */
#define REG_ADR_GFIL03_FSK_FDEV4  0, 0x5c  /* Gaussian filter coefficient setting 4 / FSK 4th frequency deviation setting */
#define REG_ADR_GFIL04            0, 0x5d  /* Gaussian filter coefficient setting 5 */
#define REG_ADR_GFIL05            0, 0x5e  /* Gaussian filter coefficient setting 6 */
#define REG_ADR_GFIL06            0, 0x5f  /* Gaussian filter coefficient setting 7 */
#define REG_ADR_GFIL07            0, 0x60  /* Gaussian filter coefficient setting 8 */
#define REG_ADR_GFIL08            0, 0x61  /* Gaussian filter coefficient setting 9 */
#define REG_ADR_GFIL09            0, 0x62  /* Gaussian filter coefficient setting 10 */
#define REG_ADR_GFIL10            0, 0x63  /* Gaussian filter coefficient setting 11 */
#define REG_ADR_GFIL11            0, 0x64  /* Gaussian filter coefficient setting 12 */
#define REG_ADR_FSK_TIME1         0, 0x65  /* FSK 3rd frequency deviation (FDEV3) hold time setting */
#define REG_ADR_FSK_TIME2         0, 0x66  /* FSK 2nd frequency deviation (FDEV2) hold time setting */
#define REG_ADR_FSK_TIME3         0, 0x67  /* FSK 1st frequency deviation (FDEV1) hold time setting */
#define REG_ADR_FSK_TIME4         0, 0x68  /* FSK no-deviation frequency (carrier frequency) hold time setting */
#define REG_ADR_PLL_MON_DIO_SEL   0, 0x69  /* PLL lock detection signal output control and DIO mode configuration */
#define REG_ADR_FAST_TX_SET       0, 0x6a  /* TX trigger level setting in FAST_TX mode */
#define REG_ADR_CH_SET            0, 0x6b  /* RF channel setting */
#define REG_ADR_RF_STATUS         0, 0x6c  /* RFstate setting and status indication */
#define REG_ADR_2DIV_ED_AVG       0, 0x6d  /* Average number setting for ED calculation during 2 diversity */
#define REG_ADR_2DIV_GAIN_CNTRL   0, 0x6e  /* Gain control setting during 2 diversity */
#define REG_ADR_2DIV_SEARCH       0, 0x6f  /* 2 diversity search mode and search time setting */
#define REG_ADR_2DIV_FAST_LV      0, 0x70  /* ED threshold level setting during 2 diversity FAST mode */
#define REG_ADR_2DIV_CNTRL        0, 0x71  /* 2 diversity setting */
#define REG_ADR_2DIV_RSLT         0, 0x72  /* 2 diversity resurt indication and forced antenna control setting */
#define REG_ADR_ANT1_ED           0, 0x73  /* Acquired ED value by antenna 1 */
#define REG_ADR_ANT2_ED           0, 0x74  /* Acquired ED value by antenna 2 */
#define REG_ADR_RF_CNTRL_SET      0, 0x75  /* RF control pin configuration (ANT_SW, TRX_SW,DCNT) */
#define REG_ADR_CRC_AREA_FIFO_TRG 0, 0x77  /* CRC calculation field and FIFO trigger setting */
#define REG_ADR_RSSI_MON          0, 0x78  /* RSSI value indication */
#define REG_ADR_TEMP_MON          0, 0x79  /* Temperature indication */
#define REG_ADR_PN9_SET_L         0, 0x7a  /* PN9 initialized status setting / randum number indication (low byte) */
#define REG_ADR_PN9_SET_H         0, 0x7b  /* PN9 initialized status setting / randum number indication (high 1bit) and PN9 enable control */
#define REG_ADR_RD_FIFO_LAST      0, 0x7c  /* FIFO remaining size or FIFO address indication */u
#define REG_ADR_WR_TX_FIFO        0, 0x7e  /* TX FIFO */
#define REG_ADR_RD_RX_FIFO        0, 0x7f  /* RX FIFO */

#define REG_ADR_DEMOD_SET         1, 0x01  /* Demodulator setting */
#define REG_ADR_RSSI_ADJ          1, 0x02  /* RSSI value adjustment */
#define REG_ADR_RSSI_TEMP_OUT     1, 0x03  /* RSSI and Temperature data output setting */
#define REG_ADR_PA_ADJ1           1, 0x04  /* PA adjustment 1st setting */
#define REG_ADR_PA_ADJ2           1, 0x05  /* PA adjustment 2nd setting */
#define REG_ADR_PA_ADJ3           1, 0x06  /* PA adjustment 3rd setting */
#define REG_ADR_PA_CNTRL          1, 0x07  /* External PA control and PA mode setting */
#define REG_ADR_SW_OUT_RAMP_ADJ   1, 0x08  /* ANT_SW/TRX_SW configuration and PA ramping up adjustment */
#define REG_ADR_PLL_CP_ADJ        1, 0x09  /* PLL charge pump current adjustment */
#define REG_ADR_IF_FREQ_H         1, 0x0a  /* IF frequency setting (high byte) */
#define REG_ADR_IF_FREQ_L         1, 0x0b  /* IF frequency setting (low byte) */
#define REG_ADR_IF_FREQ_CCA_H     1, 0x0c  /* IF frequency setting during CCA operation (high byte) */
#define REG_ADR_IF_FREQ_CCA_L     1, 0x0d  /* IF frequency setting during CCA operation (low byte) */
#define REG_ADR_BPF_ADJ_H         1, 0x0e  /* Bandpass filter bandwidth adjustment (high 2bits) */
#define REG_ADR_BPF_ADJ_L         1, 0x0f  /* Bandpass filter bandwidth adjustment (low byte) */
#define REG_ADR_BPF_CCA_ADJ_H     1, 0x10  /* Bandpass filter bandwidth adjustment during CCA operation (high 2bits) */
#define REG_ADR_BPF_CCA_ADJ_L     1, 0x11  /* Bandpass filter bandwidth adjustment during CCA operation (low byte) */
#define REG_ADR_RSSI_LPF_ADJ      1, 0x12  /* RSSI lowpass filter adjustment */
#define REG_ADR_PA_REG_FINE_ADJ   1, 0x13  /* PA regulator fine adjustment */
#define REG_ADR_IQ_MAG_ADJ        1, 0x14  /* IF I/Q amplitude balance adjustment */
#define REG_ADR_IQ_PHASE_ADJ      1, 0x15  /* IF I/Q phase balance adjustment */
#define REG_ADR_VCO_CAL_MIN_FL    1, 0x16  /* VCO calibration low limit frequency setting (low byte) */
#define REG_ADR_VCO_CAL_MIN_FM    1, 0x17  /* VCO calibration low limit frequency setting (middle byte) */
#define REG_ADR_VCO_CAL_MIN_FH    1, 0x18  /* VCO calibration low limit frequency setting (high 4bits) */
#define REG_ADR_VCO_CAL_MAX_N     1, 0x19  /* VCO calibration upper limit frequency setting */
#define REG_ADR_VCO_CAL_MIN       1, 0x1a  /* VCO calibration low limit value indication and setting */
#define REG_ADR_VCO_CAL_MAX       1, 0x1b  /* VCO calibration upper limit value indication and setting */
#define REG_ADR_VCO_CAL           1, 0x1c  /* VCO_CAL VCO calibration value indication and setting */
#define REG_ADR_VCO_CAL_START     1, 0x1d  /* VCO calibration execution */
#define REG_ADR_BPF_ADJ_OFFSET    1, 0x1e  /* BPF adjustment offset value indication */
#define REG_ADR_ID_CODE           1+8, 0x2b /* ID code indication */
#define REG_ADR_PA_REG_ADJ1       1+8, 0x33 /* PA regulator adjustment (1st setting) */
#define REG_ADR_PA_REG_ADJ2       1+8, 0x34 /* PA regulator adjustment (2nd setting) */
#define REG_ADR_PA_REG_ADJ3       1+8, 0x35 /* PA regulator adjustment (3rd setting) */
#define REG_ADR_PLL_CTRL          1+8, 0x3a  /* PLL setting */
#define REG_ADR_RX_ON_ADJ2        1+8, 0x3f  /* RX_ON timing adjustment #2 */
#define REG_ADR_LNA_GAIN_ADJ_M    1+8, 0x49  /* LNA gain adjustment during middle gain operation */
#define REG_ADR_LNA_GAIN_ADJ_L    1+8, 0x4a  /* LNA gain adjustment during low gain operation */
#define REG_ADR_MIX_GAIN_ADJ_H    1+8, 0x4d  /* Mixer gain adjustment during high gain operation */
#define REG_ADR_MIX_GAIN_ADJ_M    1+8, 0x4e  /* Mixer gain adjustment during middle gain operation */
#define REG_ADR_MIX_GAIN_ADJ_L    1+8, 0x4f  /* Mixer gain adjustment during low gain operation */
#define REG_ADR_TX_OFF_ADJ1       1+8, 0x55  /* TX_OFF ramping down adjustment */
#define REG_ADR_RSSI_SLOPE_ADJ    1+8, 0x5a  /* RSSI slope adjustment */

#define REG_ADR_DEMSET3           2+8, 0x03  /* AFC Point of inflection detection MAX threshold 2 */
#define REG_ADR_DEMSET14          2+8, 0x0E  /* The noise amplitude detection threshold */
#define REG_ADR_SYNC_MODE         2+8, 0x12  /* Bit synchronization mode setting */
#define REG_ADR_PA_ON_ADJ         2+8, 0x1e  /* PA_ON timing adjustment */
#define REG_ADR_DATA_IN_ADJ       2+8, 0x1f  /* DATA enable timing adjustment */
#define REG_ADR_RX_ON_ADJ         2+8, 0x22  /* RX_ON timing adjustment */
#define REG_ADR_RXD_ADJ           2+8, 0x24  /* RXD timing adjustment */
#define REG_ADR_RATE_ADJ1         2, 0x2a    /* Demodulator adjustment for optional data rate (low byte) */
#define REG_ADR_RATE_ADJ2         2, 0x2b    /* Demodulator adjustment for optional data rate (high 2 bits) */
#define REG_ADR_RAMP_CNTRL        2+8, 0x2c  /* Ramp control enable setting */
#define REG_ADR_PRIVATE_BPF_CAP1  2+8, 0x2d  /* BPF capacity setting 1 */
#define REG_ADR_PRIVATE_BPF_CAP2  2+8, 0x2e  /* BPF capacity setting 2 */
#define REG_ADR_PRIVATE_BPF_ADJ1  2+8, 0x2f  /* BPF adjustment */
#define REG_ADR_PRIVATE_BPF_ADJ2  2+8, 0x30  /* BPF adjustment */
#define REG_ADR_ADDFIL_CNTRL      2, 0x60  /* Address filtering function setting */
#define REG_ADR_PANID_L           2, 0x61  /* PANID setting for address filtering function (low byte) */
#define REG_ADR_PANID_H           2, 0x62  /* PANID setting for address filtering function (high byte) */
#define REG_ADR_64ADDR1           2, 0x63  /* 64bit address setting for address filtering function (1st byte) */
#define REG_ADR_64ADDR2           2, 0x64  /* 64bit address setting for address filtering function (2nd byte) */
#define REG_ADR_64ADDR3           2, 0x65  /* 64bit address setting for address filtering function (3rd byte) */
#define REG_ADR_64ADDR4           2, 0x66  /* 64bit address setting for address filtering function (4th byte) */
#define REG_ADR_64ADDR5           2, 0x67  /* 64bit address setting for address filtering function (5th byte) */
#define REG_ADR_64ADDR6           2, 0x68  /* 64bit address setting for address filtering function (6th byte) */
#define REG_ADR_64ADDR7           2, 0x69  /* 64bit address setting for address filtering function (7th byte) */
#define REG_ADR_64ADDR8           2, 0x6a  /* 64bit address setting for address filtering function (8th byte) */
#define REG_ADR_SHT_ADDR0_L       2, 0x6b  /* Short address #0 setting for address filtering function (low byte) */
#define REG_ADR_SHT_ADDR0_H       2, 0x6c  /* Short address #0 setting for address filtering function (high byte) */
#define REG_ADR_SHT_ADDR1_L       2, 0x6d  /* Short address #1 setting for address filtering function (low byte) */
#define REG_ADR_SHT_ADDR1_H       2, 0x6e  /* Short address #1 setting for address filtering function (high byte) */
#define REG_ADR_DISCARD_COUNT_L   2, 0x6f  /* Discarded packet number indication by address filtering (low byte) */
#define REG_ADR_DISCARD_COUNT_H   2, 0x70  /* Discarded packet number indication by address filtering (high byte) */

#define REG_ADR_WRITE_BIT         0x01     /* SPI light bit */

/** Public function
 */

extern int ml7396_hwif_init(void);
extern int ml7396_hwif_spi_transfer(const uint8_t *wdata, uint8_t *rdata, uint8_t size);
extern int ml7396_hwif_sint_handler(void (*func)(void));
extern int ml7396_hwif_sint_ei(void);
extern int ml7396_hwif_sint_di(void);
extern int ml7396_hwif_timer_start(uint16_t msec);
extern int ml7396_hwif_timer_stop(void);
extern int ml7396_hwif_timer_handler(void (*func)(void));
extern int ml7396_hwif_timer_ei(void);
extern int ml7396_hwif_timer_di(void);
extern int ml7396_hwif_timer_tick(uint32_t *msec);
extern int ml7396_hwif_regset(void *data);


#endif  /* #ifndef _INCLUDE_ML7396_REG_H */
