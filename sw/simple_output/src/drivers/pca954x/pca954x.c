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
#include "sleep.h"
#include "xstatus.h"
#include "xil_printf.h"
#include "pca954x.h"
#include "../../xparameters_zc702.h"


VirtualAdapter *PCA954X_RegisterVirtAdapter( u16 DeviceId, u8 ChannelNum, PCA954X *IicMux )
{
	VirtualAdapter *Instance = malloc(sizeof *Instance);

	Instance->DeviceId = DeviceId;
	Instance->IicMux = IicMux;
	Instance->ChannelNumber = ChannelNum;

	return Instance;
}


int PCA954X_CfgInitialize(PCA954X *Instance, PCA954X_Config *Config)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(Instance != NULL);
	Xil_AssertNonvoid(Config != NULL);

	Instance->Config.DeviceId = Config->DeviceId;
	Instance->Config.IicAddress = Config->IicAddress;
	Instance->Config.NumChannels = Config->NumChannels;
	Instance->CurrChannel = 0x00;

	return XST_SUCCESS;
}


PCA954X *PCA954X_Initialize( u16 DeviceId, IicAdapter *IicAdapter)
{
	VirtualAdapter *VirtAdapter;
	u8 ChanNum = 1;

	static struct IicAdapterFuncs Funcs = {
		PCA954X_ReadByte,
		PCA954X_ReadBlock,
		PCA954X_ReadMsg,
		PCA954X_WriteByte,
		PCA954X_WriteBlock,
		PCA954X_WriteMsg
	};

	PCA954X *Instance = malloc(sizeof *Instance);
	PCA954X_Config *Config = PCA954X_LookupConfig(DeviceId);
	PCA954X_CfgInitialize(Instance, Config);
	Instance->ParentAdapter = IicAdapter;

	int i;
	for (i = 0; i < Instance->Config.NumChannels; i++) {
		VirtAdapter = PCA954X_RegisterVirtAdapter( DeviceId, ChanNum, Instance );
		Instance->VirtAdapter[i] = Iic_RegisterAdapter( (void *) VirtAdapter, &Funcs );
		ChanNum <<= 1;
	}

	return Instance;
}


int PCA954X_SelectChannel( VirtualAdapter *VirtAdapter )
{
	int Status;

	if (VirtAdapter->ChannelNumber != VirtAdapter->IicMux->CurrChannel) {
		Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_WriteByte(VirtAdapter->IicMux->ParentAdapter, VirtAdapter->IicMux->Config.IicAddress, VirtAdapter->ChannelNumber);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
		VirtAdapter->IicMux->CurrChannel = VirtAdapter->ChannelNumber;
	}

	return XST_SUCCESS;
}


int PCA954X_ReadByte( IicAdapter *Adapter, u16 Address, u8 *Data )
{
	VirtualAdapter *VirtAdapter = (VirtualAdapter *) (Adapter->Instance);
	int Status;

    Status = PCA954X_SelectChannel(VirtAdapter);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_ReadByte( VirtAdapter->IicMux->ParentAdapter, Address, Data );

	return Status;
}


int PCA954X_ReadBlock( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount )
{
	VirtualAdapter *VirtAdapter = (VirtualAdapter *) (Adapter->Instance);
	int Status;

    Status = PCA954X_SelectChannel(VirtAdapter);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_ReadBlock( VirtAdapter->IicMux->ParentAdapter, Address, Register, Data, ByteCount );

	return Status;
}


int PCA954X_ReadMsg( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength )
{
	VirtualAdapter *VirtAdapter = (VirtualAdapter *) (Adapter->Instance);
	int Status;

    Status = PCA954X_SelectChannel(VirtAdapter);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_ReadMsg( VirtAdapter->IicMux->ParentAdapter, Address, Msg, MsgLength );

	return Status;
}


int PCA954X_WriteByte( IicAdapter *Adapter, u16 Address, u8 Data )
{
	VirtualAdapter *VirtAdapter = (VirtualAdapter *) (Adapter->Instance);
	int Status;

    Status = PCA954X_SelectChannel(VirtAdapter);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_WriteByte( VirtAdapter->IicMux->ParentAdapter, Address, Data );

	return Status;
}


int PCA954X_WriteBlock( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount )
{
	VirtualAdapter *VirtAdapter = (VirtualAdapter *) (Adapter->Instance);
	int Status;

    Status = PCA954X_SelectChannel(VirtAdapter);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_WriteBlock( VirtAdapter->IicMux->ParentAdapter, Address, Register, Data, ByteCount );

	return Status;
}


int PCA954X_WriteMsg( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength )
{
	VirtualAdapter *VirtAdapter = (VirtualAdapter *) (Adapter->Instance);
	int Status;

    Status = PCA954X_SelectChannel(VirtAdapter);
	if (Status != XST_SUCCESS) {
		iic_debug_printf("[PCA954X_SelectChannel] failed\n\r");
		return XST_FAILURE;
	}

	Status = VirtAdapter->IicMux->ParentAdapter->Funcs->Iic_WriteMsg( VirtAdapter->IicMux->ParentAdapter, Address, Msg, MsgLength );

	return Status;
}
