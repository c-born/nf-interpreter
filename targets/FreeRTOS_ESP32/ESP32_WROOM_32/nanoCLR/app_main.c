#pragma GCC optimize ("O0")

//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#include <Esp32_os.h>

#include <targetHAL.h>
#include <nanoCLR_Application.h>
#include <WireProtocol_ReceiverThread.h>
#include <LaunchCLR.h>
#include <string.h>

//
//#include "lv_obj.h"
//#include "lv_draw.h"
//#include "lv_draw_line.h"
//#include "lv_hal_disp.h"
//#include "lv_hal_indev.h"
//#include "lvgl.h"
//
//#include "ili9341.h"
//#include "xpt2046.h"
//#include "lv_drv_conf.h"
//
//#include "disp_spi.h"
//#include "tp_spi.h"


void lv_tutorial_hello_world(void);
void lv_calendar(void);

extern void CLRStartupThread(void const* argument);

void GraphicsInitialize();

// Mutex for GLOBAL_LOCK / GLOBAL_UNLOCK
portMUX_TYPE globalLockMutex = portMUX_INITIALIZER_UNLOCKED;

void receiver_task(void* pvParameter)
{
	(void)pvParameter;

	ReceiverThread(0);

	vTaskDelete(NULL);
}


//void littlevGL_Refresh(void* pvParameter)
//{
//	(void)pvParameter;
//
//	lv_init();
//	disp_spi_init();
//	ili9341_init();
//
//	//tp_spi_init();
//	//xpt2046_init();
//	lv_disp_drv_t disp;
//	lv_disp_drv_init(&disp);
//	disp.disp_flush = ili9341_flush;
//	disp.disp_fill = ili9341_fill;
//	lv_disp_drv_register(&disp);
//	lv_indev_drv_t indev;
//	lv_indev_drv_init(&indev);
//	indev.read = xpt2046_read;
//	indev.type = LV_INDEV_TYPE_POINTER;
//	lv_indev_drv_register(&indev);
//
//
//
//	// TickType_t xLastWakeTime;
//	// const TickType_t xFrequency = 10 * portTICK_PERIOD_MS;  // 2 seconds?
//	// xLastWakeTime = xTaskGetTickCount();	// Initialise the xLastWakeTime variable with the current time.
//     GraphicsInitialize();
//	while (1)
//	{
//	// vTaskDelayUntil(&xLastWakeTime, xFrequency);	// Wait for the next cycle.
//	   vTaskDelay(0);
//	   lv_task_handler();
//	}
//}

// Main task start point
void main_task(void* pvParameter)
{
	(void)pvParameter;// CLR settings to launch CLR thread
	CLR_SETTINGS clrSettings;
	(void)memset(&clrSettings, 0, sizeof(CLR_SETTINGS));

	clrSettings.MaxContextSwitches = 50;
	clrSettings.WaitForDebugger = false;
	clrSettings.EnterDebuggerLoopAfterExit = true;
	CLRStartupThread(&clrSettings);

	vTaskDelete(NULL);
}

// App_main 
// Called from Esp32 IDF start up code before scheduler starts
//
void  app_main()
{
	// Switch off logging so as not to interfere with WireProtocol over Uart0
	esp_log_level_set("*", ESP_LOG_NONE);

    ESP_ERROR_CHECK(nvs_flash_init());

	xTaskCreatePinnedToCore(&receiver_task, "ReceiverThread", 2048, NULL, 5, NULL, 1);

	// Start the main task pinned to 2nd core
	xTaskCreatePinnedToCore(&main_task, "main_task", 15000, NULL, 5, NULL, 1);

	// Start the lvl graphics loop
	// xTaskCreatePinnedToCore(&littlevGL_Refresh, "littlevGL_Refresh", 2048, NULL, 5, NULL, 1);

}

//void GraphicsInitialize()
//{
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//
//	//lv_init();
//	//disp_spi_init();
//	//ili9341_init();
//
//	////tp_spi_init();
//	////xpt2046_init();
//	//lv_disp_drv_t disp;
//	//lv_disp_drv_init(&disp);
//	//disp.disp_flush = ili9341_flush;
//	//disp.disp_fill = ili9341_fill;
//	//lv_disp_drv_register(&disp);
//	//lv_indev_drv_t indev;
//	//lv_indev_drv_init(&indev);
//	//indev.read = xpt2046_read;
//	//indev.type = LV_INDEV_TYPE_POINTER;
//	//lv_indev_drv_register(&indev);
//
//	//esp_register_freertos_tick_hook(lv_tick_task);
//	//demo_create();
//
//	lv_obj_t* btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
//	lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
//	lv_obj_set_size(btn, 100, 50);                          /*Set its size*/
//
//	lv_obj_t* label = lv_label_create(btn, NULL);          /*Add a label to the button*/
//	lv_label_set_text(label, "Button");                     /*Set the labels text*/
//
//	//lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_action);/*Assign a callback to the button*/
//	/*lv_res_t btn_action(lv_obj_t * btn)
//	{
//		printf("Clicked\n");
//		return LV_RES_OK;
//	}*/
//
//	lv_calendar();
//	lv_tutorial_hello_world();
//}
//
//void lv_tutorial_hello_world(void)
//
//{
//	/*Create a Label on the currently active screen*/
//	lv_obj_t* label1 = lv_label_create(lv_scr_act(), NULL);
//	lv_label_set_text(label1, "Hello AGAIN and AGAIN!");
//	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
//}
//
//void lv_calendar(void)
//{
//	/*Create a Calendar object*/
//	lv_obj_t* calendar = lv_calendar_create(lv_scr_act(), NULL);
//	lv_obj_set_size(calendar, 240, 220);
//	lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
//
//	/*Create a style for the current week*/
//	static lv_style_t style_week_box;
//	lv_style_copy(&style_week_box, &lv_style_plain);
//	style_week_box.body.border.width = 1;
//	style_week_box.body.border.color = LV_COLOR_HEX3(0x333);
//	style_week_box.body.empty = 1;
//	style_week_box.body.radius = LV_RADIUS_CIRCLE;
//	style_week_box.body.padding.ver = 3;
//	style_week_box.body.padding.hor = 3;
//
//	/*Create a style for today*/
//	static lv_style_t style_today_box;
//	lv_style_copy(&style_today_box, &lv_style_plain);
//	style_today_box.body.border.width = 2;
//	style_today_box.body.border.color = LV_COLOR_NAVY;
//	style_today_box.body.empty = 1;
//	style_today_box.body.radius = LV_RADIUS_CIRCLE;
//	style_today_box.body.padding.ver = 3;
//	style_today_box.body.padding.hor = 3;
//	style_today_box.text.color = LV_COLOR_BLUE;
//
//	/*Create a style for the highlighted days*/
//	static lv_style_t style_highlighted_day;
//	lv_style_copy(&style_highlighted_day, &lv_style_plain);
//	style_highlighted_day.body.border.width = 2;
//	style_highlighted_day.body.border.color = LV_COLOR_NAVY;
//	style_highlighted_day.body.empty = 1;
//	style_highlighted_day.body.radius = LV_RADIUS_CIRCLE;
//	style_highlighted_day.body.padding.ver = 3;
//	style_highlighted_day.body.padding.hor = 3;
//	style_highlighted_day.text.color = LV_COLOR_BLUE;
//
//	/*Apply the styles*/
//	lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_WEEK_BOX, &style_week_box);
//	lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_TODAY_BOX, &style_today_box);
//	lv_calendar_set_style(calendar, LV_CALENDAR_STYLE_HIGHLIGHTED_DAYS, &style_highlighted_day);
//
//
//	/*Set the today*/
//	lv_calendar_date_t today;
//	today.year = 2018;
//	today.month = 10;
//	today.day = 23;
//
//	lv_calendar_set_today_date(calendar, &today);
//	lv_calendar_set_showed_date(calendar, &today);
//
//	/*Highlight some days*/
//	static lv_calendar_date_t highlihted_days[3];       /*Only it's pointer will be saved so should be static*/
//	highlihted_days[0].year = 2018;
//	highlihted_days[0].month = 10;
//	highlihted_days[0].day = 6;
//
//	highlihted_days[1].year = 2018;
//	highlihted_days[1].month = 10;
//	highlihted_days[1].day = 11;
//
//	highlihted_days[2].year = 2018;
//	highlihted_days[2].month = 11;
//	highlihted_days[2].day = 22;
//
//	lv_calendar_set_highlighted_dates(calendar, highlihted_days, 3);
//}
