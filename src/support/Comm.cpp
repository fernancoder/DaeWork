/*
 * Comm.cpp
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

#include "../daework-support.h"

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

string Comm::getLogParams()
{
	string infoRequest = string("");
	bool isFirst = true;
	for (map<string, string>::iterator iter = this->requestParams.begin(); iter != this->requestParams.end(); ++iter)
	{
		if ( isFirst )
		{
			infoRequest.append("info.action=#");
			infoRequest.append(iter->second);
			infoRequest.append("#");
		}
		else
		{
			infoRequest.append(";info.request.");
			infoRequest.append(iter->first);
			infoRequest.append("=#");
			infoRequest.append(iter->second);
			infoRequest.append("#");
		}
		isFirst = false;
	}

	return infoRequest;
}


string Comm::getRequestParams()
{
	string response = string("");
	bool isFirst = true;
	for (map<string, string>::iterator iter = this->requestParams.begin(); iter != this->requestParams.end(); ++iter)
	{
		if ( !isFirst )
		    response.append(",");
		response.append("\"");
		response.append(iter->first);
		response.append("\" : \"");
		response.append(iter->second);
		response.append("\"");

		isFirst = false;
	}

	return response;
}



