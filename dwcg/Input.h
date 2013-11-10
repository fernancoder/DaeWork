/*
 * input.h
 *
 *  Created on: 19/10/2013
 *      Author: fernando
 */

#ifndef INPUT_H_
#define INPUT_H_

struct Verb
{
	string name;
	string className;
	vector<string> params;
};

struct Service
{
	string name;
	vector<Verb *> verbs;
	string port;
	string appId;
	string path;
};

class Input {
private:
	Service *service;

public:
	Input();
	virtual ~Input();

	void getInput();
	void printSummary();
	void clear();
	void loadForTest();

public:
	bool askForMore(const char *msg);
	void showError(const char *msg);

private:
	void showWarning(const char *msg);

	string getServiceName();
	string getActionName();
	string getParameterName();
	string getPort();
	string getApp();
	string getPath();

	string &ltrim(std::string &s);
	string &rtrim(std::string &s);
	string &trim(std::string &s);
	string &toLower(string &s);
	string &toUpper(string &s);
	string firstCahrToUpper(string buffer);
	bool isAlphaNumAscii(string s);
	bool isNum(string s);
	string extractParentPath(string s);

	bool verifyLength(string input, unsigned int minLength, unsigned int maxLength);
	bool verifyLength(string input, unsigned int length);
	bool verifyFirstIsAlpha(string input);
	bool verifyAlphaNumAscii(string input);
	bool verifyPort(string input);
	bool verifyPath(string input);

public:
	string returnServiceName(){return service->name;};
	string returnServerName(){return firstCahrToUpper(service->name).append("Server");};
	string returnThreadName(){return firstCahrToUpper(service->name).append("Thread");};
	string returnDispatcherName(){return firstCahrToUpper(service->name).append("Dispatcher");};
	string returnActionName(){return firstCahrToUpper(service->name).append("Action");};
	string returnAppId(){return service->appId;};
	vector<Verb *>returnActions(){return service->verbs;};
	string returnPort(){return service->port;};
	string returnPath(){return service->path;};
};

#endif /* INPUT_H_ */
