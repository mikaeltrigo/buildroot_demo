/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mRs232.h
Author				: Cestele Yves
Date				: 26 juin 2017
Description			: RS232 Communication management. File based
				  on xuartps (V3.1) and xuart_lite to manage:
				      - 2x Uart_PS
				      - 1x Uart_Lite

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MRS232_H_
#define SRC_MODULES_MRS232_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------


#include "TimerDef.h"
#include "IpAddress.h"
#include "mGPS.h"
#include "answerMessages.h"
#include "FPGA_Registers.h"
//--------------------------------------------------------------
// 				Structures
//--------------------------------------------------------------



//typedef struct
//{
//    XUartPs 	Uart1_Ps;
//    XUartPs 	Uart0_Ps;
//    XUartLite 	Uart0_Lite;
//}sUartInstList;

typedef enum
{
    Uart0 =0,	// Uart1_PS	PC_Sport
    Uart1 =1,	// Uart0_Ps	Printer
    Uart2 =2,	// Uart0_Lite	GPS
    Uart3 =3,	// Uart1_Lite	Serial 1
    Uart4 =4,	// Uart2_Lite	Serial 2
    Uart5 =5,	// Uart3_Lite	Serial 3
    Uart6 =6,	// Uart4_Lite	Serial 4
    Uart7 =7	// Uart5_Lite	Serial 5
}enumUartChoice;

void mRs232_SetFDFORTEST(u8 newFd);

void mRs232_SetFDFORTESTPrinter(u8 newFd);

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name			: mRs232_config
    // Author			: Cestele Yves
    // Date			: 26 juin 2017
    // Descritpion		: Setup the RS232 communication
    //
    // Return			: a Structure of the instancied Uarts
    //
    // Modification		:
    //--------------------------------------------------------------
//    rs232InstStruct mRs232_config(XUartPs_Handler aHandlerUartPs0, XUartPs_Handler aHandlerUartPs1, XUartLite_Handler aUartLite0SendHandler,
//				    XUartLite_Handler aUartLite1SendHandler, XUartLite_Handler aUartLite2SendHandler, XUartLite_Handler aUartLite3SendHandler,
//				    XUartLite_Handler aUartLite4SendHandler, XUartLite_Handler aUartLite5SendHandler, XUartLite_Handler aUartLite0RecvHandler,
//				    XUartLite_Handler aUartLite1RecvHandler, XUartLite_Handler aUartLite2RecvHandler, XUartLite_Handler aUartLite3RecvHandler,
//				    XUartLite_Handler aUartLite4RecvHandler, XUartLite_Handler aUartLite5RecvHandler);

    //--------------------------------------------------------------
    // Name		: mRs232_SendString
    // Author		: Cestele Yves
    // Date		: 26 juin 2017
    // Descritpion	: Send a String until \0 on the selected Uart
    //
    // Parameters	: enumUartChoice -> Selected port
    //			  *u8		 -> data to send
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_SendString(enumUartChoice aChannel, u8 aDataPtr[], int length);

    //--------------------------------------------------------------
    // Name		: mRs232_ReadString
    // Author		: Cestele Yves
    // Date		: 26 juin 2017
    // Descritpion	: Read the string received on a selected
    //			  UART port
    //
    // Parameters	: enumUartChoice -> Selected Port
    //			  u8* 		 -> Data read
    //
    // Return		: Return the number of char reads
    //
    // Modification	:
    //--------------------------------------------------------------
    int mRs232_ReadString(enumUartChoice aChannel, u8 aDataPtr[]);

    //--------------------------------------------------------------
    // Name			: mRs232_ReadByte
    // Author		: Cestele Yves
    // Date			: 26 juin 2017
    // Descritpion		: Read One Byte on the selected Uart
    //			  (FIFO)
    //
    // Parameters		: enumUartChoice -> Selected Port
    //
    // Return		: u8	-> Byte Read
    //
    // Modification	:
    //--------------------------------------------------------------
    u8 mRs232_ReadByte(enumUartChoice aChannel);

    //--------------------------------------------------------------
    // Name			: mRs232_CmdExecute
    // Author		: Cestele Yves
    // Date			: 28 juin 2017
    // Descritpion		: Execute the command provided from PC Host
    //
    // Parameters		: FrameStruct*
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_CmdExecute(FrameStruct *aFrame);
    void test2();
    //--------------------------------------------------------------
    // Name		: mRs232_AskDayTime
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Ask the actual time of day
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskDayTime(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_KeepAlive
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Frame send to PC Sport that says we're alive
    //
    // Parameters	: u8* -> payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_KeepAlive(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskTcpParam
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Return the TCP parameters
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskTcpParam(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskSerialParam
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the informations about Serial prms
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskSerialParam(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskArmDisarmStateAllTimingInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give which input is armed / not armed
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskArmDisarmStateAllTimingInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskDebounceAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give which ad input is debounced
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskDebounceAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskDebounceOneTimingInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the deb time for one  input
    //
    // Parameters	: u8* -> Payload with [Inp nb]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskDebounceOneTimingInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskEnDisStateAllTimingInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the state of inputs (armed/notArmed)
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskEnDisStateAllTimingInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskEnDisStateAllTimingOut
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the state of inputs (enable / disable)
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskEnDisStateAllTimingOut(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskEnDisStateAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the state of AD Inputs (Enable / Disable)
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskEnDisStateAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskActiveSlopeAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the slope for AD Inputs
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskActiveSlopeAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskActiveSlopeAllTimingInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the slope for all inputs
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskActiveSlopeAllTimingInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskOneTimingOutState
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the prms of 1 output
    //
    // Parameters	: u8* -> Payload with [out nb]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskOneTimingOutState(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskOneRTState
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give a complete RT state
    //
    // Parameters	: u8* -> Payload with [RT nb]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskOneRTState(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskPolarityAllOutputs
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the polarity of all outputs
    //
    // Parameters	: u8* -> payload with nothiing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskPolarityAllOutputs(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskGenericOutputsReg
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the generic outputs register
    //
    // Parameters	: u8* -> payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskGenericOutputsReg(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskGenericInputsReg
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the generic inputs register
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskGenericInputsReg(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskLevelAllTimingInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the level of all timing inputs
    //
    // Parameters	: u8* -> payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskLevelAllTimingInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AskLevelAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the level of all Time stamp inputs
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AskLevelAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_GpsTime
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Return the GPS and actual Time
    //
    // Parameters	: u64* -> Gps Time in uS
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_GpsTime(u64* aGpsTimeMicroSec);

    //--------------------------------------------------------------
    // Name		: mRs232_GetBoardsVersion
    // Author		: Cestele Yves
    // Date		: 30 juin 2017
    // Descritpion	: Give the board informations
    //
    // Parameters	: u8* -> payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_GetBoardsVersion(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_GetEEpromData
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Get Data from EEprom
    //
    // Parameters	: u8* -> Payload with [addr0][addr1]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_GetEEpromData(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_Set24HoursMode
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Set the 24 Hrs mode
    //
    // Parameters	: u8* -> Payload with [state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_Set24HoursMode(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_AuxInputValues
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Get the aux inputs value
    //
    // Parameters	: u8* -> Payload with [][][][][][][][]
    //				 (8 bytes of datas)
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_AuxInputValues(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_SetGpsProtocol
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Set the GPS Protocol
    //
    // Parameters	: u8* -> Payload with [Type][Protocol]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_SetGpsProtocol(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_SetAutoPrintMode
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Set Auto print mode
    //
    // Parameters	: u8* -> Payload with [modeEnum]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_SetAutoPrintMode(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_GetFpgaConfig
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Get the Quantum FPGA configuration
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_GetFpgaConfig(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_GetFpgaVersionAQ
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Get the FPGA Version aquatic
    //
    // Parameters	: u8* -> Payload with nothong
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_GetFpgaVersionAQ(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: mRs232_GetAdValues
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Get the digital AD Value (non impl)
    //
    // Parameters	: u8* -> Payload with nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void mRs232_GetAdValues(u8 *aPayload);




#endif /* SRC_MODULES_MRS232_H_ */
