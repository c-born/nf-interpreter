//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _DISPLAY_INTERFACE_H_
#define _DISPLAY_INTERFACE_H_ 1

#include "nanoCLR_Types.h"

struct DisplayInterface
{
	static bool InitializeDisplayDriver();
	static void SendCommand(CLR_UINT8 c);
	static void SendCommand(CLR_UINT8 command, CLR_UINT8 value);
	static void SendCommandAndData(CLR_UINT8 command, CLR_UINT8 data[], CLR_UINT32 dataCount);
	static void SendData(CLR_UINT16 value);    
	static void SendData(const CLR_UINT16 data[], CLR_UINT16 count);
	static void DisplayBacklight(bool on) // true = on
	{

	}
	static void DisplayPower(bool powerState)  // true = on
	{

	}
	static void DisplayCommandDelay(CLR_INT16 delay);

}

#endif  // _DISPLAY_INTERFACE_H_
