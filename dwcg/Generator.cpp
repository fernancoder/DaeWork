/*
 * Generator.cpp
 *
 *  Created on: 24/10/2013
 *      Author: fernando
 */

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <vector>
#include <map>
using namespace std;

#include "Template.h"
#include "Input.h"
#include "Generator.h"

Generator::Generator(Input *input, string templatePath)
{
	this->input = input;
	this->templatePath = templatePath;
	procesator = new Template();
}

Generator::~Generator()
{
	delete procesator;
}

bool Generator::execute()
{
	cout << endl << "Generate *****************************:" << endl;
	if ( !generate_service() ||
	     !generate_service_ini() ||
	     !generate_service_server_h() ||
	     !generate_service_server_cpp() ||
	     !generate_service_thread_h() ||
	     !generate_service_thread_cpp() ||
	     !generate_service_dispacher_h() ||
	     !generate_service_dispacher_cpp() ||
	     !generate_service_action_h() ||
	     !generate_service_action_cpp() ||
	     !generate_actions() ||
	     !generate_makefile() )
	{
		cout << endl << "\033[0;31mProcess fail\033[0m" << endl << endl;
		return true;
	}
	cout << endl << "\033[0;32mProcess completed successfully ******\033[0m" << endl << endl;
	return false;
}

bool Generator::generate_service()
{
	map<string,void*> keyValuePairs;

	string serverName = input->returnServerName();
	string serviceName = input->returnServiceName();
    string appId = input->returnAppId();
	keyValuePairs["server"] = (void *)&serverName;
	keyValuePairs["service"] = (void *)&serviceName;
	keyValuePairs["appid"] = (void *)&appId;

	cout << serviceName << ".cpp" << endl;

	if ( procesator->generate(templatePath + "/main.tmp", input->returnPath() + serviceName + ".cpp", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_ini()
{
	map<string,void*> keyValuePairs;

	string serviceName = input->returnServiceName();
	string appId = input->returnAppId();
	string port = input->returnPort();
	keyValuePairs["appid"] = (void *)&appId;
	keyValuePairs["port"] = (void *)&port;

	cout << serviceName << ".ini" << endl;

	if ( procesator->generate(templatePath + "/ini.tmp", input->returnPath() + serviceName + ".ini", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_server_h()
{
	map<string,void*> keyValuePairs;

	string serverName = input->returnServerName();
	keyValuePairs["server"] = (void *)&serverName;

	cout << serverName << ".h" << endl;

	if ( procesator->generate(templatePath + "/server_h.tmp", input->returnPath() + serverName + ".h", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_server_cpp()
{
	map<string,void*> keyValuePairs;

	string serverName = input->returnServerName();
	string threadName = input->returnThreadName();
	string dispatcherName = input->returnDispatcherName();
	keyValuePairs["server"] = (void *)&serverName;
	keyValuePairs["thread"] = (void *)&threadName;
	keyValuePairs["dispatcher"] = (void *)&dispatcherName;

	cout << serverName << ".cpp" << endl;

	if ( procesator->generate(templatePath + "/server_cpp.tmp", input->returnPath() + serverName + ".cpp", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_thread_h()
{
	map<string,void*> keyValuePairs;

	string threadName = input->returnThreadName();
	keyValuePairs["thread"] = (void *)&threadName;

	cout << threadName << ".h" << endl;

	if ( procesator->generate(templatePath + "/thread_h.tmp", input->returnPath() + threadName + ".h", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_thread_cpp()
{
	map<string,void*> keyValuePairs;

	string threadName = input->returnThreadName();
	keyValuePairs["thread"] = (void *)&threadName;

	cout << threadName << ".cpp" << endl;

	if ( procesator->generate(templatePath + "/thread_cpp.tmp", input->returnPath() + threadName + ".cpp", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_dispacher_h()
{
	map<string,void*> keyValuePairs;

	string dispatcherName = input->returnDispatcherName();
	keyValuePairs["dispatcher"] = (void *)&dispatcherName;

	cout << dispatcherName << ".h" << endl;

	if ( procesator->generate(templatePath + "/dispatcher_h.tmp", input->returnPath() + dispatcherName + ".h", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_dispacher_cpp()
{
	map<string,void*> keyValuePairs;

	string dispatcherName = input->returnDispatcherName();
	keyValuePairs["dispatcher"] = (void *)&dispatcherName;

	vector<Verb *> verbs = input->returnActions();
	vector<map<string, void*> > actions;
	for(vector<Verb *>::iterator verbIt = verbs.begin(); verbIt != verbs.end(); ++verbIt) {
		map<string, void*> action;
		action["verb"] = (void *)&((*verbIt)->name);
		action["className"] = (void *)&((*verbIt)->className);
		actions.push_back(action);
	}
	keyValuePairs["actions"] = (void *)&actions;

	cout << dispatcherName << ".cpp" << endl;

	if ( procesator->generate(templatePath + "/dispatcher_cpp.tmp", input->returnPath() + dispatcherName + ".cpp", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_action_h()
{
	map<string,void*> keyValuePairs;

	string actionName = input->returnActionName();
	keyValuePairs["action"] = (void *)&actionName;

	cout << actionName << ".h" << endl;

	if ( procesator->generate(templatePath + "/action_h.tmp", input->returnPath() + actionName + ".h", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_service_action_cpp()
{
	map<string,void*> keyValuePairs;

	string actionName = input->returnActionName();
	keyValuePairs["action"] = (void *)&actionName;

	cout << actionName << ".cpp" << endl;

	if ( procesator->generate(templatePath + "/action_cpp.tmp", input->returnPath() + actionName + ".cpp", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_actions()
{
	vector<Verb *> verbs = input->returnActions();
	for(vector<Verb *>::iterator verbIt = verbs.begin(); verbIt != verbs.end(); ++verbIt) {
		if ( !generate_action(*verbIt) )
			return false;
	}
	return true;
}

bool Generator::generate_makefile()
{
	map<string,void*> keyValuePairs;

	//string actionName = input->returnActionName();
	//keyValuePairs["action"] = (void *)&actionName;

	cout << "Makefile" << endl;

	if ( procesator->generate(templatePath + "/makefile.tmp", input->returnPath() + "Makefile", &keyValuePairs) == 0 )
		return true;
	return false;
}

bool Generator::generate_action(Verb *verb)
{
	if ( !generate_action_h(verb) )
		return false;
	if ( !generate_action_cpp(verb) )
		return false;

	return true;
}

bool Generator::generate_action_h(Verb *verb)
{
	map<string,void*> keyValuePairs;

	string actionName = input->returnActionName();
	string verbName = verb->className;
	keyValuePairs["action"] = (void *)&actionName;
	keyValuePairs["verb"] = (void *)&verbName;

	cout << verbName << ".h" << endl;

	if ( procesator->generate(templatePath + "/verb_h.tmp", input->returnPath() + verbName + ".h", &keyValuePairs) == 0 )
		return true;
	return false;
}
bool Generator::generate_action_cpp(Verb *verb)
{
	map<string,void*> keyValuePairs;

	string verbName = verb->className;
	keyValuePairs["verb"] = (void *)&verbName;

	vector<map<string, void*> > params;
	for(vector<string>::iterator paramIt = verb->params.begin(); paramIt != verb->params.end(); ++paramIt) {
		map<string, void*> param;
		param["param"] = (void *)&((*paramIt));
		params.push_back(param);
	}
	keyValuePairs["params"] = (void *)&params;

	cout << verbName << ".cpp" << endl;

	if ( procesator->generate(templatePath + "/verb_cpp.tmp", input->returnPath() + verbName + ".cpp", &keyValuePairs) == 0 )
		return true;
	return false;
}

