/*
 * DwmMemcached.h
 *
 *  Created on: 06/08/2013
 *      Author: fernancoder
 */

#ifndef DWMMEMCACHED_H_
#define DWMMEMCACHED_H_

#include <daework-include.h>
#include <daework-support.h>

#include <libmemcached/util.h>

class DwmMemcached {
	private:
        static bool instanceFlag;
        static DwmMemcached *dwmMemcached;
        memcached_pool_st *pool;

        DwmMemcached();

    public:
        static DwmMemcached* getInstance();
        memcached_st *getMemcachedAccess();
        void releaseMemcachedAccess(memcached_st *memc);
        ~DwmMemcached();
};

#endif /* DWMMEMCACHED_H_ */


