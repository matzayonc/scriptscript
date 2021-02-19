#pragma once
#include <string>
#include <iostream>
#include "Variable.h"
#include "Expression.h"
#include "Scope.h"

using string = std::string;


class Function{
	string name;
	string code;
	Scope scope;

public:
	Function() :name("undefined") {};
	Function(Scope& scope, string name) :scope(scope), name(name) {};
	Function(Scope& scope, string name, string code) :scope(scope), name(name), code(code) {};

	string getName() const;
	bool exists() const;
	void removeComments();
	void execute();
};

