# MSPEGGIATOR Project Overview
The MSPEGGIATOR is a simple arpeggiator built with the MSP430 that allows you to play the 7 chords in the C major (C, Dm, Em, F, G, Am, Bdim) in 4 different modes.
- Mode 1. Chord:   plays the 3 notes in the chord simultaneously.
- Mode 2. Up:      cycles from the lowest to highest note in the chord, for example C >> E >> G for the C chord. 
- Mode 3. Down:    cycles from the highest to lowest note in the chord, for example G >> E >> C for the C chord.
- Mode 4. Up-down: cycles from the lowest to highest note then back to the lowest note, for example C >> E >> G >> E >> C for the C chord. \n
At start up, the MSPEGGIATOR plays the C chord in mode 1. You can increment or decrement the code by pressing button 1 or 2, and increment or decrement the mode by pressing button 3 or 4. The LCD display will show the current chord in row 1 and the current mode number in row 2.

# Hardware/Software Description
## Buzzers
To play multiple notes at different frequencies, we use TimerA1 and its 3 CC registers (TA1CCR0. TA1CCR1, TA1CCR2) to drive 3 piezo buzzers. The timer is initialized to continuous-up mode, and each CC register is updated separately to different duty cycles corresponding to a note in a chord. The 7 chords have set periods for each note in the chord while the four arpeggio modes are achieved by toggling P2DIR to decide which buzzer is outputting at a given time, hence creating different cycles. The tempo at which the notes play is controlled by TimerA0 with a global variable TEMPO. All timers are handled by interrupt service routines.

## Buttons
Four buttons are used to increment or decrement the current chord or arpeggio mode. They are connected to port P1 inputs where button presses of high to low transitions are detected by port 1 interrupt service routine. A helper function with bit masks is used to determine which button is pressed and perform the task for the corresponding button.

## LCD Display
The chord and mode are displayed on a 16x2 LCD display via I2C protocol. SDA on P1.7 controls the data line to transmit the data from the MSP430 to the display while SCL on P1.6 generates a clock signal to synchronize the data transfer.

## Block Diagram
The block diagram below shows the main components of the MSPEGGIATOR:
![mspeggiator_block](https://github.com/aidcol/elec327-final-project/assets/85061507/98978fad-2cf9-4a19-a46b-dfa9d840a3c3)

# Circuit Diagram
The circuit diagram below shows the wire connections for the MSPEGGIATOR. You can change the resistors connected to the piezo buzzers to control volume.
![mspeggiator_wiring](https://github.com/aidcol/elec327-final-project/assets/85061507/466f0a94-dbfd-498a-b099-75b5c556b3ea)

# Instructions
After wiring up the MSPEGGIATOR, download all the .c files and .h files and run the main.c file with Code Composer Studio to start jamming!

# Demo Video
Link: [https://rice.box.com/s/g15091qozm21yw360w6cgqeiamauzs9f].

by Aidan Colon, Maaz Zuberi, Hong-Ye Wang for ELEC 327 Spring 2024.
