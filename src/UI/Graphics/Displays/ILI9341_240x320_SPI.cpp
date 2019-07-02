//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "nanoCLR_Types.h"
#include "Display.h"
#include "DisplayInterface.h"
#include "ILI9341_320x240.h"


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


//#define LCD_SCREEN_PIXELS_PER_WORD      (32/LCD_SCREEN_BPP)
//#define LCD_SCREEN_WIDTH_IN_WORDS       ((LCD_SCREEN_WIDTH + LCD_SCREEN_PIXELS_PER_WORD - 1) / LCD_SCREEN_PIXELS_PER_WORD)
//#define LCD_SCREEN_SIZE_IN_WORDS        (LCD_SCREEN_WIDTH_IN_WORDS * LCD_SCREEN_HEIGHT)
//#define LCD_SCREEN_SIZE_IN_BYTES        (LCD_SCREEN_SIZE_IN_WORDS * 4)
//
//#define LCD_NO_PIXEL_CLOCK_DIVIDER      0
//
//#define LCD_ORIENTATION	   		  LANDSCAPE
//#define SCREEN_SIZE_LONGER_SIDE   320        // The maximum resolution of longer longer side of physical LCD
//#define SCREEN_SIZE_SHORTER_SIDE  240       // The maximum resolution of  shorter longer side of physical LCD
//

enum ILI9341_Command : CLR_UINT8
{
	CMD_NOP = 0x00,
	CMD_Sleep_Out = 0x11,
	CMD_Gamma_Set = 0x26,
	CMD_Display_ON = 0x29,
	CMD_Column_Address_Set = 0x2A,
	CMD_Page_Address_Set = 0x2B,
	CMD_Memory_Write = 0x2C,
	CMD_Memory_Access_Control = 0x36,
	CMD_Pixel_Format_Set = 0x3A,
	CMD_Frame_Rate_Control_Normal = 0xB1,
	CMD_Display_Function_Control = 0xB6,
	CMD_Entry_Mode_Set = 0xB7,
	CMD_Power_Control_1 = 0xC0,
	CMD_Power_Control_2 = 0xC1,
	CMD_VCOM_Control = 0xC5,
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
//	COLMOD_RGB565
//	COLMOD_RGB888
//	MADCTR_MODE_LANDSCAPE

#define CommandData(c)   c,(CLR_UINT8 *)(CLR_UINT8[c])  // Macro to simplify visualisation of passing pointer to parameters

bool Display::Initialize()
{
	DisplayAttributes::Orientation = DisplayOrientation::PORTRAIT;
	DisplayAttributes::BitsPerPixel = 16;
	DisplayAttributes::PowerSave = PowerSaveState::NORMAL;

	DisplayAttributes::LongerSize = 320;
	DisplayAttributes::ShorterSize = 240;
	DisplayAttributes::Height = 240;
	DisplayAttributes::Width = 320;

	DisplayInterface::SendCommandAndData({ CMD_NOP, 0x00 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Power_Control_B,  0x00, 0x83, 0X30 }, 3);
	DisplayInterface::SendCommandAndData({ CMD_Power_On_Sequence, 0x64, 0x03, 0X12, 0X81 }, 4);
	DisplayInterface::SendCommandAndData({ CMD_Driver_Timing_Control_A,   0x85, 0x01, 0x79 }, 3);
	DisplayInterface::SendCommandAndData({ CMD_Power_Control_A,   0x39, 0x2C, 0x00, 0x34, 0x02 }, 5);
	DisplayInterface::SendCommandAndData({ CMD_Pump_Ratio_Control,  , 0x20 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Driver_Timing_Control_B,   0x00, 0x00 }, 2);
	DisplayInterface::SendCommandAndData({ CMD_Power_Control_1,   0x26 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Power_Control_2,   0x11 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_VCOM_Control,  0x35, 0x3E }, 2);
	DisplayInterface::SendCommandAndData({ CMD_VCOM_Control_2,0xBE }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Memory_Access_Control,0x28 }, 1);

	DisplayInterface::SendCommandAndData({ CMD_Pixel_Format_Set,0x55 }, 1);

	DisplayInterface::SendCommandAndData({ CMD_Frame_Rate_Control_Normal 0x00, 0x1B }, 2);
	DisplayInterface::SendCommandAndData({ CMD_Enable_3G,0x08 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Gamma_Set,0x01 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Positive_Gamma_Correction,0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00 }, 15);
	DisplayInterface::SendCommandAndData({ CMD_Negative_Gamma_Correction,0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F }, 15);

	DisplayInterface::SendCommandAndData({ CMD_Column_Address_Set,0x00, 0x00, 0x00, 0xEF }, 4);
	DisplayInterface::SendCommandAndData({ CMD_Page_Address_Set,0x00, 0x00, 0x01, 0x3f }, 4);

	DisplayInterface::SendCommandAndData({ CMD_Memory_Write,0 }, 0); // ???
	DisplayInterface::SendCommandAndData({ CMD_Entry_Mode_Set, 0x07 }, 1);
	DisplayInterface::SendCommandAndData({ CMD_Display_Function_Control, 0x0A, 0x82, 0x27, 0x00 }, 4);
	DisplayInterface::SendCommandAndData({ CMD_Sleep_Out, 0x80 }, 0); //??
																	 // Send Sleep Out command to display : no parameter
	osDelay(120);

	DisplayInterface::SendCommandAndData({ CMD_Display_ON,0x80 }, 0); //??

	return TRUE;
}
bool Display::Uninitialize()
{
	Clear();
	//FIXME: ??
	return TRUE;
}
bool Display::SetWindow(CLR_UINT16 x1, CLR_UINT16 y1, CLR_UINT16 x2, CLR_UINT16 y2)
{
	CLR_UINT16 x1_x2;
	CLR_UINT16 Addr1, Addr2;

	switch (Display::Orientation)
	{
	default:
		// Invalid! Fall through to portrait mode
	case PORTRAIT:
		Addr1 = x1;
		Addr2 = y1;
		x1_x2 = (CLR_UINT16)((x2 << 8) + x1);   // pack X-Values into one word            
		break;
	case PORTRAIT180:
		Addr1 = (CLR_UINT16)(SCREEN_SIZE_SHORTER_SIDE - 1 - x1);
		Addr2 = (CLR_UINT16)(SCREEN_SIZE_LONGER_SIDE - 1 - y1);
		x1_x2 = (CLR_UINT16)((Addr1 << 8) + (SCREEN_SIZE_SHORTER_SIDE - 1 - x2));    // pack X-Values into one word
		y1 = (CLR_UINT16)(SCREEN_SIZE_LONGER_SIDE - 1 - y2);
		y2 = Addr2;
		break;
	case LANDSCAPE:
		Addr1 = (CLR_UINT16)(SCREEN_SIZE_SHORTER_SIDE - 1 - y1);
		Addr2 = x1;
		x1_x2 = (CLR_UINT16)((Addr1 << 8) + (SCREEN_SIZE_SHORTER_SIDE - 1 - y2));    // pack X-Values into one word
		y1 = x1;
		y2 = x2;
		break;
	case LANDSCAPE180:
		Addr1 = y1;
		Addr2 = (CLR_UINT16)(SCREEN_SIZE_LONGER_SIDE - 1 - x1);    // pack X-Values into one word
		x1_x2 = (CLR_UINT16)((y2 << 8) + y1);
		y1 = (CLR_UINT16)(SCREEN_SIZE_LONGER_SIDE - 1 - x2);
		y2 = Addr2;
		break;
	}

	// TODO FIXME
	//Set Window

	// THIS IS AN EXAMPLE FOR 1289
	//
	// CHANGE FOR
	//
	// ILI9341
	//
	(void)DisplayInterface::SendCommand(0x0044);
	(void)DisplayInterface::((UINT16)x1_x2);
	(void)DisplayInterface::(0x0045);
	(void)DisplayInterface::SendDataWord((UINT16)y1);
	(void)DisplayInterface::SendCmdWord(0x0046);
	(void)DisplayInterface::SendDataWord((UINT16)y2);
	// Set Start Address counter
	(void)DisplayInterface::SendCmdWord(0x004e);
	(void)DisplayInterface::SendDataWord((UINT16)Addr1);
	(void)DisplayInterface::SendCmdWord(0x004f);
	(void)DisplayInterface::SendDataWord((UINT16)Addr2);
	(void)DisplayInterface::SendCmdWord(0x0022);


	return TRUE;
}
void Display::PowerSave(PowerSaveState powerState)
{
	switch (powerState)
	{
	case PowerSaveState::SLEEP:
		DisplayInterface::SendCommand(2);
		break;
	case PowerSaveState::STANDBY:
		DisplayInterface::SendCommand(2);
		break;
	}
	return;
}
void Display::Clear()
{
	//reset the cursor pos to the begining
	Display::m_cursor = 0;

	// TODO FIXME
	//DisplayInterface::Clear();

}
void Display::BitBlt(int width, int height, int widthInWords, CLR_UINT32 data[])
{
	_ASSERTE(width == (int)LCD_GetWidth());
	_ASSERTE(height == (int)LCD_GetHeight());
	_ASSERTE(widthInWords == width / (int)PixelsPerWord());

	BitBltEx(0, 0, width, height, data);
}
void Display::BitBltEx(int x, int y, int width, int height, CLR_UINT32 data[])
{
	ASSERT((x >= 0) && ((x + width) <= LCD_SCREEN_WIDTH));
	ASSERT((y >= 0) && ((y + height) <= LCD_SCREEN_HEIGHT));

	CLR_UINT16* StartOfLine_src = (CLR_UINT16*)& data[0];
	SetWindow(x, y, (x + width - 1), (y + height - 1));

	CLR_UINT16 offset = (y * Display::Width) + x;
	StartOfLine_src += offset;

	while (height--)
	{
		CLR_UINT16* src;
		int      Xcnt;
		src = StartOfLine_src;
		Xcnt = width;
		while (Xcnt--)
		{
			DisplayInterface::SendDataWord(*src++);
		}
		StartOfLine_src += Display::Width;
	}
}
void Display::WriteChar(unsigned char c, int row, int col)
{
	// MUNEEB - Font_Width refers to font 8x8 or 8x15...so limiting it to 8x8.  tinyclr.proj defines that we are using 8x8
	//int width = Font_Width();
	//int height = Font_Height();
	int width = 8;
	int height = 8;

	// convert to LCD pixel coordinates
	row *= height;
	col *= width;

	if (row > (int)(Display::Height - height)) return;
	if (col > (int)(Display::Width - width)) return;

	const CLR_UINT8* font = Font_GetGlyph(c);
	// MUNEEB - SEE NOTE ABOVE
	//CLR_UINT16 data[height*width];
	CLR_UINT16 data[8 * 8];
	int i = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// FIXME: fix to allow compilation, code needs fixing

			// CLR_UINT16 val = ILI9341_COLOUR::LCD_COLOR_BLACK;
			CLR_UINT16 val = 1;
			// the font data is mirrored
			// if ((font[y] & (1 << (width - x - 1))) != 0) val |= ILI9341_COLOUR::LCD_COLOR_GREEN;
			if ((font[y] & (1 << (width - x - 1))) != 0) val |= 1;
			data[i] = val;
			i++;
		}
	}
	SetWindow(col, row, col + width - 1, row + height - 1);
	for (i = 0; i < width * height; i++)
	{
		// TODO FIXME
		(void)data;
		DisplayInterface::DrawPixel(col, row, data[i);
	}
}
void Display::WriteFormattedChar(unsigned char c)
{
	if (c < 32)
	{
		switch (c)
		{
		case '\b':                      /* backspace, clear previous char and move cursor back */
			if ((Display::m_cursor % TextColumns()) > 0)
			{
				Display::m_cursor--;
				WriteChar(' ', Display::m_cursor / TextColumns(), Display::m_cursor % TextColumns());
			}
			break;

		case '\f':                      /* formfeed, clear screen and home cursor */
			//Clear();
			Display::m_cursor = 0;
			break;

		case '\n':                      /* newline */
			Display::m_cursor += TextColumns();
			Display::m_cursor -= (Display::m_cursor % TextColumns());
			break;

		case '\r':                      /* carriage return */
			Display::m_cursor -= (Display::m_cursor % TextColumns());
			break;

		case '\t':                      /* horizontal tab */
			Display::m_cursor += (Font_TabWidth() - ((Display::m_cursor % TextColumns()) % Font_TabWidth()));
			// deal with line wrap scenario
			if ((Display::m_cursor % TextColumns()) < (CLR_UINT32)Font_TabWidth())
			{
				// bring the cursor to start of line
				Display::m_cursor -= (Display::m_cursor % TextColumns());
			}
			break;

		case '\v':                      /* vertical tab */
			Display::m_cursor += TextColumns();
			break;

		default:
			//FIXME:   DEBUTRACE2(TRACE_ALWAYS, "Unrecognized control character in LCD_WriteChar: %2u (0x%02x)\r\n", (unsigned int)c, (unsigned int)c);
			break;
		}
	}
	else
	{
		WriteChar(c, Display::m_cursor / TextColumns(), Display::m_cursor % TextColumns());
		Display::m_cursor++;
	}

	if (Display::m_cursor >= (TextColumns() * TextRows()))
	{
		Display::m_cursor = 0;
	}
}
CLR_UINT32 Display::PixelsPerWord()
{
	return ((8 * sizeof(CLR_UINT32)) / DISPLAY_ATTRIBUTES::BITS_PER_PIXEL);
}
CLR_UINT32 Display::TextRows()
{
	return (Display::Height / Font_Height());
}
CLR_UINT32 Display::TextColumns()
{
	return (DisplayAttributes::Width / Font_Width());
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
	int Width = DisplayAttributes::Width = 320;
	switch (Orientation)
	{
	case DisplayOrientation::LANDSCAPE:
	case DisplayOrientation::LANDSCAPE:
		
	}
	return Display::Width;
}
CLR_INT32 Display::GetHeight()
{
	return DisplayAttributes::Height = 240;
}
CLR_INT32 Display::GetBitsPerPixel()
{
	return DisplayAttributes::BitsPerPixel;
}
CLR_UINT32 Display::GetPixelClockDivider()
{
	return Display::PixelClockDivider;
}
CLR_UINT32 Display::ConvertColor(CLR_UINT32 color)
{
	// Only require code if there is a requirement not already supported by the core
	// 16Bits per pixel is supported by core software and although the ILI9341 supports 
	// 18 bits per pixel colour would require changes to the initialization routine
	return color;
}
CLR_INT32 Display::GetOrientation()
{
	return DisplayAttributes::Orientation;
}
bool Display::ChangeOrientation(DisplayOrientation newOrientation)
{
	DisplayAttributes::Orientation = newOrientation;
	return true;
}



