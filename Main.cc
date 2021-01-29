#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <stack>

#include "Expression.h"
#include "Variable.h"


using string = std::string;
using Scope = std::map<std::string, Variable>;


int main() {

	Scope scope;
	std::ifstream file("./script.ds");
	string line = "";


	if (file.is_open()) {
		while (getline(file, line)) {

			line += '\n';

			VarType declaredType = VarType::VOID;
			string last = "";
			bool pause = true;

			bool assigning = false;
			VarType assignmentType = VarType::NUM;
			Variable* lhs = nullptr;
			string rhs = "";


			bool printing = false;
			bool prevIsForwardSlash = false;


			Expression expr("", scope);

			size_t eqs = line.find('=');
			if (eqs != std::string::npos)
				expr.setString(line.substr(eqs + 1, std::string::npos));
			else
				expr.setString(line);

			
			for (const char& i : line) {
				if (i == '(') {
					if (last == "out") {
						printing = true;
						last = "";
					}
					else
						std::cerr << "cannot call" << last << '\n';
				}
				else if (i == ')') {
					if (printing)
						std::cout << "out: " << scope[last].getValue() << '\n';

				}
				else if (i == ' ' || i == '\t' || i == '\n') {
					pause = true;

					if (last.size()) {
						if (assigning && assignmentType == VarType::NUM) {
							if (isDigit(last[0]))
								rhs += last;
							else if (scope[last].exists())
								rhs += std::to_string((int)scope[last].getValue());
							else if (isOperator(last[0]))
								rhs += last;
							else
								std::cerr << "word: \"" << last << "\" is not a number nor a variable\n";

							last = "";
						}
					}


					if (i == '\n') {
						if (assigning && lhs && lhs->isType(VarType::NUM)) {
							if (rhs.size()) {
								//std::cout << rhs;
								lhs->setValue(expr.eval());
								std::cout << expr.eval();
							}
							else
								std::cerr << "word: rhs\"" << rhs << "\" is not a number nor a variable\n";

							assigning = false;
						}
					}

					

					if (declaredType != VarType::VOID) {

						scope.insert({ last, Variable(last) });

						declaredType = VarType::VOID;
					}
					else if (last == "num")
					{
						declaredType = VarType::NUM;
						last = "";
					}
				}
				else if (i == '=') {
					//std::cout << "lhs: " << last << '\n';
					lhs = &(scope[last]);
					assigning = true;
					last = "";
				}
				else if (i == '/') {
					if (prevIsForwardSlash)
						break;
					else
						prevIsForwardSlash = true;
				}
				else
					last += i;

			}



		}
		file.close();
	}

	return 0;
}