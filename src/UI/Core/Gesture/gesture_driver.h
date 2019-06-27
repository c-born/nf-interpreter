////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "nanoCLR_Types.h"
#include "nanoCLR_Runtime.h"

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
    static void GestureContinuationRoutine(void *arg);

};

extern GestureDriver g_GestureDriver;

