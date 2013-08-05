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
	string response = "\"message\" : \"Hola, ";
	response.append(this->getRequestParam("name"));
	response.append("\"");

	this->sendSuccess(response);

	//Cierra la conexión
	this->closeConnection();

}

