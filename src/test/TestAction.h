/*
 * TestAction.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef TESTADACTION_H_
#define TESTADACTION_H_

#include "include.h"
//**class Server; //Declaración "forward"
//**#include "kernel/Thread.h"
//**#include "kernel/Server.h"
//**#include "kernel/Action.h"
//**#include "utils/Util.h"
#include "daework.h"
#include "TestServer.h"

class TestAction : public Action
{

	public:
		static TestAction *createHandler();
		void execute();

};

#endif /* TESTADACTION_H_ */
