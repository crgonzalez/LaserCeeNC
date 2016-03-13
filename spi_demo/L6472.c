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
void L6472_spi_txrx( uint8_t xByte, uint8_t yByte );


void L6472_init( void ) {

}

uint8_t x_byte_txrx( uint8_t xByte ) {

	L6472_spi_txrx( xByte, 0 );

	return g_ucRxBuff[1];

}

uint8_t y_byte_txrx( uint8_t yByte ) {

	L6472_spi_txrx( 0, yByte );

	return g_ucRxBuff[0];

}

uint8_t *x_string_txrx( uint8_t *xString, int length ) {
	int i;

	for( i = 0; i < length; i++ ) {
		return_buffer[i] = x_byte_txrx( *xString );
		xString++;
	}

	return return_buffer;
}


uint8_t *y_string_txrx( uint8_t *yString, int length ) {
	int i;

	for( i = 0; i < length; i++ ) {
		return_buffer[i] = y_byte_txrx( *yString );
		yString++;
	}

	return return_buffer;
}

void x_set_max_speed( uint16_t speed ) {
	// Command
	send_buffer[0] = '\x07';
	// MSByte
	send_buffer[1] = (speed >> 8) & 0x00ff;
	// LSByte
	send_buffer[2] = speed & 0x00ff;

	x_string_txrx( send_buffer, 3 );
}

int x_get_max_speed( void ) {
	int speed = 0;
	// Command
	send_buffer[0] = '\x27';
	// padding
	send_buffer[1] = '\x00';
	send_buffer[2] = '\x00';

	x_string_txrx( send_buffer, 3 );

	//speed = (int)(return_buffer[1]);
	//speed <<= 8;
	//speed += (int)(return_buffer[2]);

	return return_buffer[2];
}

void y_set_max_speed( uint16_t speed ) {
	// Command
	send_buffer[0] = '\x07';
	// MSByte
	send_buffer[1] = (speed >> 8) & 0x00ff;
	// LSByte
	send_buffer[2] = speed & 0x00ff;

	y_string_txrx( send_buffer, 3 );
}

int y_get_max_speed( void ) {
	int speed = 0;
	// Command
	send_buffer[0] = '\x27';
	// padding
	send_buffer[1] = '\x00';
	send_buffer[2] = '\x00';

	y_string_txrx( send_buffer, 3 );

	//speed += return_buffer[1];
	//speed <<= 8;
	//speed += return_buffer[2];

	return return_buffer[2];
}

void L6472_spi_txrx( uint8_t xByte, uint8_t yByte ) {

	g_ucTxBuff[1] = xByte;
	g_ucTxBuff[0] = yByte;

    MAP_SPITransfer(GSPI_BASE,g_ucTxBuff,g_ucRxBuff,2,
                SPI_CS_ENABLE|SPI_CS_DISABLE);

}
