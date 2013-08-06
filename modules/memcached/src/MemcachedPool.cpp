/*
 * MemcachedPool.cpp
 *
 *  Created on: 30/10/2012
 *      Author: fernancoder
 */

#include "MemcachedPool.h"

bool MemcachedPool::instanceFlag=0;
MemcachedPool *MemcachedPool::memcachedPool=0;

MemcachedPool::MemcachedPool()
{
	const char *config_string= Config::getInstance()->getParam("memcached_servers").c_str();
	this->pool= memcached_pool(config_string, strlen(config_string));
}

MemcachedPool* MemcachedPool::getInstance()
{
    if(!instanceFlag)
    {
    	memcachedPool = new MemcachedPool();
    	instanceFlag = true;
    	return memcachedPool;
    }
    else
    {
    	return memcachedPool;
    }
}

MemcachedPool::~MemcachedPool()
{
	memcached_pool_destroy(this->pool);
}

memcached_st *MemcachedPool::getMemcachedAccess()
{
	memcached_return_t rc;
	return memcached_pool_pop(this->pool, false, &rc);
}

void MemcachedPool::releaseMemcachedAccess(memcached_st *memc)
{
	memcached_pool_push(this->pool, memc);
}





