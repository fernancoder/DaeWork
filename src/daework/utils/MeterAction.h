/*
 * MeterAction.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef METERACTION_H_
#define METERACTION_H_

#include "../include.h"
class Server; //Forward declaration
#include "../kernel/Thread.h"
#include "../kernel/Server.h"
#include "../kernel/Action.h"

class MeterAction : public Action
{
	public:
		static MeterAction *createHandler(){ return new MeterAction(); };
		void execute();

	private:
		string intToString(int value);
};

#endif /* METERACTION_H_ */
