#pragma once
#include <string>
#include <iostream>
#include "Variable.h"

using string = std::string;


class Function{
	string name;
	string code;

public:
	Function() :name("undefined") {};
	Function(string name) :name(name) {};
	Function(string name, string code) :name(name), code(code) {};
	Function(const Function& var) :name(var.getName()) {};

	string getName() const;
	bool exists() const;
	void execute();
};

