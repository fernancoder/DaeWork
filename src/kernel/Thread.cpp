/*
 * Thread.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#include "../daework-kernel.h"
#include "../daework-support.h"

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

string Thread::getRequestParams()
{
	return this->comm->getRequestParams();
}

string Thread::getLogParams()
{
	return this->comm->getLogParams();
}

bool Thread::dispatch()
{
	int status = this->comm->analizeComm();
	if ( status == COMM_NO_ERROR )
	{
		if ( this->comm->getRequestParam("action").compare("s-t-o-p-s-e-r-v-e-r") == 0 )
			return false; //Exit thread (for a gracefull shutdown)

		if ( this->comm->getRequestParam("action").compare("meter") != 0 && this->comm->getRequestParam("action").compare("status") != 0 )
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
	return true; //Next petition
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



