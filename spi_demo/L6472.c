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
#define TR_BUFF_SIZE     100

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

	Report( "\r\na" );
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA2, PRCM_RUN_MODE_CLK);
    Report( "\r\nA" );

    //
    // Configure PIN_01 for GPIOOutput
    //
    // I think GPIO22(A2-6) is pin 15, mode 0 for gpio, and false to make it not open drain
    Report( "\r\nb" );
    MAP_PinTypeGPIO(PIN_15, PIN_MODE_0, false);
    Report( "\r\nB" );
    Report( "\r\nc" );
    MAP_GPIODirModeSet(GPIOA2_BASE, GPIO_PIN_6, GPIO_DIR_MODE_OUT);
    Report( "\r\nC" );

}

uint8_t y_busy( void ) {
	if( GPIOPinRead( GPIOA2_BASE, GPIO_PIN_6 ) ) {
		return 1;
	} else {
		return 0;
	}
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


