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

}

Thread *TestServer::createThreadObject()
{
	return (Thread *)(new TestThread());
}

Dispatcher *TestServer::createDispatcherObject()
{
	return (Dispatcher *)(new TestDispatcher());
}

