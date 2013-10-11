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

#ifndef FMC_IPMI_H_
#define FMC_IPMI_H_


#include "xiic_adapter.h"


#define FRU_BOARD_INFO_LEN 120


// Turn on/off Debug messages
#ifdef FMC_IPMI_DEBUG
#define  fmc_ipmi_debug_printf  printf
#else
#define  fmc_ipmi_debug_printf(msg, args...) do {  } while (0)
#endif


enum FmcType {
	LPC=0,
	HPC=1
};


// FRU Common Header
typedef struct {
	u8 Version;
	struct	{
		u8 Internal;
		u8 Chassis;
		u8 Board;
		u8 Product;
		u8 MultiRecord;
	} Offset;
	u8 Pad;
	u8 Checksum;
} FRU_Common;


// FRU Board Info Area
typedef struct {
	u8  Version;
	u8  Length;
	u8  Lang;
	u32 MfgDateTime;
	char *Mfg;
	char *Prod;
	char *Serial;
	char *Part;
	char *FileId;
} FRU_Board;


typedef struct {
	u16 DeviceId;
	u16 IicAddress;
	enum FmcType Type;
} FMC_IPMI_Config;


typedef struct {
	FMC_IPMI_Config Config;
	IicAdapter *IicAdapter;
	FRU_Common CommonInfo;
	FRU_Board BoardInfo;
} FMC_IPMI;


// Function for configuration lookup
FMC_IPMI_Config *FMC_IPMI_LookupConfig(u16 DeviceId);

// Function for general setup
int FMC_IPMI_CfgInitialize(FMC_IPMI *Instance, FMC_IPMI_Config *Config);

// IIC Client Init Function
FMC_IPMI *FMC_IPMI_Initialize(u16 DeviceId, IicAdapter *Adapter);


#endif /* FMC_IPMI_H_ */
