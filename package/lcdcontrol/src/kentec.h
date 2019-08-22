#ifndef __SSD2119_CTRLLCD_H__
#define ___SSD2119_CTRLLCD_H__


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define BUF_SIZE 9

#define CHAR_DEV_NAME   "fpga-control"

#include "grlib/grlib.h"



//*****************************************************************************
//
// This driver operates in four different screen orientations.  They are:
//
// * Portrait - The screen is taller than it is wide, and the flex connector is
//              on the left of the display.  This is selected by defining
//              PORTRAIT.
//
// * Landscape - The screen is wider than it is tall, and the flex connector is
//               on the bottom of the display.  This is selected by defining
//               LANDSCAPE.
//
// * Portrait flip - The screen is taller than it is wide, and the flex
//                   connector is on the right of the display.  This is
//                   selected by defining PORTRAIT_FLIP.
//
// * Landscape flip - The screen is wider than it is tall, and the flex
//                    connector is on the top of the display.  This is
//                    selected by defining LANDSCAPE_FLIP.
//
// These can also be imagined in terms of screen rotation; if portrait mode is
// 0 degrees of screen rotation, landscape is 90 degrees of counter-clockwise
// rotation, portrait flip is 180 degrees of rotation, and landscape flip is
// 270 degress of counter-clockwise rotation.
//
// If no screen orientation is selected, "landscape flip" mode will be used.
//
//*****************************************************************************
#if ! defined(PORTRAIT) && ! defined(PORTRAIT_FLIP) && \
    ! defined(LANDSCAPE) && ! defined(LANDSCAPE_FLIP)
#define LANDSCAPE
//#define PORTRAIT_FLIP
#endif

//*****************************************************************************
//
// Various definitions controlling coordinate space mapping and drawing
// direction in the four supported orientations.
//
//*****************************************************************************
#ifdef PORTRAIT
#define HORIZ_DIRECTION 0x28
#define VERT_DIRECTION 0x20
#define MAPPED_X(x, y) (319 - (y))
#define MAPPED_Y(x, y) (x)
#endif
#ifdef LANDSCAPE
#define HORIZ_DIRECTION 0x00
#define VERT_DIRECTION  0x08
#define MAPPED_X(x, y) (319 - (x))
#define MAPPED_Y(x, y) (239 - (y))
#endif
#ifdef PORTRAIT_FLIP
#define HORIZ_DIRECTION 0x18
#define VERT_DIRECTION 0x10
#define MAPPED_X(x, y) (y)
#define MAPPED_Y(x, y) (239 - (x))
#endif
#ifdef LANDSCAPE_FLIP
#define HORIZ_DIRECTION 0x30
#define VERT_DIRECTION  0x38
#define MAPPED_X(x, y) (x)
#define MAPPED_Y(x, y) (y)
#endif

#define SPI3	//9-bit 3-wire SPI (SSI2) mode (SCLK, SDA, SCS)
              // Default setting for the BOOSTXL-K350QVG-S1
							// Need to remove the "R10" (connect the "PB7/SSI2Tx" to "PD1/AIN6_TOUCH_XP") on Launchpad
//#define SPI4	//8-bit 4-wire SPI (SSI2) mode (SCLK, SDA, SCS, SDC)
							// Need to remove the "R10" (connect the "PB7/SSI2Tx" to "PD1/AIN6_TOUCH_XP") on Launchpad
							// Need to move the "R2" to "R3" position,
							// and move "R8" to "R9" position on the BOOSTXL-K350QVG-S1

//*****************************************************************************
//
// Defines for the pins that are used to communicate with the SSD2119.
//
//*****************************************************************************
#define LCD_CS_PERIPH           SYSCTL_PERIPH_GPIOA
#define LCD_CS_BASE             GPIO_PORTA_BASE
#define LCD_CS_PIN              GPIO_PIN_4

#define LCD_DC_PERIPH           SYSCTL_PERIPH_GPIOA
#define LCD_DC_BASE             GPIO_PORTA_BASE
#define LCD_DC_PIN              GPIO_PIN_5

#define LCD_RST_PERIPH           SYSCTL_PERIPH_GPIOD
#define LCD_RST_BASE             GPIO_PORTD_BASE
#define LCD_RST_PIN              GPIO_PIN_7

#define LCD_LED_PERIPH           SYSCTL_PERIPH_GPIOF
#define LCD_LED_BASE             GPIO_PORTF_BASE
#define LCD_LED_PIN              GPIO_PIN_2

//*****************************************************************************
//
// The dimensions of the LCD panel.
//
//*****************************************************************************
#define LCD_VERTICAL_MAX 240
#define LCD_HORIZONTAL_MAX 320


#define SSD2119_OSC_START_REG   			0x00
#define SSD2119_OUTPUT_CTRL_REG 			0x01
#define SSD2119_LCD_DRIVE_AC_CTRL_REG     	0x02
#define SSD2119_PWR_CTRL_1_REG  			0x03
#define SSD2119_DISPLAY_CTRL_REG        	0x07
#define SSD2119_FRAME_CYCLE_CTRL_REG    	0x0b
#define SSD2119_PWR_CTRL_2_REG  			0x0c
#define SSD2119_PWR_CTRL_3_REG  			0x0d
#define SSD2119_PWR_CTRL_4_REG  			0x0e
#define SSD2119_GATE_SCAN_START_REG     	0x0f
#define SSD2119_SLEEP_MODE_1_REG        	0x10
#define SSD2119_ENTRY_MODE_REG  			0x11
#define SSD2119_SLEEP_MODE_2_REG        	0x12
#define SSD2119_GEN_IF_CTRL_REG 			0x15
#define SSD2119_PWR_CTRL_5_REG  			0x1e
#define SSD2119_RAM_DATA_REG    			0x22
#define SSD2119_FRAME_FREQ_REG  			0x25
#define SSD2119_ANALOG_SET_REG  			0x26
#define SSD2119_VCOM_OTP_1_REG  			0x28
#define SSD2119_VCOM_OTP_2_REG  			0x29
#define SSD2119_GAMMA_CTRL_1_REG        	0x30
#define SSD2119_GAMMA_CTRL_2_REG        	0x31
#define SSD2119_GAMMA_CTRL_3_REG        	0x32
#define SSD2119_GAMMA_CTRL_4_REG        	0x33
#define SSD2119_GAMMA_CTRL_5_REG        	0x34
#define SSD2119_GAMMA_CTRL_6_REG        	0x35
#define SSD2119_GAMMA_CTRL_7_REG        	0x36
#define SSD2119_GAMMA_CTRL_8_REG        	0x37
#define SSD2119_GAMMA_CTRL_9_REG        	0x3a
#define SSD2119_GAMMA_CTRL_10_REG       	0x3b
#define SSD2119_V_RAM_POS_REG   			0x44
#define SSD2119_H_RAM_START_REG 			0x45
#define SSD2119_H_RAM_END_REG   			0x46
#define SSD2119_X_RAM_ADDR_REG  			0x4e
#define SSD2119_Y_RAM_ADDR_REG  			0x4f

#define ENTRY_MODE_DEFAULT      0x6830
#define ENTRY_MODE_DEFAULT 0x6830
#define MAKE_ENTRY_MODE(x) ((ENTRY_MODE_DEFAULT & 0xFF00) | (x))

//*****************************************************************************
//
// Translates a 24-bit RGB color to a display driver-specific color.
//
// \param c is the 24-bit RGB color.  The least-significant byte is the blue
// channel, the next byte is the green channel, and the third byte is the red
// channel.
//
// This macro translates a 24-bit RGB color into a value that can be written
// into the display's frame buffer in order to reproduce that color, or the
// closest possible approximation of that color.
//
// \return Returns the display-driver specific color.
//
//*****************************************************************************
#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8) |               \
                                 (((c) & 0x0000fc00) >> 5) |               \
                                 (((c) & 0x000000f8) >> 3))





//unsigned short convertColor(unsigned char r, unsigned char g, unsigned char b);
void SSD2119_Init(void);
void SSD2119_open();
void SSD2119_InitNew(void);
//void SSD2119PixelDraw(int lX, int lY,unsigned int ulValue);
//void SSD2119LineDrawH(int lX1, int lX2, int lY, unsigned int ulValue);
void SSD2119_close();
extern const tDisplay g_sKentec320x240x16_SSD2119;

#endif // __SSD2119_CTRLLCD_H__
