/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mGPS.c
Author				: Cestele Yves
Date				: 4 juil. 2017
Description			: Description in mGPS.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mGPS.h"

u8 gGpsType 	= 0;			    // Gps protocol and type
u8 gGpsProtocol = 0;

//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mGPS_FrameProcessing
    // Author		: Cestele Yves
    // Date		: 23 juil. 2017
    // Descritpion	: Processing the GPS Frames and update
    //			  general Time and signal force
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mGPS_FrameProcessing()
    {
    static enumStateCmdPCSport sState =kWaitStartByte;
    static u8 sBuf[100];
    static u8 sIndex =0;

    // Read 1 byte:
    u8 aData;
    //u8 aSize = XUartLite_Recv(&gUartInstList.UartLite0, &aData, 1);
    u8 aSize = 0x00;

	if(aSize!=00)
	{
	    switch(sState)
	    {
		case kWaitStartByte:
		    if(aData==0x01)
		    {
			sIndex=0;
			sBuf[sIndex++] = aData;
			sState = kCapturePayload;
		    }
		    break;

		case kCapturePayload:
		    if(aData==0x00)		// End Frame detected
		    {
			sBuf[sIndex++] = aData;

			u8 aBuf[100];
			DecodeFrame(sBuf, sIndex, aBuf);

			// Time update:
			gTime = 0x00;
			gTime |= (((u64)aBuf[7]<<42)&((u64)0x7f<<42));
			gTime |= (((u64)aBuf[6]<<35)&((u64)0x7f<<35));
			gTime |= (((u64)aBuf[5]<<28)&((u64)0x7f<<28));
			gTime |= (((u32)aBuf[4]<<21)&((u32)0x7f<<21));
			gTime |= (((u32)aBuf[3]<<14)&((u32)0x7f<<14));
			gTime |= (((u32)aBuf[2]<<7)&((u32)0x7f<<7));
			gTime |= (((u32)aBuf[1]<<0)&((u32)0x7f<<0));

			gQuality = aBuf[8];
			sIndex=0;
			sState = kWaitStartByte;
		    }
		    else if(aData==0x01)	// Start a Frame detected without a end
		    {
			sIndex=0;
			sBuf[sIndex++] = aData;
		    }
		    else
		    {
			sBuf[sIndex++] = aData;
		    }
		    break;
		default:
		    break;
	    }
	}


    }

    //--------------------------------------------------------------
    // Name			: mGps_SendGpsInfo
    // Author		: Cestele Yves
    // Date			: 7 juil. 2017
    // Descritpion		: Send infos to PC Sport
    //
    // Parameters		: u64 -> GPS Time
    //			  u8  -> GPS Quality
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mGps_SendGpsInfo(u64* aTime, u8 aGpsQuality)
    {
	u64 aZeroTime = 0;

	if (aGpsQuality != 0)
	{
	    mRs232_GpsTime(aTime);
	}
	else
	{
	    mRs232_GpsTime(&aZeroTime);
	}
    }
