/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gPrinter.h
Author				: Cestele Yves
Date				: 11 juil. 2017
Description			: Header for the printer manager

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_GESTIONNAIRES_GPRINTER_H_
#define SRC_GESTIONNAIRES_GPRINTER_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "TimerDef.h"
#include "utils.h"
#include "mPulseBuffer.h"
#include "mRollingTimeBuffer.h"
#include "mPrintBuffer.h"

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: gPrinter_setup
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Setup of the gPrinter manager
    //
    // Return		:
    //
    // Modification	:
    //--------------------------------------------------------------
    void gPrinter_setup(void);

    //--------------------------------------------------------------
    // Name		: gPrinter_Execute
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Execution of the printer manager
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gPrinter_Execute(void);





#endif /* SRC_GESTIONNAIRES_GPRINTER_H_ */
