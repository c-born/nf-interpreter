//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _UI_H_
#define _TARGETPAL_UI_H_ 1

#include "nanoCLR_Types.h"
#include <nanoPAL.h>
#include <target_platform.h>
#include <Esp32_os.h>


//----------------------------------
// ESP32 Pin

#define SPI_MOSI GPIO_NUM_23		// MOSI_1	GPIO23	SDA
#define SPI_MISO GPIO_NUM_25        // MISO_1	GPIO25	SDO
#define SPI_CLK  GPIO_NUM_19        // CLK_1	GPIO19	SCL
#define SPI_CS   GPIO_NUM_22        // CS_1	    GPIO22	CS

#define LCD_RESET GPIO_NUM_18       // RST_1	GPIO18	RESET
#define LCD_D_CX  GPIO_NUM_21       // D/CX_1	GPIO21	D/C

#define SPI_HOST HSPI_HOST

bool UI_TOUCH::Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
	// Enable interrupt on GPIO PIN

	// Enable SPI for touch functions
	return TRUE;
}
bool UI_TOUCH::Disable()
{
	// Remove GPIO interrupt activity

	// Remove use of SPI for touch functions
	return true;
}


bool UI_TOUCH::Write_Read(const SPI_CONFIGURATION& Configuration, CLR_UINT8* Write8, CLR_INT32 WriteCount, CLR_UINT8* Read8, CLR_INT32 ReadCount, CLR_INT32 ReadStartOffset)
{

	return true;
}

};

#endif  // _DRIVERS_PAL_GRAPHICS_H_
