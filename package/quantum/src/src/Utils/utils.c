/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute école ARC Ingéniérie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: utils.c
Author				: Cestele Yves
Date				: 26 juin 2017
Description			: Description in utils.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "utils.h"

// ASCII Control STX char
#define kSTX  				0x02

boolean g24HoursMode = false;

//--------------------------------------------------------------
// 				FUNCTIONS
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
    u8 BuildCodedFrame(u8 *aSrcFrame, u8 *aDestFrame, u8 aSrcFrameSize)
    {

      u8 i=0;
      u8 j=0;

      for(i=0,j=0;i<aSrcFrameSize;i++,j++)
	{
	  if(aSrcFrame[i]>252)
	    {
	     aDestFrame[j]=kSTX;
	     j++;
	     aDestFrame[j]=aSrcFrame[i];
	    }
	  else if((i!=0)&&(i<(aSrcFrameSize-1)))
	    {
	     aDestFrame[j]=(u8)(aSrcFrame[i]+3);
	    }
	  else
	    {
	     aDestFrame[j]=aSrcFrame[i];
	    }
	}

      return j;
    }

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
    u8 DecodeFrame(u8 *aBuffPtr,u8 aSize,u8 *aNewBuffPtr)
    {
      boolean aNext = false;
      u8 aNewSize=0;

      while(aSize>0)
        {
          if ((*aBuffPtr != 0x00) && (*aBuffPtr != 0x01))
            {
              if (aNext == false)
                {
                  if (*aBuffPtr ==0x02)
                    {
                      aNext = true;
                    }
                  else
                    {
                      *aNewBuffPtr=*aBuffPtr;
                      *aNewBuffPtr-=3;
                      aNewBuffPtr++;
                      aNewSize++;
                    }
                }
              else
                {
                  *aNewBuffPtr=*aBuffPtr;
                  aNewBuffPtr++;
                  aNewSize++;
                  aNext = false;
                }
            }

          aBuffPtr++;
          aSize--;
        }

      return aNewSize;
    }

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
    u32 utils_pow10(s8 anExp)
    {
      u32 aPwr = 1;

      while(anExp > 0)
      {
        aPwr = aPwr * 10;
        anExp--;
      }

      return aPwr;
    }

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
    DateTimeStruct ToDateTime(u64* aTimeUs)
    {
        u64 usTime;
        u32 fracTime;

        DateTimeStruct aResult;

        // Only 48bits are needed
        usTime = (*aTimeUs)& 0x000000FFFFFFFFFF;

        // time in seconds
        fracTime = (u32)(usTime / ((u64)1000000));

        // Get decimal part
        aResult.Decimal = (u32)(usTime - (fracTime * 1000000));

        // Get Hour (can be greater than 23 !!!
        aResult.Hour = (u8)(fracTime / 3600);

        fracTime = fracTime - (aResult.Hour * 3600);

        // Reset to 0 at midnight
        if (g24HoursMode == true)
        {
          aResult.Hour = aResult.Hour % 24;
        }

        // Get Minutes
        aResult.Minute = (u8)(fracTime / 60);

        fracTime = fracTime - (aResult.Minute * 60);

        // Get Second
        aResult.Second = (u8)(fracTime);

        return aResult;
    }

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
    void ConvertToString(u32 aTime, u8* aDataBuffer, u32 aDivider)
    {

        u32 aTempTime;
        u8 aLoopIdx;

        aLoopIdx = 0;

        do
        {
            aTempTime = (aTime / aDivider);
            aDataBuffer[aLoopIdx] = (u8)(aTempTime + 48);
            aTime = (aTime - (aTempTime * aDivider));

            aLoopIdx += 1;
            aDivider/=10;
        }while(aDivider != 0);
    }
