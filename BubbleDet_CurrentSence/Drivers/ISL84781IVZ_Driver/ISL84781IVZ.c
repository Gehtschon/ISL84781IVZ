/*
 * ISL84781IVZ.c
 *
 *  Created on: Sep 2, 2025
 *      Author: Fabian Glutz
 */


void Update(ISL84781IVZ *dev, ISL84781IVZ_state_t state){

	if (state == dev->status) {
		return;
	}
	dev->status = state;

	// set pins and all stuff


}
