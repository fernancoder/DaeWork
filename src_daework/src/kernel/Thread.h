/*
 * Thread.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "../include.h"
#include "../utils/Comm.h"
#include "../utils/CommTelnet.h"
#include "../utils/CommHttp.h"
#include "../modules/LogManager.h"
class Thread; //Declaración "forward"
#include "Server.h"

class Thread
{
	public:
		virtual ~Thread(){};

	public:
		void virtual init(){};

	private:
		Server *server;
		int connfd;
		int protocol;
		Comm *comm;

	public:
		void setServer(Server *server);
		Server *getServer();
		void setConnectionHandler(int connfd);
		//int getConnectionHandler();
		void closeConnectionHandler();
		string getRequestParam(string paramKey);

		void send(const char *szBuff);

		void dispatch();
		//void preDispatch(string actionName);

		int addMeasurement(string key);
		int getMeasurement(string key);
};

#endif /* THREAD_H_ */
