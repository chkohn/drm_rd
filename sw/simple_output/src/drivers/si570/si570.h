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

#ifndef SI570_H_
#define SI570_H_


#include "xiic_adapter.h"


// Turn on/off Debug messages
#ifdef SI570_DEBUG
#include <stdio.h>
#define  si570_debug_printf  printf
#else
#define  si570_debug_printf(msg, args...) do {  } while (0)
#endif


typedef struct {
	u16 DeviceId;                    // Unique ID of device
	u16 IicAddress;                  // IIC address of device
	unsigned long long FreqDefault;  // Factory Default Frequency
	unsigned long long FreqDcoMax;   // Max DCO Frequency
	unsigned long long FreqDcoMin;   // Min DCO Frequency
} SI570_Config;


typedef struct {
	SI570_Config Config;			 // Configuration structure
	IicAdapter *IicAdapter;             // IIC Adapter
	u8  HSDiv;                       // DCO High Speed Divider
	u8  N1Div;                       // CLKOUT output divider
	unsigned long long FreqRef; 	 // Reference Frequency (Input to DCO)
	unsigned long long FreqXtal;     // Factory Crystal Frequency
	unsigned long long FreqOut;      // Programmed Output Frequency
} SI570;


// Constants
const unsigned long long freq_HD1080P;
const unsigned long long freq_WSXGA;
const unsigned long long freq_SXGA;
const unsigned long long freq_HD720P;
const unsigned long long freq_XGA;
const unsigned long long freq_SVGA;
const unsigned long long freq_VGA;


// Function for configuration lookup
SI570_Config *SI570_LookupConfig(u16 DeviceId);

// Function for general setup
int SI570_CfgInitialize(SI570 *Instance, SI570_Config *Config);

// IIC Client Init Function
SI570 *SI570_Initialize( u16 DeviceId, IicAdapter *Adapter );

// USRCLK Functions
int SI570_SetFrequency( SI570 *Instance, unsigned long long new_freq );
unsigned long long SI570_GetFrequency( SI570 *Instance );


#endif /* SI570_H_ */
