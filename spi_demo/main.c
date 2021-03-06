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
#include "gcode.h"


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

    laser_off();

    while(1)
    {
    	Report( "\r\nPress key to turn run: " );
    	ulUserData = MAP_UARTCharGet(UARTA0_BASE);


    	//M05 S0
    	M5_s( 0 );
    	//G90
    	G90();
    	//G21
    	G21();
    	//G1 F3000
    	G1_f( 3000 );
    	//G1  X64.8809 Y42.5
    	G1_xy( 64.8809, 42.5 );
    	//G4 P0
    	G4_p( 0 );
    	//M03 S256
    	M3_s( 256 );
    	//G4 P0
    	G4_p( 0 );
    	//G1 F100.000000
    	G1_f( 100 );
    	//G2 X58.3257 Y26.6743 I-22.3809 J0.
    	G2_xyij( 58.3257, 26.6743, -22.3809, 0 );
    	//G2 X42.5 Y20.1191 I-15.8257 J15.8257
    	G2_xyij( 42.5, 20.1191, -15.8257, 15.8257 );
    	//G2 X26.6743 Y26.6743 I0. J22.3809
    	G2_xyij( 26.6743, 26.2743, 0, 22.3809 );
    	//G2 X20.1191 Y42.5 I15.8257 J15.8257
    	G2_xyij( 20.1191, 42.5, 15.8257, 15.8257 );
    	//G2 X21.8228 Y51.0648 I22.3809 J0.
    	G2_xyij( 21.8228, 51.0648, 22.3809, 0 );
    	//G2 X26.6743 Y58.3257 I20.6772 J-8.5648
    	G2_xyij( 26.6743, 58.3257, 20.6772, -8.5648 );
    	//G2 X33.9352 Y63.1772 I15.8257 J-15.8257
    	G2_xyij( 33.9352, 63.1772, 15.8257, -15.8257 );
    	//G2 X42.5 Y64.8809 I8.5648 J-20.6772
    	G2_xyij( 42.5, 64.8809, 8.5648, -20.6772 );
    	//G2 X51.0648 Y63.1772 I-0. J-22.3809
    	G2_xyij( 51.0648, 63.1772, 0, -22.3809 );
    	//G2 X58.3257 Y58.3257 I-8.5648 J-20.6772
    	G2_xyij( 58.3257, 58.3257, -8.5648, -20.6772 );
    	//G2 X63.1772 Y51.0648 I-15.8257 J-15.8257
    	G2_xyij( 63.1772, 51.0648, -15.8257, -15.8257 );
    	//G2 X64.8809 Y42.5 I-20.6772 J-8.5648
    	G2_xyij( 64.8809, 42.5, -20.6772, -8.5648 );
    	//G1  X64.8809 Y42.5
    	G1_xy( 64.8809, 42.5 );
    	//G4 P0
    	G4_p( 0 );
    	//M05 S0
    	M5_s( 0 );
    	//G1 F3000
    	G1_f( 3000 );
    	//G1 X0 Y0
    	G1_xy( 0, 0 );
    	//M18
    	M18();



    }

}

