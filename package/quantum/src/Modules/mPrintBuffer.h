/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mPrintBuffer.h
Author				: Cestele Yves
Date				: 11 juil. 2017
Description			:

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MPRINTBUFFER_H_
#define SRC_MODULES_MPRINTBUFFER_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "TimerDef.h"
#include "utils.h"
#include "mRs232.h"

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mPrintBuffer_WritePrintBuffer
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Print infos in the buffer
    //
    // Parameters	: u8*	-> Ptr on datas to print
       //			  u16	-> Size
    //			  u8	-> Must be direct printed?!
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mPrintBuffer_WritePrintBuffer(u8* aDataToPrint, u16 aSize, u8 immediatePrint);

    //--------------------------------------------------------------
    // Name		: mPrintBuffer_ReadPrintBuffer
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Print the buffer
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mPrintBuffer_ReadPrintBuffer();


#endif /* SRC_MODULES_MPRINTBUFFER_H_ */
