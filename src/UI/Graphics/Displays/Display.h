//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.

#ifndef _DISPLAY_H_
#define _DISPLAY_H_ 1

#include "nanoCLR_Types.h"

enum DisplayOrientation : CLR_INT16
{
	PORTRAIT,
	PORTRAIT180,
	LANDSCAPE,
	LANDSCAPE180
} 
enum PixelFormat : CLR_UINT8 {
	FORMAT_RGB888 = 0,         // Pixel format chosen is RGB888 : 24 bpp
	FORMAT_RBG565 = 2,         // Pixel format chosen is RGB565 : 16 bpp
};
struct DisplayAttributes
{
	static CLR_UINT32 Cursor;
	static DisplayOrientation Orientation;
	static PowerSaveState PowerSave;
	static CLR_INT16 Height;
	static CLR_INT16 Width;
	static CLR_INT16 BitsPerPixel;
};
enum PowerSaveState : CLR_UINT8 {
	NORMAL = 0,
	SLEEP = 0,
	STANDBY = 1
};

#define LCD_COLOUR_RGB(R,G,B) ((UINT16)((((R) / 8) << 11) + (((G) / 4) << 5) + ((B) / 8)))
enum LCD_COLOUR : UINT16
{
	DARK_BLUE = LCD_COLOUR_RGB(0, 0, 152),
	BRIGHT_BLUE = LCD_COLOUR_RGB(222, 219, 255),
	BLUE = LCD_COLOUR_RGB(0, 0, 255),
	CYAN = LCD_COLOUR_RGB(0, 255, 255),
	BRIGHT_YELLOW = LCD_COLOUR_RGB(255, 220, 120),
	YELLOW = LCD_COLOUR_RGB(255, 255, 0),
	ORANGE = LCD_COLOUR_RGB(255, 152, 96),
	BRIGHT_RED = LCD_COLOUR_RGB(255, 28, 24),
	RED = LCD_COLOUR_RGB(255, 0, 0),
	DARK_RED = LCD_COLOUR_RGB(152, 0, 0),
	MAGENTA = LCD_COLOUR_RGB(255, 0, 255),
	BRIGHT_GREEN = LCD_COLOUR_RGB(152, 255, 152),
	GREEN = LCD_COLOUR_RGB(0, 255, 0),
	DARK_GREEN = LCD_COLOUR_RGB(0, 128, 0),
	BRIGHT_GREY = LCD_COLOUR_RGB(48, 48, 48),
	LIGHT_GREY = LCD_COLOUR_RGB(120, 120, 120),
	GREY = LCD_COLOUR_RGB(24, 24, 24),
	WHITE = LCD_COLOUR_RGB(255, 255, 255),
	BLACK = LCD_COLOUR_RGB(0, 0, 0)
};

struct Display
{
public:
	static bool SetWindow(CLR_UINT16 x1, CLR_UINT16 y1, CLR_UINT16 x2, CLR_UINT16 y2);
	static bool Initialize();
	static bool Uninitialize();
	static void PowerSave(PowerSaveState powerState);
	static void Clear();
	static void BitBltEx(int x, int y, int width, int height, CLR_UINT32 data[]);
	static void BitBlt(int width, int height, int widthInWords, CLR_UINT32 data[]);
	static void WriteChar(unsigned char c, int row, int col);
	static void WriteFormattedChar(unsigned char c);
	static CLR_UINT32 PixelsPerWord();
	static CLR_UINT32 TextRows();
	static CLR_UINT32 TextColumns();
	static CLR_UINT32 WidthInWords();
	static CLR_UINT32 SizeInWords();
	static CLR_UINT32 SizeInBytes();
	static CLR_INT32 GetWidth();
	static CLR_INT32 GetHeight();
	static CLR_INT32 GetBitsPerPixel();
	static CLR_UINT32 GetPixelClockDivider();
	static CLR_UINT32 ConvertColor(CLR_UINT32 color);
	static CLR_INT32 GetOrientation();
	static bool Display::ChangeOrientation(DisplayOrientation newOrientation);

};
#endif 