/*
 * LogManager.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernando
 */

#include "../daework-support.h"

bool CmdLineParamManager::instanceFlag=0;
CmdLineParamManager *CmdLineParamManager::cmdLineParamManager=0;

CmdLineParamManager* CmdLineParamManager::getInstance()
{
    if(!instanceFlag)
    {
    	cmdLineParamManager = new CmdLineParamManager();
		instanceFlag = true;
		return cmdLineParamManager;
    }
    else
    {
		return cmdLineParamManager;
    }
}

void CmdLineParamManager::setCmdLineParam(string key, string value)
{
	mapCmdLineParams[key] = value;
}

string CmdLineParamManager::getCmdLineParam(string key)
{
	if ( this->mapCmdLineParams.find(key) != this->mapCmdLineParams.end() )
		return mapCmdLineParams[key];

	return string("");
}
