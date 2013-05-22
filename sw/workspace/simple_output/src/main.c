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

#include <stdio.h>
#include <stdlib.h>

#include "sleep.h"
#include "xil_cache.h"
#include "vdma.h"
#include "xvtc.h"
#include "cresample.h"
#include "rgb2ycrcb.h"
#ifdef USE_TPG
#include "tpg.h"
#endif
#include "xosd.h"
#include "xiicps_adapter.h"
#include "video_common.h"
#include "xparameters_zc702.h"

#include "drivers/pca954x/pca954x.h"
#ifdef USE_SI570
#include "drivers/si570/si570.h"
#endif
#include "drivers/adv7511/adv7511.h"


// Frame Buffer Base Address
#define FB0_ADDR 0x30000000


// Turn on/off Debug messages
#ifdef DEBUG_PRINT
#define  debug_printf  xil_printf
#else
#define  debug_printf(msg, args...) do {  } while (0)
#endif


enum TPG_Pattern {
	V_TPG_ColorBar,
	V_TPG_ZonePlate
};


static const u32 pix_argb32[8] = {
		ARGB32_WHITE,
		ARGB32_YELLOW,
		ARGB32_CYAN,
		ARGB32_GREEN,
		ARGB32_MAGENTA,
		ARGB32_RED,
		ARGB32_BLUE,
		ARGB32_BLACK
};

static const u32 pix_uyvy[8] = {
		UYVY_WHITE,
		UYVY_YELLOW,
		UYVY_CYAN,
		UYVY_GREEN,
		UYVY_MAGENTA,
		UYVY_RED,
		UYVY_BLUE,
		UYVY_BLACK
};


// OSD functions
XOSD *XOSD_Initialize(u16 DeviceId)
{
	XOSD *Instance = malloc(sizeof *Instance);
	XOSD_Config *Config = XOSD_LookupConfig(DeviceId);
	XOSD_CfgInitialize(Instance, Config, Config->BaseAddress);

	return Instance;
}

void XOSD_Configure(XOSD *Instance, int LayerIndex, const VideoTiming *Timing)
{
	debug_printf("Configure On Screen Display\r\n");

	XOSD_RegUpdateDisable(Instance);

	// Set screen size
	XOSD_SetScreenSize(Instance, Timing->LineWidth, Timing->Field0Height);

	// Set up Layer Alpha, Priority, Dimension and enable it
	XOSD_SetLayerAlpha(Instance, LayerIndex, 1, 0xFF);
	XOSD_SetLayerPriority(Instance, LayerIndex, XOSD_LAYER_PRIORITY_0);
	XOSD_SetLayerDimension(Instance, LayerIndex, 0, 0,  Timing->LineWidth, Timing->Field0Height);
	XOSD_EnableLayer(Instance, LayerIndex);

    XOSD_RegUpdateEnable(Instance);
}

void XOSD_Start(XOSD *Instance)
{
	debug_printf("Start On Screen Display\r\n");

	XOSD_Enable(Instance);
}

// VTC functions
// TODO workaround
#if 1
static void StubCallBack(void *CallBackRef)
{
	Xil_AssertVoidAlways();
}

static void StubErrCallBack(void *CallBackRef, u32 ErrorMask)
{
	Xil_AssertVoidAlways();
}

int my_XVtc_CfgInitialize(XVtc *InstancePtr, XVtc_Config *CfgPtr,
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
#if 0
	XVtc_CfgInitialize(Instance, Config, Config->BaseAddress);
#else
	my_XVtc_CfgInitialize(Instance, Config, Config->BaseAddress);
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

// CRESAMPLE functions
void CRESAMPLE_Configure(const VideoTiming *Timing)
{
	debug_printf("Configure Chroma Resampler\r\n");

	CRESAMPLE_RegUpdateDisable(XPAR_CRESAMPLE_0_BASEADDR);
	CRESAMPLE_WriteReg(XPAR_CRESAMPLE_0_BASEADDR, CRESAMPLE_ACTIVE_SIZE, (Timing->Field0Height<<16 | Timing->LineWidth));
    CRESAMPLE_RegUpdateEnable(XPAR_CRESAMPLE_0_BASEADDR);
}

void CRESAMPLE_Start()
{
	debug_printf("Start Chroma Resampler\r\n");

	CRESAMPLE_Enable(XPAR_CRESAMPLE_0_BASEADDR);
}

void CRESAMPLE_Stop()
{
	debug_printf("Stop Chroma Resampler\r\n");

	CRESAMPLE_Disable(XPAR_CRESAMPLE_0_BASEADDR);
}

// RGB functions
void RGB_Configure(const VideoTiming *Timing)
{
	debug_printf("Configure Color Space Converter\r\n");

	RGB_RegUpdateDisable(XPAR_V_RGB2YCRCB_0_BASEADDR);
	RGB_WriteReg(XPAR_V_RGB2YCRCB_0_BASEADDR, RGB_ACTIVE_SIZE, (Timing->Field0Height<<16 | Timing->LineWidth));
    RGB_RegUpdateEnable(XPAR_V_RGB2YCRCB_0_BASEADDR);
}

void RGB_Start()
{
	debug_printf("Start Color Space Converter\r\n");

	RGB_Enable(XPAR_V_RGB2YCRCB_0_BASEADDR);
}

void RGB_Stop()
{
	debug_printf("Stop Color Space Converter\r\n");

	RGB_Disable(XPAR_V_RGB2YCRCB_0_BASEADDR);
}

#ifdef USE_TPG
// TPG functions
void TPG_SetPattern(const enum TPG_Pattern Pattern, int EnableBox)
{
	debug_printf("Set Pattern of Test Pattern Generator\r\n");

	TPG_RegUpdateDisable(XPAR_V_TPG_1_BASEADDR);
	// select Pattern
	if (Pattern == V_TPG_ColorBar) {
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_PATTERN_CONTROL, 0x9);
	} else if (Pattern == V_TPG_ZonePlate) {
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_PATTERN_CONTROL, 0xA);
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_ZPLATE_HOR_CONTROL, (0x0<<16 | 0x90));
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_ZPLATE_VER_CONTROL, (0x0<<16 | 0x3));
	}
	// enable Box
	if (EnableBox) {
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_PATTERN_CONTROL, \
					(TPG_ReadReg(XPAR_V_TPG_1_BASEADDR, TPG_PATTERN_CONTROL) | 0x1020));
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_BOX_COLOR, ARGB32_RED);
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_BOX_SIZE, 0x50);
		TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_MOTION_SPEED, 0xA);
	}
    TPG_RegUpdateEnable(XPAR_V_TPG_1_BASEADDR);
}

void TPG_Configure(const VideoTiming *Timing)
{
	debug_printf("Configure Test Pattern Generator\r\n");

	TPG_RegUpdateDisable(XPAR_V_TPG_1_BASEADDR);
	TPG_WriteReg(XPAR_V_TPG_1_BASEADDR, TPG_ACTIVE_SIZE, (Timing->Field0Height<<16 | Timing->LineWidth));
    TPG_RegUpdateEnable(XPAR_V_TPG_1_BASEADDR);
}

void TPG_Start()
{
	debug_printf("Start Test Pattern Generator\r\n");

	TPG_Enable(XPAR_V_TPG_1_BASEADDR);
}

void TPG_Stop()
{
	debug_printf("Stop Test Pattern Generator\r\n");

	TPG_Disable(XPAR_V_TPG_1_BASEADDR);
}
#endif

#ifdef USE_SI570
// SI570 functions
void SI570_Configure(SI570 *Instance, const VideoTiming *Timing)
{
	debug_printf("Configure Video Clock Synthesizer\r\n");

	SI570_SetFrequency(Instance, (unsigned long long) (Timing->VideoClkFrequency * 1000));
    usleep(100000);
    printf("Video Clock Frequency: %llu Hz\n\r", SI570_GetFrequency(Instance));
}
#endif

#ifndef USE_TPG
// Initialize frame buffer
void FB_Initialize(u32 BaseAddr, const VideoTiming *Timing, const VideoFormat *Format, int FrameCnt)
{
	u32 fcnt, row, col;
	u32 addr = BaseAddr;

	for (fcnt = 0; fcnt < FrameCnt; fcnt++) {
		for (row = 0; row < Timing->Field0Height; row++) {
			for (col = 0; col < Timing->LineWidth; col++) {
				if (Format->Id == V_ARGB32)
					Xil_Out32(addr, pix_argb32[col / (Timing->LineWidth / 8)]);
				else if (Format->Id == V_UYVY)
					Xil_Out32(addr, pix_uyvy[col / (Timing->LineWidth / 8)]);
				addr += 4;
			}
		}
	}

	Xil_DCacheFlush();
}
#endif

// main
int main()
{
	int Status;
	const VideoTiming *Timing = LookupVideoTiming_ById(V_1080p);
	const VideoFormat *Format= LookupVideoFormat_ById(V_ARGB32);

	printf("Video Output Resolution: %ux%u @ 60fps\r\n", Timing->LineWidth, Timing->Field0Height);

    // Initialize PS I2C0 Adapter
    XIicPs *XIicPs_0 = XIicPs_Initialize(XPAR_XIICPS_0_DEVICE_ID, 100000);
    IicAdapter *IicAdapter_XIicPs_0 = XIicPs_RegisterAdapter((void *) XIicPs_0);

    // Initialize I2C Mux
    PCA954X *IicMux_0 = PCA954X_Initialize(XPAR_PCA954X_0_DEVICE_ID, IicAdapter_XIicPs_0);

#ifdef USE_SI570
    // Initialize Clock Synthesizer
    SI570 *SI570_0 = SI570_Initialize(XPAR_SI570_0_DEVICE_ID, IicMux_0->VirtAdapter[0]);
#endif

    // Initialize HDMI Output
	ADV7511 *ADV7511_0 = ADV7511_Initialize(XPAR_ADV7511_0_DEVICE_ID, IicMux_0->VirtAdapter[1]);

	// Initialize VDMA
	XAxiVdma *XAxiVdma_0 = XAxiVdma_Initialize(XPAR_AXI_VDMA_0_DEVICE_ID);

	// Initialize VTC
	XVtc *XVtc_0 = XVtc_Initialize(XPAR_V_TC_0_DEVICE_ID);

	// Initialize OSD
	XOSD *XOSD_0 = XOSD_Initialize(XPAR_V_OSD_0_DEVICE_ID);

#ifndef USE_TPG
	// Initialize FB0
	FB_Initialize(FB0_ADDR, Timing, Format, XAxiVdma_0->MaxNumFrames);
#endif

#ifdef USE_SI570
    // Configure Clock Synthesizer
    SI570_Configure(SI570_0, Timing);
#endif

	// Configure HDMI Output
	Status = ADV7511_SetVideoMode(ADV7511_0, V_UYVY);
	if (Status == XST_FAILURE) {
		xil_printf("ERROR : No monitor detected on HDMI output!\r\n");
		exit(XST_FAILURE);
	}

    // Configure and Start VTC
	XVtc_Configure(XVtc_0, Timing);
	XVtc_Start(XVtc_0);

	// Configure and Start Chroma Resampler
    CRESAMPLE_Configure(Timing);
    CRESAMPLE_Start();

    // Configure and Start Color Space Converter
    RGB_Configure(Timing);
    RGB_Start();

	// Configure and Start On Screen Display
	XOSD_Configure(XOSD_0, 0, Timing);
	XOSD_Start(XOSD_0);

	// Configure and Start VDMA MM2S
	XAxiVdma_SetupReadChannel(XAxiVdma_0, Timing, Format, FB0_ADDR, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_0, XAXIVDMA_READ);

#ifdef USE_TPG
    // Configure and Start Test Pattern Generator
    TPG_SetPattern(V_TPG_ColorBar, 1);
    TPG_Configure(Timing);
    TPG_Start();

	// Configure and Start VDMA S2MM
	XAxiVdma_SetupWriteChannel(XAxiVdma_0, Timing, Format, FB0_ADDR, 3, 1);
	XAxiVdma_DmaStart(XAxiVdma_0, XAXIVDMA_WRITE);
#endif

	printf("Exit simple_output!\r\n");

    return 0;
}
