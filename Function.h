#pragma once
#include <string>
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

	virtual void execute(Variable&) const = 0;
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

	void execute() const;

};


//MOVEME: move to distinct file(folder?)

class Out: public FunctionInterface {


public:
	void execute(Variable& var) const { //FIXME: Dynamic arguments?
		std::cout << var.getAsString() << std::endl;
	}
};