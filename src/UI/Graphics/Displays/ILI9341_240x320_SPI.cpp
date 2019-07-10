//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "Graphics.h"
#include "Display.h"
#include "DisplayInterface.h"


/*
ILI9341 is a 262,144-color single-chip SOC driver for a-TFT liquid crystal display with resolution of 240RGBx320
dots, comprising a 720-channel source driver, a 320-channel gate driver, 172,800 bytes GRAM for graphic
display data of 240RGBx320 dots, and power supply circuit.

ILI9341 supports parallel 8-/9-/16-/18-bit data bus MCU interface, 6-/16-/18-bit data bus RGB interface and
3-/4-line serial peripheral interface (SPI).

ILI9341 supports full color, 8-color display mode and sleep mode for precise power control by software.

Power saving mode:
 Sleep mode
 Deep standby mode

This implementation was initially written for 16 bit colour, SPI interface of a ESP32-WROVER-KIT-v4.1
*/

enum ILI9341_Command : CLR_UINT8
{
	CMD_NOP = 0x00,
	CMD_SOFTWARE_RESET = 0x01,
	CMD_POWER_STATE = 0x10,
	CMD_Sleep_Out = 0x11,
	CMD_Gamma_Set = 0x26,
	CMD_Display_OFF = 0x28,
	CMD_Display_ON = 0x29,
	CMD_Column_Address_Set = 0x2A,
	CMD_Page_Address_Set = 0x2B,
	CMD_Memory_Write = 0x2C,
	CMD_Colour_Set = 0x2D,
	CMD_Memory_Read = 0x2E,
	CMD_Partial_Area = 0x30,
	CMD_Memory_Access_Control = 0x36,
	CMD_Pixel_Format_Set = 0x3A,
	CMD_Write_Display_Brightness = 0x51,
	CMD_Frame_Rate_Control_Normal = 0xB1,
	CMD_Display_Function_Control = 0xB6,
	CMD_Entry_Mode_Set = 0xB7,
	CMD_Power_Control_1 = 0xC0,
	CMD_Power_Control_2 = 0xC1,
	CMD_VCOM_Control_1 = 0xC5,
	CMD_VCOM_Control_2 = 0xC7,
	CMD_Power_Control_A = 0xCB,
	CMD_Power_Control_B = 0xCF,
	CMD_Positive_Gamma_Correction = 0xE0,
	CMD_Negative_Gamma_Correction = 0XE1,
	CMD_Driver_Timing_Control_A = 0xE8,
	CMD_Driver_Timing_Control_B = 0xEA,
	CMD_Power_On_Sequence = 0xED,
	CMD_Enable_3G = 0xF2,
	CMD_Pump_Ratio_Control = 0xF7

};
enum ILI9341_Orientation : CLR_UINT8
{
	MADCTL_MH = 0x04, // sets the Horizontal Refresh, 0=Left-Right and 1=Right-Left
	MADCTL_ML = 0x10, // sets the Vertical Refresh, 0=Top-Bottom and 1=Bottom-Top
	MADCTL_MV = 0x20, // sets the Row/Column Swap, 0=Normal and 1=Swapped
	MADCTL_MX = 0x40, // sets the Column Order, 0=Left-Right and 1=Right-Left
	MADCTL_MY = 0x80, // sets the Row Order, 0=Top-Bottom and 1=Bottom-Top

	MADCTL_BGR = 0x08 // Blue-Green-Red pixel order
};

#define CommandData(c)   c,(CLR_UINT8 *)(CLR_UINT8[c])  // Macro to simplify visualisation of passing pointer to parameters;

bool Display::Initialize()
{
	// Define the LCD/TFT resolution
	DisplayAttributes::Orientation = DisplayOrientation::PORTRAIT;
	DisplayAttributes::PowerSave = PowerSaveState::NORMAL;
	DisplayAttributes::Height = 320;
	DisplayAttributes::Width = 240;
	DisplayAttributes::BitsPerPixel = 16;
	DisplayAttributes::LongerSide = 320;
	DisplayAttributes::ShorterSide = 240;

	// Initialize ILI9341 registers

	CLR_UINT8 CMD_Power_Control_A_Data[] = { 0x39, 0x2C, 0x00, 0x34, 0x02 };
	CLR_UINT8 CMD_Power_Control_B_Data[] = { 0x00, 0xC1, 0X30 };
	CLR_UINT8  CMD_Driver_Timing_Control_A_Data[] = { 0x85, 0x01, 0x79 };
	CLR_UINT8  CMD_Driver_Timing_Control_B_Data[] = { 0x00, 0x00 };
	CLR_UINT8  CMD_Power_On_Sequence_Data[] = { 0x64, 0x03, 0X12, 0X81 };
	CLR_UINT8  CMD_Pump_Ratio_Control_Data[] = { 0x20 };
	CLR_UINT8  CMD_Power_Control_1_Data[] = { 0x26 };
	CLR_UINT8  CMD_Power_Control_2_Data[] = { 0x11 };
	CLR_UINT8  CMD_VCOM_Control_1_Data[] = { 0x35, 0x3E };
	CLR_UINT8  CMD_VCOM_Control_2_Data[] = { 0xBE };
	CLR_UINT8  CMD_Memory_Access_Control_Data[] = { 0x28 };  // Portrait?
	CLR_UINT8  CMD_Pixel_Format_Set_Data[] = { 0x55 };   // 0x55 -> 16 bit 
	CLR_UINT8  CMD_Frame_Rate_Control_Normal_Data[] = { 0x00, 0x1B };
	CLR_UINT8  CMD_Display_Function_Control_Data[] = { 0x0A, 0x82, 0x27, 0x00 };
	CLR_UINT8  CMD_Enable_3G_Data[] = { 0x08 };
	CLR_UINT8  CMD_Gamma_Set_Data[] = { 0x01 }; // Gamma curve selected (0x01, 0x02, 0x04, 0x08)
	CLR_UINT8  CMD_Positive_Gamma_Correction_Data[] = { 0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00 }; //gamma set 4
	CLR_UINT8  CMD_Negative_Gamma_Correction_Data[] = { 0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F };
	CLR_UINT8  CMD_Column_Address_Set_Data[] = { 0x00, 0x00, 0x00, 0xEF };  // Size = 239
	CLR_UINT8  CMD_Page_Address_Set_Data[] = { 0x00, 0x00, 0x01, 0x3f };  // Size = 319
	CLR_UINT8  CMD_Entry_Mode_Set_Data[] = { 0x07 };  // Entry mode set
	

	DisplayInterface::SendCommand(CMD_SOFTWARE_RESET);
	DisplayInterface::DisplayCommandDelay(20);																 // Send Sleep Out command to display : no parameter
	DisplayInterface::SendCommand(CMD_Display_OFF);
	DisplayInterface::SendCommandAndData(CMD_Power_Control_A, CMD_Power_Control_A_Data, 5);
	DisplayInterface::SendCommandAndData(CMD_Power_Control_B, CMD_Power_Control_B_Data, 3);
	DisplayInterface::SendCommandAndData(CMD_Driver_Timing_Control_A, CMD_Driver_Timing_Control_A_Data, 3);
	DisplayInterface::SendCommandAndData(CMD_Driver_Timing_Control_B, CMD_Driver_Timing_Control_B_Data, 2);
	DisplayInterface::SendCommandAndData(CMD_Power_On_Sequence, CMD_Power_On_Sequence_Data, 4);
	DisplayInterface::SendCommandAndData(CMD_Pump_Ratio_Control, CMD_Pump_Ratio_Control_Data, 1);
	DisplayInterface::SendCommandAndData(CMD_Power_Control_1, CMD_Power_Control_1_Data, 1);
	DisplayInterface::SendCommandAndData(CMD_Power_Control_2, CMD_Power_Control_2_Data, 1);
	DisplayInterface::SendCommandAndData(CMD_VCOM_Control_1, CMD_VCOM_Control_1_Data, 2);
	DisplayInterface::SendCommandAndData(CMD_VCOM_Control_2, CMD_VCOM_Control_2_Data, 1);
	DisplayInterface::SendCommandAndData(CMD_Memory_Access_Control, CMD_Memory_Access_Control_Data, 1);  // Portrait?
	DisplayInterface::SendCommandAndData(CMD_Pixel_Format_Set, CMD_Pixel_Format_Set_Data, 1);   // 0x55 -> 16 bit 
	DisplayInterface::SendCommandAndData(CMD_Frame_Rate_Control_Normal, CMD_Frame_Rate_Control_Normal_Data, 2);
	DisplayInterface::SendCommandAndData(CMD_Display_Function_Control, CMD_Display_Function_Control_Data, 4);
	DisplayInterface::SendCommandAndData(CMD_Enable_3G, CMD_Enable_3G_Data, 1);
	DisplayInterface::SendCommandAndData(CMD_Gamma_Set, CMD_Gamma_Set_Data, 1); // Gamma curve selected (0x01, 0x02, 0x04, 0x08)
	DisplayInterface::SendCommandAndData(CMD_Positive_Gamma_Correction, CMD_Positive_Gamma_Correction_Data, 15); //gamma set 4
	DisplayInterface::SendCommandAndData(CMD_Negative_Gamma_Correction, CMD_Negative_Gamma_Correction_Data, 15);
	DisplayInterface::DisplayCommandDelay(120);																 // Send Sleep Out command to display : no parameter
	DisplayInterface::SendCommandAndData(CMD_Column_Address_Set, CMD_Column_Address_Set_Data, 4);  // Size = 239
	DisplayInterface::SendCommandAndData(CMD_Page_Address_Set, CMD_Page_Address_Set_Data, 4);  // Size = 319
	DisplayInterface::SendCommand(CMD_Memory_Write);
	DisplayInterface::SendCommandAndData(CMD_Entry_Mode_Set, CMD_Entry_Mode_Set_Data, 1);  // Entry mode set
	DisplayInterface::SendCommand(CMD_Sleep_Out);
	DisplayInterface::DisplayCommandDelay(120);																 // Send Sleep Out command to display : no parameter
	DisplayInterface::SendCommand(CMD_Display_ON);
	DisplayInterface::DisplayCommandDelay(120);																 // Send Sleep Out command to display : no parameter
	DisplayInterface::SendCommand(CMD_NOP);   // End of sequence
	return true;
}
bool Display::Uninitialize()
{
	Clear();
	// Anything else to Uninitialize?
	return TRUE;
}
bool Display::SetWindow(CLR_UINT16 x1, CLR_UINT16 y1, CLR_UINT16 x2, CLR_UINT16 y2)
{
	CLR_UINT16 Addr1, Addr2;

	switch (DisplayAttributes::Orientation)
	{
	default:
		// Invalid! Fall through to portrait mode
	case PORTRAIT:
		Addr1 = x1;
		Addr2 = y1;
		break;
	case PORTRAIT180:
		Addr1 = (CLR_UINT16)(DisplayAttributes::ShorterSide - 1 - x1);
		Addr2 = (CLR_UINT16)(DisplayAttributes::LongerSide - 1 - y1);
		y1 = (CLR_UINT16)(DisplayAttributes::LongerSide - 1 - y2);
		y2 = Addr2;
		break;
	case LANDSCAPE:
		Addr1 = (CLR_UINT16)(DisplayAttributes::ShorterSide - 1 - y1);
		Addr2 = x1;
		y1 = x1;
		y2 = x2;
		break;
	case LANDSCAPE180:
		Addr1 = y1;
		Addr2 = (CLR_UINT16)(DisplayAttributes::ShorterSide - 1 - x1);    // pack X-Values into one word
		y1 = (CLR_UINT16)(DisplayAttributes::LongerSide - 1 - x2);
		y2 = Addr2;
		break;
	}

	CLR_UINT8  CMD_Column_Address_Set_Data[4];
	CMD_Column_Address_Set_Data[0] = (Addr1 >> 8) & 0xFF;
	CMD_Column_Address_Set_Data[1] = Addr1 & 0xFF;
	CMD_Column_Address_Set_Data[2] = (Addr2 >> 8) & 0xFF;
	CMD_Column_Address_Set_Data[3] = Addr2 & 0xFF;

	CLR_UINT8  CMD_Page_Address_Set_Data[4];
	CMD_Page_Address_Set_Data[0] = (y1 >> 8) & 0xFF;
	CMD_Page_Address_Set_Data[1] = y1 & 0xFF;
	CMD_Page_Address_Set_Data[2] = (y2 >> 8) & 0xFF;
	CMD_Page_Address_Set_Data[3] = y2 & 0xFF;

	DisplayInterface::SendCommandAndData(CMD_Column_Address_Set, CMD_Column_Address_Set_Data, 4); 
	DisplayInterface::SendCommandAndData(CMD_Page_Address_Set, CMD_Page_Address_Set_Data, 4);  
	DisplayInterface::SendCommand(CMD_Memory_Write);



	return true;
}
void Display::PowerSave(PowerSaveState powerState)
{
	CLR_UINT8 CMD_POWER_STATE_Data_ON[] = { 0x0000 };
	CLR_UINT8 CMD_POWER_STATE_Data_SLEEP[] = { 0x0001 };
	switch (powerState)
	{
	default:
		// illegal fall through to Power on
	case PowerSaveState::NORMAL:
		DisplayInterface::SendCommandAndData(CMD_POWER_STATE, CMD_POWER_STATE_Data_ON, 1);  // leave sleep mode
		break;
	case PowerSaveState::SLEEP:
		DisplayInterface::SendCommandAndData(CMD_POWER_STATE, CMD_POWER_STATE_Data_SLEEP, 1);  // enter sleep mode
		break;
	}
	return;
}
void Display::Clear()
{
	//reset the cursor pos to the begining
	// Clear the ILI9341 controller 

}
void Display::DisplayBrightness(CLR_INT16 brightness)
{
	_ASSERTE( brightness >= 0 && brightness <= 100);
	CLR_UINT8  CMD_Write_Display_Brightness_Data[] = { (CLR_UINT8)brightness };
	DisplayInterface::SendCommandAndData(CMD_Write_Display_Brightness, CMD_Write_Display_Brightness_Data, 1);
}
void Display::BitBlt(int width, int height, int widthInWords, CLR_UINT32 data[])
{
	_ASSERTE(width == (int)DisplayAttributes::Width);
	_ASSERTE(height == (int)DisplayAttributes::Height);
	_ASSERTE(widthInWords == width / (int)PixelsPerWord());

	BitBltEx(0, 0, width, height, data);
}
void Display::BitBltEx(int x, int y, int width, int height, CLR_UINT32 data[])
{
	ASSERT((x >= 0) && ((x + width) <= DisplayAttributes::Width));
	ASSERT((y >= 0) && ((y + height) <= DisplayAttributes::Height));

	CLR_UINT16* StartOfLine_src = (CLR_UINT16*)& data[0];
	SetWindow(x, y, (x + width - 1), (y + height - 1));

	CLR_UINT16 offset = (y * DisplayAttributes::Width) + x;
	StartOfLine_src += offset;



}
CLR_UINT32 Display::PixelsPerWord()
{
	return (32 / DisplayAttributes::BitsPerPixel);
}
CLR_UINT32 Display::WidthInWords()
{
	return ((DisplayAttributes::Width + (PixelsPerWord() - 1)) / PixelsPerWord());
}
CLR_UINT32 Display::SizeInWords()
{
	return (WidthInWords() * DisplayAttributes::Height);
}
CLR_UINT32 Display::SizeInBytes()
{
	return (SizeInWords() * sizeof(CLR_UINT32));
}
CLR_INT32 Display::GetWidth()
{
	return DisplayAttributes::Width;
}
CLR_INT32 Display::GetHeight()
{
	return DisplayAttributes::Height;
}
CLR_INT32 Display::GetBitsPerPixel()
{
	return DisplayAttributes::BitsPerPixel;
}
CLR_UINT32 Display::ConvertColor(CLR_UINT32 color)
{
	// Only require code if there is a requirement not already supported by the core.
	// 16Bits per pixel is supported by core software which is use by this ILI9341 implementation.
	// 18 bits per pixel colour is possible on ILI9341 controller but would require 
	// changes to the InitializeDisplayRegisters() routine and Graphics memory used
	return color;
}
CLR_INT32 Display::GetOrientation()
{
	return DisplayAttributes::Orientation;
}
bool Display::ChangeOrientation(DisplayOrientation newOrientation)
{
	DisplayAttributes::Orientation = newOrientation;
	CLR_UINT8  CMD_Memory_Access_Control_Data_Portrait[] = { 0x48 };
	CLR_UINT8  CMD_Memory_Access_Control_Data_Portrait180[] = { 0x88 };
	CLR_UINT8  CMD_Memory_Access_Control_Data_Landscape[] = { 0xE8 };
	CLR_UINT8  CMD_Memory_Access_Control_Data_Landscape180[] = { 0x28 };

	switch (newOrientation)
	{
	default:
		// Invalid! Fall through to portrait mode
	case DisplayOrientation::PORTRAIT:
		DisplayAttributes::Height = DisplayAttributes::LongerSide;
		DisplayAttributes::Width = DisplayAttributes::ShorterSide;
		DisplayInterface::SendCommandAndData(CMD_Memory_Access_Control, CMD_Memory_Access_Control_Data_Portrait, 1);
		break;
	case DisplayOrientation::PORTRAIT180:
		DisplayAttributes::Height = DisplayAttributes::LongerSide;
		DisplayAttributes::Width = DisplayAttributes::ShorterSide;
		DisplayInterface::SendCommandAndData(CMD_Memory_Access_Control, CMD_Memory_Access_Control_Data_Portrait180, 1); /* X and Y axes non-inverted */
		break;
	case DisplayOrientation::LANDSCAPE:
		DisplayAttributes::Height = DisplayAttributes::ShorterSide;
		DisplayAttributes::Width = DisplayAttributes::LongerSide;
		DisplayInterface::SendCommandAndData(CMD_Memory_Access_Control, CMD_Memory_Access_Control_Data_Landscape, 1); /* Invert X and Y axes */
		break;
	case DisplayOrientation::LANDSCAPE180:
		DisplayAttributes::Height = DisplayAttributes::ShorterSide;
		DisplayAttributes::Width = DisplayAttributes::LongerSide;
		DisplayInterface::SendCommandAndData(CMD_Memory_Access_Control, CMD_Memory_Access_Control_Data_Landscape180, 1); /* Invert X and Y axes */
		break;
	}
	return true;
}
//CLR_UINT32* Display::GetFrameBuffer()
//{
//	return g_FrameBuffer;
//}



