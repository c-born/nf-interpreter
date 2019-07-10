
#ifndef _TOUCHINTERFACE_H_
#define _TOUCHINTERFACE_H_ 1

//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
struct SPI_CONFIGURATION
{
	GPIO_PIN       DeviceCS;
	bool           CS_Active;             // False = LOW active,      TRUE = HIGH active
	bool           MSK_IDLE;              // False = LOW during idle, TRUE = HIGH during idle
	bool           MSK_SampleEdge;        // False = sample falling edge,  TRUE = samples on rising
	bool           MD_16bits;
	CLR_UINT32         Clock_RateKHz;
	CLR_UINT32         CS_Setup_uSecs;
	CLR_UINT32         CS_Hold_uSecs;
	CLR_UINT32         SPI_mod;
//	GPIO_FLAG      BusyPin;
};

struct TouchInterface
{
	static SPI_CONFIGURATION g_SpiConfiguration;
	static bool Write_Read(const SPI_CONFIGURATION& Configuration, CLR_UINT8* Write8, CLR_INT32 WriteCount, CLR_UINT8* Read8, CLR_INT32 ReadCount, CLR_INT32 ReadStartOffset);
};

#endif // _TOUCHINTERFACE_H_



//struct TOUCH_SPI_CONFIGURATION
//{
//    SPI_CONFIGURATION SpiConfiguration;
//    GPIO_PIN          InterruptPin;
//};
