
#include "nanoHAL.h"
#include "nanoCLR_Types.h"
#include "Display_driver.h"
#include "Display_functions.h"
#include "Cpu_To_Graphics_Display.h"

#define DisplayData(c)   c,(CLR_UINT8 *)(CLR_UINT8[c])  // Macro to simplify visualisation of passing pointer to parameters

extern UI g_UI;

bool Display_Driver::SetWindow(CLR_UINT16 x1, CLR_UINT16 y1, CLR_UINT16 x2, CLR_UINT16 y2)
{
	CLR_UINT16 x1_x2;
	CLR_UINT16 Addr1, Addr2;

	switch (g_UI.lcd_orientation)
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
	(void)x1_x2;
	//g_Cpu_Display_Driver.SetWindowSize(g_ILI9341_Display_Driver.lcd_orientation,x1_x2, y1,y2);

	return TRUE;
}
bool Display_Driver::Initialize()
{

	// Enable CMD2 to access vendor specific commands
	// Enter in command 2 mode and set EXTC to enable address shift function (0x00)
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);
	g_Cpu_Display_Driver.SendData(DisplayData(4) { 0x80, 0x09, 0x01, 0xFF }, 4);

	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::CMD_Power_Control_B, { 0x00, 0x83, 0X30 });
	g_Cpu_Display_Driver.SendData(DisplayData(3) { 0x00, 0x83, 0X30 });

	g_Cpu_Display_Driver.SendCommand(CMD_Power_On_Sequence);
	g_Cpu_Display_Driver.SendData(DisplayData(4) { 0x64, 0x03, 0X12, 0X81 });

	g_Cpu_Display_Driver.SendCommand(CMD_Driver_Timing_Control_A);
	g_Cpu_Display_Driver.SendData(DisplayData(3 ) { 0x85, 0x01, 0x79 });

	g_Cpu_Display_Driver.SendCommand(CMD_Power_Control_A);
	g_Cpu_Display_Driver.SendData(DisplayData(5) { 0x39, 0x2C, 0x00, 0x34, 0x02 });

	g_Cpu_Display_Driver.SendCommand(CMD_Pump_Ratio_Control);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x20 });

	g_Cpu_Display_Driver.SendCommand(CMD_Driver_Timing_Control_B);
	g_Cpu_Display_Driver.SendData(DisplayData(2) { 0x00, 0x00 });

	g_Cpu_Display_Driver.SendCommand(CMD_Power_Control_1);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x26 });

	g_Cpu_Display_Driver.SendCommand(CMD_Power_Control_2);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x11 });

	g_Cpu_Display_Driver.SendCommand(CMD_VCOM_Control);
	g_Cpu_Display_Driver.SendData(DisplayData(2) { 0x35, 0x3E });

	g_Cpu_Display_Driver.SendCommand(CMD_VCOM_Control_2);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0xBE });

	g_Cpu_Display_Driver.SendCommand(CMD_Memory_Access_Control);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x28 });

	g_Cpu_Display_Driver.SendCommand(CMD_Pixel_Format_Set);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x55 });

	g_Cpu_Display_Driver.SendCommand(CMD_Frame_Rate_Control_Normal);
	g_Cpu_Display_Driver.SendData(DisplayData(2) { 0x00, 0x1B });

	g_Cpu_Display_Driver.SendCommand(CMD_Enable_3G);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x08 });

	g_Cpu_Display_Driver.SendCommand(CMD_Gamma_Set);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x01 });

	g_Cpu_Display_Driver.SendCommand(CMD_Positive_Gamma_Correction);
	g_Cpu_Display_Driver.SendData(DisplayData(15) { 0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00 });

	g_Cpu_Display_Driver.SendCommand(CMD_Negative_Gamma_Correction);
	g_Cpu_Display_Driver.SendData(DisplayData(15) { 0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F });

	g_Cpu_Display_Driver.SendCommand(CMD_Column_Address_Set);
	g_Cpu_Display_Driver.SendData(DisplayData(4) { 0x00, 0x00, 0x00, 0xEF });

	g_Cpu_Display_Driver.SendCommand(CMD_Page_Address_Set);
	g_Cpu_Display_Driver.SendData(DisplayData(4) { 0x00, 0x00, 0x01, 0x3f });

	g_Cpu_Display_Driver.SendCommand(CMD_Memory_Write);
	g_Cpu_Display_Driver.SendData(DisplayData(0) { 0 });

	g_Cpu_Display_Driver.SendCommand(CMD_Entry_Mode_Set);
	g_Cpu_Display_Driver.SendData(DisplayData(1) { 0x07 });

	g_Cpu_Display_Driver.SendCommand(CMD_Display_Function_Control);
	g_Cpu_Display_Driver.SendData(DisplayData(4) { 0x0A, 0x82, 0x27, 0x00 });

	g_Cpu_Display_Driver.SendCommand(CMD_Sleep_Out);
	g_Cpu_Display_Driver.SendData(DisplayData(0) { 0x80 });

	g_Cpu_Display_Driver.SendCommand(CMD_Display_ON);
	g_Cpu_Display_Driver.SendData(DisplayData(0) { 0x80 });


	// Enter ORISE Command 2
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80); // Shift address to 0x80
	g_Cpu_Display_Driver.SendData(DisplayData(3) { 0x80, 0x09, 0xFF });

	// SD_PCH_CTRL - 0xC480h - 129th parameter - Default 0x00
	// Set SD_PT -> Source output level during porch and non-display area to GND
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	g_Cpu_Display_Driver.SendCommand(0xC4, 0x30);
	osDelay(10);
	// Not documented
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x8A);
	g_Cpu_Display_Driver.SendCommand(0xC4, 0x40);
	osDelay(10);

	// PWR_CTRL4 - 0xC4B0h - 178th parameter - Default 0xA8
	// Set gvdd_en_test -> enable GVDD test mode
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB1);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0xA9);

	// PWR_CTRL2 - 0xC590h - 146th parameter - Default 0x79
	// Set pump 4 vgh voltage  -> from 15.0v down to 13.0v
	// Set pump 5 vgh voltage   -> from -12.0v downto -9.0v
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x91);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0x34);

	/* P_DRV_M - 0xC0B4h - 181th parameter - Default 0x00 */
	/* -> Column inversion                                */
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB4);
	g_Cpu_Display_Driver.SendCommand(0xC0, 0x50);

	// VCOMDC - 0xD900h - 1st parameter - Default 0x39h
	// VCOM Voltage settings -> from -1.0000v downto -1.2625v 
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);
	g_Cpu_Display_Driver.SendCommand(0xD9, 0x4E);

	/* Oscillator adjustment for Idle/Normal mode (LPDT only) set to 65Hz (default is 60Hz) */
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x81);
	g_Cpu_Display_Driver.SendCommand(0xC1, 0x66);

	/* Video mode internal */
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA1);
	g_Cpu_Display_Driver.SendCommand(0xC1, 0x08);

	// PWR_CTRL2 - 0xC590h - 147h parameter - Default 0x00
	// Set pump 4&5 x6  -> ONLY VALID when PUMP4_EN_ASDM_HV = "0"
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x92);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0x01);

	// PWR_CTRL2 - 0xC590h - 150th parameter - Default 0x33h
	// Change pump4 clock ratio -> from 1 line to 1/2 line
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x95);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0x34);

	// GVDD/NGVDD settings
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);
	g_Cpu_Display_Driver.SendData(DisplayData(3) { 0x79, 0x79, 0xD8 }, 3);

	// PWR_CTRL2 - 0xC590h - 149th parameter - Default 0x33h
	// Rewrite the default value !
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x94);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0x33);

	// Panel display timing Setting 3
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA3);
	g_Cpu_Display_Driver.SendCommand(0xC0, 0x1B);

	// Power control 1
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x82);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0x83);

	// Source driver precharge */
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x81);
	g_Cpu_Display_Driver.SendCommand(0xC4, 0x83);
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA1);
	g_Cpu_Display_Driver.SendCommand(0xC1, 0x0E);
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA6);
	g_Cpu_Display_Driver.SendData(DisplayData(3) { 0x00, 0x01, 0xB3 });



	// GOAVST
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	g_Cpu_Display_Driver.SendData(DisplayData(7) { 0x85, 0x01, 0x00, 0x84, 0x01, 0x00, 0xCE });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA0);
	g_Cpu_Display_Driver.SendData(DisplayData(15) { 0x18, 0x04, 0x03, 0x39, 0x00, 0x00, 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00, 0xCE });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB0);
	g_Cpu_Display_Driver.SendData(DisplayData(15) { 0x18, 0x02, 0x03, 0x3B, 0x00, 0x00, 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00, 0xCE });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xC0);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0xCF });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xD0);
	g_Cpu_Display_Driver.SendCommand(0xCF, 0x00);
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x90);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA0);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB0);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xC0);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xD0);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xE0);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xF0);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCB });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x80);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0x00, 0x26, 0x09, 0x0B, 0x01, 0x25, 0x00, 0x00, 0x00, 0x00, 0xCC });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x90);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02, 0xCC });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xA0);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB0);
	g_Cpu_Display_Driver.SendData(DisplayData(11) { 0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00, 0xCC });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xC0);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01, 0xCC });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xD0);
	g_Cpu_Display_Driver.SendData(DisplayData(16) { 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC });

	/////////////////////////////////////////////////////////////////////////////
	// PWR_CTRL1 - 0xc580h - 130th parameter - default 0x00
	// Pump 1 min and max DM
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0x81);
	g_Cpu_Display_Driver.SendCommand(0xC5, 0x66);
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_NOP, 0xB6);
	g_Cpu_Display_Driver.SendCommand(0xF5, 0x06);
	/////////////////////////////////////////////////////////////////////////////

	// Exit CMD2 mode
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);
	g_Cpu_Display_Driver.SendData(DisplayData(4) { 0xFF, 0xFF, 0xFF, 0xFF });

	//*************************************************************************** 
	// Standard DCS Initialization TO KEEP CAN BE DONE IN HSDT                   
	//*************************************************************************** 
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);  // NOP - goes back to DCS std command ?
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);  // Gamma correction 2.2+ table (HSDT possible)
	g_Cpu_Display_Driver.SendData(DisplayData(17) { 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE1 });
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);  // Gamma correction 2.2- table (HSDT possible)
	g_Cpu_Display_Driver.SendData(DisplayData(17) { 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE2 });
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_SLPOUT, 0x00);    // Send Sleep Out command to display : no parameter
	osDelay(120);                             // Wait for sleep out exit

	uint32_t ColourCoding = PixelFormat::ILI9341_FORMAT_RBG565;
	switch (ColourCoding)
	{
	case ILI9341_FORMAT_RBG565:                        // Set Pixel color format to RGB565
		g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_COLMOD, ILI9341_COLMOD_RGB565);
		break;
	case ILI9341_FORMAT_RGB888:                        // Set Pixel color format to RGB888
		g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_COLMOD, ILI9341_COLMOD_RGB888);
		break;
	default:
		break;
	}
	if (g_ILI9341_Display_Driver.lcd_orientation == LANDSCAPE)  //  By default the orientation mode is portrait
	{
		// CASET value (Column Address Set) : X direction LCD GRAM boundaries
		// depending on LCD orientation mode and PASET value (Page Address Set) : Y direction
		// LCD GRAM boundaries depending on LCD orientation mode
		// XS[15:0] = 0x000 = 0, XE[15:0] = 0x31F = 799 for landscape mode : apply to CASET
		// YS[15:0] = 0x000 = 0, YE[15:0] = 0x31F = 799 for portrait mode : : apply to PASET
		g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_MADCTR, ILI9341_MADCTR_MODE_LANDSCAPE);
		g_Cpu_Display_Driver.SendData(DisplayData(5) { 0x00, 0x00, 0x03, 0x1F, ILI9341_Commands::ILI9341_CMD_CASET });
		// XS[15:0] = 0x000 = 0, XE[15:0] = 0x1DF = 479 for portrait mode : apply to CASET
		// YS[15:0] = 0x000 = 0, YE[15:0] = 0x1DF = 479 for landscape mode : apply to PASET
		g_Cpu_Display_Driver.SendData(DisplayData(5) { 0x00, 0x00, 0x01, 0xDF, ILI9341_Commands::ILI9341_CMD_PASET });
	}
	// CABC : Content Adaptive Backlight Control section start >>
	// Note : defaut is 0 (lowest Brightness), 0xFF is highest Brightness, try 0x7F : intermediate value
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_WRDISBV, 0x7F);
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_WRCTRLD, 0x2C);        // defaut is 0, try 0x2C - Brightness Control Block, Display Dimming & BackLight on */
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_WRCABC, 0x02);         // defaut is 0, try 0x02 - image Content based Adaptive Brightness [Still Picture]
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_WRCABCMB, 0xFF);       // defaut is 0 (lowest Brightness), 0xFF is highest Brightness
	// CABC : Content Adaptive Backlight Control section end <</
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_DISPON, 0x00);         // Send Command Display On
	g_Cpu_Display_Driver.SendCommand(ILI9341_CMD_NOP, 0x00);  // NOP
	// Send Command GRAM memory write (no parameters) : this initiates frame write via other DSI commands sent by/
	// DSI host from LTDC incoming pixels in video mode/
	g_Cpu_Display_Driver.SendCommand(ILI9341_Commands::ILI9341_CMD_RAMWR, 0x00);

	return TRUE;
}
bool Display_Driver::Uninitialize()
{
	Clear();
	//FIXME: ??
	return TRUE;
}
void Display_Driver::PowerSave(bool On)
{

	// FIXME: eliminate unused by creating dummy use of on
	if (On)
	{
		g_Cpu_Display_Driver.SendCommand(1);
	}
	else
	{
		g_Cpu_Display_Driver.SendCommand(2);
	}
	return;
}
void Display_Driver::Clear()
{
	//reset the cursor pos to the begining
	ILI9341_Driver.m_cursor = 0;

	// TODO FIXME
	//g_Cpu_Display_Driver.Clear();

}
void Display_Driver::BitBltEx(int x, int y, int width, int height, CLR_UINT32 data[])
{
	ASSERT((x >= 0) && ((x + width) <= LCD_SCREEN_WIDTH));
	ASSERT((y >= 0) && ((y + height) <= LCD_SCREEN_HEIGHT));

	CLR_UINT16* StartOfLine_src = (CLR_UINT16*)& data[0];
	SetWindow(x, y, (x + width - 1), (y + height - 1));

	CLR_UINT16 offset = (y * g_ILI9341_Config.Width) + x;
	StartOfLine_src += offset;

	while (height--)
	{
		//CLR_UINT16 * src;
		//int      Xcnt;
		//src = StartOfLine_src;
		//Xcnt = width;
		//while (Xcnt--)
		//{
		//    // SendDataWord(*src++);

		//}
		//StartOfLine_src += g_ILI9341_Config.Width;
	}
}
void Display_Driver::BitBlt(int width, int height, int widthInWords, CLR_UINT32 data[])
{
	_ASSERTE(width == (int)LCD_GetWidth());
	_ASSERTE(height == (int)LCD_GetHeight());
	_ASSERTE(widthInWords == width / (int)PixelsPerWord());

	BitBltEx(0, 0, width, height, data);
}
void Display_Driver::WriteChar(unsigned char c, int row, int col)
{
	// MUNEEB - Font_Width refers to font 8x8 or 8x15...so limiting it to 8x8.  tinyclr.proj defines that we are using 8x8
	//int width = Font_Width();
	//int height = Font_Height();
	int width = 8;
	int height = 8;

	// convert to LCD pixel coordinates
	row *= height;
	col *= width;

	if (row > (int)(ILI9341_Config.Height - height)) return;
	if (col > (int)(ILI9341_Config.Width - width)) return;

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
		// g_Cpu_Display_Driver.DrawPixel(col,row,data[i);
	}
}
void Display_Driver::WriteFormattedChar(unsigned char c)
{
	if (c < 32)
	{
		switch (c)
		{
		case '\b':                      /* backspace, clear previous char and move cursor back */
			if ((ILI9341_Driver.m_cursor % TextColumns()) > 0)
			{
				ILI9341_Driver.m_cursor--;
				WriteChar(' ', ILI9341_Driver.m_cursor / TextColumns(), ILI9341_Driver.m_cursor % TextColumns());
			}
			break;

		case '\f':                      /* formfeed, clear screen and home cursor */
			//Clear();
			ILI9341_Driver.m_cursor = 0;
			break;

		case '\n':                      /* newline */
			ILI9341_Driver.m_cursor += TextColumns();
			ILI9341_Driver.m_cursor -= (ILI9341_Driver.m_cursor % TextColumns());
			break;

		case '\r':                      /* carriage return */
			ILI9341_Driver.m_cursor -= (ILI9341_Driver.m_cursor % TextColumns());
			break;

		case '\t':                      /* horizontal tab */
			ILI9341_Driver.m_cursor += (Font_TabWidth() - ((ILI9341_Driver.m_cursor % TextColumns()) % Font_TabWidth()));
			// deal with line wrap scenario
			if ((ILI9341_Driver.m_cursor % TextColumns()) < (CLR_UINT32)Font_TabWidth())
			{
				// bring the cursor to start of line
				ILI9341_Driver.m_cursor -= (ILI9341_Driver.m_cursor % TextColumns());
			}
			break;

		case '\v':                      /* vertical tab */
			ILI9341_Driver.m_cursor += TextColumns();
			break;

		default:
			//FIXME:   DEBUTRACE2(TRACE_ALWAYS, "Unrecognized control character in LCD_WriteChar: %2u (0x%02x)\r\n", (unsigned int)c, (unsigned int)c);
			break;
		}
	}
	else
	{
		WriteChar(c, ILI9341_Driver.m_cursor / TextColumns(), ILI9341_Driver.m_cursor % TextColumns());
		ILI9341_Driver.m_cursor++;
	}

	if (ILI9341_Driver.m_cursor >= (TextColumns() * TextRows()))
	{
		ILI9341_Driver.m_cursor = 0;
	}
}
CLR_UINT32 Display_Driver::PixelsPerWord()
{
	return ((8 * sizeof(CLR_UINT32)) / g_ILI9341_Config.BitsPerPixel);
}
CLR_UINT32 Display_Driver::TextRows()
{
	return (g_ILI9341_Config.Height / Font_Height());
}
CLR_UINT32 Display_Driver::TextColumns()
{
	return (g_ILI9341_Config.Width / Font_Width());
}
CLR_UINT32 Display_Driver::WidthInWords()
{
	return ((g_ILI9341_Config.Width + (PixelsPerWord() - 1)) / PixelsPerWord());
}
CLR_UINT32 Display_Driver::SizeInWords()
{
	return (WidthInWords() * g_ILI9341_Config.Height);
}
CLR_UINT32 Display_Driver::SizeInBytes()
{
	return (SizeInWords() * sizeof(CLR_UINT32));
}
