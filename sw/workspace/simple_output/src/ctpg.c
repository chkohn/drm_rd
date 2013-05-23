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


void TPG_SetPattern(const enum TPG_Pattern Pattern, int EnableBox)
{
	debug_printf("Set Pattern of Test Pattern Generator\r\n");

	TPG_RegUpdateDisable(XPAR_V_TPG_0_BASEADDR);
	// select Pattern
	if (Pattern == V_TPG_ColorBar) {
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_PATTERN_CONTROL, 0x9);
	} else if (Pattern == V_TPG_ZonePlate) {
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_PATTERN_CONTROL, 0xA);
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_ZPLATE_HOR_CONTROL, (0x0<<16 | 0x90));
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_ZPLATE_VER_CONTROL, (0x0<<16 | 0x3));
	}
	// enable Box
	if (EnableBox) {
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_PATTERN_CONTROL, \
					(TPG_ReadReg(XPAR_V_TPG_0_BASEADDR, TPG_PATTERN_CONTROL) | 0x1020));
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_BOX_COLOR, ARGB32_RED);
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_BOX_SIZE, 0x50);
		TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_MOTION_SPEED, 0xA);
	}
    TPG_RegUpdateEnable(XPAR_V_TPG_0_BASEADDR);
}

void TPG_Configure(const VideoTiming *Timing)
{
	debug_printf("Configure Test Pattern Generator\r\n");

	TPG_RegUpdateDisable(XPAR_V_TPG_0_BASEADDR);
	TPG_WriteReg(XPAR_V_TPG_0_BASEADDR, TPG_ACTIVE_SIZE, (Timing->Field0Height<<16 | Timing->LineWidth));
    TPG_RegUpdateEnable(XPAR_V_TPG_0_BASEADDR);
}

void TPG_Start()
{
	debug_printf("Start Test Pattern Generator\r\n");

	TPG_Enable(XPAR_V_TPG_0_BASEADDR);
}

void TPG_Stop()
{
	debug_printf("Stop Test Pattern Generator\r\n");

	TPG_Disable(XPAR_V_TPG_0_BASEADDR);
}
