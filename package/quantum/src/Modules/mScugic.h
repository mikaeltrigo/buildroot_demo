/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: mScugic.h
Author				: Cestele Yves
Date				: 26 juin 2017
Description			: Snoop Control Unit Generic Interrupt
				  Controller Snoop management

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_MODULES_MSCUGIC_H_
#define SRC_MODULES_MSCUGIC_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------

#include "utils.h"
#include "mRs232.h"

#define ST_IRQ1_INTERRUPT_ID 	61				// Interruptions IDs according to ZynqBook p. 214
#define ST_IRQ2_INTERRUPT_ID 	62
#define ST_IRQ3_INTERRUPT_ID 	63
#define ST_IRQ4_INTERRUPT_ID 	64
#define ST_IRQ5_INTERRUPT_ID 	65
#define ST_IRQ6_INTERRUPT_ID 	66
#define ST_IRQ7_INTERRUPT_ID 	67
#define UL0_IRQ_INTERRUPT_ID 	68
#define UL1_IRQ_INTERRUPT_ID 	69
#define UL2_IRQ_INTERRUPT_ID 	70
#define UL3_IRQ_INTERRUPT_ID 	71
#define UL4_IRQ_INTERRUPT_ID 	72
#define UL5_IRQ_INTERRUPT_ID 	73

//typedef struct
//{
//    Xil_InterruptHandler IRQ1_handler;
//    Xil_InterruptHandler IRQ2_handler;
//    Xil_InterruptHandler IRQ3_handler;
//    Xil_InterruptHandler IRQ4_handler;
//    Xil_InterruptHandler IRQ5_handler;
//    Xil_InterruptHandler IRQ6_handler;
//    Xil_InterruptHandler IRQ7_handler;
//}swissTimingHandlerStruct;

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: mScugic_setup
    // Author		: Cestele Yves
    // Date		: 26 juin 2017
    // Descritpion	: SCUGIC Setup
    //
    // Modification	:
    //--------------------------------------------------------------
    void mScugic_setup();

    //--------------------------------------------------------------
    // Name		: mScugiv_UartPS_Connect
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Connect the Uarts intr to Def handlers
    //
    // Parameters	: uartPsInstStruct -> Struct with inst of
    //					      each Uart
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    //void mScugiv_Uarts_Connect(rs232InstStruct *aRS232Inst);

    //--------------------------------------------------------------
    // Name		: mScugic_SwissTiming_Connect
    // Author		: Cestele Yves
    // Date		: 5 juil. 2017
    // Descritpion	: Connect the SwissTiming IRQs to selected
    //			  handler
    //
    // Parameters	: swissTimingHandlerStruct -> struct with
    //			  a handler for each IRQ
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    //void mScugic_SwissTiming_Connect(swissTimingHandlerStruct aHandler);


#endif /* SRC_MODULES_MSCUGIC_H_ */
