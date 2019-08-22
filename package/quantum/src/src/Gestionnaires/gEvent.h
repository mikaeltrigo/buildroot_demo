/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gEvent.h
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Functions that's react to events in prg

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_GESTIONNAIRES_GEVENT_H_
#define SRC_GESTIONNAIRES_GEVENT_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"
#include "mRs232.h"
#include "utils.h"
#include "TimerDef.h"
#include "mRollingTimeBuffer.h"
#include "mPulseBuffer.h"

//--------------------------------------------------------------
// 				STRUCTURES
//--------------------------------------------------------------



//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
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
    void gEvent_Setup(void);

    //--------------------------------------------------------------
    // Name		: gEvent_Execute
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: gEvent function
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void gEvent_Execute(void);

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
    void *swissTiming_IRQ1_handler(void *arg);

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
    void* swissTiming_IRQ2_handler(void *arg);

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
    void* swissTiming_IRQ3_handler(void *arg);

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
    void* swissTiming_IRQ4_handler(void *arg);

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
    void* swissTiming_IRQ5_handler(void *arg);

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
    void* swissTiming_IRQ6_handler(void *arg);

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
    void* swissTiming_IRQ7_handler(void *arg);


#endif /* SRC_GESTIONNAIRES_GEVENT_H_ */
