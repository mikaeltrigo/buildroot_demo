/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "kentec.h"
#include "sys/time.h"
#include "grlib/grlib.h"
#include <errno.h>
#include <string.h>

#define MAP_SIZE 0x20

typedef struct SInterruptManagement
{
    const int 	pending;
    const int 	reenable;
    int 	fdInterrupt;
    int 	fdRegister;
    uint32_t*	puBaseAddr;
}SInterruptManagement;

static SInterruptManagement me = {0x00, 0xFF};

int keyBoard_Init()
{
    char *uiod = "/dev/uio0";

    me.fdInterrupt = open(uiod, O_RDWR);
    if(me.fdInterrupt < 1)
    {
	printf("Invalid UIO device file:%s.\n", uiod);
	return -1;
    }

    char *uioe = "/dev/uio8";

    me.fdRegister = open(uioe, O_RDWR);
    if(me.fdRegister < 1)
    {
	printf("Invalid UIO device file:%s.\n", uiod);
	return -1;
    }

    /* open STATUS_REG */
    if ((me.puBaseAddr = (uint32_t *)mmap(0x00, 0x60, PROT_READ | PROT_WRITE, MAP_SHARED, me.fdRegister, 0x00)) == NULL) //If use mem, should ask MEM_BASE instead of 0x00
    {
	printf("Cannot open Memory Map\n");
	return -1;
    }

    me.puBaseAddr+= 0x10;
    char test[100];
    sprintf(test, "%s", strerror(errno));
    printf("Error: %s", strerror(errno));

    return 0;
}

void keyBoard_Open()
{
    write(me.fdInterrupt, (void *)&me.reenable, sizeof(int));
}

int keyBoard_close()
{
    if (munmap(me.puBaseAddr, MAP_SIZE) == -1)
    {
      fprintf(stderr, "Cannot close Memory Map");
      return -1;
    }

    close(me.fdInterrupt);

    return 0;
}

uint32_t keyBoard_ReadPressed()
{
    uint32_t ret = 0x00;

    // Wait
    read(me.fdInterrupt, (void *)&me.pending, sizeof(int));

    // Reqad the register:
    ret = *(me.puBaseAddr)&0xFF;
    *(me.puBaseAddr) = 0x0000;



    // Reset the interrupt:
    write(me.fdInterrupt, (void *)&me.reenable, sizeof(int));

    return ret;

}

int main(int argc, char *argv[])
{
	Graphics_Context graphics_Context;
	uint8_t loopEnd = 0;

	/***************************************************
	 * INITIALIZATION:
	 **************************************************/
	printf("LCD initialization:");
	SSD2119_Init();
	SSD2119_open();

	printf("Interrupt initialization:");
	keyBoard_Init();
	keyBoard_Open();

//	SSD2119_InitNew();	// Other Gamma values

	GrContextInit(&graphics_Context, &g_sKentec320x240x16_SSD2119);

//	printf("Printing on the LCD");
//	GrContextForegroundSet(&graphics_Context, ClrWhite);
//	GrContextFontSet(&graphics_Context, &g_sFontCmss48);
//	char test[] = "PowerTime III";
//	GrStringDrawCentered(&graphics_Context, (int8_t*)test, -1, 160, 120, false);
//
//	printf("Drawinf on the LCD");
//	Graphics_fillCircle(&graphics_Context, 160, 180, 30);
//	GrContextForegroundSet(&graphics_Context, ClrRed);
//	Graphics_fillCircle(&graphics_Context, 160, 180, 25);
//	GrContextForegroundSet(&graphics_Context, ClrWhite);
//	Graphics_fillCircle(&graphics_Context, 160, 180, 20);
//	GrContextForegroundSet(&graphics_Context, ClrRed);
//	Graphics_fillCircle(&graphics_Context, 160, 180, 15);
//	GrContextForegroundSet(&graphics_Context, ClrWhite);
//	Graphics_fillCircle(&graphics_Context, 160, 180, 10);
//	GrContextForegroundSet(&graphics_Context, ClrRed);
//	Graphics_fillCircle(&graphics_Context, 160, 180, 5);
//
//	printf("Displaying image on the LCD");
//	//GrImageDraw(&graphics_Context, &swt4BPP_COMP_RLE4, 0, 0);
//	GrImageDraw(&graphics_Context, &trigo8BPP_COMP_RLE8, 0, 0);
//
//	printf("Example of the desired result:");

	/***************************************************
	 * LOOP:
	 **************************************************/
	GrContextForegroundSet(&graphics_Context, ClrWhite);
	GrContextBackgroundSet(&graphics_Context, ClrBlack);
	GrContextFontSet(&graphics_Context, &g_sFontCmss12);
	char txt[100];
//	sprintf(txt, "Wait for an interrupt!");
//	GrStringDrawCentered(&graphics_Context, (int8_t*)txt, -1, 160, 120, false);

	#define NB_LINE_TO_PRINT 16
	char txtLine[NB_LINE_TO_PRINT][100];
	int uCpt = 0x00;
	int x = 0;


	GrContextForegroundSet(&graphics_Context, ClrBlack);
	Graphics_fillRectangle(&graphics_Context, &graphics_Context.clipRegion);

	GrContextForegroundSet(&graphics_Context, ClrWhite);
	GrContextFontSet(&graphics_Context, &g_sFontCmss14);

	do
	{
	    // Wait an interrupt
	    int iPressed = keyBoard_ReadPressed();
//	    GrClearDisplay(&graphics_Context);

//	    GrClearDisplay(&graphics_Context);


//	    GrContextForegroundSet(&graphics_Context, ClrWhite);
//	    GrContextFontSet(&graphics_Context, &g_sFontCmss14);
//	    sprintf(txt, "Button %d pressed", iPressed);
//	    GrStringDraw(&graphics_Context, (int8_t*)txt, -1, 10, (uCpt)*28, false);
//	    sprintf(txt, " -> 00:00:00.0000");
//	    GrStringDraw(&graphics_Context, (int8_t*)txt, -1, 10, (uCpt++)*28 +14, false);

	    sprintf(txtLine[uCpt % NB_LINE_TO_PRINT], "Button %d pressed", iPressed);
	    uCpt++;
	    sprintf(txtLine[uCpt % NB_LINE_TO_PRINT], " -> 00:00:00.0000");
	    uCpt++;

	    int uToGo = (uCpt >= NB_LINE_TO_PRINT ? NB_LINE_TO_PRINT : uCpt);
	    int uLocCpt = (uCpt >= NB_LINE_TO_PRINT ? uCpt : 0);

	    if(uLocCpt > NB_LINE_TO_PRINT)
	    {
		GrContextForegroundSet(&graphics_Context, ClrBlack);
		Graphics_fillRectangle(&graphics_Context, &graphics_Context.clipRegion);
	    }

	    GrContextForegroundSet(&graphics_Context, ClrGhostWhite);

	    for(x=0; x < uToGo; x++)
	    {
		GrStringDraw(&graphics_Context, (int8_t*)txtLine[(uLocCpt + x)%NB_LINE_TO_PRINT], -1, 10, (x)*14, false);
	    }



//	    sprintf(txt, "%d", iPressed);
//	    GrContextForegroundSet(&graphics_Context, ClrWhite);
//	    GrContextFontSet(&graphics_Context, &g_sFontCmss48);
//	    GrStringDrawCentered(&graphics_Context, (int8_t*)txt, -1, 160, 120, false);

	    if(21 == iPressed)
	    {
		loopEnd = 0x01;
	    }


	    // Display the mask value on the LCD
	}
	while(0x01 != loopEnd);

	usleep(1000000);

	GrImageDraw(&graphics_Context, &trigo8BPP_COMP_RLE8, 0, 0);

	usleep(1000000);

	sprintf(txt, "Finish!");
	GrContextFontSet(&graphics_Context, &g_sFontCmss14);
	GrStringDrawCentered(&graphics_Context, (int8_t*)txt, -1, 160, 120, false);

	keyBoard_close();

	return 0;
}
