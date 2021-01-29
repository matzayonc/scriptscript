#pragma once
#include <iostream>
#include <string>
#include <map>
#include <stack>

#include "Variable.h"

using string = std::string;


class Expression{
	string expr;

	string toRPN();

public:
	Expression(string expression) : expr(expression) {};
	float eval();
};


bool isDigit(const char character);

bool isOperator(const char c);