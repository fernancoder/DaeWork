/*
 * Command.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

//#include "Dispatcher.h"
#include "../daework-kernel.h"
#include "../daework-utils.h"

//#include "../utils/MeterAction.h"
//#include "../utils/VoidAction.h"

//Comportamiento común
Action *Dispatcher::defaultAction(string action)
{
	if ( action.compare("meter") == 0 )
		return MeterAction::createHandler();
	return VoidAction::createHandler();
};

