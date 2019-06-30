//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.

#ifndef _DISPLAY_H_
#define _DISPLAY_H_ 1

#include "nanoCLR_Types.h"

typedef enum
{
	PORTRAIT,
	PORTRAIT180,
	LANDSCAPE,
	LANDSCAPE180
} SCREEN_ORIENTATION;

enum PixelFormat : CLR_UINT8 {
	TEMPLATE_FORMAT_RGB888 = 0,         // Pixel format chosen is RGB888 : 24 bpp
	TEMPLATE_FORMAT_RBG565 = 2          // Pixel format chosen is RGB565 : 16 bpp
};

struct Display
{
public:
	static CLR_UINT32 Cursor;
	static SCREEN_ORIENTATION Orientation;

	static bool SetWindow(CLR_UINT16 x1, CLR_UINT16 y1, CLR_UINT16 x2, CLR_UINT16 y2);
	static bool Initialize();
	static bool Uninitialize();
	static void PowerSave(bool On);
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
	static CLR_INT32 GetOrientation();
	static CLR_UINT32 ConvertColor(CLR_UINT32 color);

};
#endif 