/*
 * Generator.h
 *
 *  Created on: 24/10/2013
 *      Author: fernando
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator {
public:
	Generator(Input *input, string templatePath);
	virtual ~Generator();

	bool execute();

private:
	Input *input;
	Template *procesator;
	string templatePath;

private:
	bool generate_service();
	bool generate_service_ini();
	bool generate_service_server_h();
	bool generate_service_server_cpp();
	bool generate_service_thread_h();
	bool generate_service_thread_cpp();
	bool generate_service_dispacher_h();
	bool generate_service_dispacher_cpp();
	bool generate_service_action_h();
	bool generate_service_action_cpp();
	bool generate_actions();
	bool generate_makefile();

	bool generate_action(Verb *verb);
	bool generate_action_h(Verb *verb);
    bool generate_action_cpp(Verb *verb);
};

#endif /* GENERATOR_H_ */
