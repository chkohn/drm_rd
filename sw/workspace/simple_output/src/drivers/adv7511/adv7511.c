/******************************************************************************
*
* (c) Copyright 2011-2012 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "xstatus.h"
#include "adv7511.h"


/*
 * The video input format of the ADV7511 is set to YCbCr, 16-bit, 4:2:2,
 * ID 1 (separate syncs), Style 3. The video output format is set to
 * RGB, 24-bit, 4:4:4, DVI mode.
 *
 * CSC coefficients (registers 0x18 - 0x2F) are taken from tables 40/57
 * of the ADV7511 programmer's guide i.e. converting HDTV YCrCb
 * (16 to 235 or limited range) to RGB (0 to 255 or full range).
 */
#define ADV7511_HDMI_RGB444_LEN  41
IicMsg ADV7511_HdmiRGB444[ADV7511_HDMI_RGB444_LEN] =
{
	{0x41, 0x10}, 	// Power Down Control
					//    R0x41[  6] = PowerDown = 0 (power-up)
	{0xD6, 0xC0}, 	// HPD Control
					//    R0xD6[7:6] = HPD Control = 11 (always high)
	{0x15, 0x01}, 	// Input YCbCr 4:2:2 with separate syncs
	{0x16, 0x3C}, 	// Output format 4:4:4, Input Color Depth = 8
					//    R0x16[  7] = Output Video Format = 0 (4:4:4)
					//    R0x16[5:4] = Input Video Color Depth = 11 (8 bits/color)
					//    R0x16[3:2] = Input Video Style = 11 (style 3)
					//    R0x16[  1] = DDR Input Edge = 0 (falling edge)
					//    R0x16[  0] = Output Color Space = 0 (RGB)
	{0x18, 0xAB}, 	// Color Space Conversion
					//    R0x18[  7] = CSC enable = 1 (CSC enabled)
					//    R0x18[6:5] = CSC Scaling Factor = 01 (+/- 2.0, -8192 - 8190)
					//    R0x18[4:0] = CSC coefficient A1[12:8]
	{0x19, 0x37},	//    R0x19[7:0] = CSC coefficient A1[ 7:0]
	{0x1A, 0x08}, 	//    R0x1A[  5] = CSC coefficient update
					//    R0x1A[4:0] = CSC coefficient A2[12:8]
	{0x1B, 0x00}, 	//    R0x1B[7:0] = CSC coefficient A2[ 7:0]
	{0x1C, 0x00}, 	//    R0x1C[4:0] = CSC coefficient A3[12:8]
	{0x1D, 0x00}, 	//    R0x1D[7:0] = CSC coefficient A3[ 7:0]
	{0x1E, 0x1A}, 	//    R0x1E[4:0] = CSC coefficient A4[12:8]
	{0x1F, 0x86}, 	//    R0x1F[7:0] = CSC coefficient A4[ 7:0]
	{0x20, 0x1A}, 	//    R0x20[4:0] = CSC coefficient B1[12:8]
	{0x21, 0x49}, 	//    R0x21[7:0] = CSC coefficient B1[ 7:0]
	{0x22, 0x08}, 	//    R0x22[4:0] = CSC coefficient B2[12:8]
	{0x23, 0x00}, 	//    R0x23[7:0] = CSC coefficient B2[ 7:0]
	{0x24, 0x1D}, 	//    R0x24[4:0] = CSC coefficient B3[12:8]
	{0x25, 0x3F}, 	//    R0x25[7:0] = CSC coefficient B3[ 7:0]
	{0x26, 0x04}, 	//    R0x26[4:0] = CSC coefficient B4[12:8]
	{0x27, 0x22}, 	//    R0x27[7:0] = CSC coefficient B4[ 7:0]
	{0x28, 0x00}, 	//    R0x28[4:0] = CSC coefficient C1[12:8]
	{0x29, 0x00}, 	//    R0x29[7:0] = CSC coefficient C1[ 7:0]
	{0x2A, 0x08}, 	//    R0x2A[4:0] = CSC coefficient C2[12:8]
	{0x2B, 0x00}, 	//    R0x2B[7:0] = CSC coefficient C2[ 7:0]
	{0x2C, 0x0E}, 	//    R0x2C[4:0] = CSC coefficient C3[12:8]
	{0x2D, 0x2D}, 	//    R0x2D[7:0] = CSC coefficient C3[ 7:0]
	{0x2E, 0x19}, 	//    R0x2E[4:0] = CSC coefficient C4[12:8]
	{0x2F, 0x14}, 	//    R0x2F[7:0] = CSC coefficient C4[ 7:0]
	{0x48, 0x00}, 	// Video Input Justification
					//    R0x48[4:3] = Video Input Justification = 00 (evenly distributed)
	{0x55, 0x00}, 	// Set RGB in AVinfo Frame
					//    R0x55[6:5] = Output Format = 00 (RGB)
	{0x56, 0x28}, 	// Aspect Ratio
					//    R0x56[5:4] = Picture Aspect Ratio = 10 (16:9)
					//    R0x56[3:0] = Active Format Aspect Ratio = 1000 (Same as Aspect Ratio)
	{0x98, 0x03}, 	// ADI Recommended Write
	{0x9A, 0xE0}, 	// ADI Recommended Write
	{0x9C, 0x30}, 	// PLL Filter R1 Value
	{0x9D, 0x61}, 	// Set clock divide
	{0xA2, 0xA4}, 	// ADI Recommended Write
	{0xA3, 0xA4}, 	// ADI Recommended Write
	{0xAF, 0x04}, 	// HDMI/DVI Modes
					//    R0xAF[  7] = HDCP Enable = 0 (HDCP disabled)
					//    R0xAF[  4] = Frame Encryption = 0 (Current frame NOT HDCP encrypted)
					//    R0xAF[3:2] = 01 (fixed)
					//    R0xAF[  1] = HDMI/DVI Mode Select = 0 (DVI Mode)
	{0xBA, 0x70},   // Programmable delay for input video clock
					//    R0xBA[7:5] = Clock Delay = 011 (no delay)
					//    R0xBA[  4] = HDCP EEPROM =   1 (external)
	{0xE0, 0xD0}, 	// Must be set to 0xD0 for proper operation
	{0xF9, 0x00}  	// Fixed I2C Address (This should be set to a non-conflicting I2C address)
};

/*
 * The video input format of the ADV7511 is set to YCbCr, 16-bit, 4:2:2,
 * ID 1 (separate syncs), Style 1. The video output format is set to
 * YCbCr, 16-bit, 4:2:2, HDMI mode.
 */
#define ADV7511_HDMI_YCBCR422_LEN  16
IicMsg ADV7511_HdmiYCbCr422[ADV7511_HDMI_YCBCR422_LEN] =
{
	{0x41, 0x10}, 	// Power Down Control
					//    R0x41[  6] = PowerDown = 0 (power-up)
	{0xD6, 0xC0}, 	// HPD Control
					//    R0xD6[7:6] = HPD Control = 11 (always high)
	{0x15, 0x01}, 	// Input YCbCr 4:2:2 with separate syncs
	{0x16, 0xB9}, 	// Output format 4:2:2, Input Color Depth = 8
					//    R0x16[  7] = Output Video Format = 1 (4:2:2)
					//    R0x16[5:4] = Input Video Color Depth = 11 (8 bits/color)
					//    R0x16[3:2] = Input Video Style = 10 (style 1)
					//    R0x16[  1] = DDR Input Edge = 0 (falling edge)
					//    R0x16[  0] = Output Color Space = 1 (YCbCr)
	{0x48, 0x00}, 	// Video Input Justification
					//    R0x48[4:3] = Video Input Justification = 00 (evenly distributed)
	{0x55, 0x20}, 	// Set RGB in AVinfo Frame
					//    R0x55[6:5] = Output Format = 01 (YCbCr)
	{0x56, 0x28},	// Aspect Ratio
					//    R0x56[5:4] = Picture Aspect Ratio = 10 (16:9)
					//    R0x56[3:0] = Active Format Aspect Ratio = 1000 (Same as Aspect Ratio)
	{0x98, 0x03}, 	// ADI Recommended Write
	{0x9A, 0xE0}, 	// ADI Recommended Write
	{0x9C, 0x30}, 	// PLL Filter R1 Value
	{0x9D, 0x61}, 	// Set clock divide
	{0xA2, 0xA4},	// ADI Recommended Write
	{0xA3, 0xA4}, 	// ADI Recommended Write
	{0xAF, 0x06}, 	// HDMI/DVI Modes
					//    R0xAF[  7] = HDCP Enable = 0 (HDCP disabled)
					//    R0xAF[  4] = Frame Encryption = 0 (Current frame NOT HDCP encrypted)
					//    R0xAF[3:2] = 01 (fixed)
					//    R0xAF[  1] = HDMI/DVI Mode Select = 2 (HDMI Mode)
	{0xE0, 0xD0}, 	// Must be set to 0xD0 for proper operation
	{0xF9, 0x00}  	// Fixed I2C Address (This should be set to a non-conflicting I2C address)
};

/*
 * The video input format of the ADV7511 is set to YCbCr, 16-bit, 4:2:2,
 * ID 2 (embedded syncs), Style 1. The video output format is set to
 * RGB, 24-bit, 4:4:4, DVI mode.
 *
 * CSC coefficients (registers 0x18 - 0x2F) are taken from tables 40/57
 * of the ADV7511 programmer's guide i.e. converting HDTV YCrCb
 * (16 to 235 or limited range) to RGB (0 to 255 or full range).
 */
#define ADV7511_HDMI_YCBCR422_EMB_SYNC_LEN  23
IicMsg ADV7511_HdmiYCbCr422EmbSync[ADV7511_HDMI_YCBCR422_EMB_SYNC_LEN] =
{
	{0x41, 0x10}, 	// Power Down Control
					//    R0x41[  6] = PowerDown = 0 (power-up)
	{0xD6, 0xC0}, 	// HPD Control
					//    R0xD6[7:6] = HPD Control = 11 (always high)
	{0x15, 0x02}, 	// Input YCbCr 4:2:2 with embedded syncs
	{0x16, 0xB9}, 	// Output format 4:2:2, Input Color Depth = 8
					//    R0x16[  7] = Output Video Format = 1 (4:2:2)
					//    R0x16[5:4] = Input Video Color Depth = 11 (8 bits/color)
					//    R0x16[3:2] = Input Video Style = 10 (style 1)
					//    R0x16[  1] = DDR Input Edge = 0 (falling edge)
					//    R0x16[  0] = Output Color Space = 1 (YCbCr)
	{0x17, 0x02},   // VSync Polarity = 0(high), HSync Polarity = 0(high)
	{0x30, 0x16},   // Hsync placement = 0001011000 (0x58) = 88
	{0x31, 0x02},   // Hsync duration  = 0000101100 (0x2C) = 44
	{0x32, 0xC0},   //
	{0x33, 0x10},   // Vsync placement = 0000000100 (0x04) =  4
	{0x34, 0x05},   // Vsync duration  = 0000000101 (0x05) =  5
	{0x48, 0x08}, 	// Video Input Justification
					//    R0x48[4:3] = Video Input Justification = 01 (right justified)
	{0x55, 0x20}, 	// Set RGB in AVinfo Frame
					//    R0x55[6:5] = Output Format = 01 (YCbCr)
	{0x56, 0x28}, 	// Aspect Ratio
					//    R0x56[5:4] = Picture Aspect Ratio = 10 (16:9)
					//    R0x56[3:0] = Active Format Aspect Ratio = 1000 (Same as Aspect Ratio)
	{0x98, 0x03}, 	// ADI Recommended Write
	{0x9A, 0xE0}, 	// ADI Recommended Write
	{0x9C, 0x30}, 	// PLL Filter R1 Value
	{0x9D, 0x61}, 	// Set clock divide
	{0xA2, 0xA4}, 	// ADI Recommended Write
	{0xA3, 0xA4}, 	// ADI Recommended Write
	{0xAF, 0x06}, 	// HDMI/DVI Modes
					//    R0xAF[  7] = HDCP Enable = 0 (HDCP disabled)
					//    R0xAF[  4] = Frame Encryption = 0 (Current frame NOT HDCP encrypted)
					//    R0xAF[3:2] = 01 (fixed)
					//    R0xAF[  1] = HDMI/DVI Mode Select = 2 (HDMI Mode)
	{0xBA, 0x70},   // Programmable delay for input video clock
					//    R0xBA[7:5] = Clock Delay = 011 (no delay)
					//    R0xBA[  4] = HDCP EEPROM =   1 (external)
	{0xE0, 0xD0}, 	// Must be set to 0xD0 for proper operation
	{0xF9, 0x00}  	// Fixed I2C Address (This should be set to a non-conflicting I2C address)
};

//TODO have proper config struct for adv7511


int ADV7511_CfgInitialize(ADV7511 *Instance, ADV7511_Config *Config)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(Instance != NULL);
	Xil_AssertNonvoid(Config != NULL);

	Instance->Config.DeviceId = Config->DeviceId;
	Instance->Config.IicAddress = Config->IicAddress;

	return XST_SUCCESS;
}


ADV7511 *ADV7511_Initialize(u16 DeviceId, IicAdapter *Adapter)
{
	ADV7511 *Instance = malloc(sizeof *Instance);
	ADV7511_Config *Config = ADV7511_LookupConfig(DeviceId);
	ADV7511_CfgInitialize(Instance, Config);
	Instance->IicAdapter = Adapter;

	return Instance;
}


int ADV7511_SetVideoMode(ADV7511 *Instance, enum VideoFormatId Format)
{
	u8 hpd_ctrl_mask = 0x40; // bit 6 = state of HPD

	// check HPD state
	IicMsg Msg = { 0x42 };
	Instance->IicAdapter->Funcs->Iic_ReadMsg( Instance->IicAdapter, Instance->Config.IicAddress, &Msg, 1);
	if((Msg.Data & hpd_ctrl_mask) != hpd_ctrl_mask)
		return XST_FAILURE;

	// write ADV7511 configuration
	if (Format == V_ARGB32)
		Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->Config.IicAddress, ADV7511_HdmiRGB444, ADV7511_HDMI_RGB444_LEN );
	if (Format == V_VYUY)
		Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->Config.IicAddress, ADV7511_HdmiYCbCr422, ADV7511_HDMI_YCBCR422_LEN );
	if (Format == V_VYUY_emb_sync)
		Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->Config.IicAddress, ADV7511_HdmiYCbCr422EmbSync, ADV7511_HDMI_YCBCR422_EMB_SYNC_LEN );

	Instance->Format = Format;

	return XST_SUCCESS;
}
