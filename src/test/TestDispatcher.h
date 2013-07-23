/*
 * TestDispatcher.h
 *
 *  Created on: 14/11/2012
 *      Author: fernancoder
 */

#ifndef TESTDISPATCHER_H_
#define TESTDISPATCHER_H_

//**class Server; //Declaración "forward"
//**#include "kernel/Thread.h"
//**#include "kernel/Dispatcher.h"
#include "daework.h"


class TestDispatcher : public Dispatcher
{
	public:
		Action *getHandler(string action);

};

#endif /* TESTDISPATCHER_H_ */
