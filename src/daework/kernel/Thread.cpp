/*
 * Thread.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */


//#include "Thread.h"
#include "../daework-kernel.h"
#include "../daework-utils.h"
#include "../daework-modules.h"

void Thread::setServer(Server *server)
{
	this->server = server;
	this->protocol = server->getServiceProtocol();
	switch (this->protocol)
	{
	    case SERVER_PROTOCOL_TELNET:
	    	this->comm = new CommTelnet(this->server->getSocketTimeOut());
	    break;
	    case SERVER_PROTOCOL_HTTP:
	    	this->comm = new CommHttp(this->server->getSocketTimeOut());
	    break;
	}
}

Server *Thread::getServer()
{
	return this->server;
}

int Thread::addMeasurement(string key)
{
	return this->getServer()->getMeter()->add(key);
}

int Thread::getMeasurement(string key)
{
	return this->getServer()->getMeter()->get(key);
}

void Thread::setConnectionHandler(int connfd)
{
	this->comm->setConnectionHandler(connfd);
}

void Thread::closeConnectionHandler()
{
	this->comm->closeConnectionHandler();
}

void Thread::send(const char *szBuff)
{
	this->comm->writeBodyComm(szBuff);
}

string Thread::getRequestParam(string paramKey)
{
	return this->comm->getRequestParam(paramKey);
}

void Thread::dispatch()
{
	int status = this->comm->AnalizeComm();

	if ( status == COMM_NO_ERROR )
	{
		if ( this->comm->getRequestParam("action").compare("meter") != 0 )
			this->addMeasurement(this->comm->getRequestParam("action"));
		Action *action = getServer()->getDispatcherObject()->getHandler(this->comm->getRequestParam("action"));
		action->setThread(this);
		action->execute();
		delete action;
	}
	else
	{
		string logMsg = "info.action=#executeAction#;info.error=#Invalid syntaxis protocol#";
		LogManager::getInstance()->write(logMsg, LOG_INFO);
	}

	this->closeConnectionHandler();
}

/*
void Thread::preDispatch(string actionName)
{
	cout << actionName << endl;
	//Log::writeLog(string(szBuffComm),LOG_LEVEL_VERBOSE);

	Action *action = getServer()->getDispatcherObject()->getHandler(actionName);
	action->setThread(this);
	action->execute();
	delete action;
}
*/



