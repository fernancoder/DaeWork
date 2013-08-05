/*
 * MeterAction.cpp
 *
 *  Created on: 29/10/2012
 *      Author: fernancoder
 */

#include "../daework-support.h"

void MeterAction::execute()
{
	string action = getRequestParam("action");
	string response;

	if ( !action.compare("status") == 0 )
	{
	    int totalActions = this->getThread()->getMeasurement(getRequestParam("name"));
	    response = "\"total\" : \"";
	    response.append(Util::intToString(totalActions));
	    response.append("\"");
	}
	this->sendSuccess(response);

	//Cierra la conexión
	this->closeConnection();
}


