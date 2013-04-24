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

#ifndef XPARAMETERS_ZC702_H_
#define XPARAMETERS_ZC702_H_


/******************************************************************/

/* Definitions for driver PCA954X */
#define XPAR_PCA954X_NUM_INSTANCES   2

/* Definitions for peripheral PCA954X_0 */
#define XPAR_PCA954X_0_DEVICE_ID     0
#define XPAR_PCA954X_0_IICADDR       0x74
#define XPAR_PCA954X_0_NUM_CHANNELS  8

/* Definitions for peripheral PCA954X_1 */
#define XPAR_PCA954X_1_DEVICE_ID     1
#define XPAR_PCA954X_1_IICADDR       0x70
#define XPAR_PCA954X_1_NUM_CHANNELS  4

/******************************************************************/

/* Definitions for driver SI570 */
#define XPAR_SI570_NUM_INSTANCES   1

/* Definitions for peripheral SI570_0 */
#define XPAR_SI570_0_DEVICE_ID     0
#define XPAR_SI570_0_IICADDR       0x5D
#define XPAR_SI570_0_DEFAULT_FREQ  156250000
#define XPAR_SI570_0_MAX_DCO_FREQ  945000000
#define XPAR_SI570_0_MIN_DCO_FREQ  10000000

/******************************************************************/

/* Definitions for driver ADV7511 */
#define XPAR_ADV7511_NUM_INSTANCES   1

/* Definitions for peripheral ADV7511_0 */
#define XPAR_ADV7511_0_DEVICE_ID     0
#define XPAR_ADV7511_0_IICADDR       0x39

/******************************************************************/

/* Definitions for driver UCD92XX */
#define XPAR_UCD92XX_NUM_INSTANCES  3

/* Definitions for peripheral UCD92XX_0 */
#define XPAR_UCD92XX_0_DEVICE_ID    0
#define XPAR_UCD92XX_0_IICADDR      0x34
#define XPAR_UCD92XX_0_NUM_PAGES    4

/* Definitions for peripheral UCD92XX_1 */
#define XPAR_UCD92XX_1_DEVICE_ID    1
#define XPAR_UCD92XX_1_IICADDR      0x35
#define XPAR_UCD92XX_1_NUM_PAGES    4

/* Definitions for peripheral UCD92XX_2 */
#define XPAR_UCD92XX_2_DEVICE_ID    2
#define XPAR_UCD92XX_2_IICADDR      0x36
#define XPAR_UCD92XX_2_NUM_PAGES    2

/******************************************************************/

/* Definitions for driver FMC_IPMI */
#define XPAR_FMC_IPMI_NUM_INSTANCES  2

/* Definitions for peripheral FMC_IPMI_0 */
#define XPAR_FMC_IPMI_0_DEVICE_ID    0
#define XPAR_FMC_IPMI_0_IICADDR      0x50
#define XPAR_FMC_IPMI_0_FMC_TYPE     0 // LPC

/* Definitions for peripheral FMC_IPMI_1 */
#define XPAR_FMC_IPMI_1_DEVICE_ID    1
#define XPAR_FMC_IPMI_1_IICADDR      0x50
#define XPAR_FMC_IPMI_1_FMC_TYPE     0 // LPC

/******************************************************************/

/* Definitions for driver PCA953X */
#define XPAR_PCA953X_NUM_INSTANCES         1

/* Definitions for peripheral PCA953X_0 */
#define XPAR_PCA953X_0_DEVICE_ID           0
#define XPAR_PCA953X_0_IICADDR             0x20
#define XPAR_PCA953X_0_NUM_GPIO_BANKS      1
#define XPAR_PCA953X_0_GPIO_BANK_SIZE      8
#define XPAR_PCA953X_0_MAX_NUM_GPIO_PORTS  8

/******************************************************************/

/* Definitions for driver ADV7611 */
#define XPAR_ADV7611_NUM_INSTANCES         1

/* Definitions for peripheral ADV7611_0 */
#define XPAR_ADV7611_0_DEVICE_ID           0
#define XPAR_ADV7611_0_IICADDR             0x4C


#endif // XPARAMETERS_ZC702_H_
