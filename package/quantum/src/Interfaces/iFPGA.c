/*---------------------------------------------------------------------------
-----------------------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland.
All rights reserved.
-----------------------------------------------------------------------------
File name 			: iFPGA.c
Author				: Cestele Yves
Date				: 28 juin 2017
Description			: Description in iFPGA.h file

Modifications		: -

---------------------------------------------------------------------------*/
#include "iFPGA.h"

//--------------------------------------------------------------
// 				FUNCTIONS
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
    void iFpga_EnDisOneTimingInput(u8 *aPayload)
    {
      // Check if the number is under the number max of inputs (otherwise it want to write somewhere false in memory)
	if(aPayload[0]<=kNbOfInput)
	{
	  // Reg addr calcul:
	  u32 aMask = 1;
	  vu32 *aRegAddr = kconfig_input1;
	  aRegAddr+=aPayload[0];

	  // Input enable
	  if(0x01==aPayload[1])
	    {
	      *aRegAddr|=aMask;
	    }
	  // Input disable
	  else if(0x00==aPayload[1])
	    {
	      *aRegAddr&=(~(aMask));
	    }
	}
    }

    //--------------------------------------------------------------
    // Name		: iFpga_EnDisAllTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: En/Dis able Timing Inputs
    //
    // Parameters	: u8* -> Payload with [ ]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_EnDisAllTimingInput(u8 *aPayload)
    {

	vu32 *aRegAddr = kconfig_input1;
	u32 *aPayLoadPtr;
	u8 i;
	u32 aMask=1;

	// Config du pointeur sur les 4 bytes de la charge utile de la commande
	aPayLoadPtr=(u32*)(&aPayload[0]);

	// Affectation de l'�tat d�sir� � chaque entr�e du Timer Fpga
	for(i=0;i<kNbOfInput;i++)
	{
	    // Enable de l'entr�e si n�cessaire
	    if(0x00000001==(((__builtin_bswap32(*aPayLoadPtr))>>i)&0x00000001))
	    {
		*aRegAddr|=aMask;
	    }
	    // Disable de l'entr�e si n�cessaire
	    else if(0x00000000==(((__builtin_bswap32(*aPayLoadPtr))>>i)&0x00000001))
	    {
		*aRegAddr&=~(aMask);
	    }
	    aRegAddr++;
	}
    }

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
    void iFpga_DebounceTimeOneTimingInput(u8 *aPayload)
    {
      u32 aMask=0x000000ff;
      u32 aVal=0;

	// Check if the input number is valid
	if(aPayload[0]<=kNbOfInput)
	{
	    vu32 *aRegAddr = kconfig_input1;
	    aRegAddr+=aPayload[0];

	    // Value construction
	    aVal=(u32)((aPayload[1]<<24)+(aPayload[2]<<16)+(aPayload[3]<<8));

	    // Field reset
	    *aRegAddr&=aMask;

	    // Affectation au registre de la valeur re�ue
	    *aRegAddr|=aVal;
	}
    }

    //--------------------------------------------------------------
    // Name		: iFpga_ArmOrDisarmOneTimingInput
    // Author		: Cestele Yves
    // Date		: 28 juin 2017
    // Descritpion	: (Un)armed input x
    //
    // Parameters	: u8* -> payload with [inp nb][state]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_ArmOrDisarmOneTimingInput(u8 *aPayload)
    {
	u32 aMask=2;

	// Check if the value is valid
	if(aPayload[0]<=kNbOfInput)
	{
	    vu32 *aRegAddr= kconfig_input1;
	    aRegAddr+=aPayload[0];

	    // Armed input
	    if(0x01==aPayload[1])
	    {
		*aRegAddr|=aMask;
	    }
	    // Unarmed input
	    else if(0x00==aPayload[1])
	    {
		*aRegAddr&=~(aMask);
	    }
	}
    }

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
    void iFpga_ArmOrDisarmAllTimingInput(u8 *aPayload)
    {
	vu32 *aRegAddr = kconfig_input1;
	u32 *aPayLoadPtr;
	u8 i;
	u16 aMask=2;

	// Pointer configuration (4 bytes useful of the command)
	aPayLoadPtr=(u32*)aPayload;

	// Desired state assignement to each time input
	for(i=0;i<kNbOfInput;i++)
	{
	    // Armed input
	    if(0x00000001==(((__builtin_bswap32(*aPayLoadPtr))>>i)&0x00000001))
	    {
		*aRegAddr|=aMask;
	    }
	    // Unarmed input
	    else if(0x00000000==(((__builtin_bswap32(*aPayLoadPtr))>>i)&0x00000001))
	    {
		*aRegAddr&=~(aMask);
	    }
	    aRegAddr++;
	}
    }

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
    void iFpga_SoftTimingInputPulse(u8 *aPayload)
    {
	u32 *aPayLoadPtr;
	vu32*aRegAddr = kSoftwareInputPulse;

	// Pointer configuration
	aPayLoadPtr=((u32*)(&aPayload[0]));

	// Write in reg
	*aRegAddr|=__builtin_bswap32(*aPayLoadPtr);
    }

    //------------------------------------------------------------
    // Fct de r�ponse de la commande RS232
    // --> Prepare synchronization
    // --> S�lection des entr�es qui vont recevoir une nouvelle
    //     heure du jour (en us) lors de la prochaine synchro
    //     La nouvelle heure du jour fait aussi partie de la commande
    // Temps ex�cution : ~92.4us
    //------------------------------------------------------------

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
    void iFpga_PrepareSynch(u8 *aPayload)
    {

	vu32 *aRegAddr = kconfig_input1;
	u32  *aPayLoadPtr;
	u8   i;
	u16  aMask=4;

	//------------------------------------------------------------
	// Enable/Disable input(s) to sync
	//------------------------------------------------------------

	aPayLoadPtr=(u32*)(&aPayload[1]);

	// Desired state assignement in each timer inputs
	for(i=0;i<kNbOfInput;i++)
	{
	    // Actives inputs
	    if(0x0001==(((__builtin_bswap32(*aPayLoadPtr))>>i)&0x0001))
	    {
		*aRegAddr|=aMask;
	    }
	    // Unactives inputs
	    else if(0x0000==(((__builtin_bswap32(*aPayLoadPtr))>>i)&0x0001))
	    {
		*aRegAddr&=(~aMask);
	    }
	    aRegAddr++;
	}

	//------------------------------------------------------------
	// Config de l'heure du jour de la prochaine synchro
	//------------------------------------------------------------
	// Init du pointeur sur la charge utile
	aPayLoadPtr=(u32*)(&aPayload[5]);

	// Affectation du byte de poids fort (Byte 5 de la valeur, position 5 dans la charge utile) au registre High
	aRegAddr = kNextSyncDayTimeh;
	*aRegAddr = (u32)(((__builtin_bswap32(*aPayLoadPtr))&0xff000000)>>24);

	// GPS Synchro
	if ((aPayload[0] & 0xF0) == 0x10)
	{
	    // Enable Synchro
	    *aRegAddr = (u32)( *aRegAddr | 0x00008000 );
	}
	else
	{
	    // Cancel synchro
	    *aRegAddr=(u32)( *aRegAddr & 0xFFFF7FFF );
	}

	// Affectation des bytes de poids faible (Bytes 4,3,2,1 de la valeur, position 6,7,8,9 dans la charge utile) au registre Low
	aRegAddr = kNextSyncDayTimel;
	*aRegAddr=(u32)(((__builtin_bswap32(*aPayLoadPtr))&0x00ffffff)<<8);
	aPayLoadPtr++;
	*aRegAddr|=(u32)(((__builtin_bswap32(*aPayLoadPtr))&0xff000000)>>24);

     }

    //--------------------------------------------------------------
    // Name		: iFpga_PrepareOneTimingOutput
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Prepare one timing Output
    //			  Config the time when an out must be activated
    //			  the pulse duration
    //
    // Parameters	: u8* -> payload with [][][][][][]
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_PrepareOneTimingOutput(u8 *aPayload)
    {

      u32 *aPayLoadPtr;
      u32 aMask;

      // Check if the output number is valid
      if(aPayload[0]<=kNbOfOutput)
        {
    	  aPayLoadPtr=(u32*)(&aPayload[0]);

    	  u32 test0 = aPayLoadPtr[0];
    	  u32 test1 = aPayLoadPtr[1];
    	  u32 test2 = aPayLoadPtr[2];
    	  u32 test3 = aPayLoadPtr[3];


          vu32 *aRegAddrh = kconfig_output1h;
          aRegAddrh +=(aPayload[0]*2);
          vu32 *aRegAddrl = kconfig_output1l;
          aRegAddrl+=(aPayload[0]*2);

          u32 iValueBefore = *aRegAddrh;	//FIXME DEBUG

          // Configuration de l'heure du jour � laquelle une pulse sera g�n�r�e
          // Deux valeurs sp�ciales pour l'heure du jour:
          // 0 : Sortie imm�diate
          // 1 : Attente uniquement sur un �v�nement d'un temps tournant

          *aRegAddrh=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ff0000)>>16);
          *aRegAddrl=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x0000ffff)<<16);
          aPayLoadPtr++;
          *aRegAddrl|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xffff0000)>>16);

          u32 iValueAfter = *aRegAddrh;	//FIXME DEBUG

          // Configuration de la dur�e de la pulse en us
          aPayLoadPtr=(u32*)(&aPayload[10]);
          *aRegAddrh|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8);



          vu32 *aRegAddr=kOutput1DestinationMask;
          aRegAddr+=aPayload[0];
          aPayLoadPtr=(u32*)&aPayload[6];
          *aRegAddr=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8);
          aPayLoadPtr++;
          *aRegAddr|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>24);


          // PC de destination auquel il faut transmettre les �v�nement de cette sortie
          gOutputPcSportDestTab[aPayload[0]]=aPayload[6];

          // Si le temps = 0  --> immediate output
          if((aPayload[1]==0)&&(aPayload[2]==0)&&(aPayload[3]==0)&&(aPayload[4]==0)&&(aPayload[5]==0))
            {
		aRegAddr=kImmediateOutputEnable;
             	aMask=(u32)(1<<aPayload[0]);
             	*aRegAddr|=aMask;
             }
          }

    }

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
    void iFpga_EnDisOneTimingOutput(u8 *aPayload)
    {

	u32 aMask=1;

	// Check if the Output nb is valid
	if(aPayload[0]<=kNbOfOutput)
	{
	    // Check if state is valid
	    if(aPayload[1]<=1)
	    {
		aMask<<=(u32)aPayload[0];

		vu32 *aRegAddr=kOuputsEnable;

		// Enable output
		if(0x01==aPayload[1])
		{
		    (*aRegAddr)|=aMask;
		}
		// Disable output
		else if(0x00==aPayload[1])
		{
		    (*aRegAddr)&=(~aMask);
		}
	    }
	}
    }

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
    void iFpga_EnDisAllTimingOutput(u8 *aPayload)
    {

      u32 *aMask;

      // Calcul du masque
      aMask=(u32*)&aPayload[0];

      // Config du pointeur sur le registre
      vu32 *aRegAddr=kOuputsEnable;

      // Par d�faut les sorties sont disable
      *aRegAddr=0;
      // Enable des sorties concern�es
      *aRegAddr|=(u32)__builtin_bswap32(*aMask);
    }

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
    void iFpga_NewRollingTime(u8 *aPayload)
    {

	u32 *aPayLoadPtr;
	u32 aMask=0xfffffffc;
	u32 aMask1=0xfffffff7;
	u32 aMask2=0xffff00ff;
	u32 aMask4=0x00000010;
	u16 aMask5=0x00000040;
	u16 i=666; // 1uS -> 1u/(1/666M) = 666

	vu32 *aRegAddrh=kConfigRollingTime1h;
	aRegAddrh+=(aPayload[0]*2);
	vu32 *aRegAddrl=kConfigRollingTime1l;
	aRegAddrl+=(aPayload[0]*2);

	// RT reset
	*aRegAddrl|=aMask4;

	// RT Starting configuration
	// 0 : Absolute start --> immediat start
	// 1 : Absolute start --> attend une commande de start, ou une pulse d'entr�e d'une entr�e arm�e
	// 2 : Daytime --> immediat start
	// 3 : Unused
	aPayLoadPtr=(u32*)(&aPayload[0]);
	*aRegAddrl&=aMask;
	*aRegAddrl|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00030000)>>16);

	// Counting direction
	// 0 : Count down
	// 1 : Count up
	*aRegAddrl&=aMask1;
	*aRegAddrl|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00000100)>>5);

	// PC Sport configuration
	aPayLoadPtr=(u32*)(&aPayload[12]);
	*aRegAddrl&=(u32)aMask2;
	*aRegAddrl|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>16);
	gRollingTimePcSportDestTab[aPayload[0]]=aPayload[12];


	// Starting time in uS
	// Mode 0 et 1  --> absolut time
	// Mode 2       --> daytime
	aPayLoadPtr=(u32*)(&aPayload[6]);
	*aRegAddrh=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8);
	aPayLoadPtr++;
	*aRegAddrh|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>24);
	*aRegAddrl|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ff0000)<<8);

	// RT interval in us
	vu32 *aRegAddr=kIntervalRollingTime1;
	aRegAddr+=aPayload[0];
	aPayLoadPtr=(u32*)(&aPayload[2]);
	*aRegAddr=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8);
	aPayLoadPtr++;
	*aRegAddr|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>24);


	// Outputs to activate by this RT
	aRegAddr=kOutputMaskRT1;
	aRegAddr+=aPayload[0];
	aPayLoadPtr=(u32*)(&aPayload[12]);
	*aRegAddr=(u32)((__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8);
	aPayLoadPtr++;
	*aRegAddr|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>24);


	// Immediat start
	if((aPayload[1]==0)||(aPayload[1]==2))
	{
	    // Attendre 1us --> calcul dans la FPGA => 1uS -> 1u/(1/666M) = 666
	    while(i>0)
	    {
		i--;
	    }
	    *aRegAddrl|=aMask5;
	}
    }

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
    void iFpga_RollingTimeNewDest(u8 *aPayload)
    {

      u32 *aPayLoadPtr;
      u8  i=0;
      u32 aTmp2=0;
      u32 aMask2=0xffff00ff;

      // Disable the new config
      if(0xFE==aPayload[6])
        {
          gRollingTimePcSportDestTab[aPayload[0]]=0;

          for(i=0;i<kNbOfInput;i++)
            {
              gRollingTimeNewDestTab[aPayload[0]][i].IsNew=false;
            }
        }

      // Apply the new immediate config
      else  if(0xFF==aPayload[6])
        {
          // Config the PC Sport for this config
          gRollingTimePcSportDestTab[aPayload[0]]=aPayload[1];

          // Configure the PC dest in FPGA:
          vu32 *aRegAddrl=kConfigRollingTime1l;
          aRegAddrl+=(aPayload[0]*2);

          aPayLoadPtr=(u32*)(&aPayload[1]);
          *aRegAddrl&=(u32)aMask2;
          *aRegAddrl|=(u32)((__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>16);

          // Outputs to activate at the end of rolling time
          vu32 *aRegAddr = kOutputMaskRT1;
          aRegAddr+=aPayload[0];
          aPayLoadPtr=(u32*)(&aPayload[2]);
      	  *aRegAddr=__builtin_bswap32(*aPayLoadPtr);
        }
      // Wait events to activate
      else
        {
          gRollingTimeNewDestTab[aPayload[0]][aPayload[6]].PCSportAddr=aPayload[1];

          aTmp2=((u32)aPayload[2])<<24;
          aTmp2|=((u32)aPayload[3])<<16;
          aTmp2|=((u32)aPayload[4])<<8;
          aTmp2|=((u32)aPayload[5]);
          gRollingTimeNewDestTab[aPayload[0]][aPayload[6]].OutPutMask=aTmp2;
          gRollingTimeNewDestTab[aPayload[0]][aPayload[6]].IsNew=true;
        }
    }


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
    void iFpga_RollingTimeNewState(u8 *aPayload)
    {

	u8 i=0;
	u32 aMask=0x00000004;
	u32 aMask1=0x00000020;

	vu32 *aRegAddr= kConfigRollingTime1l;
	aRegAddr+=(aPayload[0]*2);

	// Apply the new immediate config
	if(0xFF==aPayload[2])
	{
	    if(0x01==aPayload[1])  // RT active
	    {
		*aRegAddr=(u32)(*aRegAddr|aMask);
	    }
	    else if(0x00==aPayload[1]) // RT Inactive
	    {
		*aRegAddr=(u32)(*aRegAddr&(~aMask));
	    }

	    vu32 *aRegAddr=kConfigRollingTime1l;
	    aRegAddr+=(aPayload[0]*2);

	    *aRegAddr=(*aRegAddr)|aMask1;
	}
	// Wait event to configure
	else
	{
	    aRegAddr=kRollingTimeNewStateMaskInput1;
	    aRegAddr+=aPayload[2];


	    if(0x00==aPayload[1]) // Active RT
	    {
		*aRegAddr|=(u32)((1<<aPayload[0]));
	    }
	    else if(0x01==aPayload[1]) // Desactive RT
	    {
		*aRegAddr|=(u32)((1<<(aPayload[0]+16)));
	    }
	}
    }

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
    void iFpga_RollingTimeNewInter(u8 *aPayload)
    {

      u32 *aPayLoadPtr;

      // Configure the time between 2 RT
      vu32 *aRegAddr=kIntervalRollingTime1;
      aRegAddr+=aPayload[0];

      aPayLoadPtr=(u32*)aPayload;
      *aRegAddr=(__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8;
      aPayLoadPtr++;
      *aRegAddr|=(__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>24;

    }

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
    void iFpga_RollingTimeNewCustomTrig(u8 *aPayload)
    {

	u32 *aPayLoadPtr;
	u32 aTmp;

	// Configuration de la valeur du trigger
	vu32 *aRegAddrh=kCustomTriggerRT1h;
	aRegAddrh+=(aPayload[0]*2);
	vu32 *aRegAddrl=kCustomTriggerRT1l;
	aRegAddrl+=(aPayload[0]*2);

	aPayLoadPtr=(u32*)&aPayload[0];
	*aRegAddrh=(__builtin_bswap32(*aPayLoadPtr)&0x00ff0000)>>16;
	*aRegAddrl=(__builtin_bswap32(*aPayLoadPtr)&0x0000ffff)<<16;
	aPayLoadPtr++;
	*aRegAddrl|=(__builtin_bswap32(*aPayLoadPtr)&0xffff0000)>>16;

	// Config out to activate at the end of RT
	vu32 *aRegAddr=kOutputMaskCT1;
	aRegAddr+=aPayload[0];

	aPayLoadPtr=(u32*)&aPayload[6];
	*aRegAddr=(__builtin_bswap32(*aPayLoadPtr)&0x00ffffff)<<8;
	aPayLoadPtr++;
	*aRegAddr|=(__builtin_bswap32(*aPayLoadPtr)&0xff000000)>>24;

	// Config du PC Sport de destination lorsque le temps tournant atteint la valeur de trig
	gRollingTimeTriggerPcSportDestTab[aPayload[0]]=aPayload[6];

	// Enable du custom trigger
	aRegAddr=kCustomTriggerEnable;
	aTmp=(u32)(1<<aPayload[0]);
	*aRegAddr|=aTmp;

    }

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
    void iFpga_EnDisOneTimeStampInp(u8 *aPayload)
    {

	u32 aTmp;

	aTmp=(u32)((aPayload[0])/32);
	vu32 *aRegAddr= kEnable_AdInputsl;
	aRegAddr-=aTmp;			//(upper_addr - x*4)

	// Mask to applicate
	aTmp=(u32)(1<<(aPayload[0]-(aTmp*32)));

	// Input En(dis)able
	if(aPayload[1]==0x01)
	{
	    *aRegAddr|=aTmp;
	}
	else if(aPayload[1]==0x00)
	{
	    *aRegAddr&=(~aTmp);
	}
    }

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
    void iFpga_EnDisAllTimeStampInp(u8 *aPayload)
    {

	u32 *aPayLoad32BitsPtr;

	vu32 *aRegAddr= kEnable_AdInputsl;

	aPayLoad32BitsPtr=(u32*)&aPayload[0];
	*aRegAddr=__builtin_bswap32(*aPayLoad32BitsPtr);

	aRegAddr=kEnable_AdInputsm;
	aPayLoad32BitsPtr=(u32*)&aPayload[4];
	*aRegAddr=__builtin_bswap32(*aPayLoad32BitsPtr);

	aRegAddr=kEnable_AdInputsh;
	aPayLoad32BitsPtr=(u32*)&aPayload[8];
	*aRegAddr=__builtin_bswap32(*aPayLoad32BitsPtr);

    }

    //--------------------------------------------------------------
    // Name		: iFpga_SetDebounceAllTimeStampInp
    // Author		: Cestele Yves
    // Date		: 29 juin 2017
    // Descritpion	: Set Debounce All Time Stamp Inputs
    //
    // Parameters	: u8* -> Payload -> deb time
    //
    // Return		: void
    //
    // Modification	:
    //--------------------------------------------------------------
    void iFpga_SetDebounceAllTimeStampInp(u8 *aPayload)
    {

	u32 *aPayLoad32BitsPtr;

	vu32 *aRegAddr=kconfig_DebounceAdInputs;
	aPayLoad32BitsPtr=(u32*)&aPayload[0];
	*aRegAddr=(((__builtin_bswap32(*aPayLoad32BitsPtr))&0xffffff00)>>8);

    }

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
    void iFpga_SoftTimeStampInputPulse(u8 *aPayload)
    {

	u32 *aPayLoad32BitsPtr;

	//       Disable interruptsd IRQ6 pendant la config
	//      MCF_EPORT_EPIER&=(~0x40);

	vu32 *aRegAddr = kSoftwareAdInputPulsel;
	aPayLoad32BitsPtr=(u32*)&aPayload[0];
	*aRegAddr=__builtin_bswap32(*aPayLoad32BitsPtr);

	aRegAddr = kSoftwareAdInputPulsem;
	aPayLoad32BitsPtr=(u32*)&aPayload[4];
	*aRegAddr=__builtin_bswap32(*aPayLoad32BitsPtr);

	aRegAddr = kSoftwareAdInputPulseh;
	aPayLoad32BitsPtr=(u32*)&aPayload[8];
	*aRegAddr=__builtin_bswap32(*aPayLoad32BitsPtr);

	//    	// Enable interrupt IRQ6
	//      MCF_EPORT_EPIER|=(0x40);
    }


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
    void iFpga_SelActSlopeAllTimeInp(u8 *aPayload)
    {

	u32 *aPayLoad32BitsPtr;
	u32 *aPayLoadSlopePtr;
	u32 aMask=1;
	u16 i;

	aPayLoad32BitsPtr=(u32*)&aPayload[0];
	aPayLoadSlopePtr=(u32*)&aPayload[4];
	vu32 *aRegAddr=kconfig_input1;

	// inputs 0 to 31
	for(i=0;i<32;i++)
	{
	    // Check if the input cmd must be changed
	    aMask=(1UL<<i);
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		vu32 *aAddr=aRegAddr+i;
		*aAddr&=0xffffffcf;
		*aAddr|=((__builtin_bswap32(*aPayLoadSlopePtr)&0xff000000)>>20);
	    }
	}
    }

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
    void iFpga_SelActSlopeAllTimeStampInp(u8 *aPayload)
    {

	u32 *aPayLoad32BitsPtr;
	u32 *aPayLoadSlopePtr;
	u32 aMask=1;
	u16 i;

	aPayLoad32BitsPtr=(u32*)&aPayload[0];
	aPayLoadSlopePtr=(u32*)&aPayload[12];
	vu32 *aRegAddr = kpolarity_AdInputs1to16;

	// Inputs 0 to 15
	for(i=0;i<16;i++)
	{
	    // Check if the input config must be modified
	    aMask=(1UL<<i);
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		*aRegAddr&=(~(3<<(i*2)));
		*aRegAddr|=(((__builtin_bswap32(*aPayLoadSlopePtr))>>24)<<(i*2));
	    }
	}

	// Reg inputs 16 to 31
	aRegAddr--;

	for(i=16;i<32;i++)
	{
	    // Check if the input config must be modified
	    aMask=(1UL<<i);
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		*aRegAddr&=(~(3<<((i-16)*2)));
		*aRegAddr|=(((__builtin_bswap32(*aPayLoadSlopePtr))>>24)<<((i-16)*2));
	    }
	}

	//inputs 32 to 63
	aPayLoad32BitsPtr++;

	// Reg inputs 32 to 47
	aRegAddr--;

	for(i=32;i<48;i++)
	{
	    // Check if the input config must be modified
	    aMask=(1UL<<(i-32));
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		*aRegAddr&=(~(3<<((i-32)*2)));
		*aRegAddr|=(((__builtin_bswap32(*aPayLoadSlopePtr))>>24)<<((i-32)*2));
	    }
	}

	// Reg inputs 48 to 63)
	aRegAddr--;

	for(i=48;i<64;i++)
	{
	    // Check if the input config must be modified
	    aMask=(1UL<<(i-32));
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		*aRegAddr&=(~(3<<((i-48)*2)));
		*aRegAddr|=(((__builtin_bswap32(*aPayLoadSlopePtr))>>24)<<((i-48)*2));
	    }
	}

	// Inputs 64 to 95
	aPayLoad32BitsPtr++;

	// Reg inputs 64 to 79
	aRegAddr--;

	// Entr�e 64 � 79
	for(i=64;i<80;i++)
	{
	    // Check if the input config must be modified
	    aMask=(1UL<<(i-64));
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		*aRegAddr&=(~(3<<((i-64)*2)));
		*aRegAddr|=(((__builtin_bswap32(*aPayLoadSlopePtr))>>24)<<((i-64)*2));
	    }
	}

	// Reg inputs 80 to 95
	aRegAddr--;

	for(i=80;i<96;i++)
	{
	    // Check if the input config must be modified
	    aMask=(1UL<<(i-64));
	    if(((__builtin_bswap32(*aPayLoad32BitsPtr))&aMask)==aMask)
	    {
		*aRegAddr&=(~(3<<((i-80)*2)));
		*aRegAddr|=(((__builtin_bswap32(*aPayLoadSlopePtr))>>24)<<((i-80)*2));
	    }
	}
    }


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
    void iFpga_RollingTimeNewSerial(u8 *aPayload)
    {

	u16 i;
	u8 len = 0;
	//u8 tempHourLen = 0;

	OneSerialPortFormatStruct* localFormat = &gRTAllSerialPortFormat[aPayload[2]].SerialPortFormatTab[aPayload[3]];

	// Configuration de l'�tat du port s�rie 1:sent et 0: not sent
	(*localFormat).State=aPayload[4];

	// Configuration de la grandeur du formatage
	(*localFormat).HeaderLen=aPayload[5];
	(*localFormat).FooterLen=aPayload[6];

	len = (u8)((*localFormat).HeaderLen + (*localFormat).FooterLen);

	//tempHourLen = (u8)(aPayload[7]);

	if (aPayload[7] > 0)
	{
	    (*localFormat).HourLen = (u16)utils_pow10((s8)(aPayload[7] - 1));
	}
	else
	{
	    (*localFormat).HourLen = 0;
	}

	if (aPayload[8] > 0)
	{
	    (*localFormat).MinLen = (u16)utils_pow10((s8)(aPayload[8] - 1));
	}
	else
	{
	    (*localFormat).MinLen = 0;
	}

	if (aPayload[9] > 0)
	{
	    (*localFormat).SecLen = (u16)utils_pow10((s8)(aPayload[9] - 1));
	}
	else
	{
	    (*localFormat).SecLen = 0;
	}

	(*localFormat).SecModulo = (u16)((*localFormat).SecLen * 10);
	(*localFormat).DecLen = aPayload[10];
	(*localFormat).DecSeparator = aPayload[11];
	(*localFormat).TimeSep = aPayload[12];
	(*localFormat).FloatingSign = aPayload[13];

	(*localFormat).ModeSeconds = ((*localFormat).HourLen == 0) && ((*localFormat).MinLen == 0);

	for(i=0;i<len;i++)
	{
	(*localFormat).Format[i]=aPayload[14+i];
	}
    }

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
    void iFpga_ResetSeveralOutput(u8 *aPayload)
    {

	u32  *aPayLoad32BitsPtr;
	vu32 *aRegAddr=kResetOutputs;
	aPayLoad32BitsPtr=(u32*)&aPayload[0];

	// Reset outputs
	*aRegAddr|=__builtin_bswap32(*aPayLoad32BitsPtr);
    }

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
    void iFpga_SetPolarityAllOutputs(u8 *aPayload)
    {

	static u32  *aPayLoad32BitsPtr;
	static u32  aMask;
	static u8  aSubVal;
	u16  i;
	vu32 *aRegAddr=kOutputsPolarity;
	static u32 tempVal=0;

// COmmented by Yves Cestele 23.7.17 -> don't understand functions
//	//**********
//	// Polarity inversion for first four output
//	// a �t� chang� dans le soft puis oubli�. Il est maintenant r�-invers�
//	// dans la FPGA. On laisse donc cette double inversion
//	aSubVal = (u8)((__builtin_bswap32(*aPayLoad32BitsPtr)) & 0x0000000F);
//	aSubVal = (~aSubVal) & 0x0F;
//
//	(*aPayLoad32BitsPtr) = (__builtin_bswap32(*aPayLoad32BitsPtr)) & 0xFFFFFFF0;
//	(*aPayLoad32BitsPtr) = (__builtin_bswap32(*aPayLoad32BitsPtr)) + aSubVal;
//	//**********
//
//	// Get register value
//	tempVal = *aRegAddr;
//
//	// Update it with new values
//	for(i=kNbOfOutput;i>0;i--)
//	{
//	    aMask=(u32)(1<<(i-1));
//	    // TODO Pas sur
//	    if((__builtin_bswap32(*aPayLoad32BitsPtr)&aMask)==aMask)
//	    {
//		    tempVal|=(u32)(aMask);
//	    }
//	    else
//	    {
//		    tempVal&=(u32)(~aMask);
//	    }
//	}
//
//	// Save new value in FPGA.
//	*aRegAddr = tempVal;
	u8 aTmp = ~aPayload[3];
	*aRegAddr = (aTmp&0x000000000f)|(aPayload[3]&0x00000000f0)|((aPayload[2]<<8)&0x0000ff00)|((aPayload[1]<<16)&0x00ff0000)|((aPayload[0]<<24)&0xff000000);
	// Latch polarity register
	aRegAddr = kglobal_Control;
	*aRegAddr =  0x00000001;

    }

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
    void iFpga_RollingClearWaitInput(u8 *aPayload)
    {

	u8 i=0;
	u8 j=0;

	// Clear tous les RT
	if(aPayload[0]==0xFF)
	{
	    // For All Rolling Times
	    for(j=0;j<kNbOfRollingTime;j++)
	    {
		// All inputs
		if(aPayload[1]==0xFF)
		{
		    vu32 *aRegAddr=kRollingTimeNewStateMaskInput1;

		    for(i=0;i<kNbOfInput;i++,aRegAddr++)
		    {
			if(aPayload[2]==0x00)	// Suspend
			{
			    *aRegAddr&=(~(u32)((1<<j)));
			}
			else if(aPayload[2]==0x01)	// Active
			{
			    *aRegAddr&=(~(u32)((1<<(j+16))));
			}

			else if(aPayload[2]==0x02)	// New PC Sport
			{
			    gRollingTimeNewDestTab[j][i].IsNew=false;
			}
			else if(aPayload[2]==0xff)	// All
			{
			    *aRegAddr&=(~(u32)((1<<j)));
			    *aRegAddr&=(~(u32)((1<<(j+16))));
			    gRollingTimeNewDestTab[j][i].IsNew=false;
			}
		    }
		}

		// Just 1 input
		else
		{
		    vu32 *aRegAddr=kRollingTimeNewStateMaskInput1;
		    aRegAddr+=aPayload[1];

		    if(aPayload[2]==0x00)	// Suspend
		    {
			*aRegAddr&=(~(u32)((1<<j)));
		    }
		    else if(aPayload[2]==0x01)	// Actives
		    {
			*aRegAddr&=(~(u32)((1<<(j+16))));
		    }

		    else if(aPayload[2]==0x02)	// New PC Sport
		    {
			gRollingTimeNewDestTab[j][aPayload[1]].IsNew=false;
		    }
		    else if(aPayload[2]==0xff)	// All
		    {
			*aRegAddr&=(~(u32)((1<<j)));
			*aRegAddr&=(~(u32)((1<<(j+16))));
			gRollingTimeNewDestTab[j][aPayload[1]].IsNew=false;
		    }
		}
	    }
	}
	else // Clear 1 Rolling Time
	{
	    // All inputs
	    if(aPayload[1]==0xFF)
	    {
		vu32 *aRegAddr=kRollingTimeNewStateMaskInput1;

		for(i=0;i<kNbOfInput;i++,aRegAddr++)	// All
		{
		    if(aPayload[2]==0x00) 		// Suspend
		    {
			*aRegAddr&=(~(u32)((1<<aPayload[0])));
		    }
		    else if(aPayload[2]==0x01)	// Actives
		    {
			*aRegAddr&=(~(u32)((1<<(aPayload[0]+16))));
		    }
		    else if(aPayload[2]==0x02)	// New PC Sport
		    {
			gRollingTimeNewDestTab[aPayload[0]][i].IsNew=false;
		    }
		    else if(aPayload[2]==0xff)
		    {
			*aRegAddr&=(~(u32)((1<<aPayload[0])));
			*aRegAddr&=(~(u32)((1<<(aPayload[0]+16))));
			gRollingTimeNewDestTab[aPayload[0]][i].IsNew=false;
		    }
		}
	    }
	    else // just 1 input
	    {
		vu32 *aRegAddr=kRollingTimeNewStateMaskInput1;
		aRegAddr+=aPayload[1];

		if(aPayload[2]==0x00)		// Suspend
		{
		    *aRegAddr&=(~(u32)((1<<aPayload[0])));
		}
		else if(aPayload[2]==0x01)	// Actives
		{
		    *aRegAddr&=(~(u32)((1<<(aPayload[0]+16))));
		}
		else if(aPayload[2]==0x02)	// New PC Sport
		{
		    gRollingTimeNewDestTab[aPayload[0]][aPayload[1]].IsNew=false;
		}
		else if(aPayload[2]==0xff)	// All
		{
		    *aRegAddr&=(~(u32)((1<<aPayload[0])));
		    *aRegAddr&=(~(u32)((1<<(aPayload[0]+16))));
		    gRollingTimeNewDestTab[aPayload[0]][aPayload[1]].IsNew=false;
		}
	    }

	}
    }

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
    void iFpga_SetGenericOutputsReg(u8 *aPayload)
    {

	vu32 *aRegAddr = kGenericOutputs;

	*aRegAddr = *aRegAddr & 0x00FF;
	*aRegAddr = *aRegAddr | (u32)(aPayload[0]<<8);
    }

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
    void iFpga_ResetFpga(u8 *aPayload)
    {

	u16 i,j,k;

	if((aPayload[0]==0x55)&&(aPayload[1]==0x0F)&&(aPayload[2]==0xF0)&&(aPayload[3]==0xAA))
	{
	    // Reset the FPGA
	    //XSlcr_PllWriteResetValues();	// TODO, check if it's the correct way to reset the PL part

	    // Reset du tableau indiquant quel sortie pour quel PC Sport
	    for(i=0;i<kNbOfOutput;i++)
	    {
		gOutputPcSportDestTab[i]=0;
	    }

	    // Reset du tableau indiquant quel Rolling Time pour quel PC Sport
	    for(i=0;i<kNbOfRollingTime;i++)
	    {
		gRollingTimePcSportDestTab[i]=0;
	    }

	    // Reset du tableau indiquant quel Rolling Time pour quel PC Sport --> trigger
	    for(i=0;i<kNbOfRollingTime;i++)
	    {
		gRollingTimeTriggerPcSportDestTab[i]=0;
	    }

	    // Reset de la structure permettant la config d'un nouveau Rolling Time
	    for(i=0;i<kNbOfRollingTime;i++)
	    {
		for(j=0;j<kNbOfInput;j++)
		{
		    gRollingTimeNewDestTab[i][j].PCSportAddr=0;
		    gRollingTimeNewDestTab[i][j].OutPutMask=0;
		    gRollingTimeNewDestTab[i][j].IsNew=false;
		}
	    }

	    // Reset du tableau des formats des 7 ports s�rie pour les 16 RT
	    for(i=0;i<kNbOfRollingTime;i++)
	    {
		for(j=0;j<kNbOfSerialPort;j++)
		{
		    for(k=0;k<kRTLengh;k++)
		    {
			gRTAllSerialPortFormat[i].SerialPortFormatTab[j].Format[k]=0;
		    }
		    gRTAllSerialPortFormat[i].SerialPortFormatTab[j].State=0;
		}
	    }
	}
    }

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
    void iFpga_RollingTimeNewSerialBin(u8 *aPayload)
    {

    	// Byte 1 : Rt number
    	// Byte 2 : Serial number
        // Byte 3 : State
    	// Byte 4 : Number high
    	// Byte 5 : Number low
        // Byte 6 : RT identifier (User defined value)

        OneSerialPortFormatStruct* localFormat = &gRTAllSerialPortFormat[aPayload[0]].SerialPortFormatTab[aPayload[1]];

    	// Serial port configuration 1:sent et 0: not sent, 2 : binary Rt, 3 : binary Rt + bib
        (*localFormat).State=aPayload[2];

        (*localFormat).NumberHigh = aPayload[3];
        (*localFormat).NumberLow = aPayload[4];

        // Rt associated identifier, used defined
        (*localFormat).RtIdentifier = aPayload[5];
    }

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
    void iFpga_LogicalOrOnInput(u8 *aPayload)
    {

      vu32 *aRegAddrOR = kPulsesOR;
      vu32 *aRegAddrAND = kInputsAND;
      u32   aMask=1;

      // Payload 2 bytes : PairNumber, State

      // Check State value
      if (aPayload[1] > 1)
      {
        return;
      }

      // Fill register
      aMask = aMask << aPayload[0];

      if(0x01 == aPayload[1])
      {
        // Clear AND function
        *aRegAddrAND&=(~(aMask));
        // Set OR function
        *aRegAddrOR|=aMask;
      }
      else if(0x00 == aPayload[1])
      {
        *aRegAddrOR&=(~(aMask));
      }

    }

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
    void iFpga_LogicalAndOnInput(u8 *aPayload)
    {
	vu32 *aRegAddrAND = kInputsAND;
	vu32 *aRegAddrOR = kPulsesOR;
	u32   aMask=1;

	// Check State value
	if (aPayload[1] > 1)
	{
	    return;
	}

	// Fill register
	aMask = aMask << aPayload[0];

	if(0x01 == aPayload[1])
	{
	    // Clear OR function
	    *aRegAddrOR&=(~(aMask));
	    // Set AND function
	    *aRegAddrAND|=aMask;
	}
	else if(0x00 == aPayload[1])
	{
	    *aRegAddrAND&=(~(aMask));
	}
    }

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
    void iFpga_StateDetectionDelay(u8 *aPayload)
    {
	// Delay:
	// 0 = inactive
	// otherwhise 0.01 sec resolution 0.01 to 2.55 sec

	if(0x01 == aPayload[0]) // Active state
	{
	    // Pointer --> kFPGAREG_BASE+0x0B0)
	    vu32 *aRegAddr = kConfigInputActiveDelay;
	    *aRegAddr = (u8)aPayload[1];
	}
	else
	{
	    // Pointer --> kFPGAREG_BASE+0x0B4)
	    vu32 *aRegAddr = kConfigInputNotActiveDelay;
	    *aRegAddr = (u8)aPayload[1];
	}
    }

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
    void iFPga_EnableDisableStateDetection(u8 *aPayload)
    {

	u32 *aPayLoadPtr;
	u8 i;
	vu32 *aRegAddr = kconfig_input1;

	aPayLoadPtr=(u32*)(&aPayload[1]);

	// For each input
	for(i=0;i<kNbOfInput;i++)
	{
	    aRegAddr+=i;

	    // Check if the input is used
	    if(0x00000001 == (((__builtin_bswap32(*aPayLoadPtr))>>i)&0x00000001))
	    {
		*aRegAddr&=~(0xC0); 	// Disabled in all cases
		if (1 == aPayload[0]) 	// Active state = 1
		{
		    // Enable Active delay
		    *aRegAddr|=0x40;
		}
		else if (2 == aPayload[0]) // Inactive state = 2
		{
		    // Enable Inactive delay
		    *aRegAddr|=0x80;
		}
	    }
	}
    }


