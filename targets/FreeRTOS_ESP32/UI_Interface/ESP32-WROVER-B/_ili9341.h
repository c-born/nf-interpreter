
#ifndef ILI9341_H
#define ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

#define ILI9341_DC   21
#define ILI9341_RST  18
#define ILI9341_BCKL 5

#include "lvgl.h"

	void ili9341_init();
	void ili9341_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
	void ili9341_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t* color_map);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ILI9341_H*/
