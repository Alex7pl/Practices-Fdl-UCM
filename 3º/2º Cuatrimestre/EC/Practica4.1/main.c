#include <msp430.h>

unsigned int i = 0;
unsigned char letra = 65;

const char alphabetBig[26][2] =
{
 {0xEF, 0x00}, /* "A" LCD segments a+b+c+e+f+g+m */
 {0xF1, 0x50}, /* "B" */
 {0x9C, 0x00}, /* "C" */
 {0xF0, 0x50}, /* "D" */
 {0x9F, 0x00}, /* "E" */
 {0x8F, 0x00}, /* "F" */
 {0xBD, 0x00}, /* "G" */
 {0x6F, 0x00}, /* "H" */
 {0x90, 0x50}, /* "I" */
 {0x78, 0x00}, /* "J" */
 {0x0E, 0x22}, /* "K" */
 {0x1C, 0x00}, /* "L" */
 {0x6C, 0xA0}, /* "M" */
 {0x6C, 0x82}, /* "N" */
 {0xFC, 0x00}, /* "O" */
 {0xCF, 0x00}, /* "P" */
 {0xFC, 0x02}, /* "Q" */
 {0xCF, 0x02}, /* "R" */
 {0xB7, 0x00}, /* "S" */
 {0x80, 0x50}, /* "T" */
 {0x7C, 0x00}, /* "U" */
 {0x0C, 0x28}, /* "V" */
 {0x6C, 0x0A}, /* "W" */
 {0x00, 0xAA}, /* "X" */
 {0x00, 0xB0}, /* "Y" */
 {0x90, 0x28} /* "Z" */
};



void main(void) {

    WDTCTL = WDTPW + WDTHOLD; // Detiene Watchdog
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    CSCTL0_H = CSKEY >> 8; // Unlock clock registers
    CSCTL1 = DCOFSEL_3 | DCORSEL; // Set DCO to 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Set all dividers
    CSCTL0_H = 0; // Lock CS registers

    // Configure USCI_A1 for UART mode
     UCA1CTLW0 = UCSWRST;            // Put eUSCI in reset
     UCA1CTLW0 |= UCSSEL__SMCLK; // CLK = SMCLK

     // Baud Rate calculation
     // 8000000/(16*9600) = 52.083
     // Fractional portion = 0.083
     // User's Guide Table 21-4: UCBRSx = 0x04
     // UCBRFx = int ( (52.083-52)*16) = 1

     UCA1BR0 = 52;   // 8000000/16/9600
     UCA1BR1 = 0x00;
     UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
     UCA1CTLW0 &= ~UCSWRST; // Initialize eUSCI

    // Configure interruptions to receive and transmit data in register UCA1IE

     P3SEL0 |= BIT4;
     P3SEL1 &= ~BIT4;

     UCA1IE |= UCTXIE;

    __enable_interrupt();
    __low_power_mode_0();
    __no_operation();
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) {

    if(letra > 90){
        letra = 65;
        UCA1IE &= ~UCTXIE;
    }
    else{
        UCA1TXBUF = letra;
        letra++;
    }

    UCA1IFG &= ~UCTXIFG;
}

