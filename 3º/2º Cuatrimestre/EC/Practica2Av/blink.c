#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= 0x01;                          // Set P1.0 to output direction
    P1REN |= BIT2;

    for(;;) {

        if(!(P1IN & BIT2)){

            P1OUT &= ~BIT0;
        }
        else {

            P1OUT |= BIT0;
        }
    }
}
