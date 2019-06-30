//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _TOUCH_H_
#define _TOUCH_H_ 1

#include "Graphics.h"
#include "TouchDevice.h"

//#define TOUCH_PANEL_SAMPLE_RATE_LOW             100
//#define TOUCH_PANEL_SAMPLE_RATE_HIGH            100
//#define RollingAverageBufferSize 8

#define TOUCH_PANEL_SAMPLE_RATE_ID             0
#define TOUCH_PANEL_SAMPLE_MS_TO_TICKS(x) (x * TIME_CONVERSION__TO_MILLISECONDS)
#define TOUCH_PANEL_CALIBRATION_POINT_COUNT_ID	1
#define TOUCH_PANEL_CALIBRATION_POINT_ID       2
#define TOUCH_PANEL_DEFAULT_TRANSIENT_BUFFER_SIZE 100
#define TOUCH_PANEL_DEFAULT_STROKE_BUFFER_SIZE 200
#define TOUCH_PANEL_MINIMUM_GESTURE_DISTANCE 10

typedef CLR_UINT32 TOUCH_PANEL_SAMPLE_FLAGS;


struct TOUCH_PANEL_SAMPLE_RATE
{
    CLR_INT32   SamplesPerSecondLow;
    CLR_INT32   SamplesPerSecondHigh;
    CLR_INT32   CurrentSampleRateSetting;
    CLR_INT32   MaxTimeForMoveEvent_ticks;
};

struct TOUCH_PANEL_CALIBRATION_POINT_COUNT
{
	CLR_UINT32 flags;
    CLR_INT32  cCalibrationPoints;
};

struct TOUCH_PANEL_CALIBRATION_POINT
{
    CLR_INT32   PointNumber;
    CLR_INT32   cDisplayWidth;
    CLR_INT32   cDisplayHeight;
    CLR_INT32   CalibrationX;
    CLR_INT32   CalibrationY;
};

enum InternalFlags
{
	Contact_Down = 0x1,
	Contact_WasDown = 0x2,
};

enum TouchPanel_SampleFlags
{
    TouchSampleValidFlag = 0x01,
    TouchSampleDownFlag = 0x02,
    TouchSampleIsCalibratedFlag = 0x04,
    TouchSamplePreviousDownFlag = 0x08,
    TouchSampleIgnore = 0x10,
    TouchSampleMouse = 0x40000000
};

enum TouchPanel_StylusFlags
{
    TouchPanelStylusInvalid = 0x0,
    TouchPanelStylusDown = 0x1,
    TouchPanelStylusUp = 0x2,
    TouchPanelStylusMove = 0x3,
};

enum TouchPanel_TouchCollectorFlags
{
    TouchCollector_EnableCollection = 0x1,
    TouchCollector_DirectInk = 0x2,
    TouchCollector_GestureRecognition = 0x4,
};

enum TouchPanel_TouchInfoFlags
{
    TouchInfo_Set = 0x1,
    TouchInfo_LastTouchPoint = 0x2,
    TouchInfo_SamplingDistance = 0x4,
    TouchInfo_StylusMoveFrequency = 0x8,
    TouchInfo_SamplingReadsToIgnore = 0x10,
    TouchInfo_SamplingReadsPerSample = 0x20,
    TouchInfo_SamplingFilterDistance = 0x40,
};

enum TouchPointLocationFlags
{
	TouchPointLocationFlags_ContactDown = 0x3FF,
	TouchPointLocationFlags_ContactUp = 0x3FE,
};

enum TouchPointContactFlags
{
	TouchPointContactFlags_Primary = 0x80000000,
	TouchPointContactFlags_Pen = 0x40000000,
	TouchPointContactFlags_Palm = 0x20000000,
};

enum GetTouchPointFlags
{
	GetTouchPointFlags_LatestPoint = 0x0,
	GetTouchPointFlags_EarliestPoint = 0x1,
	GetTouchPointFlags_NextPoint = 0x2,
	GetTouchPointFlags_PreviousPoint = 0x3,
	GetTouchPointFlags_UseTime = 0x10,
	GetTouchPointFlags_UseSource = 0x20,
};

struct TOUCH_PANEL_CalibrationData
{
    CLR_INT32 Mx;
    CLR_INT32 My;

    CLR_INT32 Cx;
    CLR_INT32 Cy;

    CLR_INT32 Dx;
    CLR_INT32 Dy;
};

struct TouchPoint
{
    /// Location is a composite of source, x and y. bits 0-13: x, 14-27: y, 28-31: source.
    /// Source is for multi touch support; 16 sources can be reported.
    CLR_UINT32 location;
    /// Contact is a composite of flags, width, and height. bits 0-13: width, 14-27: height, 28-31: flags
    CLR_UINT32 contact;
    CLR_INT64  time;
};

struct TOUCH_PANEL_Point
{
    CLR_UINT16 sx;
    CLR_UINT16 sy;
};

struct TOUCH_PANEL_SamplingSettings
{
	CLR_INT32 ReadsToIgnore;
	CLR_INT32 ReadsPerSample;
	CLR_INT32 MaxFilterDistance; /// This is actually sqaured value of the max distance allowed between two points.
	bool  ActivePinStateForTouchDown;
	TOUCH_PANEL_SAMPLE_RATE SampleRate;
};


extern TOUCH_PANEL_CalibrationData g_TouchPanel_Calibration_Config;
extern TOUCH_PANEL_SamplingSettings g_TouchPanel_Sampling_Settings;
extern TouchPoint g_PAL_TouchPointBuffer[];
extern CLR_UINT32     g_PAL_TouchPointBufferSize;
extern TOUCH_PANEL_Point g_PAL_RunningAvg_Buffer[];
extern CLR_UINT32     g_PAL_RunningAvg_Buffer_Size;

struct TOUCH_PANEL_TouchCollectorData
{
    /// ISSUE: Use something like private alloc here?
    /// For now these are static buffers.
    TOUCH_PANEL_Point TransientBuffer[TOUCH_PANEL_DEFAULT_TRANSIENT_BUFFER_SIZE];
    TOUCH_PANEL_Point StrokeBuffer[TOUCH_PANEL_DEFAULT_STROKE_BUFFER_SIZE];
    unsigned char TouchCollectorFlags;
    CLR_INT32 TouchCollectorX1;
    CLR_INT32 TouchCollectorX2;
    CLR_INT32 TouchCollectorY1;
    CLR_INT32 TouchCollectorY2;
    Hal_Queue_UnknownSize<TOUCH_PANEL_Point> TransientPointBuffer;
    Hal_Queue_UnknownSize<TOUCH_PANEL_Point> StrokePointBuffer;

    TOUCH_PANEL_Point InkLastPoint;
    CLR_INT32 GestureCurrentStateX;
    CLR_INT32 GestureCurrentStateY;
    TOUCH_PANEL_Point GestureLastPoint;

    /// ISSUE: Some questions here. I need partial redraw support, and also
    /// need to lock this bitmap memory so gc won't move it.
    PAL_GFX_Bitmap* CollectorBitmap;
    CLR_UINT32*     BitmapData;
};






#endif // _TOUCH_H_

