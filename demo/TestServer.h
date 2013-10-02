/*
 * FastPrefixServer.h
 *
 *  Created on: 14/11/2012
 *      Author: fernancoder
 */

#ifndef TESTSERVER_H_
#define TESTSERVER_H_

#include "daework-include.h"
#include "daework-kernel.h"

class TestServer  : public Server
{
	public:

		Dispatcher *dispatcherObject;

	public:
		TestServer(const char *cfgFilePath, const char *env, const char *module):Server(cfgFilePath, env, module){};

		void init();
		Thread *createThreadObject();
		Dispatcher *createDispatcherObject();

};
#endif /* TESTSERVER_H_ */
