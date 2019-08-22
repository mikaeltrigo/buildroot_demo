/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: gHostCmd.h
Author				: Cestele Yves
Date				: 28 juin 2019
Description			: Commands to execute after a Frame from
				  host come

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_GESTIONNAIRES_GHOSTCMD_H_
#define SRC_GESTIONNAIRES_GHOSTCMD_H_

#include "xil_types.h"
#include "mRs232.h"
#include "utils.h"
#include "TimerDef.h"
#include "mHostCmd.h"
#include "mScugic.h"
#include "mRs232.h"
#include "gEvent.h"		// Include to have ref on handler functions
#include "answerMessages.h"

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#define kSizeBufferFrame	20		// Size of the FIFO for the Frames that comes from the PC Sport

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

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
    void gHostCmd_Setup(void);

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
    void gHostCmd_Execute(void);

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
    //void handler_uart0_interrupts(void *CallBackRef, u32 Event, u32 EventData);

    //--------------------------------------------------------------
    // Name		: _handle_uart1_interrupt
    // Author		: Cestele Yves
    // Date		: 23 juin 2019
    // Descritpion	:
    //
    // Parameters	: CallBackRef 	: Element wich call the function
    //			  Event		: Event that occurred
    //			  EventData	: Datas
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void handler_uart1_interrupts(void *CallBackRef, u32 Event, u32 EventData);

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
    void UartLite0SendHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite0RecvHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite1SendHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite1RecvHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite2SendHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite2RecvHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite3SendHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite3RecvHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite4SendHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite4RecvHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite5SendHandler(void *CallBackRef, unsigned int EventData);

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
    void UartLite5RecvHandler(void *CallBackRef, unsigned int EventData);

#endif /* SRC_GESTIONNAIRES_GHOSTCMD_H_ */
