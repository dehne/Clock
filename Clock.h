/****
 *
 *   Part of the "Clock" library for Arduino. Version 1.1
 *
 *   Clock.h Copyright 2013 by D. L. Ehnebuske 
 *   License terms: Creative Commons Attribution-ShareAlike 3.0 United States (CC BY-SA 3.0 US) 
 *                  See http://creativecommons.org/licenses/by-sa/3.0/us/ for specifics. 
 *
 *   The Clock class represents one of those Lavet motor quartz clock movements that are powered by a single
 *   AAA cell. It assumes the movement has been modified to bypass the quartz timing mechanism by tying
 *   the connections to the ends of its coil to two pins, tickPin and tockPin, of the Arduino. The clock is
 *   advanced by alternating pulses on the two pins. Each pulse advances the clock mechanism by one second.
 *
 ****/
#ifndef Clock_H
#define Clock_H

  #if ARDUINO >= 100
    #include <Arduino.h>  // Arduino 1.0
  #else
    #include <WProgram.h> // Arduino 0022
  #endif

// Some constants
#define LAVET_STEP_INTERVAL (200)			// Interval between steps of the Lavet motor (ms)
#define LAVET_PULSE_DURATION (40)			// Duration of the pulses that move the Lavet motor (ms)

// Compile-time options
#define FAST_TICK							// Uncomment if driveMicros() is called more often than about every 0.6 sec

class Clock {
private:
// Instance variables
	byte tickPin;							// The pin to pulse to tick the clock forward one second
	byte tockPin;							// The pin to pulse to tock the clock forward one second
	boolean tick;							// Step should "tick" the clock if true, "tock" it if not
	long accumus;							// Number of μs (in addition to accumSec) we need to work off
	long accumSec;							// Number of seconds (in addition to accumus) we need to work off
	
// Methods
	void step();							// Step clock forward one second
public:
// Constructors
	Clock(byte iPin = 10, byte oPin = 11);	// Construct Clock attached to iPin and oPin
	
// Operational methods
	void driveMicros(long amt);				// Drive the clock forward by amt μs if > 0 or pause it if < 0
	void driveSec(long amt);				// Drive the clock forward by amt sec if > 0 or pause it if < 0
	void cancelDrive();						// Reset accumulated time to work off
};
#endif