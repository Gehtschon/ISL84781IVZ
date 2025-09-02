/*
 * ISL84781IVZ.c
 *
 *  Created on: Sep 2, 2025
 *      Author: Fabian Glutz
 */

#include "ISL84781IVZ.h"



void Update(ISL84781IVZ *dev, ISL84781IVZ_state_t state){

	if (state == dev->status) {
		return;
	}
	dev->status = state;

	//Determine pins with bit shift

	dev->ADD0.ADD_Status = (state >> 0) & 1u;
	dev->ADD1.ADD_Status = (state >> 1) & 1u;
	dev->ADD2.ADD_Status = (state >> 2) & 1u;
	dev->INH.ADD_Status  = (state >> 3) & 1u;


	SetPorts(dev);



}


static void SetPorts(ISL84781IVZ *dev){

	HAL_GPIO_WritePin(dev->ADD0.ADD_Port, dev->ADD0.ADD_Pin, dev->ADD0.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD1.ADD_Port, dev->ADD1.ADD_Pin, dev->ADD1.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD2.ADD_Port, dev->ADD2.ADD_Pin, dev->ADD2.ADD_Status);
}
