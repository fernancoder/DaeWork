//============================================================================
// Name        : dwcg.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <map>
using namespace std;

#include "Template.h"
#include "Input.h"
#include "Generator.h"

int use(char *progName)
{
	cout << "Use:" << endl;
	cout << progName << " [-f template_path]" << endl;
	return (0);
}

bool verifyFile(char *path, char *file)
{
	char filePath[256];
	strcpy(filePath,path);
	strcat(filePath,"/");
	strcat(filePath,file);

	struct stat sb;

        if ( stat(filePath, &sb) == 0 && S_ISREG(sb.st_mode))
		return true;

	return false;
}

bool verifyTemplatePath(char *templatePath)
{
	struct stat sb;

	if ( stat(templatePath, &sb) == 0 && S_ISDIR(sb.st_mode) )
		return true;

	return false;
}

bool verifyTemplateFiles(char *templatePath)
{
	if ( verifyFile(templatePath,(char *)"action_cpp.tmp") &&
         verifyFile(templatePath,(char *)"action_h.tmp") &&
         verifyFile(templatePath,(char *)"dispatcher_cpp.tmp") &&
         verifyFile(templatePath,(char *)"dispatcher_h.tmp") &&
         verifyFile(templatePath,(char *)"ini.tmp") &&
         verifyFile(templatePath,(char *)"main.tmp") &&
         verifyFile(templatePath,(char *)"makefile.tmp") &&
         verifyFile(templatePath,(char *)"server_cpp.tmp") &&
         verifyFile(templatePath,(char *)"server_h.tmp") &&
         verifyFile(templatePath,(char *)"thread_cpp.tmp") &&
         verifyFile(templatePath,(char *)"thread_h.tmp") &&
         verifyFile(templatePath,(char *)"verb_cpp.tmp") &&
         verifyFile(templatePath,(char *)"verb_h.tmp") )

		return true;

	return false;
}

int main(int argc, char **argv) {

	if ( argc != 1 && argc != 3 )
		return use((char *)"dwcg");

	if ( argc == 3 && strcmp(argv[1],"-f") )
		return use((char *)"dwcg");

	char templatePath[256];

	if ( argc == 3 )
		strcpy(templatePath,argv[2]);
	else
		strcpy(templatePath,"/usr/local/share/dw_templates");

	if ( templatePath[strlen(templatePath)-1] == '/')
		templatePath[strlen(templatePath)-1] = '\0';

	Input *input = new Input();
	if ( !verifyTemplatePath(templatePath) )
	{
		input->showError("Template path not found");
		input->showError("Generation aborted");
	}
	else if ( !verifyTemplateFiles(templatePath) )
	{
		input->showError("Template files not found");
		input->showError("Generation aborted");
	}
	else
	{
		input->getInput();	//COMMENT FOR UNIT TEST!!! (see below)
		//input->loadForTest();	//ONLY FOR UNIT TEST!!!
		input->printSummary();

		if ( input->askForMore("Do you want to generate service code skeleton? (Y/N) ") )
		{
			Generator *generator = new Generator(input, templatePath);
			generator->execute();
			delete generator;
		}
		else
			input->showError("Generation aborted");
	}

	delete input;
}

