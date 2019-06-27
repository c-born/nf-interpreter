////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "nanoCLR_Types.h"
#include "nanoCLR_Runtime.h"

#include "gesture_driver.h"
#include "touchpanel_decl.h"
#include "gesture_decl.h"
GestureDriver g_GestureDriver;



// It seems that events are defined in  nanoHAL_V2.h and are required to be matched with managed code events.
// This is a fudge to get it to compile
#define EVENT_GESTURE 1


bool GestureDriver::s_initialized = FALSE;


#if defined(PLATFORM_DEPENDENT__GESTURE_COMPLETION_TIME_USEC)
#define GESTURE_COMPLETION_TIME_USEC PLATFORM_DEPENDENT__GESTURE_COMPLETION_TIME_USEC
#else
// 50ms - allow for some touch points to accumulate before we run the gesture engine
#define GESTURE_COMPLETION_TIME_USEC 50000 
#endif

//#define _GESTURE_DEBUGGING_ 

HRESULT GestureDriver::Initialize()
{
    if (!GestureDriver::s_initialized)
    {
        g_GestureDriver.m_gestureCompletion.InitializeForUserMode( GestureContinuationRoutine );

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
    if(!GestureDriver::s_initialized) return FALSE;
    
    g_GestureDriver.m_index = (flags >> 16);
    
    if (x == TouchPointLocationFlags_ContactUp)
    {
        CLR_UINT8 gesture = (CLR_UINT8)RecognizedGesture[g_GestureDriver.m_currentState];

#if defined(_GESTURE_DEBUGGING_)
        debug_printf("Final Gesture: %s\n", gesture <= 1 ? "NONE"    : gesture == 2 ? "RIGHT" : gesture == 3 ? "RIGHT_UP"  : gesture == 4 ? "UP" : 
                                            gesture == 5 ? "LEFT_UP" : gesture == 6 ? "LEFT"  : gesture == 7 ? "LEFT_DOWN" : gesture == 8 ? "DOWN" : "RIGHT_DOWN" );
#endif

        if(gesture != (CLR_UINT8)TouchGesture_NoGesture)
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
            if(adx > ady)
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
            else if(adx > ady)
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
            if(g_GestureDriver.m_stateIgnoreIndex >= 2*g_GestureDriver.c_IgnoreCount)
            {
                g_GestureDriver.m_currentState = g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreHead];

                g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreHead] = GestureStates[g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreTail]].NextState[dir];

                g_GestureDriver.m_stateIgnoreHead++;
                if(g_GestureDriver.m_stateIgnoreHead >= g_GestureDriver.c_IgnoreCount) g_GestureDriver.m_stateIgnoreHead = 0;

                g_GestureDriver.m_stateIgnoreTail++;
                if(g_GestureDriver.m_stateIgnoreTail >= g_GestureDriver.c_IgnoreCount) g_GestureDriver.m_stateIgnoreTail = 0;
            }
            else if(g_GestureDriver.m_stateIgnoreIndex >= g_GestureDriver.c_IgnoreCount)
            {
                g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreTail] = 
                    GestureStates[g_GestureDriver.m_stateIgnoreTail == 0 ? 0 : 
                    g_GestureDriver.m_stateIgnoreBuffer[g_GestureDriver.m_stateIgnoreTail-1]].NextState[dir];

                g_GestureDriver.m_stateIgnoreIndex++;
                
                if((g_GestureDriver.m_stateIgnoreTail+1) < g_GestureDriver.c_IgnoreCount)
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
            debug_printf("Gesture: %s\n", dir == 0 ? "E" : dir == 1 ? "NE" : dir == 2 ? "N" : dir == 3 ? "NW" : dir == 4 ? "W" : dir == 5 ? "SW" : dir == 6 ? "S" : "SE" );
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
void GestureDriver::GestureContinuationRoutine(void *arg)
{
    HRESULT hr = S_OK;
    CLR_UINT32 flags = (g_GestureDriver.m_index << 16) | GetTouchPointFlags_NextPoint | GetTouchPointFlags_UseTime | GetTouchPointFlags_UseSource;
    CLR_UINT16 source = 0;
    CLR_UINT16 x = 0;
    CLR_UINT16 y = 0;
    CLR_INT64 time = 0;

    while((hr = TOUCH_PANEL_GetTouchPoint(&flags, &source, &x, &y, &time)) == S_OK)
    {
        if(!ProcessPoint(flags, source, x, y, time)) break;
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
#pragma GCC diagnostic pop

