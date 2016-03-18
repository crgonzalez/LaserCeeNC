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

void L6472_init( void );

uint16_t get_status( void );
uint16_t L6472_spi_txrx( uint8_t xByte, uint8_t yByte );


void 	y_move( direction_t dir, uint32_t steps );
void 	y_wait( void );
void 	y_set_origin( void );
void 	y_goto_origin( void );

uint8_t y_byte_txrx( uint8_t yByte );
uint8_t y_busy( void );
void 	y_set_max_speed( uint16_t speed );
int 	y_get_max_speed( void );
void 	y_set_speed( uint32_t speed );
int 	y_get_speed( void );
void 	y_run( direction_t dir, uint32_t speed );


uint8_t x_byte_txrx( uint8_t xByte );

void x_set_max_speed( uint16_t speed );
int x_get_max_speed( void );

#endif /* L6472_H_ */
