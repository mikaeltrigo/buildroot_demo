/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gGPS.c
Author				: Cestele Yves
Date				: 11 juil. 2017
Description			: Description in gGPS.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "gGPS.h"

//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: gGps_Setup
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Setup for the GPS manager layer
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gGps_Setup(void)
    {
	//FIXME -> Create task for gps execute ant sem_wait(); sem_post() in matching uart (or pipe)
    }

    //--------------------------------------------------------------
    // Name		: gGps_Execute
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Execution of the GPS manager layer
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gGps_Execute(void)
    {
	mGPS_FrameProcessing();
    }
