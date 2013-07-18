/*
 * Util.h
 *
 *  Created on: 11/05/2013
 *      Author: fernando
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "../include.h"

class Util {
public:
	Util();
	virtual ~Util();

    static vector<string> split(string buffer, char separator);
    static string intToString(int i);
    static char *rtrim(char *buffer);
};

#endif /* UTIL_H_ */
