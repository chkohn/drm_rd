/*
 * xgpio_adapter.h
 *
 *  Created on: Jul 12, 2012
 *      Author: ckohn
 */

#ifndef XGPIO_ADAPTER_H_
#define XGPIO_ADAPTER_H_


#include "xil_types.h"


#define SLEEP_10MS    10000
#define SLEEP_100MS   100000

#define GPIO_DIR_IN   0
#define GPIO_DIR_OUT  1


// Turn on/off Debug messages
#ifdef GPIO_DEBUG
#define  gpio_debug_printf  xil_printf
#else
#define  gpio_debug_printf(msg, args...) do {  } while (0)
#endif


// Implementation independent GPIO adapter structure
typedef struct {
	void *Instance;
	struct GpioAdapterFuncs *Funcs;
} GpioAdapter;


typedef struct {
	GpioAdapter *Adapter;
	int Id;
	int Dir;
} GpioPin;


// Implementation specific GPIO adapter functions
struct GpioAdapterFuncs {
	int  (*Gpio_ReadPin)         ( GpioAdapter *Adapter, int Pin );
	void (*Gpio_WritePin)        ( GpioAdapter *Adapter, int Pin, int Data );
	int  (*Gpio_GetDirectionPin) ( GpioAdapter *Adapter, int Pin );
	void (*Gpio_SetDirectionPin) ( GpioAdapter *Adapter, int Pin, int Direction );
};


GpioAdapter *Gpio_RegisterAdapter( void *Instance, struct GpioAdapterFuncs *Funcs );
void Gpio_Connect( GpioPin *Pin, GpioAdapter *Adapter, int Id, int Dir );

int  Gpio_Get(GpioPin *Gpio);
void Gpio_Set(GpioPin *Gpio);
void Gpio_Reset(GpioPin *Gpio);


#endif /* XGPIO_ADAPTER_H_ */
