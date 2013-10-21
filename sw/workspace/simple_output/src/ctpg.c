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

#include "ctpg.h"
#include <stdlib.h>


XTpg *XTpg_Initialize(u16 DeviceId)
{
	XTpg *Instance = malloc(sizeof *Instance);
	XTpg_Config *Config = XTpg_LookupConfig(DeviceId);
	XTpg_CfgInitialize(Instance, Config, Config->BaseAddr);

	return Instance;
}

void TPG_SetPattern(XTpg *Instance, const enum TPG_Pattern Pattern, int EnableBox)
{
	debug_printf("Set Pattern of Test Pattern Generator\r\n");

	XTpg_RegUpdateDisable(Instance->Config.BaseAddr);

	// select Pattern
	if (Pattern == V_TPG_ColorBar) {
		XTpg_SetBackground(Instance, ColorBars);
		XTpg_SetComponentMask(Instance, Comp_000000);
	} else if (Pattern == V_TPG_ZonePlate) {
		XTpg_SetMotionSpeed(Instance, 0xA);
		XTpg_EnableMotion(Instance, 1);
		XTpg_SetBackground(Instance, ZonePlate);
		XTpg_SetComponentMask(Instance, Comp_FFFF00);
		XTpg_SetHsweepDelta(Instance, 0x90);
		XTpg_SetVsweepDelta(Instance, 0x3);
	} else if (Pattern == V_TPG_PassThrough) {
		XTpg_SetBackground(Instance, PassThrough);
		XTpg_SetComponentMask(Instance, Comp_000000);
	} else {
		xil_printf("Error: Invalid pattern selected\r\n");
	}

	// enable Box
	if (EnableBox) {
		XTpg_SetMotionSpeed(Instance, 0xA);
		XTpg_EnableMotion(Instance, 1);
		XTpg_SetBoxSize(Instance, 0x50);
		XTpg_SetBoxColor(Instance, VYUY_BLUE);
		XTpg_EnableBox(Instance, 1);
	} else {
		XTpg_EnableBox(Instance, 0);
	}

    XTpg_RegUpdateEnable(Instance->Config.BaseAddr);
}

void TPG_Configure(XTpg *Instance, const VideoTiming *Timing)
{
	debug_printf("Configure Test Pattern Generator\r\n");

	XTpg_RegUpdateDisable(Instance->Config.BaseAddr);
	XTpg_SetFrameSize(Instance, Timing->LineWidth, Timing->Field0Height);
    XTpg_RegUpdateEnable(Instance->Config.BaseAddr);
}

void TPG_Start(XTpg *Instance)
{
	debug_printf("Start Test Pattern Generator\r\n");

	XTpg_Enable(Instance->Config.BaseAddr);
}

void TPG_Stop(XTpg *Instance)
{
	debug_printf("Stop Test Pattern Generator\r\n");

	XTpg_Disable(Instance->Config.BaseAddr);
}
