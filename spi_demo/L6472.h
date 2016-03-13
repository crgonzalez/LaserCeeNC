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


void L6472_init( void );

uint8_t x_byte_txrx( uint8_t xByte );
uint8_t y_byte_txrx( uint8_t yByte );

uint8_t *x_string_txrx( uint8_t *xString, int length );
uint8_t *y_string_txrx( uint8_t *yString, int length );

void x_set_max_speed( uint16_t speed );
int x_get_max_speed( void );

void y_set_max_speed( uint16_t speed );
int y_get_max_speed( void );

#endif /* L6472_H_ */
