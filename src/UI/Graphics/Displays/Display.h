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
};
enum PixelFormat : CLR_UINT8 {
	FORMAT_RGB888 = 0,         // Pixel format chosen is RGB888 : 24 bpp
	FORMAT_RBG565 = 2,         // Pixel format chosen is RGB565 : 16 bpp
};
enum PowerSaveState : CLR_UINT8 {
	NORMAL = 0,
	SLEEP = 1
};

struct DisplayAttributes
{
	static PowerSaveState PowerSave;
	static DisplayOrientation Orientation;  //Future
	static CLR_INT16 Height;
	static CLR_INT16 Width;
	static CLR_INT16 BitsPerPixel;
	static CLR_INT16 LongerSide;  // Pixels
	static CLR_INT16 ShorterSide; // Pixels
};

#define LCD_COLOUR_RGB(R,G,B) ((CLR_UINT16)((((R) / 8) << 11) + (((G) / 4) << 5) + ((B) / 8)))

struct Display
{
	static CLR_UINT32* g_FrameBuffer;         // = NULL
	static CLR_UINT32 g_FrameBufferSize;      // = 0;
	static bool   g_LcdInitialized;           // = false;

	static bool Initialize();
	static bool Uninitialize();
	static void Clear();
	static void DisplayBrightness(CLR_INT16 brightness);
	static void BitBltEx(int x, int y, int width, int height, CLR_UINT32 data[]);
	static void BitBlt(int width, int height, int widthInWords, CLR_UINT32 data[]);
	static void PowerSave(PowerSaveState powerState);
	static bool ChangeOrientation(DisplayOrientation newOrientation);
	static CLR_INT32 GetWidth();
	static CLR_INT32 GetHeight();
	static CLR_INT32 GetBitsPerPixel();
	static CLR_UINT32 PixelsPerWord();
	static CLR_UINT32 WidthInWords();
	static CLR_UINT32 SizeInWords();
	static CLR_UINT32 SizeInBytes();
	static CLR_UINT32 ConvertColor(CLR_UINT32 color);
	static CLR_INT32 GetOrientation();
	static bool SetWindow(CLR_UINT16 x1, CLR_UINT16 y1, CLR_UINT16 x2, CLR_UINT16 y2);
	//static CLR_UINT32*  GetFrameBuffer();
};

#endif 