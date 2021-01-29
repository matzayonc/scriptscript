#pragma once
#include <iostream>
#include <string>
#include <map>
#include <stack>

#include "Variable.h"

using string = std::string;
using Scope = std::map<std::string, Variable>;


class Expression{
	string expr;
	Scope scope;

	string toRPN();
	void hydrateVariables();

public:
	Expression(string expression, Scope& currentScope) : expr(expression), scope(currentScope) {};
	void setString(string expression);
	float eval();
};


bool isDigit(const char character);
bool isOperator(const char c);
bool isValidInVariableName(const char c);
bool isWhitespace(const char c);