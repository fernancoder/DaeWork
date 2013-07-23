/*
 * Action.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

//#include "Action.h"
#include "../daework-kernel.h"

void Action::setThread(Thread *thread)
{
	this->thread = thread;
}

Thread *Action::getThread()
{
	return this->thread;
}

Server *Action::getServer()
{
	return this->thread->getServer();
}

string Action::getRequestParam(string paramName)
{
	return this->thread->getRequestParam(paramName);
}

void Action::send(const char *szBuff)
{
	this->thread->send(szBuff);
}
/*
void Action::sendError(string errorCode, string errorDescription)
{
	string response = "{\"status\":\"error\",\"error\":{\"code\":\"" + errorCode + "\",\"description\":\"" + errorDescription + "\"}}";
	this->thread->send(response.c_str());
}

void Action::sendOk()
{
	string response = "{\"status\":\"success\"}";
	this->thread->send(response.c_str());
}
*/
void Action::closeConnection()
{
	this->thread->closeConnectionHandler();
}

