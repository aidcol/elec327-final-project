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
    case 0: // Cmaj
        period1 = C1;
        period2 = E1;
        period3 = G1;
        period4 = B2;
        break;
    case 1: // Dmin
        period1 = D1;
        period2 = F1;
        period3 = A1;
        period4 = C2;
        break;
    case 2: // Emin
        period1 = E1;
        period2 = G1;
        period3 = B1;
        period4 = D2;
        break;
    case 3: // Fmaj
        period1 = F1;
        period2 = A1;
        period3 = C2;
        period4 = E2;
        break;
    case 4: // Gmaj
        period1 = G1;
        period2 = B1;
        period3 = D2;
        period4 = F2;
        break;
    case 5: // Amin
        period1 = A1;
        period2 = C2;
        period3 = E2;
        period4 = G2;
        break;
    case 6: // Bdim
        period1 = B1;
        period2 = D2;
        period3 = F2;
        period4 = A2;
        break;
    case 7: // Cmaj
        period1 = C2;
        period2 = E2;
        period3 = G2;
        period4 = B2;
        break;
    }
}


void set_mode(unsigned int m) {
    mode = m;

    switch(m) {
    case 0: // Chord mode
        note = 0;
        break;
    case 1: // Up mode
        note = 3;
        break;
    case 2: // Down mode
        note = 1;
        break;
    case 3: // Up-down mode
        note = 4;
        break;
    }
}


void set_note_outs(unsigned int note) {
    switch(note) {
    case 0:
        P2DIR = BIT0 + BIT1 + BIT4;
        break;
    case 1:
        P2DIR = BIT0;
        break;
    case 2: case 4:
        P2DIR = BIT1;
        break;
    case 3:
        P2DIR = BIT4;
        break;
    }
}


void next_note(unsigned int mode) {
    if (mode == 0) {
        note = 0;
    }

    if (mode > 0) { // Chord mode is mode=0
        switch(mode) {
        case 1:     // Up mode
            note += 1;
            if (note == 4) {
                note = 1;
            }
            break;
        case 2:     // Down mode
            note -= 1;
            if (note == 0) {
                note = 3;
            }
            break;
        case 3:     // Up-down mode
            note += 1;
            if (note == 5) {
                note = 1;
            }
            break;
        }
    }

    if (note > 5) { // Prevent `note` from going out of bounds
        note = 1;
    }

    set_note_outs(note);
}

