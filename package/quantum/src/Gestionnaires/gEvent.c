/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gEvent.c
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Description in gEvent.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "gEvent.h"

#include "mRs232.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

static u8 sTxDataTab[kCodedAsciiMessage];			// Buffer used to build ascii message
static u8 sTxCodedDataTab[kCodedBinaryBuffer];		// Message used to store binary coded message

//--------------------------------------------------------------
// 		FUNCTIONS Description
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: gEvent_Setup
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: Setup of the gEvent
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gEvent_Setup(void)
    {

    }

    //--------------------------------------------------------------
    // Name			: gEvent_Execute
    // Author		: Cestele Yves
    // Date			: 28 juin 2017
    // Descritpion		: gEvent function
    //
    // Return		: void
    //
    // Modification		:
    //--------------------------------------------------------------
    void gEvent_Execute(void)
    {

    }

    //--------------------------------------------------------------
    // Name		: gEvents_GpsSynchroEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: CallBack for GPS sync Event callBack
    //
    // Parameters	: void
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_GpsSynchroEventCallBack(void)
    {
      u8 aSize=0;

      vu32 *aRegAddrh= kReceivedGpsSyncTimeh;
      vu32 *aRegAddrl= kReceivedGpsSyncTimel;

      // Construction de la trame RS232
      sTxDataTab[0]=kStartOfFrame;                    		// Start
      sTxDataTab[1]=kGpsSynchroEvent;                		// Command
      sTxDataTab[2]=(u8)((*aRegAddrh)&0x000000ff);		// Trigger time (2*32 bits -> 40 bits)
      sTxDataTab[3]=(u8)(((*aRegAddrl)&0xff000000)>>24);
      sTxDataTab[4]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
      sTxDataTab[5]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
      sTxDataTab[6]=(u8)((*aRegAddrl)&0x000000ff);
      sTxDataTab[7]=kEndOfFrame;                      		// End

      aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kGpsSynchroFrameSize);
      mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_ArmedInputEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Armed Input event Callback
    //
    // Parameters	: u8 -> nb of the armed input
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_ArmedInputEventCallBack(u8 aArmedInputNb)
    {

	u8 aSize=0;

	vu32 *aRegAddrh= kTimeEventInput1h;
	aRegAddrh+=(aArmedInputNb*2);
	vu32 *aRegAddrl= kTimeEventInput1l;
	aRegAddrl+=(aArmedInputNb*2);

	// Construction de la trame RS232
	sTxDataTab[0]=kStartOfFrame;                    	// Start
	sTxDataTab[1]=kArmedInpEventCmd;                	// Command
	sTxDataTab[2]=aArmedInputNb;                    	// Input nb
	sTxDataTab[3]=(u8)((*aRegAddrh)&0x000000ff);		// Trigger time (2*32 bits) -> 40 bits result
	sTxDataTab[4]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[5]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[6]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[7]=(u8)((*aRegAddrl)&0x000000ff);
	sTxDataTab[8]=kRealTimingInputPulse;			// Pulse type
	sTxDataTab[9]=kEndOfFrame;                      	// End

	// Add pulse to buffer for printer
	mPulseBuffer_Add((u8)(aArmedInputNb + 1), (u64*)&sTxDataTab[0], kArmedPulse);

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kArmedInpEventFrameSize);
	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_GpsPPSEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Send infos to the GPS
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_GpsPPSEventCallBack(void)
    {
	u64 time = 9240000000;
	//mGps_SendGpsInfo(&time, 1);
	mGps_SendGpsInfo(&gTime, gQuality);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_RTNewDestCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Config a new RT destination
    //
    // Parameters	: RT number, Input number
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_RTNewDestCallBack(u8 aRTNb,u8 aInpNb)
    {
      u32 aMask2=0xffff00ff;
      u32 *aPayLoadPtr;

      // Config du PC Sport de destination pour ce temps tournant
      gRollingTimePcSportDestTab[aRTNb]=(u8)gRollingTimeNewDestTab[aRTNb][aInpNb].PCSportAddr;

      // Reconfigure le PC dest dans le registre du temps tournant dans la FPGA
      vu32 *aRegAddrl=kConfigRollingTime1l;
      aRegAddrl+=(aRTNb*2);

      aPayLoadPtr=(u32*)(&gRollingTimePcSportDestTab[aRTNb]);
      *aRegAddrl&=(u32)aMask2;
      *aRegAddrl|=(u32)((*aPayLoadPtr&0xff000000)>>16);

      vu32 *aRegAddr=kOutputMaskRT1;
      aRegAddr+=aRTNb*4;
      *aRegAddr=(u32)(gRollingTimeNewDestTab[aRTNb][aInpNb].OutPutMask);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_NotArmedInputEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Not Armed Input Event Callback
    //
    // Parameters	: u8 -> Input nbr
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_NotArmedInputEventCallBack(u8 aNotArmedInputNb)
    {
	u8   aSize=0;

	vu32 *aRegAddrh= kTimeEventInput1h;
	aRegAddrh+=(aNotArmedInputNb*2);
	vu32 *aRegAddrl= kTimeEventInput1l;
	aRegAddrl+=(aNotArmedInputNb*2);

	// RS2323 Frame construction
	sTxDataTab[0]=kStartOfFrame;                    	// Start
	sTxDataTab[1]=kNotArmedInpEventCmd;             	// Command
	sTxDataTab[2]=aNotArmedInputNb;                 	// Inp nbr
	sTxDataTab[3]=(u8)((*aRegAddrh)&0x000000ff);		// Trigger time in 2*32 bits -> 40 bits result
	sTxDataTab[4]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[5]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[6]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[7]=(u8)((*aRegAddrl)&0x000000ff);
	sTxDataTab[8]=kRealTimingInputPulse;			// Pulse type
	sTxDataTab[9]=kEndOfFrame;                      	// End

	// Add pulse to buffer for printer
	mPulseBuffer_Add((u8)(aNotArmedInputNb + 1), (u64*)&sTxDataTab[0], kNotArmedPulse);

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kNotArmedInpEventFrameSize);
	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_DelayReachedEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Send that's a delay is reached
    //
    // Parameters	: u8  -> Command Number
    //			  u8  -> Command size
    //			  u32 -> Inputs register
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_DelayReachedEventCallBack(u8 aCmdNumber, u8 aCmdSize, u32 aInputReg)
    {
	u8 aSize=0;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;                    	// Start
	sTxDataTab[1]=aCmdNumber;                       	// Command
	sTxDataTab[2]=(u8)((aInputReg&0xff000000)>>24);
	sTxDataTab[3]=(u8)((aInputReg&0x00ff0000)>>16);
	sTxDataTab[4]=(u8)((aInputReg&0x0000ff00)>>8);
	sTxDataTab[5]=(u8)(aInputReg&0x000000ff);
	sTxDataTab[6]=kEndOfFrame;                      	// End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,aCmdSize);
	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_SinglePulseOrEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: OR pulse detection event management
    //
    // Parameters	: u16
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_SinglePulseOrEventCallBack(u16 aInputReg)
    {

	u8 aSize=0;

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;                    // Start
	sTxDataTab[1]=kOROnlyOnePulseCmd;               // Command
	sTxDataTab[2]=(u8)((aInputReg&0xff00)>>8);
	sTxDataTab[3]=(u8)(aInputReg&0x00ff);
	sTxDataTab[4]=kEndOfFrame;                      // End

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kOROnlyOnePulseCmdSize);
	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_SoftwareInputEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Soft Input Event Callback
    //
    // Parameters	: u8 -> nput nbr
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_SoftwareInputEventCallBack(u8 aSoftwareInputNb)
    {
	u8 aSize=0;

	vu32 *aRegAddrh= kTimeEventInput1h;
	aRegAddrh+=(aSoftwareInputNb*2);
	vu32 *aRegAddrl= kTimeEventInput1l;
	aRegAddrl+=(aSoftwareInputNb*2);

	// RS232 Frame construction
	sTxDataTab[0]=kStartOfFrame;                    	// Start du message
	sTxDataTab[1]=kSoftInpEventCmd;             		// Command
	sTxDataTab[2]=aSoftwareInputNb;                 	// Num�ro de l'entr�e
	sTxDataTab[3]=(u8)((*aRegAddrh)&0x000000ff);		// Trigger time (2*32 bits ) -> 40 bits result
	sTxDataTab[4]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	sTxDataTab[5]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	sTxDataTab[6]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	sTxDataTab[7]=(u8)((*aRegAddrl)&0x000000ff);
	sTxDataTab[8]=(u8)kSoftInputPulse;			// Pulse type
	sTxDataTab[9]=kEndOfFrame;                      	// End

	// Add pulse to buffer for printer
	mPulseBuffer_Add((u8)(aSoftwareInputNb + 1), (u64*)&sTxDataTab[0], kArmedPulse);

	aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kSoftwareInpEventFrameSize);
	mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_RTEndPeriodCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: RT End period Callback
    //
    // Parameters	: u8 -> rollingtime number
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_RTEndPeriodCallBack(u8 aRollingTimeNb)
    {

	u8 aSize=0;
	static u8 sTxDataTab1[20];

	vu32 *aRegAddrh= kRollingTime1h;
	aRegAddrh+=(aRollingTimeNb*2);
	vu32 *aRegAddrl= kRollingTime1l;
	aRegAddrl+=(aRollingTimeNb*2);

	// If adr of PC Sport differe of 0, send the message
	if(gRollingTimePcSportDestTab[aRollingTimeNb]>0)
	{
	    // RS232 Frame construction
	    sTxDataTab1[0]=kStartOfFrame;                    		// Start
	    sTxDataTab1[1]=kRTEndPeriodCmd;                  		// Command
	    sTxDataTab1[2]=aRollingTimeNb;                   		// RT nb
	    sTxDataTab1[3]=gRollingTimePcSportDestTab[aRollingTimeNb]; 	// PC Sport dest
	    sTxDataTab1[4]=(u8)((*aRegAddrh)&0x000000ff);		// Trigger time (2*32 bits) -> 40 bits result
	    sTxDataTab1[5]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	    sTxDataTab1[6]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	    sTxDataTab1[7]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	    sTxDataTab1[8]=(u8)((*aRegAddrl)&0x000000ff);
	    sTxDataTab1[9]=kEndOfFrame;                      		// end

	    // Copy to send rolling time on external RS port
	    mRollingTimeBuffer_AddRTPeriodToBuffer(aRollingTimeNb, (sTxDataTab1[4]|sTxDataTab1[5]<<8|sTxDataTab1[6]<<16|sTxDataTab1[7]<<24|(u64)sTxDataTab1[8]<<32));

	    aSize=BuildCodedFrame(sTxDataTab1,sTxCodedDataTab,kRTEndPeriodFrameSize);
	    mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
	}
    }

    static void gEvents_CustomTriggerCallBack(u8 aCustomTriggerNb)
    {
	u8 aSize=0;

	vu32 *aRegAddrh= kCustomTriggerRT1h;
	aRegAddrh+=(aCustomTriggerNb*2);
	vu32 *aRegAddrl= kCustomTriggerRT1l;
	aRegAddrl+=(aCustomTriggerNb*2);

	// If adr of PC Sport differ of 0, send the message
	if(gRollingTimeTriggerPcSportDestTab[aCustomTriggerNb]>0)
	{
	    // RS232 Frame construction
	    sTxDataTab[0]=kStartOfFrame;                    			// Start
	    sTxDataTab[1]=kCustomTriggerCmd;                			// Command
	    sTxDataTab[2]=aCustomTriggerNb;                 			// CT number
	    sTxDataTab[3]=gRollingTimeTriggerPcSportDestTab[aCustomTriggerNb]; 	// PC Sport dest
	    sTxDataTab[4]=(u8)((*aRegAddrh)&0x000000ff);				// Trigger time (2*32 bits) -> 40 bits result
	    sTxDataTab[5]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	    sTxDataTab[6]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	    sTxDataTab[7]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	    sTxDataTab[8]=(u8)((*aRegAddrl)&0x000000ff);
	    sTxDataTab[9]=kEndOfFrame;                      			// End

	    aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kCustomTriggerFrameSize);
	    mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
	}
    }

    //--------------------------------------------------------------
    // Name		: gEvents_OutputEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Output Event Callback
    //
    // Parameters	: u8
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_OutputEventCallBack(u8 aOutPutNb)
    {
	u8 aSize=0;

	vu32 *aRegAddrh= kActivatedDayTimeOutput1h;
	aRegAddrh+=(aOutPutNb*2);
	vu32 *aRegAddrl= kActivatedDayTimeOutput1l;
	aRegAddrl+=(aOutPutNb*2);

	// If adr of PC Sport differ of 0, send the message
	if(gOutputPcSportDestTab[aOutPutNb]!=0)
	{
	    // RS232 Frame construction
	    sTxDataTab[0]=kStartOfFrame;                    	// Start
	    sTxDataTab[1]=kOutPutEventCmd;                  	// Command
	    sTxDataTab[2]=aOutPutNb;                        	// Output event nb
	    sTxDataTab[3]=gOutputPcSportDestTab[aOutPutNb]; 	// PC Sport dest
	    sTxDataTab[4]=(u8)((*aRegAddrh)&0x000000ff);	// Trigger time (2*32 bits) -> 40 bits result
	    sTxDataTab[5]=(u8)(((*aRegAddrl)&0xff000000)>>24);
	    sTxDataTab[6]=(u8)(((*aRegAddrl)&0x00ff0000)>>16);
	    sTxDataTab[7]=(u8)(((*aRegAddrl)&0x0000ff00)>>8);
	    sTxDataTab[8]=(u8)((*aRegAddrl)&0x000000ff);
	    sTxDataTab[9]=kEndOfFrame;                      	// End

	    aSize=BuildCodedFrame(sTxDataTab,sTxCodedDataTab,kOutputEventFrameSize);
	    mRs232_SendString(Uart0, sTxCodedDataTab,aSize);
	}
    }

    //--------------------------------------------------------------
    // Name		: gEvents_InputADEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Add event callback
    //
    // Parameters	: u8 -> input nb to add to buffer
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_InputADEventCallBack(u8 aInputADNb)
    {
	u8 aSize=0;
	u64  aTime;

	vu32 *aRegAddrh= kTimeEventAdInput1h;
	aRegAddrh+=(aInputADNb*2);
	vu32 *aRegAddrl= kTimeEventAdInput1l;
	aRegAddrl+=(aInputADNb*2);

	// Add pulse to buffer to send them later outside IRQ. (63 usec original, 25 usec now)
	// TODO add this two functions
//	MemCpy(&aTime, (u32*)aRegAddrh, 8);
//	mAddPulseBuffer_Add(aInputADNb, &aTime, kAddPulse);
    }

    //--------------------------------------------------------------
    // Name		: gEvents_SoftwareInputADEventCallBack
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Add software Event callback
    //
    // Parameters	: u8 -> input add nb to add to buffer
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static void gEvents_SoftwareInputADEventCallBack(u8 aInputADNb)
    {
	u8 aSize=0;
	u64  aTime;

	vu32 *aRegAddrh= kTimeEventAdInput1h;
	aRegAddrh+=(aInputADNb*2);
	vu32 *aRegAddrl= kTimeEventAdInput1l;
	aRegAddrl+=(aInputADNb*2);

	// Add pulse to buffer to send them later outside IRQ.
	// TODO add this two functions
//	MemCpy(&aTime, (UInt32*)aRegPtrh, 8);
//	mAddPulseBuffer_Add(aInputADNb, &aTime, kAddSoftPulse);

    }



//--------------------------------------------------------------
// 	INTERRUPTS HANDLERS FOR SWISS_TIMING IP
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ1_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				ReceivedArmedState
    //				ReceivedSync
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ1_handler(void *arg)
    {

    	int fd;
    	char *uiod = "/dev/uio1";
    	int pending = 0;
    	int reenable = 0xFF;

    	fd = open(uiod, O_RDWR);
    	if (fd < 1)
    	{
    		//printf("Invalid UIO2 device file:%s.\n", uiod);
    	}
    	else
    	{
    		//printf("UIO2 opened, wait for interrupt\n");
    	}

    	write(fd, (void *)&reenable, sizeof(int));

    	for(;;)
    	{
    	  read(fd, (void *)&pending, sizeof(int));

		  u8   i=0;
		  u32  j=0;
		  u8   k=0;

		  // First check for GPS synchro
		  vu32 *aRegAddr=kReceivedGpsState;
		  vu32 *aReg1Addr=kReceivedGpsState_Ack;

		  if ( ((*aRegAddr) & 0x00000001) == 0x00000001)
		  {
			// Ack Event
			*aReg1Addr|=0x00000001;
			gEvents_GpsSynchroEventCallBack();
		  }
		  else if ( ((*aRegAddr) & 0x00000002) == 0x00000002) // GPS PPS Event
		  {
			// Ack Event
			*aReg1Addr|=0x00000002;
			gEvents_GpsPPSEventCallBack();
		  }
		  else if ( ((*aRegAddr) & 0x00000004) == 0x00000004) // Pulse synchro event
		  {
			// Ack Event
			*aReg1Addr|=0x00000004;
			// Not handled by a spontaneous message
		  }
		  else if ( ((*aRegAddr) & 0x00000008) == 0x00000008) // Manual synchro event
		  {
			// Ack Event
			*aReg1Addr|=0x00000008;
			// Not handled by a spontaneous message
		  }
		  else
		  {
			//------------------------------------------------------------
			// Armed Input Event management
			//------------------------------------------------------------
			// Init pointeurs
			aRegAddr=kReceivedArmedState;
			aReg1Addr=kReceivedArmedState_Ack;
			for(i=0,j=1;i<kNbOfInput;i++,j<<=1)
			  {
				// Check if Armed Input Event is waiting
				if((*aRegAddr&j)==j)
				  {
					// Armed input event ack
					*aReg1Addr|=j;

					// Armed Input Event Callback
					gEvents_ArmedInputEventCallBack(i);

					// Is it a new destination to configure!?
					for(k=0;k<kNbOfRollingTime;k++)
					  {
						if(true==gRollingTimeNewDestTab[k][i].IsNew)
						  {
							gRollingTimeNewDestTab[k][i].IsNew=false;
							// Rolling Time New Destination Callback
							gEvents_RTNewDestCallBack(k,i);
						  }
					  }
				  }
			  }
		  }

		//TODO Debug
		//u8 buf[] = {"IRQ1"};
//		mRs232_SendString(Uart1, buf, 4);
		write(fd, (void *)&reenable, sizeof(int));
		//printf("IRQ1\r\n");
    	}
    }

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ2_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				ReceivedNotArmedState
    //
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ2_handler(void *arg)
    {
    	int fd;
    	char *uiod = "/dev/uio2";
    	int pending = 0;
    	int reenable = 0xFF;

    	fd = open(uiod, O_RDWR);
    	if (fd < 1)
    	{
    		//printf("Invalid UIO3 device file:%s.\n", uiod);
    	}
    	else
    	{
    		//printf("UIO3 opened, wait for interrupt\n");
    	}

    	write(fd, (void *)&reenable, sizeof(int));

    	for(;;)
    	{
    		read(fd, (void *)&pending, sizeof(int));

			u8   i=0;
			u32  j=0;

			//------------------------------------------------------------
			// Not Armed Input Event management
			//------------------------------------------------------------
			vu32 *aRegAddr = kReceivedNotArmedState;
			vu32 *aReg1Addr = kReceivedNotArmedState_Ack;
			for(i=0,j=1;i<kNbOfInput;i++,j<<=1)
			{
				// Is a Not armed input in waiting state
				if((*aRegAddr&j)==j)
				{
				// Not Armed Input Event ack
				*aReg1Addr|=j;
				gEvents_NotArmedInputEventCallBack(i);
				}
			}
			write(fd, (void *)&reenable, sizeof(int));
			//printf("IRQ2\r\n");
    	}
	// TODO DEBUG
	//u8 buf[] = {"IRQ2"};
	//mRs232_SendString(Uart1, buf, 4);
    }

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ3_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				ReceivedSoftwareInput
    //				ReceivedInputActiveDelayEvent
    //				ReceivedInputNotActiveDelayEvent
    //				ReceivedOROnePulseEvent
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ3_handler(void *arg)
    {
    	int fd;
    	char *uiod = "/dev/uio3";
    	int pending = 0;
    	int reenable = 0xFF;

    	fd = open(uiod, O_RDWR);
    	if (fd < 1)
    	{
    		//printf("Invalid UIO4 device file:%s.\n", uiod);
    	}
    	else
    	{
    		//printf("UIO4 opened, wait for interrupt\n");
    	}

    	write(fd, (void *)&reenable, sizeof(int));

    	for(;;)
    	{
    		read(fd, (void *)&pending, sizeof(int));

			u8   i=0;
			u32  j=0;
			u8   k=0;
			u32  aInputList = 0;

			// Handle Input Active Delay Event
			vu32 *aRegAddr= kReceivedInputActiveDelayEvent;
			if ( (*aRegAddr) != 0x00000000 )
			{
				aInputList = (*aRegAddr);

				// Acq IRQ
				vu32 *aReg1Addr = kReceivedInputActiveDelayEvent_Ack;
				*aReg1Addr |= aInputList;

				gEvents_DelayReachedEventCallBack(kInputActiveDelayCmd, kInputActiveDelayCmdSize, aInputList);
			}

			// Handle Input Not Active Delay Event
			aRegAddr= kReceivedInputNotActiveDelayEvent;
			if ( (*aRegAddr) != 0x00000000 )
			{
				aInputList = (*aRegAddr);

				vu32 *aReg1Addr= kReceivedInputNotActiveDelayEvent_Ack;
				*aReg1Addr |= aInputList;

				gEvents_DelayReachedEventCallBack(kInputInactiveDelayCmd, kInputInactiveDelayCmdSize, aInputList);
			}

			// Received OR One Pulse Event
			aRegAddr= kReceivedOROnePulseEvent;
			if ( (*aRegAddr) != 0x00000000 )
			{
				// Get MISSING pulse
				aInputList = (*aRegAddr);

				vu32 *aReg1Addr= kReceivedOROnePulseEvent_Ack;
				*aReg1Addr |= aInputList;

				gEvents_SinglePulseOrEventCallBack((u16)aInputList);
			}

			//------------------------------------------------------------
			// Software Input Event support
			//------------------------------------------------------------
			// Init pointeurs
			aRegAddr= kReceivedSoftwareInput;
			vu32 *aReg1Addr= kReceivedSoftwareInput_Ack;

			for(i=0,j=1;i<kNbOfInput;i++,j<<=1)
			{
				// Is a Soft Input Event in waiting state
				if((*aRegAddr&j)==j)
				{
				// Soft input ack
				*aReg1Addr|=j;

				// Software Input Event Callback
				gEvents_SoftwareInputEventCallBack(i);

				// Is a new RT destination to configure?!
				for(k=0;k<kNbOfRollingTime;k++)
				{
					if(true==gRollingTimeNewDestTab[k][i].IsNew)
					{
					gRollingTimeNewDestTab[k][i].IsNew=false;
					gEvents_RTNewDestCallBack(k,i);
					}
				}
				}
			}
			write(fd, (void *)&reenable, sizeof(int));
			//printf("IRQ3\r\n");
    	}
	// TODO Debug:
	//u8 buf[] = {"IRQ3"};
	//mRs232_SendString(Uart1, buf, 4);
    }

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ4_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				RollingtimeEvent
    //				CustomTriggerEvent
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ4_handler(void *arg)
    {

    	int fd;
    	char *uiod = "/dev/uio4";
    	int pending = 0;
    	int reenable = 0xFF;

    	fd = open(uiod, O_RDWR);
    	if (fd < 1)
    	{
    		//printf("Invalid UIO5 device file:%s.\n", uiod);
    	}
    	else
    	{
    		//printf("UIO5 opened, wait for interrupt\n");
    	}

    	write(fd, (void *)&reenable, sizeof(int));

    	for(;;)
    	{
    		read(fd, (void *)&pending, sizeof(int));

			u8 i=0;
			u32 j=0;

			//------------------------------------------------------------
			// Rolling Time End Period support
			//------------------------------------------------------------
			// Check active RT
			vu32 *aRegAddr= kRollingTimeEvent;
			vu32 *aReg1Addr= kRollingTimeEvent_Ack;

			vu32 *test = kFPGA_Config;

			for(i=0,j=1;i<kNbOfRollingTime;i++,j<<=1)
			{
				u32 uVal = *aRegAddr;
				u32 val2 = *test;

				// Is a RT end period in waiting state?!
				if((uVal&j)==j)
				{
				// RT event ack
				*aReg1Addr|=j;
				gEvents_RTEndPeriodCallBack(i);
				}

			}

			//------------------------------------------------------------
			// Custom Trigger support
			//------------------------------------------------------------
			aRegAddr=kCustomTriggerEvent;
			aReg1Addr=kCustomTriggerEvent_Ack;

			for(i=0,j=1;i<kNbOfCustomTrigger;i++,j<<=1)
			{
				// Check si un Output Event est en attente
				if((*aRegAddr&j)==j)
				{
				// Ack du Custom Trigger
				*aReg1Addr|=j;
				gEvents_CustomTriggerCallBack(i);
				}
			}
			write(fd, (void *)&reenable, sizeof(int));
			//printf("IRQ4\r\n");
    	}
	// TODO Debug:
	//u8 buf[] = {"IRQ4"};
	//mRs232_SendString(Uart1, buf, 4);
    }

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ5_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				OutputEvent
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ5_handler(void *arg)
    {
    	int fd;
    	char *uiod = "/dev/uio5";
    	int pending = 0;
    	int reenable = 0xFF;

    	fd = open(uiod, O_RDWR);
    	if (fd < 1)
    	{
    		//printf("Invalid UIO6 device file:%s.\n", uiod);
    	}
    	else
    	{
    		//printf("UIO6 opened, wait for interrupt\n");
    	}

    	write(fd, (void *)&reenable, sizeof(int));

    	for(;;)
    	{
    		read(fd, (void *)&pending, sizeof(int));

			u8 i=0;
			u32 j=0;

			//------------------------------------------------------------
			// Output Event support
			//------------------------------------------------------------
			vu32 *aRegAddr= kOutputEvent;
			vu32 *aReg1Addr= kOutputEvent_Ack;

			for(i=0,j=1;i<kNbOfOutput;i++,j<<=1)
			{
				// Is an output event in waiting state
				if((*aRegAddr&j)==j)
				{
				// Output Event Ack
				*aReg1Addr|=j;
				gEvents_OutputEventCallBack(i);
				}
			}
			write(fd, (void *)&reenable, sizeof(int));
			//printf("IRQ5\r\n");
    	}
	// TODO Debug:
	//u8 buf[] = {"IRQ5"};
	//mRs232_SendString(Uart1, buf, 4);
    }

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ6_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				ReceivedADInputsEvent
    //				ReceivedSoftwareADInput
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ6_handler(void *arg)
    {

    	int fd;
    	char *uiod = "/dev/uio6";
    	int pending = 0;
    	int reenable = 0xFF;

    	fd = open(uiod, O_RDWR);
    	if (fd < 1)
    	{
    		//printf("Invalid UIO7 device file:%s.\n", uiod);
    	}
    	else
    	{
    		//printf("UIO7 opened, wait for interrupt\n");
    	}

    	write(fd, (void *)&reenable, sizeof(int));

    	for(;;)
    	{
    		read(fd, (void *)&pending, sizeof(int));

			u8 i=0;
			u32 j=0;

			//------------------------------------------------------------
			// Input AD Event support
			//------------------------------------------------------------
			vu32 *aRegAddrh=kReceivedAdInputsEventh;
			vu32 *aRegAddrm=kReceivedAdInputsEventm;
			vu32 *aRegAddrl=kReceivedAdInputsEventl;
			vu32 *aReg1Addrh=kReceivedAdInputsEvent_Ackh;
			vu32 *aReg1Addrm=kReceivedAdInputsEvent_Ackm;
			vu32 *aReg1Addrl=kReceivedAdInputsEvent_Ackl;

			// 0 to 31 Input AD
			for(i=0,j=1;i<(kNbOfAdInput/3);i++,j<<=1)
			{
				// Check if an Input AD Event occured
				if((*aRegAddrl&j)==j)
				{
				*aReg1Addrl|=j;
				gEvents_InputADEventCallBack(i);
				}
			}

			// 32 to 63 Input AD
			for(i=0,j=1;i<(kNbOfAdInput/3);i++,j<<=1)
			{
				// Check if an Input AD Event occured
				if((*aRegAddrm&j)==j)
				{
				*aReg1Addrm|=j;
				gEvents_InputADEventCallBack((u8)(i+32));
				}
			}

			// 64 � 95 Input AD
			for(i=0,j=1;i<(kNbOfAdInput/3);i++,j<<=1)
			{
				// Check if an Input AD Event occured
				if((*aRegAddrh&j)==j)
				{
				*aReg1Addrh|=j;
				gEvents_InputADEventCallBack((u8)(i+64));
				}
			}

			//------------------------------------------------------------
			// Software Input AD Event support
			//------------------------------------------------------------
			// Init des pointeurs
			aRegAddrh=kReceivedSoftwareAdInputh;
			aRegAddrm=kReceivedSoftwareAdInputm;
			aRegAddrl=kReceivedSoftwareAdInputl;
			aReg1Addrh=kReceivedSoftwareAdInput_Ackh;
			aReg1Addrm=kReceivedSoftwareAdInput_Ackm;
			aReg1Addrl=kReceivedSoftwareAdInput_Ackl;

			// 0 � 31 Soft Input AD
			for(i=0,j=1;i<(kNbOfSoftAdInput/3);i++,j<<=1)
			{
				// Check if an Input software AD Event occured
				if((*aRegAddrl&j)==j)
				{
				*aReg1Addrl|=j;
				gEvents_SoftwareInputADEventCallBack(i);
				}
			}

			// 32 � 63 Soft Input AD
			for(i=0,j=1;i<(kNbOfSoftAdInput/3);i++,j<<=1)
			{
				// Check if an Input software AD Event occured
				if((*aRegAddrm&j)==j)
				{
				*aReg1Addrm|=j;
				gEvents_SoftwareInputADEventCallBack((u8)(i+32));
				}
			}

			// 64 � 95 SoftInput AD
			for(i=0,j=1;i<(kNbOfSoftAdInput/3);i++,j<<=1)
			{
				// Check if an Input software AD Event occured
				if((*aRegAddrh&j)==j)
				{
				*aReg1Addrh|=j;
				gEvents_SoftwareInputADEventCallBack((u8)(i+64));
				}
			}
			write(fd, (void *)&reenable, sizeof(int));
			//printf("IRQ6\r\n");
    	}
	// TODO Debug:
	//u8 buf[] = {"IRQ6"};
	//mRs232_SendString(Uart1, buf, 4);
    }

    //--------------------------------------------------------------
    // Name		: swissTiming_IRQ7_handler
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Interrupt handler for:
    //				External UARTs (NOT USED)
    //
    // Parameters	: void* -> Ptr on Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void* swissTiming_IRQ7_handler(void *arg)
    {
	// TODO debug:
	//u8 buf[] = {"IRQ7"};
	//mRs232_SendString(Uart1, buf, 4);
    }

















