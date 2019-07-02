//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_ 1

#include "nanoCLR_Types.h"
#include "nanoCLR_Interop.h"
#include "nanoCLR_Runtime.h"
#include "nanoCLR_Platformdef.h"
#include "nanohal.h"
#include "Font.h"
#include "GraphicsMemoryHeap.h"

struct CLR_GFX_Bitmap;
struct CLR_GFX_Font;

#define __min(a,b) (((a) < (b)) ? (a) : (b))
#define abs(a) (((a) < 0) ? -(a) : (a))

struct GFX_Rect
{
	int left;
	int top;
	int right;
	int bottom;

	int Width() const { return right - left + 1; }
	int Height() const { return bottom - top + 1; }
};
struct GFX_Brush
{
	// GFX_Brush is a structure to capture all information needed to perform a fill. 
	// Note:
	// To create a solid brush, make gradientStartColor == gradientEndColor
	// To create a empty (no fill) brush, make opacity = c_ColorTransparent
	// To create a linear gradient brush, fill in the start and end information

	CLR_UINT32 gradientStartColor;
	int    gradientStartX;
	int    gradientStartY;
	CLR_UINT32 gradientEndColor;
	int    gradientEndX;
	int    gradientEndY;
	CLR_UINT16 opacity;
};
struct GFX_Pen
{
	CLR_UINT32 color;
	int thickness;
};

// This is the callback signature for Graphics_SetPixelsHelper(). This callback will be called once for each pixel in the area specified.
// The parameters are as follow:
// 1) int -- the x coordinates of the current pixel
// 2) int -- the y coordinates of the current pixel
// 3) CLR_UINT32 -- flags that communicate the status of the SetPixels operation, more specifically --
//      c_SetPixels_First           - This is the first time the callback is called, can be used to
//                                    conditionally perform any initialization work
//      c_SetPixels_NewRow          - This is the first pixel of a new row (i.e. new y value)
//      c_SetPixels_PixelHidden     - This pixel is outside of the clipping area. Note that if
//                                    c_SetPixelsConfig_NoClipChecks is set, this bit will never be
//                                    set.
// 4) CLR_UINT16& -- the return value for opacity. Note that you can set this to c_OpacityTransparent if
//               you want to leave the pixel unchanged.
// 5) void* -- this is the custom parameter that was passed into Graphics_SetPixelsHelper(), and it is
//             persisted between each callback call
// Return Value -- The color of the pixel
typedef CLR_UINT32(*GFX_SetPixelsCallback) (int, int, CLR_UINT32, CLR_UINT16&, void*);

// Graphics_SetPixelsHelper is designed to allow the caller to fill an area of a bitmap without incurring unnecessary cost
// of calculating the x, y position for each pixel.
// The parameters are as follow:
// 1) bitmap -- the target bitmap
// 2) rect -- the area on the bitmap to iterate through
// 3) config -- configuration for how the callbacks will be made, more specifically:
//      c_SetPixelsConfig_NoClip        - No clipping will be done, each pixel in the rect area specified will received 
//                                        a callback once in order.
//      c_SetPixelsConfig_Clip          - Clipping will be done against bitmap.clipping, and each pixel in the visible area 
//                                        will receive a callback once in order.
//      c_SetPixelsConfig_NoClipChecks  - By default, when c_SetPixelsConfig_NoClip is set, each pixel is passed through
//                                        a series of test to determine if the pixel is visible prior to the callback, and
//                                        the result is reflected in the c_SetPixels_PixelHidden flag. If those check are
//                                        unneccessary, this configuration option will save some time.
//      c_SetPixelsConfig_ReverseY      - The default order of the callback is increasing x, increasing y (top to bottom,
//                                        and within each row, left to right). Setting c_SetPixelsConfig_ReverseY will change
//                                        the order to be increasing x, decreasing y (bottom to top, and within each row, 
//                                        left to right).
// 4) param -- a custom pointer that's passed into each callback.
void Graphics_SetPixelsHelper(const PAL_GFX_Bitmap& bitmap, const GFX_Rect& rect, CLR_UINT32 config, GFX_SetPixelsCallback callback, void* param);

 struct PAL_GFX_Bitmap
{
	int width;
	int height;
	CLR_UINT32* data;
	GFX_Rect clipping;
	CLR_UINT32 transparentColor;

	static const CLR_UINT32 c_InvalidColor = 0xFF000000;
	static const CLR_UINT16 c_OpacityTransparent = 0;
	static const CLR_UINT16 c_OpacityOpaque = 256;
	static const CLR_UINT32 c_SetPixels_None = 0x00000000;
	static const CLR_UINT32 c_SetPixels_First = 0x00000001;
	static const CLR_UINT32 c_SetPixels_NewRow = 0x00000002;
	static const CLR_UINT32 c_SetPixels_PixelHidden = 0x00000004;
	static const CLR_UINT32 c_SetPixelsConfig_NoClip = 0x00000000;
	static const CLR_UINT32 c_SetPixelsConfig_Clip = 0x00000001;
	static const CLR_UINT32 c_SetPixelsConfig_NoClipChecks = 0x00000002;
	static const CLR_UINT32 c_SetPixelsConfig_ReverseY = 0x00000004;
};
 struct CLR_GFX_BitmapDescription
{
	// !!!!WARNING!!!!
	// These fields should correspond to CLR_GFX_BitmapDescription in GenerateResource.cs
	// and should be 4-byte aligned in size. When these fields are changed, the version number 
	// of the tinyresource file should be incremented, the tinyfnts should be updated (buildhelper -convertfont ...)
	// and the MMP should also be updated as well.
	CLR_UINT32 m_width;
	CLR_UINT32 m_height;
	CLR_UINT16 m_flags;
	CLR_UINT8  m_bitsPerPixel;
	CLR_UINT8  m_type;

	static const CLR_UINT16 c_ReadOnly = 0x0001;
	static const CLR_UINT16 c_Compressed = 0x0002;
	
	static const CLR_UINT8 c_CompressedRun = 0x80;
	static const CLR_UINT8 c_CompressedRunSet = 0x40;
	static const CLR_UINT8 c_CompressedRunLengthMask = 0x3f;
	static const CLR_UINT8 c_UncompressedRunLength = 7;
	static const CLR_UINT8 c_CompressedRunOffset = c_UncompressedRunLength + 1;
	
	//static // Note that these type definitions has to match the ones defined in Bitmap.BitmapImageType enum defined in Graphics.cs
	static const CLR_UINT8 c_TypeTinyCLRBitmap = 0;
	static const CLR_UINT8 c_TypeGif = 1;
	static const CLR_UINT8 c_TypeJpeg = 2;
	static const CLR_UINT8 c_TypeBmp = 3; // The windows .bmp format

	// When m_bitsPerPixel == c_NativeBpp it means that the data in this bitmap is in the native PAL graphics 
	// format, the exact bit depth and format is something the CLR is abstracted away from. 
	static const int c_NativeBpp = 0;

	static const CLR_INT32 c_MaxWidth = 524287;  // 0x7ffff;
	static const CLR_INT32 c_MaxHeight = 65535;   // 0x0ffff;

	bool BitmapDescription_Initialize(int width, int height, int bitsPerPixel);

	int GetTotalSize() const;
	int GetWidthInWords() const;
};
 struct CLR_GFX_Bitmap
{
	CLR_GFX_BitmapDescription m_bm;         // Initialized by the caller!
	PAL_GFX_Bitmap            m_palBitmap;

	static const int FIELD__m_bitmap = 1;

	// These have to be kept in sync with the Microsft.SPOT.Bitmap.DT_ flags
	static const CLR_UINT32 c_DrawText_WordWrap = 0x00000001;
	// Note - 0x00000002 is used for Alignment (look below)
	static const CLR_UINT32 c_DrawText_TruncateAtBottom = 0x00000004;
	// Note - 0x00000008 is used for Trimming (look below)
	static const CLR_UINT32 c_DrawText_IgnoreHeight = 0x00000010;

	static const CLR_UINT32 c_DrawText_AlignmentLeft = 0x00000000;
	static const CLR_UINT32 c_DrawText_AlignmentCenter = 0x00000002;
	static const CLR_UINT32 c_DrawText_AlignmentRight = 0x00000020;
	static const CLR_UINT32 c_DrawText_AlignmentUnused = 0x00000022;
	static const CLR_UINT32 c_DrawText_AlignmentMask = 0x00000022;

	static const CLR_UINT32 c_DrawText_TrimmingNone = 0x00000000;
	static const CLR_UINT32 c_DrawText_TrimmingWordEllipsis = 0x00000008;
	static const CLR_UINT32 c_DrawText_TrimmingCharacterEllipsis = 0x00000040;
	static const CLR_UINT32 c_DrawText_TrimmingUnused = 0x00000048;
	static const CLR_UINT32 c_DrawText_TrimmingMask = 0x00000048;

	HRESULT CreateInstance(CLR_RT_HeapBlock& ref, const CLR_GFX_BitmapDescription& bm);
	HRESULT CreateInstance(CLR_RT_HeapBlock& ref, const CLR_UINT8* data, CLR_UINT32 size, CLR_RT_Assembly* assm);
	HRESULT CreateInstance(CLR_RT_HeapBlock& ref, const CLR_UINT8* data, const CLR_UINT32 size, const CLR_UINT8 type);

	HRESULT CreateInstanceJpeg(CLR_RT_HeapBlock& ref, const CLR_UINT8* data, const CLR_UINT32 size);
	HRESULT CreateInstanceGif(CLR_RT_HeapBlock& ref, const CLR_UINT8* data, const CLR_UINT32 size);
	HRESULT CreateInstanceBmp(CLR_RT_HeapBlock& ref, const CLR_UINT8* data, const CLR_UINT32 size);

	HRESULT GetInstanceFromGraphicsHeapBlock(const CLR_RT_HeapBlock& ref, CLR_GFX_Bitmap*& bitmap);
	HRESULT DeleteInstance(CLR_RT_HeapBlock& ref);

	CLR_UINT32 CreateInstanceJpegHelper(int x, int y, CLR_UINT32 flags, CLR_UINT16& opacity, void* param);
	CLR_UINT32 ConvertToNative1BppHelper(CLR_UINT32 flags, CLR_UINT16& opacity, void* param);
	CLR_UINT32 ConvertToNative16BppHelper(CLR_UINT32 flags, CLR_UINT16& opacity, void* param);

	void Bitmap_Initialize();
	void Clear();
	void SetClipping(GFX_Rect& rc);
	CLR_UINT32 GetPixel(int xPos, int yPos) const;
	void       SetPixel(int xPos, int yPos, CLR_UINT32 color);
	void DrawLine(const GFX_Pen& pen, int x0, int y0, int x1, int y1);
	void DrawRectangle(const GFX_Pen& pen, const GFX_Brush& brush, const GFX_Rect& rectangle);
	void DrawRoundedRectangle(const GFX_Pen& pen, const GFX_Brush& brush, const GFX_Rect& rectangle, int radiusX, int radiusY);
	void DrawEllipse(const GFX_Pen& pen, const GFX_Brush& brush, int x, int y, int radiusX, int radiusY);
	void DrawImage(const GFX_Rect& dst, const CLR_GFX_Bitmap& bitmapSrc, const GFX_Rect& src, CLR_UINT16 opacity);
	void RotateImage(int angle, const GFX_Rect& dst, const CLR_GFX_Bitmap& bitmapSrc, const GFX_Rect& src, CLR_UINT16 opacity);
	
	void DrawText(LPCSTR str, CLR_GFX_Font& font, CLR_UINT32 color, int x, int y);
	void HRESULT DrawTextInRect(LPCSTR& szText, int& xRelStart, int& yRelStart, int& renderWidth, int& renderHeight, CLR_GFX_Bitmap* bm, int x, int y, int width, int height, CLR_UINT32 dtFlags, CLR_UINT32 color, CLR_GFX_Font* font);
	void Screen_Flush(CLR_GFX_Bitmap& bitmap, CLR_UINT16 x, CLR_UINT16 y, CLR_UINT16 width, CLR_UINT16 height);
	void SetPixelsHelper(const GFX_Rect& rect, CLR_UINT32 config, GFX_SetPixelsCallback callback, void* param);
	void Relocate();
	void RelocationHandler(CLR_RT_HeapBlock_BinaryBlob* ptr);
private:
	void Decompress(const CLR_UINT8* data, const CLR_GFX_BitmapDescription* bm, CLR_UINT32 size);
	void Decompress(const CLR_UINT8* data, CLR_UINT32 size);
	void ConvertToNative(const CLR_GFX_BitmapDescription* bmSrc, CLR_UINT32* dataSrc);

	PROHIBIT_ALL_CONSTRUCTORS(CLR_GFX_Bitmap);
};

struct Graphics_Driver
{
public:
	static int GetSize(int width, int height);
	static int GetWidthInWords(int width);
	static void Clear(const PAL_GFX_Bitmap& bitmap);
	static CLR_UINT32 GetPixel(const PAL_GFX_Bitmap& bitmap, int x, int y);
	static void SetPixel(const PAL_GFX_Bitmap& bitmap, int x, int y, CLR_UINT32 color);
	static void DrawLine(const PAL_GFX_Bitmap& bitmap, const GFX_Pen& pen, int x0, int y0, int x1, int y1);
	static void DrawLineRaw(const PAL_GFX_Bitmap& bitmap, const GFX_Pen& pen, int x0, int y0, int x1, int y1);
	static void DrawRectangle(const PAL_GFX_Bitmap& bitmap, const GFX_Pen& pen, const GFX_Brush& brush, const GFX_Rect& rectangle);
	static void DrawRoundedRectangle(const PAL_GFX_Bitmap& bitmap, const GFX_Pen& pen, const GFX_Rect& rectangle, int radiusX, int radiusY);
	static void DrawEllipse(const PAL_GFX_Bitmap& bitmap, const GFX_Pen& pen, const GFX_Brush& brush, int x, int y, int radiusX, int radiusY);
	static void DrawImage(const PAL_GFX_Bitmap& bitmapDst, const GFX_Rect& dst, const PAL_GFX_Bitmap& bitmapSrc, const GFX_Rect& src, CLR_UINT16 opacity);
	static void SetPixelsHelper(const PAL_GFX_Bitmap& bitmap, const GFX_Rect& rect, CLR_UINT32 config, GFX_SetPixelsCallback callback, void* param);
	static void RotateImage(CLR_INT16 degree, const PAL_GFX_Bitmap& dst, const GFX_Rect& dstRect, const PAL_GFX_Bitmap& src, const GFX_Rect& srcRect, CLR_UINT16 opacity);

	static const CLR_UINT32 c_MaxSize = 2097152; // 2MB
	static CLR_UINT32 GetPixelNative(const PAL_GFX_Bitmap& bitmap, int x, int y);
	static void SetPixelNative(const PAL_GFX_Bitmap& bitmap, int x, int y, CLR_UINT32 color);
	static void SetThickPixel(const PAL_GFX_Bitmap& bitmap, int x, int y, GFX_Pen& pen);
	static void DrawLineNative(const PAL_GFX_Bitmap& bitmap, GFX_Pen& pen, int x0, int y0, int x1, int y1);
	static void DrawRectangleNative(const PAL_GFX_Bitmap& bitmap, GFX_Pen& pen, GFX_Brush& brush, const GFX_Rect& rectangle);
	static void DrawRoundedRectangleNative(const PAL_GFX_Bitmap& bitmap, GFX_Pen& pen, const GFX_Rect& rectangle, int radiusX, int radiusY);
	static void DrawEllipseNative(const PAL_GFX_Bitmap& bitmap, GFX_Pen& pen, GFX_Brush& brush, int x, int y, int radiusX, int radiusY);
	static CLR_UINT32* ComputePosition(const PAL_GFX_Bitmap& bitmap, int xPos, int yPos, CLR_UINT32& mask, CLR_UINT32& shift);
	static bool IsPixelVisible(const GFX_Rect& clipping, int x, int y);
	static bool ClipToVisible(const PAL_GFX_Bitmap& target, int& x, int& y, int& width, int& height, const PAL_GFX_Bitmap* pSrc, int& xSrc, int& ySrc);
	static void DrawBresLineNative(const PAL_GFX_Bitmap& bitmap, int x0, int y0, int x1, int y1, GFX_Pen& pen);
	static CLR_UINT32 NativeColorInterpolate(CLR_UINT32 colorTo, CLR_UINT32 colorFrom, CLR_UINT16 scalar);
	__inline static CLR_UINT8 NativeColorRValue(CLR_UINT32 color) { return (color & 0xF800) >> 11; }
	__inline static CLR_UINT8 NativeColorGValue(CLR_UINT32 color) { return (color & 0x07E0) >> 5; }
	__inline static CLR_UINT8 NativeColorBValue(CLR_UINT32 color) { return  color & 0x1F; }
	__inline static CLR_UINT32 NativeColorFromRGB(CLR_UINT8 r, CLR_UINT8 g, CLR_UINT8 b)
	{
		ASSERT((b <= 0x1F) && (g <= 0x3F) && (r <= 0x1F));
		return (r << 11) | (g << 5) | b;
	}
	__inline static CLR_UINT8 ColorRValue(CLR_UINT32 color) { return  color & 0x0000FF; }
	__inline static CLR_UINT8 ColorGValue(CLR_UINT32 color) { return (color & 0x00FF00) >> 8; }
	__inline static CLR_UINT8 ColorBValue(CLR_UINT32 color) { return (color & 0xFF0000) >> 16; }
	__inline static CLR_UINT32 ColorFromRGB(CLR_UINT8 r, CLR_UINT8 g, CLR_UINT8 b) { return (b << 16) | (g << 8) | r; }
	__inline static CLR_UINT32 ConvertNativeToColor(CLR_UINT32 nativeColor)
	{
		int r = NativeColorRValue(nativeColor) << 3; if ((r & 0x8) != 0) r |= 0x7;   // Copy LSB
		int g = NativeColorGValue(nativeColor) << 2; if ((g & 0x4) != 0) g |= 0x3;   // Copy LSB
		int b = NativeColorBValue(nativeColor) << 3; if ((b & 0x8) != 0) b |= 0x7;   // Copy LSB
		return ColorFromRGB(r, g, b);
	}
	__inline static CLR_UINT32 ConvertColorToNative(CLR_UINT32 color)
	{
		return NativeColorFromRGB(ColorRValue(color) >> 3, ColorGValue(color) >> 2, ColorBValue(color) >> 3);
	}
	__inline static GFX_Pen ConvertPenToNative(const GFX_Pen& pen)
	{
		GFX_Pen nativePen;
		nativePen.thickness = pen.thickness;
		nativePen.color = ConvertColorToNative(pen.color);
		return nativePen;
	}
	__inline static GFX_Brush ConvertBrushToNative(const GFX_Brush& brush)
	{
		GFX_Brush nativeBrush;
		nativeBrush.gradientStartX = brush.gradientStartX;
		nativeBrush.gradientStartY = brush.gradientStartY;
		nativeBrush.gradientStartColor = ConvertColorToNative(brush.gradientStartColor);
		nativeBrush.gradientEndX = brush.gradientEndX;
		nativeBrush.gradientEndY = brush.gradientEndY;
		nativeBrush.gradientEndColor = ConvertColorToNative(brush.gradientEndColor);
		nativeBrush.opacity = brush.opacity;
		return nativeBrush;
	}
	typedef void(*EllipseCallback) (const PAL_GFX_Bitmap&, int, int, void*);
	static void EllipseAlgorithm(const PAL_GFX_Bitmap& bitmap, int radiusX, int radiusY, void* params, EllipseCallback ellipseCallback);
	static void Draw4PointsEllipse(const PAL_GFX_Bitmap& bitmap, int offsetX, int offsetY, void* params);
	static void Draw4PointsRoundedRect(const PAL_GFX_Bitmap& bitmap, int offsetX, int offsetY, void* params);
};

// The PAL Graphics API uses the 24bit BGR color space, the one that's used for TinyCore and
// CLR. It is the responsibility of whoever is implementing the PAL to deal with color conversion
// as neither CLR or TinyCore understands any color space other than this default one.
// For opacity, the valid value are from 0 (c_OpacityTransparent) to 256 (c_OpacityOpaque).

#endif  // _GRAPHICS_H_
