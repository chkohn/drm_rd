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

#include "video_common.h"
#include "xil_printf.h"


const VideoTiming VideoData_WUXGA = {
	.Name              = "WUXGA",
	.Id                = V_WUXGA,
	.LineWidth         =   1920,
	.HFrontPorch       =     48,
	.HSyncWidth        =     32,
	.HBackPorch        =     80,
	.TotalLineWidth    =   2080,
	.Field0Height      =   1200,
	.Field0FrontPorch  =      3,
	.Field0SyncWidth   =      6,
	.Field0BackPorch   =     26,
	.Field0TotalHeight =   1235,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency = 154000
};

const VideoTiming VideoData_1080p = {
	.Name              = "1080p",
	.Id                = V_1080p,
	.LineWidth         =   1920,
	.HFrontPorch       =     88,
	.HSyncWidth        =     44,
	.HBackPorch        =    148,
	.TotalLineWidth    =   2200,
	.Field0Height      =   1080,
	.Field0FrontPorch  =      4,
	.Field0SyncWidth   =      5,
	.Field0BackPorch   =     36,
	.Field0TotalHeight =   1125,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency = 148500
};

const VideoTiming VideoData_WSXGAplus = {
	.Name              = "WSXGA+",
	.Id                = V_WSXGAplus,
	.LineWidth         =   1680,
	.HFrontPorch       =     48,
	.HSyncWidth        =     32,
	.HBackPorch        =     80,
	.TotalLineWidth    =   1840,
	.Field0Height      =   1050,
	.Field0FrontPorch  =      3,
	.Field0SyncWidth   =      6,
	.Field0BackPorch   =     21,
	.Field0TotalHeight =   1080,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency = 119000
};

const VideoTiming VideoData_SXGA = {
	.Name              = "SXGA",
	.Id                = V_SXGA,
	.LineWidth         =   1280,
	.HFrontPorch       =     48,
	.HSyncWidth        =    112,
	.HBackPorch        =    248,
	.TotalLineWidth    =   1688,
	.Field0Height      =   1024,
	.Field0FrontPorch  =      1,
	.Field0SyncWidth   =      3,
	.Field0BackPorch   =     38,
	.Field0TotalHeight =   1066,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency = 108000
};

const VideoTiming VideoData_720p = {
	.Name              = "720p",
	.Id                = V_720p,
	.LineWidth         =   1280,
	.HFrontPorch       =    110,
	.HSyncWidth        =     40,
	.HBackPorch        =    220,
	.TotalLineWidth    =   1650,
	.Field0Height      =    720,
	.Field0FrontPorch  =      5,
	.Field0SyncWidth   =      5,
	.Field0BackPorch   =     20,
	.Field0TotalHeight =    750,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency =  74250
};

const VideoTiming VideoData_XGA = {
	.Name              =  "XGA",
	.Id                =  V_XGA,
	.LineWidth         =   1024,
	.HFrontPorch       =     24,
	.HSyncWidth        =    136,
	.HBackPorch        =    160,
	.TotalLineWidth    =   1344,
	.Field0Height      =    768,
	.Field0FrontPorch  =      3,
	.Field0SyncWidth   =      6,
	.Field0BackPorch   =     29,
	.Field0TotalHeight =    806,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency =  65000
};

const VideoTiming VideoData_SVGA = {
	.Name              = "SVGA",
	.Id                = V_SVGA,
	.LineWidth         =    800,
	.HFrontPorch       =     40,
	.HSyncWidth        =    128,
	.HBackPorch        =     88,
	.TotalLineWidth    =   1056,
	.Field0Height      =    600,
	.Field0FrontPorch  =      1,
	.Field0SyncWidth   =      4,
	.Field0BackPorch   =     23,
	.Field0TotalHeight =    628,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency =  40000
};

const VideoTiming VideoData_576p = {
	.Name              = "576p",
	.Id                = V_576p,
	.LineWidth         =    720,
	.HFrontPorch       =     12,
	.HSyncWidth        =     63,
	.HBackPorch        =     69,
	.TotalLineWidth    =    864,
	.Field0Height      =    576,
	.Field0FrontPorch  =      5,
	.Field0SyncWidth   =      5,
	.Field0BackPorch   =     39,
	.Field0TotalHeight =    625,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency =  27000   // 50fps
};

const VideoTiming VideoData_VGA = {
	.Name              =  "VGA",
	.Id                =  V_VGA,
	.LineWidth         =    640,
	.HFrontPorch       =     16,
	.HSyncWidth        =     96,
	.HBackPorch        =     48,
	.TotalLineWidth    =    800,
	.Field0Height      =    480,
	.Field0FrontPorch  =     10,
	.Field0SyncWidth   =      2,
	.Field0BackPorch   =     33,
	.Field0TotalHeight =    525,
	.HSyncPolarity     =      1,
	.VSyncPolarity     =      1,
	.VideoClkFrequency =  25200
};


#define VIDEO_TIMING_ALL_SIZE 9
const VideoTiming *VideoTimingAll[VIDEO_TIMING_ALL_SIZE] = {
	&VideoData_WUXGA,
	&VideoData_1080p,
	&VideoData_WSXGAplus,
	&VideoData_SXGA,
	&VideoData_720p,
	&VideoData_XGA,
	&VideoData_SVGA,
	&VideoData_576p,
	&VideoData_VGA
};


const VideoFormat VideoFormat_ARGB32 = {
	.Name              =  "ARGB32",
	.Id                =  V_ARGB32,
	.BytesPerPixel     =  4
};

const VideoFormat VideoFormat_YUYV = {
	.Name              =  "YUYV",
	.Id                =  V_UYVY,
	.BytesPerPixel     =  2
};

#define VIDEO_FORMAT_ALL_SIZE 2
const VideoFormat *VideoFormatAll[VIDEO_FORMAT_ALL_SIZE] = {
	&VideoFormat_ARGB32,
	&VideoFormat_YUYV
};


void ReportVideoTiming(const VideoTiming *Timing)
{
	xil_printf("VideoTiming       : %6s\n\r", Timing->Name);
	xil_printf("VideoId           : %6d\n\r", Timing->Id);

	xil_printf("LineWidth         : %6d\n\r", Timing->LineWidth);
	xil_printf("HFrontPorch       : %6d\n\r", Timing->HFrontPorch);
	xil_printf("HSyncWidth        : %6d\n\r", Timing->HSyncWidth);
	xil_printf("HBackPorch        : %6d\n\r", Timing->HBackPorch);
	xil_printf("TotalLineWidth    : %6d\n\r", Timing->TotalLineWidth);

	xil_printf("Field0Height      : %6d\n\r", Timing->Field0Height);
	xil_printf("Field0FrontPorch  : %6d\n\r", Timing->Field0FrontPorch);
	xil_printf("Field0SyncWidth   : %6d\n\r", Timing->Field0SyncWidth);
	xil_printf("Field0BackPorch   : %6d\n\r", Timing->Field0BackPorch);
	xil_printf("Field0TotalHeight : %6d\n\r", Timing->Field0TotalHeight);

	xil_printf("HSyncPolarity     : %6d\n\r", Timing->HSyncPolarity);
	xil_printf("VSyncPolarity     : %6d\n\r", Timing->VSyncPolarity);

	xil_printf("VideoClkFrequency : %6d\n\r", Timing->VideoClkFrequency);
}

const VideoTiming *LookupVideoTiming_ByDimensions(u32 Width, u32 Height)
{
	int i;
	for (i = 0; i < VIDEO_TIMING_ALL_SIZE; i++) {
		if (Width  == VideoTimingAll[i]->LineWidth && Height == VideoTimingAll[i]->Field0Height)
			return VideoTimingAll[i];
	}
	return NULL;
}

const VideoTiming *LookupVideoTiming_ById(enum VideoTimingId Id)
{
	int i;
	for (i = 0; i < VIDEO_TIMING_ALL_SIZE; i++) {
		if (Id  == VideoTimingAll[i]->Id)
			return VideoTimingAll[i];
	}
	return NULL;
}

void ReportVideoFormat(const VideoFormat *Format)
{
	xil_printf("VideoFormat       : %6s\n\r", Format->Name);
	xil_printf("VideoId           : %6d\n\r", Format->Id);

	xil_printf("BytesPerPixel     : %6d\n\r", Format->BytesPerPixel);
}

const VideoFormat *LookupVideoFormat_ById(enum VideoFormatId Id)
{
	int i;
	for (i = 0; i < VIDEO_FORMAT_ALL_SIZE; i++) {
		if (Id  == VideoFormatAll[i]->Id)
			return VideoFormatAll[i];
	}
	return NULL;
}

