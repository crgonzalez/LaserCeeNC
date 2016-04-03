/*********************************************
 *
 * fileparse.c
 *
 *
 * Created on 4/1/2016  9:37 PM
 *
 * Author: Zachary L. Mitchell
 *
 *
 *Source handles the parsing operations
 *for the GCodeParseTask in the main file
 *
 *********************************************/
// Standard includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "interrupt.h"
#include "utils.h"
#include "pin.h"
#include "uart.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "hw_common_reg.h"
#include "spi.h"

//Free_rtos/ti-rtos includes
#include "osi.h"

// common interface includes
#include "gpio_if.h"
#include "uart_if.h"
#include "common.h"

//Laser/Motor control includes
#include "L6472.h"
#include "LaserBoard.h"
#include "gcode.h"

#include "pinmux.h"

#include "fileparse.h"

/*********************************************************************
**********************************************************************

						FileParse Functions

**********************************************************************
*********************************************************************/


int fileparse(char* val)
{
	int opt = 0;
	char code[50];
	char err[1];

	sscanf(val, "%50[^'Z']%c", code, err);

	if (err[0] == 'Z')
		return 1;

	sscanf(val, "%c", code);

	if (code[0] == 'G')
		opt = 1;
	else if (code[0] == 'M')
		opt = 2;

	switch (opt){
	case 1:
		gcommand(val+1);
		break;
	case 2:
		mcommand(val+1);
		break;
	default:
		return 1;
	}

	return 0;
}


/********************************************************************

					G Command Handler

********************************************************************/


void gcommand(char* instr)
{
	int g_num;
	char param1[1];

	float f_val;
	float x_vals;
	float y_vals;
	float p_val;
	float i_vals;
	float j_vals;

	sscanf(instr, "%d %c", &g_num, param1);



	switch(g_num){
	case 0:
		while (instr[0] != 'F' && instr[0] != 'X')
			instr++;
		if (param1[0] == 'F')
		{
			sscanf(instr, "F%f", &f_val);
			//G0_f(f_val);
			UART_PRINT("G0 F%f\n", f_val);
		}
		else
		{
			sscanf(instr, "X%f Y%f", &x_vals, &y_vals);
			//G0_xy(x_vals, y_vals);
			UART_PRINT("G0 X%f Y%f\n", x_vals, y_vals);
		}
		break;
	case 1:
		while (instr[0] != 'F' && instr[0] != 'X')
			instr++;
		if (param1[0] == 'F')
		{
			sscanf(instr, "F%f", &f_val);
			//G1_f(f_val);
			UART_PRINT("G1 F%f\n", f_val);
		}
		else
		{
			sscanf(instr, "X%f Y%f", &x_vals, &y_vals);
			//G1_xy(x_vals, y_vals);
			UART_PRINT("G1 X%f Y%f\n", x_vals, y_vals);
		}
		break;
	case 2:
		while (instr[0] != 'X')
			instr++;
		sscanf(instr, "X%f Y%f I%f J%f", &x_vals, &y_vals, &i_vals, &j_vals);
		//G2_xyij(x_vals, y_vals, i_vals, j_vals);
		UART_PRINT("G2 X%f Y%f I%f J%f\n", x_vals, y_vals, i_vals, j_vals);
		break;
	case 4:
		while (instr[0] != 'P')
			instr++;
		sscanf(instr, "P%f", &p_val);
		//G4_p(p_vals);
		UART_PRINT("G4 P%f\n", p_val);
		break;
	case 21:
		//G21();
		UART_PRINT("G21\n");
		break;
	case 90:
		//G90();
		UART_PRINT("G90\n");
		break;
	default:
		break;
	}
}


/********************************************************************

					M Command Handler

********************************************************************/


void mcommand(char* instr)
{
	int m_num;
	char s_code;
	int s_val;

	sscanf(instr, "%d %c %d", &m_num, &s_code, &s_val);

	switch(m_num){
	case 3:
		//M3_s(s_val);
		UART_PRINT("M3 S%d\n", s_val);
		break;
	case 5:
		//M5_s(s_val);
		UART_PRINT("M5 S%d\n", s_val);
		break;
	case 18:
		//M18();
		UART_PRINT("M18\n");
		break;
	default:
		break;
	}
}
















