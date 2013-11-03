/*
 * Util.cpp
 *
 *  Created on: 11/05/2013
 *      Author: fernando
 */

#include "../daework-support.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

vector<string> Util::split(string buffer, char separator)
{
        vector<string> parts;
        int iPos=0;
        int bufferLength = buffer.length();

        while ( iPos < bufferLength )
        {
                string part("");

                while ( iPos < bufferLength && buffer[iPos] != separator )
                {
                        part += buffer[iPos];
                        iPos++;
                }

                iPos++;
                parts.push_back(part);
        }

        return parts;
}

string Util::intToString(int i)
{
    stringstream ss;
    string s;
    ss << i;
    s = ss.str();

    return s;
}

char *Util::rtrim(char *buffer)
{
	if ( strlen(buffer) == 0 )
		return buffer;
	char *ptr = buffer+strlen(buffer)-1;
	while ( ptr >= buffer && (*ptr == '\r' || *ptr == '\n') )
		*(ptr--) = '\0';
	return buffer;
}


string Util::decodeURL(string URL)
{
    string ret;
    char ch;
    unsigned int i, ii;
    for (i=0; i<URL.length(); i++) {
        if (int(URL[i])==37) {
            sscanf(URL.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=URL[i];
        }
    }

    //erase HTTP/X.X
    int pos = ret.length();
    while ( pos && ret[pos-1] != ' ' )
        pos--;

    if ( pos >= 0 )
    	return ret.substr(0,pos-1);
    return ret;
}

void Util::sendStopToServer(string address, int port)
{
	struct hostent *hostp;
	int sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if ( sockfd < 0 )
	{
		string logMsg = "info.action=#killThread#;info.error=#Creation socket error#";
		LogManager::getInstance()->write(logMsg, LOG_INFO);
		return;
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port=htons(port);
	if ( (servaddr.sin_addr.s_addr = inet_addr(address.c_str())) ==  (unsigned long)INADDR_NONE )
	{
		hostp = gethostbyname(address.c_str());

		if(hostp == (struct hostent *)NULL)
		{
			string logMsg = "info.action=#killThread#;info.error=#Get host by name error#";
			LogManager::getInstance()->write(logMsg, LOG_INFO);
			return;
		}
		memcpy(&(servaddr.sin_addr), hostp->h_addr, sizeof(servaddr.sin_addr));
	}

	if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		string logMsg = "info.action=#killThread#;info.error=#Socket connection error#";
		LogManager::getInstance()->write(logMsg, LOG_INFO);
		close(sockfd);
		return;
	}

	string request = "GET /?action=s-t-o-p-s-e-r-v-e-r HTTP/1.1\n\n";
	write(sockfd,request.c_str(),request.length());

	close(sockfd);
}
