/*
 * LogManager.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernando
 */

#include "LogManager.h"
#include "IniParser.h"

bool LogManager::instanceFlag=0;
LogManager *LogManager::logManager=0;

LogManager* LogManager::getInstance()
{
    if(!instanceFlag)
    {
    	logManager = new LogManager();
		instanceFlag = true;
		return logManager;
    }
    else
    {
		return logManager;
    }
}

LogManager::LogManager()
{
	this->isOpen = false;
}

LogManager::~LogManager()
{
    if ( this->isOpen )
    	closelog();
}

int LogManager::start(string module, string enviroment)
{
	this->levelLog = IniParser::getInstance()->getIntWithDefault("log", "level", 0);
	this->facility = IniParser::getInstance()->getIntWithDefault("log", "facility", 160);
	this->app = IniParser::getInstance()->getStringWithDefault("log", "app", "TEST");
	this->module = IniParser::getInstance()->getStringWithDefault("log", "module", module, "MAIN");
	this->enviroment = enviroment;

	string progName = "#";
	progName.append(app);
	progName.append("#");
	progName.append(module);
	progName.append("#");
	progName.append(enviroment);
	progName.append("#");

	strcpy(ident,progName.c_str()); //ident debe ser persistente (¡que raro!)
	openlog (ident, LOG_CONS | LOG_PID | LOG_NDELAY, this->facility);

	this->isOpen = true;

	return LOG_NO_ERROR;
}

void LogManager::write(string message, int priority)
{
	syslog(priority, "%s", (char *)message.c_str());
}
