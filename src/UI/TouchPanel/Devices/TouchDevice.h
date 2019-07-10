//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _TOUCHDEVICE_H_
#define _TOUCHDEVICE_H_ 1

#include "Graphics.h"
#include "nanoPAL_AsyncProcCalls_decl.h"
#include "TouchPanel.h"

typedef void (*GPIO_INTERRUPT_SERVICE_ROUTINE)(GPIO_PIN Pin, bool PinState, void* Param);

struct TouchDevice
{
	
	static CLR_INT32 ReadsToIgnore;
	static CLR_INT32 ReadsPerSample;
	static CLR_INT32 MaxFilterDistance;		// This is actually sqaured value of the max distance allowed between two points.

	static bool Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
	static bool Disable();

};

#endif //_TOUCHDEVICE_H_

