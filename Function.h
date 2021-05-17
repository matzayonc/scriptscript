#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Variable.h"
#include "Expression.h"
#include "Scope.h"

using string = std::string;


class FunctionInterface{
protected:
	string name;
	Scope* scope = nullptr;

public:
	FunctionInterface() :name("undefined") {};
	FunctionInterface(Scope& scope, string name) :scope(&scope), name(name) {};

	string getName() const;
	bool exists() const;

	virtual void execute(const std::vector<Variable*> args) const = 0;
};


class Function: public FunctionInterface {
protected:
	string code;
	void removeNonCode();

public:

	Function(Scope& scope, string name, string code)
	:FunctionInterface(scope, name), code(code) {
		removeNonCode();
	};

	void execute(const std::vector<Variable*> args) const;

};


//MOVEME: move to distinct file(folder?)

class OutBuildIn: public FunctionInterface {


public:
	void execute(const std::vector<Variable*> args) const {
		for(auto arg : args)
			std::cout << arg->getAsString() << ", ";

		std::cout << std::endl;
	}
};