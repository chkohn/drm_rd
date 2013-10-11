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
#include "gpio.h"
#include "xiicps_adapter.h"
#include "xgpiops_adapter.h"

#include "xparameters_zc702.h"
#include "drivers/pca954x/pca954x.h"
#include "drivers/si570/si570.h"
#include "drivers/adv7511/adv7511.h"
#include "drivers/fmc_ipmi/fmc_ipmi.h"
#include "drivers/pca953x/pca953x.h"
#include "drivers/adv7611/adv7611.h"


// Frame Buffer Base Addresses
#define FB0_ADDR 0x30000000
#define FB1_ADDR 0x307E9000
#define FB2_ADDR 0x30FD2000
#define TMP_ADDR 0x317BB000


// Drivers
XIicPs *XIicPs_0;
IicAdapter *IicAdapter_XIicPs_0;
XGpioPs *XGpioPs_0;
GpioAdapter *XGpioPs_Adapter_0;
PCA954X *IicMux_0;
SI570 *SI570_0;
ADV7511 *ADV7511_0;
XIicPs *XIicPs_1;
IicAdapter *IicAdapter_XIicPs_1;
PCA954X *IicMux_1;
PCA953X *PCA953X_0;
GpioAdapter *PCA953X_Adapter_0;
ADV7611 *ADV7611_0;
FMC_IPMI *FMC_IPMI_1;
XAxiVdma *XAxiVdma_0;
XAxiVdma *XAxiVdma_1;
XAxiVdma *XAxiVdma_2;
XAxiVdma *XAxiVdma_3;
XVtc *XVtc_0;
XVtc *XVtc_1;
XOSD *XOSD_0;
XSobel_filter* XSobel_filter_0;

// GPIO Pins
GpioPin VMux_SELECT;
GpioPin IicMux_0_RST_B;
GpioPin IicMux_1_RST_B;
GpioPin ADV7611_HDMII_RST_B;
GpioPin ADV7611_HDMII_HPD_CTRL;
GpioPin ADV7511_HDMIO_HPD;
GpioPin ADV7511_HDMIO_PD;

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


// Program and initialize ADV7611
void ADV7611_Setup(ADV7611 *Instance)
{
	// hide HDMI receiver till EDID is written
	ADV7611_Hpd(0);
	usleep(SLEEP_100MS);

	// release reset
	ADV7611_Reset(0);
	usleep(SLEEP_100MS);

	// program IIC addresses
	ADV7611_ProgramIicAddresses(Instance);

	// write EDID
	ADV7611_WriteEDID(Instance);

	// allow HDMI source to detect the HDMI receiver
	ADV7611_Hpd(1);
	usleep(SLEEP_100MS);

	// write HDMI config
	ADV7611_WriteConfig(Instance);
}


// Read video timing parameters from ADV7611
const VideoTiming *ADV7611_GetVideoTiming(ADV7611 *Instance)
{
	ADV7611_VideoData VideoDataIn;
	ADV7611_GetTiming(Instance, &VideoDataIn);

	return LookupVideoTiming_ByDimensions(VideoDataIn.LineWidth, VideoDataIn.Field0Height);
}


// Configure video pipeline
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
	int sel = VMUX_SELECT_EXT;
	enum TPG_Pattern pattern = V_TPG_ZonePlate;

	// Set Video Mux
	VMux_Select(sel);
	if (sel == VMUX_SELECT_EXT) {
//		XVtc_GetTiming(XVtc_0);
		pattern = V_TPG_ExtVideo;
	}

	// Configure and Start Video Timing Controller
	XVtc_Configure(XVtc_1, Timing);
	XVtc_Start(XVtc_1);

	// Configure and Start Test Pattern Generator
	TPG_SetPattern(pattern, 1);
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
//	int ExtVideoEnable = 0;

	// Set Video Formats
	FormatOUT0 = LookupVideoFormat_ById(V_ARGB32);
	FormatOUT1 = LookupVideoFormat_ById(V_VYUY);
	FormatOUT2 = LookupVideoFormat_ById(V_VYUY);
	FormatM2M = LookupVideoFormat_ById(V_VYUY);
	FormatCAP = LookupVideoFormat_ById(V_VYUY);

    // Initialize PS GPIO Adapter
    XGpioPs_0 = XGpioPs_Initialize(XPAR_XGPIOPS_0_DEVICE_ID);
    XGpioPs_Adapter_0 = XGpioPs_RegisterAdapter((void *) XGpioPs_0);
    Gpio_Connect(&IicMux_0_RST_B, XGpioPs_Adapter_0, 13, GPIO_DIR_OUT);
    Gpio_Connect(&IicMux_1_RST_B, XGpioPs_Adapter_0, 54, GPIO_DIR_OUT);
    Gpio_Connect(&VMux_SELECT, XGpioPs_Adapter_0, 55, GPIO_DIR_OUT);

    // Initialize PS I2C0 Adapter
    XIicPs_0 = XIicPs_Initialize(XPAR_XIICPS_0_DEVICE_ID, 100000);
    IicAdapter_XIicPs_0 = XIicPs_RegisterAdapter((void *) XIicPs_0);

    // Initialize I2C Mux
    IicMux_0 = PCA954X_Initialize(XPAR_PCA954X_0_DEVICE_ID, IicAdapter_XIicPs_0);
    IicMux_0_ToggleReset();

    // Initialize Clock Synthesizer
    SI570_0 = SI570_Initialize(XPAR_SI570_0_DEVICE_ID, IicMux_0->VirtAdapter[0]);

    // Initialize HDMI Output
	ADV7511_0 = ADV7511_Initialize(XPAR_ADV7511_0_DEVICE_ID, IicMux_0->VirtAdapter[1]);

	// Initialize External Video Input on FMC (if present)
	FMC_IPMI_1 = FMC_IPMI_Initialize(XPAR_FMC_IPMI_1_DEVICE_ID, IicMux_0->VirtAdapter[6]);

	if (FMC_IPMI_1 == NULL) {
		xil_printf("INFO : No FMC card detected on FMC2... disabling external video input!\n\r\n\r");
	} else {
		FRU_Board *BoardInfo = (FRU_Board *) &FMC_IPMI_1->BoardInfo;

		if (strcmp((char *) BoardInfo->Mfg, "Avnet") == 0 && strcmp((char *) BoardInfo->Prod, "FMC-IMAGEON") == 0) {
			xil_printf("INFO : %s %s detected on FMC2... enabling external video input!\n\r\n\r", BoardInfo->Mfg, BoardInfo->Prod);

			// Initialize PS IIC1 Adapter
			XIicPs_1 = XIicPs_Initialize(XPAR_XIICPS_1_DEVICE_ID, 100000);
			IicAdapter_XIicPs_1 = XIicPs_RegisterAdapter((void *) XIicPs_1);

			// Initialize FMC IIC Mux
			IicMux_1 = PCA954X_Initialize(XPAR_PCA954X_1_DEVICE_ID, IicAdapter_XIicPs_1);
			IicMux_1_ToggleReset();

			// Initialize FMC GPIO Adapter
			PCA953X_0 = PCA953X_Initialize(XPAR_PCA953X_0_DEVICE_ID, IicMux_1->VirtAdapter[3]);
			PCA953X_Adapter_0 = PCA953X_RegisterAdapter((void *) PCA953X_0);
			Gpio_Connect(&ADV7611_HDMII_RST_B, PCA953X_Adapter_0, 0, GPIO_DIR_OUT);
			Gpio_Connect(&ADV7611_HDMII_HPD_CTRL, PCA953X_Adapter_0, 2, GPIO_DIR_OUT);
			Gpio_Connect(&ADV7511_HDMIO_HPD, PCA953X_Adapter_0, 3, GPIO_DIR_IN);
			Gpio_Connect(&ADV7511_HDMIO_PD, PCA953X_Adapter_0, 4, GPIO_DIR_OUT);

			// Initialize FMC HDMI Input
			ADV7611_0 = ADV7611_Initialize(XPAR_ADV7611_0_DEVICE_ID, IicMux_1->VirtAdapter[2]);
			ADV7611_Setup(ADV7611_0);

//			ExtVideoEnable = 1;
		}
		else {
			xil_printf("INFO : Unknown FMC card detected on FMC2 (%s %s)... disabling external video input!\n\r\n\r", BoardInfo->Mfg, BoardInfo->Prod);
		}
	}

	// Initialize VDMA_0
	XAxiVdma_0 = XAxiVdma_Initialize(XPAR_VIDEO_DISPLAY_AXI_VDMA_2_DEVICE_ID);

	// Initialize VDMA_1
	XAxiVdma_1 = XAxiVdma_Initialize(XPAR_AXI_VDMA_1_DEVICE_ID);

	// Initialize VDMA_3
	XAxiVdma_3 = XAxiVdma_Initialize(XPAR_VIDEO_DISPLAY_AXI_VDMA_3_DEVICE_ID);

	// Initialize Display VTC
	XVtc_0 = XVtc_Initialize(XPAR_VIDEO_DISPLAY_V_TC_1_DEVICE_ID);

	// Initialize OSD
	XOSD_0 = XOSD_Initialize(XPAR_VIDEO_DISPLAY_V_OSD_1_DEVICE_ID);

	// Configure HDMI Output
	Status = ADV7511_SetVideoMode(ADV7511_0, V_VYUY);
	if (Status == XST_FAILURE) {
		xil_printf("ERROR : No monitor detected on HDMI output!\r\n");
		exit(XST_FAILURE);
	}

	// Initialize Capture VTC
	XVtc_1 = XVtc_Initialize(XPAR_VIDEO_CAPTURE_V_TC_1_DEVICE_ID);

	// Initialize VDMA_2
	XAxiVdma_2 = XAxiVdma_Initialize(XPAR_VIDEO_PROCESSING_AXI_VDMA_M2M_DEVICE_ID);

	// Initialize Sobel Filter
	XSobel_filter_0 = XSobel_Initialize(XPAR_VIDEO_PROCESSING_SOBEL_FILTER_1_DEVICE_ID);

    // Configure Video Pipeline
	VideoPipe_Configure(V_1080p);

	printf("Exit simple_output!\r\n");

    return 0;
}
