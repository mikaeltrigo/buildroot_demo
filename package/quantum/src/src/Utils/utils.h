/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: utils.h
Author				: Cestele Yves
Date				: 26 juin 2017
Description			: Useful functions

Modifications			: -

---------------------------------------------------------------------------*/
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

//--------------------------------------------------------------
// 				INCLUDES & DEFINES
//--------------------------------------------------------------
#include "xil_types.h"

typedef unsigned long 	boolean;
typedef boolean		bool;
typedef volatile u32	vu32;

#define true		TRUE
#define false		FALSE

typedef struct
{
    u16  Hour;
    u8   Minute;
    u32  Second;
    u32  Decimal;
}DateTimeStruct;

extern boolean g24HoursMode;		// True to reset time have 0 hours at midnight

//--------------------------------------------------------------
// 				FUNCTIONS'S LIST
//--------------------------------------------------------------

    //--------------------------------------------------------------
    // Name		: BuildCodedFrame
    // Author		: Cestele Yves
    // Date		: 26 juin 2017
    // Descritpion	: Coding of the transmitted frame.
    //			  All bytes conatining a velue between 0 and 252
    //			  are transmitted with an offset of +3
    //			  3 bytes reserved:
    //				SOH -> Beginning
    //				NUL -> Ending
    //				STX -> Prefix for a mess cont 253 or 254
    //
    //
    // Parameters	: u8* Source Frame
    //			  u8* Destination Frame
    //			  u8  Source frame size
    //
    // Return		: u8  Dest size frame
    //
    // Modification	:
    //--------------------------------------------------------------
    u8 BuildCodedFrame(u8 *aSrcFrame, u8 *aDestFrame, u8 aSrcFrameSize);

    //--------------------------------------------------------------
    // Name		: DecodeFrame
    // Author		: Cestele Yves
    // Date		: 27 juin 2017
    // Descritpion	: Decoding for the received Frame:
    //			  3 bytes reserved:
    //				SOH -> Beginning
    //				NUL -> Ending
    //				STX -> Prefix for a mess cont 253 or 254
    //
    // Parameters	: u8* Source Frame
    //			  u8  Source frame size
    //			  u8* Destination Frame
    //
    // Return		: u8  Dest size frame
    //
    // Modification	:
    //--------------------------------------------------------------
    u8 DecodeFrame(u8 *aBuffPtr,u8 aSize,u8 *aNewBuffPtr);

    //--------------------------------------------------------------
    // Name		: pow10
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Power of 10
    //
    // Parameters	: SInt8   -> Input
    //
    // Return		: UInt32  -> Input^10
    //
    // Modification	:
    //--------------------------------------------------------------
    u32 utils_pow10(s8 anExp);

    //--------------------------------------------------------------
    // Name		: ToDateTime
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Convert us to Date and time struct
    //
    // Parameters	: u64* -> ptr on time in us
    //
    // Return		: DateTimeStruct -> DT struct
    //
    // Modification	:
    //--------------------------------------------------------------
    DateTimeStruct ToDateTime(u64* aTimeUs);

    //--------------------------------------------------------------
    // Name		: ConvertToString
    // Author		: Cestele Yves
    // Date		: 11 juil. 2017
    // Descritpion	: Convert time to string
    //
    // Parameters	: u32	-> time in us
    //			  u8*	-> result in string
    //			  u32	-> Divider
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void ConvertToString(u32 aTime, u8* aDataBuffer, u32 aDivider);

#endif /* SRC_UTILS_H_ */
