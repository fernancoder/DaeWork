/*
 * Comm.cpp
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

#include "Comm.h"

Comm::Comm(int timeOut) {
	this->connfd = 0;
	this->timeOut = timeOut;
}

Comm::~Comm() {
	// TODO Auto-generated destructor stub
}

void Comm::setConnectionHandler(int connfd)
{
	this->connfd = connfd;
	this->isHeadWroten = false;
}

void Comm::closeConnectionHandler()
{
	if ( this->connfd )
	{
	    if ( this->isHeadWroten )
	        this->writeFootComm();
  	    close(this->connfd);
	    this->connfd = 0;
	}
}

ssize_t Comm::readLine(int connfd, string *strBuff, size_t maxlen)
{
	int readSize;
	char *szBuff = (char *)malloc((maxlen+1)*sizeof(char));

	time_t startTime = time(NULL);
	time_t curTime;

	for ( size_t i=0; i< maxlen; i++ )
	{
		curTime = time(NULL);
		if ( curTime - startTime > this->timeOut )
		{
			free(szBuff);
			return 0;
		}

		readSize = read(connfd, (szBuff+i), 1);
		if ( readSize )
		{
			if ( szBuff[i] == '\n' )
			{
				szBuff[i+1] = '\0';
				*strBuff = string(Util::rtrim(szBuff));
				free(szBuff);
				return strBuff->length();
			}
		}
	}

	free(szBuff);
	return 0;
}

string Comm::getRequestParam(string key)
{
	return this->requestParams[key];
}

