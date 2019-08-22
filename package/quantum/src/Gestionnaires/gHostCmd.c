/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gHostCmd.c
Author				: Cestele Yves
Date				: 28 juin 2019
Description			: Description in gHostCmd.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "gHostCmd.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "stdio.h"
#include<pthread.h>
#include "event.h"
#include "semaphore.h"

//--------------------------------------------------------------
// 				VARIABLES
//--------------------------------------------------------------
static volatile FrameStruct 	sFramesBuffer[kSizeBufferFrame];
static u8		sBufferIndexUP =0;
static u8		sBufferIndexDOWN =0;
static u16 		sCmdTabSize=0;				// Size of the commands table

void* handler_uart0_interrupts(void *arg);

struct FrameCallBackStruct
{
    u8 Cmd;
    void (* Callback)(FrameStruct *aFrame);
    bool TestInp;
    bool TestState;
};

//=========================================================================================================
// Undifine functions recovery:
void mI2cEEprom_CmdExecute(FrameStruct *aFrameStruct)
{

}

// FIXME these functions have to be moved in module:
int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars

        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing

        tty.c_lflag &= ~ICANON;                // no signaling chars, no echo,
        tty.c_lflag = 0x00;

        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 1;            // read block
        tty.c_cc[VTIME] = 0;

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        // set raw mode:
        tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                        | INLCR | IGNCR | ICRNL | IXON);
        tty.c_oflag &= ~OPOST;
        tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        tty.c_cflag &= ~(CSIZE | PARENB);
        tty.c_cflag |= CS8;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf("error %d setting term attributes", errno);
}


//--------------------------------------------------------------
// Structure that give which command run which program
//--------------------------------------------------------------
struct FrameCallBackStruct sFrameCallBack[] =
{
    {0x00,mHostCmd_CmdExecute,true,true}, 	// Commands from Sport PC 	--> Enable or Disable one timing input
    {0x01,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Enable or Disable all timing inputs
    {0x02,mHostCmd_CmdExecute,true,false}, 	// Commands from Sport PC 	--> Set debouncing time for one timing input
    {0x03,mHostCmd_CmdExecute,true,true}, 	// Commands from Sport PC 	--> Arm or Disarm one timing input
    {0x04,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Arm or Disarm all timing inputs
    {0x05,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Software timing input pulse --> Ask Timer to simulate an armed pulse on one or more timing input
    {0x06,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Prepare synchronization --> Program the day time synchronization at the next valid armed timing input pulse
    {0x07,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Prepare one timing Output --> Program the day time synchronization at the next valid armed timing input pulse
    {0x08,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Enable or Disable one timing Output
    {0x09,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Enable or Disable all timing Output
    {0x0A,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> New Rolling Time
    {0x0B,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Rolling Time new Destination
    {0x0C,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Rolling Time new State
    {0x0D,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Rolling Time new Interval
    {0x0E,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Rolling Time new Custom Trigger
    {0x0F,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Get Day Time
    {0x10,mRs232_CmdExecute,false,false},    	// PC Request to Timer 	  	--> Keep Alive
    {0x11,mI2cEEprom_CmdExecute,false,false},	// Configuration		--> Configure the MAC Address
    {0x12,mI2cEEprom_CmdExecute,false,false},	// Configuration		--> Configure the TCP/IP connexion
    {0x13,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask TCP/IP Configuration
    {0x14,mI2cEEprom_CmdExecute,false,false},	// Configuration		--> Select communication protocol
    {0x15,mI2cEEprom_CmdExecute,false,false},	// Configuration		--> Select Serial port Parameters
    {0x16,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Serial port Parameters
    {0x17,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Enable / Disable state of the 32 timing inputs
    {0x18,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Enable / Disable state of the 96 time stamp inputs
    {0x19,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Arm / Disarm state of the 32 timing inputs
    {0x1a,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Enable / Disable state of the 32 timing outputs
    {0x1b,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask one timing output current state
    {0x1c,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask one of the 16 rolling time current state
    {0x1d,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Enable / Disable one time stamp Input
    {0x1e,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Enable / Disable all 96 time stamp inputs
    {0x1f,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Set debouncing time for one time stamp input
    {0x20,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Debouncing time for one timing input
    {0x21,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask Debouncing time for one time stamp input
    {0x22,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Software time stamp input Pulse
    {0x23,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Select active slope for all timing inputs
    {0x24,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Select active slope for all time stamp inputs
    {0x25,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask active slope for all timing inputs
    {0x26,mRs232_CmdExecute,false,false},   	// PC Request to Timer 		--> Ask active slope for all time stamp inputs
    {0x27,mHostCmd_CmdExecute,false,false}, 	// Commands from Sport PC 	--> Rolling Time new serial port destination
    {0x28,mRs232_CmdExecute,false,false},  	// PC Request to Timer 		--> Send a messge on a serial port
    {0x29,mHostCmd_CmdExecute,false,false},  	// Commands from Sport PC 	--> Reset several outputs
    {0x2a,mHostCmd_CmdExecute,false,false},  	// Commands from Sport PC 	--> Set polarity all outputs
    {0x2b,mHostCmd_CmdExecute,false,false},  	// Commands from Sport PC 	--> Set generic outputs registers
    {0x2c,mRs232_CmdExecute,false,false},  	// PC Request to Timer 		--> Ask Polarity All Outputs
    {0x2d,mRs232_CmdExecute,false,false},  	// PC Request to Timer 		--> Ask generic outputs register
    {0x2e,mRs232_CmdExecute,false,false},  	// PC Request to Timer 		--> Ask generic inputs register
    {0x2f,mHostCmd_CmdExecute,false,false},  	// Commands from Sport PC 	--> Rolling Time Clear Wait Input
    {0x30,mHostCmd_CmdExecute,false,false},  	// Commands from Sport PC 	--> Reset FPGA
    {0x31,mRs232_CmdExecute,false,false},	// PC Request to Timer 		--> Reset eeprom to default
    {0x32,mRs232_CmdExecute,false,false},	// PC Request to Timer 		-->Ask Level all timing input
    {0x33,mRs232_CmdExecute,false,false},	// PC Request to Timer 		-->Ask Level all time stamp input
    {0x34,mRs232_CmdExecute,false,false},	// Set Serial Routing mode
    {0x35,mI2cEEprom_CmdExecute,false,false},   // Write data to Interface and IO board EEprom
    {0x36,mRs232_CmdExecute,false,false},       // Return boards version values
    {0x37,mRs232_CmdExecute,false,false},       // Set auto print pulse modes
    {0x38,mRs232_CmdExecute,false,false},       // Get AD values
    {0x39,mHostCmd_CmdExecute,false,false},     // Enable/disable harnet status
    {0x3a,mRs232_CmdExecute,false,false},       // Get FPGA version (AQ hardware)
    {0x3b,mI2cEEprom_CmdExecute,false,false},   // SetBoot mode
    {0x3c,mRs232_CmdExecute,false,false},       // Set 24 hours mode
    {0x3d,mI2cEEprom_CmdExecute,false,false},   // Write in EEprom
    {0x3e,mRs232_CmdExecute,false,false},       // Read in EEprom
    {0x3f,mHostCmd_CmdExecute,false,false},     // Binary rolling time on serial port
    {0x40,mRs232_CmdExecute,false,false},       // Return Quantum FPGA configuration (Std / Mini Quantum)
    {0x41,mRs232_CmdExecute,false,false},       // Set Gps protocol type
    {0x42,mHostCmd_CmdExecute,false,false},     // Enable/Disable logical OR on input
    {0x43,mHostCmd_CmdExecute,false,false},     // Enable/Disable logical AND on input
    {0x44,mHostCmd_CmdExecute,false,false},     // Configure state detection for all input
    {0x45,mHostCmd_CmdExecute, false, false},   // Enable/Disable state detection on input
    {0xff,(void *) 0,false,false}  		// Rien --> fin du tableau
};

//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: gEvent_incBufferIndex
    // Author		: Cestele Yves
    // Date		: 28 juin 2019
    // Descritpion	: Function to increment the buffers
    //			  indexs of the rotate buffer
    //
    // Parameters	: u8*
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    static __inline void gHostCmd_incBufferIndex(u8 *aToInc)
    {

	    if(*aToInc >= kSizeBufferFrame)
	    {
		(*aToInc)=0;
	    }
	    else
	    {
		(*aToInc)++;
	    }
    }

    //--------------------------------------------------------------
    // Name		: gHostCmd_Setup
    // Author		: Cestele Yves
    // Date		: 28 juin 2019
    // Descritpion	: Setup of the gHostCmd
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gHostCmd_Setup(void)
    {

        int err;
        pthread_t tIdUart1;

		err = pthread_create(&(tIdUart1), NULL, &handler_uart0_interrupts, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread UART1:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread UART1 created successfully\n");
		}

		// Interrupt 1:
        pthread_t tIdInt1;

		err = pthread_create(&(tIdInt1), NULL, &swissTiming_IRQ1_handler, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread INT1:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread INT1 created successfully\n");
		}

		// Interrupt 2:
        pthread_t tIdInt2;

		err = pthread_create(&(tIdInt2), NULL, &swissTiming_IRQ2_handler, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread INT2:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread INT2 created successfully\n");
		}

		// Interrupt 3:
        pthread_t tIdInt3;

		err = pthread_create(&(tIdInt3), NULL, &swissTiming_IRQ3_handler, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread INT3:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread INT3 created successfully\n");
		}

		// Interrupt 4:
        pthread_t tIdInt4;

		err = pthread_create(&(tIdInt4), NULL, &swissTiming_IRQ4_handler, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread INT4:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread INT4 created successfully\n");
		}

		// Interrupt 5:
        pthread_t tIdInt5;

		err = pthread_create(&(tIdInt5), NULL, &swissTiming_IRQ5_handler, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread INT5:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread INT5 created successfully\n");
		}

		// Interrupt 6:
        pthread_t tIdInt6;

		err = pthread_create(&(tIdInt6), NULL, &swissTiming_IRQ6_handler, NULL);
		if (err != 0)
		{
			printf("\ncan't create thread INT6:[%s]", strerror(err));
		}
		else
		{
			printf("\n Thread INT6 created successfully\n");
		}

	u16 i;
	u16 j;

	// Count the number of commands availible in the tab
	// to avoid to run a bad address
	for(i=0;sFrameCallBack[i].Cmd!=0xFF;i++){}
	for(j=0;gCmdfromPcSportCallBack[j].Cmd!=0xFF;j++){}

	sCmdTabSize=i-1;
    }

    //--------------------------------------------------------------
    // Name		: gHostCmd_Setup
    // Author		: Cestele Yves
    // Date		: 28 juin 2019
    // Descritpion	: gHostCmd function (Run the PC Sport cmds)
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gHostCmd_Execute(void)
    {
	//sem_wait(QUANTUM_EVENT_PC_SPORT_MSG_AVAILABLE);

		while(sBufferIndexUP!=sBufferIndexDOWN)
		{
			if(sFramesBuffer[sBufferIndexDOWN].Cmd<=0x45)
			{
				sFrameCallBack[(sFramesBuffer[sBufferIndexDOWN].Cmd)].Callback(&sFramesBuffer[sBufferIndexDOWN]);
			}
			// Increment the Buffer's index
			gHostCmd_incBufferIndex(&sBufferIndexDOWN);
		}
    }

//--------------------------------------------------------------
// 			Functions for Interrupts
//--------------------------------------------------------------

//    //--------------------------------------------------------------
//    // Name		: _handle_uart0_interrupt
//    // Author		: Cestele Yves
//    // Date		: 23 juin 2019
//    // Descritpion	:
//    //
//    // Parameters	: CallBackRef 	: Element which call the function
//    //			  Event		: Event that occurred
//    //			  EventData	: Datas
//    //
//    // Return		: void
//    //
//    // Modification	:
//    //--------------------------------------------------------------
//    void handler_uart0_interrupts(void *CallBackRef, u32 Event, u32 EventData)
//    {
//	/* All of the data has been sent */
//	if (Event == XUARTPS_EVENT_SENT_DATA) {
//	    __asm("nop");
//
//	}
//
//	/* All of the data has been received */
//	if (Event == XUARTPS_EVENT_RECV_DATA)
//	{
//
//	    static enumStateCmdPCSport sState =kWaitStartByte;
//	    static u8 sBuf[100];
//	    static u8 sIndex =0;
//
//
//	    // Read 1 byte:
//	    u8 aData = mRs232_ReadByte(Uart0);
//
//	    switch(sState)
//	    {
//		case kWaitStartByte:
//		    if(aData==0x01)
//		    {
//			sIndex=0;
//			sBuf[sIndex++] = aData;
//			sState = kCapturePayload;
//		    }
//		    break;
//
//		case kCapturePayload:
//		    if(aData==0x00)		// End Frame detected
//		    {
//			sBuf[sIndex++] = aData;
//			static u8 sBufDecoded[100];
//			DecodeFrame(sBuf, sIndex, sBufDecoded);
//
//			// Copy the datas in Frames FIFO:
//			sFramesBuffer[sBufferIndexUP].Cmd = sBufDecoded[0];
//			sFramesBuffer[sBufferIndexUP].PayloadSize = sIndex-3;			// -3 because start & stop are removed and first byte is for the command
//
//			u8 i = 0;
//			s8 aBoucle = sIndex-3;
//			if(aBoucle<0)
//			{
//			    sFramesBuffer[sBufferIndexUP].PayloadSize=0;
//			    aBoucle=0;
//			}
//			for(i=0;i<aBoucle;i++)
//			{
//			    sFramesBuffer[sBufferIndexUP].Payload[i] = sBufDecoded[i+1];
//			}
//
//			gHostCmd_incBufferIndex(&sBufferIndexUP);
//
//			// For Debug (check if each command is received)
////			u8 aOK[] = {"OK"};
////			mRs232_SendString(Uart1, aOK, 2);
//
//			sIndex=0;
//			sState = kWaitStartByte;
//		    }
//		    else if(aData==0x01)	// Start a Frame detected without a end
//		    {
//			sIndex=0;
//			sBuf[sIndex++] = aData;
//		    }
//		    else
//		    {
//			sBuf[sIndex++] = aData;
//		    }
//		    break;
//		default:
//		    break;
//	    }
//	}
//    }
//
//    //--------------------------------------------------------------
//    // Name		: _handle_uart1_interrupt
//    // Author		: Cestele Yves
//    // Date		: 23 juin 2019
//    // Descritpion	:
//    //
//    // Parameters	: CallBackRef 	: Element wich call the function
//    //			  Event		: Event that occurred
//    //			  EventData	: Datas
//    //
//    // Return		: void
//    //
//    // Modification	:
//    //--------------------------------------------------------------
//    void handler_uart1_interrupts(void *CallBackRef, u32 Event, u32 EventData)
//    {
//
//	//XUartPs *UartInstPtr = CallBackRef;
//
//	/* All of the data has been sent */
//	if (Event == XUARTPS_EVENT_SENT_DATA) {
//
//	}
//
//	/* All of the data has been received */
//	if (Event == XUARTPS_EVENT_RECV_DATA)
//	{
//	    static enumStateCmdPCSport sState =kWaitStartByte;
//	    static u8 sBuf[100];
//	    static u8 sIndex =0;
//
//	    // Read 1 byte:
//	    u8 aData = mRs232_ReadByte(Uart1);
//
//	    switch(sState)
//	    {
//		case kWaitStartByte:
//		    if(aData==0x01)
//		    {
//			sIndex=0;
//			sBuf[sIndex++] = aData;
//			sState = kCapturePayload;
//		    }
//		    break;
//
//		case kCapturePayload:
//		    if(aData==0x00)		// End Frame detected
//		    {
//			sBuf[sIndex++] = aData;
//
//			u8 aBuf1[100];
//			DecodeFrame(sBuf, sIndex, aBuf1);
//
//			int i=sIndex-1;
//			for(i=sIndex-1;i>0;i--)
//			{
//			    aBuf1[i] = aBuf1[i-1];
//			}
//			aBuf1[0] = 0x01;
//			aBuf1[sIndex-1]=0x00;
//
//			//u8 aSizeCoded = BuildCodedFrame(aBuf1, sBuf, aSizeUncoded+2);
//			//mRs232_SendString(Uart1, sBuf, aSizeCoded);
//			sIndex=0;
//			sState = kWaitStartByte;
//		    }
//		    else if(aData==0x01)	// Start a Frame detected without a end
//		    {
//			sIndex=0;
//			sBuf[sIndex++] = aData;
//		    }
//		    else
//		    {
//			sBuf[sIndex++] = aData;
//		    }
//		    break;
//		default:
//		    break;
//	    }
//	}
//
//	if (Event == XUARTPS_EVENT_RECV_TOUT) {
//
//	}
//    }


//--------------------------------------------------------------
// Name		: _handle_uart0_interrupt
// Author		: Cestele Yves
// Date		: 23 juin 2019
// Descritpion	:
//
// Parameters	: CallBackRef 	: Element which call the function
//			  Event		: Event that occurred
//			  EventData	: Datas
//
// Return		: void
//
// Modification	:
//--------------------------------------------------------------
void* handler_uart0_interrupts(void *arg)
{

	static enumStateCmdPCSport sState =kWaitStartByte;
	static u8 sBuf[100];
	static u8 sIndex =0;
	static char buf [100];

//	//======================================================================
//	//TX
//	char *portnameTx = "/tmp/txQuantum";
//
//	int fdTx = open (portnameTx, O_WRONLY);
//	if (fdTx < 0)
//	{
//	    printf("error %d opening %s: %s", errno, portnameTx, strerror (errno));
//	    return NULL;
//	}
//
//	mRs232_SetFDFORTEST(fdTx);
//
//	//======================================================================
//	//RX
//	char *portnameRx = "/tmp/rxQuantum";//"/dev/ttyUL2";
//
//
//	int fdRx = open (portnameRx, O_RDONLY);
//	if (fdRx < 0)
//	{
//	    printf("error %d opening %s: %s", errno, portnameRx, strerror (errno));
//	    return NULL;
//	}

//	//======================================================================
//	//FOR test ONLY -> has to be moved in a special task FIXME
//	char *portnamePrinter = "/tmp/printerQuantum";
//
//	int fdPrinter = open (portnamePrinter, O_WRONLY);
//	if (fdPrinter < 0)
//	{
//	    printf("error %d opening %s: %s", errno, portnamePrinter, strerror (errno));
//	    return NULL;
//	}
//
//	mRs232_SetFDFORTESTPrinter(fdPrinter);

//	//======================================================================
//	//FOR test ONLY -> has to be moved in a special task FIXME
//	char *portnameRolling = "/tmp/rollingQuantum";
//
//	int fdRolling = open (portnameRolling, O_WRONLY);
//	if (fdRolling < 0)
//	{
//	    printf("error %d opening %s: %s", errno, portnameRolling, strerror (errno));
//	    return NULL;
//	}
//
//	mRs232_SetFDFORTESTRollingTime(fdRolling);

//	char *portnamePrinter = "/dev/ttyUL0";
//	int fdPrinter = open (portnamePrinter, O_RDWR | O_NOCTTY | O_SYNC);
//	if (fd < 0)
//	{
//			printf("error %d opening %s: %s", errno, portname, strerror (errno));
//			return NULL;
//	}
//
//	set_interface_attribs(fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
//	mRs232_SetFDFORTESTPrinter(fdPrinter);

	//======================================================================
	//UART
	char *portname = "/dev/ttyUL2";

	int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0)
	{
	    printf("error %d opening %s: %s", errno, portname, strerror (errno));
	    return NULL;
	}

	set_interface_attribs(fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	mRs232_SetFDFORTEST(fd);

	for(;;)
	{
		// Read 1 byte:
//		read(fdRx, buf, 1);
		read(fd, buf, 1);

		u8 aData = buf[0];

		switch(sState)
		{
		case kWaitStartByte:
			if(aData==0x01)
			{
			sIndex=0;
			sBuf[sIndex++] = aData;
			sState = kCapturePayload;
			}
			break;

		case kCapturePayload:
			if(aData==0x00)		// End Frame detected
			{
				sBuf[sIndex++] = aData;
				static u8 sBufDecoded[100];
				DecodeFrame(sBuf, sIndex, sBufDecoded);

				// Copy the datas in Frames FIFO:
				sFramesBuffer[sBufferIndexUP].Cmd = sBufDecoded[0];
				sFramesBuffer[sBufferIndexUP].PayloadSize = sIndex-3;			// -3 because start & stop are removed and first byte is for the command

				u8 i = 0;
				s8 aBoucle = sIndex-3;
				if(aBoucle<0)
				{
					sFramesBuffer[sBufferIndexUP].PayloadSize=0;
					aBoucle=0;
				}
				for(i=0;i<aBoucle;i++)
				{
					sFramesBuffer[sBufferIndexUP].Payload[i] = sBufDecoded[i+1];
				}

				gHostCmd_incBufferIndex(&sBufferIndexUP);

				sIndex=0;
				sState = kWaitStartByte;

				sem_post(QUANTUM_EVENT_PC_SPORT_MSG_AVAILABLE);
			}
			else if(aData==0x01)	// Start a Frame detected without a end
			{
				sIndex=0;
				sBuf[sIndex++] = aData;
			}
			else
			{
				sBuf[sIndex++] = aData;
			}
			break;
		default:
			break;
		}
	}
}

    //--------------------------------------------------------------
    // Name		: UartLite0SendHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite0SendHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite0RecvHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite0RecvHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite1SendHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite1SendHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite1RecvHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite1RecvHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite2SendHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite2SendHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite2RecvHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite2RecvHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite3SendHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite3SendHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite3RecvHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite3RecvHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite4SendHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite4SendHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite4RecvHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite4RecvHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite5SendHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite5SendHandler(void *CallBackRef, unsigned int EventData)
    {

    }

    //--------------------------------------------------------------
    // Name		: UartLite5RecvHandler
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: void*, unsigned int
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void UartLite5RecvHandler(void *CallBackRef, unsigned int EventData)
    {

    }
