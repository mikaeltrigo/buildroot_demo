/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: TimerDef.c
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Description in TimerDef.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "TimerDef.h"
#include "mRs232.h"

u8 gOutputPcSportDestTab[kNbOfOutput];							// Array give which out get on which PC Sport
u8 gRollingTimePcSportDestTab[kNbOfRollingTime];					// Array that give which RT get on which PC Sport
RollingTimeNewDestStruct gRollingTimeNewDestTab[kNbOfRollingTime][kNbOfInput];		// Structure to configure a new rolling time
u8 gRollingTimeTriggerPcSportDestTab[kNbOfRollingTime];					// Array that give which RT get on which PC Sport (trigger)
AllSerialPortFormatStruct gRTAllSerialPortFormat[kNbOfRollingTime];			// Com ports for the rollings times
TimerConfigStruct gTimerConfig;								// Timer configuration
BoardDataStruct gTimerBoardData;							// Timer Board identification
BoardDataStruct gBaseBoardData;								// Interface board identification
AutoPrintModeEnum  gAutoPrintMode = kPrintAllPulses;					// Global value for printing commands

u64  gTime;										// Global values for GPS
u8   gQuality;

u16 gFpgaVersionH1=0;									// Store AQ FPGA version
u16 gFpgaVersionH2=0;

//=========================================================================================================
// Undifine functions recovery:
void undef_function(u8 *aPayload)
{
    static u32 sCpt =0;
    sCpt++;
}
//=========================================================================================================

// Structure that contain informations about PC Sport commands
struct CmdfromPcSportCallBackStruct gCmdfromPcSportCallBack[] =
{
    {0x00,2 ,false,iFpga_EnDisOneTimingInput},        		// Enable or Disable one timing input
    {0x01,4 ,false,iFpga_EnDisAllTimingInput},        		// Enable or Disable all timing inputs
    {0x02,4 ,false,iFpga_DebounceTimeOneTimingInput}, 		// Set debouncing time for one timing input
    {0x03,2 ,false,iFpga_ArmOrDisarmOneTimingInput},  		// Arm or Disarm one timing input
    {0x04,4 ,false,iFpga_ArmOrDisarmAllTimingInput},  		// Arm or Disarm all timing inputs
    {0x05,4 ,false,iFpga_SoftTimingInputPulse},       		// Software timing input pulse --> Ask Timer to simulate an armed pulse on one or more timing input
    {0x06,15,false,mFpga_PrepareSynch},               		// Prepare synchronization --> Program the day time synchronization at the next valid armed timing input pulse
    {0x07,14,false,iFpga_PrepareOneTimingOutput},    		// Prepare one timing Output --> Program the day time synchronization at the next valid armed timing input pulse
    {0x08,2 ,false,iFpga_EnDisOneTimingOutput},       		// Enable or Disable one timing Output
    {0x09,4 ,false,iFpga_EnDisAllTimingOutput},       		// Enable or Disable all timing Output
    {0x0a,17,false,iFpga_NewRollingTime},            		// New Rolling Time
    {0x0b,7,false,iFpga_RollingTimeNewDest},         		// Rolling Time new Destination
    {0x0c,3 ,false,iFpga_RollingTimeNewState},        		// Rolling Time new State
    {0x0d,5 ,false,iFpga_RollingTimeNewInter},        		// Rolling Time new Interval
    {0x0e,11,false,iFpga_RollingTimeNewCustomTrig},  		// Rolling Time new Custom Trigger
    {0x0f,0 ,false,mRs232_AskDayTime},        			// Get Day Time
    {0x10,0 ,false,mRs232_KeepAlive},        			// Keep Alive
    //{0x11,6 ,false,mI2cEEprom_ConfigMacAddr},      		// Configure the MAC Address
    {0x11,6 ,false,undef_function},

    //{0x12,12,false,mI2cEEprom_ConfigTcp},        	 	// Configure the TCP/IP connexion
    {0x12,12,false,undef_function},

    {0x13,0 ,false,mRs232_AskTcpParam},   			// Ask TCP/IP Configuration
    //{0x14,1 ,false,mI2cEEprom_SelectCommProtocol}, 		// Select communication protocol
    {0x14,1 ,false,undef_function},

    //{0x15,5 ,false,mI2cEEprom_ConfigSerialParam},		// Select Serial port Parameters
    {0x15,5 ,false,undef_function},

    {0x16,1 ,false,mRs232_AskSerialParam}, 			// Ask Serial port Parameters
    {0x17,0 ,false,mRs232_AskEnDisStateAllTimingInp}, 		// Ask Enable / Disable state of the 32 timing inputs
    {0x18,0 ,false,mRs232_AskEnDisStateAllTimeStampInp},  	// Ask Enable / Disable state of the 96 time stamp inputs
    {0x19,0 ,false,mRs232_AskArmDisarmStateAllTimingInp}, 	// Ask Arm / Disarm state of the 32 timing inputs
    {0x1a,0 ,false,mRs232_AskEnDisStateAllTimingOut},     	// Ask Enable / Disable state of the 32 timing outputs
    {0x1b,1 ,false,mRs232_AskOneTimingOutState},    		// Ask one timing output current state
    {0x1c,1 ,false,mRs232_AskOneRTState},       		// Ask one of the 16 rolling time current state
    {0x1d,2 ,false,iFpga_EnDisOneTimeStampInp},       		// Enable / Disable one time stamp Input
    {0x1e,12,false,iFpga_EnDisAllTimeStampInp},       		// Enable / Disable all 96 time stamp inputs
    {0x1f,3 ,false,iFpga_SetDebounceAllTimeStampInp}, 		// Set debouncing time for one time stamp input
    {0x20,1 ,false,mRs232_AskDebounceOneTimingInp},   		// Ask Debouncing time for one timing input
    {0x21,0 ,false,mRs232_AskDebounceAllTimeStampInp},		// Ask Debouncing time for all time stamp input
    {0x22,12,false,iFpga_SoftTimeStampInputPulse},    		// Software time stamp input Pulse
    {0x23,5 ,false,iFpga_SelActSlopeAllTimeInp},   		// Select active slope for all timing inputs
    {0x24,13,false,iFpga_SelActSlopeAllTimeStampInp}, 		// Select active slope for all time stamp inputs
    {0x25,0 ,false,mRs232_AskActiveSlopeAllTimingInp},      	// Ask active slope for all timing inputs
    {0x26,0 ,false,mRs232_AskActiveSlopeAllTimeStampInp},   	// Ask active slope for all time stamp inputs
    {0x27,0 ,true,iFpga_RollingTimeNewSerial},       		// Rolling Time new serial port destination
    //{0x28,0 ,true,mRs232_SendMsgOnSerialPort},        		// Send a message on an other serial port
    {0x28,0 ,true,undef_function},

    {0x29,4 ,false,iFpga_ResetSeveralOutput},			// Reset several outputs
    {0x2a,4 ,false,iFpga_SetPolarityAllOutputs},		// Set polarity for all Outputs
    {0x2b,2 ,false,iFpga_SetGenericOutputsReg},			// Set generic outputs register
    {0x2c,0 ,false,mRs232_AskPolarityAllOutputs},		// Ask Polarity All Outputs
    {0x2d,0 ,false,mRs232_AskGenericOutputsReg},		// Ask generic outputs register
    {0x2e,0 ,false,mRs232_AskGenericInputsReg},			// Ask generic inputs register
    {0x2f,3 ,false,iFpga_RollingClearWaitInput},		// Rolling Time Clear Wait Input
    {0x30,4 ,false,iFpga_ResetFpga},				// Reset de la FPGA
    //{0x31,4 ,false,mI2cEEprom_ResetEEpromdefault},	      	// Reset eeprom to default
    {0x31,4 ,false,undef_function},

    {0x32,0 ,false,mRs232_AskLevelAllTimingInp},	      	// Ask Level all timing input
    {0x33,0 ,false,mRs232_AskLevelAllTimeStampInp},		// Ask Level all time stamp input
    //{0x34,2 ,false,iFpga_SetCommModeRouting},			// SerialPortRouting
    {0x34,2 ,false,undef_function},

    //{0x35,3 ,false,mI2cEEprom_WriteOtherBoardEEprom},     	// Write data to Interface and IO board EEprom
    {0x35,3 ,false,undef_function},

    {0x36,0 ,false,mRs232_GetBoardsVersion},              	// Return boards version values
    {0x37,1 ,false,mRs232_SetAutoPrintMode},              	// Set auto print pulse mode
    {0x38,0 ,false,mRs232_GetAdValues},                   	// Get AD values
    //{0x39,1 ,false,mSpi_EnDisHarnetStatus},               	// Enable/disable harnet status
    {0x39,1 ,false,undef_function},

    {0x3a,0 ,false,mRs232_GetFpgaVersionAQ},              	// Get FPGA version (AQ hardware)
    //{0x3b,4 ,false,mI2cEEprom_BootLoaderMode},            	// SetBoot mode
    {0x3b,4 ,false,undef_function},

    {0x3c,1 ,false,mRs232_Set24HoursMode},                	// Set 24 hours mode
    //{0x3d,35,false,mI2cEEprom_EepromAccess},              	// Write in EEprom
    {0x3d,35,false,undef_function},

    {0x3e,2,false,mRs232_GetEEpromData},                  	// Read in EEprom
    {0x3f,6, false, iFpga_RollingTimeNewSerialBin},       	// Send rolling time binary with bib number
    {0x40,0, false, mRs232_GetFpgaConfig},                	// Return Quantum FPGA configuration (Std / Mini Quantum)
    {0x41,2, false, mRs232_SetGpsProtocol},               	// Set Gps protocol type
    {0x42,2, false, iFpga_LogicalOrOnInput},              	// Enable/Disable logical OR on input
    {0x43,2, false, iFpga_LogicalAndOnInput},             	// Enable/Disable logical AND on input
    {0x44,2, false, iFpga_StateDetectionDelay},           	// Configure state detection for all input
    {0x45,5, false, iFPga_EnableDisableStateDetection},   	// Enable/Disable state detection on input
    {0xff,0 ,false,(void *)0}					// Fin du tableau
};


//--------------------------------------------------------------
// 				FUNCTIONS
//--------------------------------------------------------------
