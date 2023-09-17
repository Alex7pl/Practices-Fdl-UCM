#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P1DIR |= 0x01;                          // Set P1.0 to output direction
    P1REN |= BIT1;


    volatile unsigned int i;            // volatile to prevent optimization
    i = 0;


    for(;;) {

        if(!(P1IN & BIT1)){

            i ^= 1;

        }
        else{

            if(i == 0){

                P1OUT |= BIT0;
            }
            else{

                P1OUT &= ~BIT0;
            }
        }
    }
}
