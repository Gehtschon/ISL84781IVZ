/*
 * ISL84781IVZ.c
 *
 *  Created on: Sep 2, 2025
 *      Author: Fabian Glutz
 */

#include "ISL84781IVZ.h"



void ISL84781IVZ_init(ISL84781IVZ *dev, GPIO_TypeDef *ADD0_Port,
		uint16_t ADD0_Pin, GPIO_TypeDef *ADD1_Port, uint16_t ADD1_Pin,
		GPIO_TypeDef *ADD2_Port, uint16_t ADD2_Pin, GPIO_TypeDef *INH_Port,uint16_t INH_Pin,ISL84781IVZ_state_t state ){



	dev->ADD0.ADD_Pin = ADD0_Pin;
	dev->ADD0.ADD_Port = ADD0_Port;

	dev->ADD1.ADD_Pin = ADD1_Pin;
	dev->ADD1.ADD_Port = ADD1_Port;

	dev->ADD2.ADD_Pin = ADD2_Pin;
	dev->ADD2.ADD_Port = ADD2_Port;

	dev->INH.ADD_Pin = INH_Pin;
	dev->INH.ADD_Port = INH_Port;

	ISL84781IVZ_Update(dev, state);



}

void ISL84781IVZ_Update(ISL84781IVZ *dev, ISL84781IVZ_state_t state){


	dev->status = state;

	//Determine pins with bit shift

	dev->ADD0.ADD_Status = (state >> 0) & 1u;
	dev->ADD1.ADD_Status = (state >> 1) & 1u;
	dev->ADD2.ADD_Status = (state >> 2) & 1u;
	dev->INH.ADD_Status  = (state >> 3) & 1u;


	ISL84781IVZ_SetPorts(dev);



}


static void ISL84781IVZ_SetPorts(ISL84781IVZ *dev){

	HAL_GPIO_WritePin(dev->INH.ADD_Port, dev->INH.ADD_Pin, dev->INH.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD0.ADD_Port, dev->ADD0.ADD_Pin, dev->ADD0.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD1.ADD_Port, dev->ADD1.ADD_Pin, dev->ADD1.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD2.ADD_Port, dev->ADD2.ADD_Pin, dev->ADD2.ADD_Status);

}
