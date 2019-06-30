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
	// Display Interface
	bool DISPLAY::InitializeDisplayDriver();
	void DISPLAY::SendCommand(CLR_UINT8 c);
	void DISPLAY::SendCommand(CLR_UINT8 command, CLR_UINT8 value);
	void DISPLAY::SendData(CLR_UINT16 value);       // Word data
	void DISPLAY::SendData(const CLR_UINT16 data[], CLR_UINT16 count);
	void DISPLAY::SendData(CLR_UINT8* pParams, int numberOfParameters);
}

#endif  // _DISPLAY_INTERFACE_H_
