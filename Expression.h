#pragma once
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <vector>

#include "Variable.h"
#include "Scope.h"

using string = std::string;

class Expression{
	Scope* scope;
	string expr;
	VarType expectedType;

	string toRPN();
	void hydrateVariables();
	void defloat();


public:
	Expression(string expression, Scope* currentScope, VarType expectedType)
	:scope(currentScope), expectedType(expectedType) {
		setString(expression);
	};

	void setString(string expression);

	float evalLegacy();
	float eval();
};


bool isDigit(const char character);
bool isOperator(const char c);
bool isValidInVariableName(const char c);
bool isWhitespace(const char c);