/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mPulseBuffer.c
Author				: Cestele Yves
Date				: 5 juil. 2017
Description			: Description in mPulseBuffer.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mPulseBuffer.h"

static u16 sPBWriteIdx;						// Write Index
static u16 sPBReadIdx;						// Read Index
static PulseBufferStruct sPulseBuffer[kPulseBufferSize];	// Buffer

#define next(a) ((u16)(((a)+1)%kPulseBufferSize))

//--------------------------------------------------------------
// 				FUNCTIONS
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
    void mPulseBuffer_Setup(void)
    {

	u8 i;

	for (i = 0; i < kPulseBufferSize; i++)
	{
	    sPulseBuffer[i].PulseNr  = 0;
	    sPulseBuffer[i].PulseTime  = 0;
	}

	sPBWriteIdx = 0;
	sPBReadIdx = 0;
    }

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
    void mPulseBuffer_Add(u8 aInputNr, u64* aTime, PulseTypeEnum aPulseType)
    {
        sPulseBuffer[sPBWriteIdx].PulseTime  = __builtin_bswap64(*aTime)& 0x000000FFFFFFFFFF;
        sPulseBuffer[sPBWriteIdx].PulseNr  = aInputNr;
        sPulseBuffer[sPBWriteIdx].PulseType = aPulseType;

        if(next(sPBWriteIdx) != sPBReadIdx)
        {
            sPBWriteIdx = next(sPBWriteIdx);
        }
        else
        {
            // Buffer Overflow
            sPBWriteIdx = next(sPBWriteIdx);
            sPBReadIdx = next(sPBWriteIdx);
        }
    }

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
    boolean mPulseBuffer_Get(PulseBufferStruct* aResult)
    {
        boolean aBuffAvail;

        aBuffAvail = false;

        if (sPBReadIdx != sPBWriteIdx)
        {
            (*aResult).PulseNr = sPulseBuffer[sPBReadIdx].PulseNr;
            (*aResult).PulseTime = sPulseBuffer[sPBReadIdx].PulseTime;
            (*aResult).PulseType = sPulseBuffer[sPBReadIdx].PulseType;
            sPBReadIdx = next(sPBReadIdx);
            aBuffAvail = true;
        }

        return aBuffAvail;
    }
