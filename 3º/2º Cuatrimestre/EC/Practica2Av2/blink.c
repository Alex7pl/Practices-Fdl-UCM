#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    P1DIR |= 0x01;
    P1REN |= BIT1;
    P1REN |= BIT2;

    volatile unsigned int i;

    i = 0;

    for(;;) {

        if(!(P1IN && BIT1)){

           i ^= 1;
        }

        if(!(P1IN & BIT2)){

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
