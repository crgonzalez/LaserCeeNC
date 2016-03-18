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



#define LASER_PCLK		PRCM_GPIOA2
#define	LASER_PIN		PIN_15
#define LASER_GPIOBASE	GPIOA2_BASE
#define	LASER_GPIOPIN	GPIO_PIN_6

void laser_init( void ) {

    MAP_PRCMPeripheralClkEnable(LASER_PCLK, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);

    //
    // Configure laser for output
    //
    // I think GPIO22(A2-6) is pin 15, mode 0 for gpio, and true to make it open drain
    MAP_PinTypeGPIO(LASER_PIN, PIN_MODE_0, false);
    MAP_GPIODirModeSet(LASER_GPIOBASE, LASER_GPIOPIN, GPIO_DIR_MODE_OUT);

    //MAP_PinTypeGPIO(PIN_02, PIN_MODE_0, false);
    //MAP_GPIODirModeSet(GPIOA1_BASE, 0x8, GPIO_DIR_MODE_OUT);

    laser_off();

}

void laser_off( void ) {
	GPIOPinWrite(LASER_GPIOBASE, LASER_GPIOPIN, LASER_GPIOPIN);

	//GPIOPinWrite(GPIOA1_BASE, 0x8, 0x8);
}

void laser_on( void ) {
	GPIOPinWrite(LASER_GPIOBASE, LASER_GPIOPIN, 0);

	//GPIOPinWrite(GPIOA1_BASE, 0x8, 0x0);
}
