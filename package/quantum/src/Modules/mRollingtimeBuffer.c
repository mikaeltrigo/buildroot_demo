/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mRollingtimeBuffer.c
Author				: Cestele Yves
Date				: 5 juil. 2017
Description			: Description in mRollingtimeBuffer.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mRollingTimeBuffer.h"


#define kNbEntriesRollingTimeBuff 20						// Number of elements


static u64 sRtPeriodBuffer[kNbOfRollingTime][kNbEntriesRollingTimeBuff];	// Rolling time buffer, they contain time in micro seconds


static u16 sWriteIdx[kNbOfRollingTime];						// Write index


static u16 sReadIdx[kNbOfRollingTime];						// Read Index
static u8 sTimeRtTab[kRTLengh];							// Buffer for time in string format

#define next(a) ((u16)(((a)+1)%kNbEntriesRollingTimeBuff))

//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mRollingTimeBuffer_AddRTPeriodToBuffer
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Add a periodic RT to buffer
    //
    // Parameters	: u8 	-> RT number
    //			  u64	-> Ptr on the period
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRollingTimeBuffer_AddRTPeriodToBuffer(u8 aRunningTimeNr, u64 aRtPeriod)
    {
	if (aRunningTimeNr < kNbOfRollingTime)
	{
	    // Copy data to the internal buffer
	    //u64 *maVariable = aRtPeriod;//&0x000000FFFFFFFFFF;
	    sRtPeriodBuffer[aRunningTimeNr][sWriteIdx[aRunningTimeNr]] = ((aRtPeriod)&0x000000FFFFFFFFFF);

	    if(next(sWriteIdx[aRunningTimeNr]) != sReadIdx[aRunningTimeNr])
	    {
		sWriteIdx[aRunningTimeNr] = next(sWriteIdx[aRunningTimeNr]);
	    }
	    else
	    {
		// Buffer Overflow
		// A Verifier car on va perdre 2 buffer en cas d'overflow !!
		sWriteIdx[aRunningTimeNr] = next(sWriteIdx[aRunningTimeNr]);
		sReadIdx[aRunningTimeNr] = next(sWriteIdx[aRunningTimeNr]);
	    }
	}
    }

    //--------------------------------------------------------------
    // Name		: mRollingTimeBuffer_FormatSendRtPeriodBuffer
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Send the RT buffers
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRollingTimeBuffer_FormatSendRtPeriodBuffer(void)
    {

	static u8  sBufferDma[kMaxLineSize]; // Intermediate buffer use to build complete message

	u8 i;
	u8 k;
	u8 aLen;
	u16 tempIndex = 0;

	// Loop on rolling time
	for(i = 0; i < kNbOfRollingTime; i++)
	{
	    if (sReadIdx[i] != sWriteIdx[i])
	    {
		tempIndex = sReadIdx[i];
		sReadIdx[i] = next(sReadIdx[i]);

		// Loop on serial port
		for(k = Uart4; k < kNbOfPeriphSerialPort; k++)
		{

		    // Copy to buffer
		    sTimeRtTab[0] = kStartOfFrame;        // Start of frame
		    sTimeRtTab[1]=  0x03;                 // Command number (3 for rolling time)
		    sTimeRtTab[2] = i;                    // Rt Number
		    sTimeRtTab[3] = 0x01;                 // PC Dest
		    sTimeRtTab[4] = (u8)(sRtPeriodBuffer[i][tempIndex])&0x00000000000000ff;

		    sTimeRtTab[5] = (u8)(((sRtPeriodBuffer[i][tempIndex])&0x000000000000ff00)>>8);

		    sTimeRtTab[6] = (u8)(((sRtPeriodBuffer[i][tempIndex])&0x0000000000ff0000)>>16);
		    u64 tmp = (((u64)sRtPeriodBuffer[i][tempIndex])&0x00000000ff000000)>>24;
		    sTimeRtTab[7] = (u8)tmp;//(((u64)sRtPeriodBuffer[i][tempIndex])&0x00000000ff000000)>>24;
		    u64 test = ((sRtPeriodBuffer[i][tempIndex])&0x000000ff00000000);
		    sTimeRtTab[8] = (u8)(((sRtPeriodBuffer[i][tempIndex])&0x000000ff00000000)>>32);
		    sTimeRtTab[9] = kEndOfFrame;          // End of frame

		    aLen=BuildCodedFrame(sTimeRtTab,sBufferDma,10); // Convert to coded frame

		    mRs232_SendString(k,sBufferDma,aLen);     		// Send it
		}
	    }
	}
    }
