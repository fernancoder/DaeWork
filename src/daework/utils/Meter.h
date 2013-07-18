/*
 * meter.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef METER_H_
#define METER_H_

#include "../include.h"

class Meter {
public:
	Meter();
	virtual ~Meter();

	int add(string key);
	int get(string key);

private:
	 pthread_mutex_t dbMeterLock;
	 map<string, long> report;
};

#endif /* METER_H_ */
