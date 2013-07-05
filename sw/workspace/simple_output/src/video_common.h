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

#ifndef COMMON_H_
#define COMMON_H_


#include "xil_types.h"


// Turn on/off Debug messages
#ifdef DEBUG_PRINT
#define  debug_printf  xil_printf
#else
#define  debug_printf(msg, args...) do {  } while (0)
#endif


// ARGB32 colors [0, 255]
#define ARGB32_WHITE    0x00FFFFFF
#define ARGB32_YELLOW   0x00FFFF00
#define ARGB32_CYAN     0x0000FFFF
#define ARGB32_GREEN    0x0000FF00
#define ARGB32_MAGENTA  0x00FF00FF
#define ARGB32_RED      0x00FF0000
#define ARGB32_BLUE     0x000000FF
#define ARGB32_BLACK    0x00000000

// VYUY colors [16, 235]
#define VYUY_WHITE      0x80EB80EB
#define VYUY_YELLOW     0x92D208D2
#define VYUY_CYAN       0x08AAA6AA
#define VYUY_GREEN      0x22913691
#define VYUY_MAGENTA    0xDE6ACa6A
#define VYUY_RED        0xF0515A51
#define VYUY_BLUE       0x6E29F029
#define VYUY_BLACK      0x80088008


#define NAME_SIZE 32


enum VideoTimingId {
	V_WUXGA,
	V_1080p,
	V_WSXGAplus,
	V_SXGA,
	V_720p,
	V_XGA,
	V_SVGA,
	V_576p,
	V_VGA
};

typedef struct {
	char Name[NAME_SIZE];
	enum VideoTimingId Id;
	u32 LineWidth;
	u32 HFrontPorch;
	u32 HSyncWidth;
	u32 HBackPorch;
	u32 TotalLineWidth;
	u32 Field0Height;
	u32 Field0FrontPorch;
	u32 Field0SyncWidth;
	u32 Field0BackPorch;
	u32 Field0TotalHeight;
	u32 Field1Height;
	u32 Field1FrontPorch;
	u32 Field1SyncWidth;
	u32 Field1BackPorch;
	u32 Field1TotalHeight;
	u32 HSyncPolarity;
	u32 VSyncPolarity;
	u32 VideoClkFrequency;
} VideoTiming;

enum VideoFormatId {
	V_ARGB32,  // The frame is stored using a 32-bit ARGB format (0xAARRGGBB)
	V_VYUY,    // The frame is stored using an 8-bit per component packed YUV format
			   // with the U and V planes horizontally sub-sampled (V-Y-U-Y),
	           // i.e. two horizontally adjacent pixels are stored as a 32-bit macropixel
	           // which has a Y value for each pixel and common U and V values.
	V_VYUY_emb_sync  // same as above but using embedded sync signals instead
};

typedef struct {
	char Name[NAME_SIZE];
	enum VideoFormatId Id;
	u8 BytesPerPixel;
} VideoFormat;


void ReportVideoTiming(const VideoTiming *Data);
const VideoTiming *LookupVideoTiming_ById(enum VideoTimingId Id);
const VideoTiming *LookupVideoTiming_ByDimensions(u32 Width, u32 Height);

void ReportVideoFormat(const VideoFormat *Format);
const VideoFormat *LookupVideoFormat_ById(enum VideoFormatId Id);


#endif /* COMMON_H_ */
