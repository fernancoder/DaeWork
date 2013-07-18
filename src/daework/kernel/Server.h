/*
 * Server.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "../include.h"
class Server; //Declaración "forward"
#include "../utils/Meter.h"
#include "Thread.h"
#include "Dispatcher.h"

const int SERVER_PROTOCOL_TELNET = 1;
const int SERVER_PROTOCOL_HTTP   = 2;

typedef struct {
	Server *server;
	string actionName;
} PreThreadInfo;

class Server
{
    public:
    	Server(const char *iniFilePath, const char *env, const char *module);
		virtual ~Server(){};
    	void start();

    	Meter *getMeter(){return meter;};

    	/*void preStartThread(string actionName){this->preThreadMake(actionName);};*/

    	//Virtuales
    	virtual void init(){};
    	virtual Thread *getThreadObject(){return NULL;};
    	virtual Dispatcher *getDispatcherObject(){return NULL;};
    	int getServiceProtocol(){return protocol;};
    	int getSocketTimeOut(){return timeOut;};

    private:
    	int port;	       //Service port (configuration)
    	int backlog_size;  //Maximum length queue of pending connections (configuration)
    	int threads;	   //Initial threads amount (configuration)
    	int timeOut;       //Socket time-out (configuration)
    	int protocol;      //Telnet, http (configuration)

    	int listenHd;	   //Listener handler
    	socklen_t addrlen;
    	pthread_mutex_t mlock;

    	int threadCount;

    	Meter *meter;

    	int tcpListen(socklen_t *addrlenp);

    	//Service threads
    	void threadMake();
    	void threadMain();
    	static void *threadCallback(void *arg);
/*
    	//Tareas pre-arrancadas
    	void preThreadMake(string actionName);
    	void preThreadMain(string actionName);
    	static void *preThreadCallback(void *arg);
    	*/
};

#endif /* SERVER_H_ */
