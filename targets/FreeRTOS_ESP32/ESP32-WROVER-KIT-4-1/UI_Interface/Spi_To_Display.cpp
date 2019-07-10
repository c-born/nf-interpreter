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


static volatile bool spi_trans_in_progress;

//----------------------------------
// ESP32 Wrover-Kit

#define SPI_MOSI GPIO_NUM_23		// MOSI_1	GPIO23	SDA
#define SPI_MISO GPIO_NUM_25        // MISO_1	GPIO25	SDO
#define SPI_CLK  GPIO_NUM_19        // CLK_1	GPIO19	SCL
#define SPI_CS   GPIO_NUM_22        // CS_1	    GPIO22	CS

#define LCD_RESET GPIO_NUM_18       // RST_1	GPIO18	RESET
#define LCD_D_CX  GPIO_NUM_21       // D/CX_1	GPIO21	D/C
#define LCD_BACKLIGHT GPIO_NUM_5  //GPIO5	Backlight

#define SPI_MAX_TRANSFER_SIZE 2048

static spi_device_handle_t spi;
static volatile bool spi_trans_in_progress;
static volatile bool spi_color_sent;


void disp_spi_send_data(uint8_t* data, uint16_t length)
{
	if (length == 0) return;           //no need to send anything
	while (spi_trans_in_progress);
	spi_transaction_t t;
	memset(&t, 0, sizeof(t));       	//Zero out the transaction
	t.length = length * 8;              //Length is in bytes, transaction length is in bits.
	t.tx_buffer = data;               	//Data
	spi_trans_in_progress = true;
	spi_color_sent = false;             //Mark the "lv_flush_ready" NOT needs to be called in "spi_ready"
	spi_device_queue_trans(spi, &t, portMAX_DELAY);
}


// Display Interface
bool DisplayInterface::InitializeDisplayInterface()
{
	esp_err_t ret;
	spi_bus_config_t buscfg = {
			.miso_io_num = -1,
			.mosi_io_num = SPI_MOSI,
			.sclk_io_num = SPI_CLK,
			.quadwp_io_num = -1,
			.quadhd_io_num = -1,
			.max_transfer_sz = SPI_MAX_TRANSFER_SIZE,
	};
	spi_device_interface_config_t devcfg = {
			.clock_speed_hz = 40 * 1000 * 1000,				//Clock out  MHz
			.mode = 0,										//SPI mode 0
			.spics_io_num = SPI_CS,							//CS pin
			.queue_size = 1,
			.pre_cb = NULL,
			.post_cb = spi_ready,
			.flags = SPI_DEVICE_NO_DUMMY					// ignore errors
	};

	//Initialize the SPI bus
	ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
	ASSERT(ret == ESP_OK);

	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
	ASSERT(ret == ESP_OK);

	gpio_set_direction(LCD_D_CX, GPIO_MODE_OUTPUT);
	gpio_set_direction(LCD_RESET, GPIO_MODE_OUTPUT);
	gpio_set_direction(LCD_BACKLIGHT, GPIO_MODE_OUTPUT);
	vTaskDelay(100 / portTICK_RATE_MS);

	return TRUE;
}
void DisplayInterface::SendCommand(CLR_UINT8 command)
{
	gpio_set_level(LCD_D_CX, 0);	 //Command mode
	spi_send_bytes(&command, 1);
	return;
}
void DisplayInterface::SendCommand(CLR_UINT8 command, CLR_UINT8 value)
{
	gpio_set_level(LCD_D_CX, 0);	 //Command mode
	spi_send_bytes(&command, 1);
	spi_send_bytes(&value, 1);
	return;
}
void SendCommandAndData(CLR_UINT8 command, CLR_UINT8* data, CLR_UINT32 dataCount)
{
	gpio_set_level(LCD_D_CX, 0);	 /*Command mode*/
	spi_send_bytes(&command, 1);
	gpio_set_level(LCD_D_CX, 1);	 /*Data mode*/
	spi_send_bytes(data, dataCount);
	return
}
void DisplayInterface::SendData(const CLR_UINT16 data[], CLR_UINT16 dataCount)
{
	int dataIndex = 0;
	int dataToSendLength = _min(dataCount, SPI_MAX_TRANSFER_SIZE);
	while (dataIndex > dataCount) {
		spi_send_bytes(buf, );
		size -= LV_HOR_RES;

	}

	gpio_set_level(LCD_D_CX, 1);	 /*Data mode*/
	spi_send_bytes(data, dataCount);
}
void spi_send_bytes(CLR_UINT8* data, CLR_UINT16 length)
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
void DisplayBacklight(bool on) // true = on
{

}
void DisplayPower(bool powerState)  // true = on
{

}
static void DisplayCommandDelay(CLR_INT16 delay)
{
	OS_DELAY(120);
}

//  STATIC FUNCTIONS
static void IRAM_ATTR spi_ready(spi_transaction_t* trans)
{
	spi_trans_in_progress = false;
	if (spi_color_sent) lv_flush_ready();
}
static void IRAM_ATTR spi_ready(spi_transaction_t* trans)
{
	if (trans == NULL) {};				// Avoid unused parameter, maybe use in the future
	spi_trans_in_progress = false;
}

#endif  // _SPI_TO_DISPLAY_

