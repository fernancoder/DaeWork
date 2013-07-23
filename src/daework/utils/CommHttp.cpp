/*
 * CommHttp.cpp
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

//#include "CommHttp.h"
#include "../daework-utils.h"
/*
CommHttp::CommHttp() {
	// TODO Auto-generated constructor stub

}*/

CommHttp::~CommHttp() {
	// TODO Auto-generated destructor stub
}

int CommHttp::AnalizeComm()
{
	string strReciebe;
	this->readLine(this->connfd, &strReciebe, MAX_BUFF_COMM);
	if ( strReciebe.substr(0,3).compare("GET") )
		return COMM_HTTP_PROTOCOL_SYNTAXIS_ERROR;

	int status = this->extractParams(strReciebe);
    while (strReciebe.compare(""))
    {
    	this->readLine(this->connfd, &strReciebe, MAX_BUFF_COMM);
    }

	if ( status != REQUEST_NO_ERROR )
		return status;

    return COMM_NO_ERROR;
}

int CommHttp::extractParams(string strReciebe)
{
	this->requestParams.clear();

	const char *ptrReciebe = strReciebe.c_str();
	int status = 0;

	char paramKey[MAX_PARAM_KEY];
	char *paramKeyPos = paramKey;

	char paramValue[MAX_PARAM_VALUE];
	char *paramValuePos = paramValue;

	while ( *ptrReciebe )
	{
		switch( status )
		{
		    case 0:  //begin
		    	if ( *ptrReciebe == '?' )
		    		status = 1;
		    break;
		    case 1:  //key
		    	if ( *ptrReciebe == '=' )
		    	{
		    		*paramKeyPos = '\0';
		    		status = 2;
		    	}
		    	else
		    		*paramKeyPos++ = *ptrReciebe;
		    break;
		    case 2:  //value
		    	if ( *ptrReciebe == '&' || *ptrReciebe == ' ' )
		    	{
		    		*paramValuePos = '\0';
		    	    this->requestParams[string(paramKey)] =string(paramValue);
		    	    paramKeyPos = paramKey;
		    	    paramValuePos = paramValue;

		    	    if ( *ptrReciebe == '&' )
		    		    status = 1;
		    	    else if ( *ptrReciebe == ' ' )
		    		    status = 3;
		    	}
		    	else
		    		*paramValuePos++ = *ptrReciebe;
		    break;
		    case 3:   //end
		    break;
		}
		ptrReciebe++;
	}

	if ( status != 3 )
		return REQUEST_PARAMS_SYNTAXIS_ERROR;

	return REQUEST_NO_ERROR;
}

int CommHttp::writeBodyComm(const char *szBuff)
{
	if ( !this->isHeadWroten )
	{
		this->writeHeadComm();
		this->isHeadWroten = true;
	}
	this->sendBuffer.append(string(szBuff));
	return COMM_NO_ERROR;
}

int CommHttp::writeHeadComm()
{
	this->sendBuffer = string("");
	this->isHeadWroten = true;
	return COMM_NO_ERROR;
}

int CommHttp::writeFootComm()
{
	string responseContent = "HTTP/1.0 %d OK\r\nServer: Daework v0.1\r\nContent-Type: text/html\r\nContent-Length: ";
	responseContent.append(Util::intToString(this->sendBuffer.length()));
	responseContent.append("\r\nConnection: close\r\n\r\n");
    //fprintf(f, "Last-Modified: %s\r\n", timebuf);
	responseContent.append(this->sendBuffer);
    write(this->connfd,responseContent.c_str(),responseContent.length());

	return COMM_NO_ERROR;
}

