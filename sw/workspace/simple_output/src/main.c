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
#include "video_common.h"
#include "vdma.h"
#include "osd.h"
#include "vtc.h"
#include "ccresample.h"
#include "crgb2ycrcb.h"
#include "ctpg.h"
#include "sobel.h"
#include "xiicps_adapter.h"

#include "xparameters_zc702.h"
#include "drivers/pca954x/pca954x.h"
#include "drivers/si570/si570.h"
#include "drivers/adv7511/adv7511.h"


// Frame Buffer Base Addresses
#define FB0_ADDR 0x30000000
#define FB1_ADDR 0x307E9000
#define FB2_ADDR 0x30FD2000
#define TMP_ADDR 0x317BB000


// Drivers
XIicPs *XIicPs_0;
IicAdapter *IicAdapter_XIicPs_0;
PCA954X *IicMux_0;
SI570 *SI570_0;
ADV7511 *ADV7511_0;
XAxiVdma *XAxiVdma_0;
XAxiVdma *XAxiVdma_1;
XAxiVdma *XAxiVdma_2;
XAxiVdma *XAxiVdma_3;
XVtc *XVtc_0;
XOSD *XOSD_0;
XSobel_filter* XSobel_filter_0;

// Video Formats
const VideoFormat *FormatOUT0;
const VideoFormat *FormatOUT1;
const VideoFormat *FormatOUT2;
const VideoFormat *FormatM2M;
const VideoFormat *FormatCAP;


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

static const u32 pix_vyuy[8] = {
		VYUY_BLACK,
		VYUY_BLUE,
		VYUY_RED,
		VYUY_MAGENTA,
		VYUY_GREEN,
		VYUY_CYAN,
		VYUY_YELLOW,
		VYUY_WHITE
};


// SI570 functions
void SI570_Configure(SI570 *Instance, const VideoTiming *Timing)
{
	debug_printf("Configure Video Clock Synthesizer\r\n");

	SI570_SetFrequency(Instance, (unsigned long long) (Timing->VideoClkFrequency * 1000));
    usleep(100000);
    debug_printf("Video Clock Frequency: %llu Hz\n\r", SI570_GetFrequency(Instance));
}


// Initialize frame buffer
void FB_Initialize(u32 BaseAddr, const VideoTiming *Timing, const VideoFormat *Format, int BufCnt)
{
	u32 buf, row, col;
	u32 addr = BaseAddr;

	u32 RowCnt = Timing->Field0Height;
	u32 ColCnt = Timing->LineWidth * Format->BytesPerPixel / 4;

	for (buf = 0; buf < BufCnt; buf++) {
		for (row = 0; row < RowCnt; row++) {
			for (col = 0; col < ColCnt; col++) {
				if (Format->Id == V_ARGB32)
					Xil_Out32(addr, pix_argb32[col / (ColCnt / 8)]);
				else if (Format->Id == V_VYUY)
					Xil_Out32(addr, pix_vyuy[col / (ColCnt / 8)]);
				addr += 4;
			}
		}
	}

	Xil_DCacheFlush();
}


void VideoPipe_Configure(const enum VideoTimingId Id)
{
	u32 tpg_addr = FB1_ADDR;
	u32 layer;
	const VideoTiming *Timing = LookupVideoTiming_ById(Id);

	debug_printf("Video Output Resolution: %ux%u @ 60fps\r\n", Timing->LineWidth, Timing->Field0Height);

#if defined(USE_OUT0) || defined(USE_OUT1) || defined(USE_OUT2)
	// Configure Clock Synthesizer
	SI570_Configure(SI570_0, Timing);

	// Configure and Start Video Timing Controller
	XVtc_Configure(XVtc_0, Timing);
	XVtc_Start(XVtc_0);

	// Configure and Start On Screen Display
	XOSD_Configure(XOSD_0, Timing);
	XOSD_Start(XOSD_0);
#endif

#ifdef USE_OUT0
	// Write pattern to FB0
	FB_Initialize(FB0_ADDR, Timing, FormatOUT0, XAxiVdma_0->MaxNumFrames);

	// Configure Layer 0
	layer = 0;
	XOSD_RegUpdateDisable(XOSD_0);
	XOSD_DisableLayer(XOSD_0, layer);
	XOSD_SetLayerAlpha(XOSD_0, layer, 1, 0xff);
	XOSD_SetLayerPriority(XOSD_0, layer, XOSD_LAYER_PRIORITY_0);
	XOSD_SetLayerDimension(XOSD_0, layer, 0, 0, Timing->LineWidth, Timing->Field0Height);
	XOSD_EnableLayer(XOSD_0, layer);
	XOSD_RegUpdateEnable(XOSD_0);

	// Configure and Start Chroma Resampler
	CRESAMPLE_Configure(Timing);
	CRESAMPLE_Start();

	// Configure and Start Color Space Converter
	RGB_Configure(Timing);
	RGB_Start();

	// Configure and Start VDMA0 MM2S
	XAxiVdma_SetupReadChannel(XAxiVdma_0, Timing, FormatOUT0, FB0_ADDR, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_0, XAXIVDMA_READ);
#endif

#ifdef USE_OUT1
#if !defined(USE_CAP) && !defined(USE_M2M)
	// Write pattern to FB0
	FB_Initialize(FB1_ADDR, Timing, FormatOUT1, XAxiVdma_1->MaxNumFrames);
#endif

	// Configure Layer 1
	layer = 1;
	XOSD_RegUpdateDisable(XOSD_0);
	XOSD_DisableLayer(XOSD_0, layer);
	XOSD_SetLayerAlpha(XOSD_0, layer, 1, 0x80);
	XOSD_SetLayerPriority(XOSD_0, layer, XOSD_LAYER_PRIORITY_1);
	XOSD_SetLayerDimension(XOSD_0, layer, 0, 0, Timing->LineWidth, Timing->Field0Height);
	XOSD_EnableLayer(XOSD_0, layer);
	XOSD_RegUpdateEnable(XOSD_0);

	// Configure and Start VDMA1 MM2S
	XAxiVdma_SetupReadChannel(XAxiVdma_1, Timing, FormatOUT1, FB1_ADDR, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_1, XAXIVDMA_READ);
#endif

#ifdef USE_OUT2
#if !defined(USE_SCALER)
	// Write pattern to FB0
	FB_Initialize(FB2_ADDR, Timing, FormatOUT2, XAxiVdma_3->MaxNumFrames);
#endif

	// Configure Layer 2
	layer = 2;
	XOSD_RegUpdateDisable(XOSD_0);
	XOSD_DisableLayer(XOSD_0, layer);
	XOSD_SetLayerAlpha(XOSD_0, layer, 1, 0x40);
	XOSD_SetLayerPriority(XOSD_0, layer, XOSD_LAYER_PRIORITY_2);
	XOSD_SetLayerDimension(XOSD_0, layer, 0, 0, Timing->LineWidth, Timing->Field0Height);
	XOSD_EnableLayer(XOSD_0, layer);
	XOSD_RegUpdateEnable(XOSD_0);

	// Configure and Start VDMA1 MM2S
	XAxiVdma_SetupReadChannel(XAxiVdma_3, Timing, FormatOUT2, FB2_ADDR, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_3, XAXIVDMA_READ);
#endif

#ifdef USE_M2M
	tpg_addr = TMP_ADDR;

#ifndef USE_CAP
	// Write pattern to FB0
	FB_Initialize(tpg_addr, Timing, FormatM2M, XAxiVdma_1->MaxNumFrames);
#endif

	// Configure and Start Sobel Filter
	XSobel_Configure(XSobel_filter_0, Timing);
	XSobel_Start(XSobel_filter_0);

	// Configure and Start VDMA2 S2MM
	XAxiVdma_SetupWriteChannel(XAxiVdma_2, Timing, FormatM2M, FB1_ADDR, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_2, XAXIVDMA_WRITE);

	// Configure and Start VDMA2 MM2S
	XAxiVdma_SetupReadChannel(XAxiVdma_2, Timing, FormatM2M, tpg_addr, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_2, XAXIVDMA_READ);
#endif

#ifdef USE_CAP
	// Configure and Start Test Pattern Generator
	TPG_SetPattern(V_TPG_ZonePlate, 1);
	TPG_Configure(Timing);
	TPG_Start();

	// Configure and Start VDMA1 S2MM
	XAxiVdma_SetupWriteChannel(XAxiVdma_1, Timing, FormatCAP, tpg_addr, 1, 1);
	XAxiVdma_DmaStart(XAxiVdma_1, XAXIVDMA_WRITE);
#endif
}


// main
int main()
{
	int Status;

	// Set Video Formats
	FormatOUT0 = LookupVideoFormat_ById(V_ARGB32);
	FormatOUT1 = LookupVideoFormat_ById(V_VYUY);
	FormatOUT2 = LookupVideoFormat_ById(V_VYUY);
	FormatM2M = LookupVideoFormat_ById(V_VYUY);
	FormatCAP = LookupVideoFormat_ById(V_VYUY);

    // Initialize PS I2C0 Adapter
    XIicPs_0 = XIicPs_Initialize(XPAR_XIICPS_0_DEVICE_ID, 100000);
    IicAdapter_XIicPs_0 = XIicPs_RegisterAdapter((void *) XIicPs_0);

    // Initialize I2C Mux
    IicMux_0 = PCA954X_Initialize(XPAR_PCA954X_0_DEVICE_ID, IicAdapter_XIicPs_0);

    // Initialize Clock Synthesizer
    SI570_0 = SI570_Initialize(XPAR_SI570_0_DEVICE_ID, IicMux_0->VirtAdapter[0]);

    // Initialize HDMI Output
	ADV7511_0 = ADV7511_Initialize(XPAR_ADV7511_0_DEVICE_ID, IicMux_0->VirtAdapter[1]);

	// Initialize VDMA_0
	XAxiVdma_0 = XAxiVdma_Initialize(XPAR_VIDEO_DISPLAY_AXI_VDMA_2_DEVICE_ID);

	// Initialize VDMA_1
	XAxiVdma_1 = XAxiVdma_Initialize(XPAR_AXI_VDMA_1_DEVICE_ID);

	// Initialize VDMA_2
	XAxiVdma_2 = XAxiVdma_Initialize(XPAR_VIDEO_PROCESSING_AXI_VDMA_M2M_DEVICE_ID);

	// Initialize VDMA_3
	XAxiVdma_3 = XAxiVdma_Initialize(XPAR_VIDEO_DISPLAY_AXI_VDMA_3_DEVICE_ID);

	// Initialize Sobel Filter
	XSobel_filter_0 = XSobel_Initialize(XPAR_VIDEO_PROCESSING_SOBEL_FILTER_1_DEVICE_ID);

	// Initialize VTC
	XVtc_0 = XVtc_Initialize(XPAR_VIDEO_DISPLAY_V_TC_1_DEVICE_ID);

	// Initialize OSD
	XOSD_0 = XOSD_Initialize(XPAR_VIDEO_DISPLAY_V_OSD_1_DEVICE_ID);

	// Configure HDMI Output
	Status = ADV7511_SetVideoMode(ADV7511_0, V_VYUY);
	if (Status == XST_FAILURE) {
		xil_printf("ERROR : No monitor detected on HDMI output!\r\n");
		exit(XST_FAILURE);
	}

    // Configure Video Pipeline
	VideoPipe_Configure(V_1080p);

	printf("Exit simple_output!\r\n");

    return 0;
}
