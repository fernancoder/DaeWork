/*
 * daework-modules.h
 *
 *  Created on: 23/07/2013
 *      Author: fernando
 */

#ifndef DAEWORK_MODULES_H_
#define DAEWORK_MODULES_H_

#include "daework-include.h"

const int MAX_SUBKEY_LENGTH = 128;

const int INI_PARSER_NO_ERROR = 0;
const int INI_PARSER_FILE_NOT_FOUND = 1;
const int INI_PARSER_SYNTAX_ERROR = 2;

typedef struct _Value Value;

typedef struct _Value
{
	string value;
	map<string, Value* > values;
} Value;

typedef struct _Section
{
	map<string, Value* > values;

} Section;

class IniParser {
public:
	static bool instanceFlag;
	static IniParser *iniParser;
	static IniParser* getInstance();

	IniParser();
	virtual ~IniParser();
	int start(string iniPath, string env);

	void insertValue(map<string, Value* > *values, const char *strLine);

	string getStringWithDefault(string key1, string defaultValue);
	string getStringWithDefault(string key1, string key2, string defaultValue);
	string getStringWithDefault(string key1, string key2, string key3, string defaultValue);
	string getStringWithDefault(string key1, string key2, string key3, string key4, string defaultValue);

	int getIntWithDefault(string key1, int defaultValue);
	int getIntWithDefault(string key1, string key2, int defaultValue);
	int getIntWithDefault(string key1, string key2, string key3, int defaultValue);
	int getIntWithDefault(string key1, string key2, string key3, string key4, int defaultValue);

private:
	string extractName(string sectionName, bool extractSection);
	string extractInheritName(string sectionName);
    string extractSectionName(string sectionName);
    void copySection(Section *desSection, Section *orgSection);
    void copyValues(map<string, Value* > *desValues, map<string, Value* > *orgValues);
    void freeSections();
    void freeValues(map<string, Value* > *values);
	void traceIni();
	void traceValue(map<string, Value* > *values, string previousKeys);
	string lineCompact(string line);
	string intToString(int i);

private:
	string iniPath;
	string env;
	map<string, Section* > sections;
	Section *selectedSection;
};
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


#endif /* DAEWORK_MODULES_H_ */
