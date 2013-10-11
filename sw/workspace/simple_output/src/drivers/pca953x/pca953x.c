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
#include "pca953x.h"
#include "pca953x_hw.h"


int PCA953X_CfgInitialize(PCA953X *Instance, PCA953X_Config *Config)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(Instance != NULL);
	Xil_AssertNonvoid(Config != NULL);

	Instance->Config.DeviceId = Config->DeviceId;
	Instance->Config.IicAddress = Config->IicAddress;
	Instance->Config.NumGpioBanks = Config->NumGpioBanks;
	Instance->Config.GpioBankSize = Config->GpioBankSize;
	Instance->Config.MaxNumGpioPorts = Config->MaxNumGpioPorts;

	return XST_SUCCESS;
}


PCA953X *PCA953X_Initialize( u16 DeviceId, IicAdapter *IicAdapter )
{
	PCA953X *Instance = malloc(sizeof *Instance);
	PCA953X_Config *Config = PCA953X_LookupConfig(DeviceId);
	PCA953X_CfgInitialize(Instance, Config);
	Instance->IicAdapter = IicAdapter;

	return Instance;
}


GpioAdapter* PCA953X_RegisterAdapter( void *Instance )
{
	static struct GpioAdapterFuncs Funcs = {
		PCA953X_Gpio_ReadPin,
		PCA953X_Gpio_WritePin,
		PCA953X_Gpio_GetDirectionPin,
		PCA953X_Gpio_SetDirectionPin
	};

	return Gpio_RegisterAdapter( Instance, &Funcs );
}


int PCA953X_Gpio_ReadPin( GpioAdapter *Adapter, int Pin )
{
	PCA953X *Instance = (PCA953X *) (Adapter->Instance);
	IicAdapter *IicAdapter = Instance->IicAdapter;

	IicMsg Msg = { .Register = INPUT_PORT };

	IicAdapter->Funcs->Iic_ReadMsg(IicAdapter, Instance->Config.IicAddress, &Msg, 1);

	return (Msg.Data >> Pin) & 1;
}


void PCA953X_Gpio_WritePin( GpioAdapter *Adapter, int Pin, int Data )
{
	PCA953X *Instance = (PCA953X *) (Adapter->Instance);
	IicAdapter *IicAdapter = Instance->IicAdapter;

	IicMsg Msg = { .Register = OUTPUT_PORT };

	// read current bank value
	IicAdapter->Funcs->Iic_ReadMsg(IicAdapter, Instance->Config.IicAddress, &Msg, 1);

	if (Data == 1) {
		Msg.Data |=  (1 << Pin);
	} else {
		Msg.Data &= ~(1 << Pin);
	}

	// modify single pin of bank
	IicAdapter->Funcs->Iic_WriteMsg(IicAdapter, Instance->Config.IicAddress, &Msg, 1);
}


int PCA953X_Gpio_GetDirectionPin( GpioAdapter *Adapter, int Pin )
{
	PCA953X *Instance = (PCA953X *) (Adapter->Instance);
	IicAdapter *IicAdapter = Instance->IicAdapter;

	IicMsg Msg = { .Register = CONFIGURATION };

	IicAdapter->Funcs->Iic_ReadMsg(IicAdapter, Instance->Config.IicAddress, &Msg, 1);

	return ~((Msg.Data >> Pin) & 1);
}


void PCA953X_Gpio_SetDirectionPin( GpioAdapter *Adapter, int Pin, int Direction )
{
	PCA953X *Instance = (PCA953X *) (Adapter->Instance);
	IicAdapter *IicAdapter = Instance->IicAdapter;

	IicMsg Msg = { .Register = CONFIGURATION };

	// read current bank value
	IicAdapter->Funcs->Iic_ReadMsg(IicAdapter, Instance->Config.IicAddress, &Msg, 1);

	if (Direction == OUTPUT_PORT) {
		Msg.Data &= ~(1 << Pin);
	} else { // Direction == INPUT_PORT
		Msg.Data |=  (1 << Pin);
	}

	// modify single pin of bank
	IicAdapter->Funcs->Iic_WriteMsg(IicAdapter, Instance->Config.IicAddress, &Msg, 1);
}
