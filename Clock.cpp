/****
 *
 *   Part of the "Clock" library for Arduino. Version 1.0
 *
 *   Clock.cpp Copyright 2013 by D. L. Ehnebuske 
 *   License terms: Creative Commons Attribution-ShareAlike 3.0 United States (CC BY-SA 3.0 US) 
 *                  See http://creativecommons.org/licenses/by-sa/3.0/us/ for specifics. 
 *
 *   The Clock class represents one of those Lavet motor quartz clock movements that are powered by a single
 *   AAA cell. It assumes the movement has been modified to bypass the quartz timing mechanism by tying
 *   the connections to the ends of its coil to two pins, tickPin and tockPin, of the Arduino. The clock is
 *   advanced by alternating pulses on the two pins. Each pulse advances the clock mechanism by one second.
 *
 ****/
 
#include "Clock.h"

/*
 *
 * Constructors
 *
 */

// Construct Clock attached to iPin and oPin
Clock::Clock(byte iPin, byte oPin) {
	tickPin = iPin;											// The Clock is attached to iPin and oPin
	tockPin = oPin;
	tick = true;											// Start with a "tick"
	accumus = accumSec = 0;									// Start with no accumulated time to work off
	pinMode(tickPin, OUTPUT);								// Set the tick pin of the clock's Lavet motor to OUTPUT,
	digitalWrite(tickPin, LOW);								//   with a low-impedance path to ground
	pinMode(tockPin, OUTPUT);								// Set the tock pin of the clock's Lavet motor to OUTPUT,
	digitalWrite(tockPin, LOW);								//   with a low impedance path to ground
}

/*
 *
 * Operational methods
 *
 */
// Drive the clock forward by amt μs if > 0 or pause it if < 0
void Clock::driveMicros(long amt) {
	accumus += amt;											// Adjust what we need to work off
	while (accumus > 2000000) {								// While we have more than 2 sec to work off
		accumSec++;											//  Transfer one second to accumSec
		accumus -= 1000000;
	}
	while (accumus < 1500000 && accumSec > 0) {				// While we are running low on μs but have sec
		accumus += 1000000;									//  Transfer one second to accumus
		accumSec--;
	}
	while (accumSec < 0 && accumus > -2000000) {			// While we have a deficit of seconds and a not much of one in μs
		accumSec++;											//   Transfer one second to accumSec
		accumus -= 1000000;
	}
	if (accumus >= 500000) {								// if the clock is behind by at least a half second
		step();												//   Step the clock forward by one second
		accumus -= 1000000;									//   Decrement amount left to advance by one second
	}
	if (accumus >= 500000) {								// If we need yet another step
		delay(LAVET_STEP_INTERVAL);							//   Give the Lavet motor time to settle first
		step();												//   Step the clock forward by one second
		accumus -= 1000000;									//   Decrement amount left to advance by one second
  }

}

// Drive the clock forward by amt sec if > 0 or pause it if <0
void Clock::driveSec(long amt) {
	accumSec += amt;										// Add amt to number of secs to work off
}

// Reset accumulated time to work off
void Clock::cancelDrive() {
	accumus = accumSec = 0;									// Zero out the work to do.
}

/*
 *
 * Private methods
 *
 */
// Step clock forward one second
void Clock::step() {
	if (tick) {
		digitalWrite(tickPin, HIGH);						// Issue a tick pulse
		delay(LAVET_PULSE_DURATION);
		digitalWrite(tickPin, LOW);
	} else {
		digitalWrite(tockPin, HIGH);						// Issue a tock pulse
		delay(LAVET_PULSE_DURATION);
		digitalWrite(tockPin, LOW);
	}
	tick = !tick;											// Switch from tick to tock or vice versa
}
