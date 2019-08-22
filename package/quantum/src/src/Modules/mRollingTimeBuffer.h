/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mRollingTimeBuffer.h
Author				: Cestele Yves
Date				: 5 juil. 2017
Description			:

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MROLLINGTIMEBUFFER_H_
#define SRC_MODULES_MROLLINGTIMEBUFFER_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "FPGA_Registers.h"
#include "TimerDef.h"
#include "mRs232.h"

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mRollingTimeBuffer_AddRTPeriodToBuffer
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Add a periodic RT to buffer
    //
    // Parameters	: u8 	-> RT number
    //			  u64	-> Ptr on the period
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRollingTimeBuffer_AddRTPeriodToBuffer(u8 aRunningTimeNr, u64 aRtPeriod);

    //--------------------------------------------------------------
    // Name		: mRollingTimeBuffer_FormatSendRtPeriodBuffer
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Send the RT buffers
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRollingTimeBuffer_FormatSendRtPeriodBuffer(void);



#endif /* SRC_MODULES_MROLLINGTIMEBUFFER_H_ */
