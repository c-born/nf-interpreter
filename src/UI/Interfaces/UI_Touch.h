//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _TARGETPAL_UI_H_
#define _TARGETPAL_UI_H_ 1

#include "nanoCLR_Types.h"
#include <nanoPAL.h>
#include <target_platform.h>
#include <Esp32_os.h>

public:
	// Display Interface
	bool UI_DISPLAY::InitializeDisplayDriver();
	void UI_DISPLAY::SendCommand(CLR_UINT8 c);
	void UI_DISPLAY::SendCommand(CLR_UINT8 command, CLR_UINT8 value);
	void UI_DISPLAY::SendData(CLR_UINT16 value);       // Word data
	void UI_DISPLAY::SendData(const CLR_UINT16 data[], CLR_UINT16 count);
	void UI_DISPLAY::SendData(CLR_UINT8* pParams, int numberOfParameters);

	CLR_INT32 UI_TOUCH::ReadsToIgnore;
	CLR_INT32 UI_TOUCH::ReadsPerSample;
	CLR_INT32 UI_TOUCH::MaxFilterDistance; /// This is actually sqaured value of the max distance allowed between two points.
	bool  UI_TOUCH::ActivePinStateForTouchDown;
	TOUCH_PANEL_SAMPLE_RATE SampleRate;

	bool UI_TOUCH::Write_Read(const SPI_CONFIGURATION& Configuration, CLR_UINT8* Write8, CLR_INT32 WriteCount, CLR_UINT8* Read8, CLR_INT32 ReadCount, CLR_INT32 ReadStartOffset);


#endif  // _DRIVERS_PAL_GRAPHICS_H_


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "nanoCLR_Types.h"
#include "TouchPanel_decl.h"
#include "CPU_GPIO_decl.h"
#include "Touch_driver.h"

bool UI_TOUCH::Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
bool UI_TOUCH::Disable();

void HAL_TOUCH_PANEL_GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY)
{
	Touch_Driver::GetPoint(pTipState, pSource, pUnCalX, pUnCalY);
}

HRESULT HAL_TOUCH_PANEL_GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
	return Touch_Driver::GetDeviceCaps(iIndex, lpOutput);
}

