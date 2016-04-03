/*
 * L6472.c
 *
 *  Created on: Mar 12, 2016
 *      Author: Isaac
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "L6472.h"

#include "hw_types.h"
#include "hw_memmap.h"
#include "spi.h"
#include "rom_map.h"
#include "gpio.h"
#include "pin.h"
#include "prcm.h"
#include "uart_if.h"

//*****************************************************************************
//                 Definitions
//*****************************************************************************
// SPI Definitions
#define SPI_IF_BIT_RATE  25000
#define TR_BUFF_SIZE     100


// Step Conversion Definitions
#define STEPS_TO_MM		800

/****************************************************************************
 * Parameters for Y_BUSY GPIO pin
 ****************************************************************************/
// Dev board
/*#define Y_BUSY_PCLK		PRCM_GPIOA3
#define	Y_BUSY_PIN		PIN_18
#define Y_BUSY_GPIOBASE	GPIOA3_BASE
#define	Y_BUSY_GPIOPIN	GPIO_PIN_4*/

// Actual board
#define Y_BUSY_PCLK		PRCM_GPIOA0
#define	Y_BUSY_PIN		PIN_61
#define Y_BUSY_GPIOBASE	GPIOA0_BASE
#define	Y_BUSY_GPIOPIN	GPIO_PIN_6

/****************************************************************************
 * Parameters for X_BUSY GPIO pin
 ****************************************************************************/
// Dev board
/*#define X_BUSY_PCLK		PRCM_GPIOA3
#define	X_BUSY_PIN		PIN_17
#define X_BUSY_GPIOBASE	GPIOA3_BASE
#define	X_BUSY_GPIOPIN	GPIO_PIN_0*/

// Actual board
#define X_BUSY_PCLK		PRCM_GPIOA0
#define	X_BUSY_PIN		PIN_60
#define X_BUSY_GPIOBASE	GPIOA0_BASE
#define	X_BUSY_GPIOPIN	GPIO_PIN_5

//*****************************************************************************
//                 GLOBAL VARIABLES
//*****************************************************************************
static unsigned char g_ucTxBuff[TR_BUFF_SIZE];
static unsigned char g_ucRxBuff[TR_BUFF_SIZE];

static float x_pos = 0;
static float y_pos = 0;


//*****************************************************************************
//                 Private function prototypes
//*****************************************************************************
uint16_t get_status( void );
uint16_t L6472_spi_txrx( uint8_t xByte, uint8_t yByte );

void	xy_byte_tx( uint8_t xByte, uint8_t yByte );
void	xy_move( direction_t xdir, uint32_t xsteps, direction_t ydir, uint32_t ysteps );

void	y_set_run_current( uint8_t current );
uint8_t y_byte_txrx( uint8_t yByte );
void 	y_move( direction_t dir, uint32_t steps );
uint8_t y_busy( void );

void	x_set_run_current( uint8_t current );
uint8_t x_byte_txrx( uint8_t xByte );
void 	x_move( direction_t dir, uint32_t steps );
uint8_t x_busy( void );

//*****************************************************************************
//                  General Public Functions
//*****************************************************************************
void L6472_init( void ) {
	// Enable SPI Peripheral Clock
    MAP_PRCMPeripheralClkEnable(PRCM_GSPI, PRCM_RUN_MODE_CLK);

    // Configure PIN_05 for SPI0 GSPI_CLK
    MAP_PinTypeSPI(PIN_05, PIN_MODE_7);

    // Configure PIN_06 for SPI0 GSPI_MISO
    MAP_PinTypeSPI(PIN_06, PIN_MODE_7);

    // Configure PIN_07 for SPI0 GSPI_MOSI
    MAP_PinTypeSPI(PIN_07, PIN_MODE_7);

    // Configure PIN_08 for SPI0 GSPI_CS
    MAP_PinTypeSPI(PIN_08, PIN_MODE_7);

    // Enable the SPI module clock
    MAP_PRCMPeripheralClkEnable(PRCM_GSPI,PRCM_RUN_MODE_CLK);

    // Reset SPI
    MAP_SPIReset(GSPI_BASE);

    // Configure SPI interface
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_3,
					 (SPI_SW_CTRL_CS |//(SPI_HW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVELOW |
					 SPI_WL_8));

    // Enable SPI for communication
    MAP_SPIEnable(GSPI_BASE);

    // Configure Y_BUSY for input
    MAP_PRCMPeripheralClkEnable(Y_BUSY_PCLK, PRCM_RUN_MODE_CLK);
    MAP_PinTypeGPIO(Y_BUSY_PIN, PIN_MODE_0, false);
    MAP_GPIODirModeSet(Y_BUSY_GPIOBASE, Y_BUSY_GPIOPIN, GPIO_DIR_MODE_IN);

    // Configure X_BUSY for input
    MAP_PRCMPeripheralClkEnable(X_BUSY_PCLK, PRCM_RUN_MODE_CLK);
    MAP_PinTypeGPIO(X_BUSY_PIN, PIN_MODE_0, false);
    MAP_GPIODirModeSet(X_BUSY_GPIOBASE, X_BUSY_GPIOPIN, GPIO_DIR_MODE_IN);

    // Reset the device
    y_reset();
    x_reset();

    // Configure motor current parameter
    y_set_run_current( 15 );
    x_set_run_current( 15 );

    // Force microstepping
    xy_set_fs_speed( 0x3ff, 0x3ff );

}


//*****************************************************************************
//                  XY Public Functions
//*****************************************************************************
void 	xy_wait( void ) {
	uint8_t xBool = 1;
	uint8_t yBool = 1;
	while( 1 ) {
		if( xBool == 0 && yBool == 0 ) {
			return;
		}

		if( xBool == 1 && x_busy() == 0 ) {
			xBool = 0;
			x_release_bridge();
		}

		if( yBool == 1 && y_busy() == 0 ) {
			yBool = 0;
			y_release_bridge();
		}
	}
}


void	xy_move_mm( float xMMs, float yMMs ) {
	// Determine Distance
	uint32_t xsteps = (uint32_t)fabs( xMMs*STEPS_TO_MM );
	uint32_t ysteps = (uint32_t)fabs( yMMs*STEPS_TO_MM );

	if( xMMs >= 0 ) {
		if( yMMs >= 0 ) {
			xy_move( POSITIVE, xsteps, POSITIVE, ysteps );
		} else if( yMMs < 0 ) {
			xy_move( POSITIVE, xsteps, NEGATIVE, ysteps );
		}
	} else if( xMMs < 0 ) {
		if( yMMs >= 0 ) {
			xy_move( NEGATIVE, xsteps, POSITIVE, ysteps );
		} else if( yMMs < 0 ) {
			xy_move( NEGATIVE, xsteps, NEGATIVE, ysteps );
		}
	}

	// Move x_pos and y_pos
	x_pos += xMMs;
	y_pos += yMMs;
}


void	move_coord_direct( float x_dest, float y_dest ) {
	float x_delta = x_dest - x_pos;
	float y_delta = y_dest - y_pos;

	xy_move_mm( x_delta, y_delta );
	xy_wait();
}


void	move_coord( float x_dest, float y_dest ) {
	float x_delta = x_dest - x_pos;
	float y_delta = y_dest - y_pos;

	// Absolute value of deltas
	const float x_delta_const = fabs(x_delta);
	const float y_delta_const = fabs(y_delta);

	// Declare direction variables
	float x_dir = 1;
	float y_dir = 1;

	// Store x direction of movement
	if( x_delta >= 0 ) {
		x_dir = 1;	// Positive
	} else {
		x_dir = -1;	// Negative
	}

	// Store y direction of movement
	if( y_delta >= 0 ) {
		y_dir = 1;	// Positive
	} else {
		y_dir = -1;	// Negative
	}

	// Remove sign from deltas
	x_delta = fabs(x_delta);
	y_delta = fabs(y_delta);

	// Loop until not movement is necessary
	Report( "\r\nHere! x_delta: %f  y_delta: %f", x_delta, y_delta );
	while( x_delta != 0 || y_delta != 0 ) {
		Report( "\r\nHere Again!" );
		Report( "\r\nx_pos: %f  y_pos: %f", x_pos, y_pos );
		if( x_delta/x_delta_const >= y_delta/y_delta_const ) {
			if( x_delta >= 0.1 ) {
				x_move_mm( 0.1*x_dir );
				x_wait();
				x_delta -= 0.1;
			} else if( x_delta < 0.1 ) {
				x_move_mm( x_delta*x_dir );

				x_wait();
				x_delta = 0;
			}
		} else {
			if( y_delta >= 0.1 ) {
				y_move_mm( 0.1*y_dir );
				y_wait();
				y_delta -= 0.1;
			} else if( y_delta < 0.1 ) {
				y_move_mm( y_delta*y_dir );
				y_wait();
				y_delta = 0;
			}
		}
	}
}

float	x_get_position( void ) {
	return x_pos;
}

float 	y_get_position( void ) {
	return y_pos;
}


//*****************************************************************************
//                  Y Public Functions
//*****************************************************************************
void y_reset( void ) {
	y_byte_txrx( 0xc0 );
}


void 	y_move_mm( float MMs ) {
	// Determine Distance
	uint32_t steps = (uint32_t)fabs( MMs*STEPS_TO_MM );

	if( MMs >= 0 ) {
		y_move( POSITIVE, steps );
	} else if( MMs < 0 ) {
		y_move( NEGATIVE, steps );
	}

	// Move y_pos
	y_pos += MMs;
}


void	y_release_bridge( void ) {
	// Put motor bridges into high impedance
	y_byte_txrx( 0xa0 );
}


void y_set_origin( void ) {
	int origin = 0;
	// Command (Set param ABS_POS)
	y_byte_txrx( 0x01 );
	// MSByte
	y_byte_txrx( (uint8_t)( (origin >> 16) & 0xff) );
	// Middle Byte
	y_byte_txrx( (uint8_t)( (origin >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(origin & 0xff) );

	// Set y_pos to origin
	y_pos = 0;
}


void y_goto_origin( void ) {
	// Command (Go Home to ABS_POS = 0)
	y_byte_txrx( 0x70 );

	// Set y_pos to origin
	y_pos = 0;
}


void y_wait( void ) {
	while( y_busy() );
	y_release_bridge();
}


void y_set_max_speed( uint16_t speed ) {
	// Command
	y_byte_txrx( 0x07 );
	// MSByte
	y_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(speed & 0xff) );
}

uint16_t y_get_max_speed( void ) {
	uint16_t max_speed = 0;
	// Command
	y_byte_txrx( 0x27 );
	// NOP
	max_speed += (uint16_t)(y_byte_txrx( 0x00 ));
	max_speed <<= 8;
	// NOP
	max_speed += (uint16_t)(y_byte_txrx( 0x00 ));
	return max_speed;
}


//*****************************************************************************
//                  X Public Functions
//*****************************************************************************
void x_reset( void ) {
	x_byte_txrx( 0xc0 );
}


void 	x_move_mm( float MMs ) {
	// Determine Distance
	uint32_t steps = (uint32_t)fabs( MMs*STEPS_TO_MM );

	if( MMs >= 0 ) {
		x_move( POSITIVE, steps );
	} else if( MMs < 0 ) {
		x_move( NEGATIVE, steps );
	}

	// Move x_pos
	x_pos += MMs;
}


void	x_release_bridge( void ) {
	// Put motor bridges into high impedance
	x_byte_txrx( 0xa0 );
}


void x_set_origin( void ) {
	int origin = 0;
	// Command (Set param ABS_POS)
	x_byte_txrx( 0x01 );
	// MSByte
	x_byte_txrx( (uint8_t)( (origin >> 16) & 0xff) );
	// Middle Byte
	x_byte_txrx( (uint8_t)( (origin >> 8) & 0xff) );
	// LSByte
	x_byte_txrx( (uint8_t)(origin & 0xff) );

	// Set x_pos to origin
	x_pos = 0;
}


void x_goto_origin( void ) {
	// Command (Go Home to ABS_POS = 0)
	x_byte_txrx( 0x70 );

	// Set x_pos to origin
	x_pos = 0;
}


void x_wait( void ) {
	while( x_busy() );
	x_release_bridge();
}

void x_set_max_speed( uint16_t speed ) {
	// Command
	x_byte_txrx( 0x07 );
	// MSByte
	x_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	x_byte_txrx( (uint8_t)(speed & 0xff) );
}

uint16_t x_get_max_speed( void ) {
	uint16_t max_speed = 0;
	// Command
	x_byte_txrx( 0x27 );
	// NOP
	max_speed += (uint16_t)(x_byte_txrx( 0x00 ));
	max_speed <<= 8;
	// NOP
	max_speed += (uint16_t)(x_byte_txrx( 0x00 ));
	return max_speed;
}



//*****************************************************************************
//                 General Private functions
//*****************************************************************************
uint16_t get_status( void ) {
	uint16_t status;
	// Command
	x_byte_txrx( 0xd0 );
	// nops while reading
	status = (uint16_t)( x_byte_txrx( 0x00 ) );
	status <<= 8;
	status += (uint16_t)( x_byte_txrx( 0x00 ) );

	return status;
}


uint16_t L6472_spi_txrx( uint8_t xByte, uint8_t yByte ) {

	uint16_t return_word = 0;

	g_ucTxBuff[1] = xByte;
	g_ucTxBuff[0] = yByte;

    MAP_SPITransfer(GSPI_BASE,g_ucTxBuff,g_ucRxBuff,2,
                SPI_CS_ENABLE|SPI_CS_DISABLE);

    return_word = (uint16_t)g_ucRxBuff[1];
    return_word <<= 8;
    return_word += (uint16_t)g_ucRxBuff[0];

    return return_word;
}


//*****************************************************************************
//                 XY Private functions
//*****************************************************************************
void	xy_byte_tx( uint8_t xByte, uint8_t yByte ) {
	// Send x and y bytes
	L6472_spi_txrx( xByte, yByte );
}


void	xy_move( direction_t xdir, uint32_t xsteps, direction_t ydir, uint32_t ysteps ) {
	// Choose direction
	if( xdir == POSITIVE ) {
		if( ydir == POSITIVE ) {
			xy_byte_tx( 0x41, 0x41 );
		} else {
			xy_byte_tx( 0x41, 0x40 );
		}
	} else {
		if( ydir == POSITIVE ) {
			xy_byte_tx( 0x40, 0x41 );
		} else {
			xy_byte_tx( 0x40, 0x40 );
		}
	}

	// Truncate x and y steps to 20 bits
	xsteps &= 0x000fffff;
	ysteps &= 0x000fffff;

	// MSByte
	xy_byte_tx( (uint8_t)( (xsteps >> 16) & 0xff), (uint8_t)( (ysteps >> 16) & 0xff) );
	// Middle Byte
	xy_byte_tx( (uint8_t)( (xsteps >> 8) & 0xff), (uint8_t)( (ysteps >> 8) & 0xff) );
	// LSByte
	xy_byte_tx( (uint8_t)(xsteps & 0xff), (uint8_t)(ysteps & 0xff) );
}


//*****************************************************************************
//                 Y Private functions
//*****************************************************************************
void	y_set_run_current( uint8_t current ) {
	// Command
	y_byte_txrx( 0x0A );
	// LSByte
	y_byte_txrx( current );
}


uint8_t y_byte_txrx( uint8_t yByte ) {

	uint16_t received_word;

	received_word = L6472_spi_txrx( 0, yByte );

	return (uint8_t)(received_word & 0x00ff);
}


void y_move( direction_t dir, uint32_t steps ) {
	//Choose directional command
	if( dir == POSITIVE ) {
		y_byte_txrx( 0x41 );
	} else {
		y_byte_txrx( 0x40 );
	}

	// Truncate steps to 20 bits
	steps &= 0x000fffff;

	// MSByte
	y_byte_txrx( (uint8_t)( (steps >> 16) & 0xff) );
	// Middle Byte
	y_byte_txrx( (uint8_t)( (steps >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(steps & 0xff) );
}


uint8_t y_busy( void ) {
	// Active low means its executing a command (probably Move())
	if( GPIOPinRead( Y_BUSY_GPIOBASE, Y_BUSY_GPIOPIN ) ) {
		return 0;
	// Inactive high means its done
	} else {
		return 1;
	}
}


//*****************************************************************************
//                 X Private functions
//*****************************************************************************
void	x_set_run_current( uint8_t current ) {
	// Command
	x_byte_txrx( 0x0A );
	// LSByte
	x_byte_txrx( current );
}


uint8_t x_byte_txrx( uint8_t xByte ) {

	uint16_t received_word;

	received_word = L6472_spi_txrx( xByte, 0 );

	return (uint8_t)( (received_word >> 8) & 0x00ff );
}


void x_move( direction_t dir, uint32_t steps ) {
	//Choose directional command
	if( dir == POSITIVE ) {
		x_byte_txrx( 0x41 );
	} else {
		x_byte_txrx( 0x40 );
	}

	// Truncate steps to 20 bits
	steps &= 0x000fffff;

	// MSByte
	x_byte_txrx( (uint8_t)( (steps >> 16) & 0xff) );
	// Middle Byte
	x_byte_txrx( (uint8_t)( (steps >> 8) & 0xff) );
	// LSByte
	x_byte_txrx( (uint8_t)(steps & 0xff) );
}


uint8_t x_busy( void ) {
	// Active low means its executing a command (probably Move())
	if( GPIOPinRead( X_BUSY_GPIOBASE, X_BUSY_GPIOPIN ) ) {
		return 0;
	// Inactive high means its done
	} else {
		return 1;
	}
}


/**********************************************************************
 * X and Y Register Setting Functions
 **********************************************************************/
void xy_set_fs_speed( uint16_t xfsspeed, uint16_t yfsspeed ) {
	// strip off extra bits (more than 10 bits)
	xfsspeed &= 0x03ff;
	yfsspeed &= 0x03ff;

	// Command
	xy_byte_tx( 0x15, 0x15 );
	// MSByte
	xy_byte_tx( (uint8_t)( (xfsspeed >> 8) & 0xff), (uint8_t)( (yfsspeed >> 8) & 0xff) );
	// LSByte
	xy_byte_tx( (uint8_t)(xfsspeed & 0xff), (uint8_t)(yfsspeed & 0xff) );
}


void xy_set_accel_speed( uint16_t xaccel, uint16_t yaccel ) {
	// strip off extra bits (more than 12 bits)
	xaccel &= 0x0fff;
	yaccel &= 0x0fff;

	// Command
	xy_byte_tx( 0x05, 0x05 );
	// MSByte
	xy_byte_tx( (uint8_t)( (xaccel >> 8) & 0xff), (uint8_t)( (yaccel >> 8) & 0xff) );
	// LSByte
	xy_byte_tx( (uint8_t)(xaccel & 0xff), (uint8_t)(yaccel & 0xff) );
}


void xy_set_decel_speed( uint16_t xdecel, uint16_t ydecel ) {
	// strip off extra bits (more than 12 bits)
	xdecel &= 0x0fff;
	ydecel &= 0x0fff;

	// Command
	xy_byte_tx( 0x06, 0x06 );
	// MSByte
	xy_byte_tx( (uint8_t)( (xdecel >> 8) & 0xff), (uint8_t)( (ydecel >> 8) & 0xff) );
	// LSByte
	xy_byte_tx( (uint8_t)(xdecel & 0xff), (uint8_t)(ydecel & 0xff) );
}


/**********************************************************************
 * X and Y Register Reading Functions
 **********************************************************************/
void	xy_get_accel_speed( void ) {
	xy_byte_tx( 0x25, 0x25 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_decel_speed( void ) {
	xy_byte_tx( 0x26, 0x26 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_max_speed( void ) {
	xy_byte_tx( 0x27, 0x27 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_min_speed( void ) {
	xy_byte_tx( 0x28, 0x28 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_fullstep_speed( void ) {
	xy_byte_tx( 0x35, 0x35 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_const_cur( void ) {
	xy_byte_tx( 0x2A, 0x2A );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_accel_cur( void ) {
	xy_byte_tx( 0x2B, 0x2B);
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_decel_cur( void ) {
	xy_byte_tx( 0x2C, 0x2C );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_status( void ) {
	xy_byte_tx( 0x39, 0x39 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

void	xy_get_config( void ) {
	xy_byte_tx( 0x38, 0x38 );
	xy_byte_tx( 0x00, 0x00 );
	xy_byte_tx( 0x00, 0x00 );
}

