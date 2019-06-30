//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "nanoCLR_Types.h"
#include "nanoCLR_Runtime.h"

#include "Graphics.h"
#include "ink_decl.h"

class InkDriver
{
public:
    bool             m_initialized;
    HAL_COMPLETION   m_InkCompletion;
    CLR_UINT32           m_index;
    InkRegionInfo    m_InkRegionInfo;
    bool             m_InkingActive;
    CLR_UINT16           m_lastx;
    CLR_UINT16           m_lasty;
    PAL_GFX_Bitmap   m_ScreenBmp;

    InkDriver()
    {
        m_initialized = false;
    }
    
    void DrawInk(void *arg);    
    HRESULT Initialize();
    HRESULT Uninitialize();
    HRESULT SetRegion(InkRegionInfo* inkRegionInfo);
    HRESULT ResetRegion();

    static void InkContinuationRoutine(void *arg);

};

extern InkDriver g_InkDriver;


//
// Copyright (c) 2019 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//


#ifndef _DRIVERS_INK_DECL_H_
#define _DRIVERS_INK_DECL_H_ 1

#include "nanoCLR_types.h"
#include <Graphics.h>

struct InkRegionInfo
{
	CLR_UINT16          X1, X2, Y1, Y2; /// Inking region in screen co-ordinates.
	CLR_UINT16          BorderWidth; /// border width for inking region
	PAL_GFX_Bitmap* Bmp; /// This field may be NULL, if not NULL it must be valid pinned memory.
						 /// Other criterion is this bitmap must have size (X2-X1) x (Y2-Y1).
	GFX_Pen         Pen;
};

HRESULT Ink_Initialize();
HRESULT Ink_Uninitialize();
HRESULT Ink_SetRegion(InkRegionInfo* inkRegionInfo);
HRESULT Ink_ResetRegion();


#endif // _DRIVERS_INK_DECL_H_

