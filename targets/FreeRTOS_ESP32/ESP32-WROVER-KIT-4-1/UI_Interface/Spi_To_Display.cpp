//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _SPI_TO_DISPLAY_
#define _SPI_TO_DISPLAY_ 1

#include "nanoCLR_Types.h"
#include <nanoPAL.h>
#include <target_platform.h>
#include <Esp32_os.h>
#include "Esp32_DeviceMapping.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "DisplayInterface.h"

// ESP32 - Documentation
// https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/spi_master.html

// ESP32 Wrover-Kit

static spi_device_handle_t spi;
static volatile bool spi_trans_in_progress;
static void disp_spi_send_bytes(CLR_UINT8* data, CLR_UINT32 length);

const int SPI_MOSI = GPIO_NUM_23;					// MOSI_1	GPIO23	SDA
const int SPI_MISO = GPIO_NUM_25;					// MISO_1	GPIO25	SDO
const int SPI_CLK = GPIO_NUM_19;					// CLK_1	GPIO19	SCL
const int SPI_CS = GPIO_NUM_22;						// CS_1	    GPIO22	CS

const gpio_num_t  LCD_RESET = GPIO_NUM_18;			// RST_1	GPIO18	RESET
const gpio_num_t LCD_D_CX = GPIO_NUM_21;			// D/CX_1	GPIO21	D/C
const gpio_num_t LCD_BACKLIGHT = GPIO_NUM_5;		// GPIO5	Backlight

const int  SPI_MAX_TRANSFER_SIZE = 4096;

static void IRAM_ATTR spi_ready(spi_transaction_t* trans)
{
	spi_trans_in_progress = false;
	if (trans->tx_buffer == NULL) {}; // avoid unused parameter, maybe used in the future
}

// Display Interface
bool DisplayInterface::InitializeDisplayInterface()
{
	esp_err_t ret;
	spi_bus_config_t buscfg;
	buscfg.mosi_io_num = SPI_MOSI;
	buscfg.miso_io_num = -1;
	buscfg.sclk_io_num = SPI_CLK;
	buscfg.quadwp_io_num = -1;
	buscfg.quadhd_io_num = -1;
	buscfg.max_transfer_sz = SPI_MAX_TRANSFER_SIZE;

	spi_device_interface_config_t devcfg;
	devcfg.clock_speed_hz = 40 * 1000 * 1000;		//Clock out  MHz
	devcfg.mode = 0;								//SPI mode 0
	devcfg.spics_io_num = SPI_CS;					//CS pin
	devcfg.queue_size = 1;
	devcfg.pre_cb = NULL;
	devcfg.post_cb = spi_ready;
	devcfg.flags = SPI_DEVICE_NO_DUMMY;				// ignore errors

	//Initialize the SPI bus
	ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
	ASSERT(ret == ESP_OK);

	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
	ASSERT(ret == ESP_OK);

	//Initialize non-SPI GPIOs
	gpio_set_direction(LCD_D_CX, GPIO_MODE_OUTPUT);
	gpio_set_direction(LCD_RESET, GPIO_MODE_OUTPUT);
	gpio_set_direction(LCD_BACKLIGHT, GPIO_MODE_OUTPUT);

	//Reset the display
	gpio_set_level(LCD_RESET, 0);
	DisplayCommandDelay(100);
	gpio_set_level(LCD_RESET, 1);
	DisplayCommandDelay(100);

	return TRUE;
}
void DisplayInterface::SendCommand(CLR_UINT8 command)
{
	gpio_set_level(LCD_D_CX, 0);	 //Command mode
	disp_spi_send_bytes(&command, 1);
	return;
}
void DisplayInterface::SendData(CLR_UINT8 data[], CLR_UINT32 dataCount)
{
	gpio_set_level(LCD_D_CX, 1);	 // Data mode
	disp_spi_send_bytes(data, dataCount);
}
void DisplayInterface::SendCommandAndData(CLR_UINT8 command, CLR_UINT8 data[], CLR_UINT32 dataCount)
{
	SendCommand(command);
	SendData(data, dataCount);
}
void DisplayInterface::DisplayBacklight(bool on) // true = on
{
	if (on)
	{
		gpio_set_level(LCD_BACKLIGHT, 1);

	}
	else
	{
		gpio_set_level(LCD_BACKLIGHT, 0);

	}

}
void DisplayInterface::DisplayCommandDelay(CLR_INT16 delay)
{
	OS_DELAY(delay);
}

//  esp-idf-v3.1 functions
void disp_spi_send_bytes(CLR_UINT8* data, CLR_UINT32 length)
{
	if (length == 0) return;           //no need to send anything
	while (spi_trans_in_progress);
	spi_transaction_t t;
	memset(&t, 0, sizeof(t));       	//Zero out the transaction
	t.length = length * 8;              //Length is in bytes, transaction length is in bits.
	t.tx_buffer = data;               	//Data
	spi_trans_in_progress = true;
	spi_device_queue_trans(spi, &t, portMAX_DELAY);

}

#endif  // _SPI_TO_DISPLAY_

