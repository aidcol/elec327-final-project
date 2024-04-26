# Project Overview
The MSPEGGIATOR is a simple arpeggiator built with the MSP430 that allows you to play the 7 chords in the C major (C, Dm, Em, F, G, Am, Bdim) in 4 different modes.
- Mode 1. Chord:   plays the 3 notes in the chord simultaneously.
- Mode 2. Up:      cycles from the lowest to highest note in the chord, for example C >> E >> G for the C chord. 
- Mode 3. Down:    cycles from the highest to lowest note in the chord, for example G >> E >> C for the C chord.
- Mode 4. Up-down: cycles from the lowest to highest note then back to the lowest note, for example C >> E >> G >> E >> C for the C chord.
At start up, the MSPEGGIATOR plays the C chord in mode 1. You can increment or decrement the code by pressing button 1 or 2, and increment or decrement the mode by pressing button 3 or 4. The LCD display will show the current chord in row 1 and the current mode number in row 2.

# Hardware/Software Description
## Buzzers
To play multiple notes at different frequencies, we use TimerA1 and its 3 CC registers (TA1CCR0. TA1CCR1, TA1CCR2) to drive 3 piezo buzzers. The timer is initialized to continuous-up mode, and each CC register is updated separately to different duty cycles corresponding to a note in a chord. The 7 chords have set periods for each note in the chord while the four arpeggio modes are achieved by toggling P2DIR to decide which buzzer is outputting at a given time, hence creating different cycles. The tempo at which the notes play is controlled by TimerA0 with a global variable TEMPO. All timers are handled by interrupt service routines.