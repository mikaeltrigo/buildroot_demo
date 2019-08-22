/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mPulseBuffer.h
Author				: Cestele Yves
Date				: 5 juil. 2017
Description			:

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MPULSEBUFFER_H_
#define SRC_MODULES_MPULSEBUFFER_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "TimerDef.h"

#define kPulseBufferSize 20

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mPulseBuffer_Setup
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Pulse Buffer setup
    //
    // Parameters	: void
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mPulseBuffer_Setup(void);

    //--------------------------------------------------------------
    // Name		: mPulseBuffer_Add
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Add a buffer pulse
    //
    // Parameters	: u8 		-> inpu nbr
    //			  u64* 		-> ptr on time
    //			  PulseTypeEnum	-> Pulse Type
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mPulseBuffer_Add(u8 aInputNr, u64* aTime, PulseTypeEnum aPulseType);

    //--------------------------------------------------------------
    // Name		: mPulseBuffer_Get
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Get a pulse
    //
    // Parameters	: PulseBufferStruct* -> ptr on pulse
    //
    // Return		: boolean -> is a pulse rdy
    //
    // Modification	:
    //--------------------------------------------------------------
    boolean mPulseBuffer_Get(PulseBufferStruct* aResult);




#endif /* SRC_MODULES_MPULSEBUFFER_H_ */
