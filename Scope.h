#pragma once
#include <map>
#include <string>
#include "Variable.h"
class Scope;
#include "Function.h"

class FunctionInterface;

using VariableScope = std::map<std::string, Variable*>;
using FunctionScope = std::map<std::string, FunctionInterface*>;


class Scope {
	static int counter;
	Scope* parent;
	short id;

	VariableScope variables;
	FunctionScope functions;


public:
	Scope(const Scope& other);
	Scope(Scope* parentScope = nullptr);
	~Scope();

	void registerVariable(string name, Variable* variable);
	void registerFunctions(string name, FunctionInterface* variable);

	bool contains(string name, bool stopPropagation=false);
	Variable* find(string name);

	int  getId() {
		return parent != nullptr ? parent->id : -1;
	}
};

