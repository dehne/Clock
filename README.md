# Lavet Motor Clock Library

Lavet Motor Clock Library Copyright 2013 by D. L. Ehnebuske  
License terms: [Creative Commons Attribution-ShareAlike 3.0 United States (CC BY-SA 3.0 US)]
(http://creativecommons.org/licenses/by-sa/3.0/us/ "CC BY-SA 3.0 US")

## What is a "Lavet motor clock"?

A Lavet motor clock is one of those quartz-controlled clock movements that are typically powered by 
a single AA or AAA cell. They are very commonly used to drive the hands of inexpensive "analog" clocks.
These clock movements can easily be repurposed so that they can be driven by an Arduino. Simply open
up the case and solder leads to the terminals of the coil of the Lavet motor.

## What does this library do?

The Clock class represents such a modified clock movement. It assumes the connections to the ends of 
the coil are tied through a current-limiting resistor to two digital pins, referred to as tickPin and 
tockPin, on the Arduino. The movement is advanced by alternating pulses on the two pins. Each pulse 
advances the movement by one second.

The main method for a Clock object is driveMicros(). This method advances the clock movement it 
represents by the number of microseconds passed as an argument. This method is intended to be invoked 
repeatedly in the loop() of an Arduino sketch that has calculated the amount of time that has passed 
since driveMicros() was last invoked. The driveMicros() method keeps track of these passing microseconds 
and advances the movement to keep the clock to within 1/2 second of correct. 

The driveMicros() method can also be used to adjust the clock by passing the amount of the adjustment
to be made. Passing positive values advances the clock, negative values pause the clock until the 
ongoing passage of time catches up with the time indicated on the clock.

To make larger adjustments to the time displayed on the clock, the driveSec() method may be used to
advance or delay the clock by the number of seconds it is passed.

Finally, cancelDrive() may be used to cancel any adjustment that may have been started with
driveMicros() or driveSec().
