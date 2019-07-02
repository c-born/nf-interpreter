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


static void IRAM_ATTR spi_ready(spi_transaction_t * trans)
{
	spi_trans_in_progress = false;
	//if (spi_color_sent) lv_flush_ready();
}

// Display Interface
bool DisplayInterface::InitializeDisplayDriver()
{
	esp_err_t ret;
	spi_bus_config_t buscfg = {
			.miso_io_num = -1,
			.mosi_io_num = SPI_MOSI,
			.sclk_io_num = SPI_CLK,
			.quadwp_io_num = -1,
			.quadhd_io_num = -1,
			.max_transfer_sz = LV_VDB_SIZE * 2,
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
	return TRUE;
}

void DisplayInterface::SendCommand(CLR_UINT8 c)
{
	gpio_set_level(LCD_D_CX, 0);	 /*Command mode*/
	disp_spi_send_data(&cmd, 1);
	return;
}
void DisplayInterface::SendCommand(CLR_UINT8 command, CLR_UINT8 value)
{
	gpio_set_level(LCD_D_CX, 0);	 /*Command mode*/
	disp_spi_send_data(&cmd, 1);
	return;
}
void SendCommandAndData(CLR_UINT8 command, CLR_UINT8 data[], CLR_UINT32 dataCount)
{
	gpio_set_level(LCD_D_CX, 0);	 /*Command mode*/
	spi_send_bytes(&cmd, 1);
	gpio_set_level(LCD_D_CX, 1);	 /*Data mode*/
	spi_send_bytes(data, dataCount);
	return
}
void DisplayInterface::SendData(const CLR_UINT16 data[], CLR_UINT16 dataCount)
{
	gpio_set_level(LCD_D_CX, 1);	 /*Data mode*/
	spi_send_bytes(data, dataCount);

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
void spi_send_bytes(uint8_t* data, uint16_t length)
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

#endif  // _SPI_TO_DISPLAY_


//////
//////void ili9341_init()
//////{
//////
//////
//////	//Initialize non-SPI GPIOs
//////
//////	//gpio_set_direction(ILI9341_DC, GPIO_MODE_OUTPUT);
//////	//gpio_set_direction(ILI9341_RST, GPIO_MODE_OUTPUT);
//////	//gpio_set_direction(ILI9341_BCKL, GPIO_MODE_OUTPUT);
//////
//////	gpio_set_direction(ILI9341_DC, GPIO_MODE_OUTPUT);
//////	gpio_set_direction(ILI9341_RST, GPIO_MODE_OUTPUT);
//////	gpio_set_direction(ILI9341_BCKL, GPIO_MODE_OUTPUT);
//////
//////
//////	//Reset the display
//////	gpio_set_level(ILI9341_RST, 0);
//////	vTaskDelay(100 / portTICK_RATE_MS);
//////	gpio_set_level(ILI9341_RST, 1);
//////	vTaskDelay(100 / portTICK_RATE_MS);
//////
//////	//Send all the commands
//////	uint16_t cmd = 0;
//////	while (ili_init_cmds[cmd].databytes != 0xff) {
//////		ili9341_send_cmd(ili_init_cmds[cmd].cmd);
//////		ili9341_send_data(ili_init_cmds[cmd].data, ili_init_cmds[cmd].databytes & 0x1F);
//////		if (ili_init_cmds[cmd].databytes & 0x80) {
//////			vTaskDelay(100 / portTICK_RATE_MS);
//////		}
//////		cmd++;
//////	}
//////	gpio_set_level(ILI9341_BCKL, 0);
//////}
//////void ili9341_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
//////{
//////	uint8_t data[4];
//////
//////	/*Column addresses*/
//////	ili9341_send_cmd(0x2A);
//////	data[0] = (x1 >> 8) & 0xFF;
//////	data[1] = x1 & 0xFF;
//////	data[2] = (x2 >> 8) & 0xFF;
//////	data[3] = x2 & 0xFF;
//////	ili9341_send_data(data, 4);
//////
//////	/*Page addresses*/
//////	ili9341_send_cmd(0x2B);
//////	data[0] = (y1 >> 8) & 0xFF;
//////	data[1] = y1 & 0xFF;
//////	data[2] = (y2 >> 8) & 0xFF;
//////	data[3] = y2 & 0xFF;
//////	ili9341_send_data(data, 4);
//////
//////	/*Memory write*/
//////	ili9341_send_cmd(0x2C);
//////
//////	uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);
//////	uint16_t buf[LV_HOR_RES];
//////
//////	uint32_t i;
//////	if (size < LV_HOR_RES) {
//////		for (i = 0; i < size; i++) buf[i] = color.full;
//////
//////	}
//////	else {
//////		for (i = 0; i < LV_HOR_RES; i++) buf[i] = color.full;
//////	}
//////
//////	while (size > LV_HOR_RES) {
//////		ili9341_send_color(buf, LV_HOR_RES * 2);
//////		size -= LV_HOR_RES;
//////	}
//////
//////	ili9341_send_color(buf, size * 2);	/*Send the remaining data*/
//////}
//////void ili9341_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t* color_map)
//////{
//////	uint8_t data[4];
//////
//////	/*Column addresses*/
//////	ili9341_send_cmd(0x2A);
//////	data[0] = (x1 >> 8) & 0xFF;
//////	data[1] = x1 & 0xFF;
//////	data[2] = (x2 >> 8) & 0xFF;
//////	data[3] = x2 & 0xFF;
//////	ili9341_send_data(data, 4);
//////
//////	/*Page addresses*/
//////	ili9341_send_cmd(0x2B);
//////	data[0] = (y1 >> 8) & 0xFF;
//////	data[1] = y1 & 0xFF;
//////	data[2] = (y2 >> 8) & 0xFF;
//////	data[3] = y2 & 0xFF;
//////	ili9341_send_data(data, 4);
//////
//////	/*Memory write*/
//////	ili9341_send_cmd(0x2C);
//////
//////
//////	uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);
//////
//////
//////	ili9341_send_color((void*)color_map, size * 2);	/*Send the remaining data*/
//////
////////	lv_flush_ready();
//////
//////}
//////static void ili9341_send_data(void* data, uint16_t length)
//////{
//////	gpio_set_level(ILI9341_DC, 1);	 /*Data mode*/
//////	disp_spi_send_data(data, length);
//////}
//////static void ili9341_send_color(void* data, uint16_t length)
//////{
//////	gpio_set_level(ILI9341_DC, 1);   /*Data mode*/
//////	disp_spi_send_colors(data, length);
//////}
//////
////////////////////
//////
///////**
////// * @file disp_spi.c
////// *
////// */
//////
////// /*********************
//////  *      INCLUDES
//////  *********************/
//////#include "disp_spi.h"
//////#include "esp_system.h"
//////#include "driver/gpio.h"
//////#include "driver/spi_master.h"
//////#include <string.h>
//////#include <freertos/FreeRTOS.h>
//////#include <freertos/semphr.h>
//////#include "freertos/task.h"
//////#include "../lvgl/lvgl.h"
//////
//////  /*********************
//////   *      DEFINES
//////   *********************/
//////
//////   /**********************
//////	*      TYPEDEFS
//////	**********************/
//////
//////	/**********************
//////	 *  STATIC PROTOTYPES
//////	 **********************/
//////static void IRAM_ATTR spi_ready(spi_transaction_t* trans);
//////
///////**********************
////// *  STATIC VARIABLES
////// **********************/
//////static spi_device_handle_t spi;
//////static volatile bool spi_trans_in_progress;
//////static volatile bool spi_color_sent;
//////
///////**********************
////// *      MACROS
////// **********************/
//////
////// /**********************
//////  *   GLOBAL FUNCTIONS
//////  **********************/
//////
//////
//////
//////
//////  //----------------------------------
//////  // ESP32 Pin
//////  // LCD Signal
//////  //-----------------------------
//////  // LCD_RST_1	GPIO18	RESET
//////  // LCD_CLK_1	GPIO19	SCL
//////  // LCD_D/CX_1	GPIO21	D / C
//////  // LCD_CS_1	GPIO22	CS
//////  // LCD_MOSI_1	GPIO23	SDA
//////  // LCD_MISO_1	GPIO25	SDO
//////  // R_IO5		GPIO5	Backlight
//////  //----------------------------------
//////
//////
//////
//////#define SPI_MOSI GPIO_NUM_23
//////#define SPI_MISO GPIO_NUM_25
//////#define SPI_CLK  GPIO_NUM_19
//////#define SPI_CS   GPIO_NUM_22
//////#define SPI_HOST HSPI_HOST
//////
//////void disp_spi_init()
//////{
//////
//////	esp_err_t ret;
//////
//////	spi_bus_config_t buscfg = {
//////			.miso_io_num = -1,
//////			.mosi_io_num = SPI_MOSI,
//////			.sclk_io_num = SPI_CLK,
//////			.quadwp_io_num = -1,
//////			.quadhd_io_num = -1,
//////			.max_transfer_sz = LV_VDB_SIZE * 2,
//////	};
//////
//////	spi_device_interface_config_t devcfg = {
//////			.clock_speed_hz = 40 * 1000 * 1000,           //Clock out at 80 MHz
//////			.mode = 0,                                //SPI mode 0
//////			.spics_io_num = SPI_CS,              //CS pin
//////			.queue_size = 1,
//////			.pre_cb = NULL,
//////			.post_cb = spi_ready,
//////			.flags = SPI_DEVICE_NO_DUMMY              // ignore errors
//////	};
//////
//////	//Initialize the SPI bus
//////	ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
//////	assert(ret == ESP_OK);
//////
//////	//Attach the LCD to the SPI bus
//////	ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
//////	assert(ret == ESP_OK);
//////}
//////
//////
//////void disp_spi_send_colors(uint8_t* data, uint16_t length)
//////{
//////	if (length == 0) return;           //no need to send anything
//////
//////	while (spi_trans_in_progress);
//////
//////	spi_transaction_t t;
//////	memset(&t, 0, sizeof(t));           //Zero out the transaction
//////	t.length = length * 8;              //Length is in bytes, transaction length is in bits.
//////	t.tx_buffer = data;                 //Data
//////	spi_trans_in_progress = true;
//////	spi_color_sent = true;              //Mark the "lv_flush_ready" needs to be called in "spi_ready"
//////	spi_device_queue_trans(spi, &t, portMAX_DELAY);
//////}


/**********************
 *   STATIC FUNCTIONS
 **********************/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static void IRAM_ATTR spi_ready(spi_transaction_t* trans)
{
	spi_trans_in_progress = false;

	if (spi_color_sent) lv_flush_ready();
}
#pragma GCC diagnostic pop

#endif  // _SPI_TO_DISPLAY_

