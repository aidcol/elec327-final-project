#include <msp430.h> 
#include <buzzer.h>


/**
 * main.c
 */
unsigned int chord = 7;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // Configure PWM outputs
    P2DIR |= (BIT0 + BIT1 + BIT4 + BIT6);
    P2SEL |= (BIT0 + BIT1 + BIT4 + BIT6);

    // Configure TimerA0 and TimerA1
    TA0CTL = TASSEL_2 + MC_2;       // SMCLK, continuous-mode
    TA1CTL = TASSEL_2 + MC_2;       // SMCLK, continuous-mode

    TA1CCTL0 = OUTMOD_4 + CCIE;     // TA1CCR0 interrupt enabled
    TA1CCTL1 = OUTMOD_4 + CCIE;     // TA1CCR1 interrupt enabled
    TA1CCTL2 = OUTMOD_4 + CCIE;     // TA1CCR2 interrupt enabled
    TA0CCTL1 = OUTMOD_4 + CCIE;     // TA0CCR1 interrupt enabled


    set_chord(chord);

    __bis_SR_register(GIE);         // Enable global interrupts
     while (1) {
         __bis_SR_register(LPM0_bits);       // Enter LPM0
     }
}


#pragma vector=TIMER1_A0_VECTOR                // Define TIMER0_A0 Interrupt Vector
__interrupt  void TIMER1_A0_ISR(void)           // TIMER0_A1 Interrupt Service Routine
{
    TA1CCR0 += period1;
    __bic_SR_register_on_exit(LPM0_bits);        // Return in Wake-Up Condition
}


#pragma  vector=TIMER1_A1_VECTOR                // Define TIMER0_A0 Interrupt Vector
__interrupt  void TIMER1_A1_ISR(void)           // TIMER0_A1 Interrupt Service Routine
{
    unsigned int temp;
    temp = TA1IV;

    if (temp == TA1IV_TACCR1) {                 // Only if TA0 Interrupt Came From CCR1 Compare
        TA1CCR1 += period2;
    }
    else if (temp == TA1IV_TACCR2) {
         TA1CCR2 += period3;
    }
    __bic_SR_register_on_exit(LPM0_bits);       // Return in Wake-Up Condition
}


#pragma vector=TIMER0_A1_VECTOR                // Define TIMER0_A0 Interrupt Vector
__interrupt  void TIMER0_A1_ISR(void)          // TIMER0_A1 Interrupt Service Routine
{
//     unsigned int temp;
//     temp = TA0IV;
//     if (temp == TA0IV_TACCR1){                 // Only if TA0 Interrupt Came From CCR1 Compare
//         period4 += C2;
//         TA1CCR1 = period4;
//     }
    TA0CCR1 += period4;
     __bic_SR_register_on_exit(LPM0_bits);       // Return in Wake-Up Condition
}
