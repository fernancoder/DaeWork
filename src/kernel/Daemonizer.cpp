/*
 * Daemonizer.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#include "../daework-kernel.h"
#include "../daework-support.h"

Server *Daemonizer::currentServer=0;

void Daemonizer::signal_handler(int sig)
{
    switch(sig)
    {
        case SIGHUP:
        	LogManager::getInstance()->write(string("info.action=#signalHandler#;info.signal=#SIGHUP#"), LOG_INFO);
        break;
        case SIGINT:
        	LogManager::getInstance()->write(string("info.action=#signalHandler#;info.signal=#SIGINT#"), LOG_INFO);
        	Daemonizer::daemonShutdown();
        	exit(EXIT_SUCCESS);
        case SIGTERM:
        	LogManager::getInstance()->write(string("info.action=#signalHandler#;info.signal=#SIGTERM#"), LOG_INFO);
        	Daemonizer::daemonShutdown();
            exit(EXIT_SUCCESS);
        break;
        default:
        	LogManager::getInstance()->write(string("info.action=#signalHandler#;info.signal=#UNHANDLED#"), LOG_INFO);
        break;
    }
}

void Daemonizer::daemonShutdown()
{
	LogManager::getInstance()->write(string("info.action=#shutingDown#"), LOG_INFO);
	Daemonizer::currentServer->stop();
}

//Static method
void Daemonizer::daemonize(Server *server, bool asDaemon)
{
	if ( !asDaemon )
	{
		//The Big Loop
	    server->start();
	}

	Daemonizer::currentServer = server;

    pid_t pid, sid;

    //Signal management
	struct sigaction newSigAction;
    sigset_t newSigSet;

    sigemptyset(&newSigSet);
    sigaddset(&newSigSet, SIGCHLD);  // ignore child - i.e. we don't need to wait for it
    sigaddset(&newSigSet, SIGTSTP);  // ignore Tty stop signals
    sigaddset(&newSigSet, SIGTTOU);  // ignore Tty background writes
    sigaddset(&newSigSet, SIGTTIN);  // ignore Tty background reads
    sigprocmask(SIG_BLOCK, &newSigSet, NULL);   // Block the above specified signals
    // Set up a signal handler
    newSigAction.sa_handler = signal_handler;
    sigemptyset(&newSigAction.sa_mask);
    newSigAction.sa_flags = 0;
    // Signals to handle
    sigaction(SIGHUP, &newSigAction, NULL);     // catch hangup signal
    sigaction(SIGTERM, &newSigAction, NULL);    // catch term signal
    sigaction(SIGINT, &newSigAction, NULL);     // catch interrupt

    //Fork the Parent Process
    pid = fork();
    if (pid < 0) {
            exit(EXIT_FAILURE);
    }

    //We got a good pid, Close the Parent Process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    //Open any logs here (pues no)

    //Change File Mask
    umask(0);

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    //Change Directory
    //If we cant find the directory we exit with failure.
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //The Big Loop
    server->start();

   	exit(EXIT_SUCCESS);
}


