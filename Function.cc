#include "Function.h"


string FunctionInterface::getName() const{
	return name;
}

bool FunctionInterface::exists() const{
	return name != "undefined";
}

void Function::removeNonCode() {
	size_t index = 0;

	while ((index = code.find_first_of("/#", index)) != std::string::npos)
		if (code[index] == '#' || code[index + 1] == '/')
			code.erase(index, code.find('\n', index) - index);
		else if (code[index + 1] == '*')
			while (true) {
				size_t end = code.find('/', index + 2);
				if (end == std::string::npos) {
					std::cerr << "couldn't find end of multiline comment, that started at position: " << index << ".\n";
					throw;
				}

				if (code[end - 1] == '*') {
					code.erase(index, end - index + 1);
					break;
				}

			}
		else index++;

	index = 1;
	while ((index = code.find('\n', index+1)) != std::string::npos)
		while (isWhitespace(code[index - 1]))
			code.erase(code.begin()+index-1);
}


void Function::execute(const std::vector<Variable*> args) const {

	for (size_t end, start = 0; start != string::npos;) {
		end = code.find_first_of(";\n", start);
		string line = code.substr(start, end-start);
		start = end == string::npos ? string::npos : end + 1;


		VarType declaredType = VarType::VOID;

		size_t eqs = line.find('=');

		if (eqs == std::string::npos) {
			Expression expr(line, scope, VarType::VOID);
			expr.eval();
			continue;
		}

		string word = "";


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
				else if (scope->contains(word)) {
					std::cout << scope->find(word)->getName() << '\n';

				}
				else
					std::cerr << "err: " << word << " is not defined\n";

				word = "";

			}
			else {
				Expression expr("", scope, VarType::NUM);
				expr.setString(line.substr(eqs + 1, std::string::npos));

				scope->registerVariable(word, VariableFactory(word, VarType::NUM, expr.eval()));
				//(*scope)[word].setValue(expr.eval(), VarType::NUM);
			}

		}



		//std::cout << line << '\n';
	}

	
}
