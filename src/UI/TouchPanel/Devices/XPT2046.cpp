//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _XPT2046_H_
#define _XPT2046_H_ 1

#include "TouchInterface.h"
#include "Graphics.h"
#include "Touch.h"

HRESULT Initialize()
{
	TouchInterface::Initialize();
}
HRESULT Uninitialize()
{
	TouchInterface::Uninitialize();
}
HRESULT GetDeviceCaps(CLR_UINT32 iIndex, void* lpOutput)
{
	return 1;
}
bool Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
	return 1;
}
bool Disable() { return 1; }
HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
	return 1;
}
HRESULT SetNativeBufferSize(int transientBufferSize, int strokeBufferSize)
{
	return 1;
}
HRESULT ResetCalibration()
{
	return 1;
}
HRESULT SetCalibration(CLR_INT32 pointCount, short* sx, short* sy, short* ux, short* uy)
{
	return 1;
}
void SetDriverDefaultCalibrationData()
{
	return ;
}
HRESULT EnableTouchCollection(CLR_INT32 flags, CLR_INT32 x1, CLR_INT32 x2, CLR_INT32 y1, CLR_INT32 y2, PAL_GFX_Bitmap* bitmap)
{
	return 1;
}
bool CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT* pTCP)
{
	return 1;
}
void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, CLR_INT32* pSource, CLR_INT32* pUnCalX, CLR_INT32* pUnCalY)
{
	return 1;
}
HRESULT GetTouchPoint(CLR_UINT32* flags, CLR_UINT16* source, CLR_UINT16* x, CLR_UINT16* y, CLR_INT64* time)
{
	return 1;
}
HRESULT GetTouchPoint(CLR_UINT32* flags, CLR_UINT32* location, CLR_INT64* time)
{
	return 1;
}
HRESULT GetTouchPoint(CLR_UINT32* flags, TouchPoint** point)
{
	return 1;
}
HRESULT GetTouchPoints(CLR_INT32* pointCount, short* sx, short* sy)
{
	return 1;
}
HRESULT GetSetTouchInfo(CLR_UINT32 flags, CLR_INT32* param1, CLR_INT32* param2, CLR_INT32* param3)
{
	return 1;
}
void TouchIsrProc(GPIO_PIN pin, bool pinState, void* context)
{
	return;
}
void TouchCompletion(void* arg)
{
	return;
}
void TouchPanelCalibratePoint(int UncalX, int UncalY, int* pCalX, int* pCalY)
{
	return;
}
CLR_UINT16 GetTouchStylusFlags(unsigned int sampleFlags)
{
	return 1;
}
void PollTouchPoint(void* arg)
{
	return;
}
TouchPoint* AddTouchPoint(CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time, bool fIgnoreDuplicate = FALSE)
{
	return NULL;
}


#endif // _XPT2046_H_