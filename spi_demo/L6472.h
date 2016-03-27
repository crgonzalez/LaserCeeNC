/*
 * L6472.h
 *
 *  Created on: Mar 12, 2016
 *      Author: Isaac
 */

#ifndef L6472_H_
#define L6472_H_

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef enum DIRECTION { POSITIVE, NEGATIVE } direction_t;

/**********************************************************************
 * Initialization function
 **********************************************************************/
void L6472_init( void );

/**********************************************************************
 * X and Y control functions
 **********************************************************************/
// Loop until x and y motor commands finish execution
//
// IMPORTANT - this function must be executed after simultaneous x and
// y move commands!
void 	xy_wait( void );

/**********************************************************************
 * Y motor control functions
 **********************************************************************/
// Reset the y motor controller
void	y_reset( void );

// Move the y axis a number of millimeters (positve or negative)
void 	y_move_mm( float MMs );

// Turn off current to a stationary motor
void	y_release_bridge( void );

// Set current position to the origin location
void 	y_set_origin( void );

// Return to origin position
void 	y_goto_origin( void );

// Loop until motor command finishes execution
//
// IMPORTANT - this function must be executed after a move command!
void 	y_wait( void );

// Choose the speed at which the motor will run
//
// RECOMENDATION - 0 to 4 for cutting speed, 10 for fast movement when not cutting
void 	y_set_max_speed( uint16_t speed );

uint16_t y_get_max_speed( void );

/**********************************************************************
 * X motor control functions
 **********************************************************************/
// Reset the x motor controller
void	x_reset( void );

// Move the x axis a number of millimeters (positve or negative)
void 	x_move_mm( float MMs );

// Turn off current to a stationary motor
void	x_release_bridge( void );

// Set current position to the origin location
void 	x_set_origin( void );

// Return to origin position
void 	x_goto_origin( void );

// Loop until motor command finishes execution
//
// IMPORTANT - this function must be executed after a move command!
void 	x_wait( void );

// Choose the speed at which the motor will run
//
// RECOMENDATION - 0 to 4 for cutting speed, 10 for fast movement when not cutting
void 	x_set_max_speed( uint16_t speed );

uint16_t x_get_max_speed( void );



#endif /* L6472_H_ */
