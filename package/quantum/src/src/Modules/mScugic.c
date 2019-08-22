///*---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
//All rights reserved.
//-----------------------------------------------------------------------------
//File name 			: mScugic.c
//Author				: Cestele Yves
//Date				: 26 juin 2017
//Description			: Description in mScugic.h file
//
//Modifications		: -
//
//---------------------------------------------------------------------------*/
//#include "mScugic.h"
//
//static XScuGic InterruptController;
//static XScuGic_Config *IntcConfig;
////--------------------------------------------------------------
//// 				FUNCTIONS
////--------------------------------------------------------------
//
//    //--------------------------------------------------------------
//    // Name		: mScugic_setup
//    // Author		: Cestele Yves
//    // Date		: 26 juin 2017
//    // Descritpion	: SCUGIC Setup
//    // 			  Connect the interrupts with handlers passing
//    //			  in parameter (Uart_lite, Uart1_ps & Uart0_ps)
//    //
//    // Modification	:
//    //--------------------------------------------------------------
//    void mScugic_setup()
//    {
//	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
//	XScuGic_CfgInitialize(&InterruptController, IntcConfig, IntcConfig->CpuBaseAddress);
//
//	//Xil_ExceptionInit();
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, &InterruptController);
//	Xil_ExceptionEnable();
//    }
//
//    //--------------------------------------------------------------
//    // Name		: mScugiv_UartPS_Connect
//    // Author		: Cestele Yves
//    // Date		: 5 juil. 2017
//    // Descritpion	: Connect the Uart_PS intr to Def handler
//    //
//    // Parameters	: uartPsInstStruct -> Struct with inst of
//    //					      each Uart_PS
//    //
//    // Return		: void
//    //
//    // Modification	:
//    //--------------------------------------------------------------
//    void mScugiv_Uarts_Connect(rs232InstStruct *aRS232Inst)
//    {
//	// Uart_PS1
//	XScuGic_SetPriorityTriggerType(&InterruptController, XPAR_XUARTPS_1_INTR, 56, 0x3);
//	XScuGic_Connect(&InterruptController, XPAR_XUARTPS_1_INTR, (Xil_InterruptHandler) XUartPs_InterruptHandler, (void *)&aRS232Inst->UartPS1);
//	XScuGic_Enable(&InterruptController, XPAR_XUARTPS_1_INTR);
//
//	// Uart_PS0
//	XScuGic_SetPriorityTriggerType(&InterruptController, XPAR_XUARTPS_0_INTR, 64, 0x3);
//	XScuGic_Connect(&InterruptController, XPAR_XUARTPS_0_INTR, (Xil_InterruptHandler) XUartPs_InterruptHandler, (void *)&aRS232Inst->UartPS0);
//	XScuGic_Enable(&InterruptController, XPAR_XUARTPS_0_INTR);
//
//	// Uart_Lite0
//	XScuGic_SetPriorityTriggerType(&InterruptController, UL0_IRQ_INTERRUPT_ID, 72, 0x3);
//	XScuGic_Connect(&InterruptController, UL0_IRQ_INTERRUPT_ID, (Xil_InterruptHandler)XUartLite_InterruptHandler, (void *)&aRS232Inst->UartLite0);
//	XScuGic_Enable(&InterruptController, UL0_IRQ_INTERRUPT_ID);
//
////	// Uart_Lite1
////	XScuGic_SetPriorityTriggerType(&InterruptController, UL1_IRQ_INTERRUPT_ID, 80, 0x3);
////	XScuGic_Connect(&InterruptController, UL1_IRQ_INTERRUPT_ID, (Xil_InterruptHandler)XUartLite_InterruptHandler, (void *)&aRS232Inst->UartLite1);
////	XScuGic_Enable(&InterruptController, UL1_IRQ_INTERRUPT_ID);
//
////	// Uart_Lite2
////	XScuGic_SetPriorityTriggerType(&InterruptController, UL2_IRQ_INTERRUPT_ID, 88, 0x3);
////	XScuGic_Connect(&InterruptController, UL2_IRQ_INTERRUPT_ID, (Xil_InterruptHandler)XUartLite_InterruptHandler, (void *)&aRS232Inst->UartLite2);
////	XScuGic_Enable(&InterruptController, UL2_IRQ_INTERRUPT_ID);
////
////	// Uart_Lite3
////	XScuGic_SetPriorityTriggerType(&InterruptController, UL3_IRQ_INTERRUPT_ID, 96, 0x3);
////	XScuGic_Connect(&InterruptController, UL3_IRQ_INTERRUPT_ID, (Xil_InterruptHandler)XUartLite_InterruptHandler, (void *)&aRS232Inst->UartLite3);
////	XScuGic_Enable(&InterruptController, UL3_IRQ_INTERRUPT_ID);
////
////	// Uart_Lite4
////	XScuGic_SetPriorityTriggerType(&InterruptController, UL4_IRQ_INTERRUPT_ID, 104, 0x3);
////	XScuGic_Connect(&InterruptController, UL4_IRQ_INTERRUPT_ID, (Xil_InterruptHandler)XUartLite_InterruptHandler, (void *)&aRS232Inst->UartLite4);
////	XScuGic_Enable(&InterruptController, UL4_IRQ_INTERRUPT_ID);
////
////	// Uart_Lite5
////	XScuGic_SetPriorityTriggerType(&InterruptController, UL5_IRQ_INTERRUPT_ID, 112, 0x3);
////	XScuGic_Connect(&InterruptController, UL5_IRQ_INTERRUPT_ID, (Xil_InterruptHandler)XUartLite_InterruptHandler, (void *)&aRS232Inst->UartLite5);
////	XScuGic_Enable(&InterruptController, UL5_IRQ_INTERRUPT_ID);
//    }
//
//
//    //--------------------------------------------------------------
//    // Name		: mScugic_SwissTiming_Connect
//    // Author		: Cestele Yves
//    // Date		: 5 juil. 2017
//    // Descritpion	: Connect the SwissTiming IRQs to selected
//    //			  handler
//    //
//    // Parameters	: swissTimingHandlerStruct -> struct with
//    //			  a handler for each IRQ
//    //
//    // Return		: void
//    //
//    // Modification	:
//    //--------------------------------------------------------------
//    void mScugic_SwissTiming_Connect(swissTimingHandlerStruct aHandler)
//    {
//	XScuGic_SetPriorityTriggerType(&InterruptController, ST_IRQ1_INTERRUPT_ID, 8, 0x3);
//	XScuGic_Connect(&InterruptController, ST_IRQ1_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ1_handler, (void *)0);
//	XScuGic_Enable(&InterruptController, ST_IRQ1_INTERRUPT_ID);
//
//	XScuGic_SetPriorityTriggerType(&InterruptController, ST_IRQ2_INTERRUPT_ID, 16, 0x3);
//	XScuGic_Connect(&InterruptController, ST_IRQ2_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ2_handler, (void *)0);
//	XScuGic_Enable(&InterruptController, ST_IRQ2_INTERRUPT_ID);
//
//	XScuGic_SetPriorityTriggerType(&InterruptController, ST_IRQ3_INTERRUPT_ID, 24, 0x3);
//	XScuGic_Connect(&InterruptController, ST_IRQ3_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ3_handler, (void *)0);
//	XScuGic_Enable(&InterruptController, ST_IRQ3_INTERRUPT_ID);
//
//	XScuGic_SetPriorityTriggerType(&InterruptController, ST_IRQ4_INTERRUPT_ID, 32, 0x3);
//	XScuGic_Connect(&InterruptController, ST_IRQ4_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ4_handler, (void *)0);
//	XScuGic_Enable(&InterruptController, ST_IRQ4_INTERRUPT_ID);
//
//	XScuGic_SetPriorityTriggerType(&InterruptController, ST_IRQ5_INTERRUPT_ID, 40, 0x3);
//	XScuGic_Connect(&InterruptController, ST_IRQ5_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ5_handler, (void *)0);
//	XScuGic_Enable(&InterruptController, ST_IRQ5_INTERRUPT_ID);
//
//	XScuGic_SetPriorityTriggerType(&InterruptController, ST_IRQ6_INTERRUPT_ID, 48, 0x3);
//	XScuGic_Connect(&InterruptController, ST_IRQ6_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ6_handler, (void *)0);
//	XScuGic_Enable(&InterruptController, ST_IRQ6_INTERRUPT_ID);
//
//	XScuGic_Connect(&InterruptController, ST_IRQ7_INTERRUPT_ID, (Xil_InterruptHandler)aHandler.IRQ7_handler, (void *)0);
//	//XScuGic_Enable(&InterruptController, ST_IRQ7_INTERRUPT_ID);
//    }
//
