/*
 * iic_utils.c
 *
 *  Created on: May 22, 2012
 *      Author: ckohn
 */


#include <stdlib.h>
#include "xil_printf.h"
#include "xiicps_adapter.h"


XIicPs *XIicPs_Initialize( u16 DeviceId, u32 ClkRate )
{
	XIicPs *Instance = malloc(sizeof *Instance);
	XIicPs_Config *Config = XIicPs_LookupConfig(DeviceId);
	XIicPs_CfgInitialize(Instance, Config, Config->BaseAddress);
	XIicPs_SetSClk(Instance, ClkRate);

	return Instance;
}


IicAdapter *XIicPs_RegisterAdapter( void *Instance )
{
	static struct IicAdapterFuncs Funcs = {
		XIicPs_ReadByte,
		XIicPs_ReadBlock,
		XIicPs_ReadMsg,
		XIicPs_WriteByte,
		XIicPs_WriteBlock,
		XIicPs_WriteMsg
	};

	return Iic_RegisterAdapter( Instance, &Funcs );
}


int XIicPs_ReadByte( IicAdapter *Adapter, u16 Address, u8 *Data )
{
	int Status;
    XIicPs *InstancePtr = (XIicPs *) (Adapter->Instance);

	/*
	* Wait until bus is idle to start another transfer.
	*/
	while (XIicPs_BusIsBusy(InstancePtr)) {
		/* NOP */
	}

	/*
	* Receive the data.
	*/
	Status = XIicPs_MasterRecvPolled(InstancePtr, Data, 1, Address);

	iic_debug_printf("[XIicPs_ReadByte]    XIicPs%d : 0x%02X=0x%02X\n\r", InstancePtr->Config.DeviceId, Address, *Data);

	return Status;
}


int XIicPs_ReadBlock( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount )
{
	int Status;
	int i;
	XIicPs *InstancePtr = (XIicPs *) (Adapter->Instance);

	/*
	 * Wait until bus is idle to start another transfer.
	 */
	while (XIicPs_BusIsBusy(InstancePtr)) {
		/* NOP */
	}

	/*
	 * Set the IIC Repeated Start option.
	 */
	Status = XIicPs_SetOptions(InstancePtr, XIICPS_REP_START_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Send the buffer using the IIC and check for errors.
	 */
	Status = XIicPs_MasterSendPolled(InstancePtr, &Register, 1, Address);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Receive the data.
	 */
	Status = XIicPs_MasterRecvPolled(InstancePtr, Data, ByteCount, Address);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Clear the IIC Repeated Start option.
	 */
	Status = XIicPs_ClearOptions(InstancePtr, XIICPS_REP_START_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	iic_debug_printf("[XIicPs_ReadBlock]   XIicPs%d : 0x%02X->0x%02X={ ", InstancePtr->Config.DeviceId, Address, Register);
	for (i=0; i < ByteCount; i++) {
		iic_debug_printf("0x%02X ", Data[i]);
	}
	iic_debug_printf("}\n\r");

	return XST_SUCCESS;
}


static int XIicPs_ReadMsgOne( IicAdapter *Adapter, u16 Address, IicMsg *Msg )
{
	int Status;
	XIicPs *InstancePtr = (XIicPs *) (Adapter->Instance);

	/*
	 * Wait until bus is idle to start another transfer.
	 */
	while (XIicPs_BusIsBusy(InstancePtr)) {
		/* NOP */
	}

	/*
	 * Set the IIC Repeated Start option.
	 */
	Status = XIicPs_SetOptions(InstancePtr, XIICPS_REP_START_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Send the buffer using the IIC and check for errors.
	 */
	Status = XIicPs_MasterSendPolled(InstancePtr, (u8 *) &Msg->Register, 1, Address);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Receive the data.
	 */
	Status = XIicPs_MasterRecvPolled(InstancePtr, (u8 *) &Msg->Data, 1, Address);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Clear the IIC Repeated Start option.
	 */
	Status = XIicPs_ClearOptions(InstancePtr, XIICPS_REP_START_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	iic_debug_printf("[XIicPs_ReadMsg]     XIicPs%d : 0x%02X->0x%02X=0x%02X\n\r", InstancePtr->Config.DeviceId, Address, Msg->Register, Msg->Data);

	return XST_SUCCESS;
}


int XIicPs_ReadMsg( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength )
{
	int Status;
	int i;

	for ( i = 0; i < MsgLength; i++ ) {
		Status = XIicPs_ReadMsgOne(Adapter, Address, (IicMsg *) &Msg[i]);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
	}

	return XST_SUCCESS;
}


int XIicPs_WriteByte( IicAdapter *Adapter, u16 Address, u8 Data )
{
	int Status;
	XIicPs *InstancePtr = (XIicPs *) (Adapter->Instance);

	iic_debug_printf("[XIicPs_WriteByte]   XIicPs%d : 0x%02X=0x%02X\n\r", InstancePtr->Config.DeviceId, Address, Data);

	/*
	 * Wait until bus is idle to start another transfer.
	 */
	while (XIicPs_BusIsBusy(InstancePtr)) {
		/* NOP */
	}

	/*
	 * Send the buffer using the IIC and check for errors.
	 */
	Status = XIicPs_MasterSendPolled(InstancePtr, &Data, 1, Address);

	return Status;
}


int  XIicPs_WriteBlock( IicAdapter *Adapter, u16 Address, u8 Register, u8 *Data, int ByteCount )
{
	u8 *WriteBuffer = (u8 *) malloc((ByteCount+1) * sizeof(u8));
	int Status;
	int i;
	XIicPs *InstancePtr = (XIicPs *) (Adapter->Instance);

	iic_debug_printf("[XIicPs_WriteBlock]  XIicPs%d : 0x%02X->0x%02X={ ", InstancePtr->Config.DeviceId, Address, Register);
	for (i=0; i < ByteCount; i++) {
		iic_debug_printf("0x%02X ", Data[i]);
	}
	iic_debug_printf("}\n\r");

	/*
	 * A temporary write buffer must be used which contains both the register
	 * and the data to be written, put the register in first
	 */
	WriteBuffer[0] = Register;
	for (i = 0; i < ByteCount; i++) {
		WriteBuffer[i+1] = Data[i];
	}

	/*
	 * Wait until bus is idle to start another transfer.
	 */
	while (XIicPs_BusIsBusy(InstancePtr)) {
		/* NOP */
	}

	/*
	 * Send the buffer using the IIC and check for errors.
	 */
	Status = XIicPs_MasterSendPolled(InstancePtr, WriteBuffer, ByteCount+1, Address);
	free(WriteBuffer);

	return Status;
}


static int XIicPs_WriteMsgOne( IicAdapter *Adapter, u16 Address, IicMsg *Msg )
{
	u8 WriteBuffer[2];
	int Status;
	XIicPs *InstancePtr = (XIicPs *) (Adapter->Instance);

	iic_debug_printf("[XIicPs_WriteMsg]    XIicPs%d : 0x%02X->0x%02X=0x%02X\n\r", InstancePtr->Config.DeviceId, Address, Msg->Register, Msg->Data);

	/*
	 * A temporary write buffer must be used which contains both the register
	 * and the data to be written, put the register in first
	 */
	WriteBuffer[0] = Msg->Register;
	WriteBuffer[1] = Msg->Data;

	/*
	 * Wait until bus is idle to start another transfer.
	 */
	while (XIicPs_BusIsBusy(InstancePtr)) {
		/* NOP */
	}

	/*
	 * Send the buffer using the IIC and check for errors.
	 */
	Status = XIicPs_MasterSendPolled(InstancePtr, WriteBuffer, 2, Address);

	return Status;
}


int XIicPs_WriteMsg( IicAdapter *Adapter, u16 Address, IicMsg Msg[], u8 MsgLength )
{
	int Status;
	int i;

	for ( i = 0; i < MsgLength; i++ ) {
		Status = XIicPs_WriteMsgOne(Adapter, Address, (IicMsg *) &Msg[i]);
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
	}

	return XST_SUCCESS;
}
