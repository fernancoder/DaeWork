/*
 * DwmMemcached.cpp
 *
 *  Created on: 06/08/2013
 *      Author: fernancoder
 */

#include "DwmMemcached.h"

bool DwmMemcached::instanceFlag=0;
DwmMemcached *DwmMemcached::dwmMemcached=0;

DwmMemcached::DwmMemcached()
{
	const char *config_string = IniParser::getInstance()->getStringWithDefault("module", "memcached", "server", "--SERVER=localhost --POOL-MIN=5 --POOL-MAX=20").c_str();

	//cout << "CONF: " << config_string << endl;

	this->pool= memcached_pool(config_string, strlen(config_string));
}

DwmMemcached* DwmMemcached::getInstance()
{
    if(!instanceFlag)
    {
    	dwmMemcached = new DwmMemcached();
    	instanceFlag = true;
    	return dwmMemcached;
    }
    else
    {
    	return dwmMemcached;
    }
}

DwmMemcached::~DwmMemcached()
{
	memcached_pool_destroy(this->pool);
}

memcached_st *DwmMemcached::getMemcachedAccess()
{
	memcached_return_t rc;
	memcached_st *Mch = memcached_pool_pop(this->pool, false, &rc);

	//if ( rc != MEMCACHED_SUCCESS )
	//	cout << "Error: " << rc << " - " << memcached_strerror(Mch, rc) << endl << endl;

	return Mch;
}

void DwmMemcached::releaseMemcachedAccess(memcached_st *memc)
{
	memcached_pool_push(this->pool, memc);
}





