/*
 * CommTelnet.h
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

#ifndef COMMTELNET_H_
#define COMMTELNET_H_

#include "Comm.h"

class CommTelnet: public Comm {
public:
	CommTelnet(int timeOut):Comm(timeOut){};
	virtual ~CommTelnet();
};

#endif /* COMMTELNET_H_ */
