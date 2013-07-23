/*
 * Daemonizer.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */


//#include "Daemonizer.h"
#include "../daework-kernel.h"

//Método estático
void Daemonizer::daemonize(Server *server, bool asDaemon)
{
	if ( !asDaemon )
	{
		/* The Big Loop */
	    server->start();
	}

	/* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
            exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
       we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
            /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory */
    if ((chdir("/")) < 0) {
            /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */

    /* The Big Loop */
    server->start();

   	exit(EXIT_SUCCESS);
}


