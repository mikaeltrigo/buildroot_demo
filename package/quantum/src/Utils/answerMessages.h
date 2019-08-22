/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: answerMessages.h
Author				: Cestele Yves
Date				: 4 juil. 2017
Description			: Answer nbr and size for cmds from PS Sport

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_UTILS_ANSWERMESSAGES_H_
#define SRC_UTILS_ANSWERMESSAGES_H_

//--------------------------------------------------------------
// 			Defines
//--------------------------------------------------------------

    // Error constants:

    #define kInvalidInpNbError               0x00	// Input nbr invalid
    #define kInvalidInpSateError             0x01	// input state invalid
    #define kInvalidCmdLengthError           0x02	// Command length invalid
    #define kInvalidCmd                      0x03	// Command size invalid
    #define kErrorFrameSize                  0x06	// Frame size error
    #define kErrorCmd                 	     0x00	// Error cmd nbr

    // Commands used for the RS232 communication :

    #define kNotArmedInpEventCmd              0x01	// Commande Not Armed Input Event
    #define kNotArmedInpEventFrameSize        10

    #define kSoftInpEventCmd                  0x02	// Commande Software Input Event
    #define kSoftwareInpEventFrameSize        10

    #define kArmedInpEventCmd                 0x02	// Commande Armed Input Event

    #define kRealTimingInputPulse   	      0x00	// Type d'Input pulse
    #define kSoftInputPulse         	      0x01
    #define kArmedInpEventFrameSize           10

    #define kRTEndPeriodCmd                   0x03	// Commande Rolling Time End Period
    #define kRTEndPeriodFrameSize             10

    #define kCustomTriggerCmd                 0x04	// Commande Custom Trigger
    #define kCustomTriggerFrameSize           10

    #define kOutPutEventCmd                   0x05	// Commande Output Event
    #define kOutputEventFrameSize             10

    #define kCurrentDayTimeAnsw               0x06	// Numéro et taille de la réponse Current day time
    #define kCurrentDayTimeAnswSize           0x08

    #define kKeepAliveAnsw                    0x07	// Numéro et taille de la réponse Keep Alive
    #define kKeepAliveAnswSize                0x09

    #define kTcpIpConfAnsw                    0x08	// Numéro et taille de la réponse ask TCP/IP conf
    #define kTcpIpConfAnswSize                19

    #define kSerialParamAnsw                  0x09	// Numéro et taille de la réponse ask Serial Port param
    #define kSerialParamAnswSize              8

    #define kEnDisState32InpAnsw              0x0a	// Numéro et taille de la réponse ask Enable/Disable state of the 32 inputs
    #define kEnDisState32InpAnswSize          7

    #define kEnDisStateAdInpAnsw              0x0b	// Numéro et taille de la réponse ask Enable/Disable state of the 32 outputs
    #define kEnDisStateAdInpSize              15

    #define kArmNotArmed32InpAnsw             0x0c	// Numéro et taille de la réponse ask Armed / Not Armed state of the 32 timing inputs
    #define kArmNotArmed32InpAnswSize         7

    #define kEnDisState32OutAnsw              0x0d	// Numéro et taille de la réponse ask Enable/Disable state of the 32 outputs
    #define kEnDisState32OutAnswSize          7

    #define kState1OutAnsw                    0x0e	// Numéro et taille de la réponse ask one timing output state
    #define kState1OutAnswSize                17

    #define kState1RTAnsw                     0x0f	// Numéro et taille de la réponse ask one rolling time state
    #define kState1RTAnswSize                 15

    #define kInpADEventCmd                    0x10	// Commande Input AD Event
    #define kInpADEventFrameSize              10

    #define kSoftInpADEventCmd                0x10	// Commande Software Input AD Event
    #define kSoftInpADEventFrameSize          10

    #define kDebounceTimeInpAnsw              0x11	// Numéro et taille de la réponse ask Debouncing time for one input
    #define kDebounceTimeInpAnswSize          7

    #define kDebounceTimeStampInpAnsw         0x12	// Numéro et taille de la réponse ask Debouncing time for one time stamp input
    #define kDebounceTimeStampInpAnswSize     6

    #define kSlopeAllInpAnsw                  0x13	// Numéro et taille de la réponse ask active slope for all time stamp inputs
    #define kSlopeAllInpSize                  11

    #define kSlopeAllAdInpAnsw                0x14	// Numéro et taille de la réponse ask active slope for all time stamp inputs
    #define kSlopeAllAdInpSize                27

    #define kCurrentGpsTimeAnsw               0x15	// Numéro et taille de la réponse GPS Time + Timer Time
    #define kCurrentGpsTimeAnswSize           0x0D

    #define kAskPolAllOutAnsw                 0x16	// Numéro et taille de la réponse ask polarity all outputs
    #define kAskPolAllOutSize                 7

    #define kAskGenOutAnsw                    0x17	// Numéro et taille de la réponse ask generic outputs register
    #define kAskGenOutAnsSize                 5

    #define kAskGenInpAnsw                    0x18	// Numéro et taille de la réponse ask generic outputs register
    #define kAskGenInpAnsSize                 5

    #define kGpsSynchroEvent                  0x19	// Gps Synchro frame
    #define kGpsSynchroFrameSize              0x08

    #define kBoardRevAnsw                     0x1A	// Nr and Size of board code frame
    #define kBoardRevAnswSize                 0x09

    #define kAskLevelAllTimingInpAnsw         0x1B	// Numéro et taille de la réponse ask level all timing inp register
    #define kAskLevelAllTimingInpAnsSize      7

    #define kAskLevelAllTimeStampInpAnsw      0x1C	// Numéro et taille de la réponse ask level all time stamp inp register
    #define kAskLevelAllTimeStampInpAnsSize   15

    #define kAuxInputValuesAnsw               0x1D	// Numéro et taille de la réponse Keep Alive
    #define kAuxInputValuesAnswSize           11

    #define kAdValuesAnsw                     0x1E	//Number and size of the Ad values answer
    #define kAdValuesAnswSize                 11

    #define kFpgaAqVersionAnsw                0x1F	//Number and size of the Fpga version AQ answer
    #define kFpgaAqVersionAnswSize            7

    #define kEepromReadAnsw                   0x20	//Number and size of the data in EEprom
    #define kEepromReadAnswSize               32

    #define kFpgaConfigAnsw                   0x21	//Number and size of the Fpga configuration (nb input...)
    #define kFpgaConfigAnswSize               7

    #define kInputActiveDelayCmd              0x22	// State detection at active level
    #define kInputActiveDelayCmdSize          7

    #define kInputInactiveDelayCmd            0x23	// State detection at inactive level
    #define kInputInactiveDelayCmdSize        7

    #define kOROnlyOnePulseCmd                0x24	// Only one pulse received in an OR input pair
    #define kOROnlyOnePulseCmdSize            5


#endif /* SRC_UTILS_ANSWERMESSAGES_H_ */
