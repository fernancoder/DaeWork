/*
 * CommHttp.cpp
 *
 *  Created on: 15/07/2013
 *      Author: fernando
 */

#include "../daework-support.h"
/*
CommHttp::CommHttp() {
	// TODO Auto-generated constructor stub

}*/

CommHttp::~CommHttp() {
	// TODO Auto-generated destructor stub
}

int CommHttp::analizeComm()
{
	string strReciebe;
	this->readLine(this->connfd, &strReciebe, MAX_BUFF_COMM);
	strReciebe = this->decode(strReciebe);
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

string CommHttp::decode(string strURL)
{
	return Util::decodeURL(strURL);
}

int CommHttp::extractParams(string strReciebe)
{
	//cout << strReciebe << endl;

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
		    	if ( *ptrReciebe == '&' /*|| *ptrReciebe == ' '*/ )
		    	{
		    		*paramValuePos = '\0';
		    	    this->requestParams[string(paramKey)] =string(paramValue);
		    	    paramKeyPos = paramKey;
		    	    paramValuePos = paramValue;
	    		    status = 1;
		    	}
		    	else
		    		*paramValuePos++ = *ptrReciebe;
		    break;
		}
		ptrReciebe++;
	}
	//El último
	if ( status == 2 )
	{
	    *paramValuePos = '\0';
        this->requestParams[string(paramKey)] =string(paramValue);
	}

	/*for(map<string, string>::const_iterator param = this->requestParams.begin(); param!=this->requestParams.end(); param++)
	{
		cout << param->first << " - " << param->second << endl;
	}*/

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
	string responseContent = "HTTP/1.0 200 OK\r\nServer: Daework v0.1\r\nContent-Type: text/html\r\nContent-Length: ";
	responseContent.append(Util::intToString(this->sendBuffer.length()));
	responseContent.append("\r\nConnection: close\r\n\r\n");
    //fprintf(f, "Last-Modified: %s\r\n", timebuf);
	responseContent.append(this->sendBuffer);
    return write(this->connfd,responseContent.c_str(),responseContent.length());
}

