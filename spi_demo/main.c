//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Application Name     - SPI Demo
// Application Overview - The demo application focuses on showing the required
//                        initialization sequence to enable the CC3200 SPI
//                        module in full duplex 4-wire master and slave mode(s).
// Application Details  -
// http://processors.wiki.ti.com/index.php/CC32xx_SPI_Demo
// or
// docs\examples\CC32xx_SPI_Demo.pdf
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup SPI_Demo
//! @{
//
//*****************************************************************************

// Standard includes
#include <string.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"

// Common interface includes
#include "uart_if.h"
#include "pinmux.h"

// My includes
#include "L6472.h"
#include "LaserBoard.h"


#define APPLICATION_VERSION     "1.1.1"
//*****************************************************************************
//
// Application Master/Slave mode selector macro
//
// MASTER_MODE = 1 : Application in master mode
// MASTER_MODE = 0 : Application in slave mode
//
//*****************************************************************************
#define MASTER_MODE      1

//#define SPI_IF_BIT_RATE  25000
#define TR_BUFF_SIZE     100

#define MASTER_MSG       "This is CC3200 SPI Master Application\n\r"
#define SLAVE_MSG        "This is CC3200 SPI Slave Application\n\r"

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************


#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************



//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

//*****************************************************************************
//
//! Main function for spi demo application
//!
//! \param none
//!
//! \return None.
//
//*****************************************************************************
void main()
{
    // Initialize Board configurations
    BoardInit();

    // Muxing UART
    PinMuxConfig();

    // Prepare the terminal
    InitTerm();
    ClearTerm();

    // Initialize motor controllers
    L6472_init();

    // Initialize laser control
    laser_init();

    // Read a character from UART terminal
    Report( "\r\nPress a key: " );
    unsigned long ulUserData;



    /*y_set_max_speed( 5 );
    Report( "\r\nmax speed: %d", y_get_max_speed() );

    x_set_max_speed( 5 );
    Report( "\r\nmax speed: %d", x_get_max_speed() );*/

    //Report( "\r\nstatus: %d", y_get_status() );


	/*xy_get_accel_speed();
	xy_get_decel_speed();
	xy_get_max_speed();
	xy_get_min_speed();
	xy_get_fullstep_speed();
    xy_get_const_cur();
    xy_get_accel_cur();
    xy_get_decel_cur();
    xy_get_status();
    xy_get_config();*/

	/*y_set_max_speed( 5 );
	x_set_max_speed( 5 );

	Report( "\r\nX Positive" );
	x_move_mm( 50 );
	x_wait();
	x_release_bridge();

	Report( "\r\nX Negative" );
	x_move_mm( -50 );
	x_wait();
	x_release_bridge();

	Report( "\r\nY Positive" );
	y_move_mm( 50 );
	y_wait();
	y_release_bridge();

	Report( "\r\nY Negative" );
	y_move_mm( -50 );
	y_wait();
	y_release_bridge();*/

    //Report( "\r\n x10 xBA" );
    /*xy_set_accel_speed( 0x10, 0x8A );
    xy_set_decel_speed( 0x10, 0x8A );

    uint16_t i;
    for( i = 1; i <= 12; i++ ) {
		// Start
    	y_set_max_speed( i );
    	x_set_max_speed( i );
		Report( "\r\n%d: ", i );

		if( i % 4 == 1 ) {
			// Move to a different position
			Report( "+x +y " );
			xy_move_mm( 20, 20 );
			xy_wait();
		}

		if( i % 4 == 2 ) {
			// Move to a different position
			Report( "+x -y " );
			xy_move_mm( 20, -20 );
			xy_wait();
		}

		if( i % 4 == 3 ) {
			// Move to a different position
			Report( "-x -y " );
			xy_move_mm( -20, -20 );
			xy_wait();
		}

		if( i % 4 == 0 ) {
			// Move to a different position
			Report( "-x +y " );
			xy_move_mm( -20, 20 );
			xy_wait();
		}
    }*/

    /*y_move_mm( 100 );
    y_wait();
    y_release_bridge();*/

    laser_off();

    x_set_origin();
    y_set_origin();
	y_set_max_speed( 10 );
	x_set_max_speed( 10 );

    while(1)
    {
    	Report( "\r\nPress key to turn run: " );
    	ulUserData = MAP_UARTCharGet(UARTA0_BASE);

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 10, 0 );
    	move_coord( 10, 0 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", -10, 0 );
    	move_coord( -10, 0 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 0, 10 );
    	move_coord( 0, 10 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 0, -10 );
    	move_coord( 0, -10 );
    	laser_off();
    	move_coord( 0, 0 );

    	ulUserData = MAP_UARTCharGet(UARTA0_BASE);

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 10, 5 );
    	move_coord( 10, 5 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 5, 10 );
    	move_coord( 5, 10 );
    	laser_off();
    	move_coord( 0, 0 );

    	ulUserData = MAP_UARTCharGet(UARTA0_BASE);

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", -5, 10 );
    	move_coord( -5, 10 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", -5, 10 );
    	move_coord( -10, 5 );
    	laser_off();
    	move_coord( 0, 0 );

    	ulUserData = MAP_UARTCharGet(UARTA0_BASE);

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", -10, -5 );
    	move_coord( -10, -5 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", -5, -10 );
    	move_coord( -5, -10 );
    	laser_off();
    	move_coord( 0, 0 );

    	ulUserData = MAP_UARTCharGet(UARTA0_BASE);

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 5, -10 );
    	move_coord( 5, -10 );
    	laser_off();
    	move_coord( 0, 0 );

    	laser_on();
    	Report( "\r\nx: %dmm\ty: %dmm", 10, -5 );
    	move_coord( 10, -5 );
    	laser_off();
    	move_coord( 0, 0 );


    }

}

