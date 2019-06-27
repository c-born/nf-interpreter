//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_ 1

#include "nanoCLR_Types.h"
#include <nanoPAL.h>
#include <target_platform.h>
#include <Esp32_os.h>


static void IRAM_ATTR spi_ready(spi_transaction_t* trans);
static spi_device_handle_t spi;
static volatile bool spi_trans_in_progress;

//----------------------------------
// ESP32 Pin
// LCD Signal
//-----------------------------
// LCD_RST_1	GPIO18	RESET
// LCD_CLK_1	GPIO19	SCL
// LCD_D/CX_1	GPIO21	D / C
// LCD_CS_1	GPIO22	CS
// LCD_MOSI_1	GPIO23	SDA
// LCD_MISO_1	GPIO25	SDO
// R_IO5		GPIO5	Backlight
//----------------------------------

//----------------------------------
// ESP32 Pin

#define SPI_MOSI GPIO_NUM_23		// MOSI_1	GPIO23	SDA
#define SPI_MISO GPIO_NUM_25        // MISO_1	GPIO25	SDO
#define SPI_CLK  GPIO_NUM_19        // CLK_1	GPIO19	SCL
#define SPI_CS   GPIO_NUM_22        // CS_1	    GPIO22	CS

#define LCD_RESET GPIO_NUM_18       // RST_1	GPIO18	RESET
#define LCD_D_CX  GPIO_NUM_21       // D/CX_1	GPIO21	D/C

#define SPI_HOST HSPI_HOST

#define LV_VDB_SIZE 1 // fudged to compile


static void IRAM_ATTR spi_ready(spi_transaction_t * trans)
{
	spi_trans_in_progress = false;
	//if (spi_color_sent) lv_flush_ready();
}

// Display Interface
bool UI_DISPLAY::InitializeDisplayDriver()
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
			.clock_speed_hz = 40 * 1000 * 1000,           //Clock out at 80 MHz
			.mode = 0,                                //SPI mode 0
			.spics_io_num = SPI_CS,              //CS pin
			.queue_size = 1,
			.pre_cb = NULL,
			.post_cb = spi_ready,
			.flags = SPI_DEVICE_NO_DUMMY              // ignore errors
	};

	//Initialize the SPI bus
	ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
	ASSERT(ret == ESP_OK);

	//Attach the LCD to the SPI bus
	ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
	ASSERT(ret == ESP_OK);

	gpio_set_direction(ILI9341_DC, GPIO_MODE_OUTPUT);
	gpio_set_direction(ILI9341_RST, GPIO_MODE_OUTPUT);
	gpio_set_direction(ILI9341_BCKL, GPIO_MODE_OUTPUT);



	return TRUE;
}
void UI_DISPLAY::SendCommand(CLR_UINT8 c)
{
	gpio_set_level(ILI9341_DC, 0);	 /*Command mode*/
	disp_spi_send_data(&cmd, 1);
	return;
}
void UI_DISPLAY::SendCommand(CLR_UINT8 command, CLR_UINT8 value)
{
	gpio_set_level(ILI9341_DC, 0);	 /*Command mode*/
	disp_spi_send_data(&cmd, 1);
	return;
}
void UI_DISPLAY::SendData(CLR_UINT16 value)         // Word data
{
	gpio_set_level(ILI9341_DC, 1);	 /*Data mode*/
	disp_spi_send_data(data, length);
}
void UI_DISPLAY::SendData(const CLR_UINT16 data[], CLR_UINT16 count)
{
	if (count == 0) return;           //no need to send anything

	while (spi_trans_in_progress);

	spi_transaction_t t;
	memset(&t, 0, sizeof(t));       	//Zero out the transaction
	t.length = count * 8;              //Length is in bytes, transaction length is in bits.
	t.tx_buffer = data;               	//Data
	spi_trans_in_progress = true;
	spi_color_sent = false;             //Mark the "lv_flush_ready" NOT needs to be called in "spi_ready"
	spi_device_queue_trans(spi, &t, portMAX_DELAY);


	int i;
	for (i = 0; i < count; i += 2)
	{
		(void)SendCommand((CLR_UINT16)data[i]);
		(void)SendData((CLR_UINT16)data[i + 1]);
	}
}
void UI_DISPLAY::SendData(CLR_UINT8* pParams, int numberOfParameters)
{
	return;
}



#endif  // _GRAPHICS_H_
