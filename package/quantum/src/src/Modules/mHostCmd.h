/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mHostCmd.h
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Command to execute from the PC Host

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MHOSTCMD_H_
#define SRC_MODULES_MHOSTCMD_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "utils.h"
#include "TimerDef.h"

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name			: mHostCmd_CmdExecute
    // Author		: Cestele Yves
    // Date			: 28 juin 2017
    // Descritpion		: Command to execute from PC Host
    //
    // Parameters		: FrameStruct*
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mHostCmd_CmdExecute(FrameStruct *aFrame);


#endif /* SRC_MODULES_MHOSTCMD_H_ */
