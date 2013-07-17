/*
 * LogManager.h
 *
 *  Created on: 16/07/2013
 *      Author: fernando
 */

#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include "../include.h"

const int MAX_LOG_IDENT = 1024;

const int LOG_NO_ERROR = 0;

class LogManager {
public:
	static bool instanceFlag;
	static LogManager *logManager;
	static LogManager* getInstance();
	int start(string module, string env);

	LogManager();
	virtual ~LogManager();

	void write(string message, int priority);

private:
	char ident[MAX_LOG_IDENT];

	int facility;
	string app;
	string module;
	string enviroment;
	int levelLog;

	bool isOpen;
};

#endif /* LOGMANAGER_H_ */
