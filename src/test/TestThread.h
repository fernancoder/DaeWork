/*
 * TestThread.h
 *
 *  Created on: 14/11/2012
 *      Author: fernancoder
 */

#ifndef TESTTHREAD_H_
#define TESTTHREAD_H_

//#include "kernel/include.h"
class Server; //Declaración "forward"
#include "kernel/Thread.h"

class TestThread : public Thread
{
	public:
		void init();

};

#endif /* TESTTHREAD_H_ */
