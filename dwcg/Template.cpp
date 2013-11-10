/*
 * Template.cpp
 *
 *  Created on: 26/10/2013
 *      Author: fernando
 */

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

#include "Template.h"

Template::Template() {
	// TODO Auto-generated constructor stub

}

Template::~Template() {
	// TODO Auto-generated destructor stub
}

int Template::generate(string templatePath, string outputPath, map <string, void*> *keyValue)
{
	fstream templateFh;
	templateFh.open(templatePath.c_str(), std::ios_base::in);
	if ( templateFh.fail() )
		return 1;

	fstream outputFh;
	outputFh.open(outputPath.c_str(), std::ios_base::out);
	if ( outputFh.fail() )
		return 2;

	string line;
	string block;
	int stat = 0;
	while ( getline(templateFh, line) )
	{
		switch ( stat )
		{
			case 0:
				if ( line.size() >= 10 && line.substr(0,10).compare("@@[repeat]") == 0 && line.substr(line.size()-9).compare("@@[end]@@") != 0 )
				{
					block = line + "\n";
					stat = 1;
				}
				else
					outputFh << replace(line,keyValue) << endl;
			break;
			case 1:
				block += (line  + "\n");
				if ( line.size() >= 9 && line.substr(0,9).compare("@@[end]@@") == 0 )
				{
					outputFh << replace(block,keyValue) << endl;
					block = "";
					stat = 0;
				}
			break;
		}
	}
	if ( templateFh.bad() )
		return 3;

	if ( outputFh.bad() )
		return 4;

	return 0;
}

string Template::replace(string line, map<string, void*> *keyValue )
{
	int stat = 0;
	int lineSize = line.length();
	string output = "";
	string key = "";
	string function = "";

	if ( line.size() >= 10 && line.substr(0,10).compare("@@[repeat]") == 0 )
	{
		string vectorName = "";
		string block = "";
		for ( int i = 0; i < lineSize; i++ )
		{
			switch (stat)
			{
				case 0:
					if ( line[i] == ']' )
						stat = 1;
				break;
				case 1:
					if ( line[i] == '@' )
						stat = 2;
					else
						vectorName += line[i];
				break;
				case 2:
					stat = 3;
				break;
				case 3:
					if ( line[i] == '@' )
						stat = 4;
					else
						block += line[i];
				break;
				case 4:
					if ( line[i] == '@' )
						stat = 5;
					else
					{
						block += '@';
						block += line[i];
						stat = 3;
					}
				break;
				case 5:
					if ( line[i] == '[' )
						stat = 6;
					else
					{
						block += "@@";
						block += line[i];
						stat = 3;
					}
				break;
				case 6:
					if ( line[i] == 'e' )
						stat = 7;
					else
					{
						block += "@@[";
						block += line[i];
						stat = 3;
					}
				break;
				case 7:
					if ( line[i] == 'n' )
						stat = 8;
					else
					{
						block += "@@[e";
						block += line[i];
						stat = 3;
					}
				break;
				case 8:
					if ( line[i] == 'd' )
						stat = 9;
					else
					{
						block += "@@[en";
						block += line[i];
						stat = 3;
					}
				break;
				case 9:
					if ( line[i] == ']' )
						stat = 10;
					else
					{
						block += "@@[end";
						block += line[i];
						stat = 3;
					}
				break;
				case 10:
				break;
			}
		}

		vector<map<string, void*> > *vectorMaps = (vector<map<string, void*> > *)(keyValue->find(vectorName)->second);
		for(vector<map<string, void*> >::iterator mapValues = vectorMaps->begin(); mapValues != vectorMaps->end(); ++mapValues)
		{
			output += this->replace(block, (map<string, void*> *)&*mapValues );
		}

		return output;

	}

	for ( int i = 0; i < lineSize; i++ )
	{
		switch (stat)
		{
			case 0:
				if ( line[i] == '@' )
					stat = 1;
				else
					output += line[i];
			break;
			case 1:
				if ( line[i] == '@' )
				{
					key = "";
					function = "";
					stat = 2;
				}
				else
				{
					output += "@";
					output += line[i];
                                        stat = 0;
				}
			break;
			case 2:
				if ( line[i] == '[' )
				{
					stat = 4;
				}
				else if ( line[i] == '@' )
				{
					string value = *(string *)(keyValue->find(key)->second);
					if ( !function.empty() )
					{
						if ( function.compare("Upper") == 0 )
							value = this->toUpper(value);
						else if ( function.compare("Lower") == 0 )
							value = this->toLower(value);
					}
					output.append(value);
					stat = 3;
				}
				else
					key += line[i];
			break;
			case 3:
				stat = 0;
			break;
			case 4:
				if ( line[i] == ']' )
				{
					stat = 2;
				}
				else
					function += line[i];
			break;
		}
	}

	if ( stat == 1 )	//line ends with @
		output += "@";

	return output;
}

string &Template::toLower(string &s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower );
	return s;
}

string &Template::toUpper(string &s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper );
	return s;
}

