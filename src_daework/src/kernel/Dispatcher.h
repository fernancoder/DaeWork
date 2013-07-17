/*
 * Dispatcher.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "../include.h"
class Server; //Forward declaration"
class Action; //Forward declaration"
class Dispatcher; //Forward declaration"
#include "Thread.h"
#include "Server.h"
#include "Action.h"

class Dispatcher
{
	public:
		virtual Action *getHandler(string action){return NULL;};
		virtual ~Dispatcher(){};

		//Comportamiento común
		virtual Action *defaultAction(string action);
};

#endif /* DISPATCHER_H_ */
