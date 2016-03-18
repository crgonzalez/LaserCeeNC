/*
 * L6472.c
 *
 *  Created on: Mar 12, 2016
 *      Author: Isaac
 */

#include <string.h>

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

// Y_Busy pin definitions
#define Y_BUSY_PCLK		PRCM_GPIOA3
#define	Y_BUSY_PIN		PIN_18
#define Y_BUSY_GPIOBASE	GPIOA3_BASE
#define	Y_BUSY_GPIOPIN	GPIO_PIN_4

//*****************************************************************************
//                 GLOBAL VARIABLES
//*****************************************************************************
static unsigned char g_ucTxBuff[TR_BUFF_SIZE];
static unsigned char g_ucRxBuff[TR_BUFF_SIZE];

static uint8_t send_buffer[5];
static uint8_t return_buffer[5];



//*****************************************************************************
//                 Private function prototypes
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

    MAP_PRCMPeripheralClkEnable(Y_BUSY_PCLK, PRCM_RUN_MODE_CLK);

    //
    // Configure Y_BUSY for input
    //
    // I think GPIO22(A2-6) is pin 15, mode 0 for gpio, and false to make it not open drain
    MAP_PinTypeGPIO(Y_BUSY_PIN, PIN_MODE_0, false);
    MAP_GPIODirModeSet(Y_BUSY_GPIOBASE, Y_BUSY_GPIOPIN, GPIO_DIR_MODE_IN);

}

uint8_t y_busy( void ) {
	// Active low means its executing a command (probably Move())
	if( GPIOPinRead( GPIOA3_BASE, GPIO_PIN_4 ) ) {
		return 0;
	// Inactive high means its done
	} else {
		return 1;
	}
}

void y_wait( void ) {
	while( y_busy() );
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

uint8_t x_byte_txrx( uint8_t xByte ) {

	uint16_t received_word;

	received_word = L6472_spi_txrx( xByte, 0 );

	return (uint8_t)( (received_word >> 8) & 0x00ff );
}

uint8_t y_byte_txrx( uint8_t yByte ) {

	uint16_t received_word;

	received_word = L6472_spi_txrx( 0, yByte );

	return (uint8_t)(received_word & 0x00ff);
}

void x_set_max_speed( uint16_t speed ) {
	// Command
	x_byte_txrx( 0x07 );
	// MSByte
	x_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	x_byte_txrx( (uint8_t)(speed & 0xff) );
}

int x_get_max_speed( void ) {
	int speed = 0;
	// Command
	x_byte_txrx( 0x27 );
	// nops while reading
	speed = (int)( x_byte_txrx( 0x00 ) );
	speed <<= 8;
	speed += (int)( x_byte_txrx( 0x00 ) );

	return speed;
}

void y_set_max_speed( uint16_t speed ) {
	// Command
	y_byte_txrx( 0x07 );
	// MSByte
	y_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(speed & 0xff) );
}

int y_get_max_speed( void ) {
	int speed = 0;
	// Command
	y_byte_txrx( 0x27 );
	// nops while reading
	speed = (int)( y_byte_txrx( 0x00 ) );
	speed <<= 8;
	speed += (int)( y_byte_txrx( 0x00 ) );

	return speed;
}

void y_set_speed( uint32_t speed ) {
	// Truncate speed to 20 bits
	speed &= 0x000fffff;
	// Command
	y_byte_txrx( 0x04 );
	// MSByte
	y_byte_txrx( (uint8_t)( (speed >> 16) & 0xff) );
	// Middle Byte
	y_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(speed & 0xff) );
}

int y_get_speed( void ) {
	int speed = 0;
	// Command
	y_byte_txrx( 0x24 );
	// nops while reading
	speed = (int)( y_byte_txrx( 0x00 ) );
	speed <<= 8;
	speed += (int)( y_byte_txrx( 0x00 ) );
	speed <<= 8;
	speed += (int)( y_byte_txrx( 0x00 ) );

	return speed;
}

void y_run( direction_t dir, uint32_t speed ) {
	//Choose directional command
	if( dir == POSITIVE ) {
		y_byte_txrx( 0x51 );
	} else {
		y_byte_txrx( 0x50 );
	}

	// Truncate speed to 20 bits
	speed &= 0x000fffff;

	// MSByte
	y_byte_txrx( (uint8_t)( (speed >> 16) & 0xff) );
	// Middle Byte
	y_byte_txrx( (uint8_t)( (speed >> 8) & 0xff) );
	// LSByte
	y_byte_txrx( (uint8_t)(speed & 0xff) );
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


