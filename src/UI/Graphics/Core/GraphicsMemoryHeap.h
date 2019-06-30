//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _GraphicsMemoryHeap_H
#define _GraphicsMemoryHeap_H 1

#include "nanoCLR_Types.h"

struct GraphicsMemoryHeap
{
	static void  Initialize(void* pHeapBuffer, CLR_UINT32 heapBuufferSize);
	static void* Allocate(CLR_UINT32 len);
	static void  Release(void* pHeapBlock);
	static void* ReAllocate(void* pHeapBlock, CLR_UINT32 len);
	static bool  IsAllocated(void* pHeapBlock);
};
#endif  // _GraphicsMemoryHeap_H
