/*
 * CommHttp.h
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

#ifndef COMMHTTP_H_
#define COMMHTTP_H_

#include "Comm.h"
#include "../utils/Util.h"

const int MAX_PARAM_KEY = 128;
const int MAX_PARAM_VALUE = 1024;

const int MAX_BUFF_COMM = 2048;

class CommHttp: public Comm {
    public:
	    CommHttp(int timeOut):Comm(timeOut){};
	    virtual ~CommHttp();

        int AnalizeComm();
	    int writeHeadComm();
        int writeBodyComm(const char *szBuff);
	    int writeFootComm();


    private:
        int extractParams(string strReciebe);

        string sendBuffer;
};

#endif /* COMMHTTP_H_ */
