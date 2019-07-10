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
	static bool InitializeDisplayInterface();
	static void SendCommand(CLR_UINT8 c);
	static void SendData(CLR_UINT8 data[], CLR_UINT32 count);
	static void SendCommandAndData(CLR_UINT8 command, CLR_UINT8 data[], CLR_UINT32 dataCount);
	static void DisplayBacklight(bool on); // true = on
	static void DisplayCommandDelay(CLR_INT16 delay);

};

#endif  // _DISPLAY_INTERFACE_H_
