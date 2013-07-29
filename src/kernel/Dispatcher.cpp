/*
 * Command.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#include "../daework-kernel.h"
#include "../daework-support.h"

//Comportamiento común
Action *Dispatcher::defaultAction(string action)
{
	if ( action.compare("meter") == 0 )
		return MeterAction::createHandler();
	return VoidAction::createHandler();
};

