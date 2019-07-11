//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//

#ifndef _GRAPHICS_MEMORY_
#define _GRAPHICS_MEMORY_ 1

#include "nanoCLR_Types.h"
#include <nanoPAL.h>
#include <target_platform.h>
#include <Esp32_os.h>
#include "Esp32_DeviceMapping.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "GraphicsMemoryHeap.h"


bool GraphicsMemorySetup()
{
	GraphicsMemory::StartingAddress = 0x0123;
	GraphicsMemory::SizeInBytes = 4;
	return true;
}

#endif  // _GRAPHICS_MEMORY_

