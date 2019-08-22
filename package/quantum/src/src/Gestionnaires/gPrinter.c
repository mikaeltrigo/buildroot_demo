/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gPrinter.c
Author				: Cestele Yves
Date				: 11 juil. 2017
Description			: Description in gPrinter.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "gPrinter.h"

//Const for compressed printer mode   (compressed mode: 0x01 instead of 0x00)
const u8 cLine[]                = {"------------------------\r\n"};
#define kLineSize 26
const u8 cModeNonCompressed[]	   = {0x1B, 0x21, 0x00};
#define kModeNonCompressedSize 3

// Boot
const u8 cLineFeed[]            = {"\r\n"};
#define kLFSize 2

static u8 cHello[]               = {"----------\r\n Quantum Timer\r\n SwissTiming Ltd.\r\n----------\r\n"};//         Primary Versions : 1.24 / 4.3\r\n----------------------------\r\n"};
#define kHelloSize 22

const u8 cConstructor[]         = {"      SwissTiming Ltd.\r\n"};
#define kConstructorSize 24

const u8 cMain[]                = {"         Primary "};
const u8 cBackup[]              = {"        Secondary"};
#define kTimerTypeSize 17

const u8 cFirmWareVers[]        = {"Versions : "};
#define kFirmVersSize 11

//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------

    u8 gPrinter_PrintHello(void)
    {
	static u8 sTxDataTab[kMaxLineSize];

	//Printer in normal pitch mode
	//mPrintBuffer_WritePrintBuffer((u8*)cModeNonCompressed, kModeNonCompressedSize, true);

	mPrintBuffer_WritePrintBuffer(cHello, 59, true);
	//mPrintBuffer_WritePrintBuffer((u8*)cHello, kHelloSize, true);
	//mPrintBuffer_WritePrintBuffer((u8*)cConstructor, kConstructorSize, true);

	if (true)//((if (iFpga_GetTimerKind() == true)
	{
	    mPrintBuffer_WritePrintBuffer((u8*)cMain, kTimerTypeSize, true);
	}
	else
	{
	    mPrintBuffer_WritePrintBuffer((u8*)cBackup, kTimerTypeSize, true);
	}

	mPrintBuffer_WritePrintBuffer((u8*)cLineFeed, kLFSize, true);

	// Internal versions
	mPrintBuffer_WritePrintBuffer((u8*)cFirmWareVers, kFirmVersSize, true);

	ConvertToString(gTimerConfig.FirmwareMainVer, &sTxDataTab[0], 10);
	sTxDataTab[2] = '.';
	ConvertToString(gTimerConfig.FirmwareSubVer, &sTxDataTab[3], 10);
	sTxDataTab[5] = '/';
	ConvertToString(gTimerConfig.FpgaMainVer, &sTxDataTab[6], 10);
	sTxDataTab[8] = '.';
	ConvertToString(gTimerConfig.FpgaSubVer, &sTxDataTab[9], 10);
	sTxDataTab[11] = '\r';
	sTxDataTab[12] = '\n';

	mPrintBuffer_WritePrintBuffer(sTxDataTab, 13, true);
	mPrintBuffer_WritePrintBuffer((u8*)cLine, kLineSize, true);

	return 1;
    }

    //--------------------------------------------------------------
    // Name		: PrintNotArmedPulse
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Prepare the string to send a not armed Pulse
    //
    // Parameters	: DateTimeStruct*	-> Time structure
    //			  u8			-> Pulse N�
    //			  u8[]			-> string
    //
    // Return		: u8 			-> const 24
    //
    // Modification	:
    //--------------------------------------------------------------
    u8 PrintNotArmedPulse(DateTimeStruct* TimeToPrint, u8 aPulseNr, u8 aTxDataTab[])
    {
	aTxDataTab[0] = '(';
	aTxDataTab[1] = ' ';
	ConvertToString(aPulseNr, &aTxDataTab[2], 100);
	aTxDataTab[5] = ')';
	aTxDataTab[6] = ' ';

	ConvertToString((*TimeToPrint).Hour, &aTxDataTab[7], 10);

	aTxDataTab[9] = ':';

	ConvertToString((*TimeToPrint).Minute, &aTxDataTab[10], 10);

	aTxDataTab[12] = ':';

	ConvertToString((*TimeToPrint).Second, &aTxDataTab[13], 10);

	aTxDataTab[15] = '.';

	ConvertToString((*TimeToPrint).Decimal, &aTxDataTab[16], 100000);

	aTxDataTab[22] = 0x0D;
	aTxDataTab[23] = 0x0A;

	return 24;
    }

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
    void gPrinter_setup(void)
    {
	mPulseBuffer_Setup();
	gPrinter_PrintHello();
    }

    //--------------------------------------------------------------
    // Name		: PrintArmedPulse
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Prepare the string to send an armed Pulse
    //
    // Parameters	: DateTimeStruct*	-> Time Structure
    //			  u8			-> Pulse N�
    //			  u8[]			-> String
    //
    // Return		: u8			-> const 24
    //
    // Modification	:
    //--------------------------------------------------------------
    u8 PrintArmedPulse(DateTimeStruct* TimeToPrint, u8 aPulseNr, u8 aTxDataTab[])
    {
	aTxDataTab[0] = '(';
	aTxDataTab[1] = 'A';
	ConvertToString(aPulseNr, &aTxDataTab[2], 100);
	aTxDataTab[5] = ')';
	aTxDataTab[6] = ' ';


	ConvertToString((*TimeToPrint).Hour, &aTxDataTab[7], 10);

	aTxDataTab[9] = ':';

	ConvertToString((*TimeToPrint).Minute, &aTxDataTab[10], 10);

	aTxDataTab[12] = ':';

	ConvertToString((*TimeToPrint).Second, &aTxDataTab[13], 10);

	aTxDataTab[15] = '.';

	ConvertToString((*TimeToPrint).Decimal, &aTxDataTab[16], 100000);

	aTxDataTab[22] = 0x0D;
	aTxDataTab[23] = 0x0A;

	return 24;
    }

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
//    void gPrinter_Execute(void)
//    {
//	boolean aNewPulse = false;
//	PulseBufferStruct aPulseToPrint;
//	DateTimeStruct aDateTime;
//	static u8 sTxDataTab[kMaxLineSize];
//	u8 aSize;
//	u8 i;
//
//	// Always get pulse (empty buffer)
//	aNewPulse = mPulseBuffer_Get(&aPulseToPrint);
//
//	if (aNewPulse)
//	{
//	    switch (gAutoPrintMode)
//	    {
//		// Don't print anything
//		case kPrintNothing:
//		    break;
//
//		// Print only armed pulses
//		case kPrintArmedPulses:
//		{
//		    aDateTime = ToDateTime(&aPulseToPrint.PulseTime);
//		    if (aPulseToPrint.PulseType == kArmedPulse)
//		    {
//			aSize = PrintArmedPulse(&aDateTime, aPulseToPrint.PulseNr, sTxDataTab);
//			mPrintBuffer_WritePrintBuffer(sTxDataTab, aSize, false);
//		    }
//		}
//		break;
//
//		// Print only not armed pulses
//		case kPrintNotArmedPulses:
//		{
//		    aDateTime = ToDateTime(&aPulseToPrint.PulseTime);
//
//		    if (aPulseToPrint.PulseType == kNotArmedPulse)
//		    {
//			aSize = PrintNotArmedPulse(&aDateTime, aPulseToPrint.PulseNr, sTxDataTab);
//			mPrintBuffer_WritePrintBuffer(sTxDataTab, aSize, false);
//		    }
//		}
//		break;
//
//		// Print all pulses
//		case kPrintAllPulses:
//		{
//		    aDateTime = ToDateTime(&aPulseToPrint.PulseTime);
//
//		    if (aPulseToPrint.PulseType == kNotArmedPulse)
//		    {
//			aSize = PrintNotArmedPulse(&aDateTime, aPulseToPrint.PulseNr, sTxDataTab);
//			mPrintBuffer_WritePrintBuffer(sTxDataTab, aSize, false);
//		    }
//		    else if (aPulseToPrint.PulseType == kArmedPulse)
//		    {
//			aSize = PrintArmedPulse(&aDateTime, aPulseToPrint.PulseNr, sTxDataTab);
//			mPrintBuffer_WritePrintBuffer(sTxDataTab, aSize, false);
//		    }
//		}
//		break;
//	    }
//	}
//
//	// Print pulses
//	mPrintBuffer_ReadPrintBuffer();
//
////	for (i = kSportPC; i < kLastPeriph; i++)
////	{
////	    // Print messages received from PC Timing
////	    mRs232_SendString((SerialPortEnum)i)
////	    mMsgToSerial_ReadMsgSerialBuffer((SerialPortEnum)i);
////	}
//
//	mRollingTimeBuffer_FormatSendRtPeriodBuffer();
//
//    }
