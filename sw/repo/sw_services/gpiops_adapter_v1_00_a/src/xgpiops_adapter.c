/*
 * xgpiops_adapter.c
 *
 *  Created on: Jul 12, 2012
 *      Author: ckohn
 */

#include <stdlib.h>
#include "xil_printf.h"
#include "xgpiops_adapter.h"


XGpioPs *XGpioPs_Initialize( u16 DeviceId )
{
	XGpioPs *Instance = malloc(sizeof *Instance);
	XGpioPs_Config *Config = XGpioPs_LookupConfig(DeviceId);
	XGpioPs_CfgInitialize(Instance, Config, Config->BaseAddr);

	return Instance;
}


GpioAdapter *XGpioPs_RegisterAdapter( void *Instance )
{
	static struct GpioAdapterFuncs Funcs = {
		XGpioPs_Gpio_ReadPin,
		XGpioPs_Gpio_WritePin,
		XGpioPs_Gpio_GetDirectionPin,
		XGpioPs_Gpio_SetDirectionPin
	};

	return Gpio_RegisterAdapter( Instance, &Funcs );
}


int XGpioPs_Gpio_ReadPin( GpioAdapter *Adapter, int Pin )
{
    XGpioPs *InstancePtr = (XGpioPs *) (Adapter->Instance);

    return XGpioPs_ReadPin( InstancePtr, Pin );
}


void XGpioPs_Gpio_WritePin( GpioAdapter *Adapter, int Pin, int Data )
{
	XGpioPs *InstancePtr = (XGpioPs *) (Adapter->Instance);

	XGpioPs_WritePin( InstancePtr, Pin, Data );
}


int XGpioPs_Gpio_GetDirectionPin( GpioAdapter *Adapter, int Pin )
{
	XGpioPs *InstancePtr = (XGpioPs *) (Adapter->Instance);

	return XGpioPs_GetDirectionPin( InstancePtr, Pin );
}


void XGpioPs_Gpio_SetDirectionPin( GpioAdapter *Adapter, int Pin, int Direction )
{
	XGpioPs *InstancePtr = (XGpioPs *) (Adapter->Instance);

	XGpioPs_SetDirectionPin( InstancePtr, Pin, Direction );

	if (Direction == GPIO_DIR_OUT) {
		XGpioPs_SetOutputEnablePin(InstancePtr, Pin, 1);
	}
}
