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

#include "sobel.h"
#include <stdlib.h>


//static int RunningFilter;


XSobel_filter *XSobel_Initialize(u16 DeviceId)
{
	XSobel_filter *Instance = malloc(sizeof *Instance);
	XSobel_filter_Config *Config = XSobel_filter_LookupConfig(DeviceId);
	XSobel_filter_CfgInitialize(Instance, Config);

	return Instance;
}

void XSobel_Configure(XSobel_filter *Instance, const VideoTiming *Timing)
{
	debug_printf("Configure Sobel filter\r\n");

	XSobel_filter_SetCols(Instance, Timing->LineWidth);
	XSobel_filter_SetRows(Instance, Timing->Field0Height);

	XSobel_filter_SetC_xr0c0(Instance, 0x1);
	XSobel_filter_SetC_xr0c1(Instance, 0x0);
	XSobel_filter_SetC_xr0c2(Instance, 0xFFFFFFFF);
	XSobel_filter_SetC_xr1c0(Instance, 0x2);
	XSobel_filter_SetC_xr1c1(Instance, 0x0);
	XSobel_filter_SetC_xr1c2(Instance, 0xFFFFFFFE);
	XSobel_filter_SetC_xr2c0(Instance, 0x1);
	XSobel_filter_SetC_xr2c1(Instance, 0x0);
	XSobel_filter_SetC_xr2c2(Instance, 0xFFFFFFFF);

	XSobel_filter_SetC_yr0c0(Instance, 0x1);
	XSobel_filter_SetC_yr0c1(Instance, 0x2);
	XSobel_filter_SetC_yr0c2(Instance, 0x1);
	XSobel_filter_SetC_yr1c0(Instance, 0x0);
	XSobel_filter_SetC_yr1c1(Instance, 0x0);
	XSobel_filter_SetC_yr1c2(Instance, 0x0);
	XSobel_filter_SetC_yr2c0(Instance, 0xFFFFFFFF);
	XSobel_filter_SetC_yr2c1(Instance, 0xFFFFFFFE);
	XSobel_filter_SetC_yr2c2(Instance, 0xFFFFFFFF);

	XSobel_filter_SetC_high_thesh(Instance, 200);
	XSobel_filter_SetC_low_thresh(Instance, 100);

	XSobel_filter_SetC_invert(Instance, 0x0);
};

void XSobel_Start(XSobel_filter *Instance)
{
	// Enable Interrupts
//	XSobel_filter_InterruptGlobalEnable(Instance);
//	XSobel_filter_InterruptEnable(Instance, 1);

	// Start Filter
	XSobel_filter_EnableAutoRestart(Instance);
	XSobel_filter_Start(Instance);
}

void XSobel_Stop(XSobel_filter *Instance)
{
	// Wait until Filter stops
	XSobel_filter_DisableAutoRestart(Instance);
	while (!XSobel_filter_IsIdle(Instance));

	// Disable Interrupts
//	XSobel_filter_InterruptGlobalDisable(Instance);
//	XSobel_filter_InterruptDisable(Instance, 1);
}

//void XSobel_Isr(void *Instance)
//{
//	XSobel_filter *FilterInstance = (XSobel_filter *) Instance;
//    u32 Status;
//
////    static int cnt;
////    xil_printf("\n\rInfo : XSobel_filterIsr %d\n\r", ++cnt);
//
//    XSobel_filter_InterruptDisable(FilterInstance, 0xffffffff);
//
//    // check interrupt status
//    Status = XSobel_filter_InterruptGetStatus(FilterInstance);
//    Xil_AssertVoid(Status == 1);
//
//	XSobel_filter_InterruptClear(FilterInstance, 1);
//
//    if (RunningFilter) {
//    	XSobel_filter_InterruptEnable(FilterInstance, 1);
//        XSobel_filter_Start(FilterInstance);
//    }
//}
