/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mFPGA.h
Author				: Cestele Yves
Date				: 4 juil. 2017
Description			: Module for the FPGA management

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MFPGA_H_
#define SRC_MODULES_MFPGA_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "iFPGA.h"

typedef enum
{
	kArmedInpEvent=1,
	kNonArmedInpEvent=2,
	kSoftInpEvent=3,
	kRTEndPeriod=4,
	kOutEvent=5,
	InpAdEvent=6
}EventNbEnum;

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mFpga_PrepareSynch
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Prepare the FPGA for Sync signal
    //
    // Parameters	: u8* -> Payload with [][][][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mFpga_PrepareSynch(u8 *aPayload);



#endif /* SRC_MODULES_MFPGA_H_ */
