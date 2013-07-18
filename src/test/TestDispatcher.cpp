/*
 * FastPrefixDispatcher.cpp
 *
 *  Created on: 14/11/2012
 *      Author: fernando
 */

#include "TestDispatcher.h"
#include "TestAction.h"


Action *TestDispatcher::getHandler(string action)
{

	//Esto será una tabla o una clase o similar

	if ( action.compare("test") == 0 )
		return TestAction::createHandler();

	return defaultAction(action);

}

