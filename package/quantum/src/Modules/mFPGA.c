/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mFPGA.c
Author				: Cestele Yves
Date				: 4 juil. 2017
Description			: Description in mFPGA.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mFPGA.h"

//--------------------------------------------------------------
// 				FUNCTIONS
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
    void mFpga_PrepareSynch(u8 *aPayload)
    {

	u8 tab1[8];
	u8 tab2[8];

	s64  *aUtcOffset;
	u32  *aPayLoadPtr;

	// Connect Main and Backup clocks
	//mSynchro_SetCanEnableSynchro(true);

	// 1st byte 1 == GPS synchronization
	if ( (aPayload[0] & 0xF0) == 0x10)
	{
//	    // TimeToSynchro starts at Payload[5](48 bits)
//	    tab1[0] = 0;
//	    tab1[1] = 0;
//	    tab1[2] = 0;
//	    tab1[3] = aPayload[5];
//	    tab1[4] = aPayload[6];
//	    tab1[5] = aPayload[7];
//	    tab1[6] = aPayload[8];
//	    tab1[7] = aPayload[9];
//
//	    // Utc Offset starts at Payload[10](48 bits)
//	    tab2[0] = 0;
//	    tab2[1] = 0;
//	    tab2[2] = 0;
//	    tab2[3] = aPayload[10];
//	    tab2[4] = aPayload[11];
//	    tab2[5] = aPayload[12];
//	    tab2[6] = aPayload[13];
//	    tab2[7] = aPayload[14];
//
//	    // Only 48 bits
//	    //*aUtcOffset = (*aUtcOffset) & 0x000000FFFFFFFFFF;
//
//	    aUtcOffset = (s64*)tab2;
//
//	    // Check UTC Offset sign
//	    if ((aPayload[0] & 0x0F) == 0x01)
//	    {
//	    (*aUtcOffset) = -(*aUtcOffset);
//	    }
//
//	    // Set UTC Offset
//	    //mGps_SetUtcOffset((u64*)tab1, aUtcOffset);
//
//
//	    // Request synchro
//	    //mGps_MakeGpsSynchro();
	}
	else
	{
	    // Cancel GPS Synchronisation
	    //mGps_CancelGpsSynchro();

	    // Normal synchronization
	    iFpga_PrepareSynch(aPayload);

	    // Check if cancel synchro
	    // All inputs are 0
	    aPayLoadPtr=(u32*)(&aPayload[1]);
//	    if ((*aPayLoadPtr) == 0x00000000)
//	    {
//		mSynchro_SetCanEnableSynchro(false);
//	    }

	}
    }

