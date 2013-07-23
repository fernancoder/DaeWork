/*
 * Util.cpp
 *
 *  Created on: 11/05/2013
 *      Author: fernando
 */

//#include "Util.h"
#include "../daework-utils.h"

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
	char *ptr = buffer+strlen(buffer)-1;
	while ( *ptr && (*ptr == '\r' || *ptr == '\n') )
		*(ptr--) = '\0';
	return buffer;
}

/*
void CleanURL(char * buffer) {
    char asciinum[3] = {0};
    int i = 0, c;

    while ( buffer[i] ) {
	if ( buffer[i] == '+' )
	    buffer[i] = ' ';
	else if ( buffer[i] == '%' ) {
	    asciinum[0] = buffer[i+1];
	    asciinum[1] = buffer[i+2];
	    buffer[i] = strtol(asciinum, NULL, 16);
	    c = i+1;
	    do {
		buffer[c] = buffer[c+2];
	    } while ( buffer[2+(c++)] );
	}
	++i;
    }
}
*/
