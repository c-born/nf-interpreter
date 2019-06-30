//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _TOUCHDEVICE_H_
#define _TOUCHDEVICE_H_ 1

#include "Graphics.h"
#include "nanoPAL_AsyncProcCalls_decl.h"

typedef void (*GPIO_INTERRUPT_SERVICE_ROUTINE)(GPIO_PIN Pin, bool PinState, void* Param);

struct TouchDevice
{
	CLR_INT32 ReadsToIgnore;
	CLR_INT32 ReadsPerSample;
	CLR_INT32 MaxFilterDistance;		// This is actually sqaured value of the max distance allowed between two points.
	bool  ActivePinStateForTouchDown;
	TOUCH_PANEL_SAMPLE_RATE SampleRate;
	int m_touchMoveIndex;
	TouchPoint* m_startMovePtr;
	TouchPoint m_tmpUpTouch;
	HAL_COMPLETION m_touchCompletion;
	TOUCH_PANEL_CalibrationData m_calibrationData;
	CLR_INT32 m_samplingTimespan;
	CLR_INT32 m_InternalFlags;
	CLR_INT32 m_readCount;
	CLR_INT32 m_runavgTotalX;
	CLR_INT32 m_runavgTotalY;
	CLR_INT32 m_runavgCount;
	CLR_INT32 m_runavgIndex;
	CLR_INT32 m_head;
	CLR_INT32 m_tail;

	HRESULT Initialize();
	HRESULT Uninitialize();
	HRESULT GetDeviceCaps(CLR_UINT32 iIndex, void* lpOutput);
	bool Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
	bool Disable();
	HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput);
	HRESULT SetNativeBufferSize(int transientBufferSize, int strokeBufferSize);
	HRESULT ResetCalibration();
	HRESULT SetCalibration(CLR_INT32 pointCount, short* sx, short* sy, short* ux, short* uy);
	void SetDriverDefaultCalibrationData();
	HRESULT EnableTouchCollection(CLR_INT32 flags, CLR_INT32 x1, CLR_INT32 x2, CLR_INT32 y1, CLR_INT32 y2, PAL_GFX_Bitmap* bitmap);
	bool CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT* pTCP);
	void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, CLR_INT32* pSource, CLR_INT32* pUnCalX, CLR_INT32* pUnCalY);
	HRESULT GetTouchPoint(CLR_UINT32* flags, CLR_UINT16* source, CLR_UINT16* x, CLR_UINT16* y, CLR_INT64* time);
	HRESULT GetTouchPoint(CLR_UINT32* flags, CLR_UINT32* location, CLR_INT64* time);
	HRESULT GetTouchPoint(CLR_UINT32* flags, TouchPoint** point);
	HRESULT GetTouchPoints(CLR_INT32* pointCount, short* sx, short* sy);
	HRESULT GetSetTouchInfo(CLR_UINT32 flags, CLR_INT32* param1, CLR_INT32* param2, CLR_INT32* param3);
	void TouchIsrProc(GPIO_PIN pin, bool pinState, void* context);
	void TouchCompletion(void* arg);
	void TouchPanelCalibratePoint(int UncalX, int UncalY, int* pCalX, int* pCalY);
	CLR_UINT16 GetTouchStylusFlags(unsigned int sampleFlags);
	void PollTouchPoint(void* arg);
	TouchPoint* AddTouchPoint(CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time, bool fIgnoreDuplicate = FALSE);


};

#endif //_TOUCHDEVICE_H_

