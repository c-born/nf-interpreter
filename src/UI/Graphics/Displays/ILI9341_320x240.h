//
// Copyright (c) 2017 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _ILI9341_H_
#define _ILI9341_H_ 1

#include "Graphics.h"
#include "Display.h"


//// LCD Size Defines
//#define LCD_HW_HEIGHT 480  // Portrait height
//#define LCD_HW_WIDTH  800  // Portrait width

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#define LCD_SCREEN_WIDTH    GetWidth()
#define LCD_SCREEN_HEIGHT   GetHeight()
#define LCD_SCREEN_BPP      GetBitsPerPixel()
#define LCD_SCREEN_ORIENTATION GetOrientation()

#define LCD_SCREEN_PIXELS_PER_WORD      (32/LCD_SCREEN_BPP)
#define LCD_SCREEN_WIDTH_IN_WORDS       ((LCD_SCREEN_WIDTH + LCD_SCREEN_PIXELS_PER_WORD - 1) / LCD_SCREEN_PIXELS_PER_WORD)
#define LCD_SCREEN_SIZE_IN_WORDS        (LCD_SCREEN_WIDTH_IN_WORDS * LCD_SCREEN_HEIGHT)
#define LCD_SCREEN_SIZE_IN_BYTES        (LCD_SCREEN_SIZE_IN_WORDS * 4)

#define LCD_NO_PIXEL_CLOCK_DIVIDER      0

#define LCD_ORIENTATION	   		  LANDSCAPE
#define SCREEN_SIZE_LONGER_SIDE   800        // The maximum resolution of longer longer side of physical LCD
#define SCREEN_SIZE_SHORTER_SIDE  480       // The maximum resolution of  shorter longer side of physical LCD

#pragma GCC diagnostic pop

#endif  // _ILI9341_H_


