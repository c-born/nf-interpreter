//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "Graphics.h"
#include "ink_driver.h"

HRESULT Ink_Initialize()
{
    return g_InkDriver.Initialize();
}

HRESULT Ink_Uninitialize()
{
    return g_InkDriver.Uninitialize();
}

HRESULT Ink_SetRegion(InkRegionInfo* inkRegionInfo)
{
    return g_InkDriver.SetRegion(inkRegionInfo);
}

HRESULT Ink_ResetRegion()
{
    return g_InkDriver.ResetRegion();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "nanoCLR_Types.h"
#include "nanoCLR_Runtime.h"

#include "ink_driver.h"
#include "Graphics.h"
#include "display_functions.h"
#include "touchpanel_decl.h"

InkDriver g_InkDriver;

//#if defined(PLATFORM_DEPENDENT__INK_COMPLETION_TIME_USEC)
//#define INK_COMPLETION_TIME_USEC PLATFORM_DEPENDENT__INK_COMPLETION_TIME_USEC
//#else
#define INK_COMPLETION_TIME_USEC 10000 // 10ms - same as default touch completion
////#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"


HRESULT InkDriver::Initialize()
{
	if (!m_initialized)
	{
		g_InkDriver.m_InkCompletion.InitializeForUserMode(InkContinuationRoutine);
		m_initialized = true;
		m_InkingActive = false;
		m_InkRegionInfo.Bmp = NULL;
		m_ScreenBmp.width = LCD_GetWidth();
		m_ScreenBmp.height = LCD_GetHeight();
		m_ScreenBmp.data = LCD_GetFrameBuffer();
		m_ScreenBmp.transparentColor = PAL_GFX_Bitmap::c_InvalidColor;
	}

	return S_OK;
}

HRESULT InkDriver::Uninitialize()
{
	if (m_initialized)
	{
		m_initialized = false;
		ResetRegion();
	}

	return S_OK;
}

HRESULT InkDriver::SetRegion(InkRegionInfo* inkRegionInfo)
{
	m_InkRegionInfo = *inkRegionInfo;

	/// Possibly validate m_InkRegionInfo data.
	m_InkingActive = true;
	m_lastx = 0xFFFF;
	m_lasty = 0xFFFF;
	m_ScreenBmp.clipping.left = m_InkRegionInfo.X1 + m_InkRegionInfo.BorderWidth;
	m_ScreenBmp.clipping.right = m_InkRegionInfo.X2 - m_InkRegionInfo.BorderWidth;
	m_ScreenBmp.clipping.top = m_InkRegionInfo.Y1 + m_InkRegionInfo.BorderWidth;
	m_ScreenBmp.clipping.bottom = m_InkRegionInfo.Y2 - m_InkRegionInfo.BorderWidth;

	if (m_InkRegionInfo.Bmp == NULL)
	{
		m_InkRegionInfo.Bmp = &m_ScreenBmp;
	}


	CLR_UINT32 flags = GetTouchPointFlags_LatestPoint | GetTouchPointFlags_UseTime | GetTouchPointFlags_UseSource;
	CLR_UINT16 source = 0;
	CLR_UINT16 x = 0;
	CLR_UINT16 y = 0;
	CLR_INT64 time = 0;

	if (TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time) == S_OK)
	{

		if (x == TouchPointLocationFlags_ContactUp) return S_OK;

		if (x == TouchPointLocationFlags_ContactDown)
		{
			TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time);
		}

		m_index = (flags >> 16);
		m_lastx = x;
		m_lasty = y;

		if (!m_InkCompletion.IsLinked()) m_InkCompletion.EnqueueDelta(INK_COMPLETION_TIME_USEC);
	}
	else return CLR_E_FAIL;

	return S_OK;
}

HRESULT InkDriver::ResetRegion()
{
	if (m_InkCompletion.IsLinked()) m_InkCompletion.Abort();

	m_InkingActive = false;
	m_InkRegionInfo.Bmp = NULL;

	return S_OK;
}

void InkDriver::InkContinuationRoutine(void* arg)
{
	g_InkDriver.DrawInk(arg);
}

void InkDriver::DrawInk(void* arg)
{
	HRESULT hr = S_OK;
	CLR_UINT32 flags = (m_index << 16) | GetTouchPointFlags_NextPoint | GetTouchPointFlags_UseTime | GetTouchPointFlags_UseSource;
	CLR_UINT16 source = 0;
	CLR_UINT16 x = 0;
	CLR_UINT16 y = 0;
	CLR_INT64 time = 0;
	CLR_INT16 dx = m_InkRegionInfo.X1;
	CLR_INT16 dy = m_InkRegionInfo.Y1;

	while ((hr = TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time)) == S_OK)
	{
		if (x == TouchPointLocationFlags_ContactUp) break;
		if (x == TouchPointLocationFlags_ContactDown) continue;

		if (m_lastx != 0xFFFF)
		{
			Graphics_Driver::DrawLineRaw(m_ScreenBmp, m_InkRegionInfo.Pen, m_lastx, m_lasty, x, y);
			if (m_InkRegionInfo.Bmp != NULL)
			{
				Graphics_Driver::DrawLine(*(m_InkRegionInfo.Bmp), m_InkRegionInfo.Pen, m_lastx - dx, m_lasty - dy, x - dx, y - dy);
			}
		}

		m_lastx = x;
		m_lasty = y;

		m_index = (flags >> 16);
	}

	if (x != TouchPointLocationFlags_ContactUp)
	{
		if (!m_InkCompletion.IsLinked()) m_InkCompletion.EnqueueDelta(INK_COMPLETION_TIME_USEC);
	}
}
#pragma GCC diagnostic pop


