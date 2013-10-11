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
#include <string.h>
#include "xstatus.h"
#include "fmc_ipmi.h"


static int FMC_IPMI_GetCommonInfo(FMC_IPMI *Instance)
{
	u8 Data[8];
	u8 Checksum = 0;
	int i;

	// read common header
	Instance->IicAdapter->Funcs->Iic_ReadBlock( Instance->IicAdapter, Instance->Config.IicAddress, 0x00, Data, 8 );

	// calculate checksum
	for ( i = 0; i < 8; i++ ) {
		Checksum += Data[i];
	}

	// verify checksum
	if ( Checksum != 0x00 )	{
		fmc_ipmi_debug_printf("FRU CHECKSUM ERROR\n\r");
		return XST_FAILURE;
	}

	// decode data
	Instance->CommonInfo.Version 			= Data[0];
	Instance->CommonInfo.Offset.Internal 	= Data[1];
	Instance->CommonInfo.Offset.Chassis  	= Data[2];
	Instance->CommonInfo.Offset.Board    	= Data[3];
	Instance->CommonInfo.Offset.Product  	= Data[4];
	Instance->CommonInfo.Offset.MultiRecord	= Data[5];
	Instance->CommonInfo.Pad             	= Data[6];
	Instance->CommonInfo.Checksum        	= Data[7];

	// verify version
	if ( Instance->CommonInfo.Version != 0x01 ) {
		fmc_ipmi_debug_printf("FRU VERSION ERROR\n\r");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


static int FMC_IPMI_GetBoardInfo(FMC_IPMI *Instance)
{
	u8 Data[FRU_BOARD_INFO_LEN];
	u8 Checksum = 0;
	int Offset;
	int i;

	// read board info area
	Offset = Instance->CommonInfo.Offset.Board << 3;  // multiples of 8 bytes -> Offset*8 equals Offset<<3
	Instance->BoardInfo.Length = FRU_BOARD_INFO_LEN;  // use fixed length for now
	Instance->IicAdapter->Funcs->Iic_ReadBlock( Instance->IicAdapter, Instance->Config.IicAddress, Offset, Data, Instance->BoardInfo.Length );

	// calculate checksum
	for ( i = 0; i < Instance->BoardInfo.Length; i++ ) {
		Checksum += Data[i];
	}

	// verify checksum
	if ( Checksum != 0x00 )	{
		fmc_ipmi_debug_printf("FRU CHECKSUM ERROR\n\r");
		return XST_FAILURE;
	}

	// decode data
	i = 0;
	// Version
	Instance->BoardInfo.Version = Data[i++];
	// Length (multiples of 8 bytes)
	Instance->BoardInfo.Length = Data[i++] << 3;
	// Language (English)
	Instance->BoardInfo.Lang = Data[i++];
	// Mfg Date/Time (Little Endian) - 3 bytes
	Instance->BoardInfo.MfgDateTime = Data[i+0] | Data[i+1] << 8 | Data[i+2] << 16;
	i += 3;
	// Board Manufacturer (8 bit ASCII)
	Instance->BoardInfo.Mfg = strdup((char *) &Data[i+1]);
	i += 1 + (Data[i] & 0x3F);
	// Board Product Name (8 bit ASCII)
	Instance->BoardInfo.Prod = strdup((char *) &Data[i+1]);
	i += 1 + (Data[i] & 0x3F);
	// Board Serial Number (8 bit ASCII)
	Instance->BoardInfo.Serial = strdup((char *) &Data[i+1]);
	i += 1 + (Data[i] & 0x3F);
	// Board Part Number (8 bit ASCII)
	Instance->BoardInfo.Part = strdup((char *) &Data[i+1]);
	i += 1 + (Data[i] & 0x3F);
	// FRU File ID (8 bit ASCII)
	Instance->BoardInfo.FileId = strdup((char *) &Data[i+1]);
	i += 1 + (Data[i] & 0x3F);

	// verify version
	if ( Instance->BoardInfo.Version != 0x01 ) {
		fmc_ipmi_debug_printf("FRU VERSION ERROR\n\r");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


static int FMC_IPMI_Detect(FMC_IPMI *Instance)
{
	u8 Data;

	// probe FMC EEPROM
	return Instance->IicAdapter->Funcs->Iic_ReadByte( Instance->IicAdapter, Instance->Config.IicAddress, &Data );
}



int FMC_IPMI_CfgInitialize(FMC_IPMI *Instance, FMC_IPMI_Config *Config)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(Instance != NULL);
	Xil_AssertNonvoid(Config != NULL);

	Instance->Config.DeviceId = Config->DeviceId;
	Instance->Config.IicAddress = Config->IicAddress;
	Instance->Config.Type = Config->Type;

	return XST_SUCCESS;
}


FMC_IPMI *FMC_IPMI_Initialize( u16 DeviceId, IicAdapter *Adapter )
{
	int Status;

	FMC_IPMI *Instance = malloc(sizeof *Instance);
	FMC_IPMI_Config *Config = FMC_IPMI_LookupConfig(DeviceId);
	FMC_IPMI_CfgInitialize(Instance, Config);
	Instance->IicAdapter = Adapter;

	// detect FMC
	Status = FMC_IPMI_Detect( Instance );
	if (Status != XST_SUCCESS) {
		free(Instance);
		return NULL;
	}

	// read common info
	Status = FMC_IPMI_GetCommonInfo( Instance );
	if (Status != XST_SUCCESS) {
		free(Instance);
		return NULL;
	}

	// read board info
	Status = FMC_IPMI_GetBoardInfo( Instance );
	if (Status != XST_SUCCESS) {
		free(Instance);
		return NULL;
	}

	return Instance;
}

