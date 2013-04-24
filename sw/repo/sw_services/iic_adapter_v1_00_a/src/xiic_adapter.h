/*
 * xiic_adapter.h
 *
 *  Created on: Jun 29, 2012
 *      Author: ckohn
 */

#ifndef XIIC_ADAPTER_H_
#define XIIC_ADAPTER_H_


#include "xil_types.h"


// Turn on/off Debug messages
#ifdef IIC_DEBUG
#define  iic_debug_printf  xil_printf
#else
#define  iic_debug_printf(msg, args...) do {  } while (0)
#endif


// Commonly used I2C message structure
typedef struct {
	u8 Register;
	u8 Data;
} IicMsg;


// Implementation independent I2C adapter structure
typedef struct {
	void *Instance;
	struct IicAdapterFuncs *Funcs;
} IicAdapter;


// Implementation specific I2C adapter functions
struct IicAdapterFuncs {
	int (*Iic_ReadByte)      ( IicAdapter *Adapter, u16 Address, u8 *Data );
	int (*Iic_ReadBlock)     ( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount );
	int (*Iic_ReadMsg)       ( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength );
	int (*Iic_WriteByte)     ( IicAdapter *Adapter, u16 Address, u8 Data );
	int (*Iic_WriteBlock)    ( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount );
	int (*Iic_WriteMsg)      ( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength );
};


IicAdapter *Iic_RegisterAdapter( void *Instance, struct IicAdapterFuncs *Funcs );


#endif /* XIIC_ADAPTER_H_ */
