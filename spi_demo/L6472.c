/*
 * L6472.c
 *
 *  Created on: Mar 12, 2016
 *      Author: Isaac
 */

#include <string.h>
#include <stdlib.h>

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
#define Y_BUSY_PCLK		PRCM_GPIOA3
#define	Y_BUSY_PIN		PIN_18
#define Y_BUSY_GPIOBASE	GPIOA3_BASE
#define	Y_BUSY_GPIOPIN	GPIO_PIN_4

// Actual board
/*#define Y_BUSY_PCLK		PRCM_GPIOA0
#define	Y_BUSY_PIN		PIN_61
#define Y_BUSY_GPIOBASE	GPIOA0_BASE
#define	Y_BUSY_GPIOPIN	GPIO_PIN_6*/

/****************************************************************************
 * Parameters for X_BUSY GPIO pin
 ****************************************************************************/
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



//*****************************************************************************
//                 Private function prototypes
//*****************************************************************************
uint16_t get_status( void );
uint16_t L6472_spi_txrx( uint8_t xByte, uint8_t yByte );

void	y_set_run_current( uint8_t current );
uint8_t y_byte_txrx( uint8_t yByte );
void 	y_move( direction_t dir, uint32_t steps );
uint8_t y_busy( void );

void	x_set_run_current( uint8_t current );
uint8_t x_byte_txrx( uint8_t xByte );
void 	x_move( direction_t dir, uint32_t steps );
uint8_t x_busy( void );

//*****************************************************************************
//                  Public Functions
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

    // Configure motor current parameter
    y_set_run_current( 10 );

}

void 	xy_wait( void ) {
	while( y_busy() || x_busy() );
}


void y_reset( void ) {
	y_byte_txrx( 0xc0 );
}


void 	y_move_mm( float MMs ) {
	// Determine Distance
	uint32_t steps = (uint32_t)abs( MMs*STEPS_TO_MM );

	if( MMs > 0 ) {
		y_move( POSITIVE, steps );
	} else if( MMs < 0 ) {
		y_move( NEGATIVE, steps );
	}
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
}


void y_goto_origin( void ) {
	// Command (Go Home to ABS_POS = 0)
	y_byte_txrx( 0x70 );
}


void y_wait( void ) {
	while( y_busy() );
}


void y_set_max_speed( uint16_t speed ) {
	// Command
	y_byte_txrx( 0x07 );
	// MSByte
	y_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(speed & 0xff) );
}


void x_reset( void ) {
	x_byte_txrx( 0xc0 );
}


void 	x_move_mm( float MMs ) {
	// Determine Distance
	uint32_t steps = (uint32_t)abs( MMs*STEPS_TO_MM );

	if( MMs > 0 ) {
		x_move( POSITIVE, steps );
	} else if( MMs < 0 ) {
		x_move( NEGATIVE, steps );
	}
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
}


void x_goto_origin( void ) {
	// Command (Go Home to ABS_POS = 0)
	x_byte_txrx( 0x70 );
}


void x_wait( void ) {
	while( x_busy() );
}


void x_set_max_speed( uint16_t speed ) {
	// Command
	x_byte_txrx( 0x07 );
	// MSByte
	x_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	x_byte_txrx( (uint8_t)(speed & 0xff) );
}





//*****************************************************************************
//                 Private functions
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



