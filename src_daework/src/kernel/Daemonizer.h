/*
 * Demonizer.h
 *
 *  Created on: 16/07/2013
 *      Author: fernancoder
 */

#ifndef DAEMONIZER_H_
#define DAEMONIZER_H_

#include "../include.h"
#include "Server.h"

class Daemonizer
{
    public:
    	static void daemonize(Server *server, bool asDaemon);
    	virtual ~Daemonizer(){};
};


#endif /* DAEMONIZER_H_ */
