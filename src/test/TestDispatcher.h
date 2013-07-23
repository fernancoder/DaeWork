/*
 * TestDispatcher.h
 *
 *  Created on: 14/11/2012
 *      Author: fernancoder
 */

#ifndef TESTDISPATCHER_H_
#define TESTDISPATCHER_H_

#include "daework-kernel.h"


class TestDispatcher : public Dispatcher
{
	public:
		Action *getHandler(string action);

};

#endif /* TESTDISPATCHER_H_ */
