/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mHostCmd.c
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Description in mHostCmd.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mHostCmd.h"

//--------------------------------------------------------------
// 				FUNCTIONS
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
void mHostCmd_CmdExecute(FrameStruct *aFrame)
{
    gCmdfromPcSportCallBack[aFrame->Cmd].Callback(aFrame->Payload);
}
