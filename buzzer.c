/*
 * buzzer.c
 *
 *  Created on: Apr 9, 2024
 *      Author: aidan
 */

#include "msp430g2553.h"
#include "buzzer.h"


void set_chord(unsigned int chord) {
    switch(chord) {
    case 0:
        period1 = C1;
        period2 = E1;
        period3 = G1;
        period4 = B2;
        break;
    case 1:
        period1 = D1;
        period2 = F1;
        period3 = A1;
        period4 = C2;
        break;
    case 2:
        period1 = E1;
        period2 = G1;
        period3 = B1;
        period4 = D2;
        break;
    case 3:
        period1 = F1;
        period2 = A1;
        period3 = C2;
        period4 = E2;
        break;
    case 4:
        period1 = G1;
        period2 = B1;
        period3 = D2;
        period4 = F2;
        break;
    case 5:
        period1 = A1;
        period2 = C2;
        period3 = E2;
        period4 = G2;
        break;
    case 6:
        period1 = B1;
        period2 = D2;
        period3 = F2;
        period4 = A2;
        break;
    case 7:
        period1 = C2;
        period2 = E2;
        period3 = G2;
        period4 = B2;
        break;
    }
}




