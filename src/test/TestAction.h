/*
 * TestAction.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef TESTADACTION_H_
#define TESTADACTION_H_

#include "daework-include.h"
#include "daework-kernel.h"
#include "TestServer.h"

class TestAction : public Action
{

	public:
		static TestAction *createHandler();
		void execute();

};

#endif /* TESTADACTION_H_ */
