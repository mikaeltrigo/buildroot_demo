/*
------------------------------------------------------------
Copyright 2003-2009 Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	FpgaRegisterDef.h	
Auteur et Date :	Monnerat Serge 19.03.2009

But : Acc�s aux registres de la FPGA

-----------------------------------------------------------------------------
Historique:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/

#ifndef __FPGAREGISTERDEF__
#define __FPGAREGISTERDEF__

#include "xil_types.h"

// Adresse de base des registres de la FPGA

#define kNbOfInput 32
#define kNbOfAdInput 96
#define kNbOfSoftAdInput 96
#define kNbOfOutput 32
#define kNbOfRollingTime 16
#define kNbOfCustomTrigger 16

u32 FPGA_Registers_getBase();

#define	kConfigInputXLowRegBaseAdr  (FPGA_Registers_getBase()+0x300)
#define	kConfigInputXHighRegBaseAdr  (FPGA_Registers_getBase()+0x302)
#define	kConfigOutputXRegBaseAdr  (FPGA_Registers_getBase()+0x200)
#define	kImmediateOutputEnableRegBaseAdr  (FPGA_Registers_getBase()+0x490)
#define	kOutputXDestMaskRegBaseAdr  (FPGA_Registers_getBase()+0x400)
#define	kIntervalRollingTimeXRegBaseAdr  (FPGA_Registers_getBase()+0x660)
#define	kConfigRollingTimeXRegBaseAdr  (FPGA_Registers_getBase()+0x100)
#define	kOutputMaskRollingTimeXRegBaseAdr  (FPGA_Registers_getBase()+0x560)
#define	kRollingTimeNewStateInpXMaskRegBaseAdr  (FPGA_Registers_getBase()+0x6a0)
#define	kCustomTriggerRollingTimeXRegBaseAdr  (FPGA_Registers_getBase()+0x600)
#define	kOutputMaskCustomTriggerRegBaseAdr  (FPGA_Registers_getBase()+0x5a0)
#define	kActivatedDayTimeOutputRegBaseAdr  (FPGA_Registers_getBase()+0x4a0)
#define	kLastEndPeriodRollingTimeRegBaseAdr  (FPGA_Registers_getBase()+0x180)
#define	kTimeEventInputRegBaseAdr  (FPGA_Registers_getBase()+0x0040)
#define	gNextSyncDayTimeLow  (FPGA_Registers_getBase()+0x0000)
#define	gNextSyncDayTimeMed  (FPGA_Registers_getBase()+0x0002)
#define	gNextSyncDayTimeHigh  (FPGA_Registers_getBase()+0x0004)
#define	gOutputEnableLow  (FPGA_Registers_getBase()+0x0480)
#define	gOutputEnableHigh  (FPGA_Registers_getBase()+0x0482)
#define	gOutputEventEventLow  (FPGA_Registers_getBase()+0x0488)
#define	gOutputEventEventHigh  (FPGA_Registers_getBase()+0x048a)
#define	gOutputEventEventAckLow  (FPGA_Registers_getBase()+0x048c)
#define	gOutputEventEventAckHigh  (FPGA_Registers_getBase()+0x048e)
#define	gCustomTriggerEvent  (FPGA_Registers_getBase()+0x0484)
#define	gCustomTriggerEventAck  (FPGA_Registers_getBase()+0x0486)
#define	gReceivedArmedStateLow  (FPGA_Registers_getBase()+0x000c)
#define	gReceivedArmedStateHigh  (FPGA_Registers_getBase()+0x000e)
#define	gReceivedArmedStateAckLow  (FPGA_Registers_getBase()+0x0010)
#define	gReceivedArmedStateAckHigh  (FPGA_Registers_getBase()+0x0012)
#define	gReceivedNotArmedStateLow  (FPGA_Registers_getBase()+0x0014)
#define	gReceivedNotArmedStateHigh  (FPGA_Registers_getBase()+0x0016)
#define	gReceivedNotArmedStateAckLow  (FPGA_Registers_getBase()+0x0018)
#define	gReceivedNotArmedStateAckHigh  (FPGA_Registers_getBase()+0x001a)
#define	gReceivedGpsSynchroTimeLow  (FPGA_Registers_getBase()+0x002C)
#define	gReceivedGpsSynchroTimeHigh  (FPGA_Registers_getBase()+0x0028)
#define	gReceivedGpsSynchroState  (FPGA_Registers_getBase()+0x0020)
#define	gReceivedGpsSynchroStateAck  (FPGA_Registers_getBase()+0x0024)
#define	kDayTimeLow  (FPGA_Registers_getBase()+0x0006)
#define	kDayTimeMed  (FPGA_Registers_getBase()+0x0008)
#define	kDayTimeHigh  (FPGA_Registers_getBase()+0x000A)
#define	kNextSyncDayTimeh  (FPGA_Registers_getBase()+0x000)
#define	kNextSyncDayTimel  (FPGA_Registers_getBase()+0x004)
#define	kCurrentDayTimeh  (FPGA_Registers_getBase()+0x008)
#define	kCurrentDayTimel  (FPGA_Registers_getBase()+0x00C)
#define	kReceivedArmedState  (FPGA_Registers_getBase()+0x010)
#define	kReceivedArmedState_Ack  (FPGA_Registers_getBase()+0x014)
#define	kReceivedNotArmedState  (FPGA_Registers_getBase()+0x018)
#define	kReceivedNotArmedState_Ack  (FPGA_Registers_getBase()+0x01C)
#define	kReceivedGpsState  (FPGA_Registers_getBase()+0x020)
#define	kReceivedGpsState_Ack  (FPGA_Registers_getBase()+0x024)
#define	kReceivedGpsSyncTimeh  (FPGA_Registers_getBase()+0x028)
#define	kReceivedGpsSyncTimel  (FPGA_Registers_getBase()+0x02C)
#define	kReceivedSoftwareInput  (FPGA_Registers_getBase()+0x030)
#define	kReceivedSoftwareInput_Ack  (FPGA_Registers_getBase()+0x034)
#define	kRollingTimeEvent  (FPGA_Registers_getBase()+0x038)
#define	kRollingTimeEvent_Ack  (FPGA_Registers_getBase()+0x03C)
#define	kSoftwareInputPulse  (FPGA_Registers_getBase()+0x040)
#define	kSoftwareAdInputPulseh  (FPGA_Registers_getBase()+0x044)
#define	kSoftwareAdInputPulsem  (FPGA_Registers_getBase()+0x048)
#define	kSoftwareAdInputPulsel  (FPGA_Registers_getBase()+0x04C)
#define	kInputsState  (FPGA_Registers_getBase()+0x050)
#define	kAdInputsStateh  (FPGA_Registers_getBase()+0x054)
#define	kAdInputsStatem  (FPGA_Registers_getBase()+0x058)
#define	kAdInputsStatel  (FPGA_Registers_getBase()+0x05C)
#define	kReceivedAdInputsEventh  (FPGA_Registers_getBase()+0x060)
#define	kReceivedAdInputsEventm  (FPGA_Registers_getBase()+0x064)
#define	kReceivedAdInputsEventl  (FPGA_Registers_getBase()+0x068)
#define	kReceivedAdInputsEvent_Ackh  (FPGA_Registers_getBase()+0x070)
#define	kReceivedAdInputsEvent_Ackm  (FPGA_Registers_getBase()+0x074)
#define	kReceivedAdInputsEvent_Ackl  (FPGA_Registers_getBase()+0x078)
#define	kReceivedSoftwareAdInputh  (FPGA_Registers_getBase()+0x080)
#define	kReceivedSoftwareAdInputm  (FPGA_Registers_getBase()+0x084)
#define	kReceivedSoftwareAdInputl  (FPGA_Registers_getBase()+0x088)
#define	kReceivedSoftwareAdInput_Ackh  (FPGA_Registers_getBase()+0x090)
#define	kReceivedSoftwareAdInput_Ackm  (FPGA_Registers_getBase()+0x094)
#define	kReceivedSoftwareAdInput_Ackl  (FPGA_Registers_getBase()+0x098)
//------------------ FPGA V5.0 -------------------
#define	kPulsesOR  (FPGA_Registers_getBase()+0x0A0)
#define	kInputsAND  (FPGA_Registers_getBase()+0x0A8)
#define	kConfigInputActiveDelay  (FPGA_Registers_getBase()+0x0B0)
#define	kConfigInputNotActiveDelay  (FPGA_Registers_getBase()+0x0B4)
#define	kReceivedInputActiveDelayEvent  (FPGA_Registers_getBase()+0x0C0)
#define	kReceivedInputActiveDelayEvent_Ack  (FPGA_Registers_getBase()+0x0C4)
#define	kReceivedInputNotActiveDelayEvent  (FPGA_Registers_getBase()+0x0C8)
#define	kReceivedInputNotActiveDelayEvent_Ack  (FPGA_Registers_getBase()+0x0CC)
#define	kReceivedOROnePulseEvent  (FPGA_Registers_getBase()+0x0D0)
#define	kReceivedOROnePulseEvent_Ack  (FPGA_Registers_getBase()+0x0D4)
//------------------ FPGA V5.0 (end) -------------
#define	kTimeEventInput1h  (FPGA_Registers_getBase()+0x100)
#define	kTimeEventInput1l  (FPGA_Registers_getBase()+0x104)
#define	kTimeEventInput2h  (FPGA_Registers_getBase()+0x108)
#define	kTimeEventInput2l  (FPGA_Registers_getBase()+0x10C)
#define	kTimeEventInput3h  (FPGA_Registers_getBase()+0x110)
#define	kTimeEventInput3l  (FPGA_Registers_getBase()+0x114)
#define	kTimeEventInput4h  (FPGA_Registers_getBase()+0x118)
#define	kTimeEventInput4l  (FPGA_Registers_getBase()+0x11C)
#define	kTimeEventInput5h  (FPGA_Registers_getBase()+0x120)
#define	kTimeEventInput5l  (FPGA_Registers_getBase()+0x124)
#define	kTimeEventInput6h  (FPGA_Registers_getBase()+0x128)
#define	kTimeEventInput6l  (FPGA_Registers_getBase()+0x12C)
#define	kTimeEventInput7h  (FPGA_Registers_getBase()+0x130)
#define	kTimeEventInput7l  (FPGA_Registers_getBase()+0x134)
#define	kTimeEventInput8h  (FPGA_Registers_getBase()+0x138)
#define	kTimeEventInput8l  (FPGA_Registers_getBase()+0x13C)
#define	kTimeEventInput9h  (FPGA_Registers_getBase()+0x140)
#define	kTimeEventInput9l  (FPGA_Registers_getBase()+0x144)
#define	kTimeEventInput10h  (FPGA_Registers_getBase()+0x148)
#define	kTimeEventInput10l  (FPGA_Registers_getBase()+0x14C)
#define	kTimeEventInput11h  (FPGA_Registers_getBase()+0x150)
#define	kTimeEventInput11l  (FPGA_Registers_getBase()+0x154)
#define	kTimeEventInput12h  (FPGA_Registers_getBase()+0x158)
#define	kTimeEventInput12l  (FPGA_Registers_getBase()+0x15C)
#define	kTimeEventInput13h  (FPGA_Registers_getBase()+0x160)
#define	kTimeEventInput13l  (FPGA_Registers_getBase()+0x164)
#define	kTimeEventInput14h  (FPGA_Registers_getBase()+0x168)
#define	kTimeEventInput14l  (FPGA_Registers_getBase()+0x16C)
#define	kTimeEventInput15h  (FPGA_Registers_getBase()+0x170)
#define	kTimeEventInput15l  (FPGA_Registers_getBase()+0x174)
#define	kTimeEventInput16h  (FPGA_Registers_getBase()+0x178)
#define	kTimeEventInput16l  (FPGA_Registers_getBase()+0x17C)
#define	kTimeEventInput17h  (FPGA_Registers_getBase()+0x180)
#define	kTimeEventInput17l  (FPGA_Registers_getBase()+0x184)
#define	kTimeEventInput18h  (FPGA_Registers_getBase()+0x188)
#define	kTimeEventInput18l  (FPGA_Registers_getBase()+0x18C)
#define	kTimeEventInput19h  (FPGA_Registers_getBase()+0x190)
#define	kTimeEventInput19l  (FPGA_Registers_getBase()+0x194)
#define	kTimeEventInput20h  (FPGA_Registers_getBase()+0x198)
#define	kTimeEventInput20l  (FPGA_Registers_getBase()+0x19C)
#define	kTimeEventInput21h  (FPGA_Registers_getBase()+0x1A0)
#define	kTimeEventInput21l  (FPGA_Registers_getBase()+0x1A4)
#define	kTimeEventInput22h  (FPGA_Registers_getBase()+0x1A8)
#define	kTimeEventInput22l  (FPGA_Registers_getBase()+0x1AC)
#define	kTimeEventInput23h  (FPGA_Registers_getBase()+0x1B0)
#define	kTimeEventInput23l  (FPGA_Registers_getBase()+0x1B4)
#define	kTimeEventInput24h  (FPGA_Registers_getBase()+0x1B8)
#define	kTimeEventInput24l  (FPGA_Registers_getBase()+0x1BC)
#define	kTimeEventInput25h  (FPGA_Registers_getBase()+0x1C0)
#define	kTimeEventInput25l  (FPGA_Registers_getBase()+0x1C4)
#define	kTimeEventInput26h  (FPGA_Registers_getBase()+0x1C8)
#define	kTimeEventInput26l  (FPGA_Registers_getBase()+0x1CC)
#define	kTimeEventInput27h  (FPGA_Registers_getBase()+0x1D0)
#define	kTimeEventInput27l  (FPGA_Registers_getBase()+0x1D4)
#define	kTimeEventInput28h  (FPGA_Registers_getBase()+0x1D8)
#define	kTimeEventInput28l  (FPGA_Registers_getBase()+0x1DC)
#define	kTimeEventInput29h  (FPGA_Registers_getBase()+0x1E0)
#define	kTimeEventInput29l  (FPGA_Registers_getBase()+0x1E4)
#define	kTimeEventInput30h  (FPGA_Registers_getBase()+0x1E8)
#define	kTimeEventInput30l  (FPGA_Registers_getBase()+0x1EC)
#define	kTimeEventInput31h  (FPGA_Registers_getBase()+0x1F0)
#define	kTimeEventInput31l  (FPGA_Registers_getBase()+0x1F4)
#define	kTimeEventInput32h  (FPGA_Registers_getBase()+0x1F8)
#define	kTimeEventInput32l  (FPGA_Registers_getBase()+0x1FC)
#define	kConfigRollingTime1h  (FPGA_Registers_getBase()+0x200)
#define	kConfigRollingTime1l  (FPGA_Registers_getBase()+0x204)
#define	kConfigRollingTime2h  (FPGA_Registers_getBase()+0x208)
#define	kConfigRollingTime2l  (FPGA_Registers_getBase()+0x20C)
#define	kConfigRollingTime3h  (FPGA_Registers_getBase()+0x210)
#define	kConfigRollingTime3l  (FPGA_Registers_getBase()+0x214)
#define	kConfigRollingTime4h  (FPGA_Registers_getBase()+0x218)
#define	kConfigRollingTime4l  (FPGA_Registers_getBase()+0x21C)
#define	kConfigRollingTime5h  (FPGA_Registers_getBase()+0x220)
#define	kConfigRollingTime5l  (FPGA_Registers_getBase()+0x224)
#define	kConfigRollingTime6h  (FPGA_Registers_getBase()+0x228)
#define	kConfigRollingTime6l  (FPGA_Registers_getBase()+0x22C)
#define	kConfigRollingTime7h  (FPGA_Registers_getBase()+0x230)
#define	kConfigRollingTime7l  (FPGA_Registers_getBase()+0x234)
#define	kConfigRollingTime8h  (FPGA_Registers_getBase()+0x238)
#define	kConfigRollingTime8l  (FPGA_Registers_getBase()+0x23C)
#define	kConfigRollingTime9h  (FPGA_Registers_getBase()+0x240)
#define	kConfigRollingTime9l  (FPGA_Registers_getBase()+0x244)
#define	kConfigRollingTime10h  (FPGA_Registers_getBase()+0x248)
#define	kConfigRollingTime10l  (FPGA_Registers_getBase()+0x24C)
#define	kConfigRollingTime11h  (FPGA_Registers_getBase()+0x250)
#define	kConfigRollingTime11l  (FPGA_Registers_getBase()+0x254)
#define	kConfigRollingTime12h  (FPGA_Registers_getBase()+0x258)
#define	kConfigRollingTime12l  (FPGA_Registers_getBase()+0x25C)
#define	kConfigRollingTime13h  (FPGA_Registers_getBase()+0x260)
#define	kConfigRollingTime13l  (FPGA_Registers_getBase()+0x264)
#define	kConfigRollingTime14h  (FPGA_Registers_getBase()+0x268)
#define	kConfigRollingTime14l  (FPGA_Registers_getBase()+0x26C)
#define	kConfigRollingTime15h  (FPGA_Registers_getBase()+0x270)
#define	kConfigRollingTime15l  (FPGA_Registers_getBase()+0x274)
#define	kConfigRollingTime16h  (FPGA_Registers_getBase()+0x278)
#define	kConfigRollingTime16l  (FPGA_Registers_getBase()+0x27C)
#define	kRollingTime1h  (FPGA_Registers_getBase()+0x280)
#define	kRollingTime1l  (FPGA_Registers_getBase()+0x284)
#define	kRollingTime2h  (FPGA_Registers_getBase()+0x288)
#define	kRollingTime2l  (FPGA_Registers_getBase()+0x28C)
#define	kRollingTime3h  (FPGA_Registers_getBase()+0x290)
#define	kRollingTime3l  (FPGA_Registers_getBase()+0x294)
#define	kRollingTime4h  (FPGA_Registers_getBase()+0x298)
#define	kRollingTime4l  (FPGA_Registers_getBase()+0x29C)
#define	kRollingTime5h  (FPGA_Registers_getBase()+0x2A0)
#define	kRollingTime5l  (FPGA_Registers_getBase()+0x2A4)
#define	kRollingTime6h  (FPGA_Registers_getBase()+0x2A8)
#define	kRollingTime6l  (FPGA_Registers_getBase()+0x2AC)
#define	kRollingTime7h  (FPGA_Registers_getBase()+0x2B0)
#define	kRollingTime7l  (FPGA_Registers_getBase()+0x2B4)
#define	kRollingTime8h  (FPGA_Registers_getBase()+0x2B8)
#define	kRollingTime8l  (FPGA_Registers_getBase()+0x2BC)
#define	kRollingTime9h  (FPGA_Registers_getBase()+0x2C0)
#define	kRollingTime9l  (FPGA_Registers_getBase()+0x2C4)
#define	kRollingTime10h  (FPGA_Registers_getBase()+0x2C8)
#define	kRollingTime10l  (FPGA_Registers_getBase()+0x2CC)
#define	kRollingTime11h  (FPGA_Registers_getBase()+0x2D0)
#define	kRollingTime11l  (FPGA_Registers_getBase()+0x2D4)
#define	kRollingTime12h  (FPGA_Registers_getBase()+0x2D8)
#define	kRollingTime12l  (FPGA_Registers_getBase()+0x2DC)
#define	kRollingTime13h  (FPGA_Registers_getBase()+0x2E0)
#define	kRollingTime13l  (FPGA_Registers_getBase()+0x2E4)
#define	kRollingTime14h  (FPGA_Registers_getBase()+0x2E8)
#define	kRollingTime14l  (FPGA_Registers_getBase()+0x2EC)
#define	kRollingTime15h  (FPGA_Registers_getBase()+0x2F0)
#define	kRollingTime15l  (FPGA_Registers_getBase()+0x2F4)
#define	kRollingTime16h  (FPGA_Registers_getBase()+0x2F8)
#define	kRollingTime16l  (FPGA_Registers_getBase()+0x2FC)
#define	kconfig_output1h  (FPGA_Registers_getBase()+0x300)
#define	kconfig_output1l  (FPGA_Registers_getBase()+0x304)
#define	kconfig_output2h  (FPGA_Registers_getBase()+0x308)
#define	kconfig_output2l  (FPGA_Registers_getBase()+0x30C)
#define	kconfig_output3h  (FPGA_Registers_getBase()+0x310)
#define	kconfig_output3l  (FPGA_Registers_getBase()+0x314)
#define	kconfig_output4h  (FPGA_Registers_getBase()+0x318)
#define	kconfig_output4l  (FPGA_Registers_getBase()+0x31C)
#define	kconfig_output5h  (FPGA_Registers_getBase()+0x320)
#define	kconfig_output5l  (FPGA_Registers_getBase()+0x324)
#define	kconfig_output6h  (FPGA_Registers_getBase()+0x328)
#define	kconfig_output6l  (FPGA_Registers_getBase()+0x32C)
#define	kconfig_output7h  (FPGA_Registers_getBase()+0x330)
#define	kconfig_output7l  (FPGA_Registers_getBase()+0x334)
#define	kconfig_output8h  (FPGA_Registers_getBase()+0x338)
#define	kconfig_output8l  (FPGA_Registers_getBase()+0x33C)
#define	kconfig_output9h  (FPGA_Registers_getBase()+0x340)
#define	kconfig_output9l  (FPGA_Registers_getBase()+0x344)
#define	kconfig_output10h  (FPGA_Registers_getBase()+0x348)
#define	kconfig_output10l  (FPGA_Registers_getBase()+0x34C)
#define	kconfig_output11h  (FPGA_Registers_getBase()+0x350)
#define	kconfig_output11l  (FPGA_Registers_getBase()+0x354)
#define	kconfig_output12h  (FPGA_Registers_getBase()+0x358)
#define	kconfig_output12l  (FPGA_Registers_getBase()+0x35C)
#define	kconfig_output13h  (FPGA_Registers_getBase()+0x360)
#define	kconfig_output13l  (FPGA_Registers_getBase()+0x364)
#define	kconfig_output14h  (FPGA_Registers_getBase()+0x368)
#define	kconfig_output14l  (FPGA_Registers_getBase()+0x36C)
#define	kconfig_output15h  (FPGA_Registers_getBase()+0x370)
#define	kconfig_output15l  (FPGA_Registers_getBase()+0x374)
#define	kconfig_output16h  (FPGA_Registers_getBase()+0x378)
#define	kconfig_output16l  (FPGA_Registers_getBase()+0x37C)
#define	kconfig_output17h  (FPGA_Registers_getBase()+0x380)
#define	kconfig_output17l  (FPGA_Registers_getBase()+0x384)
#define	kconfig_output18h  (FPGA_Registers_getBase()+0x388)
#define	kconfig_output18l  (FPGA_Registers_getBase()+0x38C)
#define	kconfig_output19h  (FPGA_Registers_getBase()+0x390)
#define	kconfig_output19l  (FPGA_Registers_getBase()+0x394)
#define	kconfig_output20h  (FPGA_Registers_getBase()+0x398)
#define	kconfig_output20l  (FPGA_Registers_getBase()+0x39C)
#define	kconfig_output21h  (FPGA_Registers_getBase()+0x3A0)
#define	kconfig_output21l  (FPGA_Registers_getBase()+0x3A4)
#define	kconfig_output22h  (FPGA_Registers_getBase()+0x3A8)
#define	kconfig_output22l  (FPGA_Registers_getBase()+0x3AC)
#define	kconfig_output23h  (FPGA_Registers_getBase()+0x3B0)
#define	kconfig_output23l  (FPGA_Registers_getBase()+0x3B4)
#define	kconfig_output24h  (FPGA_Registers_getBase()+0x3B8)
#define	kconfig_output24l  (FPGA_Registers_getBase()+0x3BC)
#define	kconfig_output25h  (FPGA_Registers_getBase()+0x3C0)
#define	kconfig_output25l  (FPGA_Registers_getBase()+0x3C4)
#define	kconfig_output26h  (FPGA_Registers_getBase()+0x3C8)
#define	kconfig_output26l  (FPGA_Registers_getBase()+0x3CC)
#define	kconfig_output27h  (FPGA_Registers_getBase()+0x3D0)
#define	kconfig_output27l  (FPGA_Registers_getBase()+0x3D4)
#define	kconfig_output28h  (FPGA_Registers_getBase()+0x3D8)
#define	kconfig_output28l  (FPGA_Registers_getBase()+0x3DC)
#define	kconfig_output29h  (FPGA_Registers_getBase()+0x3E0)
#define	kconfig_output29l  (FPGA_Registers_getBase()+0x3E4)
#define	kconfig_output30h  (FPGA_Registers_getBase()+0x3E8)
#define	kconfig_output30l  (FPGA_Registers_getBase()+0x3EC)
#define	kconfig_output31h  (FPGA_Registers_getBase()+0x3F0)
#define	kconfig_output31l  (FPGA_Registers_getBase()+0x3F4)
#define	kconfig_output32h  (FPGA_Registers_getBase()+0x3F8)
#define	kconfig_output32l  (FPGA_Registers_getBase()+0x3FC)
#define	kconfig_input1  (FPGA_Registers_getBase()+0x400)
#define	kconfig_input2  (FPGA_Registers_getBase()+0x404)
#define	kconfig_input3  (FPGA_Registers_getBase()+0x408)
#define	kconfig_input4  (FPGA_Registers_getBase()+0x40C)
#define	kconfig_input5  (FPGA_Registers_getBase()+0x410)
#define	kconfig_input6  (FPGA_Registers_getBase()+0x414)
#define	kconfig_input7  (FPGA_Registers_getBase()+0x418)
#define	kconfig_input8  (FPGA_Registers_getBase()+0x41C)
#define	kconfig_input9  (FPGA_Registers_getBase()+0x420)
#define	kconfig_input10  (FPGA_Registers_getBase()+0x424)
#define	kconfig_input11  (FPGA_Registers_getBase()+0x428)
#define	kconfig_input12  (FPGA_Registers_getBase()+0x42C)
#define	kconfig_input13  (FPGA_Registers_getBase()+0x430)
#define	kconfig_input14  (FPGA_Registers_getBase()+0x434)
#define	kconfig_input15  (FPGA_Registers_getBase()+0x438)
#define	kconfig_input16  (FPGA_Registers_getBase()+0x43C)
#define	kconfig_input17  (FPGA_Registers_getBase()+0x440)
#define	kconfig_input18  (FPGA_Registers_getBase()+0x444)
#define	kconfig_input19  (FPGA_Registers_getBase()+0x448)
#define	kconfig_input20  (FPGA_Registers_getBase()+0x44C)
#define	kconfig_input21  (FPGA_Registers_getBase()+0x450)
#define	kconfig_input22  (FPGA_Registers_getBase()+0x454)
#define	kconfig_input23  (FPGA_Registers_getBase()+0x458)
#define	kconfig_input24  (FPGA_Registers_getBase()+0x45C)
#define	kconfig_input25  (FPGA_Registers_getBase()+0x460)
#define	kconfig_input26  (FPGA_Registers_getBase()+0x464)
#define	kconfig_input27  (FPGA_Registers_getBase()+0x468)
#define	kconfig_input28  (FPGA_Registers_getBase()+0x46C)
#define	kconfig_input29  (FPGA_Registers_getBase()+0x470)
#define	kconfig_input30  (FPGA_Registers_getBase()+0x474)
#define	kconfig_input31  (FPGA_Registers_getBase()+0x478)
#define	kconfig_input32  (FPGA_Registers_getBase()+0x47C)
#define	kOutput1DestinationMask  (FPGA_Registers_getBase()+0x480)
#define	kOutput2DestinationMask  (FPGA_Registers_getBase()+0x484)
#define	kOutput3DestinationMask  (FPGA_Registers_getBase()+0x488)
#define	kOutput4DestinationMask  (FPGA_Registers_getBase()+0x48C)
#define	kOutput5DestinationMask  (FPGA_Registers_getBase()+0x490)
#define	kOutput6DestinationMask  (FPGA_Registers_getBase()+0x494)
#define	kOutput7DestinationMask  (FPGA_Registers_getBase()+0x498)
#define	kOutput8DestinationMask  (FPGA_Registers_getBase()+0x49C)
#define	kOutput9DestinationMask  (FPGA_Registers_getBase()+0x4A0)
#define	kOutput10DestinationMask  (FPGA_Registers_getBase()+0x4A4)
#define	kOutput11DestinationMask  (FPGA_Registers_getBase()+0x4A8)
#define	kOutput12DestinationMask  (FPGA_Registers_getBase()+0x4AC)
#define	kOutput13DestinationMask  (FPGA_Registers_getBase()+0x4B0)
#define	kOutput14DestinationMask  (FPGA_Registers_getBase()+0x4B4)
#define	kOutput15DestinationMask  (FPGA_Registers_getBase()+0x4B8)
#define	kOutput16DestinationMask  (FPGA_Registers_getBase()+0x4BC)
#define	kOutput17DestinationMask  (FPGA_Registers_getBase()+0x4C0)
#define	kOutput18DestinationMask  (FPGA_Registers_getBase()+0x4C4)
#define	kOutput19DestinationMask  (FPGA_Registers_getBase()+0x4C8)
#define	kOutput20DestinationMask  (FPGA_Registers_getBase()+0x4CC)
#define	kOutput21DestinationMask  (FPGA_Registers_getBase()+0x4D0)
#define	kOutput22DestinationMask  (FPGA_Registers_getBase()+0x4D4)
#define	kOutput23DestinationMask  (FPGA_Registers_getBase()+0x4D8)
#define	kOutput24DestinationMask  (FPGA_Registers_getBase()+0x4DC)
#define	kOutput25DestinationMask  (FPGA_Registers_getBase()+0x4E0)
#define	kOutput26DestinationMask  (FPGA_Registers_getBase()+0x4E4)
#define	kOutput27DestinationMask  (FPGA_Registers_getBase()+0x4E8)
#define	kOutput28DestinationMask  (FPGA_Registers_getBase()+0x4EC)
#define	kOutput29DestinationMask  (FPGA_Registers_getBase()+0x4F0)
#define	kOutput30DestinationMask  (FPGA_Registers_getBase()+0x4F4)
#define	kOutput31DestinationMask  (FPGA_Registers_getBase()+0x4F8)
#define	kOutput32DestinationMask  (FPGA_Registers_getBase()+0x4FC)
#define	kOuputsEnable  (FPGA_Registers_getBase()+0x500)
#define	kCustomTriggerEvent  (FPGA_Registers_getBase()+0x510)
#define	kCustomTriggerEvent_Ack  (FPGA_Registers_getBase()+0x514)
#define	kOutputEvent  (FPGA_Registers_getBase()+0x520)
#define	kOutputEvent_Ack  (FPGA_Registers_getBase()+0x524)
#define	kImmediateOutputEnable  (FPGA_Registers_getBase()+0x530)
#define	kCustomTriggerEnable  (FPGA_Registers_getBase()+0x534)
#define	kResetOutputs  (FPGA_Registers_getBase()+0x540)
#define	kOutputsPolarity  (FPGA_Registers_getBase()+0x550)
#define	kGenericInputs  (FPGA_Registers_getBase()+0x560)
#define	kGenericOutputs  (FPGA_Registers_getBase()+0x570)
#define	kActivatedDayTimeOutput1h  (FPGA_Registers_getBase()+0x600)
#define	kActivatedDayTimeOutput1l  (FPGA_Registers_getBase()+0x604)
#define	kActivatedDayTimeOutput2h  (FPGA_Registers_getBase()+0x608)
#define	kActivatedDayTimeOutput2l  (FPGA_Registers_getBase()+0x60C)
#define	kActivatedDayTimeOutput3h  (FPGA_Registers_getBase()+0x610)
#define	kActivatedDayTimeOutput3l  (FPGA_Registers_getBase()+0x614)
#define	kActivatedDayTimeOutput4h  (FPGA_Registers_getBase()+0x618)
#define	kActivatedDayTimeOutput4l  (FPGA_Registers_getBase()+0x61C)
#define	kActivatedDayTimeOutput5h  (FPGA_Registers_getBase()+0x620)
#define	kActivatedDayTimeOutput5l  (FPGA_Registers_getBase()+0x624)
#define	kActivatedDayTimeOutput6h  (FPGA_Registers_getBase()+0x628)
#define	kActivatedDayTimeOutput6l  (FPGA_Registers_getBase()+0x62C)
#define	kActivatedDayTimeOutput7h  (FPGA_Registers_getBase()+0x630)
#define	kActivatedDayTimeOutput7l  (FPGA_Registers_getBase()+0x634)
#define	kActivatedDayTimeOutput8h  (FPGA_Registers_getBase()+0x638)
#define	kActivatedDayTimeOutput8l  (FPGA_Registers_getBase()+0x63C)
#define	kActivatedDayTimeOutput9h  (FPGA_Registers_getBase()+0x640)
#define	kActivatedDayTimeOutput9l  (FPGA_Registers_getBase()+0x644)
#define	kActivatedDayTimeOutput10h  (FPGA_Registers_getBase()+0x648)
#define	kActivatedDayTimeOutput10l  (FPGA_Registers_getBase()+0x64C)
#define	kActivatedDayTimeOutput11h  (FPGA_Registers_getBase()+0x650)
#define	kActivatedDayTimeOutput11l  (FPGA_Registers_getBase()+0x654)
#define	kActivatedDayTimeOutput12h  (FPGA_Registers_getBase()+0x658)
#define	kActivatedDayTimeOutput12l  (FPGA_Registers_getBase()+0x65C)
#define	kActivatedDayTimeOutput13h  (FPGA_Registers_getBase()+0x660)
#define	kActivatedDayTimeOutput13l  (FPGA_Registers_getBase()+0x664)
#define	kActivatedDayTimeOutput14h  (FPGA_Registers_getBase()+0x668)
#define	kActivatedDayTimeOutput14l  (FPGA_Registers_getBase()+0x66C)
#define	kActivatedDayTimeOutput15h  (FPGA_Registers_getBase()+0x670)
#define	kActivatedDayTimeOutput15l  (FPGA_Registers_getBase()+0x674)
#define	kActivatedDayTimeOutput16h  (FPGA_Registers_getBase()+0x678)
#define	kActivatedDayTimeOutput16l  (FPGA_Registers_getBase()+0x67C)
#define	kActivatedDayTimeOutput17h  (FPGA_Registers_getBase()+0x680)
#define	kActivatedDayTimeOutput17l  (FPGA_Registers_getBase()+0x684)
#define	kActivatedDayTimeOutput18h  (FPGA_Registers_getBase()+0x688)
#define	kActivatedDayTimeOutput18l  (FPGA_Registers_getBase()+0x68C)
#define	kActivatedDayTimeOutput19h  (FPGA_Registers_getBase()+0x690)
#define	kActivatedDayTimeOutput19l  (FPGA_Registers_getBase()+0x694)
#define	kActivatedDayTimeOutput20h  (FPGA_Registers_getBase()+0x698)
#define	kActivatedDayTimeOutput20l  (FPGA_Registers_getBase()+0x69C)
#define	kActivatedDayTimeOutput21h  (FPGA_Registers_getBase()+0x6A0)
#define	kActivatedDayTimeOutput21l  (FPGA_Registers_getBase()+0x6A4)
#define	kActivatedDayTimeOutput22h  (FPGA_Registers_getBase()+0x6A8)
#define	kActivatedDayTimeOutput22l  (FPGA_Registers_getBase()+0x6AC)
#define	kActivatedDayTimeOutput23h  (FPGA_Registers_getBase()+0x6B0)
#define	kActivatedDayTimeOutput23l  (FPGA_Registers_getBase()+0x6B4)
#define	kActivatedDayTimeOutput24h  (FPGA_Registers_getBase()+0x6B8)
#define	kActivatedDayTimeOutput24l  (FPGA_Registers_getBase()+0x6BC)
#define	kActivatedDayTimeOutput25h  (FPGA_Registers_getBase()+0x6C0)
#define	kActivatedDayTimeOutput25l  (FPGA_Registers_getBase()+0x6C4)
#define	kActivatedDayTimeOutput26h  (FPGA_Registers_getBase()+0x6C8)
#define	kActivatedDayTimeOutput26l  (FPGA_Registers_getBase()+0x6CC)
#define	kActivatedDayTimeOutput27h  (FPGA_Registers_getBase()+0x6D0)
#define	kActivatedDayTimeOutput27l  (FPGA_Registers_getBase()+0x6D4)
#define	kActivatedDayTimeOutput28h  (FPGA_Registers_getBase()+0x6D8)
#define	kActivatedDayTimeOutput28l  (FPGA_Registers_getBase()+0x6DC)
#define	kActivatedDayTimeOutput29h  (FPGA_Registers_getBase()+0x6E0)
#define	kActivatedDayTimeOutput29l  (FPGA_Registers_getBase()+0x6E4)
#define	kActivatedDayTimeOutput30h  (FPGA_Registers_getBase()+0x6E8)
#define	kActivatedDayTimeOutput30l  (FPGA_Registers_getBase()+0x6EC)
#define	kActivatedDayTimeOutput31h  (FPGA_Registers_getBase()+0x6F0)
#define	kActivatedDayTimeOutput31l  (FPGA_Registers_getBase()+0x6F4)
#define	kActivatedDayTimeOutput32h  (FPGA_Registers_getBase()+0x6F8)
#define	kActivatedDayTimeOutput32l  (FPGA_Registers_getBase()+0x6FC)
#define	kOutputMaskRT1  (FPGA_Registers_getBase()+0x700)
#define	kOutputMaskRT2  (FPGA_Registers_getBase()+0x704)
#define	kOutputMaskRT3  (FPGA_Registers_getBase()+0x708)
#define	kOutputMaskRT4  (FPGA_Registers_getBase()+0x70C)
#define	kOutputMaskRT5  (FPGA_Registers_getBase()+0x710)
#define	kOutputMaskRT6  (FPGA_Registers_getBase()+0x714)
#define	kOutputMaskRT7  (FPGA_Registers_getBase()+0x718)
#define	kOutputMaskRT8  (FPGA_Registers_getBase()+0x71C)
#define	kOutputMaskRT9  (FPGA_Registers_getBase()+0x720)
#define	kOutputMaskRT10  (FPGA_Registers_getBase()+0x724)
#define	kOutputMaskRT11  (FPGA_Registers_getBase()+0x728)
#define	kOutputMaskRT12  (FPGA_Registers_getBase()+0x72C)
#define	kOutputMaskRT13  (FPGA_Registers_getBase()+0x730)
#define	kOutputMaskRT14  (FPGA_Registers_getBase()+0x734)
#define	kOutputMaskRT15  (FPGA_Registers_getBase()+0x738)
#define	kOutputMaskRT16  (FPGA_Registers_getBase()+0x73C)
#define	kOutputMaskCT1  (FPGA_Registers_getBase()+0x740)
#define	kOutputMaskCT2  (FPGA_Registers_getBase()+0x744)
#define	kOutputMaskCT3  (FPGA_Registers_getBase()+0x748)
#define	kOutputMaskCT4  (FPGA_Registers_getBase()+0x74C)
#define	kOutputMaskCT5  (FPGA_Registers_getBase()+0x750)
#define	kOutputMaskCT6  (FPGA_Registers_getBase()+0x754)
#define	kOutputMaskCT7  (FPGA_Registers_getBase()+0x758)
#define	kOutputMaskCT8  (FPGA_Registers_getBase()+0x75C)
#define	kOutputMaskCT9  (FPGA_Registers_getBase()+0x760)
#define	kOutputMaskCT10  (FPGA_Registers_getBase()+0x764)
#define	kOutputMaskCT11  (FPGA_Registers_getBase()+0x768)
#define	kOutputMaskCT12  (FPGA_Registers_getBase()+0x76C)
#define	kOutputMaskCT13  (FPGA_Registers_getBase()+0x770)
#define	kOutputMaskCT14  (FPGA_Registers_getBase()+0x774)
#define	kOutputMaskCT15  (FPGA_Registers_getBase()+0x778)
#define	kOutputMaskCT16  (FPGA_Registers_getBase()+0x77C)
#define	kCustomTriggerRT1h  (FPGA_Registers_getBase()+0x780)
#define	kCustomTriggerRT1l  (FPGA_Registers_getBase()+0x784)
#define	kCustomTriggerRT2h  (FPGA_Registers_getBase()+0x788)
#define	kCustomTriggerRT2l  (FPGA_Registers_getBase()+0x78C)
#define	kCustomTriggerRT3h  (FPGA_Registers_getBase()+0x790)
#define	kCustomTriggerRT3l  (FPGA_Registers_getBase()+0x794)
#define	kCustomTriggerRT4h  (FPGA_Registers_getBase()+0x798)
#define	kCustomTriggerRT4l  (FPGA_Registers_getBase()+0x79C)
#define	kCustomTriggerRT5h  (FPGA_Registers_getBase()+0x7A0)
#define	kCustomTriggerRT5l  (FPGA_Registers_getBase()+0x7A4)
#define	kCustomTriggerRT6h  (FPGA_Registers_getBase()+0x7A8)
#define	kCustomTriggerRT6l  (FPGA_Registers_getBase()+0x7AC)
#define	kCustomTriggerRT7h  (FPGA_Registers_getBase()+0x7B0)
#define	kCustomTriggerRT7l  (FPGA_Registers_getBase()+0x7B4)
#define	kCustomTriggerRT8h  (FPGA_Registers_getBase()+0x7B8)
#define	kCustomTriggerRT8l  (FPGA_Registers_getBase()+0x7BC)
#define	kCustomTriggerRT9h  (FPGA_Registers_getBase()+0x7C0)
#define	kCustomTriggerRT9l  (FPGA_Registers_getBase()+0x7C4)
#define	kCustomTriggerRT10h  (FPGA_Registers_getBase()+0x7C8)
#define	kCustomTriggerRT10l  (FPGA_Registers_getBase()+0x7CC)
#define	kCustomTriggerRT11h  (FPGA_Registers_getBase()+0x7D0)
#define	kCustomTriggerRT11l  (FPGA_Registers_getBase()+0x7D4)
#define	kCustomTriggerRT12h  (FPGA_Registers_getBase()+0x7D8)
#define	kCustomTriggerRT12l  (FPGA_Registers_getBase()+0x7DC)
#define	kCustomTriggerRT13h  (FPGA_Registers_getBase()+0x7E0)
#define	kCustomTriggerRT13l  (FPGA_Registers_getBase()+0x7E4)
#define	kCustomTriggerRT14h  (FPGA_Registers_getBase()+0x7E8)
#define	kCustomTriggerRT14l  (FPGA_Registers_getBase()+0x7EC)
#define	kCustomTriggerRT15h  (FPGA_Registers_getBase()+0x7F0)
#define	kCustomTriggerRT15l  (FPGA_Registers_getBase()+0x7F4)
#define	kCustomTriggerRT16h  (FPGA_Registers_getBase()+0x7F8)
#define	kCustomTriggerRT16l  (FPGA_Registers_getBase()+0x7FC)
#define	kIntervalRollingTime1  (FPGA_Registers_getBase()+0x800)
#define	kIntervalRollingTime2  (FPGA_Registers_getBase()+0x804)
#define	kIntervalRollingTime3  (FPGA_Registers_getBase()+0x808)
#define	kIntervalRollingTime4  (FPGA_Registers_getBase()+0x80C)
#define	kIntervalRollingTime5  (FPGA_Registers_getBase()+0x810)
#define	kIntervalRollingTime6  (FPGA_Registers_getBase()+0x814)
#define	kIntervalRollingTime7  (FPGA_Registers_getBase()+0x818)
#define	kIntervalRollingTime8  (FPGA_Registers_getBase()+0x81C)
#define	kIntervalRollingTime9  (FPGA_Registers_getBase()+0x820)
#define	kIntervalRollingTime10  (FPGA_Registers_getBase()+0x824)
#define	kIntervalRollingTime11  (FPGA_Registers_getBase()+0x828)
#define	kIntervalRollingTime12  (FPGA_Registers_getBase()+0x82C)
#define	kIntervalRollingTime13  (FPGA_Registers_getBase()+0x830)
#define	kIntervalRollingTime14  (FPGA_Registers_getBase()+0x834)
#define	kIntervalRollingTime15  (FPGA_Registers_getBase()+0x838)
#define	kIntervalRollingTime16  (FPGA_Registers_getBase()+0x83C)
#define	kRollingTimeNewStateMaskInput1  (FPGA_Registers_getBase()+0x880)
#define	kRollingTimeNewStateMaskInput2  (FPGA_Registers_getBase()+0x884)
#define	kRollingTimeNewStateMaskInput3  (FPGA_Registers_getBase()+0x888)
#define	kRollingTimeNewStateMaskInput4  (FPGA_Registers_getBase()+0x88C)
#define	kRollingTimeNewStateMaskInput5  (FPGA_Registers_getBase()+0x890)
#define	kRollingTimeNewStateMaskInput6  (FPGA_Registers_getBase()+0x894)
#define	kRollingTimeNewStateMaskInput7  (FPGA_Registers_getBase()+0x898)
#define	kRollingTimeNewStateMaskInput8  (FPGA_Registers_getBase()+0x89C)
#define	kRollingTimeNewStateMaskInput9  (FPGA_Registers_getBase()+0x8A0)
#define	kRollingTimeNewStateMaskInput10  (FPGA_Registers_getBase()+0x8A4)
#define	kRollingTimeNewStateMaskInput11  (FPGA_Registers_getBase()+0x8A8)
#define	kRollingTimeNewStateMaskInput12  (FPGA_Registers_getBase()+0x8AC)
#define	kRollingTimeNewStateMaskInput13  (FPGA_Registers_getBase()+0x8B0)
#define	kRollingTimeNewStateMaskInput14  (FPGA_Registers_getBase()+0x8B4)
#define	kRollingTimeNewStateMaskInput15  (FPGA_Registers_getBase()+0x8B8)
#define	kRollingTimeNewStateMaskInput16  (FPGA_Registers_getBase()+0x8BC)
#define	kRollingTimeNewStateMaskInput17  (FPGA_Registers_getBase()+0x8C0)
#define	kRollingTimeNewStateMaskInput18  (FPGA_Registers_getBase()+0x8C4)
#define	kRollingTimeNewStateMaskInput19  (FPGA_Registers_getBase()+0x8C8)
#define	kRollingTimeNewStateMaskInput20  (FPGA_Registers_getBase()+0x8CC)
#define	kRollingTimeNewStateMaskInput21  (FPGA_Registers_getBase()+0x8D0)
#define	kRollingTimeNewStateMaskInput22  (FPGA_Registers_getBase()+0x8D4)
#define	kRollingTimeNewStateMaskInput23  (FPGA_Registers_getBase()+0x8D8)
#define	kRollingTimeNewStateMaskInput24  (FPGA_Registers_getBase()+0x8DC)
#define	kRollingTimeNewStateMaskInput25  (FPGA_Registers_getBase()+0x8E0)
#define	kRollingTimeNewStateMaskInput26  (FPGA_Registers_getBase()+0x8E4)
#define	kRollingTimeNewStateMaskInput27  (FPGA_Registers_getBase()+0x8E8)
#define	kRollingTimeNewStateMaskInput28  (FPGA_Registers_getBase()+0x8EC)
#define	kRollingTimeNewStateMaskInput29  (FPGA_Registers_getBase()+0x8F0)
#define	kRollingTimeNewStateMaskInput30  (FPGA_Registers_getBase()+0x8F4)
#define	kRollingTimeNewStateMaskInput31  (FPGA_Registers_getBase()+0x8F8)
#define	kRollingTimeNewStateMaskInput32  (FPGA_Registers_getBase()+0x8FC)
#define	kTimeEventAdInput1h  (FPGA_Registers_getBase()+0x900)
#define	kTimeEventAdInput1l  (FPGA_Registers_getBase()+0x904)
#define	kTimeEventAdInput2h  (FPGA_Registers_getBase()+0x908)
#define	kTimeEventAdInput2l  (FPGA_Registers_getBase()+0x90C)
#define	kTimeEventAdInput3h  (FPGA_Registers_getBase()+0x910)
#define	kTimeEventAdInput3l  (FPGA_Registers_getBase()+0x914)
#define	kTimeEventAdInput4h  (FPGA_Registers_getBase()+0x918)
#define	kTimeEventAdInput4l  (FPGA_Registers_getBase()+0x91C)
#define	kTimeEventAdInput5h  (FPGA_Registers_getBase()+0x920)
#define	kTimeEventAdInput5l  (FPGA_Registers_getBase()+0x924)
#define	kTimeEventAdInput6h  (FPGA_Registers_getBase()+0x928)
#define	kTimeEventAdInput6l  (FPGA_Registers_getBase()+0x92C)
#define	kTimeEventAdInput7h  (FPGA_Registers_getBase()+0x930)
#define	kTimeEventAdInput7l  (FPGA_Registers_getBase()+0x934)
#define	kTimeEventAdInput8h  (FPGA_Registers_getBase()+0x938)
#define	kTimeEventAdInput8l  (FPGA_Registers_getBase()+0x93C)
#define	kTimeEventAdInput9h  (FPGA_Registers_getBase()+0x940)
#define	kTimeEventAdInput9l  (FPGA_Registers_getBase()+0x944)
#define	kTimeEventAdInput10h  (FPGA_Registers_getBase()+0x948)
#define	kTimeEventAdInput10l  (FPGA_Registers_getBase()+0x94C)
#define	kTimeEventAdInput11h  (FPGA_Registers_getBase()+0x950)
#define	kTimeEventAdInput11l  (FPGA_Registers_getBase()+0x954)
#define	kTimeEventAdInput12h  (FPGA_Registers_getBase()+0x958)
#define	kTimeEventAdInput12l  (FPGA_Registers_getBase()+0x95C)
#define	kTimeEventAdInput13h  (FPGA_Registers_getBase()+0x960)
#define	kTimeEventAdInput13l  (FPGA_Registers_getBase()+0x964)
#define	kTimeEventAdInput14h  (FPGA_Registers_getBase()+0x968)
#define	kTimeEventAdInput14l  (FPGA_Registers_getBase()+0x96C)
#define	kTimeEventAdInput15h  (FPGA_Registers_getBase()+0x970)
#define	kTimeEventAdInput15l  (FPGA_Registers_getBase()+0x974)
#define	kTimeEventAdInput16h  (FPGA_Registers_getBase()+0x978)
#define	kTimeEventAdInput16l  (FPGA_Registers_getBase()+0x97C)
#define	kTimeEventAdInput17h  (FPGA_Registers_getBase()+0x980)
#define	kTimeEventAdInput17l  (FPGA_Registers_getBase()+0x984)
#define	kTimeEventAdInput18h  (FPGA_Registers_getBase()+0x988)
#define	kTimeEventAdInput18l  (FPGA_Registers_getBase()+0x98C)
#define	kTimeEventAdInput19h  (FPGA_Registers_getBase()+0x990)
#define	kTimeEventAdInput19l  (FPGA_Registers_getBase()+0x994)
#define	kTimeEventAdInput20h  (FPGA_Registers_getBase()+0x998)
#define	kTimeEventAdInput20l  (FPGA_Registers_getBase()+0x99C)
#define	kTimeEventAdInput21h  (FPGA_Registers_getBase()+0x9A0)
#define	kTimeEventAdInput21l  (FPGA_Registers_getBase()+0x9A4)
#define	kTimeEventAdInput22h  (FPGA_Registers_getBase()+0x9A8)
#define	kTimeEventAdInput22l  (FPGA_Registers_getBase()+0x9AC)
#define	kTimeEventAdInput23h  (FPGA_Registers_getBase()+0x9B0)
#define	kTimeEventAdInput23l  (FPGA_Registers_getBase()+0x9B4)
#define	kTimeEventAdInput24h  (FPGA_Registers_getBase()+0x9B8)
#define	kTimeEventAdInput24l  (FPGA_Registers_getBase()+0x9BC)
#define	kTimeEventAdInput25h  (FPGA_Registers_getBase()+0x9C0)
#define	kTimeEventAdInput25l  (FPGA_Registers_getBase()+0x9C4)
#define	kTimeEventAdInput26h  (FPGA_Registers_getBase()+0x9C8)
#define	kTimeEventAdInput26l  (FPGA_Registers_getBase()+0x9CC)
#define	kTimeEventAdInput27h  (FPGA_Registers_getBase()+0x9D0)
#define	kTimeEventAdInput27l  (FPGA_Registers_getBase()+0x9D4)
#define	kTimeEventAdInput28h  (FPGA_Registers_getBase()+0x9D8)
#define	kTimeEventAdInput28l  (FPGA_Registers_getBase()+0x9DC)
#define	kTimeEventAdInput29h  (FPGA_Registers_getBase()+0x9E0)
#define	kTimeEventAdInput29l  (FPGA_Registers_getBase()+0x9E4)
#define	kTimeEventAdInput30h  (FPGA_Registers_getBase()+0x9E8)
#define	kTimeEventAdInput30l  (FPGA_Registers_getBase()+0x9EC)
#define	kTimeEventAdInput31h  (FPGA_Registers_getBase()+0x9F0)
#define	kTimeEventAdInput31l  (FPGA_Registers_getBase()+0x9F4)
#define	kTimeEventAdInput32h  (FPGA_Registers_getBase()+0x9F8)
#define	kTimeEventAdInput32l  (FPGA_Registers_getBase()+0x9FC)
#define	kTimeEventAdInput33h  (FPGA_Registers_getBase()+0xA00)
#define	kTimeEventAdInput33l  (FPGA_Registers_getBase()+0xA04)
#define	kTimeEventAdInput34h  (FPGA_Registers_getBase()+0xA08)
#define	kTimeEventAdInput34l  (FPGA_Registers_getBase()+0xA0C)
#define	kTimeEventAdInput35h  (FPGA_Registers_getBase()+0xA10)
#define	kTimeEventAdInput35l  (FPGA_Registers_getBase()+0xA14)
#define	kTimeEventAdInput36h  (FPGA_Registers_getBase()+0xA18)
#define	kTimeEventAdInput36l  (FPGA_Registers_getBase()+0xA1C)
#define	kTimeEventAdInput37h  (FPGA_Registers_getBase()+0xA20)
#define	kTimeEventAdInput37l  (FPGA_Registers_getBase()+0xA24)
#define	kTimeEventAdInput38h  (FPGA_Registers_getBase()+0xA28)
#define	kTimeEventAdInput38l  (FPGA_Registers_getBase()+0xA2C)
#define	kTimeEventAdInput39h  (FPGA_Registers_getBase()+0xA30)
#define	kTimeEventAdInput39l  (FPGA_Registers_getBase()+0xA34)
#define	kTimeEventAdInput40h  (FPGA_Registers_getBase()+0xA38)
#define	kTimeEventAdInput40l  (FPGA_Registers_getBase()+0xA3C)
#define	kTimeEventAdInput41h  (FPGA_Registers_getBase()+0xA40)
#define	kTimeEventAdInput41l  (FPGA_Registers_getBase()+0xA44)
#define	kTimeEventAdInput42h  (FPGA_Registers_getBase()+0xA48)
#define	kTimeEventAdInput42l  (FPGA_Registers_getBase()+0xA4C)
#define	kTimeEventAdInput43h  (FPGA_Registers_getBase()+0xA50)
#define	kTimeEventAdInput43l  (FPGA_Registers_getBase()+0xA54)
#define	kTimeEventAdInput44h  (FPGA_Registers_getBase()+0xA58)
#define	kTimeEventAdInput44l  (FPGA_Registers_getBase()+0xA5C)
#define	kTimeEventAdInput45h  (FPGA_Registers_getBase()+0xA60)
#define	kTimeEventAdInput45l  (FPGA_Registers_getBase()+0xA64)
#define	kTimeEventAdInput46h  (FPGA_Registers_getBase()+0xA68)
#define	kTimeEventAdInput46l  (FPGA_Registers_getBase()+0xA6C)
#define	kTimeEventAdInput47h  (FPGA_Registers_getBase()+0xA70)
#define	kTimeEventAdInput47l  (FPGA_Registers_getBase()+0xA74)
#define	kTimeEventAdInput48h  (FPGA_Registers_getBase()+0xA78)
#define	kTimeEventAdInput48l  (FPGA_Registers_getBase()+0xA7C)
#define	kTimeEventAdInput49h  (FPGA_Registers_getBase()+0xA80)
#define	kTimeEventAdInput49l  (FPGA_Registers_getBase()+0xA84)
#define	kTimeEventAdInput50h  (FPGA_Registers_getBase()+0xA88)
#define	kTimeEventAdInput50l  (FPGA_Registers_getBase()+0xA8C)
#define	kTimeEventAdInput51h  (FPGA_Registers_getBase()+0xA90)
#define	kTimeEventAdInput51l  (FPGA_Registers_getBase()+0xA94)
#define	kTimeEventAdInput52h  (FPGA_Registers_getBase()+0xA98)
#define	kTimeEventAdInput52l  (FPGA_Registers_getBase()+0xA9C)
#define	kTimeEventAdInput53h  (FPGA_Registers_getBase()+0xAA0)
#define	kTimeEventAdInput53l  (FPGA_Registers_getBase()+0xAA4)
#define	kTimeEventAdInput54h  (FPGA_Registers_getBase()+0xAA8)
#define	kTimeEventAdInput54l  (FPGA_Registers_getBase()+0xAAC)
#define	kTimeEventAdInput55h  (FPGA_Registers_getBase()+0xAB0)
#define	kTimeEventAdInput55l  (FPGA_Registers_getBase()+0xAB4)
#define	kTimeEventAdInput56h  (FPGA_Registers_getBase()+0xAB8)
#define	kTimeEventAdInput56l  (FPGA_Registers_getBase()+0xABC)
#define	kTimeEventAdInput57h  (FPGA_Registers_getBase()+0xAC0)
#define	kTimeEventAdInput57l  (FPGA_Registers_getBase()+0xAC4)
#define	kTimeEventAdInput58h  (FPGA_Registers_getBase()+0xAC8)
#define	kTimeEventAdInput58l  (FPGA_Registers_getBase()+0xACC)
#define	kTimeEventAdInput59h  (FPGA_Registers_getBase()+0xAD0)
#define	kTimeEventAdInput59l  (FPGA_Registers_getBase()+0xAD4)
#define	kTimeEventAdInput60h  (FPGA_Registers_getBase()+0xAD8)
#define	kTimeEventAdInput60l  (FPGA_Registers_getBase()+0xADC)
#define	kTimeEventAdInput61h  (FPGA_Registers_getBase()+0xAE0)
#define	kTimeEventAdInput61l  (FPGA_Registers_getBase()+0xAE4)
#define	kTimeEventAdInput62h  (FPGA_Registers_getBase()+0xAE8)
#define	kTimeEventAdInput62l  (FPGA_Registers_getBase()+0xAEC)
#define	kTimeEventAdInput63h  (FPGA_Registers_getBase()+0xAF0)
#define	kTimeEventAdInput63l  (FPGA_Registers_getBase()+0xAF4)
#define	kTimeEventAdInput64h  (FPGA_Registers_getBase()+0xAF8)
#define	kTimeEventAdInput64l  (FPGA_Registers_getBase()+0xAFC)
#define	kTimeEventAdInput65h  (FPGA_Registers_getBase()+0xB00)
#define	kTimeEventAdInput65l  (FPGA_Registers_getBase()+0xB04)
#define	kTimeEventAdInput66h  (FPGA_Registers_getBase()+0xB08)
#define	kTimeEventAdInput66l  (FPGA_Registers_getBase()+0xB0C)
#define	kTimeEventAdInput67h  (FPGA_Registers_getBase()+0xB10)
#define	kTimeEventAdInput67l  (FPGA_Registers_getBase()+0xB14)
#define	kTimeEventAdInput68h  (FPGA_Registers_getBase()+0xB18)
#define	kTimeEventAdInput68l  (FPGA_Registers_getBase()+0xB1C)
#define	kTimeEventAdInput69h  (FPGA_Registers_getBase()+0xB20)
#define	kTimeEventAdInput69l  (FPGA_Registers_getBase()+0xB24)
#define	kTimeEventAdInput70h  (FPGA_Registers_getBase()+0xB28)
#define	kTimeEventAdInput70l  (FPGA_Registers_getBase()+0xB2C)
#define	kTimeEventAdInput71h  (FPGA_Registers_getBase()+0xB30)
#define	kTimeEventAdInput71l  (FPGA_Registers_getBase()+0xB34)
#define	kTimeEventAdInput72h  (FPGA_Registers_getBase()+0xB38)
#define	kTimeEventAdInput72l  (FPGA_Registers_getBase()+0xB3C)
#define	kTimeEventAdInput73h  (FPGA_Registers_getBase()+0xB40)
#define	kTimeEventAdInput73l  (FPGA_Registers_getBase()+0xB44)
#define	kTimeEventAdInput74h  (FPGA_Registers_getBase()+0xB48)
#define	kTimeEventAdInput74l  (FPGA_Registers_getBase()+0xB4C)
#define	kTimeEventAdInput75h  (FPGA_Registers_getBase()+0xB50)
#define	kTimeEventAdInput75l  (FPGA_Registers_getBase()+0xB54)
#define	kTimeEventAdInput76h  (FPGA_Registers_getBase()+0xB58)
#define	kTimeEventAdInput76l  (FPGA_Registers_getBase()+0xB5C)
#define	kTimeEventAdInput77h  (FPGA_Registers_getBase()+0xB60)
#define	kTimeEventAdInput77l  (FPGA_Registers_getBase()+0xB64)
#define	kTimeEventAdInput78h  (FPGA_Registers_getBase()+0xB68)
#define	kTimeEventAdInput78l  (FPGA_Registers_getBase()+0xB6C)
#define	kTimeEventAdInput79h  (FPGA_Registers_getBase()+0xB70)
#define	kTimeEventAdInput79l  (FPGA_Registers_getBase()+0xB74)
#define	kTimeEventAdInput80h  (FPGA_Registers_getBase()+0xB78)
#define	kTimeEventAdInput80l  (FPGA_Registers_getBase()+0xB7C)
#define	kTimeEventAdInput81h  (FPGA_Registers_getBase()+0xB80)
#define	kTimeEventAdInput81l  (FPGA_Registers_getBase()+0xB84)
#define	kTimeEventAdInput82h  (FPGA_Registers_getBase()+0xB88)
#define	kTimeEventAdInput82l  (FPGA_Registers_getBase()+0xB8C)
#define	kTimeEventAdInput83h  (FPGA_Registers_getBase()+0xB90)
#define	kTimeEventAdInput83l  (FPGA_Registers_getBase()+0xB94)
#define	kTimeEventAdInput84h  (FPGA_Registers_getBase()+0xB98)
#define	kTimeEventAdInput84l  (FPGA_Registers_getBase()+0xB9C)
#define	kTimeEventAdInput85h  (FPGA_Registers_getBase()+0xBA0)
#define	kTimeEventAdInput85l  (FPGA_Registers_getBase()+0xBA4)
#define	kTimeEventAdInput86h  (FPGA_Registers_getBase()+0xBA8)
#define	kTimeEventAdInput86l  (FPGA_Registers_getBase()+0xBAC)
#define	kTimeEventAdInput87h  (FPGA_Registers_getBase()+0xBB0)
#define	kTimeEventAdInput87l  (FPGA_Registers_getBase()+0xBB4)
#define	kTimeEventAdInput88h  (FPGA_Registers_getBase()+0xBB8)
#define	kTimeEventAdInput88l  (FPGA_Registers_getBase()+0xBBC)
#define	kTimeEventAdInput89h  (FPGA_Registers_getBase()+0xBC0)
#define	kTimeEventAdInput89l  (FPGA_Registers_getBase()+0xBC4)
#define	kTimeEventAdInput90h  (FPGA_Registers_getBase()+0xBC8)
#define	kTimeEventAdInput90l  (FPGA_Registers_getBase()+0xBCC)
#define	kTimeEventAdInput91h  (FPGA_Registers_getBase()+0xBD0)
#define	kTimeEventAdInput91l  (FPGA_Registers_getBase()+0xBD4)
#define	kTimeEventAdInput92h  (FPGA_Registers_getBase()+0xBD8)
#define	kTimeEventAdInput92l  (FPGA_Registers_getBase()+0xBDC)
#define	kTimeEventAdInput93h  (FPGA_Registers_getBase()+0xBE0)
#define	kTimeEventAdInput93l  (FPGA_Registers_getBase()+0xBE4)
#define	kTimeEventAdInput94h  (FPGA_Registers_getBase()+0xBE8)
#define	kTimeEventAdInput94l  (FPGA_Registers_getBase()+0xBEC)
#define	kTimeEventAdInput95h  (FPGA_Registers_getBase()+0xBF0)
#define	kTimeEventAdInput95l  (FPGA_Registers_getBase()+0xBF4)
#define	kTimeEventAdInput96h  (FPGA_Registers_getBase()+0xBF8)
#define	kTimeEventAdInput96l  (FPGA_Registers_getBase()+0xBFC)
#define	kconfig_DebounceAdInputs  (FPGA_Registers_getBase()+0xD80)
#define	kEnable_AdInputsh  (FPGA_Registers_getBase()+0xE00)
#define	kEnable_AdInputsm  (FPGA_Registers_getBase()+0xE04)
#define	kEnable_AdInputsl  (FPGA_Registers_getBase()+0xE08)
#define	kpolarity_AdInputs81to96  (FPGA_Registers_getBase()+0xE10)
#define	kpolarity_AdInputs65to80  (FPGA_Registers_getBase()+0xE14)
#define	kpolarity_AdInputs49to64  (FPGA_Registers_getBase()+0xE18)
#define	kpolarity_AdInputs33to48  (FPGA_Registers_getBase()+0xE1C)
#define	kpolarity_AdInputs17to32  (FPGA_Registers_getBase()+0xE20)
#define	kpolarity_AdInputs1to16  (FPGA_Registers_getBase()+0xE24)
#define	kglobal_Control  (FPGA_Registers_getBase()+0xE30)
#define	kFPGA_Config  (FPGA_Registers_getBase()+0xFF0)
#define	kFPGA_Version  (FPGA_Registers_getBase()+0xFFC)

//u32 kConfigInputXLowRegBaseAdr;
//u32 kConfigInputXHighRegBaseAdr;
//u32 kConfigOutputXRegBaseAdr;
//u32 kImmediateOutputEnableRegBaseAdr;
//u32 kOutputXDestMaskRegBaseAdr;
//u32 kIntervalRollingTimeXRegBaseAdr;
//u32 kConfigRollingTimeXRegBaseAdr;
//u32 kOutputMaskRollingTimeXRegBaseAdr;
//u32 kRollingTimeNewStateInpXMaskRegBaseAdr;
//u32 kCustomTriggerRollingTimeXRegBaseAdr;
//u32 kOutputMaskCustomTriggerRegBaseAdr;
//u32 kActivatedDayTimeOutputRegBaseAdr;
//u32 kLastEndPeriodRollingTimeRegBaseAdr;
//u32 kTimeEventInputRegBaseAdr;
//u32 gNextSyncDayTimeLow;
//u32 gNextSyncDayTimeMed;
//u32 gNextSyncDayTimeHigh;
//u32 gOutputEnableLow;
//u32 gOutputEnableHigh;
//u32 gOutputEventEventLow;
//u32 gOutputEventEventHigh;
//u32 gOutputEventEventAckLow;
//u32 gOutputEventEventAckHigh;
//u32 gCustomTriggerEvent;
//u32 gCustomTriggerEventAck;
//u32 gReceivedArmedStateLow;
//u32 gReceivedArmedStateHigh;
//u32 gReceivedArmedStateAckLow;
//u32 gReceivedArmedStateAckHigh;
//u32 gReceivedNotArmedStateLow;
//u32 gReceivedNotArmedStateHigh;
//u32 gReceivedNotArmedStateAckLow;
//u32 gReceivedNotArmedStateAckHigh;
//u32 gReceivedGpsSynchroTimeLow;
//u32 gReceivedGpsSynchroTimeHigh;
//u32 gReceivedGpsSynchroState;
//u32 gReceivedGpsSynchroStateAck;
//u32 kDayTimeLow;
//u32 kDayTimeMed;
//u32 kDayTimeHigh;
//u32 kNextSyncDayTimeh;
//u32 kNextSyncDayTimel;
//u32 kCurrentDayTimeh;
//u32 kCurrentDayTimel;
//u32 kReceivedArmedState;
//u32 kReceivedArmedState_Ack;
//u32 kReceivedNotArmedState;
//u32 kReceivedNotArmedState_Ack;
//u32 kReceivedGpsState;
//u32 kReceivedGpsState_Ack;
//u32 kReceivedGpsSyncTimeh;
//u32 kReceivedGpsSyncTimel;
//u32 kReceivedSoftwareInput;
//u32 kReceivedSoftwareInput_Ack;
//u32 kRollingTimeEvent;
//u32 kRollingTimeEvent_Ack;
//u32 kSoftwareInputPulse;
//u32 kSoftwareAdInputPulseh;
//u32 kSoftwareAdInputPulsem;
//u32 kSoftwareAdInputPulsel;
//u32 kInputsState;
//u32 kAdInputsStateh;
//u32 kAdInputsStatem;
//u32 kAdInputsStatel;
//u32 kReceivedAdInputsEventh;
//u32 kReceivedAdInputsEventm;
//u32 kReceivedAdInputsEventl;
//u32 kReceivedAdInputsEvent_Ackh;
//u32 kReceivedAdInputsEvent_Ackm;
//u32 kReceivedAdInputsEvent_Ackl;
//u32 kReceivedSoftwareAdInputh;
//u32 kReceivedSoftwareAdInputm;
//u32 kReceivedSoftwareAdInputl;
//u32 kReceivedSoftwareAdInput_Ackh;
//u32 kReceivedSoftwareAdInput_Ackm;
//u32 kReceivedSoftwareAdInput_Ackl;
////------------------ FPGA V5.0 -------------------
//u32 kPulsesOR;
//u32 kInputsAND;
//u32 kConfigInputActiveDelay;
//u32 kConfigInputNotActiveDelay;
//u32 kReceivedInputActiveDelayEvent;
//u32 kReceivedInputActiveDelayEvent_Ack;
//u32 kReceivedInputNotActiveDelayEvent;
//u32 kReceivedInputNotActiveDelayEvent_Ack;
//u32 kReceivedOROnePulseEvent;
//u32 kReceivedOROnePulseEvent_Ack;
////------------------ FPGA V5.0 (end) -------------
//u32 kTimeEventInput1h;
//u32 kTimeEventInput1l;
//u32 kTimeEventInput2h;
//u32 kTimeEventInput2l;
//u32 kTimeEventInput3h;
//u32 kTimeEventInput3l;
//u32 kTimeEventInput4h;
//u32 kTimeEventInput4l;
//u32 kTimeEventInput5h;
//u32 kTimeEventInput5l;
//u32 kTimeEventInput6h;
//u32 kTimeEventInput6l;
//u32 kTimeEventInput7h;
//u32 kTimeEventInput7l;
//u32 kTimeEventInput8h;
//u32 kTimeEventInput8l;
//u32 kTimeEventInput9h;
//u32 kTimeEventInput9l;
//u32 kTimeEventInput10h;
//u32 kTimeEventInput10l;
//u32 kTimeEventInput11h;
//u32 kTimeEventInput11l;
//u32 kTimeEventInput12h;
//u32 kTimeEventInput12l;
//u32 kTimeEventInput13h;
//u32 kTimeEventInput13l;
//u32 kTimeEventInput14h;
//u32 kTimeEventInput14l;
//u32 kTimeEventInput15h;
//u32 kTimeEventInput15l;
//u32 kTimeEventInput16h;
//u32 kTimeEventInput16l;
//u32 kTimeEventInput17h;
//u32 kTimeEventInput17l;
//u32 kTimeEventInput18h;
//u32 kTimeEventInput18l;
//u32 kTimeEventInput19h;
//u32 kTimeEventInput19l;
//u32 kTimeEventInput20h;
//u32 kTimeEventInput20l;
//u32 kTimeEventInput21h;
//u32 kTimeEventInput21l;
//u32 kTimeEventInput22h;
//u32 kTimeEventInput22l;
//u32 kTimeEventInput23h;
//u32 kTimeEventInput23l;
//u32 kTimeEventInput24h;
//u32 kTimeEventInput24l;
//u32 kTimeEventInput25h;
//u32 kTimeEventInput25l;
//u32 kTimeEventInput26h;
//u32 kTimeEventInput26l;
//u32 kTimeEventInput27h;
//u32 kTimeEventInput27l;
//u32 kTimeEventInput28h;
//u32 kTimeEventInput28l;
//u32 kTimeEventInput29h;
//u32 kTimeEventInput29l;
//u32 kTimeEventInput30h;
//u32 kTimeEventInput30l;
//u32 kTimeEventInput31h;
//u32 kTimeEventInput31l;
//u32 kTimeEventInput32h;
//u32 kTimeEventInput32l;
//u32 kConfigRollingTime1h;
//u32 kConfigRollingTime1l;
//u32 kConfigRollingTime2h;
//u32 kConfigRollingTime2l;
//u32 kConfigRollingTime3h;
//u32 kConfigRollingTime3l;
//u32 kConfigRollingTime4h;
//u32 kConfigRollingTime4l;
//u32 kConfigRollingTime5h;
//u32 kConfigRollingTime5l;
//u32 kConfigRollingTime6h;
//u32 kConfigRollingTime6l;
//u32 kConfigRollingTime7h;
//u32 kConfigRollingTime7l;
//u32 kConfigRollingTime8h;
//u32 kConfigRollingTime8l;
//u32 kConfigRollingTime9h;
//u32 kConfigRollingTime9l;
//u32 kConfigRollingTime10h;
//u32 kConfigRollingTime10l;
//u32 kConfigRollingTime11h;
//u32 kConfigRollingTime11l;
//u32 kConfigRollingTime12h;
//u32 kConfigRollingTime12l;
//u32 kConfigRollingTime13h;
//u32 kConfigRollingTime13l;
//u32 kConfigRollingTime14h;
//u32 kConfigRollingTime14l;
//u32 kConfigRollingTime15h;
//u32 kConfigRollingTime15l;
//u32 kConfigRollingTime16h;
//u32 kConfigRollingTime16l;
//u32 kRollingTime1h;
//u32 kRollingTime1l;
//u32 kRollingTime2h;
//u32 kRollingTime2l;
//u32 kRollingTime3h;
//u32 kRollingTime3l;
//u32 kRollingTime4h;
//u32 kRollingTime4l;
//u32 kRollingTime5h;
//u32 kRollingTime5l;
//u32 kRollingTime6h;
//u32 kRollingTime6l;
//u32 kRollingTime7h;
//u32 kRollingTime7l;
//u32 kRollingTime8h;
//u32 kRollingTime8l;
//u32 kRollingTime9h;
//u32 kRollingTime9l;
//u32 kRollingTime10h;
//u32 kRollingTime10l;
//u32 kRollingTime11h;
//u32 kRollingTime11l;
//u32 kRollingTime12h;
//u32 kRollingTime12l;
//u32 kRollingTime13h;
//u32 kRollingTime13l;
//u32 kRollingTime14h;
//u32 kRollingTime14l;
//u32 kRollingTime15h;
//u32 kRollingTime15l;
//u32 kRollingTime16h;
//u32 kRollingTime16l;
//u32 kconfig_output1h;
//u32 kconfig_output1l;
//u32 kconfig_output2h;
//u32 kconfig_output2l;
//u32 kconfig_output3h;
//u32 kconfig_output3l;
//u32 kconfig_output4h;
//u32 kconfig_output4l;
//u32 kconfig_output5h;
//u32 kconfig_output5l;
//u32 kconfig_output6h;
//u32 kconfig_output6l;
//u32 kconfig_output7h;
//u32 kconfig_output7l;
//u32 kconfig_output8h;
//u32 kconfig_output8l;
//u32 kconfig_output9h;
//u32 kconfig_output9l;
//u32 kconfig_output10h;
//u32 kconfig_output10l;
//u32 kconfig_output11h;
//u32 kconfig_output11l;
//u32 kconfig_output12h;
//u32 kconfig_output12l;
//u32 kconfig_output13h;
//u32 kconfig_output13l;
//u32 kconfig_output14h;
//u32 kconfig_output14l;
//u32 kconfig_output15h;
//u32 kconfig_output15l;
//u32 kconfig_output16h;
//u32 kconfig_output16l;
//u32 kconfig_output17h;
//u32 kconfig_output17l;
//u32 kconfig_output18h;
//u32 kconfig_output18l;
//u32 kconfig_output19h;
//u32 kconfig_output19l;
//u32 kconfig_output20h;
//u32 kconfig_output20l;
//u32 kconfig_output21h;
//u32 kconfig_output21l;
//u32 kconfig_output22h;
//u32 kconfig_output22l;
//u32 kconfig_output23h;
//u32 kconfig_output23l;
//u32 kconfig_output24h;
//u32 kconfig_output24l;
//u32 kconfig_output25h;
//u32 kconfig_output25l;
//u32 kconfig_output26h;
//u32 kconfig_output26l;
//u32 kconfig_output27h;
//u32 kconfig_output27l;
//u32 kconfig_output28h;
//u32 kconfig_output28l;
//u32 kconfig_output29h;
//u32 kconfig_output29l;
//u32 kconfig_output30h;
//u32 kconfig_output30l;
//u32 kconfig_output31h;
//u32 kconfig_output31l;
//u32 kconfig_output32h;
//u32 kconfig_output32l;
//u32 kconfig_input1;
//u32 kconfig_input2;
//u32 kconfig_input3;
//u32 kconfig_input4;
//u32 kconfig_input5;
//u32 kconfig_input6;
//u32 kconfig_input7;
//u32 kconfig_input8;
//u32 kconfig_input9;
//u32 kconfig_input10;
//u32 kconfig_input11;
//u32 kconfig_input12;
//u32 kconfig_input13;
//u32 kconfig_input14;
//u32 kconfig_input15;
//u32 kconfig_input16;
//u32 kconfig_input17;
//u32 kconfig_input18;
//u32 kconfig_input19;
//u32 kconfig_input20;
//u32 kconfig_input21;
//u32 kconfig_input22;
//u32 kconfig_input23;
//u32 kconfig_input24;
//u32 kconfig_input25;
//u32 kconfig_input26;
//u32 kconfig_input27;
//u32 kconfig_input28;
//u32 kconfig_input29;
//u32 kconfig_input30;
//u32 kconfig_input31;
//u32 kconfig_input32;
//u32 kOutput1DestinationMask;
//u32 kOutput2DestinationMask;
//u32 kOutput3DestinationMask;
//u32 kOutput4DestinationMask;
//u32 kOutput5DestinationMask;
//u32 kOutput6DestinationMask;
//u32 kOutput7DestinationMask;
//u32 kOutput8DestinationMask;
//u32 kOutput9DestinationMask;
//u32 kOutput10DestinationMask;
//u32 kOutput11DestinationMask;
//u32 kOutput12DestinationMask;
//u32 kOutput13DestinationMask;
//u32 kOutput14DestinationMask;
//u32 kOutput15DestinationMask;
//u32 kOutput16DestinationMask;
//u32 kOutput17DestinationMask;
//u32 kOutput18DestinationMask;
//u32 kOutput19DestinationMask;
//u32 kOutput20DestinationMask;
//u32 kOutput21DestinationMask;
//u32 kOutput22DestinationMask;
//u32 kOutput23DestinationMask;
//u32 kOutput24DestinationMask;
//u32 kOutput25DestinationMask;
//u32 kOutput26DestinationMask;
//u32 kOutput27DestinationMask;
//u32 kOutput28DestinationMask;
//u32 kOutput29DestinationMask;
//u32 kOutput30DestinationMask;
//u32 kOutput31DestinationMask;
//u32 kOutput32DestinationMask;
//u32 kOuputsEnable;
//u32 kCustomTriggerEvent;
//u32 kCustomTriggerEvent_Ack;
//u32 kOutputEvent;
//u32 kOutputEvent_Ack;
//u32 kImmediateOutputEnable;
//u32 kCustomTriggerEnable;
//u32 kResetOutputs;
//u32 kOutputsPolarity;
//u32 kGenericInputs;
//u32 kGenericOutputs;
//u32 kActivatedDayTimeOutput1h;
//u32 kActivatedDayTimeOutput1l;
//u32 kActivatedDayTimeOutput2h;
//u32 kActivatedDayTimeOutput2l;
//u32 kActivatedDayTimeOutput3h;
//u32 kActivatedDayTimeOutput3l;
//u32 kActivatedDayTimeOutput4h;
//u32 kActivatedDayTimeOutput4l;
//u32 kActivatedDayTimeOutput5h;
//u32 kActivatedDayTimeOutput5l;
//u32 kActivatedDayTimeOutput6h;
//u32 kActivatedDayTimeOutput6l;
//u32 kActivatedDayTimeOutput7h;
//u32 kActivatedDayTimeOutput7l;
//u32 kActivatedDayTimeOutput8h;
//u32 kActivatedDayTimeOutput8l;
//u32 kActivatedDayTimeOutput9h;
//u32 kActivatedDayTimeOutput9l;
//u32 kActivatedDayTimeOutput10h;
//u32 kActivatedDayTimeOutput10l;
//u32 kActivatedDayTimeOutput11h;
//u32 kActivatedDayTimeOutput11l;
//u32 kActivatedDayTimeOutput12h;
//u32 kActivatedDayTimeOutput12l;
//u32 kActivatedDayTimeOutput13h;
//u32 kActivatedDayTimeOutput13l;
//u32 kActivatedDayTimeOutput14h;
//u32 kActivatedDayTimeOutput14l;
//u32 kActivatedDayTimeOutput15h;
//u32 kActivatedDayTimeOutput15l;
//u32 kActivatedDayTimeOutput16h;
//u32 kActivatedDayTimeOutput16l;
//u32 kActivatedDayTimeOutput17h;
//u32 kActivatedDayTimeOutput17l;
//u32 kActivatedDayTimeOutput18h;
//u32 kActivatedDayTimeOutput18l;
//u32 kActivatedDayTimeOutput19h;
//u32 kActivatedDayTimeOutput19l;
//u32 kActivatedDayTimeOutput20h;
//u32 kActivatedDayTimeOutput20l;
//u32 kActivatedDayTimeOutput21h;
//u32 kActivatedDayTimeOutput21l;
//u32 kActivatedDayTimeOutput22h;
//u32 kActivatedDayTimeOutput22l;
//u32 kActivatedDayTimeOutput23h;
//u32 kActivatedDayTimeOutput23l;
//u32 kActivatedDayTimeOutput24h;
//u32 kActivatedDayTimeOutput24l;
//u32 kActivatedDayTimeOutput25h;
//u32 kActivatedDayTimeOutput25l;
//u32 kActivatedDayTimeOutput26h;
//u32 kActivatedDayTimeOutput26l;
//u32 kActivatedDayTimeOutput27h;
//u32 kActivatedDayTimeOutput27l;
//u32 kActivatedDayTimeOutput28h;
//u32 kActivatedDayTimeOutput28l;
//u32 kActivatedDayTimeOutput29h;
//u32 kActivatedDayTimeOutput29l;
//u32 kActivatedDayTimeOutput30h;
//u32 kActivatedDayTimeOutput30l;
//u32 kActivatedDayTimeOutput31h;
//u32 kActivatedDayTimeOutput31l;
//u32 kActivatedDayTimeOutput32h;
//u32 kActivatedDayTimeOutput32l;
//u32 kOutputMaskRT1;
//u32 kOutputMaskRT2;
//u32 kOutputMaskRT3;
//u32 kOutputMaskRT4;
//u32 kOutputMaskRT5;
//u32 kOutputMaskRT6;
//u32 kOutputMaskRT7;
//u32 kOutputMaskRT8;
//u32 kOutputMaskRT9;
//u32 kOutputMaskRT10;
//u32 kOutputMaskRT11;
//u32 kOutputMaskRT12;
//u32 kOutputMaskRT13;
//u32 kOutputMaskRT14;
//u32 kOutputMaskRT15;
//u32 kOutputMaskRT16;
//u32 kOutputMaskCT1;
//u32 kOutputMaskCT2;
//u32 kOutputMaskCT3;
//u32 kOutputMaskCT4;
//u32 kOutputMaskCT5;
//u32 kOutputMaskCT6;
//u32 kOutputMaskCT7;
//u32 kOutputMaskCT8;
//u32 kOutputMaskCT9;
//u32 kOutputMaskCT10;
//u32 kOutputMaskCT11;
//u32 kOutputMaskCT12;
//u32 kOutputMaskCT13;
//u32 kOutputMaskCT14;
//u32 kOutputMaskCT15;
//u32 kOutputMaskCT16;
//u32 kCustomTriggerRT1h;
//u32 kCustomTriggerRT1l;
//u32 kCustomTriggerRT2h;
//u32 kCustomTriggerRT2l;
//u32 kCustomTriggerRT3h;
//u32 kCustomTriggerRT3l;
//u32 kCustomTriggerRT4h;
//u32 kCustomTriggerRT4l;
//u32 kCustomTriggerRT5h;
//u32 kCustomTriggerRT5l;
//u32 kCustomTriggerRT6h;
//u32 kCustomTriggerRT6l;
//u32 kCustomTriggerRT7h;
//u32 kCustomTriggerRT7l;
//u32 kCustomTriggerRT8h;
//u32 kCustomTriggerRT8l;
//u32 kCustomTriggerRT9h;
//u32 kCustomTriggerRT9l;
//u32 kCustomTriggerRT10h;
//u32 kCustomTriggerRT10l;
//u32 kCustomTriggerRT11h;
//u32 kCustomTriggerRT11l;
//u32 kCustomTriggerRT12h;
//u32 kCustomTriggerRT12l;
//u32 kCustomTriggerRT13h;
//u32 kCustomTriggerRT13l;
//u32 kCustomTriggerRT14h;
//u32 kCustomTriggerRT14l;
//u32 kCustomTriggerRT15h;
//u32 kCustomTriggerRT15l;
//u32 kCustomTriggerRT16h;
//u32 kCustomTriggerRT16l;
//u32 kIntervalRollingTime1;
//u32 kIntervalRollingTime2;
//u32 kIntervalRollingTime3;
//u32 kIntervalRollingTime4;
//u32 kIntervalRollingTime5;
//u32 kIntervalRollingTime6;
//u32 kIntervalRollingTime7;
//u32 kIntervalRollingTime8;
//u32 kIntervalRollingTime9;
//u32 kIntervalRollingTime10;
//u32 kIntervalRollingTime11;
//u32 kIntervalRollingTime12;
//u32 kIntervalRollingTime13;
//u32 kIntervalRollingTime14;
//u32 kIntervalRollingTime15;
//u32 kIntervalRollingTime16;
//u32 kRollingTimeNewStateMaskInput1;
//u32 kRollingTimeNewStateMaskInput2;
//u32 kRollingTimeNewStateMaskInput3;
//u32 kRollingTimeNewStateMaskInput4;
//u32 kRollingTimeNewStateMaskInput5;
//u32 kRollingTimeNewStateMaskInput6;
//u32 kRollingTimeNewStateMaskInput7;
//u32 kRollingTimeNewStateMaskInput8;
//u32 kRollingTimeNewStateMaskInput9;
//u32 kRollingTimeNewStateMaskInput10;
//u32 kRollingTimeNewStateMaskInput11;
//u32 kRollingTimeNewStateMaskInput12;
//u32 kRollingTimeNewStateMaskInput13;
//u32 kRollingTimeNewStateMaskInput14;
//u32 kRollingTimeNewStateMaskInput15;
//u32 kRollingTimeNewStateMaskInput16;
//u32 kRollingTimeNewStateMaskInput17;
//u32 kRollingTimeNewStateMaskInput18;
//u32 kRollingTimeNewStateMaskInput19;
//u32 kRollingTimeNewStateMaskInput20;
//u32 kRollingTimeNewStateMaskInput21;
//u32 kRollingTimeNewStateMaskInput22;
//u32 kRollingTimeNewStateMaskInput23;
//u32 kRollingTimeNewStateMaskInput24;
//u32 kRollingTimeNewStateMaskInput25;
//u32 kRollingTimeNewStateMaskInput26;
//u32 kRollingTimeNewStateMaskInput27;
//u32 kRollingTimeNewStateMaskInput28;
//u32 kRollingTimeNewStateMaskInput29;
//u32 kRollingTimeNewStateMaskInput30;
//u32 kRollingTimeNewStateMaskInput31;
//u32 kRollingTimeNewStateMaskInput32;
//u32 kTimeEventAdInput1h;
//u32 kTimeEventAdInput1l;
//u32 kTimeEventAdInput2h;
//u32 kTimeEventAdInput2l;
//u32 kTimeEventAdInput3h;
//u32 kTimeEventAdInput3l;
//u32 kTimeEventAdInput4h;
//u32 kTimeEventAdInput4l;
//u32 kTimeEventAdInput5h;
//u32 kTimeEventAdInput5l;
//u32 kTimeEventAdInput6h;
//u32 kTimeEventAdInput6l;
//u32 kTimeEventAdInput7h;
//u32 kTimeEventAdInput7l;
//u32 kTimeEventAdInput8h;
//u32 kTimeEventAdInput8l;
//u32 kTimeEventAdInput9h;
//u32 kTimeEventAdInput9l;
//u32 kTimeEventAdInput10h;
//u32 kTimeEventAdInput10l;
//u32 kTimeEventAdInput11h;
//u32 kTimeEventAdInput11l;
//u32 kTimeEventAdInput12h;
//u32 kTimeEventAdInput12l;
//u32 kTimeEventAdInput13h;
//u32 kTimeEventAdInput13l;
//u32 kTimeEventAdInput14h;
//u32 kTimeEventAdInput14l;
//u32 kTimeEventAdInput15h;
//u32 kTimeEventAdInput15l;
//u32 kTimeEventAdInput16h;
//u32 kTimeEventAdInput16l;
//u32 kTimeEventAdInput17h;
//u32 kTimeEventAdInput17l;
//u32 kTimeEventAdInput18h;
//u32 kTimeEventAdInput18l;
//u32 kTimeEventAdInput19h;
//u32 kTimeEventAdInput19l;
//u32 kTimeEventAdInput20h;
//u32 kTimeEventAdInput20l;
//u32 kTimeEventAdInput21h;
//u32 kTimeEventAdInput21l;
//u32 kTimeEventAdInput22h;
//u32 kTimeEventAdInput22l;
//u32 kTimeEventAdInput23h;
//u32 kTimeEventAdInput23l;
//u32 kTimeEventAdInput24h;
//u32 kTimeEventAdInput24l;
//u32 kTimeEventAdInput25h;
//u32 kTimeEventAdInput25l;
//u32 kTimeEventAdInput26h;
//u32 kTimeEventAdInput26l;
//u32 kTimeEventAdInput27h;
//u32 kTimeEventAdInput27l;
//u32 kTimeEventAdInput28h;
//u32 kTimeEventAdInput28l;
//u32 kTimeEventAdInput29h;
//u32 kTimeEventAdInput29l;
//u32 kTimeEventAdInput30h;
//u32 kTimeEventAdInput30l;
//u32 kTimeEventAdInput31h;
//u32 kTimeEventAdInput31l;
//u32 kTimeEventAdInput32h;
//u32 kTimeEventAdInput32l;
//u32 kTimeEventAdInput33h;
//u32 kTimeEventAdInput33l;
//u32 kTimeEventAdInput34h;
//u32 kTimeEventAdInput34l;
//u32 kTimeEventAdInput35h;
//u32 kTimeEventAdInput35l;
//u32 kTimeEventAdInput36h;
//u32 kTimeEventAdInput36l;
//u32 kTimeEventAdInput37h;
//u32 kTimeEventAdInput37l;
//u32 kTimeEventAdInput38h;
//u32 kTimeEventAdInput38l;
//u32 kTimeEventAdInput39h;
//u32 kTimeEventAdInput39l;
//u32 kTimeEventAdInput40h;
//u32 kTimeEventAdInput40l;
//u32 kTimeEventAdInput41h;
//u32 kTimeEventAdInput41l;
//u32 kTimeEventAdInput42h;
//u32 kTimeEventAdInput42l;
//u32 kTimeEventAdInput43h;
//u32 kTimeEventAdInput43l;
//u32 kTimeEventAdInput44h;
//u32 kTimeEventAdInput44l;
//u32 kTimeEventAdInput45h;
//u32 kTimeEventAdInput45l;
//u32 kTimeEventAdInput46h;
//u32 kTimeEventAdInput46l;
//u32 kTimeEventAdInput47h;
//u32 kTimeEventAdInput47l;
//u32 kTimeEventAdInput48h;
//u32 kTimeEventAdInput48l;
//u32 kTimeEventAdInput49h;
//u32 kTimeEventAdInput49l;
//u32 kTimeEventAdInput50h;
//u32 kTimeEventAdInput50l;
//u32 kTimeEventAdInput51h;
//u32 kTimeEventAdInput51l;
//u32 kTimeEventAdInput52h;
//u32 kTimeEventAdInput52l;
//u32 kTimeEventAdInput53h;
//u32 kTimeEventAdInput53l;
//u32 kTimeEventAdInput54h;
//u32 kTimeEventAdInput54l;
//u32 kTimeEventAdInput55h;
//u32 kTimeEventAdInput55l;
//u32 kTimeEventAdInput56h;
//u32 kTimeEventAdInput56l;
//u32 kTimeEventAdInput57h;
//u32 kTimeEventAdInput57l;
//u32 kTimeEventAdInput58h;
//u32 kTimeEventAdInput58l;
//u32 kTimeEventAdInput59h;
//u32 kTimeEventAdInput59l;
//u32 kTimeEventAdInput60h;
//u32 kTimeEventAdInput60l;
//u32 kTimeEventAdInput61h;
//u32 kTimeEventAdInput61l;
//u32 kTimeEventAdInput62h;
//u32 kTimeEventAdInput62l;
//u32 kTimeEventAdInput63h;
//u32 kTimeEventAdInput63l;
//u32 kTimeEventAdInput64h;
//u32 kTimeEventAdInput64l;
//u32 kTimeEventAdInput65h;
//u32 kTimeEventAdInput65l;
//u32 kTimeEventAdInput66h;
//u32 kTimeEventAdInput66l;
//u32 kTimeEventAdInput67h;
//u32 kTimeEventAdInput67l;
//u32 kTimeEventAdInput68h;
//u32 kTimeEventAdInput68l;
//u32 kTimeEventAdInput69h;
//u32 kTimeEventAdInput69l;
//u32 kTimeEventAdInput70h;
//u32 kTimeEventAdInput70l;
//u32 kTimeEventAdInput71h;
//u32 kTimeEventAdInput71l;
//u32 kTimeEventAdInput72h;
//u32 kTimeEventAdInput72l;
//u32 kTimeEventAdInput73h;
//u32 kTimeEventAdInput73l;
//u32 kTimeEventAdInput74h;
//u32 kTimeEventAdInput74l;
//u32 kTimeEventAdInput75h;
//u32 kTimeEventAdInput75l;
//u32 kTimeEventAdInput76h;
//u32 kTimeEventAdInput76l;
//u32 kTimeEventAdInput77h;
//u32 kTimeEventAdInput77l;
//u32 kTimeEventAdInput78h;
//u32 kTimeEventAdInput78l;
//u32 kTimeEventAdInput79h;
//u32 kTimeEventAdInput79l;
//u32 kTimeEventAdInput80h;
//u32 kTimeEventAdInput80l;
//u32 kTimeEventAdInput81h;
//u32 kTimeEventAdInput81l;
//u32 kTimeEventAdInput82h;
//u32 kTimeEventAdInput82l;
//u32 kTimeEventAdInput83h;
//u32 kTimeEventAdInput83l;
//u32 kTimeEventAdInput84h;
//u32 kTimeEventAdInput84l;
//u32 kTimeEventAdInput85h;
//u32 kTimeEventAdInput85l;
//u32 kTimeEventAdInput86h;
//u32 kTimeEventAdInput86l;
//u32 kTimeEventAdInput87h;
//u32 kTimeEventAdInput87l;
//u32 kTimeEventAdInput88h;
//u32 kTimeEventAdInput88l;
//u32 kTimeEventAdInput89h;
//u32 kTimeEventAdInput89l;
//u32 kTimeEventAdInput90h;
//u32 kTimeEventAdInput90l;
//u32 kTimeEventAdInput91h;
//u32 kTimeEventAdInput91l;
//u32 kTimeEventAdInput92h;
//u32 kTimeEventAdInput92l;
//u32 kTimeEventAdInput93h;
//u32 kTimeEventAdInput93l;
//u32 kTimeEventAdInput94h;
//u32 kTimeEventAdInput94l;
//u32 kTimeEventAdInput95h;
//u32 kTimeEventAdInput95l;
//u32 kTimeEventAdInput96h;
//u32 kTimeEventAdInput96l;
//u32 kconfig_DebounceAdInputs;
//u32 kEnable_AdInputsh;
//u32 kEnable_AdInputsm;
//u32 kEnable_AdInputsl;
//u32 kpolarity_AdInputs81to96;
//u32 kpolarity_AdInputs65to80;
//u32 kpolarity_AdInputs49to64;
//u32 kpolarity_AdInputs33to48;
//u32 kpolarity_AdInputs17to32;
//u32 kpolarity_AdInputs1to16;
//u32 kglobal_Control;
//u32 kFPGA_Config;
//u32 kFPGA_Version;


void FPGA_Registers_Init();
void FPGA_Registers_Open();
void FPGA_Registers_Close();

#endif
