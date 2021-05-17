#include <iostream>
#include "Scope.h"


int Scope::counter = 0;

Scope::Scope(Scope* parentScope) {
	parent = parentScope;
	id = counter++;
}

Scope::Scope(const Scope& other) {
	parent = other.parent;
	id = counter++;
}

Scope::~Scope() {
	for (auto& i : variables)
		delete i.second;	
	
	for (auto& i : functions)
		delete i.second;
}

void Scope::registerVariable(string name, Variable* variable) {
	variables[name] = variable;
}

void Scope::registerFunctions(string name, FunctionInterface* variable) {
	functions[name] = variable;
}

Variable* Scope::find(string name) {
	auto var = variables.find(name);

	if (var != variables.end())
		return var->second;

	if (parent != nullptr)
		return parent->find(name);

	std::cerr << "no such variable as : " << name << " in scope: " << id << ".\n";
	return nullptr;
}

bool Scope::contains(string name, bool stopPropagation) {
	if (variables.find(name) != variables.end())
		return true;
	else if (parent != nullptr)
		return  parent->contains(name);
	else
		return false;
}
