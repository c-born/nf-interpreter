
#ifndef _TOUCHINTERFACE_H_
#define _TOUCHINTERFACE_H_ 1

//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

struct TouchInterface
{
	bool Write_Read(const SPI_CONFIGURATION& Configuration, CLR_UINT8* Write8, CLR_INT32 WriteCount, CLR_UINT8* Read8, CLR_INT32 ReadCount, CLR_INT32 ReadStartOffset);
}

#endif // _TOUCHINTERFACE_H_



//struct TOUCH_SPI_CONFIGURATION
//{
//    SPI_CONFIGURATION SpiConfiguration;
//    GPIO_PIN          InterruptPin;
//};
