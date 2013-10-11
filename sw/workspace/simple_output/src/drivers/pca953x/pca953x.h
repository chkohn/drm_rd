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

#ifndef PCA953X_H_
#define PCA953X_H_


#include "xiic_adapter.h"
#include "xgpio_adapter.h"


typedef struct {
	u16 DeviceId;
	u16 IicAddress;
	u8  NumGpioBanks;
	u8  GpioBankSize;
	u8  MaxNumGpioPorts;
} PCA953X_Config;


typedef struct {
	PCA953X_Config Config;
	IicAdapter *IicAdapter;
} PCA953X;


// GPIO Init Functions
PCA953X_Config *PCA953X_LookupConfig(u16 DeviceId);
PCA953X *PCA953X_Initialize( u16 DeviceId, IicAdapter *IicAdapter );

// GPIO Register Function
GpioAdapter* PCA953X_RegisterAdapter( void *Instance );

// GPIO Read Functions
int PCA953X_Gpio_ReadPin( GpioAdapter *Adapter, int Pin );
int PCA953X_Gpio_GetDirectionPin( GpioAdapter *Adapter, int Pin );

// GPIO Write Functions
void PCA953X_Gpio_WritePin( GpioAdapter *Adapter, int Pin, int Data );
void PCA953X_Gpio_SetDirectionPin( GpioAdapter *Adapter, int Pin, int Direction );


#endif /* PCA953X_H_ */
