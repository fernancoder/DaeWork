/*
 * input.cpp
 *
 *  Created on: 19/10/2013
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
using namespace std;

#include "Input.h"

Input::Input()
{
	service = NULL;
}

Input::~Input() {
	clear();
}

void Input::getInput()
{
	clear();
	service = new(Service);

	cout << endl << "DaeWork code generator" << endl;
	cout << "Ver 1.0" << endl;
	service->name = this->getServiceName();
	while (true)
	{
		Verb *verb = new Verb();
		verb->name = this->getActionName();
		verb->className = this->firstCahrToUpper(verb->name) + "Action";
		if ( askForMore("Has this verb parameters? (Y/N): ") )
		{
			while (true)
			{
				string param = this->getParameterName();
				verb->params.push_back(param);
				if ( !askForMore("Do you want to enter another parameter (Y/N): ") )
					break;
			}
		}

		service->verbs.push_back(verb);

		if ( !askForMore("Do you want to enter another verb (Y/N): ") )
			break;
	}
	service->port = this->getPort();
	service->appId = this->getApp();
	service->path = this->getPath();
}

void Input::printSummary()
{
	cout << "\033[0;32m" << endl;
	cout << "Summary ******************************:" << endl << endl;
	cout << "Service: \033[1;32m" << service->name << "\033[0;32m" << endl;
	for(vector<Verb *>::iterator verbIt = service->verbs.begin(); verbIt != service->verbs.end(); ++verbIt) {
	    cout << "Verb: \033[1;32m" << (*verbIt)->name << "\033[0;32m" << endl;
	    string strParams = "";
	    for(vector<string>::iterator paramsIt = (*verbIt)->params.begin(); paramsIt != (*verbIt)->params.end(); ++paramsIt) {
	    	if ( !strParams.empty() )
	    		strParams.append("\033[0;32m, \033[1;32m");
	    	strParams.append(*paramsIt);
	    }
	    cout << "Parameters: \033[1;32m" << strParams << "\033[0;32m" << endl;
	}
	cout << "Port: \033[1;32m" << service->port << "\033[0;32m" << endl;
	cout << "App id: \033[1;32m" << service->appId << "\033[0;32m" << endl;
	cout << "Destination: \033[1;32m" << service->path << "\033[0;32m" << endl;
	cout << "\033[0m" << endl;
}

void Input::clear()
{
	if ( service != NULL )
	{
		for(vector<Verb *>::iterator verbIt = service->verbs.begin(); verbIt != service->verbs.end(); ++verbIt)
			delete (*verbIt);
		service->verbs.clear();
		delete service;
	}

	service = NULL;
}

void Input::loadForTest()
{
	clear();

	service = new(Service);
	Verb *verb;

	service->name = "test";

	verb = new Verb();
	verb->name = "actionOne";
	verb->className = "ActionOneAction";
	verb->params.push_back("paramOneOne");
	verb->params.push_back("paramOneTwo");
	verb->params.push_back("paramOneThree");
	service->verbs.push_back(verb);

	verb = new Verb();
	verb->name = "actionTwo";
	verb->className = "ActionTwoAction";
	verb->params.push_back("paramTwoOne");
	verb->params.push_back("paramTwoTwo");
	verb->params.push_back("paramTwoThree");
	service->verbs.push_back(verb);

	verb = new Verb();
	verb->name = "actionThree";
	verb->className = "ActionThreeAction";
	verb->params.push_back("paramThreeOne");
	verb->params.push_back("paramThreeTwo");
	verb->params.push_back("paramThreeThree");
	service->verbs.push_back(verb);

	service->port = "2041";
	service->appId = "TST";
	service->path = "test/";
}

void Input::showError(const char *msg)
{
    cout << "\033[0;31m" << msg << "\033[0m" << endl;
}

void Input::showWarning(const char *msg)
{
    cout << "\033[1;33m" << msg << "\033[0m" << endl;
}

bool Input::askForMore(const char *msg)
{
	string input="";

	while (true)
	{
	   string input="";
	   cout << msg;
	   getline(cin, input);
	   if ( !input.compare("Y") || !input.compare("y") )
		   return true;
	   if ( !input.compare("N") || !input.compare("n") )
		   return false;
	   this->showError("Wrong value (it must be Y or N)");
	}
}

string Input::getServiceName()
{
	string input="";
	while ( true )
	{
		cout << "Enter a short service name: ";
		getline(cin, input);
		string realInput = input;
		this->trim(input);

        if ( !this->verifyLength(input, 1, 8) )
        	continue;

        if ( !this->verifyFirstIsAlpha(input) )
           	continue;

        if( !this->verifyAlphaNumAscii(input) )
           	continue;

        this->toLower(input);

        if ( input.compare(realInput) )
        {
        	char msg[128];
        	sprintf(msg, "Warning value (you enter \"%s\" but we are going to use \"%s\")",realInput.c_str(), input.c_str());
        	this->showWarning(msg);
        }

		return input;
	}
}

string Input::getActionName()
{
	string input="";
	while (true)
	{
		cout << "Enter a short verb name: ";
		getline(cin, input);
        if ( !this->verifyLength(input, 1, 32) )
        	continue;
    	return input;
	}
}

string Input::getParameterName()
{
	string input="";
	while (true)
	{
		cout << "Enter a parameter name: ";
		getline(cin, input);
		if ( !this->verifyLength(input, 1, 32) )
        	continue;
		return input;
	}
}

string Input::getPort()
{
	string input="";
	while (true )
	{
		cout << "Enter port: ";
		getline(cin, input);
		if ( !this->verifyPort(input) )
        	continue;
	    return input;
	}
}

string Input::getApp()
{
	string input="";
	while (true )
	{
		cout << "Enter app id: ";
		getline(cin, input);
		if ( !this->verifyLength(input, 3) )
			continue;

		string realInput = input;
		this->toUpper(input);

        if ( input.compare(realInput) )
        {
        	char msg[128];
        	sprintf(msg, "Warning value (you enter \"%s\" but we are going to use \"%s\")",realInput.c_str(), input.c_str());
        	this->showWarning(msg);
        }
		return input;
	}
}

string Input::getPath()
{
	string input="";
	while ( true )
	{
		cout << "Enter destination path: ";
		getline(cin, input);

		if ( !this->verifyPath(input) )
			continue;

		if ( input[input.length()] != '/' )
			input.append("/");
		return input;
	}
}

//Utils
string &Input::ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
	return s;
}

string &Input::rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

string &Input::trim(string &s) {
	return ltrim(rtrim(s));
}

string &Input::toLower(string &s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower );
	return s;
}

string &Input::toUpper(string &s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper );
	return s;
}

string Input::firstCahrToUpper(string buffer)
{
	if ( buffer[0] >= 'a' )
		buffer[0] = buffer[0] - 32;
	return buffer;
}

bool Input::isAlphaNumAscii(string s)
{
	const char *ptr = s.c_str();
	while ( *ptr )
	{
		if ( (*ptr >= '0' && *ptr <= '9') || (*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z') )
		{
			ptr++;
			continue;
		}
		return false;
	}
	return true;
}

bool Input::isNum(string s)
{
	return count_if(s.begin(), s.end(), ::isdigit) == (int)s.size();
}

bool Input::verifyLength(string input, unsigned int minLength, unsigned int maxLength)
{
	if ( input.length() < minLength || input.length() > maxLength )
	{
		char errorMsg[128];
		sprintf(errorMsg,"Wrong value (length must be between %d and %d)", minLength, maxLength);
		this->showError(errorMsg);
		return false;
	}
	return true;
}

string Input::extractParentPath(string s)
{
	if ( s[s.size()-1] == '/')
		s.erase(s.size()-1);

	while ( s.size() && s[s.size()-1] != '/' )
		s.erase(s.size()-1);

	return s;
}

bool Input::verifyLength(string input, unsigned int length)
{
	if ( input.length() != length )
	{
		char errorMsg[128];
		sprintf(errorMsg,"Wrong value (length must be equal to %d)", length);
		this->showError(errorMsg);
		return false;
	}
	return true;
}

bool Input::verifyFirstIsAlpha(string input)
{
	if ( input[0] >= '0' && input[0] <= '9' )
	{
		this->showError("Wrong value (first char must be an alphabetic char)");
		return false;
	}
	return true;
}

bool Input::verifyAlphaNumAscii(string input)
{
	if( !this->isAlphaNumAscii(input) )
	{
		this->showError("Wrong value (only alphanumeric chars)");
		return false;
	}
	return true;
}

bool Input::verifyPort(string input)
{
	if ( !isNum(input) )
	{
		this->showError("Wrong value (only numeric chars)");
		return false;
	}
	long port = atol(input.c_str());
	if ( input.length() > 6 || port < 1 || port > 65535 )
	{
		this->showError("Wrong value (port value must be between 1 and 65535)");
		return false;
	}
	return true;
}

bool Input::verifyPath(string input)
{
	struct stat sb;

	if ( stat(input.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode) )
		return true;

	string parent = extractParentPath(input);
	if ( stat(parent.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode) )
	{
		char msg[512];
		sprintf(msg, "\033[1;33mWarning: \"%s\" doesn't exist but \"%s\" there. Would you like to create it? (Y/N)\033[0m ",input.c_str(), parent.c_str());
    	if ( this->askForMore(msg) )
    	{
    		if ( mkdir(input.c_str(),  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH) )
    		{
    			this->showError("Creation unsuccessful");
    			return false;
    		}
    		return true;
    	}
	}

	char errorMsg[128];
	sprintf(errorMsg,"Wrong value (directory \"%s\" doesn't exist)", input.c_str());
	this->showError(errorMsg);
	return false;
}


