/*
 * MemcachedPool.h
 *
 *  Created on: 30/10/2012
 *      Author: fernancoder
 */

#ifndef MEMCACHEDPOOL_H_
#define MEMCACHEDPOOL_H_

#include "include.h"
#include "Config.h"
#include <libmemcached/util.h>

class MemcachedPool {
	private:
        static bool instanceFlag;
        static MemcachedPool *memcachedPool;
        memcached_pool_st *pool;

        MemcachedPool();

    public:
        static MemcachedPool* getInstance();
        memcached_st *getMemcachedAccess();
        void releaseMemcachedAccess(memcached_st *memc);
        ~MemcachedPool();
};

#endif /* MEMCACHEDPOOL_H_ */


