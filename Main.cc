#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <stack>

#include "Expression.h"
#include "Variable.h"
#include "Function.h"
#include "Scope.h"


using string = std::string;


string readFile(string filename) {
	std::ifstream file("./script.ds");
	string line = "";
	string code = "";

	if (file.is_open()) {
		while (getline(file, line))
			code += line + '\n';
		file.close();
	}

	return code;
}

int main() {

	Scope scope;
	Function main(scope, "a", readFile("script.ds"));
	main.execute();

	return 0;
}