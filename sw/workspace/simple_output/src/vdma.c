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

#include <stdlib.h>
#include "vdma.h"
#include "xil_printf.h"

#define INITIALIZATION_POLLING   100000


XAxiVdma *XAxiVdma_Initialize(u16 DeviceId)
{
	XAxiVdma *Instance = malloc(sizeof *Instance);
	XAxiVdma_Config *Config = XAxiVdma_LookupConfig(DeviceId);
	XAxiVdma_CfgInitialize(Instance, Config, Config->BaseAddress);

	return Instance;
}

static int XAxiVdma_ResetChannel(XAxiVdma *InstancePtr, u16 Direction)
{
	XAxiVdma_Channel *Channel;
	int Polls;

	Channel = XAxiVdma_GetChannel(InstancePtr, Direction);

	XAxiVdma_ChannelReset(Channel);

	Polls = INITIALIZATION_POLLING;

	while (Polls && XAxiVdma_ChannelResetNotDone(Channel))
		Polls -= 1;

	if (!Polls) {
		xdbg_printf(XDBG_DEBUG_ERROR, "Read channel reset failed %x\n\r", (unsigned int) XAxiVdma_ChannelGetStatus(Channel));
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int XAxiVdma_SetupReadChannel(XAxiVdma *InstancePtr, const VideoTiming *Timing, const VideoFormat *Format, u32 ReadAddrBase, int FrameStore, u8 UseSOF)
{
	int Index;
	u32 Addr;
	int Status;
	XAxiVdma_DmaSetup ReadCfg;

	if (FrameStore > InstancePtr->MaxNumFrames) {
		xil_printf("Read channel requested frame store (%d) exceeds max number frames (%d)", FrameStore, InstancePtr->MaxNumFrames);
		return XST_FAILURE;
	}

//	XAxiVdma_ResetChannel(InstancePtr, XAXIVDMA_READ);
	XAxiVdma_SetFrmStore(InstancePtr, FrameStore, XAXIVDMA_READ);
	if (UseSOF)
		XAxiVdma_FsyncSrcSelect(InstancePtr, XAXIVDMA_S2MM_TUSER_FSYNC, XAXIVDMA_READ);
	else
		XAxiVdma_FsyncSrcSelect(InstancePtr, XAXIVDMA_CHAN_FSYNC, XAXIVDMA_READ);

	ReadCfg.VertSizeInput = Timing->Field0Height;
	ReadCfg.HoriSizeInput = Timing->LineWidth * Format->BytesPerPixel;

	ReadCfg.Stride = ReadCfg.HoriSizeInput;
	ReadCfg.FrameDelay = 0;  /* This example does not test frame delay */

	ReadCfg.EnableCircularBuf = 1;
	ReadCfg.EnableSync = 0;  /* No Gen-Lock */

	ReadCfg.PointNum = 0;    /* No Gen-Lock */
	ReadCfg.EnableFrameCounter = 0; /* Endless transfers */

	ReadCfg.FixedFrameStoreAddr = 0; /* We are not doing parking */

	Status = XAxiVdma_DmaConfig(InstancePtr, XAXIVDMA_READ, &ReadCfg);
	if (Status != XST_SUCCESS) {
		xil_printf("Read channel config failed %d\r\n", Status);
		return XST_FAILURE;
	}

	/* Initialize buffer addresses
	 *
	 * These addresses are physical addresses
	 */
	Addr = ReadAddrBase;
	for(Index = 0; Index < FrameStore; Index++) {
		ReadCfg.FrameStoreStartAddr[Index] = Addr;
		Addr += ReadCfg.VertSizeInput * ReadCfg.HoriSizeInput;
	}

	/* Set the buffer addresses for transfer in the DMA engine
	 * The buffer addresses are physical addresses
	 */
	Status = XAxiVdma_DmaSetBufferAddr(InstancePtr, XAXIVDMA_READ, ReadCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("Read channel set buffer address failed %d\r\n", Status);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int XAxiVdma_SetupWriteChannel(XAxiVdma *InstancePtr, const VideoTiming *Timing, const VideoFormat *Format, u32 WriteAddrBase, int FrameStore, u8 UseSOF)
{
	int Index;
	u32 Addr;
	int Status;
	XAxiVdma_DmaSetup WriteCfg;

	if (FrameStore > InstancePtr->MaxNumFrames) {
		xil_printf("Write channel requested frame store (%d) exceeds max number frames (%d)", FrameStore, InstancePtr->MaxNumFrames);
		return XST_FAILURE;
	}

//	XAxiVdma_ResetChannel(InstancePtr, XAXIVDMA_WRITE);
	XAxiVdma_SetFrmStore(InstancePtr, InstancePtr->MaxNumFrames, XAXIVDMA_WRITE);
	if (UseSOF)
		XAxiVdma_FsyncSrcSelect(InstancePtr, XAXIVDMA_S2MM_TUSER_FSYNC, XAXIVDMA_WRITE);
	else
		XAxiVdma_FsyncSrcSelect(InstancePtr, XAXIVDMA_CHAN_FSYNC, XAXIVDMA_WRITE);

	WriteCfg.VertSizeInput = Timing->Field0Height;
	WriteCfg.HoriSizeInput = Timing->LineWidth * Format->BytesPerPixel;

	WriteCfg.Stride = WriteCfg.HoriSizeInput;
	WriteCfg.FrameDelay = 0;  /* This example does not test frame delay */

	WriteCfg.EnableCircularBuf = 1;
	WriteCfg.EnableSync = 0;  /* No Gen-Lock */

	WriteCfg.PointNum = 0;    /* No Gen-Lock */
	WriteCfg.EnableFrameCounter = 0; /* Endless transfers */

	WriteCfg.FixedFrameStoreAddr = 0; /* We are not doing parking */

	Status = XAxiVdma_DmaConfig(InstancePtr, XAXIVDMA_WRITE, &WriteCfg);
	if (Status != XST_SUCCESS) {
		xil_printf("Write channel config failed %d\r\n", Status);
		return XST_FAILURE;
	}

	/* Initialize buffer addresses
	 *
	 * Use physical addresses
	 */
	Addr = WriteAddrBase;
	for(Index = 0; Index < FrameStore; Index++) {
		WriteCfg.FrameStoreStartAddr[Index] = Addr;
		Addr += WriteCfg.VertSizeInput * WriteCfg.HoriSizeInput;
	}

	/* Set the buffer addresses for transfer in the DMA engine
	 */
	Status = XAxiVdma_DmaSetBufferAddr(InstancePtr, XAXIVDMA_WRITE, WriteCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("Write channel set buffer address failed %d\r\n", Status);
		return XST_FAILURE;
	}

	/* Clear data buffer
	 */
//	memset((void *) WriteAddrBase, 0, FRAME_HORIZONTAL_LEN * FRAME_VERTICAL_LEN * NUMBER_OF_WRITE_FRAMES);

	return XST_SUCCESS;
}
