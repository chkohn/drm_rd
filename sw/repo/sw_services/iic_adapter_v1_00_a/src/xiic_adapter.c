/*
 * xiic_adapter.c
 *
 *  Created on: Jul 2, 2012
 *      Author: ckohn
 */

#include <stdlib.h>
#include <string.h>
#include "xiic_adapter.h"


IicAdapter *Iic_RegisterAdapter( void *Instance, struct IicAdapterFuncs *Funcs )
{
	IicAdapter *Adapter = malloc(sizeof *Adapter);

	Adapter->Instance = Instance;
	Adapter->Funcs = Funcs;

	return Adapter;
}
