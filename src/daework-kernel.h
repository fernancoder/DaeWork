/*
 * daework.h
 *
 *  Created on: 23/07/2013
 *      Author: fernando
 */

#ifndef DAEWORK_KERNEL_H_
#define DAEWORK_KERNEL_H_

#include "daework-include.h"

class Comm; //Forward declaration"
class Meter; //Forward declaration"
class Server; //Declaración "forward"
class Action; //Forward declaration"
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
		string getRequestParams();

		void send(const char *szBuff);

		bool dispatch();
		//void preDispatch(string actionName);

		int addMeasurement(string key);
		int getMeasurement(string key);
};
class Dispatcher
{
	public:
		virtual Action *getHandler(string action){return NULL;};
		virtual ~Dispatcher(){};

		//Comportamiento común
		virtual Action *defaultAction(string action);
};
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
    	void stop();
    	void signalHandler(int sig);
    	void threadStop();

    	Meter *getMeter(){return meter;};

    	/*void preStartThread(string actionName){this->preThreadMake(actionName);};*/

    	//Virtuales
    	virtual void init(){};
    	virtual Thread *createThreadObject(){return NULL;};
    	virtual Dispatcher *createDispatcherObject(){return NULL;};
    	Dispatcher *getDispatcherObject(){return dispatcherObject;};
    	int getServiceProtocol(){return protocol;};
    	int getSocketTimeOut(){return timeOut;};

    private:
    	Dispatcher *dispatcherObject;

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
		void sendSuccess(string response);
		void sendError(int id, string message);
		void closeConnection();
};
class Daemonizer
{
    private:
	    static Server *currentServer;
    public:
    	static void daemonize(Server *server, bool asDaemon);
    	static void signal_handler(int sig);
    	static void daemonShutdown();
    	virtual ~Daemonizer(){};
};

#endif /* DAEWORK_KERNEL_H_ */
