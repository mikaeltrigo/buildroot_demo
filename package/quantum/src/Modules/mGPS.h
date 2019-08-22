/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mGPS.h
Author				: Cestele Yves
Date				: 4 juil. 2017
Description			: GPS functions management

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MGPS_H_
#define SRC_MODULES_MGPS_H_
//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "TimerDef.h"
#include "mRs232.h"

typedef enum
{
    kWaitStartByte,
    kCapturePayload
}enumStateCmdPCSport;

// Gps protocol and type
extern u8 gGpsType;
extern u8 gGpsProtocol;

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

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
    void mGps_SendGpsInfo(u64* aTime, u8 aGpsQuality);

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
    void mGPS_FrameProcessing();

#endif /* SRC_MODULES_MGPS_H_ */
