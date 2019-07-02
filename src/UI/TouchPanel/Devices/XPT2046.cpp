//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _XPT2046_H_
#define _XPT2046_H_ 1

#include "TouchInterface.h"
#include "Graphics.h"
#include "Touch.h"

HRESULT Initialize()
{
	TouchInterface::Initialize();
}
HRESULT Uninitialize()
{
	TouchInterface::Uninitialize();
}
HRESULT GetDeviceCaps(CLR_UINT32 iIndex, void* lpOutput)
{
	return 1;
}
bool Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
	return 1;
}
bool Disable() { return 1; }
HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
	return 1;
}
HRESULT SetNativeBufferSize(int transientBufferSize, int strokeBufferSize)
{
	return 1;
}
HRESULT ResetCalibration()
{
	return 1;
}
HRESULT SetCalibration(CLR_INT32 pointCount, short* sx, short* sy, short* ux, short* uy)
{
	return 1;
}
void SetDriverDefaultCalibrationData()
{
	return ;
}
HRESULT EnableTouchCollection(CLR_INT32 flags, CLR_INT32 x1, CLR_INT32 x2, CLR_INT32 y1, CLR_INT32 y2, PAL_GFX_Bitmap* bitmap)
{
	return 1;
}
bool CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT* pTCP)
{
	return 1;
}
void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, CLR_INT32* pSource, CLR_INT32* pUnCalX, CLR_INT32* pUnCalY)
{
	return 1;
}
HRESULT GetTouchPoint(CLR_UINT32* flags, CLR_UINT16* source, CLR_UINT16* x, CLR_UINT16* y, CLR_INT64* time)
{
	return 1;
}
HRESULT GetTouchPoint(CLR_UINT32* flags, CLR_UINT32* location, CLR_INT64* time)
{
	return 1;
}
HRESULT GetTouchPoint(CLR_UINT32* flags, TouchPoint** point)
{
	return 1;
}
HRESULT GetTouchPoints(CLR_INT32* pointCount, short* sx, short* sy)
{
	return 1;
}
HRESULT GetSetTouchInfo(CLR_UINT32 flags, CLR_INT32* param1, CLR_INT32* param2, CLR_INT32* param3)
{
	return 1;
}
void TouchIsrProc(GPIO_PIN pin, bool pinState, void* context)
{
	return;
}
void TouchCompletion(void* arg)
{
	return;
}
void TouchPanelCalibratePoint(int UncalX, int UncalY, int* pCalX, int* pCalY)
{
	return;
}
CLR_UINT16 GetTouchStylusFlags(unsigned int sampleFlags)
{
	return 1;
}
void PollTouchPoint(void* arg)
{
	return;
}
TouchPoint* AddTouchPoint(CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time, bool fIgnoreDuplicate = FALSE)
{
	return NULL;
}


#endif // _XPT2046_H_

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



bool UI_TOUCH::Write_Read(const SPI_CONFIGURATION & Configuration, CLR_UINT8 * Write8, CLR_INT32 WriteCount, CLR_UINT8 * Read8, CLR_INT32 ReadCount, CLR_INT32 ReadStartOffset)
{

	return true;
}

};


////////////////////////////


/**
 * @file XPT2046.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "xpt2046.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "tp_spi.h"
#include <stddef.h>

  /*********************
   *      DEFINES
   *********************/
#define CMD_X_READ  0b10010000
#define CMD_Y_READ  0b11010000

   /**********************
	*      TYPEDEFS
	**********************/

	/**********************
	 *  STATIC PROTOTYPES
	 **********************/
static void xpt2046_corr(int16_t * x, int16_t * y);
static void xpt2046_avg(int16_t* x, int16_t* y);

/**********************
 *  STATIC VARIABLES
 **********************/
int16_t avg_buf_x[XPT2046_AVG];
int16_t avg_buf_y[XPT2046_AVG];
uint8_t avg_last;

/**********************
 *      MACROS
 **********************/

 /**********************
  *   GLOBAL FUNCTIONS
  **********************/

  /**
   * Initialize the XPT2046
   */
void xpt2046_init(void)
{
	gpio_set_direction(XPT2046_IRQ, GPIO_MODE_INPUT);
	gpio_set_direction(TP_SPI_CS, GPIO_MODE_OUTPUT);
	gpio_set_level(TP_SPI_CS, 1);

}

/**
 * Get the current position and state of the touchpad
 * @param data store the read data here
 * @return false: because no ore data to be read
 */
bool xpt2046_read(lv_indev_data_t* data)
{
	static int16_t last_x = 0;
	static int16_t last_y = 0;
	bool valid = true;
	uint8_t buf;

	int16_t x = 0;
	int16_t y = 0;

	uint8_t irq = gpio_get_level(XPT2046_IRQ);

	if (irq == 0) {
		gpio_set_level(TP_SPI_CS, 0);
		tp_spi_xchg(CMD_X_READ);         /*Start x read*/

		buf = tp_spi_xchg(0);           /*Read x MSB*/
		x = buf << 8;
		buf = tp_spi_xchg(CMD_Y_READ);  /*Until x LSB converted y command can be sent*/
		x += buf;

		buf = tp_spi_xchg(0);   /*Read y MSB*/
		y = buf << 8;

		buf = tp_spi_xchg(0);   /*Read y LSB*/
		y += buf;
		gpio_set_level(TP_SPI_CS, 1);

		/*Normalize Data*/
		x = x >> 3;
		y = y >> 3;
		xpt2046_corr(&x, &y);
		xpt2046_avg(&x, &y);
		last_x = x;
		last_y = y;


	}
	else {
		x = last_x;
		y = last_y;
		avg_last = 0;
		valid = false;
	}

	data->point.x = x;
	data->point.y = y;
	data->state = valid == false ? LV_INDEV_STATE_REL : LV_INDEV_STATE_PR;

	return valid;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void xpt2046_corr(int16_t* x, int16_t* y)
{
#if XPT2046_XY_SWAP != 0
	int16_t swap_tmp;
	swap_tmp = *x;
	*x = *y;
	*y = swap_tmp;
#endif

	if ((*x) > XPT2046_X_MIN)(*x) -= XPT2046_X_MIN;
	else(*x) = 0;

	if ((*y) > XPT2046_Y_MIN)(*y) -= XPT2046_Y_MIN;
	else(*y) = 0;

	(*x) = (uint32_t)((uint32_t)(*x) * LV_HOR_RES) /
		(XPT2046_X_MAX - XPT2046_X_MIN);

	(*y) = (uint32_t)((uint32_t)(*y) * LV_VER_RES) /
		(XPT2046_Y_MAX - XPT2046_Y_MIN);

#if XPT2046_X_INV != 0
	(*x) = LV_HOR_RES - (*x);
#endif

#if XPT2046_Y_INV != 0
	(*y) = LV_VER_RES - (*y);
#endif


}


static void xpt2046_avg(int16_t* x, int16_t* y)
{
	/*Shift out the oldest data*/
	uint8_t i;
	for (i = XPT2046_AVG - 1; i > 0; i--) {
		avg_buf_x[i] = avg_buf_x[i - 1];
		avg_buf_y[i] = avg_buf_y[i - 1];
	}

	/*Insert the new point*/
	avg_buf_x[0] = *x;
	avg_buf_y[0] = *y;
	if (avg_last < XPT2046_AVG) avg_last++;

	/*Sum the x and y coordinates*/
	int32_t x_sum = 0;
	int32_t y_sum = 0;
	for (i = 0; i < avg_last; i++) {
		x_sum += avg_buf_x[i];
		y_sum += avg_buf_y[i];
	}

	/*Normalize the sums*/
	(*x) = (int32_t)x_sum / avg_last;
	(*y) = (int32_t)y_sum / avg_last;
}

#endif  // _DRIVERS_PAL_GRAPHICS_H_
