/*
 * Server.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#include "../daework-kernel.h"
#include "../daework-support.h"

Server::Server(const char *iniFilePath, const char *env, const char *module)
{
	int error = IniParser::getInstance()->start(string(iniFilePath), string(env));

	if ( error != INI_PARSER_NO_ERROR )
	{
		cout  << "CONFIGURATION FILE FATAL ERROR!!!" << endl;
		switch (error)
		{
		    case INI_PARSER_FILE_NOT_FOUND:
		    	cout << "Configuration file not found" << endl;
		    break;
		    case INI_PARSER_SYNTAX_ERROR:
		    	cout << "Configuration file syntax error" << endl;
		    break;
		    default:
		    	cout << "Configuration undefined error" << endl;
		    break;
		}
		exit(error);
	}

	LogManager::getInstance()->start(string(module), string(env));

	this->port = IniParser::getInstance()->getIntWithDefault("service", "port", 2021);
	this->backlog_size = IniParser::getInstance()->getIntWithDefault("service", "backlog_size", 1024);
	this->threads = IniParser::getInstance()->getIntWithDefault("service", "threads", 20);
	this->timeOut = IniParser::getInstance()->getIntWithDefault("service", "timeout", 30);
	string strProtocol = IniParser::getInstance()->getStringWithDefault("service", "protocol", "http");
	if ( !strProtocol.compare("telnet") )
		this->protocol = SERVER_PROTOCOL_TELNET;
	else if ( !strProtocol.compare("http") )
		this->protocol = SERVER_PROTOCOL_HTTP;
	else
	{
		string logMsg = "info.action=#startDaeworkServer#;info.error=#Unsuported service protocol#";
		LogManager::getInstance()->write(logMsg, LOG_INFO);
		exit(1);
	}

	//Debug
	string logMsg;
	logMsg = "info.action=#startDaeworkServer#;info.config.port=#";
	logMsg.append(Util::intToString(this->port));
	logMsg.append("#;info.config.backlogSize=#");
	logMsg.append(Util::intToString(this->backlog_size));
	logMsg.append("#;info.config.threads=#");
	logMsg.append(Util::intToString(this->threads));
	logMsg.append("#;info.config.timeout=#");
	logMsg.append(Util::intToString(this->timeOut));
	logMsg.append("#");
	LogManager::getInstance()->write(logMsg, LOG_INFO);

   	this->meter = new Meter();

	pthread_mutex_init(&mlock,NULL);
}


void Server::start()
{
	this->init();
	this->listenHd = tcpListen(&(this->addrlen));

	this->threadCount = 0;
	for (int i = 0;  i < this->threads; i++)
		this->threadMake();

	for ( ; ; )
		pause();
}

void Server::stop()
{
	LogManager::getInstance()->write(string("info.action=#stopDaeworkServer#"), LOG_INFO);
}

int Server::tcpListen(socklen_t *addrlenp)
{
	int listenfd;
	const int option = 1;

	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( getaddrinfo(NULL, Util::intToString(this->port).c_str(), &hints, &res) != 0)
		exit(0);
	ressave = res;

	do {
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (listenfd < 0)
			continue;		// error, try next one

		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
		if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;			// success

		close(listenfd);	// bind error, close and try next one


	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)	// errno from final socket() or bind()
	{
		string logMsg = "info.action=#createSocketListen#;info.result.error=#Socket error#";
		LogManager::getInstance()->write(logMsg, LOG_CRIT);
		exit(1);
	}

	listen(listenfd, this->backlog_size);
	if (addrlenp)
		*addrlenp = res->ai_addrlen;	// return size of protocol address

	freeaddrinfo(ressave);

	return(listenfd);
}

void Server::threadMake()
{
	pthread_attr_t attr;
	pthread_t thread_tid;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_tid, &attr, &(Server::threadCallback), (void *) this);
	pthread_attr_destroy(&attr);
	return;
}

//Método estático
void *Server::threadCallback(void *arg)
{
	((Server *)arg)->threadMain();
	return NULL;
}

void Server::threadMain()
{
	int     connfd;
	socklen_t clilen;
	struct sockaddr *cliaddr;
	Thread *threadObject = this->getThreadObject();
	threadObject->setServer(this);
	threadObject->init();

	cliaddr = (struct sockaddr *)malloc(addrlen);

	string logMsg = "info.action=#startThread#;info.threadCount=#";
	logMsg.append(Util::intToString(this->threadCount++));
	logMsg.append("#");
	LogManager::getInstance()->write(logMsg, LOG_INFO);

	for ( ; ; ) {
		clilen = addrlen;
		pthread_mutex_lock(&mlock);
		connfd = accept(listenHd, cliaddr, &clilen);
		pthread_mutex_unlock(&mlock);
		threadObject->setConnectionHandler(connfd);
		threadObject->dispatch();      // process request
	}
}
/*
void Server::preThreadMake(string actionName)
{
	PreThreadInfo *preThreadInfo = new PreThreadInfo();
	preThreadInfo->server = this;
	preThreadInfo->actionName = actionName;

	pthread_t thread_tid;
	pthread_create(&thread_tid, NULL, &(Server::preThreadCallback), (void *)preThreadInfo);
	return;
}

//Método estático
void *Server::preThreadCallback(void *preThreadInfo)
{
	((PreThreadInfo *)preThreadInfo)->server->preThreadMain(((PreThreadInfo *)preThreadInfo)->actionName);
	return NULL;
}

void Server::preThreadMain(string actionName)
{
	Thread *threadObject = this->getThreadObject();
	threadObject->setServer(this);
	threadObject->init();

	cout << "pre_start_thread" << endl;
	//Log::writeLog("pre_start_thread",LOG_LEVEL_VERBOSE);

	threadObject->preDispatch(actionName);      // process request
}
*/
