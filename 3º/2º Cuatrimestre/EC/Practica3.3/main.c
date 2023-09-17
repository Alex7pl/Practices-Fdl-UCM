#include <msp430.h>
void main(void) {
 WDTCTL = WDTPW + WDTHOLD; // Detiene Watchdog
 PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
 P1DIR |= BIT0; // P1.0 salida
 P1OUT |= BIT0; // Enciende LED
 // Configuración TIMER_A:
 // TimerA1, ACLK/1, modo up, reinicia TACLR
 TA1CTL = TASSEL_1 | TACLR | MC_1;
 // ACLK tiene una frecuencia de 32768 Hz
 // Carga cuenta en TA1CCR0 0.1seg TA1CCR=(0,1*32768)-1
 TA1CCR0 = 32767;
 TA1CCTL0 = CCIE; // Habilita interrupción (bit CCIE)
 // LPM0, habilitación general de interrupciones
 __low_power_mode_0();
 __no_operation();
}
// Rutina de interrupción de TIMER1_A0
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
 P1OUT ^= 0x01; // conmuta LED en P1.0
}
