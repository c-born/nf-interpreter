//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "nanoCLR_Types.h"
#include "Display.h"
#include "DisplayInterface.h"
#include "ILI9341_320x240.h"

#define DisplayData(c)   c,(CLR_UINT8 *)(CLR_UINT8[c])  // Macro to simplify visualisation of passing pointer to parameters

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
bool Display::Initialize()
{

	// Enable CMD2 to access vendor specific commands
	// Enter in command 2 mode and set EXTC to enable address shift function (0x00)
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);
	DisplayInterface::SendData(DisplayData(4) { 0x80, 0x09, 0x01, 0xFF }, 4);

	DisplayInterface::SendCommand(ILI9341_Commands::CMD_Power_Control_B, { 0x00, 0x83, 0X30 });
	DisplayInterface::SendData(DisplayData(3) { 0x00, 0x83, 0X30 });

	DisplayInterface::SendCommand(CMD_Power_On_Sequence);
	DisplayInterface::SendData(DisplayData(4) { 0x64, 0x03, 0X12, 0X81 });

	DisplayInterface::SendCommand(CMD_Driver_Timing_Control_A);
	DisplayInterface::SendData(DisplayData(3 ) { 0x85, 0x01, 0x79 });

	DisplayInterface::SendCommand(CMD_Power_Control_A);
	DisplayInterface::SendData(DisplayData(5) { 0x39, 0x2C, 0x00, 0x34, 0x02 });

	DisplayInterface::SendCommand(CMD_Pump_Ratio_Control);
	DisplayInterface::SendData(DisplayData(1) { 0x20 });

	DisplayInterface::SendCommand(CMD_Driver_Timing_Control_B);
	DisplayInterface::SendData(DisplayData(2) { 0x00, 0x00 });

	DisplayInterface::SendCommand(CMD_Power_Control_1);
	DisplayInterface::SendData(DisplayData(1) { 0x26 });

	DisplayInterface::SendCommand(CMD_Power_Control_2);
	DisplayInterface::SendData(DisplayData(1) { 0x11 });

	DisplayInterface::SendCommand(CMD_VCOM_Control);
	DisplayInterface::SendData(DisplayData(2) { 0x35, 0x3E });

	DisplayInterface::SendCommand(CMD_VCOM_Control_2);
	DisplayInterface::SendData(DisplayData(1) { 0xBE });

	DisplayInterface::SendCommand(CMD_Memory_Access_Control);
	DisplayInterface::SendData(DisplayData(1) { 0x28 });

	DisplayInterface::SendCommand(CMD_Pixel_Format_Set);
	DisplayInterface::SendData(DisplayData(1) { 0x55 });

	DisplayInterface::SendCommand(CMD_Frame_Rate_Control_Normal);
	DisplayInterface::SendData(DisplayData(2) { 0x00, 0x1B });

	DisplayInterface::SendCommand(CMD_Enable_3G);
	DisplayInterface::SendData(DisplayData(1) { 0x08 });

	DisplayInterface::SendCommand(CMD_Gamma_Set);
	DisplayInterface::SendData(DisplayData(1) { 0x01 });

	DisplayInterface::SendCommand(CMD_Positive_Gamma_Correction);
	DisplayInterface::SendData(DisplayData(15) { 0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00 });

	DisplayInterface::SendCommand(CMD_Negative_Gamma_Correction);
	DisplayInterface::SendData(DisplayData(15) { 0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F });

	DisplayInterface::SendCommand(CMD_Column_Address_Set);
	DisplayInterface::SendData(DisplayData(4) { 0x00, 0x00, 0x00, 0xEF });

	DisplayInterface::SendCommand(CMD_Page_Address_Set);
	DisplayInterface::SendData(DisplayData(4) { 0x00, 0x00, 0x01, 0x3f });

	DisplayInterface::SendCommand(CMD_Memory_Write);
	DisplayInterface::SendData(DisplayData(0) { 0 });

	DisplayInterface::SendCommand(CMD_Entry_Mode_Set);
	DisplayInterface::SendData(DisplayData(1) { 0x07 });

	DisplayInterface::SendCommand(CMD_Display_Function_Control);
	DisplayInterface::SendData(DisplayData(4) { 0x0A, 0x82, 0x27, 0x00 });

	DisplayInterface::SendCommand(CMD_Sleep_Out);
	DisplayInterface::SendData(DisplayData(0) { 0x80 });

	DisplayInterface::SendCommand(CMD_Display_ON);
	DisplayInterface::SendData(DisplayData(0) { 0x80 });


	// Enter ORISE Command 2
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80); // Shift address to 0x80
	DisplayInterface::SendData(DisplayData(3) { 0x80, 0x09, 0xFF });

	// SD_PCH_CTRL - 0xC480h - 129th parameter - Default 0x00
	// Set SD_PT -> Source output level during porch and non-display area to GND
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	DisplayInterface::SendCommand(0xC4, 0x30);
	osDelay(10);
	// Not documented
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x8A);
	DisplayInterface::SendCommand(0xC4, 0x40);
	osDelay(10);

	// PWR_CTRL4 - 0xC4B0h - 178th parameter - Default 0xA8
	// Set gvdd_en_test -> enable GVDD test mode
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB1);
	DisplayInterface::SendCommand(0xC5, 0xA9);

	// PWR_CTRL2 - 0xC590h - 146th parameter - Default 0x79
	// Set pump 4 vgh voltage  -> from 15.0v down to 13.0v
	// Set pump 5 vgh voltage   -> from -12.0v downto -9.0v
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x91);
	DisplayInterface::SendCommand(0xC5, 0x34);

	/* P_DRV_M - 0xC0B4h - 181th parameter - Default 0x00 */
	/* -> Column inversion                                */
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB4);
	DisplayInterface::SendCommand(0xC0, 0x50);

	// VCOMDC - 0xD900h - 1st parameter - Default 0x39h
	// VCOM Voltage settings -> from -1.0000v downto -1.2625v 
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);
	DisplayInterface::SendCommand(0xD9, 0x4E);

	/* Oscillator adjustment for Idle/Normal mode (LPDT only) set to 65Hz (default is 60Hz) */
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x81);
	DisplayInterface::SendCommand(0xC1, 0x66);

	/* Video mode internal */
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA1);
	DisplayInterface::SendCommand(0xC1, 0x08);

	// PWR_CTRL2 - 0xC590h - 147h parameter - Default 0x00
	// Set pump 4&5 x6  -> ONLY VALID when PUMP4_EN_ASDM_HV = "0"
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x92);
	DisplayInterface::SendCommand(0xC5, 0x01);

	// PWR_CTRL2 - 0xC590h - 150th parameter - Default 0x33h
	// Change pump4 clock ratio -> from 1 line to 1/2 line
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x95);
	DisplayInterface::SendCommand(0xC5, 0x34);

	// GVDD/NGVDD settings
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);
	DisplayInterface::SendData(DisplayData(3) { 0x79, 0x79, 0xD8 }, 3);

	// PWR_CTRL2 - 0xC590h - 149th parameter - Default 0x33h
	// Rewrite the default value !
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x94);
	DisplayInterface::SendCommand(0xC5, 0x33);

	// Panel display timing Setting 3
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA3);
	DisplayInterface::SendCommand(0xC0, 0x1B);

	// Power control 1
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x82);
	DisplayInterface::SendCommand(0xC5, 0x83);

	// Source driver precharge */
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x81);
	DisplayInterface::SendCommand(0xC4, 0x83);
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA1);
	DisplayInterface::SendCommand(0xC1, 0x0E);
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA6);
	DisplayInterface::SendData(DisplayData(3) { 0x00, 0x01, 0xB3 });



	// GOAVST
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	DisplayInterface::SendData(DisplayData(7) { 0x85, 0x01, 0x00, 0x84, 0x01, 0x00, 0xCE });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA0);
	DisplayInterface::SendData(DisplayData(15) { 0x18, 0x04, 0x03, 0x39, 0x00, 0x00, 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00, 0xCE });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB0);
	DisplayInterface::SendData(DisplayData(15) { 0x18, 0x02, 0x03, 0x3B, 0x00, 0x00, 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00, 0xCE });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xC0);
	DisplayInterface::SendData(DisplayData(11) { 0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0xCF });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xD0);
	DisplayInterface::SendCommand(0xCF, 0x00);
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	DisplayInterface::SendData(DisplayData(11) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x90);
	DisplayInterface::SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA0);
	DisplayInterface::SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB0);
	DisplayInterface::SendData(DisplayData(11) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xC0);
	DisplayInterface::SendData(DisplayData(16) { 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xD0);
	DisplayInterface::SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xE0);
	DisplayInterface::SendData(DisplayData(11) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xF0);
	DisplayInterface::SendData(DisplayData(11) { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCB });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	DisplayInterface::SendData(DisplayData(11) { 0x00, 0x26, 0x09, 0x0B, 0x01, 0x25, 0x00, 0x00, 0x00, 0x00, 0xCC });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x90);
	DisplayInterface::SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02, 0xCC });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA0);
	DisplayInterface::SendData(DisplayData(16) { 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB0);
	DisplayInterface::SendData(DisplayData(11) { 0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00, 0xCC });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xC0);
	DisplayInterface::SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01, 0xCC });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xD0);
	DisplayInterface::SendData(DisplayData(16) { 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC });

	/////////////////////////////////////////////////////////////////////////////
	// PWR_CTRL1 - 0xc580h - 130th parameter - default 0x00
	// Pump 1 min and max DM
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x81);
	DisplayInterface::SendCommand(0xC5, 0x66);
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB6);
	DisplayInterface::SendCommand(0xF5, 0x06);
	/////////////////////////////////////////////////////////////////////////////

	// Exit CMD2 mode
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);
	DisplayInterface::SendData(DisplayData(4) { 0xFF, 0xFF, 0xFF, 0xFF });

	//*************************************************************************** 
	// Standard DCS Initialization TO KEEP CAN BE DONE IN HSDT                   
	//*************************************************************************** 
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);  // NOP - goes back to DCS std command ?
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);  // Gamma correction 2.2+ table (HSDT possible)
	DisplayInterface::SendData(DisplayData(17) { 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE1 });
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);  // Gamma correction 2.2- table (HSDT possible)
	DisplayInterface::SendData(DisplayData(17) { 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE2 });
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_SLPOUT, 0x00);    // Send Sleep Out command to display : no parameter
	osDelay(120);                             // Wait for sleep out exit

	uint32_t ColourCoding = PixelFormat::ILI9341_FORMAT_RBG565;
	switch (ColourCoding)
	{
	case ILI9341_FORMAT_RBG565:                        // Set Pixel color format to RGB565
		DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_COLMOD, ILI9341_COLMOD_RGB565);
		break;
	case ILI9341_FORMAT_RGB888:                        // Set Pixel color format to RGB888
		DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_COLMOD, ILI9341_COLMOD_RGB888);
		break;
	default:
		break;
	}
	if (Display::Orientation == LANDSCAPE)  //  By default the orientation mode is portrait
	{
		// CASET value (Column Address Set) : X direction LCD GRAM boundaries
		// depending on LCD orientation mode and PASET value (Page Address Set) : Y direction
		// LCD GRAM boundaries depending on LCD orientation mode
		// XS[15:0] = 0x000 = 0, XE[15:0] = 0x31F = 799 for landscape mode : apply to CASET
		// YS[15:0] = 0x000 = 0, YE[15:0] = 0x31F = 799 for portrait mode : : apply to PASET
		DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_MADCTR, ILI9341_MADCTR_MODE_LANDSCAPE);
		DisplayInterface::SendData(DisplayData(5) { 0x00, 0x00, 0x03, 0x1F, ILI9341_Commands::ILI9341_CMD_CASET });
		// XS[15:0] = 0x000 = 0, XE[15:0] = 0x1DF = 479 for portrait mode : apply to CASET
		// YS[15:0] = 0x000 = 0, YE[15:0] = 0x1DF = 479 for landscape mode : apply to PASET
		DisplayInterface::SendData(DisplayData(5) { 0x00, 0x00, 0x01, 0xDF, ILI9341_Commands::ILI9341_CMD_PASET });
	}
	// CABC : Content Adaptive Backlight Control section start >>
	// Note : defaut is 0 (lowest Brightness), 0xFF is highest Brightness, try 0x7F : intermediate value
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_WRDISBV, 0x7F);
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_WRCTRLD, 0x2C);        // defaut is 0, try 0x2C - Brightness Control Block, Display Dimming & BackLight on */
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_WRCABC, 0x02);         // defaut is 0, try 0x02 - image Content based Adaptive Brightness [Still Picture]
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_WRCABCMB, 0xFF);       // defaut is 0 (lowest Brightness), 0xFF is highest Brightness
	// CABC : Content Adaptive Backlight Control section end <</
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_DISPON, 0x00);         // Send Command Display On
	DisplayInterface::SendCommand(ILI9341_CMD_NOP, 0x00);  // NOP
	// Send Command GRAM memory write (no parameters) : this initiates frame write via other DSI commands sent by/
	// DSI host from LTDC incoming pixels in video mode/
	DisplayInterface::SendCommand(ILI9341_Commands::ILI9341_CMD_RAMWR, 0x00);

	return TRUE;
}
bool Display::Uninitialize()
{
	Clear();
	//FIXME: ??
	return TRUE;
}
void Display::PowerSave(bool On)
{

	// FIXME: eliminate unused by creating dummy use of on
	if (On)
	{
		DisplayInterface::SendCommand(1);
	}
	else
	{
		DisplayInterface::SendCommand(2);
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
		CLR_UINT16 * src;
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
		DisplayInterface::DrawPixel(col,row,data[i);
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
	return ((8 * sizeof(CLR_UINT32)) / Display::BitsPerPixel);
}
CLR_UINT32 Display::TextRows()
{
	return (Display::Height / Font_Height());
}
CLR_UINT32 Display::TextColumns()
{
	return (Display::Width / Font_Width());
}
CLR_UINT32 Display::WidthInWords()
{
	return ((Display::Width + (PixelsPerWord() - 1)) / PixelsPerWord());
}
CLR_UINT32 Display::SizeInWords()
{
	return (WidthInWords() * Display::Height);
}
CLR_UINT32 Display::SizeInBytes()
{
	return (SizeInWords() * sizeof(CLR_UINT32));
}
CLR_INT32 Display::GetWidth()
{
	//Screen is rotated
	return Display::Width;
}
CLR_INT32 Display::GetHeight()
{
	//Screen is rotated
	return Display::Height;
}
CLR_INT32 Display::GetBitsPerPixel()
{
	return Display::BitsPerPixel;
}
CLR_UINT32 Display::GetPixelClockDivider()
{
	return Display::PixelClockDivider;
}
CLR_INT32 Display::GetOrientation()
{
	return Display::Orientation;
}
CLR_UINT32 Display::ConvertColor(CLR_UINT32 color)
{
	return color;
}
