/*
 * Action.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "../include.h"
class Server; //Declaración "forward"
#include "Thread.h"
#include "Server.h"

class Action
{
	public:
		Thread *thread;

	public:
		virtual void execute() {};
		virtual ~Action(){};

	public:
		void setThread(Thread *thread);
		Thread *getThread();
		Server *getServer();
		string getRequestParam(string paramName);
		void send(const char *szBuff);
//		void sendError(string errorCode, string errorDescription);
//		void sendOk();
		void closeConnection();
};


#endif /* ACTION_H_ */
