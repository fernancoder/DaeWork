/*
 * Action.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#include "../daework-kernel.h"
#include "../daework-support.h"

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

void Action::sendSuccess(string response)
{
	string message = "{\"status\" : \"success\", \"request\" : {";
	message.append(this->thread->getRequestParams());
	message.append("}, \"response\" : {");
	message.append(response);
	message.append("}}");

	this->send(message.c_str());

	//Cierra la conexión
	this->closeConnection();
}

void Action::sendError(int id, string error)
{
	string message = "{\"status\" : \"error\", \"request\" : {";
	message.append(this->thread->getRequestParams());
	message.append("}, \"response\" : {\"id\" : ");
	message.append(Util::intToString(id));
	message.append(", \"message\" : \"");
	message.append(error);
	message.append("\"}}");

	this->send(message.c_str());

	//Cierra la conexión
	this->closeConnection();
}

void Action::closeConnection()
{
	this->thread->closeConnectionHandler();
}

