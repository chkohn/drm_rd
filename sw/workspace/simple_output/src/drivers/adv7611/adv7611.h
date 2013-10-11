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

#ifndef ADV7611_H_
#define ADV7611_H_


#include "xiic_adapter.h"


// Turn on/off Debug messages
#ifdef ADV7611_DEBUG
#include "xil_printf.h"
#define  adv7611_debug_printf  xil_printf
#else
#define  adv7611_debug_printf(msg, args...) do {  } while (0)
#endif


typedef struct {
	u16 DeviceId;
	u16 IicAddress;
} ADV7611_Config;


typedef struct {
	ADV7611_Config Config;
	IicAdapter *IicAdapter;
	struct {
		u16 IO;
		u16 CP;
		u16 CEC;
		u16 INFOFRAME;
		u16 HDMI;
		u16 EDID;
		u16 KSV;
		u16 DPLL;
	} IicAddress;
} ADV7611;


typedef struct {
	u32 IsHDMI;
	u32 IsEncrypted;
	u32 IsInterlaced;
	u32 DeepColorMode;
	u32 LineWidth;
	u32 HFrontPorch;
	u32 HSyncWidth;
	u32 HBackPorch;
	u32 TotalLineWidth;
	u32 Field0Height;
	u32 Field0FrontPorch;
	u32 Field0SyncWidth;
	u32 Field0BackPorch;
	u32 Field0TotalHeight;
	u32 Field1Height;
	u32 Field1FrontPorch;
	u32 Field1SyncWidth;
	u32 Field1BackPorch;
	u32 Field1TotalHeight;
	u32 HSyncPolarity;
	u32 VSyncPolarity;
} ADV7611_VideoData;


// Function for configuration lookup
ADV7611_Config *ADV7611_LookupConfig(u16 DeviceId);

// Function for general setup
int ADV7611_CfgInitialize(ADV7611 *Instance, ADV7611_Config *Config);

// Init Function
ADV7611 *ADV7611_Initialize(u16 DeviceId, IicAdapter *IicAdapter);

// Program IIC Addresses
int ADV7611_ProgramIicAddresses(ADV7611 *Instance);

// Write EDID
void ADV7611_WriteEDID(ADV7611 *Instance);

// Write Configuration
void ADV7611_WriteConfig(ADV7611 *Instance);

// Lock Status
int ADV7611_GetLock(ADV7611 *Instance);

// Video Timing
void ADV7611_GetTiming(ADV7611 *Instance, ADV7611_VideoData *Data);


#endif /* ADV7611_H_ */
