/*
 * LaserBoard.c
 *
 *  Created on: Mar 16, 2016
 *      Author: Isaac
 */
#include "hw_types.h"
#include "LaserBoard.h"
#include "gpio.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "pin.h"
#include "prcm.h"
#include "rom_map.h"

/****************************************************************************
 * Parameters for laser control GPIO pin
 ****************************************************************************/
// Dev board
#define LASER_PCLK		PRCM_GPIOA2
#define	LASER_PIN		PIN_15
#define LASER_GPIOBASE	GPIOA2_BASE
#define	LASER_GPIOPIN	GPIO_PIN_6

// Actual board
/*#define LASER_PCLK	PRCM_GPIOA0
#define	LASER_PIN		PIN_59
#define LASER_GPIOBASE	GPIOA0_BASE
#define	LASER_GPIOPIN	GPIO_PIN_4*/

void laser_init( void ) {

    // Configure LASER_PIN for laser control
    MAP_PRCMPeripheralClkEnable(LASER_PCLK, PRCM_RUN_MODE_CLK);

    // Configure laser for output
    MAP_PinTypeGPIO(LASER_PIN, PIN_MODE_0, false);
    MAP_GPIODirModeSet(LASER_GPIOBASE, LASER_GPIOPIN, GPIO_DIR_MODE_OUT);

    laser_off();

}

void laser_off( void ) {
	GPIOPinWrite(LASER_GPIOBASE, LASER_GPIOPIN, LASER_GPIOPIN);
}

void laser_on( void ) {
	GPIOPinWrite(LASER_GPIOBASE, LASER_GPIOPIN, 0);
}
