/*
 * iic_utils.h
 *
 *  Created on: May 22, 2012
 *      Author: ckohn
 */

#ifndef XIICPS_ADAPTER_H_
#define XIICPS_ADAPTER_H_


#include "xiic_adapter.h"
#include "xiicps.h"


// IIC Init Function
XIicPs *XIicPs_Initialize( u16 DeviceId, u32 ClkRate );

// IIC Register Function
IicAdapter* XIicPs_RegisterAdapter( void *Instance );

// IIC Read Functions
int XIicPs_ReadByte( IicAdapter *Adapter, u16 Address, u8 *Data );
int XIicPs_ReadBlock( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount );
int XIicPs_ReadMsg( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength );

// IIC Write Functions
int XIicPs_WriteByte( IicAdapter *Adapter, u16 Address, u8 Data );
int XIicPs_WriteBlock( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount );
int XIicPs_WriteMsg( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength );


#endif /* XIICPS_ADAPTER_H_ */
