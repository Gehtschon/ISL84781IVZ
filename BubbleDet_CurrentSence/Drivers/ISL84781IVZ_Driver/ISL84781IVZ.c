/*
 * ISL84781IVZ.c
 *
 *  Created on: Sep 2, 2025
 *      Author: Fabian Glutz
 */

#include "ISL84781IVZ.h"

void ISL84781IVZ_init(ISL84781IVZ *dev, GPIO_TypeDef *ADD0_Port,
		uint16_t ADD0_Pin, GPIO_TypeDef *ADD1_Port, uint16_t ADD1_Pin,
		GPIO_TypeDef *ADD2_Port, uint16_t ADD2_Pin, GPIO_TypeDef *INH_Port,
		uint16_t INH_Pin, ISL84781IVZ_state_t state) {

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

void ISL84781IVZ_Update(ISL84781IVZ *dev, ISL84781IVZ_state_t state) {

	dev->status = state;

	//Determine pins with bit shift

	dev->ADD0.ADD_Status = (state >> 0) & 1u;
	dev->ADD1.ADD_Status = (state >> 1) & 1u;
	dev->ADD2.ADD_Status = (state >> 2) & 1u;
	dev->INH.ADD_Status = (state >> 3) & 1u;

	ISL84781IVZ_SetPorts(dev);

}

ISL84781IVZ_state_t ISL84781IVZ_GoNext(ISL84781IVZ *dev) {

	ISL84781IVZ_state_t nextState = dev->status + 1;
	if (nextState > NO7) {
		nextState = NO0;
	}
	ISL84781IVZ_Update(dev, nextState);
	return nextState;

}

ISL84781IVZ_state_t ISL84781IVZ_GoPrevious(ISL84781IVZ *dev) {

	ISL84781IVZ_state_t previousState = dev->status - 1;
	if (previousState < NO0) {
		previousState = NO7;
	}
	ISL84781IVZ_Update(dev, previousState);
	return previousState;
}

void ISL84781IVZ_GoNext_Multiple(ISL84781IVZ *devs[], uint8_t numDevs) {
// This function can be used to go one step futher with every function call
	// Variables to store the current device
	static uint8_t currentDevIndex = 0;
	static bool firstCall = true;
	if (numDevs == 0)
		return; // No devices to process

	if (firstCall) {
		firstCall = false;
		for (uint8_t i = 0; i < numDevs; i++) {
			ISL84781IVZ_Update(devs[i], NONE);
		}
		return;
	}

	if (devs[currentDevIndex]->status == NO7) {
		devs[currentDevIndex]->status = NONE;
		currentDevIndex = (currentDevIndex + 1) % numDevs;
		ISL84781IVZ_Update(devs[currentDevIndex], NO0);
	} else {
		ISL84781IVZ_GoNext(devs[currentDevIndex]);

	}
}

void ISL84781IVZ_InOutNext(ISL84781IVZ *InDevs[], uint8_t InNumDevs,
		ISL84781IVZ *OutDevs[], uint8_t OutNumDevs) {
	static uint8_t currentInDevIndex = 0;
	static uint8_t currentOutDevIndex = 0;
	static bool firstCall = true;
	static bool roundComplete = false;
	ISL84781IVZ_state_t forbiddenInState = NONE;

	if (InNumDevs == 0 || OutNumDevs == 0)
		return; // No devices to process

	if (firstCall) {
		firstCall = false;
		for (uint8_t i = 0; i < InNumDevs; i++) {
			ISL84781IVZ_Update(InDevs[i], NONE);
		}
		for (uint8_t i = 0; i < OutNumDevs; i++) {
			ISL84781IVZ_Update(OutDevs[i], NONE);
		}
		OutDevs[currentOutDevIndex] = NO0; // Start with the first output
	}

	if (roundComplete == true) {
		roundComplete = false;
		if (OutDevs[currentOutDevIndex]->status == NO7) {
			OutDevs[currentOutDevIndex]->status = NONE;
			currentOutDevIndex = (currentOutDevIndex + 1) % OutNumDevs;
			ISL84781IVZ_Update(OutDevs[currentOutDevIndex], NO0);
			forbiddenInState = NO0;
		} else {
			forbiddenInState = ISL84781IVZ_GoNext(OutDevs[currentOutDevIndex]);
		}

	}

	if (currentInDevIndex == currentOutDevIndex) {
		if (InDevs[currentInDevIndex]->status + 1 == forbiddenInState) {
			// Set state to forbidden state but don't write it to Hardware
			InDevs[currentInDevIndex]->status = forbiddenInState;
		}
	}

	if (InDevs[currentInDevIndex]->status == NO7) {
		InDevs[currentInDevIndex]->status = NONE;
		currentInDevIndex = (currentInDevIndex + 1) % InNumDevs;
		ISL84781IVZ_Update(InDevs[currentInDevIndex], NO0);
		if (currentInDevIndex == 0) {
			roundComplete = true;
		}
	} else {
		ISL84781IVZ_GoNext(InDevs[currentInDevIndex]);
	}

}

static void ISL84781IVZ_SetPorts(ISL84781IVZ *dev) {

	HAL_GPIO_WritePin(dev->INH.ADD_Port, dev->INH.ADD_Pin, dev->INH.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD0.ADD_Port, dev->ADD0.ADD_Pin,
			dev->ADD0.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD1.ADD_Port, dev->ADD1.ADD_Pin,
			dev->ADD1.ADD_Status);
	HAL_GPIO_WritePin(dev->ADD2.ADD_Port, dev->ADD2.ADD_Pin,
			dev->ADD2.ADD_Status);

}
