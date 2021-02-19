#include "Function.h"


string Function::getName() const{
	return name;
}

bool Function::exists() const{
	return name != "undefined";
}

void Function::removeComments() {
	size_t index = 0;

	while ((index = code.find('/', index)) != std::string::npos)
		if (code[index + 1] == '/')
			code.erase(index, code.find('\n', index) - index);
}

void Function::execute() {
	removeComments();

	for (size_t end, start = 0; start != string::npos;) {
		end = code.find_first_of(";\n", start);
		string line = code.substr(start, end-start);
		start = end == string::npos ? string::npos : end + 1;



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

			if (declaredType == VarType::VOID) {
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



		//std::cout << line << '\n';
	}

	
}
