#pragma once
#include <map>
#include <string>
#include "Variable.h"

typedef std::map<std::string, Variable*> Scope;
typedef std::map<std::string, FunctionInterface*> FunctionScope;