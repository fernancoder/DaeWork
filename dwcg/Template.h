/*
 * Template.h
 *
 *  Created on: 26/10/2013
 *      Author: fernando
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#define MAX_TEMPLATE_LINE 2048;

class Template {
public:
	Template();
	virtual ~Template();

	int generate(string templatePath, string outputPath, map<string, void*> *keyValue);

	string &toLower(string &s);
	string &toUpper(string &s);

private:
	string replace(string line, map<string, void*> *keyValue );
};

#endif /* TEMPLATE_H_ */
