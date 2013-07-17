/*
 * TestServer.cpp
 *
 *  Created on: 14/11/2012
 *      Author: fernando
 */

#include "TestServer.h"
#include "TestDispatcher.h"
#include "TestThread.h"

void TestServer::init()
{
	this->dispatcherObject = (Dispatcher *)(new TestDispatcher());
}

Thread *TestServer::getThreadObject()
{
	return (Thread *)(new TestThread());
}

Dispatcher *TestServer::getDispatcherObject()
{
	return this->dispatcherObject;
}

