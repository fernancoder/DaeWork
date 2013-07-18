/*
 * VoidAction.h
 *
 *  Created on: 16/07/2013
 *      Author: fmartin
 */

#ifndef VOIDACTION_H_
#define VOIDACTION_H_

#include "../include.h"
class Server; //Declaración "forward"
#include "../kernel/Thread.h"
#include "../kernel/Server.h"
#include "../kernel/Action.h"

class VoidAction : public Action
{
	public:
		static VoidAction *createHandler(){ return new VoidAction(); };
		void execute()
		{
			string msg = "200\r\n";
			send(msg.c_str());
		};
};

#endif /* VOIDACTION_H_ */
