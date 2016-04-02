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

void	xy_move_mm( float xMMs, float yMMs );

void	move_coord_direct( float x_dest, float y_dest );

void	move_coord( float x_dest, float y_dest );

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



/**********************************************************************
 * X and Y Register Setting Functions
 **********************************************************************/
void xy_set_fs_speed( uint16_t xfsspeed, uint16_t yfsspeed );
void xy_set_accel_speed( uint16_t xaccel, uint16_t yaccel );
void xy_set_decel_speed( uint16_t xdecel, uint16_t ydecel );

/**********************************************************************
 * X and Y Register Reading Functions
 **********************************************************************/
void	xy_get_accel_speed( void );

void	xy_get_decel_speed( void );

void	xy_get_max_speed( void );

void	xy_get_min_speed( void );

void	xy_get_fullstep_speed( void );

void	xy_get_const_cur( void );

void	xy_get_accel_cur( void );

void	xy_get_decel_cur( void );

void	xy_get_status( void );

void	xy_get_config( void );

/*uint16_t x_get_accel_speed( void );
uint16_t y_get_accel_speed( void );

uint16_t x_get_decel_speed( void );
uint16_t y_get_decel_speed( void );

uint16_t x_get_max_speed( void );
uint16_t y_get_max_speed( void );

uint16_t x_get_min_speed( void );
uint16_t y_get_min_speed( void );

uint16_t x_get_fullstep_speed( void );
uint16_t y_get_fullstep_speed( void );

uint8_t x_get_const_cur( void );
uint8_t y_get_const_cur( void );

uint8_t x_get_accel_cur( void );
uint8_t y_get_accel_cur( void );

uint8_t x_get_decel_cur( void );
uint8_t y_get_decel_cur( void );

uint16_t x_get_status( void );
uint16_t y_get_status( void );

uint16_t x_get_config( void );
uint16_t y_get_config( void );*/


#endif /* L6472_H_ */
