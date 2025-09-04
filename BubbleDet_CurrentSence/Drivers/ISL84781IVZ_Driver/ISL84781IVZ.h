/*
 * ISL84781IVZ.h
 *
 *  Created on: Sep 2, 2025
 *      Author: Fabian Glutz
 */

#ifndef ISL84781IVZ_DRIVER_ISL84781IVZ_H_
#define ISL84781IVZ_DRIVER_ISL84781IVZ_H_

#include "stdbool.h"
#include "stm32l4xx_hal.h"

// State from Datasheet Table

/*
 * N00 0000
 * N01 0001
 * N02 0010
 * N03 0011
 * N04 0100
 * N05 0101
 * N06 0110
 * N07 0111
 * N08 1000
 */
typedef enum {
	NO0 = 0, NO1, NO2, NO3, NO4, NO5, NO6, NO7, NONE
} ISL84781IVZ_state_t;

typedef struct {
	GPIO_TypeDef *ADD_Port;
	uint16_t ADD_Pin;
	bool ADD_Status;
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

void ISL84781IVZ_init(ISL84781IVZ *dev, GPIO_TypeDef *ADD0_Port,
		uint16_t ADD0_Pin, GPIO_TypeDef *ADD1_Port, uint16_t ADD1_Pin,
		GPIO_TypeDef *ADD2_Port, uint16_t ADD2_Pin, GPIO_TypeDef *INH_Port,uint16_t INH_Pin,ISL84781IVZ_state_t state );

void ISL84781IVZ_Update(ISL84781IVZ *dev, ISL84781IVZ_state_t state);

static void ISL84781IVZ_SetPorts(ISL84781IVZ *dev);

#endif /* ISL84781IVZ_DRIVER_ISL84781IVZ_H_ */
