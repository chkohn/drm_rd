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

#include <math.h>
#include <stdlib.h>
#include "xil_printf.h"
#include "xstatus.h"
#include "si570.h"


#define ZC702_USRCLK_ADDR 0x5D


const unsigned long long freq_HD1080P = 148500000; // VESA, 1920 x 1080, 148.5   MHz at 60 fps
const unsigned long long freq_WSXGA   = 147140000; // VESA, 1680 x 1050, 147.14  MHz at 60 fps
const unsigned long long freq_SXGA    = 108000000; // VESA, 1280 x 1024, 108     MHz at 60 fps
const unsigned long long freq_HD720P  =  74250000; // VESA, 1280 x  720,  74.25  MHz at 60 fps
const unsigned long long freq_XGA     =  65000000; // VESA, 1024 x  768,  65     MHz at 60 fps
const unsigned long long freq_SVGA    =  40000000; // VESA,  800 x  600,  40     MHz at 60 fps
const unsigned long long freq_VGA     =  25175000; // VESA,  640 x  480,  25.175 MHz at 60 fps



// SI570 Lookup Struct
typedef struct {
	u8 hs_div;
	u8 n1;
	unsigned long long freq;
} ZC702_SI570_LOOKUP;


/*
 * The Data field of the SI570 struct will hold the default register values
 * for registers 0x7 to 0xC of a specific SI570 device on a ZC702 board.
 * On ZC702, the frequency of the SI570 defaults to 156.25 MHz.
 *
 * The Init field of the SI570 struct will hold the derived register values
 * for generating a 148.5 MHz output clock which is our default video clock.
 *
 * The Data and Init fields are populated by calling the zc702_si570_init
 * function.
 */

#define ZC702_USRCLK_CONFIG_LEN  6
static IicMsg zc702_usrclk_config[ZC702_USRCLK_CONFIG_LEN] =
{
	{0x07, 0x00},  // High Speed / N1 Dividers
				   //    R0x07[7:5] = HS_DIV[2:0]
				   //	  R0x07[4:0] = N1[6:2]
	{0x08, 0x00},  // N1 Divider / Reference Frequency
				   //    R0x08[7:6] = N1[1:0]
				   //    R0x08[5:0] = RFREQ[37:32]
	{0x09, 0x00},  //    R0x09[7:0] = RFREQ[31:24]
	{0x0A, 0x00},  //    R0x0A[7:0] = RFREQ[23:16]
	{0x0B, 0x00},  //    R0x0B[7:0] = RFREQ[15: 8]
	{0x0C, 0x00}   //    R0x0C[7:0] = RFREQ[ 7: 0]
//	{0x87, 0x40}   // Reset / Freeze / Memory Control
				   //    R0x87[7] = RST_REG      = 0
				   //    R0x87[6] = NewFreq      = 1
				   //    R0x87[5] = Freeze M     = 0
				   //    R0x87[4] = Freeze VCADC = 0
				   //    R0x87[0] = RECALL       = 0
};


/*
 * The HS_DIV[2:0] value maps to 6 possible DCO High Speed Divider settings.
 * A table is used to define this mapping and enable the 3-bit encoded HS_DIV[2:0] value
 * to be converted into an absolute value.
 *
 *    HS_DIV[2:0]      'HS_DIV' value
 *
 *        000               4
 *        001               5
 *        010               6
 *        011               7
 *        100               -
 *        101               9
 *        110               -
 *        111              11
 */

static const u8 HS_DIV_lookup[8] =
{
	4, 5, 6, 7, 0, 9, 0, 11
};


/*
 * This table maps each of the valid HS_DIV values to a byte value which encodes the
 * HS_DIV[2:0] into bits [7:5] of a byte.
 *
 *  value of    HS_DIV[2:0]       Byte
 *   HS_DIV      encoding       encoding
 *     4            000         00000000 = 00
 *     5            001         00100000 = 20
 *     6            010         01000000 = 40
 *     7            011         01100000 = 60
 *     9            101         10100000 = A0
 *    11            111         11100000 = E0
 */

static const u8 HS_DIV_lookup_reverse[8] =
{
	0x00, 0x20, 0x40, 0x60, 0x00, 0xA0, 0x00, 0xE0
};


/*
 * The DCO must operate in the frequency range 4.85GHz to 5.67GHz. To achieve this an
 * appropriate combination of HS_DIV and N1 divider values must be selected to correspond
 * with the desired output frequency of the Si570.
 *
 *     HS_DIV can only have values 4, 5, 6, 7, 9 or 11.
 *     N1 can only have values 1 and any even number up to 128.
 *
 * The following table was prepared provides suitable pairs of valid HS_DIV and N1 values
 * that cover ranges of the full output frequency spectrum.
 */

#define ZC702_SI570_LOOKUP_LEN 38
static const ZC702_SI570_LOOKUP SI570_lookup[ZC702_SI570_LOOKUP_LEN] =
{
//   HS_DIV  N1    Start of Frequency Range  hex / MHz
	 {7,    70,    0x00989680}, //  10
	 {6,    74,    0x00A7D8C0}, //  11
	 {7,    58,    0x00B71B00}, //  12
	 {7,    50,    0x00D59F80}, //  14
	 {9,    34,    0x00F42400}, //  16
	 {4,    68,    0x0112A880}, //  18
	 {4,    62,    0x01312D00}, //  20
	 {7,    32,    0x014FB180}, //  22
	 {7,    28,    0x017D7840}, //  25
	{11,    16,    0x01AB3F00}, //  28
	 {4,    38,    0x01E84800}, //  32
	{11,    12,    0x02349340}, //  37
	 {6,    20,    0x02719C40}, //  41
	 {4,    26,    0x02CD29C0}, //  47
	 {9,    10,    0x0337F980}, //  54
	 {5,    16,    0x03A2C940}, //  61
	 {7,    10,    0x042C1D80}, //  70
	 {4,    16,    0x0487AB00}, //  76
	 {7,     8,    0x052F83C0}, //  87
	 {5,    10,    0x05D75C80}, //  98
	{11,     4,    0x069DB9C0}, // 111
	 {5,     8,    0x07459280}, // 122
	 {9,     4,    0x080BEFC0}, // 135
	 {4,     8,	   0x090F5600}, // 152
	 {7,     4,    0x0A5F0780}, // 174
	 {6,     4,    0x0C0EDA60}, // 202.3
	{11,     2,	   0x0D2C3140}, // 221
	 {5,     4,    0x0E7BE2C0}, // 243
	 {9,     2,    0x1017DF80}, // 270
	 {4,     4,    0x121EAC00}, // 304
	 {7,     2,	   0x14AECCC0}, // 347
	 {6,     2,    0x1823CF40}, // 405
	{11,     1,    0x1A492040}, // 441
	 {5,     2,    0x1CF7C580}, // 486
	 {9,     1,    0x20207CC0}, // 539
	 {4,     2,    0x242E15C0}, // 607
	 {7,     1,    0x295D9980}, // 694
	 {6,     1,    0x30385C40}  // 809
};


static void SI570_GetDefaults( SI570 *Instance )
{
	u8 n1;
	unsigned long long dco_freq;
	unsigned long long rfreq;
	double rfreq_d;

	// reload default register values from NVM into RAM by setting RECALL bit
	IicMsg Msg = { 0x87, 0x01 };
	Instance->IicAdapter->Funcs->Iic_WriteMsg(Instance->IicAdapter, Instance->Config.IicAddress, &Msg, 1);

	// read default register values of SI570 into zc702_usrclk_config
	Instance->IicAdapter->Funcs->Iic_ReadMsg( Instance->IicAdapter, Instance->Config.IicAddress, zc702_usrclk_config, ZC702_USRCLK_CONFIG_LEN );

	// convert 3-bit HS_DIV value into its true division factor using a lookup table
	Instance->HSDiv = HS_DIV_lookup[zc702_usrclk_config[0].Data >> 5];

	si570_debug_printf("HS_DIV: %d\n\r", Instance->HSDiv);

	// extract 7-bit N1 value into its true division factor
	n1  = zc702_usrclk_config[0].Data << 2;
	n1 |= zc702_usrclk_config[1].Data >> 6;
	n1 &= 0x7f;
	// increment N1 if odd
	n1 = (n1 & 1) ? (n1 + 1) : n1;
	// set N1 to 1 if set to 0
	n1 = (n1 == 0) ? 1 : n1;

	Instance->N1Div = n1;

	si570_debug_printf("N1: %d\n\r", Instance->N1Div);

	// determine DCO frequency corresponding with the default output frequency
	dco_freq = Instance->HSDiv * Instance->N1Div * Instance->Config.FreqDefault;

	si570_debug_printf("DCO frequency: %llu\n\r", dco_freq);

	// extract 38-bit fixed point RFREQ (10-bit integer and 28-bit fraction)
	rfreq  = (unsigned long long) zc702_usrclk_config[1].Data << 32; // 0x08[5:0] = RFREQ[37:32]
	rfreq |= (unsigned long long) zc702_usrclk_config[2].Data << 24; // 0x09[7:0] = RFREQ[31:24]
	rfreq |= (unsigned long long) zc702_usrclk_config[3].Data << 16; // 0x0A[7:0] = RFREQ[23:16]
	rfreq |= (unsigned long long) zc702_usrclk_config[4].Data <<  8; // 0x0B[7:0] = RFREQ[15: 8]
	rfreq |= (unsigned long long) zc702_usrclk_config[5].Data;       // 0x0C[7:0] = RFREQ[ 7: 0]
	rfreq &= 0x3fffffffff;

	Instance->FreqRef = rfreq;

	si570_debug_printf("RFREQ: %llx\n\r", Instance->FreqRef);
	si570_debug_printf("RFREQ: %llu\n\r", Instance->FreqRef);

	rfreq_d = (double) rfreq / pow( 2.0, 28 );

	si570_debug_printf("RFREQ: %f\n\r", rfreq_d);

	Instance->FreqXtal = (unsigned long long) round( (double) dco_freq / rfreq_d );

	si570_debug_printf("XTAL frequency: %llu\n\r", Instance->FreqXtal);

	Instance->FreqOut = Instance->Config.FreqDefault;
}


int SI570_CfgInitialize(SI570 *Instance, SI570_Config *Config)
{
	/*
	 * Assert validates the input arguments.
	 */
	Xil_AssertNonvoid(Instance != NULL);
	Xil_AssertNonvoid(Config != NULL);

	Instance->Config.DeviceId = Config->DeviceId;
	Instance->Config.IicAddress = Config->IicAddress;
	Instance->Config.FreqDefault = Config->FreqDefault;
	Instance->Config.FreqDcoMax = Config->FreqDcoMax;
	Instance->Config.FreqDcoMin = Config->FreqDcoMin;

	return XST_SUCCESS;
}


SI570 *SI570_Initialize( u16 DeviceId, IicAdapter *Adapter )
{
	SI570 *Instance = malloc(sizeof *Instance);
	SI570_Config *Config = SI570_LookupConfig(DeviceId);
	SI570_CfgInitialize(Instance, Config);
	Instance->IicAdapter = Adapter;
	SI570_GetDefaults(Instance);

	return Instance;
}


int SI570_SetFrequency( SI570 *Instance, unsigned long long new_freq )
{
	u8 hs_div;
	u8 n1;
	int i;
	unsigned long long dco_freq;
	unsigned long long rfreq;
	double rfreq_d;

	/*
	 * Determine HS_DIV and N1 such that DCO frequency which is calculated as
	 * HS_DIV x N1 x desired output frequency is operating in the range 4.85 GHz
	 * to 5.67 GHz.
	 */

	// set hs_div and n1 to 809 - 945 MHz frequency range
	if ( new_freq <= Instance->Config.FreqDcoMax && new_freq >= Instance->Config.FreqDcoMin )
	{
		hs_div = SI570_lookup[ZC702_SI570_LOOKUP_LEN-1].hs_div;
		n1 = SI570_lookup[ZC702_SI570_LOOKUP_LEN-1].n1;
	}
	else
	{
		si570_debug_printf("Error: The desired output frequency %llu MHz is out of range (%llu - %llu MHz)!\n\r", \
				new_freq, Instance->Config.FreqDcoMin, Instance->Config.FreqDcoMax);
		return XST_FAILURE;
	}

	/*
	 * Determine if frequency needs to be set to 10 - 809 MHz range and look up
	 * the exact frequency range bracket in lookup table.
	 */
	for (i = 0; i < ZC702_SI570_LOOKUP_LEN-1; i++) {
		if ( new_freq < SI570_lookup[i+1].freq )
		{
			hs_div = SI570_lookup[i].hs_div;
			n1 = SI570_lookup[i].n1;
			break;
		}
	}

	Instance->HSDiv = hs_div;
	Instance->N1Div = n1;

	si570_debug_printf("new HS_DIV: %d\n\r", Instance->HSDiv);
	si570_debug_printf("new N1: %d\n\r", Instance->N1Div);

	// Determine new DCO frequency
	dco_freq = Instance->HSDiv * Instance->N1Div * new_freq;

	si570_debug_printf("new DCO frequency: %llu\n\r", dco_freq);

	// Determine new RFREQ value
	rfreq_d = (double) dco_freq / (double) Instance->FreqXtal;

	si570_debug_printf("new RFREQ: %f\n\r", rfreq_d);

	rfreq = (unsigned long long) round( rfreq_d * pow( 2.0, 28 ) );

	Instance->FreqRef = rfreq;

	si570_debug_printf("new RFREQ: %llu\n\r", Instance->FreqRef);
	si570_debug_printf("new RFREQ: %llx\n\r", Instance->FreqRef);

	// Encode HS_DIV, N1 and set new HS_DIV, N1, and RFREQ in SI570 struct
	zc702_usrclk_config[0].Data  = HS_DIV_lookup_reverse[hs_div - 4];
	zc702_usrclk_config[0].Data |= (n1 - 1) >> 2;
	zc702_usrclk_config[1].Data  = (n1 - 1) << 6;
	zc702_usrclk_config[1].Data |= rfreq >> 32;
	zc702_usrclk_config[2].Data  = rfreq >> 24;
	zc702_usrclk_config[3].Data  = rfreq >> 16;
	zc702_usrclk_config[4].Data  = rfreq >>  8;
	zc702_usrclk_config[5].Data  = rfreq;

	for ( i = 0; i < ZC702_USRCLK_CONFIG_LEN; i++ )
	{
		si570_debug_printf("SI570 0x%02x=0x%02x\n\r", zc702_usrclk_config[i].Register, zc702_usrclk_config[i].Data);
	}

	// send zc702_usrclk_config with new register values to SI570 via IIC
	Instance->IicAdapter->Funcs->Iic_WriteMsg( Instance->IicAdapter, Instance->Config.IicAddress, zc702_usrclk_config, ZC702_USRCLK_CONFIG_LEN );

	// load new register values by setting NewFreq bit
	IicMsg Msg = { 0x87, 0x40 };
	Instance->IicAdapter->Funcs->Iic_WriteMsg(Instance->IicAdapter, Instance->Config.IicAddress, &Msg, 1);

	return XST_SUCCESS;
}


unsigned long long SI570_GetFrequency( SI570 *Instance )
{
	u8  hs_div;
	u8  n1;
	double rfreq_d;
	unsigned long long dco_freq;
	unsigned long long rfreq;
	unsigned long long freq;

	// read current register values of SI570 into zc702_usrclk_config
	Instance->IicAdapter->Funcs->Iic_ReadMsg( Instance->IicAdapter, Instance->Config.IicAddress, zc702_usrclk_config, ZC702_USRCLK_CONFIG_LEN );

	// convert 3-bit HS_DIV value into its true division factor using a lookup table
	hs_div = HS_DIV_lookup[zc702_usrclk_config[0].Data >> 5];

	Instance->HSDiv = hs_div;

	si570_debug_printf("HS_DIV: %d\n\r", Instance->HSDiv);

	// extract 7-bit N1 value into its true division factor
	n1  = zc702_usrclk_config[0].Data << 2;
	n1 |= zc702_usrclk_config[1].Data >> 6;
	n1 &= 0x7f;
	// increment N1 if odd
	n1 = (n1 & 1) ? (n1 + 1) : n1;
	// set N1 to 1 if set to 0
	n1 = (n1 == 0) ? 1 : n1;

	Instance->N1Div = n1;

	si570_debug_printf("N1: %d\n\r", Instance->N1Div);

	// extract 38-bit fixed point RFREQ (10-bit integer and 28-bit fraction)
	rfreq  = (unsigned long long) zc702_usrclk_config[1].Data << 32; // 0x08[5:0] = RFREQ[37:32]
	rfreq |= (unsigned long long) zc702_usrclk_config[2].Data << 24; // 0x09[7:0] = RFREQ[31:24]
	rfreq |= (unsigned long long) zc702_usrclk_config[3].Data << 16; // 0x0A[7:0] = RFREQ[23:16]
	rfreq |= (unsigned long long) zc702_usrclk_config[4].Data <<  8; // 0x0B[7:0] = RFREQ[15: 8]
	rfreq |= (unsigned long long) zc702_usrclk_config[5].Data;       // 0x0C[7:0] = RFREQ[ 7: 0]
	rfreq &= 0x3fffffffff;

	Instance->FreqRef = rfreq;

	si570_debug_printf("RFREQ: %llx\n\r", Instance->FreqRef);
	si570_debug_printf("RFREQ: %llu\n\r", Instance->FreqRef);

	rfreq_d = (double) rfreq / pow( 2.0, 28 );

	si570_debug_printf("RFREQ: %f\n\r", rfreq_d);

	dco_freq = (unsigned long long) round(rfreq_d * (double) Instance->FreqXtal);

	si570_debug_printf("DCO frequency: %llu\n\r", dco_freq);

	freq = dco_freq / (hs_div * n1);

	Instance->FreqOut = freq;

	si570_debug_printf("Output frequency: %llu\n\r", Instance->FreqOut);

	return freq;
}
