/*
 * gcode.c
 *
 *  Created on: Apr 1, 2016
 *      Author: Isaac
 */


#include "gcode.h"
#include "L6472.h"
#include "LaserBoard.h"


/****************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************/
// G0 speed
static float f_g0 = 3;
// G1 speed
static float f_g1 = 3;
// M3 and M5 laser intensity
static uint8_t s_m3_m5;


/****************************************************************************
 * G0: Rapid positioning
 ****************************************************************************/
// Set f paramter
void G0_f( float f ) {
	//f_g0 = f;
}

// Execute move to position (x,y)
void G0_xy( float x, float y ) {
	// Configure speed
	x_set_max_speed( f_g0 );
	y_set_max_speed( f_g0 );

	// Execute move
	move_coord( x, y );
}


/****************************************************************************
 * G1: Linear interpolation
 ****************************************************************************/
// Set f (speed) paramter
void G1_f( float f ) {
	//f_g1 = f;
}

// Execute move to position (x,y)
void G1_xy( float x, float y ) {
	// Configure speed
	x_set_max_speed( f_g1 );
	y_set_max_speed( f_g1 );

	// Execute move
	move_coord( x, y );
}


/****************************************************************************
 * G4: Dwell
 ****************************************************************************/
//
void G4_p( float p ) {
	// do nothing right now
}


/****************************************************************************
 * G1: Linear interpolation
 ****************************************************************************/
// Program in MMs
void G21( void ) {
	//lol does nothing
}


/****************************************************************************
 * G90: Absolute position
 ****************************************************************************/
// Set origin to current location
void G90( void ) {
	// Lock in zero position on x and y
	x_set_origin();
	y_set_origin();
}


/****************************************************************************
 * M3: Laser on
 ****************************************************************************/
// Turn on laser
void M3_s( uint8_t s ) {
	// Set intensity (this variable does nothing)
	s_m3_m5 = s;

	laser_on();
}


/****************************************************************************
 * M5: Laser off
 ****************************************************************************/
// Turn off laser
void M5_s( uint8_t s ) {
	// Set intensity (this variable does nothing)
	s_m3_m5 = s;

	laser_off();
}

/****************************************************************************
 * M18: Disable stepper motors
 ****************************************************************************/
// Release x and y motor bridges
void M18( void ) {
	x_release_bridge();
	y_release_bridge();
}
