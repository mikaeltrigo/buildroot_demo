//*****************************************************************************
//
// Kentec320x240x16_SSD2119_SPI.c - Display driver for the Kentec
//                                  BOOSTXL-K350QVG-S1 TFT display with an SSD2119_
//                                  controller.  This version assumes an SPI interface
//                                  between the micro and display.
//
// https://github.com/bennycooly/school-projects/blob/master/EE319K_Labswc/students/rvr324_byf69/Lab7_EE319K/SSD2119_.c
//*****************************************************************************

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/sysctl.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "kentec.h"
#include "grlib/grlib.h"

static void WriteDataSPI(unsigned short usData);
static void WriteCommandSPI(unsigned short usData);

typedef struct SKentecConfig
{
    int fd;
}SKentecConfig;

static SKentecConfig me;


void SSD2119_open()
{

}

static void spi_init()
{
	int buf_size = 32;
	char path[buf_size];

	snprintf(path, buf_size, "/dev/%s", CHAR_DEV_NAME);

	if((me.fd = open(path, O_RDWR)) < 0)
	{
		printf("Error opening device: %s\n", strerror(errno));
	}

}

/*----------------------------------------------------------------------------*/
void SSD2119_close_control()
{
	close(me.fd);
}

/*----------------------------------------------------------------------------*/

int spi_write_value( int addr,int value)
{
	int ret;

	lseek(me.fd, addr, SEEK_SET);
	ret = write(me.fd, &value, sizeof(value));
	if(ret < 0)
	{
		printf("Write error: %s\n", strerror(errno));
		return -1;
	}

	if(ret != sizeof(value))
	{
		printf("Write error, written %i, expected %i\n",
				ret, sizeof(value));
		return -1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
int spi_read_value( int addr, int *value)
{
	int ret;

	lseek(me.fd, addr, SEEK_SET);
	ret = read(me.fd, value, sizeof(*value));
	if(ret < 0)
	{
		printf("Read error: %s\n", strerror(errno));
		return -1;
	}

	if(ret != sizeof(*value))
	{
		printf("Read error, read %i, expected %i\n",
				ret, sizeof(*value));
		return -1;
	}

	return 0;
}




int SSD2119_spi_transfer_cmd(uint8_t cmd)
{
	uint32_t reg_wr = 0x00010000;//cmd start transfer
	int r_value;
	reg_wr = reg_wr |  cmd;
	spi_write_value(0xC, reg_wr);
//	spi_read_value(0xC, &r_value);
//	r_value = r_value & 0x10000000;
//	if (r_value == 0x10000000 )
//		return -1;
//	else
		return 0;

}
int SSD2119_spi_transfer_data(uint16_t data)
{
	uint32_t reg_wr = 0x00020000;//data start transfer
	int r_value;
	reg_wr = reg_wr |  data;
	spi_write_value(0xC, reg_wr);
//	spi_read_value(0xC, &r_value);
//	r_value = r_value & 0x10000000;
//	if (r_value == 0x10000000 )
//		return -1;
//	else
		return 0;

}


//*****************************************************************************
// Writes a data word to the SSD2119_.  This function implements the 4-wire SPI
// interface to the LCD display.
//*****************************************************************************
static void
WriteDataSPI(unsigned short usData)
{
	int ret=0;

	//perform_spi_transfer( pui16Data, default_rx, sizeof(pui16Data));
	ret=SSD2119_spi_transfer_data(usData&0xFFFF);
	//for debug
	if(ret < 0)
	{
		printf("Error WriteDataSPI ");
	}

}
//*****************************************************************************
// Writes register word to the SSD2119_.  This function implements the 4-wire SPI
// interface to the LCD display.
//*****************************************************************************
static void
WriteCommandSPI(unsigned short usData)
{
	int ret = 0;
//	usleep(1);//must add it otherwise problem
//	long INTERVAL_NS = 500;
//	struct timespec sleepValue = {0};
//
//	sleepValue.tv_nsec = INTERVAL_NS;
//	nanosleep(&sleepValue, NULL);

	ret=SSD2119_spi_transfer_cmd(usData&0xFF);
	//for debug
	if(ret < 0)
	{
		printf("Error WriteDataSPI ");
	}
}



// ************** convertColor ****************************
// - Converts 8-8-8 RGB values into 5-6-5 RGB
// ********************************************************
unsigned short convertColor(unsigned char r, unsigned char g, unsigned char b)
{
    return ((r>>3)<<11) | ((g>>2)<<5) | (b>>3);
}


//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the SSD2119_ display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void SSD2119_Init(void)
{
    unsigned int ulCount;

    me.fd = 0x00;

    spi_init();

    // Reset the LCD and enable backlite
    spi_write_value(0x8, 0x140);
    usleep(50000);
    spi_write_value(0x8, 0x141);
    usleep(50000);

    // Enter sleep mode (if we are not already there).
    WriteCommandSPI(0x10);//SLEEP_MODE_REG
    WriteDataSPI(0x0001);

    //
    // Set initial power parameters.
    //
    WriteCommandSPI(0x1E);//SSD2119_PWR_CTRL_5_REG
    WriteDataSPI(0x00BA);//ToDo: 0xb2
    WriteCommandSPI(0x28);//SSD2119_VCOM_OTP_1_REG
    WriteDataSPI(0x0006);

    //
    // Start the oscillator.
    //
    WriteCommandSPI(0x00);
    WriteDataSPI(0x0001);

    //
    // Set pixel format and basic display orientation (scanning direction).
    //
    WriteCommandSPI(0x01);
    WriteDataSPI(0x30EF);
    WriteCommandSPI(0x02);
    WriteDataSPI(0x0600);

    //
    // Exit sleep mode.
    //
    WriteCommandSPI(0x10);//SSD2119_SLEEP_MODE_REG
    WriteDataSPI(0x0000);

    //
    // Delay 30mS
    //
    usleep(30000);

    //
    // Configure pixel color format and MCU interface parameters.
    //
    WriteCommandSPI(SSD2119_ENTRY_MODE_REG);
    WriteDataSPI(ENTRY_MODE_DEFAULT);

    //
    // Enable the display.
    //
    WriteCommandSPI(0x07);
    WriteDataSPI(0x0033);

    //
    // Set VCIX2 voltage to 6.1V.
    //
    WriteCommandSPI(0x0C);//SSD2119_PWR_CTRL_2_REG
    WriteDataSPI(0x0005);

    //
    // Configure gamma correction.
    //
    WriteCommandSPI(0x30);    WriteDataSPI(0x0000);//SSD2119_GAMMA_CTRL_1
    WriteCommandSPI(0x31);    WriteDataSPI(0x0400);//SSD2119_GAMMA_CTRL_2
    WriteCommandSPI(0x32);    WriteDataSPI(0x0106);//SSD2119_GAMMA_CTRL_3
    WriteCommandSPI(0x33);    WriteDataSPI(0x0700);//SSD2119_GAMMA_CTRL_4
    WriteCommandSPI(0x34);    WriteDataSPI(0x0002);//SSD2119_GAMMA_CTRL_5
    WriteCommandSPI(0x35);    WriteDataSPI(0x0702);//SSD2119_GAMMA_CTRL_6
    WriteCommandSPI(0x36);    WriteDataSPI(0x0707);//SSD2119_GAMMA_CTRL_7
    WriteCommandSPI(0x37);    WriteDataSPI(0x0203);//SSD2119_GAMMA_CTRL_8
    WriteCommandSPI(0x3A);    WriteDataSPI(0x1400);//SSD2119_GAMMA_CTRL_9
    WriteCommandSPI(0x3B);    WriteDataSPI(0x0F03);//SSD2119_GAMMA_CTRL_10

    //
    // Configure Vlcd63 and VCOMl.
    //
    WriteCommandSPI(0x0D);//SSD2119_PWR_CTRL_3_REG
    WriteDataSPI(0x0007); //Todo: 0xa
    WriteCommandSPI(0x0E);//SSD2119_PWR_CTRL_4_REG
    WriteDataSPI(0x3100);//Todo: 0x2e00

    //
    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    //
    WriteCommandSPI(SSD2119_V_RAM_POS_REG);
    WriteDataSPI((LCD_VERTICAL_MAX-1) << 8);
    WriteCommandSPI(SSD2119_H_RAM_START_REG);
    WriteDataSPI(0x0000);
    WriteCommandSPI(SSD2119_H_RAM_END_REG);
    WriteDataSPI(LCD_HORIZONTAL_MAX-1);
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(0x0000);
    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(0x0000);

    // Clear the contents of the display buffer.
    WriteCommandSPI(SSD2119_RAM_DATA_REG);
    for(ulCount = 0; ulCount < (320 * 240); ulCount++)
    {
        WriteDataSPI(0x0000);
    }

}
//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the SSD2119_ display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void SSD2119_InitNew(void)
{
    unsigned int ulCount;

    spi_init();

    me.fd = 0x00;

    // Reset the LCD and config of the SPI freq
    spi_write_value(0x8, 0x140);
    usleep(50000);
    spi_write_value(0x8, 0x141);
    usleep(50000);

    // Enter sleep mode (if we are not already there).
    WriteCommandSPI(0x10);//SLEEP_MODE_REG
    WriteDataSPI(0x0001);

    //
    // Set initial power parameters.
    //
    WriteCommandSPI(0x1E);//SSD2119_PWR_CTRL_5_REG
    WriteDataSPI(0x00B2);//ToDo: 0xb2
    WriteCommandSPI(0x28);//SSD2119_VCOM_OTP_1_REG
    WriteDataSPI(0x0006);

    //
    // Start the oscillator.
    //
    WriteCommandSPI(0x00);
    WriteDataSPI(0x0001);

    //
    // Set pixel format and basic display orientation (scanning direction).
    //
    WriteCommandSPI(0x01);
    WriteDataSPI(0x30EF);
    WriteCommandSPI(0x02);
    WriteDataSPI(0x0600);

    //
    // Exit sleep mode.
    //
    WriteCommandSPI(0x10);//SSD2119_SLEEP_MODE_REG
    WriteDataSPI(0x0000);

    //
    // Delay 30mS
    //
    usleep(30000);

    //
    // Configure pixel color format and MCU interface parameters.
    //
    WriteCommandSPI(SSD2119_ENTRY_MODE_REG);
    WriteDataSPI(ENTRY_MODE_DEFAULT);

    //
    // Enable the display.
    //
    WriteCommandSPI(0x07);
    WriteDataSPI(0x0033);

    //
    // Set VCIX2 voltage to 6.1V.
    //
    WriteCommandSPI(0x0C);//SSD2119_PWR_CTRL_2_REG
    WriteDataSPI(0x0005);

    //
    // Configure gamma correction.
    //
    WriteCommandSPI(SSD2119_GAMMA_CTRL_1_REG);
    WriteDataSPI(0x0000);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_2_REG);
    WriteDataSPI(0x0303);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_3_REG);
    WriteDataSPI(0x0407);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_4_REG);
    WriteDataSPI(0x0301);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_5_REG);
    WriteDataSPI(0x0301);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_6_REG);
    WriteDataSPI(0x0403);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_7_REG);
    WriteDataSPI(0x0707);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_8_REG);
    WriteDataSPI(0x0400);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_9_REG);
    WriteDataSPI(0x0a00);
    WriteCommandSPI(SSD2119_GAMMA_CTRL_10_REG);
    WriteDataSPI(0x1000);

    //
    // Configure Vlcd63 and VCOMl.
    //
    WriteCommandSPI(0x0D);//SSD2119_PWR_CTRL_3_REG
    WriteDataSPI(0x000a); //Todo: 0xa
    WriteCommandSPI(0x0E);//SSD2119_PWR_CTRL_4_REG
    WriteDataSPI(0x2e00);//Todo: 0x2e00

    //
    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    //
    WriteCommandSPI(SSD2119_V_RAM_POS_REG);
    WriteDataSPI((LCD_VERTICAL_MAX-1) << 8);
    WriteCommandSPI(SSD2119_H_RAM_START_REG);
    WriteDataSPI(0x0000);
    WriteCommandSPI(SSD2119_H_RAM_END_REG);
    WriteDataSPI(LCD_HORIZONTAL_MAX-1);
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(0x0000);
    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(0x0000);

    // Clear the contents of the display buffer.
    WriteCommandSPI(SSD2119_RAM_DATA_REG);
    for(ulCount = 0; ulCount < (680 * 280); ulCount++)
    {
        WriteDataSPI(0x0000);
    }
}

//*****************************************************************************
//
//! Draws a pixel on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the pixel.
//! \param lY is the Y coordinate of the pixel.
//! \param ulValue is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
SSD2119_PixelDraw(void *pvDisplayData, int32_t i32X,
        int32_t i32Y,
        uint32_t ui32Value)
{
    //
    // Set the X address of the display cursor.
    //
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_X(i32X, i32Y));

    //
    // Set the Y address of the display cursor.
    //
    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_Y(i32X, i32Y));

    //
    // Write the pixel value.
    //
    WriteCommandSPI(SSD2119_RAM_DATA_REG);
    WriteDataSPI(ui32Value);
}
//*****************************************************************************
//
//! Draws a horizontal line.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX1 is the X coordinate of the start of the line.
//! \param lX2 is the X coordinate of the end of the line.
//! \param lY is the Y coordinate of the line.
//! \param ulValue is the color of the line.
//!
//! This function draws a horizontal line on the display.  The coordinates of
//! the line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
SSD2119_LineDrawH(void *pvDisplayData, int32_t i32X1,
        int32_t i32X2, int32_t i32Y,
        uint32_t ui32Value)
{
    //
    // Set the cursor increment to left to right, followed by top to bottom.
    //
    WriteCommandSPI(SSD2119_ENTRY_MODE_REG);
    WriteDataSPI(MAKE_ENTRY_MODE(HORIZ_DIRECTION));

    //
    // Set the starting X address of the display cursor.
    //
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_X(i32X1, i32Y));

    //
    // Set the Y address of the display cursor.
    //
    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_Y(i32X1, i32Y));

    //
    // Write the data RAM write command.
    //
    WriteCommandSPI(SSD2119_RAM_DATA_REG);

    //
    // Loop through the pixels of this horizontal line.
    //
    while(i32X1++ <= i32X2)
    {
        //
        // Write the pixel value.
        //
        WriteDataSPI(ui32Value);
    }
}

static void
SSD2119_PixelDrawMultiple(void *pvDisplayData, int32_t i32X,
                                           int32_t i32Y, int32_t i32X0,
                                           int32_t i32Count, int32_t i32BPP,
                                           const uint8_t *pui8Data,
                                           const uint8_t *pui8Palette)
{
    uint32_t ui32Byte;

    //
    // Set the cursor increment to left to right, followed by top to bottom.
    //
    WriteCommandSPI(SSD2119_ENTRY_MODE_REG);
    WriteDataSPI(MAKE_ENTRY_MODE(HORIZ_DIRECTION));
    //
    // Set the starting X address of the display cursor.
    //
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_X(i32X, i32Y));

    //
    // Set the Y address of the display cursor.
    //
    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_Y(i32X, i32Y));

    //
    // Write the data RAM write command.
    //
    WriteCommandSPI(SSD2119_RAM_DATA_REG);

    //
    // Determine how to interpret the pixel data based on the number of bits
    // per pixel.
    //
    switch(i32BPP & 0x1D)
    {
        //
        // The pixel data is in 1 bit per pixel format.
        //
        case 1:
        {
            //
            // Loop while there are more pixels to draw.
            //
            while(i32Count)
            {
                //
                // Get the next byte of image data.
                //
                ui32Byte = *pui8Data++;

                //
                // Loop through the pixels in this byte of image data.
                //
                for(; (i32X0 < 8) && i32Count; i32X0++, i32Count--)
                {
                    //
                    // Draw this pixel in the appropriate color.
                    //
                    WriteDataSPI(((uint32_t *)pui8Palette)
                            [(ui32Byte >> (7 - i32X0)) & 1]);
                }

                //
                // Start at the beginning of the next byte of image data.
                //
                i32X0 = 0;
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // The pixel data is in 4 bit per pixel format.
        //
        case 4:
        {
            //
            // Loop while there are more pixels to draw.  "Duff's device" is
            // used to jump into the middle of the loop if the first nibble of
            // the pixel data should not be used.  Duff's device makes use of
            // the fact that a case statement is legal anywhere within a
            // sub-block of a switch statement.  See
            // http://en.wikipedia.org/wiki/Duff's_device for detailed
            // information about Duff's device.
            //
            switch(i32X0 & 1)
            {
                case 0:
                    while(i32Count)
                    {
                        //
                        // Get the upper nibble of the next byte of pixel data
                        // and extract the corresponding entry from the
                        // palette.
                        //
                        ui32Byte = (*pui8Data >> 4) * 3;
                        ui32Byte = (*(uint32_t *)(pui8Palette + ui32Byte) &
                                  0x00ffffff);

                        //
                        // Translate this palette entry and write it to the
                        // screen.
                        //
                        WriteDataSPI(DPYCOLORTRANSLATE(ui32Byte));

                        //
                        // Decrement the count of pixels to draw.
                        //
                        i32Count--;

                        //
                        // See if there is another pixel to draw.
                        //
                        if(i32Count)
                        {
                case 1:
                            //
                            // Get the lower nibble of the next byte of pixel
                            // data and extract the corresponding entry from
                            // the palette.
                            //
                            ui32Byte = (*pui8Data++ & 15) * 3;
                            ui32Byte = (*(uint32_t *)(pui8Palette + ui32Byte) &
                                      0x00ffffff);

                            //
                            // Translate this palette entry and write it to the
                            // screen.
                            //
                            WriteDataSPI(DPYCOLORTRANSLATE(ui32Byte));

                            //
                            // Decrement the count of pixels to draw.
                            //
                            i32Count--;
                        }
                    }
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // The pixel data is in 8 bit per pixel format.
        //
        case 8:
        {
            //
            // Loop while there are more pixels to draw.
            //
            while(i32Count--)
            {
                //
                // Get the next byte of pixel data and extract the
                // corresponding entry from the palette.
                //
                ui32Byte = *pui8Data++ * 3;
                ui32Byte = *(uint32_t *)(pui8Palette + ui32Byte) & 0x00ffffff;

                //
                // Translate this palette entry and write it to the screen.
                //
                WriteDataSPI(DPYCOLORTRANSLATE(ui32Byte));
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // We are being passed data in the display's native format.  Merely
        // write it directly to the display.  This is a special case which is
        // not used by the graphics library but which is helpful to
        // applications which may want to handle, for example, JPEG images.
        //
        case 16:
        {
            uint16_t ui16Byte;

            //
            // Loop while there are more pixels to draw.
            //
            while(i32Count--)
            {
                //
                // Get the next byte of pixel data and extract the
                // corresponding entry from the palette.
                //
                ui16Byte = *((uint16_t *)pui8Data);
                pui8Data += 2;

                //
                // Translate this palette entry and write it to the screen.
                //
                WriteDataSPI(ui16Byte);
            }
        }
    }
}


static void
SSD2119_LineDrawV(void *pvDisplayData, int32_t i32X,
        int32_t i32Y1, int32_t i32Y2,
        uint32_t ui32Value)
{
    //
    // Set the cursor increment to top to bottom, followed by left to right.
    //
    WriteCommandSPI(SSD2119_ENTRY_MODE_REG);
    WriteDataSPI(MAKE_ENTRY_MODE(VERT_DIRECTION));

    //
    // Set the X address of the display cursor.
    //
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_X(i32X, i32Y1));

    //
    // Set the starting Y address of the display cursor.
    //
    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_Y(i32X, i32Y1));

    //
    // Write the data RAM write command.
    //
    WriteCommandSPI(SSD2119_RAM_DATA_REG);

    //
    // Loop through the pixels of this vertical line.
    //
    while(i32Y1++ <= i32Y2)
    {
        //
        // Write the pixel value.
        //
        WriteDataSPI(ui32Value);
    }
}


static void
SSD2119_RectFill(void *pvDisplayData, const tRectangle *pRect,
                                 uint32_t ui32Value)
{
    int32_t i32Count;

    //
    // Write the Y extents of the rectangle.
    //
    WriteCommandSPI(SSD2119_ENTRY_MODE_REG);
    WriteDataSPI(MAKE_ENTRY_MODE(HORIZ_DIRECTION));

    //
    // Write the X extents of the rectangle.
    //
    WriteCommandSPI(SSD2119_H_RAM_START_REG);
#if (defined PORTRAIT) || (defined LANDSCAPE)
    WriteDataSPI(MAPPED_X(pRect->xMax, pRect->xMax));
#else
    WriteDataSPI(MAPPED_X(pRect->i16XMin, pRect->i16YMin));
#endif

    WriteCommandSPI(SSD2119_H_RAM_END_REG);
#if (defined PORTRAIT) || (defined LANDSCAPE)
    WriteDataSPI(MAPPED_X(pRect->xMin, pRect->xYMin));
#else
    WriteDataSPI(MAPPED_X(pRect->i16XMax, pRect->i16YMax));
#endif

    //
    // Write the Y extents of the rectangle
    //
    WriteCommandSPI(SSD2119_V_RAM_POS_REG);
#if (defined LANDSCAPE_FLIP) || (defined PORTRAIT)
    WriteDataSPI(MAPPED_Y(pRect->i16XMin, pRect->i16YMin) |
             (MAPPED_Y(pRect->i16XMax, pRect->i16YMax) << 8));
#else
    WriteDataSPI(MAPPED_Y(pRect->xMax, pRect->yMax) |
             (MAPPED_Y(pRect->xMin, pRect->yMin) << 8));
#endif

    //
    // Set the display cursor to the upper left of the rectangle (in
    // application coordinate space).
    //
    WriteCommandSPI(SSD2119_X_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_X(pRect->xMin, pRect->yMin));

    WriteCommandSPI(SSD2119_Y_RAM_ADDR_REG);
    WriteDataSPI(MAPPED_Y(pRect->xMin, pRect->yMin));

    //
    // Tell the controller we are about to write data into its RAM.
    //
    WriteCommandSPI(SSD2119_RAM_DATA_REG);

    //
    // Loop through the pixels of this filled rectangle.
    //
    for(i32Count = ((pRect->xMax - pRect->xMin + 1) *
                  (pRect->yMax - pRect->yMin + 1));
                  i32Count >= 0; i32Count--)
    {
        //
        // Write the pixel value.
        //
        WriteDataSPI(ui32Value);
    }

    //
    // Reset the X extents to the entire screen.
    //
    WriteCommandSPI(SSD2119_H_RAM_START_REG);
    WriteDataSPI(0x0000);
    WriteCommandSPI(SSD2119_H_RAM_END_REG);
    WriteDataSPI(0x013F);

    //
    // Reset the Y extent to the full screen
    //
    WriteCommandSPI(SSD2119_V_RAM_POS_REG);
    WriteDataSPI(0xEF00);
}


static uint32_t
SSD2119_ColorTranslate(void *pvDisplayData,
                                       uint32_t ui32Value)
{
    //
    // Translate from a 24-bit RGB color to a 5-6-5 RGB color.
    //
    return(DPYCOLORTRANSLATE(ui32Value));
}

//*****************************************************************************
//
//! Flushes any cached drawing operations.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//!
//! This functions flushes any cached drawing operations to the display.  This
//! is useful when a local frame buffer is used for drawing operations, and the
//! flush would copy the local frame buffer to the display.  For the SSD2119_
//! driver, the flush is a no operation.
//!
//! \return None.
//
//*****************************************************************************
static void
SSD2119_Flush(void *pvDisplayData)
{
    //
    // There is nothing to be done.
    //
}

//*****************************************************************************
//
//! Flushes any cached drawing operations.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//!
//! This functions flushes any cached drawing operations to the display.  This
//! is useful when a local frame buffer is used for drawing operations, and the
//! flush would copy the local frame buffer to the display.  For the SSD2119_
//! driver, the flush is a no operation.
//!
//! \return None.
//
//*****************************************************************************
static void
SSD2119_ClearDisplay(void *pvDisplayData, uint16_t value)
{
    // Clear the contents of the display buffer.
    WriteCommandSPI(SSD2119_RAM_DATA_REG);
    unsigned int ulCount;
    for(ulCount = 0; ulCount < (320 * 240); ulCount++)
    {
        WriteDataSPI(0x0000);
    }
}

//*****************************************************************************
//
//! The display structure that describes the driver for the Kentec
//! K350QVG-V2-F TFT panel with an SSD2119_ controller.
//
//*****************************************************************************
const tDisplay g_sKentec320x240x16_SSD2119 =
{
    sizeof(tDisplay),
    0,
    320,
    240,
    SSD2119_PixelDraw,
    SSD2119_PixelDrawMultiple,
    SSD2119_LineDrawH,
    SSD2119_LineDrawV,
    SSD2119_RectFill,
    SSD2119_ColorTranslate,
    SSD2119_Flush,
    SSD2119_ClearDisplay
};
