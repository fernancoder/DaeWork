/*
 * meter.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fmartin
 */

#include "../daework-support.h"

Meter::Meter() {
	pthread_mutex_init(&dbMeterLock,NULL);

}

Meter::~Meter() {
	pthread_mutex_destroy(&dbMeterLock);
}

int Meter::add(string key)
{return 1;
	pthread_mutex_lock(&dbMeterLock);

	int ret;
	if ( report.find(key) == report.end() )
	{
		ret = report[key] = 1;
	}
	else
	{
		ret = ++(report[key]);
	}

	pthread_mutex_unlock(&dbMeterLock);

	return ret;
}

int Meter::get(string key)
{
	pthread_mutex_lock(&dbMeterLock);

	int ret = 0;
	if ( report.find(key) != report.end() )
	{
		ret = report[key];
		report[key] = 0;
	}

	pthread_mutex_unlock(&dbMeterLock);

	return ret;
}




