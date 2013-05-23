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

#include "osd.h"
#include <stdlib.h>


XOSD *XOSD_Initialize(u16 DeviceId)
{
	XOSD *Instance = malloc(sizeof *Instance);
	XOSD_Config *Config = XOSD_LookupConfig(DeviceId);
	XOSD_CfgInitialize(Instance, Config, Config->BaseAddress);

	return Instance;
}

void XOSD_Configure(XOSD *Instance, const VideoTiming *Timing)
{
	debug_printf("Configure On Screen Display\r\n");

	XOSD_RegUpdateDisable(Instance);

	// Set screen size
	XOSD_SetScreenSize(Instance, Timing->LineWidth, Timing->Field0Height);

    XOSD_RegUpdateEnable(Instance);
}

void XOSD_ConfigureLayer(XOSD *Instance, struct XOSD_LayerConfig *Config)
{
	debug_printf("Configure On Screen Display - Layer %d\r\n", Config->Index);

	XOSD_RegUpdateDisable(Instance);

	if (Config->Enable) {
		// Set up Layer Alpha, Priority, Dimension and enable it
		XOSD_SetLayerAlpha(Instance, Config->Index, Config->GlobalAlphaEnble, Config->GlobalAlphaValue);
		XOSD_SetLayerPriority(Instance, Config->Index, Config->Priority);
		XOSD_SetLayerDimension(Instance, Config->Index, Config->XStart, Config->YStart, Config->XSize, Config->YSize);
		XOSD_EnableLayer(Instance, Config->Index);
	} else {
		XOSD_DisableLayer(Instance, Config->Index);
	}

	XOSD_RegUpdateEnable(Instance);
}

void XOSD_Start(XOSD *Instance)
{
	debug_printf("Start On Screen Display\r\n");

	XOSD_Enable(Instance);
}
