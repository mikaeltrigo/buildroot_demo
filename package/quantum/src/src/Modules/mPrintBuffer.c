/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mPrintBuffer.c
Author				: Cestele Yves
Date				: 11 juil. 2017
Description			: Description in mPrintBuffer.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mPrintBuffer.h"

#define kNbEntries 20					// Number of elements
#define next(a) ((u16)(((a)+1)%kNbEntries))		// Function to inc the ctr

static LineBufferStruct sPrinterBuffer[kNbEntries];	// Buffer
static u16 sWriteIdx;					// Write index
static u16 sReadIdx;					// Read Index
static u8 sPrintingEnable = 1;				// Printing enable/disable



//--------------------------------------------------------------
// 				FUNCTIONS
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
    void mPrintBuffer_WritePrintBuffer(u8* aDataToPrint, u16 aSize, u8 immediatePrint)
    {
	u16 i;
	u16 localLength = aSize;

	if (localLength > kMaxLineSize)
	{
	   localLength = kMaxLineSize;
	}

	for(i = 0; i < aSize; i++)
	{
	    sPrinterBuffer[sWriteIdx].LineBuffer[i] = aDataToPrint[i];
	}
	sPrinterBuffer[sWriteIdx].LineSize = localLength;


	if(next(sWriteIdx) != sReadIdx)
	{
	    sWriteIdx = next(sWriteIdx);
	}
	else
	{
	    // Buffer Overflow
	    // A Verifier car on va perdre 2 buffer en cas d'overflow !!
	    sWriteIdx = next(sWriteIdx);
	    sReadIdx = next(sWriteIdx);
	}

	// Print immediately
	if (immediatePrint)
	{
	  mPrintBuffer_ReadPrintBuffer();
	}
    }

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
    void mPrintBuffer_ReadPrintBuffer()
    {
	if(sPrintingEnable == true)
	{
	    if (sReadIdx != sWriteIdx)
	    {
		u8 k = 0;
		for(k = Uart1; k <= Uart1; k++)
		{
		    mRs232_SendString(k, sPrinterBuffer[sReadIdx].LineBuffer, sPrinterBuffer[sReadIdx].LineSize);
		}

		sPrinterBuffer[sReadIdx].LineSize = 0;
		sReadIdx = next(sReadIdx);
	    }
	}
    }

