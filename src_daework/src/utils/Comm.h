/*
 * Comm.h
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

#ifndef COMM_H_
#define COMM_H_

const int COMM_NO_ERROR = 0;
const int COMM_HTTP_PROTOCOL_SYNTAXIS_ERROR = 1;

const int REQUEST_NO_ERROR = 0;
const int REQUEST_PARAMS_SYNTAXIS_ERROR = 1;

#include "../include.h"
#include "Util.h"

class Comm {
    public:
	    Comm(int timeOut);
	    virtual ~Comm();
	    virtual int AnalizeComm(){return 0;}
	    virtual int writeHeadComm(){return 0;}
	    virtual int writeBodyComm(const char *szBuff){return 0;}
	    virtual int writeFootComm(){return 0;}

	    void setConnectionHandler(int connfd);
   		void closeConnectionHandler();

   		ssize_t readLine(int connfd, string *strBuff, size_t maxlen);

   		string getRequestParam(string key);

    protected:
	    int connfd;
	    int timeOut;
	    bool isHeadWroten;

	    map<string, string> requestParams;
};

#endif /* COMM_H_ */
