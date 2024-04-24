/*
 * buzzer.h
 *
 *  Created on: Apr 9, 2024
 *      Author: aidan
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#define C1 1911
#define D1 1703
#define E1 1517
#define F1 1432
#define G1 1276
#define A1 1136
#define B1 1012
#define C2 956
#define D2 851
#define E2 758
#define F2 716
#define G2 638
#define A2 568
#define B2 506


unsigned int period1, period2, period3, period4;
int chord;
int mode;
unsigned int note;


void set_chord(unsigned int chord);
void set_mode(unsigned int mode);
void next_note(unsigned int mode);


#endif /* BUZZER_H_ */
