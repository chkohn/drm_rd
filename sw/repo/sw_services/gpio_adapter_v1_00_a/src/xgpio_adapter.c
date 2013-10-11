/*
 * xgpio_adpater.c
 *
 *  Created on: Jul 12, 2012
 *      Author: ckohn
 */

#include <stdlib.h>
#include <string.h>
#include "xgpio_adapter.h"
#include "xil_assert.h"


GpioAdapter *Gpio_RegisterAdapter( void *Instance, struct GpioAdapterFuncs *Funcs )
{
	GpioAdapter *Adapter = malloc(sizeof *Adapter);

	Adapter->Instance = Instance;
	Adapter->Funcs = Funcs;

	return Adapter;
}


void Gpio_Connect( GpioPin *Pin, GpioAdapter *Adapter, int Id, int Dir )
{
	Pin->Adapter = Adapter;
	Pin->Id = Id;
	Pin->Dir = Dir;
}


int Gpio_Get(GpioPin *Pin)
{
	Xil_AssertNonvoid(Pin->Adapter != NULL);
	Xil_AssertNonvoid(Pin->Dir == GPIO_DIR_IN);

	Pin->Adapter->Funcs->Gpio_SetDirectionPin(Pin->Adapter, Pin->Id, Pin->Dir);
	return Pin->Adapter->Funcs->Gpio_ReadPin(Pin->Adapter, Pin->Id);
}


void Gpio_Set(GpioPin *Pin)
{
	Xil_AssertVoid(Pin->Adapter != NULL);
	Xil_AssertVoid(Pin->Dir == GPIO_DIR_OUT);

	Pin->Adapter->Funcs->Gpio_SetDirectionPin(Pin->Adapter, Pin->Id, Pin->Dir);
	Pin->Adapter->Funcs->Gpio_WritePin(Pin->Adapter, Pin->Id, 1);
}


void Gpio_Reset(GpioPin *Pin)
{
	Xil_AssertVoid(Pin->Adapter != NULL);
	Xil_AssertVoid(Pin->Dir == GPIO_DIR_OUT);

	Pin->Adapter->Funcs->Gpio_SetDirectionPin(Pin->Adapter, Pin->Id, Pin->Dir);
	Pin->Adapter->Funcs->Gpio_WritePin(Pin->Adapter, Pin->Id, 0);
}
