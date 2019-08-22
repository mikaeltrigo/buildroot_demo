/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mRs232.c
Author				: Cestele Yves
Date				: 26 juin 2017
Description			: Description in mRs232.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "mRs232.h"
#include "FPGA_Registers.h"
#include "unistd.h"
#define kREAD_BUFFER_SIZE 200

//--------------------------------------------------------------
// 				VARIABLES
//--------------------------------------------------------------

u8 sTxDataTab[kCodedAsciiMessage];
u8 sTxCodedDataTab[kCodedBinaryBuffer];
u8 fd = 0x00;
u8 fdPrinter = 0x00;

//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name			: mRs232_config
    // Author			: Cestele Yves
    // Date			: 26 juin 2017
    // Descritpion		: Setup the RS232 communication
    //
    // Return			: void
    //
    // Modification		:
    //--------------------------------------------------------------
//    rs232InstStruct mRs232_config(XUartPs_Handler aHandlerUartPs0, XUartPs_Handler aHandlerUartPs1, XUartLite_Handler aUartLite0SendHandler,
//				XUartLite_Handler aUartLite1SendHandler, XUartLite_Handler aUartLite2SendHandler, XUartLite_Handler aUartLite3SendHandler,
//				XUartLite_Handler aUartLite4SendHandler, XUartLite_Handler aUartLite5SendHandler, XUartLite_Handler aUartLite0RecvHandler,
//				XUartLite_Handler aUartLite1RecvHandler, XUartLite_Handler aUartLite2RecvHandler, XUartLite_Handler aUartLite3RecvHandler,
//				XUartLite_Handler aUartLite4RecvHandler, XUartLite_Handler aUartLite5RecvHandler)
//    {
//	// Uart1_PS and Uart0_PS config:
//	XUartPs_Config *ConfigUart0_ps;
//	XUartPs_Config *ConfigUart1_ps;
//	u32 IntrMask;
//
//	ConfigUart0_ps = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);
//	ConfigUart1_ps = XUartPs_LookupConfig(XPAR_XUARTPS_1_DEVICE_ID);
//
//	XUartPs_CfgInitialize(&gUartInstList.UartPS0, ConfigUart0_ps, ConfigUart0_ps->BaseAddress);
//	XUartPs_SelfTest(&gUartInstList.UartPS0);
//	XUartPs_CfgInitialize(&gUartInstList.UartPS1, ConfigUart1_ps, ConfigUart1_ps->BaseAddress);
//	XUartPs_SelfTest(&gUartInstList.UartPS1);
//
//	IntrMask = XUARTPS_IXR_RXOVR;
//
//	XUartPs_SetHandler(&gUartInstList.UartPS0, (XUartPs_Handler)aHandlerUartPs0, &gUartInstList.UartPS0);
//	XUartPs_SetHandler(&gUartInstList.UartPS1, (XUartPs_Handler)aHandlerUartPs1, &gUartInstList.UartPS1);
//
//	XUartPs_SetInterruptMask(&gUartInstList.UartPS0, IntrMask);
//	XUartPs_SetInterruptMask(&gUartInstList.UartPS1, IntrMask);
//	XUartPs_SetOperMode(&gUartInstList.UartPS0, XUARTPS_OPER_MODE_NORMAL);
//	XUartPs_SetOperMode(&gUartInstList.UartPS1, XUARTPS_OPER_MODE_NORMAL);
//	XUartPs_SetRecvTimeout(&gUartInstList.UartPS0, 8);
//	XUartPs_SetRecvTimeout(&gUartInstList.UartPS1, 8);
//
//	XUartPs_SetFifoThreshold(&gUartInstList.UartPS0, 1);
//	XUartPs_SetFifoThreshold(&gUartInstList.UartPS1, 1);
//	XUartPs_SetBaudRate(&gUartInstList.UartPS0, 115200);
//	XUartPs_SetBaudRate(&gUartInstList.UartPS1, 115200);
//
//	// UartLite config:
//	XUartLite_Initialize(&gUartInstList.UartLite0, XPAR_UARTLITE_0_DEVICE_ID);
//	XUartLite_SetSendHandler(&gUartInstList.UartLite0, (XUartLite_Handler)aUartLite0SendHandler, &gUartInstList.UartLite0);
//	XUartLite_SetRecvHandler(&gUartInstList.UartLite0, (XUartLite_Handler)aUartLite0RecvHandler, &gUartInstList.UartLite0);
//	XUartLite_EnableInterrupt(&gUartInstList.UartLite0);
//
//	XUartLite_Initialize(&gUartInstList.UartLite1, XPAR_UARTLITE_1_DEVICE_ID);
////	XUartLite_SetSendHandler(&gUartInstList.UartLite1, (XUartLite_Handler)aUartLite1SendHandler, &gUartInstList.UartLite1);
////	XUartLite_SetRecvHandler(&gUartInstList.UartLite1, (XUartLite_Handler)aUartLite1RecvHandler, &gUartInstList.UartLite1);
////	XUartLite_EnableInterrupt(&gUartInstList.UartLite1);
////
//	XUartLite_Initialize(&gUartInstList.UartLite2, XPAR_UARTLITE_2_DEVICE_ID);
////	XUartLite_SetSendHandler(&gUartInstList.UartLite2, (XUartLite_Handler)aUartLite2SendHandler, &gUartInstList.UartLite2);
////	XUartLite_SetRecvHandler(&gUartInstList.UartLite2, (XUartLite_Handler)aUartLite2RecvHandler, &gUartInstList.UartLite2);
////	XUartLite_EnableInterrupt(&gUartInstList.UartLite2);
////
//	XUartLite_Initialize(&gUartInstList.UartLite3, XPAR_UARTLITE_3_DEVICE_ID);
////	XUartLite_SetSendHandler(&gUartInstList.UartLite3, (XUartLite_Handler)aUartLite3SendHandler, &gUartInstList.UartLite3);
////	XUartLite_SetRecvHandler(&gUartInstList.UartLite3, (XUartLite_Handler)aUartLite3RecvHandler, &gUartInstList.UartLite3);
////	XUartLite_EnableInterrupt(&gUartInstList.UartLite3);
////
//	XUartLite_Initialize(&gUartInstList.UartLite4, XPAR_UARTLITE_4_DEVICE_ID);
////	XUartLite_SetSendHandler(&gUartInstList.UartLite4, (XUartLite_Handler)aUartLite4SendHandler, &gUartInstList.UartLite4);
////	XUartLite_SetRecvHandler(&gUartInstList.UartLite4, (XUartLite_Handler)aUartLite4RecvHandler, &gUartInstList.UartLite4);
////	XUartLite_EnableInterrupt(&gUartInstList.UartLite4);
////
//	XUartLite_Initialize(&gUartInstList.UartLite5, XPAR_UARTLITE_5_DEVICE_ID);
////	XUartLite_SetSendHandler(&gUartInstList.UartLite5, (XUartLite_Handler)aUartLite5SendHandler, &gUartInstList.UartLite5);
////	XUartLite_SetRecvHandler(&gUartInstList.UartLite5, (XUartLite_Handler)aUartLite5RecvHandler, &gUartInstList.UartLite5);
////	XUartLite_EnableInterrupt(&gUartInstList.UartLite5);
//
//
//	return gUartInstList;
//
//    }

	void mRs232_SetFDFORTEST(u8 newFd)
	{
		fd = newFd;
	}

	void mRs232_SetFDFORTESTPrinter(u8 newFd)
	{
		fdPrinter = newFd;
	}

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
    void mRs232_SendString(enumUartChoice aChannel, u8 aDataPtr[], int length)
    {

	switch(aChannel)
	{
	    case Uart0:
		write(fd, aDataPtr, length);
		//XUartPs_Send(&gUartInstList.UartPS0, aDataPtr, length);
		break;

	    case Uart1:
		//write(fdPrinter, aDataPtr, length);
		//XUartPs_Send(&gUartInstList.UartPS1, aDataPtr, length);
		break;

	    case Uart2:
		//XUartLite_Send(&gUartInstList.UartLite0, aDataPtr, length);
		break;

	    case Uart3:
		//XUartLite_Send(&gUartInstList.UartLite1, aDataPtr, length);
		break;

	    case Uart4:
		//XUartLite_Send(&gUartInstList.UartLite2, aDataPtr, length);
		break;

	    case Uart5:
		//XUartLite_Send(&gUartInstList.UartLite3, aDataPtr, length);
		break;

	    case Uart6:
		//XUartLite_Send(&gUartInstList.UartLite4, aDataPtr, length);
		break;

	    case Uart7:
		//XUartLite_Send(&gUartInstList.UartLite5, aDataPtr, length);
		break;

	    default:
		break;
	}


    }

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
    int mRs232_ReadString(enumUartChoice aChannel, u8 aDataPtr[])
    {
	switch(aChannel)
	{
	    case Uart0:
		//return XUartPs_Recv(&gUartInstList.UartPS0, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart1:
		//return XUartPs_Recv(&gUartInstList.UartPS1, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart2:
		//return XUartLite_Recv(&gUartInstList.UartLite0, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart3:
		//return XUartLite_Recv(&gUartInstList.UartLite1, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart4:
		//return XUartLite_Recv(&gUartInstList.UartLite2, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart5:
		//return XUartLite_Recv(&gUartInstList.UartLite3, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart6:
		//return XUartLite_Recv(&gUartInstList.UartLite4, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    case Uart7:
		//return XUartLite_Recv(&gUartInstList.UartLite5, aDataPtr, kREAD_BUFFER_SIZE);
		break;

	    default:
		break;
	}
	return 0;
    }

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
    u8 mRs232_ReadByte(enumUartChoice aChannel)
    {

	u8 aData;

	switch(aChannel)
	{
	    case Uart0:
		//XUartPs_Recv(&gUartInstList.UartPS0, &aData, 1);
		break;

	    case Uart1:
		//XUartPs_Recv(&gUartInstList.UartPS1, &aData, 1);
		break;

	    case Uart2:
		//XUartLite_Recv(&gUartInstList.UartLite0, &aData, 1);
		break;

	    case Uart3:
		//XUartLite_Recv(&gUartInstList.UartLite1, &aData, 1);
		break;

	    case Uart4:
		//XUartLite_Recv(&gUartInstList.UartLite2, &aData, 1);
		break;

	    case Uart5:
		//XUartLite_Recv(&gUartInstList.UartLite3, &aData, 1);
		break;

	    case Uart6:
		//XUartLite_Recv(&gUartInstList.UartLite4, &aData, 1);
		break;

	    case Uart7:
		//XUartLite_Recv(&gUartInstList.UartLite5, &aData, 1);
		break;

	    default:
		break;
	}
	return aData;
    }

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
    void mRs232_CmdExecute(FrameStruct *aFrame)
    {
	gCmdfromPcSportCallBack[aFrame->Cmd].Callback(aFrame->Payload);
    }


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
    void mRs232_AskDayTime(u8 *aPayload)
    {

      u8 aSize=0;

      vu32 *aRegAddrh=kCurrentDayTimeh;
      vu32 *aRegAddrl=kCurrentDayTimel;

      // RS232 Frame construction
      sTxDataTab[0]=kStartOfFrame;                		// Start
      sTxDataTab[1]=kCurrentDayTimeAnsw;          		// Cmd
      sTxDataTab[2]=(u8)((*aRegAddrh)&0x000000ff);		// Actual Time
      sTxDataTab[3]=(u8)(((*aRegAddrl)&0xff000000)>>24);
      sTxDataTab[4]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
      sTxDataTab[5]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
      sTxDataTab[6]=(u8)((*aRegAddrl)&0x000000ff);
      sTxDataTab[7]=kEndOfFrame;                   		// End

      aSize=BuildCodedFrame(sTxDataTab, sTxCodedDataTab, kCurrentDayTimeAnswSize);

      // Emission de la trame via le DMA du RS232
      mRs232_SendString(Uart0, sTxCodedDataTab,aSize);

    }

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
    void mRs232_KeepAlive(u8 *aPayload)
    {

	u8 aSize=0;
	u8 aFlag=0;

	// Wich kind of timer (Main/Backup)
	aFlag = 0x01; //iFpga_GetTimerKind();

	// Check UP & DOWN limits
//	if(((!iDio_GetPort(kLCDDATAL,kIo5))==true)&&(iDio_GetPort(kLCDDATAL,kIo4)==true))
//	{
	    aFlag|=(1<<3);
//	}
//	else
//	{
//	    aFlag&=(~(1<<3));
//	}

	// Check REF OK
//	if(iDio_GetPort(kLCDDATAL,kIo3)==true)
//	{
	    aFlag|=(1<<4);
//	}
//	else
//	{
//	    aFlag&=(~(1<<4));
//	}

	// Reset bit (main/backup)
	aFlag&=(~0x02);
	aFlag|=0x01<<1;//(iFpga_GetMainBackupBtn()<<1);

	// Is timer 2 sync?!
//	if((kCurrentDayTimeh&0x00000100)==0x00000100)
//	{
	    aFlag|=(1<<2);
//	}
//	else
//	{
//	    aFlag&=(~(1<<2));
//	}

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;      		// Star
	sTxDataTab[1]=kKeepAliveAnsw;     		// Command
	sTxDataTab[2]=0x01;				// Type of the connected timer. 01: FPGA Timer 02: Emulator.
	sTxDataTab[3]=gTimerConfig.FpgaMainVer;		// TODO Initialize this one
	sTxDataTab[4]=gTimerConfig.FpgaSubVer;
	sTxDataTab[5]=gTimerConfig.FirmwareMainVer;
	sTxDataTab[6]=gTimerConfig.FirmwareSubVer;
	sTxDataTab[7]=aFlag;				// FLAGS
	sTxDataTab[8]=kEndOfFrame;        		// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kKeepAliveAnswSize);

	// Emission de la trame via le DMA du RS232
	mRs232_SendString(Uart0, sTxCodedDataTab, aSize);
    }


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
    void mRs232_AskTcpParam(u8 *aPayload)
    {
	u8 aSize=0;

	//RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;      				// Start
	sTxDataTab[1]=kTcpIpConfAnsw;     				// command
	sTxDataTab[2]=gIPConfig.MacAddress.addr[0];
	sTxDataTab[3]=gIPConfig.MacAddress.addr[1];
	sTxDataTab[4]=gIPConfig.MacAddress.addr[2];
	sTxDataTab[5]=gIPConfig.MacAddress.addr[3];
	sTxDataTab[6]=gIPConfig.MacAddress.addr[4];
	sTxDataTab[7]=gIPConfig.MacAddress.addr[5];
	sTxDataTab[8]=(u8)((gIPConfig.IPAddr&0xff000000)>>24);	// Ip Adresse
	sTxDataTab[9]=(u8)((gIPConfig.IPAddr&0x00ff0000)>>16);
	sTxDataTab[10]=(u8)((gIPConfig.IPAddr&0x0000ff00)>>8);
	sTxDataTab[11]=(u8)((gIPConfig.IPAddr&0x000000ff));
	sTxDataTab[12]=(u8)((gIPConfig.IPmask&0xff000000)>>24);	// Ip mask
	sTxDataTab[13]=(u8)((gIPConfig.IPmask&0x00ff0000)>>16);
	sTxDataTab[14]=(u8)((gIPConfig.IPmask&0x0000ff00)>>8);
	sTxDataTab[15]=(u8)((gIPConfig.IPmask&0x000000ff));
	sTxDataTab[16]=(u8)((gIPConfig.RemotePort&0x0000ff00)>>8);	// Port Number
	sTxDataTab[17]=(u8)((gIPConfig.RemotePort&0x000000ff));
	sTxDataTab[18]=kEndOfFrame;        				// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kTcpIpConfAnswSize);

	// Emission de la trame via le DMA du RS232
	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskSerialParam(u8 *aPayload)
    {
	u8 aSize=0;

	//RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     				// Start
	sTxDataTab[1]=kSerialParamAnsw;   				// Command
	sTxDataTab[2]=aPayload[0];					// Serial Port
	sTxDataTab[3]=gTimerConfig.SerialTab[aPayload[0]].SerialSpeed;	// Baudrate
	sTxDataTab[4]=gTimerConfig.SerialTab[aPayload[0]].DataBits;	// Data bits nb
	sTxDataTab[5]=gTimerConfig.SerialTab[aPayload[0]].StopBits;	// Stop bit(s) nb
	sTxDataTab[6]=gTimerConfig.SerialTab[aPayload[0]].Parity;	// Parity
	sTxDataTab[7]=kEndOfFrame;        				// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kSerialParamAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskArmDisarmStateAllTimingInp(u8 *aPayload)
    {

	u8 aSize=0;
	u32 aVal=0;
	u16 i=0;
	vu32 *aRegAddr=kconfig_input1;

	// Check if armed or not
	for(i=0;i<kNbOfInput;i++,aRegAddr++)
	{
	    if(((*aRegAddr)&0x00000002)==0x00000002)
	    {
		aVal|=(1<<i);
	    }
	}

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     		// Start
	sTxDataTab[1]=kArmNotArmed32InpAnsw;		// Command
	sTxDataTab[2]=(u8)((aVal&0xff000000)>>24);	// State (armed, not armed)
	sTxDataTab[3]=(u8)((aVal&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)((aVal&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)((aVal&0x000000ff));		// Etat des 32 entr�e (arm�e ou non arm�e)
	sTxDataTab[6]=kEndOfFrame;        		// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kArmNotArmed32InpAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskDebounceAllTimeStampInp(u8 *aPayload)
    {

	u8 aSize=0;
	vu32 *aRegAddr=kconfig_DebounceAdInputs;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kDebounceTimeStampInpAnsw;		// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0x00ff0000)>>16);	// Debounce ad inps
	sTxDataTab[3]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[4]=(u8)(((*aRegAddr)&0x000000ff));
	sTxDataTab[5]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kDebounceTimeStampInpAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskDebounceOneTimingInp(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddr=kconfig_input1;

	aRegAddr+=aPayload[0];

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kDebounceTimeInpAnsw;			// Command
	sTxDataTab[2]=aPayload[0];				// Inp nb
	sTxDataTab[3]=(u8)(((*aRegAddr)&0xff000000)>>24);	// Debounce inp
	sTxDataTab[4]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[5]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[6]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kDebounceTimeInpAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskEnDisStateAllTimingInp(u8 *aPayload)
    {
	u8 aSize=0;
	u32 aVal=0;
	u16 i=0;
	vu32 *aRegAddr=kconfig_input1;

	// Check if armed or not
	for(i=0;i<kNbOfInput;i++,aRegAddr++)
	{
	    if(((*aRegAddr)&0x00000001)==0x00000001)
	    {
		aVal|=(1<<i);
	    }
	}

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     		// Start
	sTxDataTab[1]=kEnDisState32InpAnsw;		// Command
	sTxDataTab[2]=(u8)((aVal&0xff000000)>>24);	// Inputs state
	sTxDataTab[3]=(u8)((aVal&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)((aVal&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)((aVal&0x000000ff));
	sTxDataTab[6]=kEndOfFrame;        		// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kEnDisState32InpAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskEnDisStateAllTimingOut(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddr=kOuputsEnable;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kEnDisState32OutAnsw;			// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0xff000000)>>24);	// Inputs state
	sTxDataTab[3]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)(((*aRegAddr)&0x000000ff));
	sTxDataTab[6]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kEnDisState32InpAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskEnDisStateAllTimeStampInp(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddrh= kEnable_AdInputsh;
	vu32 *aRegAddrm= kEnable_AdInputsm;
	vu32 *aRegAddrl= kEnable_AdInputsl;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kEnDisStateAdInpAnsw;			// Command
	sTxDataTab[2]=(u8)(((*aRegAddrl)&0xff000000)>>24);	// State of inputs AD (96x)
	sTxDataTab[3]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)(((*aRegAddrl)&0x000000ff));
	sTxDataTab[6]=(u8)(((*aRegAddrm)&0xff000000)>>24);
	sTxDataTab[7]=(u8)(((*aRegAddrm)&0x00ff0000)>>16);
	sTxDataTab[8]=(u8)(((*aRegAddrm)&0x0000ff00)>>8);
	sTxDataTab[9]=(u8)(((*aRegAddrm)&0x000000ff));
	sTxDataTab[10]=(u8)(((*aRegAddrh)&0xff000000)>>24);
	sTxDataTab[11]=(u8)(((*aRegAddrh)&0x00ff0000)>>16);
	sTxDataTab[12]=(u8)(((*aRegAddrh)&0x0000ff00)>>8);
	sTxDataTab[13]=(u8)(((*aRegAddrh)&0x000000ff));
	sTxDataTab[14]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kEnDisStateAdInpSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskActiveSlopeAllTimeStampInp(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddr=kpolarity_AdInputs1to16;

	// Construction de la trame RS232
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kSlopeAllAdInpAnsw;			// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0xff000000)>>24);	// Slopes 95-0
	sTxDataTab[3]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)(((*aRegAddr)&0x000000ff));
	aRegAddr--;
	sTxDataTab[6]=(u8)(((*aRegAddr)&0xff000000)>>24);
	sTxDataTab[7]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[8]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[9]=(u8)(((*aRegAddr)&0x000000ff));
	aRegAddr--;
	sTxDataTab[10]=(u8)(((*aRegAddr)&0xff000000)>>24);
	sTxDataTab[11]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[12]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[13]=(u8)(((*aRegAddr)&0x000000ff));
	aRegAddr--;
	sTxDataTab[14]=(u8)(((*aRegAddr)&0xff000000)>>24);
	sTxDataTab[15]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[16]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[17]=(u8)(((*aRegAddr)&0x000000ff));
	aRegAddr--;
	sTxDataTab[18]=(u8)(((*aRegAddr)&0xff000000)>>24);
	sTxDataTab[19]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[20]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[21]=(u8)(((*aRegAddr)&0x000000ff));
	aRegAddr--;
	sTxDataTab[22]=(u8)(((*aRegAddr)&0xff000000)>>24);
	sTxDataTab[23]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[24]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[25]=(u8)(((*aRegAddr)&0x000000ff));
	sTxDataTab[26]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kSlopeAllAdInpSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskActiveSlopeAllTimingInp(u8 *aPayload)
    {

	u8 aSize=0;
	u32 aVal=0;
	u32 aVal1=0;
	u16 i=0;
	u32 aTmp;
	vu32 *aRegAddr=kconfig_input1;

	// Read the slope for each input
	for(i=0,aTmp=0,aVal=0;i<(kNbOfInput/2);i++,aRegAddr++)
	{
	    aTmp=(u32)(*aRegAddr);
	    aVal|=(((aTmp&0x30)>>4)<<(i*2));
	}

	for(i=(kNbOfInput/2),aTmp=0,aVal1=0;i<kNbOfInput;i++,aRegAddr++)
	{
	    aTmp=(u32)(*aRegAddr);
	    aVal1|=(((aTmp&0x30)>>4)<<((i-16)*2));
	}

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     		// Start
	sTxDataTab[1]=kSlopeAllInpAnsw;			// Command
	sTxDataTab[2]=(u8)((aVal&0xff000000)>>24);	// Input slope 31 - 0
	sTxDataTab[3]=(u8)((aVal&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)((aVal&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)((aVal&0x000000ff));
	sTxDataTab[6]=(u8)((aVal1&0xff000000)>>24);
	sTxDataTab[7]=(u8)((aVal1&0x00ff0000)>>16);
	sTxDataTab[8]=(u8)((aVal1&0x0000ff00)>>8);
	sTxDataTab[9]=(u8)((aVal1&0x000000ff));
	sTxDataTab[10]=kEndOfFrame;        		// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kSlopeAllInpSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskOneTimingOutState(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddrh=kconfig_output1h;
	aRegAddrh+=(aPayload[0]*2);
	vu32 *aRegAddrl=kconfig_output1l;
	aRegAddrl+=(aPayload[0]*2);

	// Construction de la trame RS232
	sTxDataTab[0]=kStartOfFrame;     			// Start du message
	sTxDataTab[1]=kState1OutAnsw;				// Nu de la r�ponse
	sTxDataTab[2]=aPayload[0];				// Nu de la sortie
	sTxDataTab[3]=(u8)(((*aRegAddrh)&0x000000ff));		// Next day time
	sTxDataTab[4]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[5]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[6]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[7]=(u8)(((*aRegAddrl)&0x000000ff));
	sTxDataTab[8]=	gOutputPcSportDestTab[aPayload[0]];	// PC destination

	aRegAddrl=kOutput1DestinationMask;
	aRegAddrl+=aPayload[0];

	sTxDataTab[9]=(u8)(((*aRegAddrl)&0xff000000)>>24);	// Output mask
	sTxDataTab[10]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[11]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[12]=(u8)(((*aRegAddrl)&0x000000ff));
	sTxDataTab[13]=(u8)(((*aRegAddrh)&0xff000000)>>24);	// Pulse duration
	sTxDataTab[14]=(u8)(((*aRegAddrh)&0x00ff0000)>>16);
	sTxDataTab[15]=(u8)(((*aRegAddrh)&0x0000ff00)>>8);
	sTxDataTab[16]=kEndOfFrame;      			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kState1OutAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }


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
    void mRs232_AskOneRTState(u8 *aPayload)
    {
	u8 aSize=0;

	vu32 *aRegAddrh=kConfigRollingTime1h;
	aRegAddrh+=(aPayload[0]*2);
	vu32 *aRegAddrl=kConfigRollingTime1l;
	aRegAddrl+=(aPayload[0]*2);

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     				// Start
	sTxDataTab[1]=kState1RTAnsw;					// Command
	sTxDataTab[2]=aPayload[0];
	sTxDataTab[3]=(u8)(((*aRegAddrl)&0x00000003));
	sTxDataTab[4]=(u8)(((*aRegAddrl)&0x00000008)>>3);

	aRegAddrl=kIntervalRollingTime1;
	aRegAddrl+=aPayload[0];

	sTxDataTab[5]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[6]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[7]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[8]=(u8)(((*aRegAddrl)&0x000000ff));

	aRegAddrh=kConfigRollingTime1h;
	aRegAddrh+=(aPayload[0]*2);
	aRegAddrl=kConfigRollingTime1l;
	aRegAddrl+=(aPayload[0]*2);

	sTxDataTab[9]=(u8)(((*aRegAddrh)&0xff000000)>>24);
	sTxDataTab[10]=(u8)(((*aRegAddrh)&0x00ff0000)>>16);
	sTxDataTab[11]=(u8)(((*aRegAddrh)&0x0000ff00)>>8);
	sTxDataTab[12]=(u8)(((*aRegAddrh)&0x000000ff));
	sTxDataTab[13]=(u8)(((*aRegAddrl)&0xff000000)>>24);

	aRegAddrh=kCurrentDayTimeh;
	aRegAddrh+=(aPayload[0]*2);
	aRegAddrl=kCurrentDayTimel;
	aRegAddrl+=(aPayload[0]*2);

	sTxDataTab[14]=(u8)(((*aRegAddrh)&0x000000ff));
	sTxDataTab[15]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[16]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[17]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[18]=(u8)(((*aRegAddrl)&0x000000ff));
	sTxDataTab[19]=gRollingTimePcSportDestTab[aPayload[0]];

	aRegAddrl=kOutputMaskRT1;
	aRegAddrl+=aPayload[0];

	sTxDataTab[20]=(u8)(((*aRegAddrl)&0xff000000)>>24);		// Current Output mask
	sTxDataTab[21]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[22]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[23]=(u8)(((*aRegAddrl)&0x000000ff));
	sTxDataTab[24]=(u8)0;
	sTxDataTab[25]=(u8)0;
	sTxDataTab[26]=(u8)0;
	sTxDataTab[27]=(u8)0;
	sTxDataTab[28]=(u8)0;
	sTxDataTab[29]=(u8)0;
	sTxDataTab[30]=(u8)0;
	sTxDataTab[31]=(u8)0;
	sTxDataTab[32]=(u8)0;
	sTxDataTab[33]=(u8)0;
	sTxDataTab[34]=(u8)0;
	sTxDataTab[35]=(u8)0;
	sTxDataTab[36]=(u8)0;
	sTxDataTab[37]=(u8)0;
	sTxDataTab[38]=(u8)0;
	sTxDataTab[39]=(u8)0;
	sTxDataTab[40]=(u8)0;
	sTxDataTab[41]=(u8)0;
	sTxDataTab[42]=(u8)0;
	sTxDataTab[43]=kEndOfFrame;        				// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kState1RTAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

//    //--------------------------------------------------------------
//    // Name		: mRs232_SendMsgOnSerialPort
//    // Author		: Cestele Yves
//    // Date		: 30 juin 2017
//    // Descritpion	: Function that send a message on an other COM port
//    //
//    // Parameters	: u8* -> Payload with [port nb][msg]...
//    //
//    // Return		: void
//    //
//    // Modification	:
//    //--------------------------------------------------------------
//    void mRs232_SendMsgOnSerialPort(UInt8 *aPayload)
//    {
//
//	static u16 pLengh;
//	static u8  pCharTab[2000];
//	static u16 i;
//
//	// Extract to determinate the data length
//	pLengh=((aPayload[0]<<8)|(aPayload[1]))-1;
//
//    if (aPayload[2] != kPrinter)
//    {
//      // Utilisation des buffers de messages pour les ports s�ries
//      mMsgToSerial_WriteMsgSerialBuffer(aPayload[2], &aPayload[3], pLengh);
//    }
//    else
//    {
//      // Utilisation des buffers propres � la sortie imprimante
//      mPrintBuffer_WritePrintBuffer(&aPayload[3], pLengh, false);
//    }
//
//    }

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
    void mRs232_AskPolarityAllOutputs(u8 *aPayload)
    {

	u8 aSize=0;
	static u8 anInvertedOutput = 0;
	vu32 *aRegAddr=kOutputsPolarity;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kAskPolAllOutAnsw;			// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0xff000000)>>24);	// Polarity Outputs
	sTxDataTab[3]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)((*aRegAddr)&0x000000ff);
	sTxDataTab[6]=kEndOfFrame;        			// End

	//**********
	// Polarity inversion for first fourth output
	// Must be modified when Ares interface card will be ready
	anInvertedOutput = sTxDataTab[5] & 0x0F;
	anInvertedOutput = (~anInvertedOutput) & 0x0F;
	sTxDataTab[5] = sTxDataTab[5] & 0xF0;
	sTxDataTab[5] += anInvertedOutput;
	//**********

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAskPolAllOutSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskGenericOutputsReg(u8 *aPayload)
    {

	u8 aSize=0;
	vu32 *aRegAddr=kGenericOutputs;

	//  RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kAskGenOutAnsw;				// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0x0000ff00)>>8);	// Generic Outputs
	sTxDataTab[3]=(u8)((*aRegAddr)&0x000000ff);
	sTxDataTab[4]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAskGenOutAnsSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskGenericInputsReg(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddr=kGenericInputs;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start du message
	sTxDataTab[1]=kAskGenInpAnsw;				// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0x0000ff00)>>8);	// Generic Inputs
	sTxDataTab[3]=(u8)((*aRegAddr)&0x000000ff);
	sTxDataTab[4]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAskGenInpAnsSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskLevelAllTimingInp(u8 *aPayload)
    {
	u8 aSize=0;
	vu32 *aRegAddr=(vu32*)kInputsState;

	// RS232 Frame construction
	sTxDataTab[0]=(u8)kStartOfFrame;     			// Start
	sTxDataTab[1]=kAskLevelAllTimingInpAnsw;		// Command
	sTxDataTab[2]=(u8)(((*aRegAddr)&0xff000000)>>24);	// Timing Inputs
	sTxDataTab[3]=(u8)(((*aRegAddr)&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)(((*aRegAddr)&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)((*aRegAddr)&0x000000ff);
	sTxDataTab[6]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAskLevelAllTimingInpAnsSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_AskLevelAllTimeStampInp(u8 *aPayload)
    {

	u8 aSize=0;
	vu32 *aRegAddrH=kAdInputsStateh;
	vu32 *aRegAddrM=kAdInputsStatem;
	vu32 *aRegAddrL=kAdInputsStatel;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;     			// Start
	sTxDataTab[1]=kAskLevelAllTimeStampInpAnsw;		// Command
	sTxDataTab[2]=(u8)(((*aRegAddrL)&0xff000000)>>24);	// Time stamp Inputs
	sTxDataTab[3]=(u8)(((*aRegAddrL)&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)(((*aRegAddrL)&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)((*aRegAddrL)&0x000000ff);
	sTxDataTab[6]=(u8)(((*aRegAddrM)&0xff000000)>>24);
	sTxDataTab[7]=(u8)(((*aRegAddrM)&0x00ff0000)>>16);
	sTxDataTab[8]=(u8)(((*aRegAddrM)&0x0000ff00)>>8);
	sTxDataTab[9]=(u8)((*aRegAddrM)&0x000000ff);
	sTxDataTab[10]=(u8)(((*aRegAddrH)&0xff000000)>>24);
	sTxDataTab[11]=(u8)(((*aRegAddrH)&0x00ff0000)>>16);
	sTxDataTab[12]=(u8)(((*aRegAddrH)&0x0000ff00)>>8);
	sTxDataTab[13]=(u8)((*aRegAddrH)&0x000000ff);
	sTxDataTab[14]=kEndOfFrame;        			// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAskLevelAllTimeStampInpAnsSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }


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
    void mRs232_GpsTime(u64* aGpsTimeMicroSec)
    {
	u8 aSize=0;
	u32 aGpsTimeHigh = 0;
	u32 aGpsTimeLow = 0;

	// Add one second to be aligned with GPS PPS Pulse
	(*aGpsTimeMicroSec) = (*aGpsTimeMicroSec) + ((u32)1000000);
	aGpsTimeHigh = (u32)( (*aGpsTimeMicroSec) >> 32);
	aGpsTimeLow =  (u32)( (*aGpsTimeMicroSec) & 0x00000000FFFFFFFF);

	vu32 *aRegAddrh=kCurrentDayTimeh;
	vu32 *aRegAddrl=kCurrentDayTimel;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;                		// Start du message
	sTxDataTab[1]=kCurrentGpsTimeAnsw;          		// Nu de la r�ponse
	sTxDataTab[2]=(u8)((aGpsTimeHigh)&0x000000ff);		// GPS Time (2* reg of 32 bits -> result on 40 bits)
	sTxDataTab[3]=(u8)(((aGpsTimeLow)&0xff000000)>>24);
	sTxDataTab[4]=(u8)(((aGpsTimeLow)&0x00ff0000)>>16);
	sTxDataTab[5]=(u8)(((aGpsTimeLow)&0x0000ff00)>>8);
	sTxDataTab[6]=(u8)((aGpsTimeLow)&0x000000ff);		// Actual time (2* reg of 32 bits -> result on 40 bits)
	sTxDataTab[7]=(u8)((*aRegAddrh)&0x000000ff);
	sTxDataTab[8]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[9]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[10]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[11]=(u8)((*aRegAddrl)&0x000000ff);
	sTxDataTab[12]=kEndOfFrame;                   		// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kCurrentGpsTimeAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_GetBoardsVersion(u8 *aPayload)
    {
	u8 aSize=0;
//	u8 aRet=0;

//	// Read EEprom
//	aRet=mI2cEEprom_ReadBuffer(kTimerEEprom, (UInt8*)&gTimerBoardData,0x0+sizeof(TimerConfigStruct) + sizeof(IPConfigStruct), sizeof(BoardDataStruct));
//	aRet=mI2cEEprom_ReadBuffer(kIntfCardEEProm, (UInt8*)&gIntfBoardData,0x0,sizeof(BoardDataStruct));
//
//	if (iFpga_GetTimerKind() == true)
//	{
//	    aRet=mI2cEEprom_ReadBuffer(kIOEEProm, (UInt8*)&gIOBoardData,0x0,sizeof(BoardDataStruct));
//	}

	// Construction de la trame RS232
	sTxDataTab[0]=kStartOfFrame;                // Start
	sTxDataTab[1]=kBoardRevAnsw;                // Command
	sTxDataTab[2]= gTimerBoardData.TypeBoard;
	sTxDataTab[3]= gTimerBoardData.Revision;
	sTxDataTab[4]= gBaseBoardData.TypeBoard;
	sTxDataTab[5]= gBaseBoardData.Revision;
	sTxDataTab[6]= 0;
	sTxDataTab[7]= 0;
	sTxDataTab[8]=kEndOfFrame;                   // End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kBoardRevAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_GetAdValues(u8 *aPayload)
    {
	u8 aSize=0;
	u8 aRet=0;

	u16 adIn = 0;
	u16 adH1 = 0;
	u16 adH2 = 0;
	u16 adOsc = 0;

	//Read the 4 AD channels
	//mAd_ReadChannel(&adIn, &adH1, &adH2, &adOsc);

	// Construction de la trame RS232
	sTxDataTab[0]= kStartOfFrame;                // Start
	sTxDataTab[1]= kAdValuesAnsw;
	sTxDataTab[2]= (u8)((adIn & 0xff00) >> 8);
	sTxDataTab[3]= (u8)(adIn & 0x00ff);
	sTxDataTab[4]= (u8)((adH1 & 0xff00) >> 8);
	sTxDataTab[5]= (u8)(adH1 & 0x00ff);
	sTxDataTab[6]= (u8)((adH2 & 0xff00) >> 8);
	sTxDataTab[7]= (u8)(adH2 & 0x00ff);
	sTxDataTab[8]= (u8)((adOsc & 0xff00) >> 8);
	sTxDataTab[9]= (u8)(adOsc & 0x00ff);


	sTxDataTab[10]=kEndOfFrame;                 // End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAdValuesAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_GetFpgaVersionAQ(u8 *aPayload)
    {
	u8 aSize=0;

	sTxDataTab[0]=kStartOfFrame;                // Start
	sTxDataTab[1]=kFpgaAqVersionAnsw;
	sTxDataTab[2]= (u8)((gFpgaVersionH1 & 0xff00) >> 8);
	sTxDataTab[3]= (u8)(gFpgaVersionH1);
	sTxDataTab[4]= (u8)((gFpgaVersionH2 & 0xff00) >> 8);
	sTxDataTab[5]= (u8)(gFpgaVersionH2);
	sTxDataTab[6]=kEndOfFrame;                 // End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kFpgaAqVersionAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_GetFpgaConfig(u8 *aPayload)
    {
	u8 aSize=0;

	sTxDataTab[0]=kStartOfFrame;                // Start
	sTxDataTab[1]=kFpgaConfigAnsw;
	sTxDataTab[2]= kNbOfInput;
	sTxDataTab[3]= kNbOfAdInput;
	sTxDataTab[4]= kNbOfOutput;
	sTxDataTab[5]= kNbOfRollingTime;
	sTxDataTab[6]=kEndOfFrame;                 // End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kFpgaConfigAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_SetAutoPrintMode(u8 *aPayload)
    {
	gAutoPrintMode = (AutoPrintModeEnum)aPayload[0];
    }

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
    void mRs232_SetGpsProtocol(u8 *aPayload)
    {
	gGpsType = aPayload[0];
	gGpsProtocol = aPayload[1];
    }

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
    void mRs232_AuxInputValues(u8 *aPayload)
    {

	u8 aSize=0;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;                // Start
	sTxDataTab[1]=kAuxInputValuesAnsw;
	sTxDataTab[2]= aPayload[0];
	sTxDataTab[3]= aPayload[1];
	sTxDataTab[4]= aPayload[2];
	sTxDataTab[5]= aPayload[3];
	sTxDataTab[6]= aPayload[4];
	sTxDataTab[7]= aPayload[5];
	sTxDataTab[8]= aPayload[6];
	sTxDataTab[9]= aPayload[7];
	sTxDataTab[10]=kEndOfFrame;                  // End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kAuxInputValuesAnswSize);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

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
    void mRs232_Set24HoursMode(u8 *aPayload)
    {
	g24HoursMode = aPayload[0];
    }


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
    void mRs232_GetEEpromData(u8 *aPayload)
    {

	u16 aPageNr = ((u8)aPayload[0] << 8) + (u8)aPayload[1];
	u32 aStartAddr = 64;
	u8 aSize=0;

	aStartAddr += (aPageNr * 32);

	// Read EEprom
	//aRet=mI2cEEprom_ReadBuffer(kBaseCardEEProm, (UInt8*)&sTxDataTab[3],aStartAddr,32);

	// RS232 Frame construction
	sTxDataTab[0]= kStartOfFrame;                 // Start du message
	sTxDataTab[1]= 0;//kEepromReadAnsw;               // Nu de la r�ponse
	sTxDataTab[2]= 0;//kEepromReadAnswSize;
	sTxDataTab[35]=kEndOfFrame;                   // Fin de la trame

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,36);

	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }
