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
#include "xstatus.h"
#include "sleep.h"
#include "adv7611.h"
#include "adv7611_hw.h"


static u8 EDID_Content[256] =
{
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x06, 0xD4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x16, 0x01, 0x03, 0x81, 0x46, 0x27, 0x78,
	0x0A, 0x32, 0x30, 0xA1, 0x54, 0x52, 0x9E, 0x26,
	0x0A, 0x49, 0x4B, 0xA3, 0x08, 0x00, 0x81, 0xC0,
	0x81, 0x00, 0x81, 0x0F, 0x81, 0x40, 0x81, 0x80,
	0x95, 0x00, 0xB3, 0x00, 0x01, 0x01, 0x02, 0x3A,
	0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
	0x45, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E,
	0xA9, 0x1A, 0x00, 0xA0, 0x50, 0x00, 0x16, 0x30,
	0x30, 0x20, 0x37, 0x00, 0xC4, 0x8E, 0x21, 0x00,
	0x00, 0x1A, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x46,
	0x4D, 0x43, 0x2D, 0x49, 0x4D, 0x41, 0x47, 0x45,
	0x4F, 0x4E, 0x0A, 0x20, 0x00, 0x00, 0x00, 0xFD,
	0x00, 0x38, 0x4B, 0x20, 0x44, 0x11, 0x00, 0x0A,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x54,
	0x02, 0x03, 0x1F, 0x71, 0x4B, 0x90, 0x03, 0x04,
	0x05, 0x12, 0x13, 0x14, 0x1F, 0x20, 0x07, 0x16,
	0x26, 0x15, 0x07, 0x50, 0x09, 0x07, 0x01, 0x67,
	0x03, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x1E, 0x01,
	0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20, 0x6E,
	0x28, 0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00,
	0x1E, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16,
	0x20, 0x58, 0x2C, 0x25, 0x00, 0xC4, 0x8E, 0x21,
	0x00, 0x00, 0x9E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20,
	0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00, 0xC4,
	0x8E, 0x21, 0x00, 0x00, 0x18, 0x01, 0x1D, 0x80,
	0x3E, 0x73, 0x38, 0x2D, 0x40, 0x7E, 0x2C, 0x45,
	0x80, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x1A,
	0x36, 0x80, 0xA0, 0x70, 0x38, 0x1F, 0x40, 0x30,
	0x20, 0x25, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00,
	0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};


int ADV7611_ProgramIicAddresses( ADV7611 *Instance )
{
	// update ADV7611 data structure
	Instance->IicAddress.CP        = ADV7611_0_IICADDR_CP;
	Instance->IicAddress.CEC       = ADV7611_0_IICADDR_CEC;
	Instance->IicAddress.INFOFRAME = ADV7611_0_IICADDR_INFOFRAME;
	Instance->IicAddress.HDMI      = ADV7611_0_IICADDR_HDMI;
	Instance->IicAddress.EDID      = ADV7611_0_IICADDR_EDID;
	Instance->IicAddress.KSV       = ADV7611_0_IICADDR_KSV;
	Instance->IicAddress.DPLL      = ADV7611_0_IICADDR_DPLL;

	// program addresses into ADV7611 device
	IicMsg Msg[] = {
		{ 0xF4, Instance->IicAddress.CEC       << 1 },
		{ 0xF5, Instance->IicAddress.INFOFRAME << 1 },
		{ 0xF8, Instance->IicAddress.DPLL      << 1 },
		{ 0xF9, Instance->IicAddress.KSV       << 1 },
		{ 0xFA, Instance->IicAddress.EDID      << 1 },
		{ 0xFB, Instance->IicAddress.HDMI      << 1 },
		{ 0xFD, Instance->IicAddress.CP        << 1 }
	};
	return Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.IO, Msg, 7 );
}


int ADV7611_GetLock( ADV7611 *Instance )
{
	IicMsg Msg = { 0x07 };  // Lock Status
	Instance->IicAdapter->Funcs->Iic_ReadMsg( Instance->IicAdapter, Instance->IicAddress.HDMI, &Msg, 1 );

	// Get lock status based on
	//    ADV7611-HDMI[0x07][7] = vertical lock
	//    ADV7611-HDMI[0x07][5] = de regen lock)
	return ((Msg.Data & 0xA0) == 0xA0) ? 1 : 0;
}


void ADV7611_GetTiming( ADV7611 *Instance, ADV7611_VideoData *Data )
{
	// Read Video Timing information from HDMI receiver
	int i;
	int len = 64;
	IicMsg Msg[len];
	for (i = 0; i < len; i++)
	   Msg[i].Register = i;
	Instance->IicAdapter->Funcs->Iic_ReadMsg( Instance->IicAdapter, Instance->IicAddress.HDMI, Msg, len );


	// Parse Video Timing information
	// Misc
	Data->IsHDMI        = (Msg[0x05].Data >> 7) & 0x01;
	Data->IsEncrypted   = (Msg[0x05].Data >> 6) & 0x01;
	Data->IsInterlaced  = (Msg[0x0B].Data >> 5) & 0x01;
	Data->DeepColorMode = (Msg[0x0B].Data >> 6) & 0x03;
	// Sync Polarity
	Data->HSyncPolarity  = (Msg[0x05].Data >> 5) & 0x01;
	Data->VSyncPolarity  = (Msg[0x05].Data >> 4) & 0x01;
	// Horizontal Timing
	Data->LineWidth      = ((u32) (Msg[0x07].Data & 0x1F) << 8) | ((u32) Msg[0x08].Data);
	Data->HFrontPorch    = ((u32) (Msg[0x20].Data & 0x1F) << 8) | ((u32) Msg[0x21].Data);
	Data->HSyncWidth     = ((u32) (Msg[0x22].Data & 0x1F) << 8) | ((u32) Msg[0x23].Data);
	Data->HBackPorch     = ((u32) (Msg[0x24].Data & 0x1F) << 8) | ((u32) Msg[0x25].Data);
	Data->TotalLineWidth = ((u32) (Msg[0x1E].Data & 0x3F) << 8) | ((u32) Msg[0x1F].Data);
	// Vertical Timing (Field 0)
	Data->Field0Height      = ((u32) (Msg[0x09].Data & 0x1F) << 8) | ((u32) Msg[0x0A].Data);
	Data->Field0FrontPorch  = ((u32) (Msg[0x2A].Data & 0x3F) << 8) | ((u32) Msg[0x2B].Data);
	Data->Field0SyncWidth   = ((u32) (Msg[0x2E].Data & 0x3F) << 8) | ((u32) Msg[0x2F].Data);
	Data->Field0BackPorch   = ((u32) (Msg[0x32].Data & 0x3F) << 8) | ((u32) Msg[0x33].Data);
	Data->Field0TotalHeight = ((u32) (Msg[0x26].Data & 0x3F) << 8) | ((u32) Msg[0x27].Data);
	// Vertical Timing (Field 1)
	Data->Field1Height      = ((u32) (Msg[0x0B].Data & 0x1F) << 8) | ((u32) Msg[0x0C].Data);
	Data->Field1FrontPorch  = ((u32) (Msg[0x2C].Data & 0x3F) << 8) | ((u32) Msg[0x2D].Data);
	Data->Field1SyncWidth   = ((u32) (Msg[0x30].Data & 0x3F) << 8) | ((u32) Msg[0x31].Data);
	Data->Field1BackPorch   = ((u32) (Msg[0x34].Data & 0x3F) << 8) | ((u32) Msg[0x35].Data);
	Data->Field1TotalHeight = ((u32) (Msg[0x28].Data & 0x3F) << 8) | ((u32) Msg[0x29].Data);

	// Print Video Timing information
	// Misc
	adv7611_debug_printf("IsHDMI : %d\r\n", Data->IsHDMI);
	adv7611_debug_printf("IsEncrypted : %d\r\n", Data->IsEncrypted);
	adv7611_debug_printf("IsInterlaced : %d\r\n", Data->IsInterlaced);
	adv7611_debug_printf("DeepColorMode : %d\r\n", Data->DeepColorMode);
	// Sync Polarity
	adv7611_debug_printf("HSyncPolarity : %d\r\n", Data->HSyncPolarity);
	adv7611_debug_printf("VSyncPolarity : %d\r\n", Data->VSyncPolarity);
	// Horizontal Timing
	adv7611_debug_printf("LineWidth : %d\r\n", Data->LineWidth);
	adv7611_debug_printf("HFrontPorch : %d\r\n", Data->HFrontPorch);
	adv7611_debug_printf("HSyncWidth : %d\r\n", Data->HSyncWidth);
	adv7611_debug_printf("HBackPorch : %d\r\n", Data->HBackPorch);
	adv7611_debug_printf("TotalLineWidth : %d\r\n", Data->TotalLineWidth);
	// Vertical Timing (Field 0)
	adv7611_debug_printf("Field0Height : %d\r\n", Data->Field0Height);
	adv7611_debug_printf("Field0FrontPorch : %d\r\n", Data->Field0FrontPorch);
	adv7611_debug_printf("Field0SyncWidth : %d\r\n", Data->Field0SyncWidth);
	adv7611_debug_printf("Field0BackPorch : %d\r\n", Data->Field0BackPorch);
	adv7611_debug_printf("Field0TotalHeight : %d\r\n", Data->Field0TotalHeight);
	// Vertical Timing (Field 1)
	adv7611_debug_printf("Field1Height : %d\r\n", Data->Field1Height);
	adv7611_debug_printf("Field1FrontPorch : %d\r\n", Data->Field1FrontPorch);
	adv7611_debug_printf("Field1SyncWidth : %d\r\n", Data->Field1SyncWidth);
	adv7611_debug_printf("Field1BackPorch : %d\r\n", Data->Field1BackPorch);
	adv7611_debug_printf("Field1TotalHeight : %d\r\n\r\n", Data->Field1TotalHeight);
}


int ADV7611_CfgInitialize(ADV7611 *Instance, ADV7611_Config *Config)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(Instance != NULL);
	Xil_AssertNonvoid(Config != NULL);

	Instance->Config.DeviceId   = Config->DeviceId;
	Instance->Config.IicAddress = Config->IicAddress;

	return XST_SUCCESS;
}


ADV7611 *ADV7611_Initialize( u16 DeviceId, IicAdapter *IicAdapter )
{
	ADV7611 *Instance = malloc(sizeof *Instance);
	ADV7611_Config *Config = ADV7611_LookupConfig(DeviceId);
	ADV7611_CfgInitialize(Instance, Config);
	Instance->IicAdapter = IicAdapter;
	Instance->IicAddress.IO = Instance->Config.IicAddress;

	return Instance;
}


void ADV7611_WriteEDID( ADV7611 *Instance )
{
	// pre EDID
	IicMsg Msg0 = { 0x77, 0x00 }; // Disable the Internal EDID
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.KSV, &Msg0, 1 );

	// write EDID
	Instance->IicAdapter->Funcs->Iic_WriteBlock( Instance->IicAdapter, Instance->IicAddress.EDID, 0x00, EDID_Content, sizeof(EDID_Content) );

	// post EDID
	IicMsg Msg1[] = {
		{ 0x77, 0x00 }, // Set the Most Significant Bit of the SPA location to 0
		{ 0x52, 0x20 }, // Set the SPA for port B.
		{ 0x53, 0x00 }, // Set the SPA for port B.
		{ 0x70, 0x9E }, // Set the Least Significant Byte of the SPA location
		{ 0x74, 0x03 }  // Enable the Internal EDID for Ports
	};
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.KSV, Msg1, 5 );
}


void ADV7611_WriteConfig( ADV7611 *Instance )
{
	IicMsg Msg0[] = {
		{ 0x01, 0x06 }, // Prim_Mode = 110b HDMI-GR
		{ 0x02, 0xF5 }, // Auto CSC, YCrCb out, Set op_656 bit
		{ 0x03, 0x80 }, // 16-Bit SDR ITU-R BT.656 4:2:2 Mode 0
		{ 0x04, 0x62 }, // OP_CH_SEL[2:0] = 011b - (P[15:8] Y, P[7:0] CrCb), XTAL_FREQ[1:0] = 01b (28.63636 MHz)
		{ 0x05, 0x2C }  // AV Codes on
	};
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.IO, Msg0, 5 );

	IicMsg Msg1 = { 0x7B, 0x05 };  //
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.CP, &Msg1, 1 );

	IicMsg Msg2[] = {
		{ 0x0B, 0x44 }, // Power up part
		{ 0x0C, 0x42 }, // Power up part
		{ 0x14, 0x7F }, // Max Drive Strength
		{ 0x15, 0x80 }, // Disable Tristate of Pins
		{ 0x06, 0xA1 }, // LLC polarity (INV_LLC_POL = 1)
		{ 0x19, 0x80 }, // LLC DLL phase (delay = 0)
		{ 0x33, 0x40 }  // LLC DLL enable
	};
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.IO, Msg2, 7 );

	IicMsg Msg3 = { 0xBA, 0x01 };  // Set HDMI FreeRun
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.CP, &Msg3, 1 );

	IicMsg Msg4 = { 0x40, 0x81 };  // Disable HDCP 1.1 features
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.KSV, &Msg4, 1 );

	IicMsg Msg5[] = {
		{ 0x9B, 0x03 }, // ADI recommended setting
		{ 0xC1, 0x01 }, // ADI recommended setting
		{ 0xC2, 0x01 }, // ADI recommended setting
		{ 0xC3, 0x01 }, // ADI recommended setting
		{ 0xC4, 0x01 }, // ADI recommended setting
		{ 0xC5, 0x01 }, // ADI recommended setting
		{ 0xC6, 0x01 }, // ADI recommended setting
		{ 0xC7, 0x01 }, // ADI recommended setting
		{ 0xC8, 0x01 }, // ADI recommended setting
		{ 0xC9, 0x01 }, // ADI recommended setting
		{ 0xCA, 0x01 }, // ADI recommended setting
		{ 0xCB, 0x01 }, // ADI recommended setting
		{ 0xCC, 0x01 }, // ADI recommended setting
		{ 0x00, 0x08 }, // Set HDMI Input Port A  (BG_MEAS_PORT_SEL = 001b)
		{ 0x02, 0x03 }, // Enable Ports A & B in background mode
		{ 0x83, 0xFC }, // Enable clock terminators for port A & B
		{ 0x6F, 0x0C }, // ADI recommended setting
		{ 0x85, 0x1F }, // ADI recommended setting
		{ 0x87, 0x70 }, // ADI recommended setting
		{ 0x8D, 0x04 }, // LFG Port A
		{ 0x8E, 0x1E }, // HFG Port A
		{ 0x1A, 0x8A }, // Unmute audio
		{ 0x57, 0xDA }, // ADI recommended setting
		{ 0x58, 0x01 }, // ADI recommended setting
		{ 0x75, 0x10 }, // DDC drive strength
		{ 0x90, 0x04 }, // LFG Port B
		{ 0x91, 0x1E }  // HFG Port B
	};
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->IicAddress.HDMI, Msg5, 27 );
}
