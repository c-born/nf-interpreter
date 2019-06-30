//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _BMP_H_
#define _BMP_H_

#include "Graphics.h"

struct  BITMAPFILEHEADER {
    CLR_UINT16 bfType;
    CLR_UINT32 bfSize;
    CLR_UINT16 bfReserved1;
    CLR_UINT16 bfReserved2;
    CLR_UINT32 bfOffBits;
} __attribute__((packed));
 struct  BITMAPINFOHEADER {
    CLR_UINT32 biSize;
    CLR_INT32  biWidth;
    CLR_INT32  biHeight;
    CLR_UINT16 biPlanes;
    CLR_UINT16 biBitCount;
    CLR_UINT32 biCompression;
    CLR_UINT32 biSizeImage;
    CLR_INT32  biXPelsPerMeter;
    CLR_INT32  biYPelsPerMeter;
    CLR_UINT32 biClrUsed;
    CLR_UINT32 biClrImportant;
 } __attribute__((packed));

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

 struct BmpOutputHelperParam
 {
	 CLR_RT_ByteArrayReader* source;
	 BmpEncodingType encodingType;
	 CLR_UINT32 srcWidthInBytes;
	 CLR_UINT8* srcRGB;
	 const CLR_UINT8* palette;
	 CLR_UINT8 paletteDepth;
 };

typedef CLR_UINT32 COLORREF;


enum BmpEncodingType
{
    BmpUnknown      = 0,
    Bmp16Bit_565    = 1,
    Bmp24Bit_RGB    = 2,
    Bmp8Bit_Indexed = 3,
    Bmp32Bit_ARGB   = 4,    
};

struct BmpDecoder
{
    int             width;
    int             height;
    BmpEncodingType encodingType;
    HRESULT BmpInitOutput ( const CLR_UINT8* src, CLR_UINT32 srcSize );
    HRESULT BmpStartOutput( CLR_GFX_Bitmap* bitmap );
    static CLR_UINT32 BmpOutputHelper(  CLR_UINT32 flags, CLR_UINT16& opacity, void* param );

private:
    CLR_RT_ByteArrayReader source;
    const CLR_UINT8* palette;
    CLR_UINT8 paletteDepth;
    bool isTopDown;
};
#endif //_BMP_H_