/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: iFPGA.h
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Commands to update the FPGA registers

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_INTERFACES_IFPGA_H_
#define SRC_INTERFACES_IFPGA_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "utils.h"
#include "TimerDef.h"
#include "FPGA_Registers.h"
//#include "xil_misc_psreset_api.h"

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: iFpga_EnDisOneTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: En/Dis able Input nb x
    //
    // Parameters	: u8* -> Payload with [num input][En/dis]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisOneTimingInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_EnDisAllTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: En/Dis able Timing Inputs
    //
    // Parameters	: u8* -> Payload with
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisAllTimingInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_DebounceTimeOneTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: Debpunce input pulse
    //
    // Parameters	: u8* payload with -> [inp nb][debTime[3]]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_DebounceTimeOneTimingInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_ArmOrDisarmOneTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: A(UN)rmed input x
    //
    // Parameters	: u8* -> payload with [inp nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_ArmOrDisarmOneTimingInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_ArmOrDisarmAllTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: (Un)armed all timer inputs
    //
    // Parameters	: u8* payload with [state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_ArmOrDisarmAllTimingInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SoftTimingInputPulse
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: Software input pulse
    //			  Send a simulate pulse on an spec input
    //
    // Parameters	: u8* -> payload with [state]32
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SoftTimingInputPulse(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_PrepareSynch
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: Prepare the sync
    //			  Activate inputs that want to received new
    //			  day time in next sync
    //
    // Parameters	: u8* -> Payload with [][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_PrepareSynch(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_PrepareOneTimingOutput
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Prepare one timing Output
    //			  Config the time when an out must be activated
    //			  the pulse duration
    //
    // Parameters	: u8*
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_PrepareOneTimingOutput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_EnDisOneTimingOutput
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: En(dis)able a Timing Output
    //
    // Parameters	: u8* -> payload with [out nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisOneTimingOutput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_EnDisAllTimingOutput
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: En(dis)able all Timing outputs
    //
    // Parameters	: u8* -> payload with [state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisAllTimingOutput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_NewRollingTime
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Configure a new Rolling time
    //
    // Parameters	: u8* -> Payload with [][][][][][][][][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_NewRollingTime(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_RollingTimeNewDest
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Configure the new destination for RTs
    //
    // Parameters	: u8* -> Payload with [][][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingTimeNewDest(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_RollingTimeNewState
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Configure new state for RT
    //
    // Parameters	: u8* -> Payload with [nb RT][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingTimeNewState(u8 *aPayload);

    //--------------------------------------------------------------
    // Name			: iFpga_RollingTimeNewInter
    // Author		: Cestele Yves
    // Date			: 29 juin 2017
    // Descritpion		: Configure en new interval between 2 RT
    //
    // Parameters		: u8*
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingTimeNewInter(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_RollingTimeNewCustomTrig
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Configure new trigger for rolling time
    //
    // Parameters	: u8* -> Payload with [][][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingTimeNewCustomTrig(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_EnDisOneTimeStampInp
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: En(dis)able a Time stamp input
    //
    // Parameters	: u8* -> payload with [inp nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisOneTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name			: iFpga_EnDisAllTimeStampInp
    // Author		: Cestele Yves
    // Date			: 29 juin 2017
    // Descritpion		: En(dis)able all time stamp inputs
    //
    // Parameters		: u8* -> payload with [state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SetDebounceAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Set Debounce All Time Stamp Inputs
    //
    // Parameters	: u8* -> Payload -> Nothing
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SetDebounceAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SoftTimeStampInputPulse
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Software time stamp input pulse
    //
    // Parameters	: u8* -> payload with [inp nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SoftTimeStampInputPulse(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SelActSlopeAllTimeInp
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Activate slope on all Time inputs
    //
    // Parameters	: u8* -> payload with [][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SelActSlopeAllTimeInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SelActSlopeAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	:
    //
    // Parameters	: u8* -> payload with [][][][][][][][][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SelActSlopeAllTimeStampInp(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_RollingTimeNewSerial
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Configure a new serial interface for RT
    //
    // Parameters	: u8* -> Payload with [][][][][][][]...14
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingTimeNewSerial(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_ResetSeveralOutput
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Reset several outputs
    //
    // Parameters	: u8* -> Payload [out to reset]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_ResetSeveralOutput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SetPolarityAllOutputs
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Set the polarity of all outputs
    //
    // Parameters	: u8* -> payload with [polarity]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SetPolarityAllOutputs(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_RollingClearWaitInput
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Clear waiting Inputs
    //
    // Parameters	: u8* -> payload with []
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingClearWaitInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_SetGenericOutputsReg
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Set generic outputs registers
    //
    // Parameters	: u8* -> paload with [state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SetGenericOutputsReg(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_ResetFpga
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Reset the FPGA and all registers
    //
    // Parameters	: u8* -> Payload with [0x55][0x0F][0xF0][0xAA]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_ResetFpga(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_RollingTimeNewSerialBin
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Create a new RT Serial Bin
    //
    // Parameters	: u8* -> Payload with [][][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_RollingTimeNewSerialBin(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_LogicalOrOnInput
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: En(dis)able logical OR inputs
    //
    // Parameters	: u8* -> Payload with [Inp nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_LogicalOrOnInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_LogicalAndOnInput
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: En(dis) logical AND on input
    //
    // Parameters	: u8* -> Payload with [inp nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_LogicalAndOnInput(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFpga_StateDetectionDelay
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: Config State Detection for all Inputs
    //
    // Parameters	: u8* -> Payload with [State][Delay]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_StateDetectionDelay(u8 *aPayload);

    //--------------------------------------------------------------
    // Name		: iFPga_EnableDisableStateDetection
    // Author		: Cestele Yves
    // Date		: 4 juil. 2017
    // Descritpion	: En(dis)able state detection
    //
    // Parameters	: u8* -> Payload with [state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFPga_EnableDisableStateDetection(u8 *aPayload);






#endif /* SRC_INTERFACES_IFPGA_H_ */
