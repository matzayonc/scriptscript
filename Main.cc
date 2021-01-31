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

			line = line.substr(0, line.find('//')) + '\n';
			//std::cout << "line: " << line << '\n';

			VarType declaredType = VarType::VOID;

			Expression expr("", &scope);

			size_t eqs = line.find('=');

			if (eqs == std::string::npos) {
				expr.setString(line);
				expr.eval();
				continue;
			}

			string word = "";

			expr.setString(line.substr(eqs + 1, std::string::npos));


			for (const char& i : line) {
				if (i == '=') break;

				if (!isWhitespace(i) && !isOperator(i)) {
					word += i;
					continue;
				}

				if (word.empty()) continue;

				if(declaredType == VarType::VOID){
					if (word == "num")
						declaredType = VarType::NUM;
					else continue;

					word = "";
					
				}
				else {
					scope.insert({ word, Variable(word) });
					scope[word].setValue(expr.eval());
				}

			}


		}
		file.close();
	}


	return 0;
}