/*
 * ISL84781IVZ.h
 *
 *  Created on: Sep 2, 2025
 *      Author: Fabian Glutz
 */

#ifndef ISL84781IVZ_DRIVER_ISL84781IVZ_H_
#define ISL84781IVZ_DRIVER_ISL84781IVZ_H_

#include "stdbool.h"

// State from Datasheet Table
typedef enum {
	NO0 = 0, NO1, NO2, NO3, NO4, NO5, NO6, NO7, NONE
} ISL84781IVZ_state_t;

typedef struct {
	GPIO_TypeDef *ADD_Port;
	uint16_t ADD_Pin;
	bool ADD0_Status;
} Pin;

typedef struct {
	Pin ADD0;
	Pin ADD1;
	Pin ADD2;
	// INH controls all Switches OFF if pulled to V+
	Pin INH;
	// Current state of the Output
	ISL84781IVZ_state_t status;

} ISL84781IVZ;



// Encodes [INH:ADD2:ADD1:ADD0] in bits 3..0
static const uint8_t ISL_SELECT_TO_INPUTS[9] = {
/* NO0  */0b0000,
/* NO1  */0b0001,
/* NO2  */0b0010,
/* NO3  */0b0011,
/* NO4  */0b0100,
/* NO5  */0b0101,
/* NO6  */0b0110,
/* NO7  */0b0111,
/* NONE */0b1000  // INH=1, ADDx don't care
		};

void Update(ISL84781IVZ *dev, ISL84781IVZ_state_t state);

#endif /* ISL84781IVZ_DRIVER_ISL84781IVZ_H_ */
