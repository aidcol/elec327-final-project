#include <msp430.h> 
#include <buzzer.h>
#include <string.h>
#include <lcd.h>


/**
 * main.c
 */

// Helper functions
void init_pwm();
void init_buttons();
void check_buttons();


// Global variables
#define TEMPO 6000


unsigned int tempo_flag = 0;
int button_input = 0;
char str[] = "welcome";


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Initialize ACLK for TimerA0
    BCSCTL3 |= LFXT1S_2;            // ACLK = VLO

    // Initialize SMCLK/DCO for Timer A1
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // Configure TimerA0 for tempo
    TA0CTL = TASSEL_1 + MC_1;       // ACLK, up-mode
    TA0CCTL0 = CCIE;                // TA0CCR0 interrupt enabled
    TA0CCR0 = TEMPO;

    init_pwm();
    init_buttons();

    // Initialize chord and mode
    chord = 0;
    mode = 0;
    set_chord(chord);
    set_mode(mode);

    // Initialize Display text
    _EINT();
//    strcpy(str_chord, "C");
//    strcpy(str_mode, "1");
    LcdInit();


    __bis_SR_register(GIE);         // Enable global interrupts
    while (1) {
        if (tempo_flag == 1) {
            next_note(mode);
            tempo_flag = 0;
        }

        if (button_input != 0) {
            check_buttons();
        }

        set_chord(chord);
        LcdSetPosition(1,1); // Sets start of string to first character, first line
        LcdWriteString(str_chord); // String constantly being written while in while loop.
        LcdSetPosition(2,1); // Sets start of string to first character, first line
        LcdWriteString(str_mode); // String constantly being written while in while loop.

        __bis_SR_register(LPM0_bits);       // Enter LPM0
    }
}


// TimerA1 ISR (handles TA1.CCR0)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    TA1CCR0 += period1;
    __bic_SR_register_on_exit(LPM0_bits);
}


// TimerA1 ISR (handles TA1.CCR1, TA1.CCR2)
#pragma  vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{
    unsigned int temp;
    temp = TA1IV;

    if (temp == TA1IV_TACCR1) {
        TA1CCR1 += period2;
    }
    else if (temp == TA1IV_TACCR2) {
        TA1CCR2 += period3;
    }
    __bic_SR_register_on_exit(LPM0_bits);
}


// TimerA0 ISR (handles TA0.CCR1)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    tempo_flag = 1;
    __bic_SR_register_on_exit(LPM0_bits);
}


// Port 1 ISR (handles Button presses)
#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
    if ((P1IN & BIT0) == 0x00)  { //Check if button pressed is  button 1
        button_input = 1; //Set button input to show we pressed button 1
        //strcpy(str, "Button 1"); // Copy the new string into str
    }
    else if ((P1IN & BIT3) == 0x00) { //Check if button pressed is button 2
        button_input = 2; //Set button input to show we pressed button 2
        //strcpy(str, "Button 2");
    }
    else if ((P1IN & BIT4) == 0x00) {
        button_input = 3;
    }
    else if ((P1IN & BIT5) == 0x00) {
        button_input = 4;
    }

    P1IFG &= ~(BIT0 + BIT3 + BIT4 + BIT5); //clear and reset interrupts
}


void init_pwm() {
    // Configure output pins
    P2SEL |= (BIT0 + BIT1 + BIT4);

    // Configure TimerA1 for PWM output
    TA1CTL = TASSEL_2 + MC_2;       // SMCLK, continuous-mode
    TA1CCTL0 = OUTMOD_4 + CCIE;     // TA1CCR0 interrupt enabled
    TA1CCTL1 = OUTMOD_4 + CCIE;     // TA1CCR1 interrupt enabled
    TA1CCTL2 = OUTMOD_4 + CCIE;     // TA1CCR2 interrupt enabled
}


void init_buttons() {
    P1DIR &= ~(BIT0 + BIT3 + BIT4 + BIT5);  // set to input
    P1REN = BIT0 + BIT3 + BIT4 + BIT5;      // enable pullup/down resistors
    P1OUT = BIT0 + BIT3 + BIT4 + BIT5;      // set resistors to pull up


    P1IES = BIT0 + BIT3 + BIT4 + BIT5;      // listen for high to low transitions
    P1IFG &=  ~(BIT0 + BIT3 + BIT4 + BIT5); // clear any pending interrupts
    P1IE = BIT0 + BIT3 + BIT4 + BIT5;       // enable interrupts for these pins
}


void check_buttons() {
    if (button_input == 1) {
        button_input = 0; // 0 is null value
        chord = chord - 1;
        if(chord == -1) {
            chord = 6;
        }
    }

    if (button_input == 2) {
        button_input = 0; // 0 is null value
        chord = chord + 1;
        if(chord == 7) {
            chord = 0;
        }
    }

    if (button_input == 3) {
        button_input = 0; // 0 is null value
        mode = mode - 1;
        if(mode == -1) {
            mode = 3;
        }
        set_mode(mode);
    }

    if (button_input == 4) {
        button_input = 0; // 0 is null value
        mode = mode + 1;
        if(mode == 4) {
            mode = 0;
        }
        set_mode(mode);
    }
}


