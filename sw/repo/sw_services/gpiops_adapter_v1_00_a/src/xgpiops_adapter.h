/*
 * xgpiops_adapter.h
 *
 *  Created on: Jul 12, 2012
 *      Author: ckohn
 */

#ifndef XGPIOPS_ADAPTER_H_
#define XGPIOPS_ADAPTER_H_


#include "xgpio_adapter.h"
#include "xgpiops.h"


// GPIO Init Function
XGpioPs *XGpioPs_Initialize( u16 DeviceId );

// GPIO Register Function
GpioAdapter *XGpioPs_RegisterAdapter( void *Instance );

// GPIO Read Functions
int XGpioPs_Gpio_ReadPin( GpioAdapter *Adapter, int Pin );
int XGpioPs_Gpio_GetDirectionPin( GpioAdapter *Adapter, int Pin );

// GPIO Write Functions
void XGpioPs_Gpio_WritePin( GpioAdapter *Adapter, int Pin, int Data );
void XGpioPs_Gpio_SetDirectionPin( GpioAdapter *Adapter, int Pin, int Direction );


#endif /* XGPIOPS_ADAPTER_H_ */
