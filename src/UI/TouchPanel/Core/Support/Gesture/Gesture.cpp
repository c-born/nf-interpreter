//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
#include "Graphics.h"
#include "gesture_decl.h"
#include "Ink.h"
#include "touchpanel_driver.h"

#include "nanoPAL.h"
#include "nanoHAL_Time.h"

HRESULT Gesture_Initialize()
{
	return g_GestureDriver.Initialize();
}

HRESULT Gesture_Uninitialize()
{
	return g_GestureDriver.Uninitialize();
}

void Gesture_ProcessPoint(CLR_UINT32 flags, CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time)
{
	g_GestureDriver.ProcessPoint(flags, source, x, y, time);
}


GestureDriver g_GestureDriver;

// It seems that events are defined in  nanoHAL_V2.h and are required to be matched with managed code events.
// This is a fudge to get it to compile
#define EVENT_GESTURE 1

bool GestureDriver::s_initialized = FALSE;

// 50ms - allow for some touch points to accumulate before we run the gesture engine

HRESULT GestureDriver::Initialize()
{
	if (!GestureDriver::s_initialized)
	{
		g_GestureDriver.m_gestureCompletion.InitializeForUserMode(GestureContinuationRoutine);

		g_GestureDriver.m_gestureListener.m_palEventListener = EventListener;
		g_GestureDriver.m_gestureListener.m_eventMask = PAL_EVENT_TOUCH | PAL_EVENT_MOUSE;
		PalEvent_Enlist(&g_GestureDriver.m_gestureListener);
		GestureDriver::s_initialized = TRUE;
	}

	return S_OK;
}

HRESULT GestureDriver::Uninitialize()
{
	if (GestureDriver::s_initialized)
	{
		GestureDriver::s_initialized = FALSE;

		if (g_GestureDriver.m_gestureCompletion.IsLinked()) g_GestureDriver.m_gestureCompletion.Abort();
		ResetRecognition();
	}

	return S_OK;
}

void GestureDriver::EventListener(unsigned int e, unsigned int param)
{
	if ((e & PAL_EVENT_TOUCH) && (param & TouchPanelStylusDown))
	{
		CLR_UINT32 flags = GetTouchPointFlags_LatestPoint | GetTouchPointFlags_UseTime | GetTouchPointFlags_UseSource;
		CLR_UINT16 source = 0;
		CLR_UINT16 x = 0;
		CLR_UINT16 y = 0;
		CLR_INT64 time = 0;

		if (TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time) == S_OK)
		{
			g_GestureDriver.ResetRecognition();

			g_GestureDriver.m_index = (flags >> 16);

			if (!g_GestureDriver.m_gestureCompletion.IsLinked()) g_GestureDriver.m_gestureCompletion.Enqueue();
		}
	}
}

#define GESTURE_STATE_COUNT 10

struct GestureState
{
	unsigned char NextState[8];
};

///
/// FUTURE: 06/16/2008- munirula.
/// Gesture is recognized using a state machine, this appears to work fairly fast
/// compare to other implementations I tried. In future we might want to revisit
/// this.
///


/// We have 8 directions (E, NE, N, NW, W, SW, S, SE) in this order. States changed
/// based on identified direction.
static GestureState GestureStates[GESTURE_STATE_COUNT] =
{
	///     E   NE  N  NW  W  SW  S  SE
	///     0    1   2    3   4    5    6   7
		{{2, 3, 4, 5, 6, 7, 8, 9}},
		{{1, 1, 1, 1, 1, 1, 1, 1}},
		{{2, 1, 1, 1, 1, 1, 1, 1}},
		{{1, 3, 1, 1, 1, 1, 1, 1}},
		{{1, 1, 4, 1, 1, 1, 1, 1}},
		{{1, 1, 1, 5, 1, 1, 1, 1}},
		{{1, 1, 1, 1, 6, 1, 1, 1}},
		{{1, 1, 1, 1, 1, 7, 1, 1}},
		{{1, 1, 1, 1, 1, 1, 8, 1}},
		{{1, 1, 1, 1, 1, 1, 1, 9}},
};

static TouchGestures RecognizedGesture[GESTURE_STATE_COUNT] =
{
	TouchGesture_NoGesture,
	TouchGesture_NoGesture,
	TouchGesture_Right,
	TouchGesture_UpRight,
	TouchGesture_Up,
	TouchGesture_UpLeft,
	TouchGesture_Left,
	TouchGesture_DownLeft,
	TouchGesture_Down,
	TouchGesture_DownRight,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
bool GestureDriver::ProcessPoint(CLR_UINT32 flags, CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time)
{
	if (!GestureDriver::s_initialized) return FALSE;

	g_GestureDriver.m_index = (flags >> 16);

	if (x == TouchPointLocationFlags_ContactUp)
	{
		CLR_UINT8 gesture = (CLR_UINT8)RecognizedGesture[g_GestureDriver.m_currentState];

#if defined(_GESTURE_DEBUGGING_)
		debug_printf("Final Gesture: %s\n", gesture <= 1 ? "NONE" : gesture == 2 ? "RIGHT" : gesture == 3 ? "RIGHT_UP" : gesture == 4 ? "UP" :
			gesture == 5 ? "LEFT_UP" : gesture == 6 ? "LEFT" : gesture == 7 ? "LEFT_DOWN" : gesture == 8 ? "DOWN" : "RIGHT_DOWN");
#endif

		if (gesture != (CLR_UINT8)TouchGesture_NoGesture)
		{
			PostManagedEvent(EVENT_GESTURE, gesture, 0, ((CLR_UINT32)g_GestureDriver.m_startx << 16) | g_GestureDriver.m_starty);
		}
		return FALSE;
	}

	if (x == TouchPointLocationFlags_ContactDown) return true;

	if (g_GestureDriver.m_lastx == 0xFFFF)
	{
		g_GestureDriver.m_lastx = x;
		g_GestureDriver.m_lasty = y;

		g_GestureDriver.m_startx = x;
		g_GestureDriver.m_starty = y;

		return TRUE;
	}

	CLR_INT16 dx = (CLR_INT16)x - (CLR_INT16)g_GestureDriver.m_lastx;
	CLR_INT16 dy = (CLR_INT16)y - (CLR_INT16)g_GestureDriver.m_lasty;
	CLR_INT16 adx = abs(dx);
	CLR_INT16 ady = abs(dy);

	if ((adx + ady) >= TOUCH_PANEL_MINIMUM_GESTURE_DISTANCE)
	{
		{
			int dir = 0;
			bool diagonal = false;

			///
			/// Diagonal line is defined as a line with angle between 22.5 degrees and 67.5 (and equivalent translations in
			/// each quadrant).  which means the abs(dx) - abs(dy) <= abs(dx) if dx > dy or abs(dy) -abs(dx) <= abs(dy) if dy > dx
			///
			if (adx > ady)
			{
				diagonal = (adx - ady) <= (adx / 2);
			}
			else
			{
				diagonal = (ady - adx) <= (ady / 2);
			}

			if (diagonal)
			{
				if (dx > 0)
				{
					if (dy > 0)
						dir = 7; /// SE.
					else
						dir = 1; /// NE.
				}
				else
				{
					if (dy > 0)
						dir = 5; /// SW
					else
						dir = 3; /// NW.
				}
			}
			else if (adx > ady)
			{
				if (dx > 0)
					dir = 0; /// E.
				else
					dir = 4; /// W.
			}
			else
			{
				if (dy > 0)
					dir = 6; /// S.
				else
					dir = 2; /// N.
			}

			/// 
			/// The first and last points are sometimes erratic, so lets ignore the first c_IgnoreCount points
			/// and the last c_IgnoreCount points.  We do this by creating a buffer to track the last c_IgnoreCount
			/// points and only update the current state when the buffer is full.
			///
			if (g_GestureDriver.m_stateIgnoreIndex >= 2 * g_GestureDriver.c_IgnoreCount)
			{
				g_GestureDriver.m_currentState = g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreHead];

				g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreHead] = GestureStates[g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreTail]].NextState[dir];

				g_GestureDriver.m_stateIgnoreHead++;
				if (g_GestureDriver.m_stateIgnoreHead >= g_GestureDriver.c_IgnoreCount) g_GestureDriver.m_stateIgnoreHead = 0;

				g_GestureDriver.m_stateIgnoreTail++;
				if (g_GestureDriver.m_stateIgnoreTail >= g_GestureDriver.c_IgnoreCount) g_GestureDriver.m_stateIgnoreTail = 0;
			}
			else if (g_GestureDriver.m_stateIgnoreIndex >= g_GestureDriver.c_IgnoreCount)
			{
				g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreTail] =
					GestureStates[g_GestureDriver.m_stateIgnoreTail == 0 ? 0 :
					g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreTail - 1]].NextState[dir];

				g_GestureDriver.m_stateIgnoreIndex++;

				if ((g_GestureDriver.m_stateIgnoreTail + 1) < g_GestureDriver.c_IgnoreCount)
				{
					g_GestureDriver.m_stateIgnoreTail++;
				}
			}
			else
			{
				g_GestureDriver.m_stateIgnoreIndex++;
			}

			g_GestureDriver.m_lastx = x;
			g_GestureDriver.m_lasty = y;

#if defined(_GESTURE_DEBUGGING_)
			debug_printf("Gesture: %s\n", dir == 0 ? "E" : dir == 1 ? "NE" : dir == 2 ? "N" : dir == 3 ? "NW" : dir == 4 ? "W" : dir == 5 ? "SW" : dir == 6 ? "S" : "SE");
#endif
		}
	}

	return true;
}
#pragma GCC diagnostic pop

void GestureDriver::ResetRecognition()
{
	g_GestureDriver.m_currentState = 0;
	g_GestureDriver.m_lastx = 0xFFFF;
	g_GestureDriver.m_lasty = 0xFFFF;
	g_GestureDriver.m_stateIgnoreIndex = 0;
	g_GestureDriver.m_stateIgnoreHead = 0;
	g_GestureDriver.m_stateIgnoreTail = 0;
	g_GestureDriver.m_stateIgnoreBuffer[0] = 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void GestureDriver::GestureContinuationRoutine(void* arg)
{
	HRESULT hr = S_OK;
	CLR_UINT32 flags = (g_GestureDriver.m_index << 16) | GetTouchPointFlags_NextPoint | GetTouchPointFlags_UseTime | GetTouchPointFlags_UseSource;
	CLR_UINT16 source = 0;
	CLR_UINT16 x = 0;
	CLR_UINT16 y = 0;
	CLR_INT64 time = 0;

	while ((hr = TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time)) == S_OK)
	{
		if (!ProcessPoint(flags, source, x, y, time)) break;
	}

	if (x == TouchPointLocationFlags_ContactUp)
	{
		if (g_GestureDriver.m_gestureCompletion.IsLinked()) g_GestureDriver.m_gestureCompletion.Abort();
	}
	else
	{
		if (!g_GestureDriver.m_gestureCompletion.IsLinked()) g_GestureDriver.m_gestureCompletion.EnqueueDelta(GESTURE_COMPLETION_TIME_USEC);
	}
}


void Listener(unsigned int e, unsigned int param);

struct GestureDriver
{
	static const int c_IgnoreCount = 2;
private:
	static bool      s_initialized;


	PalEventListener m_gestureListener;
	HAL_COMPLETION   m_gestureCompletion;
	CLR_UINT32           m_index;
	CLR_UINT32           m_currentState;
	CLR_UINT16           m_lastx;
	CLR_UINT16           m_lasty;
	CLR_UINT16           m_startx;
	CLR_UINT16           m_starty;

	CLR_UINT32           m_stateIgnoreIndex;
	CLR_UINT32           m_stateIgnoreHead;
	CLR_UINT32           m_stateIgnoreTail;
	CLR_UINT32           m_stateIgnoreBuffer[c_IgnoreCount];


public:
	static HRESULT Initialize();
	static HRESULT Uninitialize();
	static bool ProcessPoint(CLR_UINT32 flags, CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time);

	static void ResetRecognition();
	static void EventListener(unsigned int e, unsigned int param);
	static void GestureContinuationRoutine(void* arg);

};

extern GestureDriver g_GestureDriver;

enum TouchGestures
{
	TouchGesture_NoGesture = 0,          //Can be used to represent an error gesture or unknown gesture

	//Standard Win7 Gestures
	TouchGesture_Begin = 1,       //Used to identify the beginning of a Gesture Sequence; App can use this to highlight UIElement or some other sort of notification.
	TouchGesture_End = 2,       //Used to identify the end of a gesture sequence; Fired when last finger involved in a gesture is removed.

	// Standard stylus (single touch) gestues
	TouchGesture_Right = 3,
	TouchGesture_UpRight = 4,
	TouchGesture_Up = 5,
	TouchGesture_UpLeft = 6,
	TouchGesture_Left = 7,
	TouchGesture_DownLeft = 8,
	TouchGesture_Down = 9,
	TouchGesture_DownRight = 10,
	TouchGesture_Tap = 11,
	TouchGesture_DoubleTap = 12,

	// Multi-touch gestures
	TouchGesture_Zoom = 114,      //Equivalent to your "Pinch" gesture
	TouchGesture_Pan = 115,      //Equivalent to your "Scroll" gesture
	TouchGesture_Rotate = 116,
	TouchGesture_TwoFingerTap = 117,
	TouchGesture_Rollover = 118,      // Press and tap               

	//Additional NetMF gestures
	TouchGesture_UserDefined = 200
};

//--//

HRESULT Gesture_Initialize();
HRESULT Gesture_Uninitialize();
void Gesture_ProcessPoint(CLR_UINT32 flags, CLR_UINT16 source, CLR_UINT16 x, CLR_UINT16 y, CLR_INT64 time);
