#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= BIT0;
    P1OUT |= BIT0;
    P1OUT |= BIT1;
    P1REN |= BIT1;
    P1IE  |= BIT1;
    P1IFG &= ~BIT1;

    __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){

    P1OUT ^= BIT0;
    P1IFG &= ~BIT1;
}
