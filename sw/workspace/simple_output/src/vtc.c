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

#include "vtc.h"
#include <stdlib.h>


#define VTC_WORKAROUND


#ifdef VTC_WORKAROUND
static void StubCallBack(void *CallBackRef)
{
	Xil_AssertVoidAlways();
}

static void StubErrCallBack(void *CallBackRef, u32 ErrorMask)
{
	Xil_AssertVoidAlways();
}

static int my_XVtc_CfgInitialize(XVtc *InstancePtr, XVtc_Config *CfgPtr,
				u32 EffectiveAddr)
{
	/* Verify arguments */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(CfgPtr != NULL);
	Xil_AssertNonvoid((u32 *)EffectiveAddr != NULL);

	/* Setup the instance */
	memset((void *)InstancePtr, 0, sizeof(XVtc));
	memcpy((void *)&(InstancePtr->Config), (const void *)CfgPtr,
			   sizeof(XVtc_Config));
	InstancePtr->Config.BaseAddress = EffectiveAddr;

	/* Set all handlers to stub values, let user configure this data later
	 */
	InstancePtr->FrameSyncCallBack = (XVtc_CallBack) StubCallBack;
	InstancePtr->LockCallBack = (XVtc_CallBack) StubCallBack;
	InstancePtr->DetectorCallBack = (XVtc_CallBack) StubCallBack;
	InstancePtr->GeneratorCallBack = (XVtc_CallBack) StubCallBack;
	InstancePtr->ErrCallBack = (XVtc_ErrorCallBack) StubErrCallBack;

	/* Reset the hardware and set the flag to indicate the driver is
	  ready */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;
//	XVtc_Reset(InstancePtr);

	return XST_SUCCESS;
}
#endif

XVtc *XVtc_Initialize(u16 DeviceId)
{
	XVtc *Instance = malloc(sizeof *Instance);
	XVtc_Config *Config = XVtc_LookupConfig(DeviceId);
#ifdef VTC_WORKAROUND
	my_XVtc_CfgInitialize(Instance, Config, Config->BaseAddress);
#else
	XVtc_CfgInitialize(Instance, Config, Config->BaseAddress);
#endif
	return Instance;
}

void XVtc_Configure(XVtc *Instance, const VideoTiming *Timing)
{
	debug_printf("Configure Video Timing Controller\r\n");

	XVtc_Polarity Polarity;
	XVtc_Signal Signal;
	XVtc_HoriOffsets HoriOffsets;
	XVtc_SourceSelect SourceSelect;

	Polarity.HSyncPol        = Timing->HSyncPolarity;
	Polarity.VSyncPol        = Timing->VSyncPolarity;
	Polarity.HBlankPol       = 1;
	Polarity.VBlankPol       = 1;
	Polarity.ActiveVideoPol  = 1;
	Polarity.ActiveChromaPol = 1;
	Polarity.FieldIdPol      = 0;
	XVtc_SetPolarity(Instance, &Polarity);

	HoriOffsets.V0BlankHoriEnd   = Timing->LineWidth;
	HoriOffsets.V0BlankHoriStart = Timing->LineWidth;
	HoriOffsets.V0SyncHoriEnd    = Timing->LineWidth;
	HoriOffsets.V0SyncHoriStart  = Timing->LineWidth;
	XVtc_SetGeneratorHoriOffset(Instance, &HoriOffsets);

	Signal.HActiveStart      = 0;
	Signal.HFrontPorchStart  = Timing->LineWidth;
	Signal.HSyncStart        = Timing->LineWidth + Timing->HFrontPorch;
	Signal.HBackPorchStart   = Timing->LineWidth + Timing->HFrontPorch + Timing->HSyncWidth;
	Signal.HTotal            = Timing->TotalLineWidth;
	Signal.V0ActiveStart     = 0;
	Signal.V0FrontPorchStart = Timing->Field0Height;
	Signal.V0SyncStart       = Timing->Field0Height + Timing->Field0FrontPorch;
	Signal.V0BackPorchStart  = Timing->Field0Height + Timing->Field0FrontPorch + Timing->Field0SyncWidth;
	Signal.V0Total           = Timing->Field0TotalHeight;
	XVtc_SetGenerator(Instance, &Signal);

	SourceSelect.FieldIdPolSrc      = 1;
	SourceSelect.ActiveChromaPolSrc = 1;
	SourceSelect.ActiveVideoPolSrc  = 1;
	SourceSelect.HSyncPolSrc        = 1;
	SourceSelect.VSyncPolSrc        = 1;
	SourceSelect.HBlankPolSrc       = 1;
	SourceSelect.VBlankPolSrc       = 1;
	SourceSelect.VChromaSrc         = 1;
	SourceSelect.VActiveSrc         = 1;
	SourceSelect.VBackPorchSrc      = 1;
	SourceSelect.VSyncSrc           = 1;
	SourceSelect.VFrontPorchSrc     = 1;
	SourceSelect.VTotalSrc          = 1;
	SourceSelect.HActiveSrc         = 1;
	SourceSelect.HBackPorchSrc      = 1;
	SourceSelect.HSyncSrc           = 1;
	SourceSelect.HFrontPorchSrc     = 1;
	SourceSelect.HTotalSrc          = 1;
	XVtc_SetSource(Instance, &SourceSelect);

	XVtc_RegUpdate(Instance);
};

void XVtc_Start(XVtc *Instance)
{
	debug_printf("Start Video Timing Controller\r\n");

	XVtc_Enable(Instance, XVTC_EN_GENERATOR);
}

void XVtc_Stop(XVtc *Instance)
{
	debug_printf("Stop Video Timing Controller\r\n");

	XVtc_Disable(Instance, XVTC_EN_GENERATOR);
}
