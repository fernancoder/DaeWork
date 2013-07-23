/*
 * FastPrefixServer.h
 *
 *  Created on: 14/11/2012
 *      Author: fernancoder
 */

#ifndef TESTSERVER_H_
#define TESTSERVER_H_

#include "include.h"
#include "daework.h"

//**#include "kernel/Server.h"
//#include "FastPrefixThread.h"
//#include "FastPrefixDispatcher.h"

class TestServer  : public Server
{
	public:

		Dispatcher *dispatcherObject;

	public:
		TestServer(const char *cfgFilePath, const char *env, const char *module):Server(cfgFilePath, env, module){};

		void init();
		Thread *getThreadObject();
		Dispatcher *getDispatcherObject();

};
#endif /* TESTSERVER_H_ */
