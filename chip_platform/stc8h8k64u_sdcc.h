/*
** Copyright (c) 2023 The tiny51_os project. All rights reserved.
** Created by crisqifawei 2023
*/
#ifndef __STC8H8K64U_SDCC_H
#define __STC8H8K64U_SDCC_H


#include <8051.h>
#include <compiler.h>

#ifdef REG8051_H
#undef REG8051_H
#endif

/*
 * Auxiliary Register
 *   Bit Mapping: T0x12 T1x12 UART_M0x6 BRTR S2SMOD BRTx12 EXTRAM S1BRS
 *   Reset Value: 0000,0000
 */
SFR(AUXR, 0x8E);

/*
 * Auxiliary Register 1
 *   Bit Mapping: - PCA_P4 SPI_P4 S2_P4 GF2 ADRJ - DPS
 *   Reset Value: x000,00x0
 */
SFR(AUXR1, 0xA2);

/*
 * Control Register for Clock Output and Power Down Wake-up
 *   Bit Mapping: PCAWAKEUP RXD_PIN_IE T1_PIN_IE T0_PIN_IE
 *                LVD_WAKE BRTCLKO T1CLKO T0CLKO
 *                (Here "O" is the letter meaning "output", not the digit.)
 *   Reset Value: 0000,0000
 */
SFR(WAKE_CLKO, 0x8F);

/*
 * Clock Devider Register
 *   Bit Mapping: - - - - - CLKS2 CLKS1 CLKS0
 *   Reset Value: xxxx,x000
 */
SFR(CLK_DIV, 0x97);

/*
 * Stretch register
 *   Bit Mapping: - - ALES1 ALES0 - RWS2 RWS1 RWS0
 *   Reset Value: xx10,x011
 */
SFR(BUS_SPEED, 0xA1);

/* Two extended bits in IE */
SBIT(ELVD, 0xA8, 6); /* Enable Low Voltage Detection Interrupt */
SBIT(EADC, 0xA8, 5); /* Enable ADC Interrupt */

/*
 * Auxiliary Interrupt Register
 *   Bit Mapping: - - - - - - ESPI ES2
 *   Reset Value: xxxx,xx00
 */
SFR(IE2, 0xAF);

/* Three extended bits in IP */
SBIT(PPCA, 0xB8, 7); /* Interrupt Priority for PCA */
SBIT(PLVD, 0xB8, 6); /* Interrupt Priority for Low Voltage Detection */
SBIT(PADC, 0xB8, 5); /* Interrupt Priority for ADC */

/*
 * Higher bits for Interrupt Priority
 *   Bit Mapping: PPCAH PLVDH PADCH PSH PT1H PX1H PT0H PX0H
 *   Reset Value: 0000,0000
 */
SFR(IPH, 0xB7);

/*
 * The 2nd Interrupt Priority Register, Lower bits
 *   Bit Mapping: - - - - - - PSPI PS2
 *   Reset Value: xxxx,xx00
 */
SFR(IP2, 0xB5);

/*
 * The 2nd Interrupt Priority Register, Higher bits
 *   Bit Mapping: - - - - - - PSPIH PS2H
 *   Reset Value: xxxx,xx00
 */
SFR(IP2H, 0xB6);

/*
 * Two Extended GPIO Ports: P4 and P5
 * - For DIP-40 and QFN-40 packages, only higher 4 bits of P4 are available.
 * - For PLCC-44 and LQFP-44 packages, only all 8 bits of P4 are available.
 * - For LQFP-48 package, all 8 bits of P4 and lower 4 bits of P5 are
 *   available.
 */
SFR(P4, 0xC0);
    SBIT(P4_0, 0xC0, 0);
    SBIT(P4_1, 0xC0, 1);
    SBIT(P4_2, 0xC0, 2);
    SBIT(P4_3, 0xC0, 3);
    SBIT(P4_4, 0xC0, 4);
    SBIT(P4_5, 0xC0, 5);
    SBIT(P4_6, 0xC0, 6);
    SBIT(P4_7, 0xC0, 7);
SFR(P5, 0xC8); /* Only lower 4 bits */
    SBIT(P5_0, 0xC8, 0);
    SBIT(P5_1, 0xC8, 1);
    SBIT(P5_2, 0xC8, 2);
    SBIT(P5_3, 0xC8, 3);
SFR(P6, 0xE8);
SFR(P7, 0xF8);
/* Working Mode Registers for P0, P1, P2, P3, P4 and P5 */
SFR(P0M0, 0x94);
SFR(P0M1, 0x93);
SFR(P1M0, 0x92);
SFR(P1M1, 0x91);
SFR(P2M0, 0x96);
SFR(P2M1, 0x95);
SFR(P3M0, 0xB2);
SFR(P3M1, 0xB1);
SFR(P4M0, 0xB4);
SFR(P4M1, 0xB3);
SFR(P4SW, 0xBB); /* - LVD_P4.6 ALE_P4.5 NA_P4.4 - - - -   Reset: x000,xxxx */
SFR(P5M0, 0xCA);
SFR(P5M1, 0xC9);

SFR(P6M0, 0xCB);
SFR(P6M1, 0xCC);
SFR(P7M0, 0xE1);
SFR(P7M1, 0xE2);
/* Slave Address Mask for Serial Communication */
SFR(SADEN, 0xB9);

/* Slave Address for Serial Communication */
SFR(SADDR, 0xA9);

/*
 * The Control Register for the 2nd Serial Communication Port
 *   Bit Mapping: S2SM0 S2SM1 S2SM2 S2REN S2TB8 S2RB8 S2TI S2RI
 *   Reset Value: 0000,0000
 */
SFR(S2CON, 0x9A);

/* Data Buffer Register for the 2nd Serial Communication Port */
SFR(S2BUF, 0x9B);

/*
 * Reload Value Register for the Specific Baud Rate Generator
 * (Independent from the 8051 Timer)
 */
SFR(BRT, 0x9C);

/*
 * Watchdog Timer Control Register
 *   Bit Mapping: WDT_FLAG - EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0
 *   Reset Value: 0x00,0000
 */
SFR(WDT_CONTR, 0xC1);

/*
 * PCA Control Register
 *   Bit Mapping: CF CR - - - - CCF1 CCF0
 *   Reset Value: 00xx,xx00
 */
SFR(CCON, 0xD8);
    SBIT(CF, 0xD8, 7);
    SBIT(CR, 0xD8, 6);
    SBIT(CCF1, 0xD8, 1);
    SBIT(CCF0, 0xD8, 0);

/*
 * PCA Mode Register
 *   Bit Mapping: CIDL - - - CPS2 CPS1 CPS0 ECF
 *   Reset Value: 0xxx,x000
 */
SFR(CMOD, 0xD9);

/* PCA Counter Registers */
SFR(CL, 0xE9); /* Lower 8 bits */
SFR(CH, 0xF9); /* Higher 8 bits */

/*
 * PCA Module 0 PWM Register
 *   Bit Mapping: - ECOM0 CAPP0 CAPN0 MAT0 TOG0 PWM0 ECCF0
 *   Reset Value: x000,0000
 */
SFR(CCAPM0, 0xDA);

/*
 * PCA Module 1 PWM Register
 *   Bit Mapping: - ECOM1 CAPP1 CAPN1 MAT1 TOG1 PWM1 ECCF1
 *   Reset Value: x000,0000
 */
SFR(CCAPM1, 0xDB);

/* PCA Module 0/1 Capture/Comparison Registers */
SFR(CCAP0L, 0xEA);
SFR(CCAP0H, 0xFA);
SFR(CCAP1L, 0xEB);
SFR(CCAP1H, 0xFB);

/*
 * PCA Module 0 PWM Auxiliary Register
 *   Bit Mapping: - - - - - - EPC0H EPC0L
 *   Reset Value: xxxx,xx00
 */
SFR(PCA_PWM0, 0xF2);

/*
 * PCA Module 1 PWM Auxiliary Register
 *   Bit Mapping: - - - - - - EPC1H EPC1L
 *   Reset Value: xxxx,xx00
 */
SFR(PCA_PWM1, 0xF3);

/* Switch P1 pins between ADC inputs and GPIO Port pins */
SFR(P1ASF, 0x9D);

/*
 * ADC Control Register
 *   Bit Mapping: ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0
 *   Reset Value: 0000,0000
 */
SFR(ADC_CONTR, 0xBC);

/* ADC Converting Result Registers */
SFR(ADC_RES, 0xBD); /* Higher Bits */
SFR(ADC_RESL, 0xBE); /* Lower Bits */

/*
 * SPI Control Register
 *   Bit Mapping: SSIG SPEN DORD MSTR CPOL CPHA SPR1 SPR0
 *   Reset Value: 0000,0100
 */
SFR(SPCTL, 0xCE);

/*
 * SPI Status Register
 *   Bit Mapping: SPIF WCOL - - - - - -
 *   Reset Value: 00xx,xxxx
 */
SFR(SPSTAT, 0xCD);

/* SPI Data Register */
SFR(SPDAT, 0xCF);

/* In-Application-Programming Data Register */
SFR(IAP_DATA, 0xC2);

/* In-Application-Programming Address Registers */
SFR(IAP_ADDRH, 0xC3); /* Higher 8 bits */
SFR(IAP_ADDRL, 0xC4); /* Lower 8 bits */

/*
 * In-Application-Programming Address Registers
 *   Bit Mapping: - - - - - - MS1 MS0
 *   Reset Value: xxxx,xx00
 */
SFR(IAP_CMD, 0xC5);

/* In-Application-Programming Trigger Registers */
SFR(IAP_TRIG, 0xC6);

/*
 * In-Application-Programming Control Register
 *   Bit Mapping: IAPEN SWBS SWRST CFAIL - WT2 WT1 WT0
 *   Reset Value: 0000,x000
 */
SFR(IAP_CONTR, 0xC7);

SFRX(P0PU, 0xFE10);
SFRX(P1PU, 0xFE11);
SFRX(P2PU, 0xFE12);
SFRX(P3PU, 0xFE13);
SFRX(P4PU, 0xFE14);
SFRX(P5PU, 0xFE15);
SFRX(P6PU, 0xFE16);
SFRX(P7PU, 0xFE17);

SFRX(P0DR, 0xFE28);
SFRX(P1DR, 0xFE29);
SFRX(P2DR, 0xFE2A);
SFRX(P3DR, 0xFE2B);
SFRX(P4DR, 0xFE2C);
SFRX(P5DR, 0xFE2D);
SFRX(P6DR, 0xFE2E);
SFRX(P7DR, 0xFE2F);

SFRX(T2L, 0xD7);
SFRX(T2H, 0xD6);

#endif //__STC8H8K64U_SDCC_H
