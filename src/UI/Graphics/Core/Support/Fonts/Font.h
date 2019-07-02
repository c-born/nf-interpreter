//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _FONT_H_
#define _FONT_H_

#pragma message "IN FONT - BEFORE: Graphics.h "
#include "Graphics.h"
#pragma message "IN FONT - AFTER:  Graphics.h "

struct CLR_GFX_FontMetrics
{
	CLR_UINT16 m_height;
	CLR_INT16  m_offset; // The bitmap could be actually smaller than the logical font height.

	CLR_INT16  m_ascent;
	CLR_INT16  m_descent;

	CLR_INT16  m_internalLeading;
	CLR_INT16  m_externalLeading;

	CLR_INT16  m_aveCharWidth;
	CLR_INT16  m_maxCharWidth;
};

struct CLR_GFX_FontMetricsExtended : public CLR_GFX_FontMetrics
{
	int m_offsetX;
	int m_offsetY;
	int m_marginLeft;
	int m_marginRight;
};

struct CLR_GFX_FontDescription
{
	static const CLR_UINT16 c_Bold = 0x0001;
	static const CLR_UINT16 c_Italic = 0x0002;
	static const CLR_UINT16 c_Underline = 0x0004;
	static const CLR_UINT16 c_FontEx = 0x0008;
	static const CLR_UINT16 c_AntiAliasMask = 0x00F0;
	static const CLR_UINT16 c_AntiAliasShift = 4;

	CLR_GFX_FontMetrics m_metrics;
	CLR_UINT16          m_ranges;
	CLR_UINT16          m_characters;
	CLR_UINT16          m_flags;
	CLR_UINT16          m_pad;

	CLR_UINT32 GetRangeSize() const;
	CLR_UINT32 GetCharacterSize() const;
	CLR_UINT32 GetCharacterExSize() const;
	CLR_UINT32 GetRangeExSize() const;
};

struct CLR_GFX_FontDescriptionEx
{
	CLR_UINT32 m_antiAliasSize;

	CLR_UINT32 GetAntiAliasSize() const;
};

struct CLR_GFX_FontCharacterRange
{
	CLR_UINT32 m_indexOfFirstFontCharacter;

	CLR_UINT16 m_firstChar;
	CLR_UINT16 m_lastChar;

	CLR_UINT32 m_rangeOffset; // the x-offset into the bitmap for this range.
};

struct CLR_GFX_FontCharacterRangeEx
{
	CLR_UINT32 m_offsetAntiAlias;
};

struct CLR_GFX_FontCharacter
{
	CLR_UINT16 m_offset;
	CLR_INT8   m_marginLeft;
	CLR_INT8   m_marginRight;
};

struct CLR_GFX_FontCharacterEx
{
	static const CLR_UINT16 c_offsetNoAntiAlias = 0xFFFF;

	CLR_UINT16 m_offsetAntiAlias;
};

struct CLR_GFX_FontCharacterInfo
{
	bool       isValid;
	CLR_INT8   marginLeft;
	CLR_INT8   marginRight;
	CLR_UINT32 offset;
	CLR_UINT16 innerWidth;
	CLR_UINT16 width;
	CLR_UINT16 height;
	CLR_UINT8* antiAlias;
	CLR_UINT8  iAntiAlias;
};

struct CLR_GFX_Font
{
	static const int FIELD__m_font = 1;
	static const CLR_INT32 c_DefaultKerning = 1024;		// Must keep in sync with Microsoft.SPOT.Font.DefaultKerning
	static const CLR_UINT16 c_UnicodeReplacementCharacter = 0xFFFD;

	CLR_GFX_FontDescription       m_font;
	CLR_GFX_FontCharacterRange* m_ranges;
	CLR_GFX_FontCharacter*		m_chars;
	CLR_GFX_Bitmap				m_bitmap;
	CLR_GFX_FontCharacterInfo     m_defaultChar;
	CLR_GFX_FontDescriptionEx     m_fontEx;
	CLR_GFX_FontCharacterRangeEx* m_rangesEx;
	CLR_GFX_FontCharacterEx* m_charsEx;
	CLR_UINT8* m_antiAliasingData;

	static HRESULT CreateInstance(CLR_RT_HeapBlock& ref, const CLR_UINT8* data, CLR_RT_Assembly* assm);
	void Font_Initialize();
	int StringOut(LPCSTR str, int maxChars, CLR_INT32 kerning, CLR_GFX_Bitmap* bm, int xPos, int yPos, CLR_UINT32 color);
	void CountCharactersInWidth(LPCSTR str, int maxChars, int width, int& totWidth, bool fWordWrap, LPCSTR& strNext, int& numChars);
	void DrawChar(CLR_GFX_Bitmap* bitmap, CLR_GFX_FontCharacterInfo& chr, int xDst, int yDst, CLR_UINT32 color);
	static CLR_UINT32 DrawCharHelper(int x, int y, CLR_UINT32 flags, CLR_UINT16& opacity, void* param);
	void GetCharInfo(CLR_UINT16 c, CLR_GFX_FontCharacterInfo& chrEx);
	void Relocate();
	static void RelocationHandler(CLR_RT_HeapBlock_BinaryBlob* ptr);

	PROHIBIT_ALL_CONSTRUCTORS(CLR_GFX_Font);
};

struct DrawCharHelperParam
{
	int originalDstX;
	int originalDstY;
	int srcX;
	int srcY;
	CLR_UINT32* srcFirstWord;
	CLR_UINT32  srcFirstPixelMask;
	CLR_UINT32  srcCurPixelMask;
	CLR_UINT32* srcCurWord;
	CLR_UINT32  srcWidthInWords;
	CLR_UINT32 color;
	CLR_UINT8* antiAlias;
	CLR_UINT8   iAntiAlias;
	CLR_UINT8   antiAliasStep;
	CLR_UINT8   antiAliasShift;
	CLR_UINT8   antiAliasShiftFirstPixel;
	CLR_UINT32  antiAliasMask;
	CLR_UINT32  antiAliasMaskFirstPixel;
};

int GetCharInfoCmp(const void* c, const void* r);

#endif


