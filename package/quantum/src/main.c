/*---------------------------------------------------------------------------
 -----------------------------------------------------------------------------
 Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
 All rights reserved.
 -----------------------------------------------------------------------------
 File name 			: main.c
 Author				: Cestele Yves
 Date				: 23 juin 2017
 Description			: Main programme

 Modifications			: -

 ---------------------------------------------------------------------------*/

//--------------------------------------------------------------
// 			INCLUDES
//--------------------------------------------------------------
#include <stdio.h>
#include "utils.h"
#include "FPGA_Registers.h"
#include "gEvent.h"
#include "gHostCmd.h"
#include "gPrinter.h"
#include "unistd.h"
#include "event.h"

//--------------------------------------------------------------
// 			FUNCTIONS
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name			: main
    // Author			: Cestele Yves
    // Date			: 23 juin 2017
    // Descritpion		:
    //
    // Return			: int
    //
    // Modification		:
    //--------------------------------------------------------------
    int main()
    {
	// General configuration:
	gTimerConfig.FirmwareMainVer = 0x01;
	gTimerConfig.FirmwareSubVer = 0x18;

	// Cache Initialisation
	FPGA_Registers_Open();

	volatile u32 *test = kFPGA_Version;
	u32 value = *test;
	gTimerConfig.FpgaMainVer=(u8)(((value)&0x000000ff));        // Firmware of the FPGA
	gTimerConfig.FpgaSubVer=(u8)(((value)&0x0000ff00)>>8);

	// Setups:
	event_init();
	gHostCmd_Setup();
	gEvent_Setup();
	gPrinter_setup();
	gGps_Setup();
	printf("\n Start QUantum version 18072019\n");

	// Infinite loop:
	for (;;)
	{
//	    gEvent_Execute();
		sem_wait(QUANTUM_EVENT_PC_SPORT_MSG_AVAILABLE);
	    gHostCmd_Execute();
	    //gPrinter_Execute();	// FIXME change to poll always...
//	    gGps_Execute();
	}

//	gHostCmd_WaitEndOfTask();

	return 0;
    }




