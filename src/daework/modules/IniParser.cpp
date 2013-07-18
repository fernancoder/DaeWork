/*
 * IniParser.cpp
 *
 *  Created on: 16/07/2013
 *      Author: fernando
 */

#include "IniParser.h"
#include "../utils/Util.h"

bool IniParser::instanceFlag=0;
IniParser *IniParser::iniParser=0;

IniParser* IniParser::getInstance()
{
    if(!instanceFlag)
    {
    	iniParser = new IniParser();
		instanceFlag = true;
		return iniParser;
    }
    else
    {
		return iniParser;
    }
}

IniParser::IniParser()
{

}

IniParser::~IniParser()
{
	this->freeSections();
}


int IniParser::start(string iniPath, string env)
{

    ifstream ifOrg;
    ifOrg.open (iniPath.c_str(),ios_base::in);
    if ( !ifOrg.is_open() )
    	return INI_PARSER_FILE_NOT_FOUND;

    string line;
    string sectionName;

    while (getline(ifOrg, line, '\n'))
    {
		line = this->lineCompact(line);
		if ( line.empty() )
			continue;

		if ( line.at(0) == '[' )
		{
			sectionName = line.substr(1,line.size()-2);
			string inheritName = this->extractInheritName(sectionName);
			sectionName = this->extractSectionName(sectionName);
			this->sections[sectionName] = new Section();
			if ( !inheritName.empty() )
				copySection(this->sections[sectionName], this->sections[inheritName]);
		}
		else
		{
			this->insertValue(&(this->sections[sectionName]->values),line.c_str());
		}
	}

    this->selectedSection = this->sections[env];
    //this->traceIni();

    return INI_PARSER_NO_ERROR;
}

void IniParser::insertValue(map<string, Value* > *values, const char *strLine)
{
	char keyName[MAX_SUBKEY_LENGTH];
	const char *ptr = strLine;

	while ( *ptr )
	{
		if ( *ptr == '.' || *ptr == '=')
		{
			memcpy(keyName, strLine, ptr-strLine);
			keyName[ptr-strLine] = '\0';

			if ( !values->count(string(keyName)) )
			{
				(*values)[string(keyName)] = new Value();
			}
		    if ( *ptr == '=' )
		    {
		    	ptr++;
		    	int ptrLen = strlen(ptr);
		    	if ( *(ptr) == '\'' )
		    	{
		    		ptr++;
		    		ptrLen -= 2;
		    	}
		    	values->at(string(keyName))->value = string(ptr,ptrLen);
			    return;
		    }

			this->insertValue(&(values->at(string(keyName))->values), ptr+1);
		    return;
		}

		++ptr;
	}
}

string IniParser::getStringWithDefault(string key1, string defaultValue)
{
	string actualValue = this->selectedSection->values[key1]->value;
	if ( actualValue.empty() )
		return defaultValue;
	return actualValue;
}

string IniParser::getStringWithDefault(string key1, string key2, string defaultValue)
{
	string actualValue = this->selectedSection->values[key1]->values[key2]->value;
	if ( actualValue.empty() )
		return defaultValue;
	return actualValue;
}

string IniParser::getStringWithDefault(string key1, string key2, string key3, string defaultValue)
{
	string actualValue = this->selectedSection->values[key1]->values[key2]->values[key3]->value;
	if ( actualValue.empty() )
		return defaultValue;
	return actualValue;
}

string IniParser::getStringWithDefault(string key1, string key2, string key3, string key4, string defaultValue)
{
	string actualValue = this->selectedSection->values[key1]->values[key2]->values[key3]->values[key4]->value;;
	if ( actualValue.empty() )
		return defaultValue;
	return actualValue;
}

int IniParser::getIntWithDefault(string key1, int defaultValue)
{
	string response = this->getStringWithDefault(key1, Util::intToString(defaultValue));
	return atoi(response.c_str());

}

int IniParser::getIntWithDefault(string key1, string key2, int defaultValue)
{
	string response = this->getStringWithDefault(key1, key2, Util::intToString(defaultValue));
	return atoi(response.c_str());
}

int IniParser::getIntWithDefault(string key1, string key2, string key3, int defaultValue)
{
	string response = this->getStringWithDefault(key1, key2, key3, Util::intToString(defaultValue));
	return atoi(response.c_str());
}

int IniParser::getIntWithDefault(string key1, string key2, string key3, string key4, int defaultValue)
{
	string response = this->getStringWithDefault(key1, key2, key3, key4, Util::intToString(defaultValue));
	return atoi(response.c_str());
}

string IniParser::extractName(string sectionName, bool extractSection)
{
	string section;
	string inherit;

	const char *ptr = sectionName.c_str();
	int stat = 0;
	while ( *ptr )
	{
		switch (stat)
		{
		    case 0:
		    	if ( *ptr == ':' )
		    		stat = 1;
		    	else
		    		section.append(1,*ptr);
		    break;
		    case 1:
		    	inherit.append(1,*ptr);
		    break;
		}
		ptr++;
	}
	if ( extractSection )
		return section;
	return inherit;
}

string IniParser::extractInheritName(string sectionName)
{
	return this->extractName(sectionName, false);
}

string IniParser::extractSectionName(string sectionName)
{
	return this->extractName(sectionName, true);
}

void IniParser::copySection(Section *desSection, Section *orgSection)
{
    this->copyValues(&(desSection->values), &(orgSection->values));
}

void IniParser::copyValues(map<string, Value* > *desValues, map<string, Value* > *orgValues)
{
	for ( map<string, Value* >::const_iterator it=orgValues->begin(); it!=orgValues->end(); ++it)
	{
		if ( !desValues->count(it->first) )
			(*desValues)[it->first] = new Value();
        this->copyValues(&((*desValues)[it->first]->values), &(it->second->values));

	    if ( !it->second->value.empty() )
			(*desValues)[it->first]->value = it->second->value;

	}
}

void IniParser::freeSections()
{
	for ( map<string, Section* >::const_iterator it=this->sections.begin(); it!=this->sections.end(); ++it)
	{
		this->freeValues(&(it->second->values));
		delete it->second;
	}
}

void IniParser::freeValues(map<string, Value* > *values)
{
	for ( map<string, Value* >::const_iterator it=values->begin(); it!=values->end(); ++it)
	{
		this->freeValues(&(it->second->values));
		delete it->second;
	}
}

void IniParser::traceIni()
{
	for ( map<string, Section* >::const_iterator it=this->sections.begin(); it!=this->sections.end(); ++it)
	{
		cout << it->first << endl;
		this->traceValue(&(it->second->values),string(""));
	}
}

void IniParser::traceValue(map<string, Value* > *values, string previousKeys)
{
	for ( map<string, Value* >::const_iterator it=values->begin(); it!=values->end(); ++it)
	{
		if ( it->second->value.empty() )
		{
			string newPreviousKeys = previousKeys;
			if ( previousKeys.empty() )
				newPreviousKeys.append(string("    "));
			else
			    newPreviousKeys.append(string("."));
			newPreviousKeys.append(string(it->first));
			this->traceValue(&(it->second->values), newPreviousKeys);
		}
		else
			cout << previousKeys << "." << it->first << "=" << it->second->value << endl;
	}
}

string IniParser::lineCompact(string line)
{
	string lineOut = string("");
	for ( string::const_iterator it=line.begin(); it!=line.end(); ++it)
        if ( *it != ' ' && *it != '\t' )
		    lineOut.append(1,*it);

	return lineOut;
}

