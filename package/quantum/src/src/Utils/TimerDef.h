/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: TimerDef.h
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Definition of variables used in all the
				  program

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_TIMERDEF_H_
#define SRC_TIMERDEF_H_

//--------------------------------------------------------------
// 		INCLUDES & DEFINES
//--------------------------------------------------------------
#include "utils.h"
#include "xil_types.h"
#include "iFPGA.h"
#include "FPGA_Registers.h"
#include "mFPGA.h"

//--------------------------------------------------------------
// 		STRUCTURES AND EXTERNALISATIONS
//--------------------------------------------------------------
    // Board informations
    typedef struct
    {
	u32 Tag;
	u8  Size;
	u8  TypeBoard;
	u8  Revision;
    }BoardDataStruct;

    extern BoardDataStruct gTimerBoardData;
    extern BoardDataStruct gBaseBoardData;

    // Protocols enumeration
    typedef enum
    {
	kSerialLinePro=0,
	kUsbPro=1,
	kTcpPro=2
    }ProtocolEnum;

    // Configuration for serial port
    typedef enum
    {
	kSportPC=0,		// PS UartPS 0
	kPeripheral1=3,		// PS UartPS 1
	kPeripheral2=4,		// PL UartLite 0
	kPrinter=2,		// PL UartLite 1
	kGPS=1, 		// PL UartLite 2
	kPeripheral3=5,		// PL UartLite 3
	kPeripheral4=6,		// PL UartLite 4
	kPeripheral5=7,
	kLastPeriph = (kPeripheral5 + 1)
    }SerialPortEnum;

    typedef enum
    {
	k1200Bauds=0,
	k2400Bauds=1,
	k4800Bauds=2,
	k9600Bauds=3,
	k19200Bauds=4,
	k38400Bauds=5,
	k57600Bauds=6,
	k115200Bauds=7
    }SerialSpeedEnum;

    typedef enum
    {
	k7DataBits=7,
	k8DataBits=8
    }DataBitsEnum;

    typedef enum
    {
	k1StopBit=1,
	k2StopBit=2
    }StopBitsEnum;

    typedef enum
    {
	kNoParity=0,
	EvenParity=1,
	kOddParity=2
    }ParityEnum;

    typedef struct
    {
	SerialSpeedEnum SerialSpeed;
	DataBitsEnum DataBits;
	StopBitsEnum StopBits;
	ParityEnum Parity;
    }SerialConfigEnum;

    // Give the informations about the timer
    typedef struct
    {
	u32 Tag;
	u8  FpgaMainVer;			// Programmable Logic Version (main)
	u8  FpgaSubVer;				// Programmable Logic Version (sub)
	u8  FirmwareMainVer;			// Embedded Software Version (main)
	u8  FirmwareSubVer;			// Embedded Software Version (sub)
	SerialPortEnum  PcSportSerialNb;	// Serial Port used for the PC Sport
	ProtocolEnum Protocol;			// Which protocole is used for the communication
	SerialConfigEnum SerialTab[7];
    }TimerConfigStruct;
    extern TimerConfigStruct gTimerConfig;


    // Frame structure of a PCSport command
    #define kPayloadSize	((u8)(2000))
    typedef struct
    {
      u8   Cmd;
      u8   Payload[kPayloadSize];
      u16  PayloadSize;
      u8   PayloadIndex;
      u32  ErrorCounter;
    }FrameStruct;

    // Structure that contain infos about command PC Sport
    struct CmdfromPcSportCallBackStruct
    {
	u8 Cmd;
	u8 PayloadSize;
	bool  VariableLengh;
	void (* Callback)(u8 *PayLoad);
    };
    extern struct CmdfromPcSportCallBackStruct gCmdfromPcSportCallBack[];

    extern u8 gOutputPcSportDestTab[kNbOfOutput];				// Array give which out get on which Uart
    extern u8 gRollingTimePcSportDestTab[kNbOfRollingTime];			// Array that give which RT get on which PC Sport
    extern u8 gRollingTimeTriggerPcSportDestTab[kNbOfRollingTime];		// Array that give which RT get on which PC Sport (trigger)
    extern u16 gFpgaVersionH1;						// Store AQ FPGA version
    extern u16 gFpgaVersionH2;

    typedef struct								// Structure to configure a new rolling time
    {
	u16 PCSportAddr;
	u32 OutPutMask;
	bool   IsNew;
    }RollingTimeNewDestStruct;

    extern RollingTimeNewDestStruct gRollingTimeNewDestTab[kNbOfRollingTime][kNbOfInput];

    //------------------------------------------------------------
    // COM ports used for the Rollings Times RS422
    //------------------------------------------------------------
    #define kStartOfFrame		0x01
    #define kEndOfFrame   		0x00
    #define kRTLengh 			255
    #define kNbOfPeriphSerialPort 	8
    #define kNbOfSerialPort 		7
    #define kCodedBinaryBuffer 		100
    #define kCodedAsciiMessage 		50

    // Format type
    typedef struct
    {
	u8 Format[kRTLengh];	// Format du RT à transmettre
	u8 State;			// Etat: 1-> transmettre
	u8 HeaderLen;
	u8 FooterLen;

	//Hours
	u16 HourLen;

	//Minutes
	u16 MinLen;

	// Time seperator
	u8 TimeSep;

	// Seconds
	u16 SecLen;

	// Seconds divider for seconds only mode
	u16 SecModulo;

	// Decimal
	u8 DecSeparator;
	u16 DecLen;
	u8 FloatingSign;

	bool ModeSeconds;

	u8 NumberHigh; // Code transmitted with the RT binary frame (ex: bib number)
	u8 NumberLow;

	u8 RtIdentifier; // User data, can be used to identify a running time
	                    // for example : 1 = Race time, 2 = Gap time
    }OneSerialPortFormatStruct;

    // Tableau des formats des 7 port série
    typedef struct
    {
	OneSerialPortFormatStruct SerialPortFormatTab[kNbOfPeriphSerialPort];
    }AllSerialPortFormatStruct;

    // Tableau des formats des 7 ports série pour les 16 RT
    extern AllSerialPortFormatStruct gRTAllSerialPortFormat[kNbOfRollingTime];

    // Global values for printing commands
    typedef enum
    {
      kPrintNothing =        0x00,
      kPrintArmedPulses =    0x01,
      kPrintNotArmedPulses = 0x02,
      kPrintAllPulses =      0x03
    }AutoPrintModeEnum;
    extern AutoPrintModeEnum  gAutoPrintMode;

    //------------------------------------------------------------
    // Internal pulse buffer structure
    //------------------------------------------------------------
    // Kinf of pulse
    typedef enum
    {
        kArmedPulse,
        kNotArmedPulse,
        kAddPulse,
        kAddSoftPulse
    }PulseTypeEnum;

    typedef struct
    {
        u8 PulseNr;            		// Pulse number
        u64 PulseTime;         		// Pulse time
        PulseTypeEnum PulseType;  	// Pulse type (armed/notarmed)
    }PulseBufferStruct;


    #define kMaxLineSize 1024		// Line Buffer generic structure
    typedef struct			// LineBuffer Structure for printer
    {
        u16 LineSize;
        u8  LineBuffer[kMaxLineSize];
    }LineBufferStruct;

    //------------------------------------------------------------
    // Global values for GPS
    //------------------------------------------------------------
    extern u64  gTime;
    extern u8   gQuality;

#endif /* SRC_TIMERDEF_H_ */
