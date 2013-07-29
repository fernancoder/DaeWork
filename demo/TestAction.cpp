/*
 * TestAction.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#include "TestAction.h"

TestAction *TestAction::createHandler()
{
	return new TestAction();
}

void TestAction::execute()
{
	string message = "{\"message\" : \"HOLA, ";
	message.append(this->getRequestParam("name"));
	message.append("\"}");

	this->send(message.c_str());

	//Cierra la conexión
	this->closeConnection();
}

