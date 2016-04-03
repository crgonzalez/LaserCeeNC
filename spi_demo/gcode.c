/*
 * gcode.c
 *
 *  Created on: Apr 1, 2016
 *      Author: Isaac
 */

#include <math.h>

#include "gcode.h"
#include "L6472.h"
#include "LaserBoard.h"

#include "hw_types.h"
#include "hw_memmap.h"
#include "spi.h"
#include "rom_map.h"
#include "gpio.h"
#include "pin.h"
#include "prcm.h"
#include "uart_if.h"

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
 * Private function prototypes
 ****************************************************************************/
// Find the distance between (x,y) and (i,j)
float distance_xyij( float x, float y, float i, float j );


/****************************************************************************
 * G0: Rapid positioning
 ****************************************************************************/
// Set f paramter
void G0_f( float f ) {
	Report( "\r\nG0 F%f", f );
	//f_g0 = f;
}

// Execute move to position (x,y)
void G0_xy( float x, float y ) {
	Report( "\r\nG0 X%f Y%f", x, y );
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
	Report( "\r\nG1 F%f", f );
	//f_g1 = f;
}

// Execute move to position (x,y)
void G1_xy( float x, float y ) {
	Report( "\r\nG1 X%f Y%f", x, y );
	// Configure speed
	x_set_max_speed( f_g1 );
	y_set_max_speed( f_g1 );

	// Execute move
	move_coord( x, y );
}


/****************************************************************************
 * G2: Clockwise arc
 ****************************************************************************/
// Move to (x,y) while remaining equidistant form (i,j)
void G2_xyij( float x, float y, float i, float j ) {

	const float dist_threshold = 0.2;

	float x_cur = x_get_position();
	float y_cur = y_get_position();

	//Report( "\r\nStart X%f Y%f", x_cur, y_cur );

	float x_next;
	float y_next;

	const float radius = distance_xyij( x, y, i, j );
	float x_mov = 0.2;

	float cur_dist = distance_xyij( x, y, x_cur, y_cur );

	while( cur_dist > dist_threshold ) {
		//Report( "\r\nx_cur %f y_cur %f", x_cur, y_cur );
		if( y_cur < j ) {
			//Report( "A" );
			x_next = x_cur - x_mov;
			if( x_next < i - radius ) {
				x_next = i - radius;
				y_next = 0;
			} else {
				y_next = -sqrt( radius*radius - x_next*x_next );
			}
		} else if( y_cur == j && x_cur > i ) {
			//Report( "B" );
			x_next = x_cur - x_mov;
			y_next = -sqrt( radius*radius - x_next*x_next );

		} else if( y_cur == j && x_cur < i ) {
			//Report( "C" );
			x_next = x_cur + x_mov;
			y_next = sqrt( radius*radius - x_next*x_next );

		} else {
			//Report( "D" );
			x_next = x_cur + x_mov;
			if( x_next > i + radius ) {
				x_next = i + radius;
				y_next = 0;
			} else {
				y_next = sqrt( radius*radius - x_next*x_next );
			}
		}

		//x_next += x_cur;
		y_next += j;
		//Report( "\r\nX%f Y%f", x_next, y_next );
		move_coord( x_next, y_next );
		x_cur = x_get_position();
		y_cur = y_get_position();
		//x_cur = x_next;
		//y_cur = y_next;
		cur_dist = distance_xyij( x, y, x_cur, y_cur );
	}

	move_coord( x, y );

}


/****************************************************************************
 * G3: Counterclockwise arc
 ****************************************************************************/
// Move to (x,y) while remaining equidistant form (i,j)
void G3_xyij( float x, float y, float i, float j ) {

	const float dist_threshold = 0.2;

	float x_cur = x_get_position();
	float y_cur = y_get_position();

	//Report( "\r\nStart X%f Y%f", x_cur, y_cur );

	float x_next;
	float y_next;

	const float radius = distance_xyij( x, y, i, j );
	float x_mov = 0.2;

	float cur_dist = distance_xyij( x, y, x_cur, y_cur );

	while( cur_dist > dist_threshold ) {
		//Report( "\r\nx_cur %f y_cur %f", x_cur, y_cur );
		if( y_cur < j ) {
			Report( "A" );
			x_next = x_cur + x_mov;
			if( x_next > i + radius ) {
				x_next = i + radius;
				y_next = 0;
			} else {
				y_next = -sqrt( radius*radius - x_next*x_next );
			}
		} else if( y_cur == j && x_cur > i ) {
			Report( "B" );
			x_next = x_cur - x_mov;
			y_next = sqrt( radius*radius - x_next*x_next );

		} else if( y_cur == j && x_cur < i ) {
			Report( "C" );
			x_next = x_cur - x_mov;
			y_next = -sqrt( radius*radius - x_next*x_next );

		} else {
			Report( "D" );
			x_next = x_cur - x_mov;
			if( x_next < i - radius ) {
				x_next = i - radius;
				y_next = 0;
			} else {
				y_next = sqrt( radius*radius - x_next*x_next );
			}
		}

		//x_next += x_cur;
		y_next += j;
		//Report( "\r\nX%f Y%f", x_next, y_next );
		move_coord( x_next, y_next );
		x_cur = x_get_position();
		y_cur = y_get_position();
		//x_cur = x_next;
		//y_cur = y_next;
		cur_dist = distance_xyij( x, y, x_cur, y_cur );
	}

	move_coord( x, y );

}


/****************************************************************************
 * G4: Dwell
 ****************************************************************************/
//
void G4_p( float p ) {
	Report( "\r\nG4 P%f", p );
	// do nothing right now
}


/****************************************************************************
 * G21: MMs as units
 ****************************************************************************/
// Program in MMs
void G21( void ) {
	Report( "\r\nG21" );
	//lol does nothing
}


/****************************************************************************
 * G90: Absolute position
 ****************************************************************************/
// Set origin to current location
void G90( void ) {
	Report( "\r\nG90" );
	// Lock in zero position on x and y
	x_set_origin();
	y_set_origin();
}


/****************************************************************************
 * M3: Laser on
 ****************************************************************************/
// Turn on laser
void M3_s( uint16_t s ) {
	Report( "\r\nM3 S%d", s );
	// Set intensity (this variable does nothing)
	s_m3_m5 = s;

	laser_on();
}


/****************************************************************************
 * M5: Laser off
 ****************************************************************************/
// Turn off laser
void M5_s( uint16_t s ) {
	Report( "\r\nM5 S%d", s );
	// Set intensity (this variable does nothing)
	s_m3_m5 = s;

	laser_off();
}

/****************************************************************************
 * M18: Disable stepper motors
 ****************************************************************************/
// Release x and y motor bridges
void M18( void ) {
	Report( "\r\nM18" );
	x_release_bridge();
	y_release_bridge();
}


/****************************************************************************
 * Private function definitions
 ****************************************************************************/
// Find the distance between (x,y) and (i,j)
float distance_xyij( float x, float y, float i, float j ) {
	return sqrt( (x - i)*(x - i) + (y - j)*(y - j) );
}
