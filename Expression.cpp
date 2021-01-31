#include "Expression.h"


using Scope = std::map<std::string, Variable>;

bool isDigit(const char character) {
	return (int)character >= 48 && (int)character <= 57;
}

bool isOperator(const char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isValidInVariableName(const char c) {
	return !isWhitespace(c) && !isOperator(c) && c != '(' && c != ')' && c != '\\' ;
}

bool isWhitespace(const char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

string Expression::toRPN() {
	string polish;
	std::stack<char> ops;
	string curr = "";

	for (const char& i : expr) {
		if (isWhitespace(i))
			continue;
		else if (isDigit(i)) {
			curr += i;
			continue;
		}
		else if (!isOperator(i)) {
			std::cerr << "idk wtf is: " << i << '\n';
			continue;
		}
		polish += curr + ' ';
		curr = "";

		while (!ops.empty()) {
			if (i == '*' || i == '/')
				if (ops.top() == '+' || ops.top() == '-')
					break;

			polish += ops.top();
			polish += ' ';
			ops.pop();
		}
		ops.push(i);
	}

	polish += curr + ' ';

	while (!ops.empty()) {
		polish += ops.top();
		polish += ' ';
		ops.pop();
	}

	return polish;
}

float Expression::eval() {
	if (expr.empty()) return 0;

	hydrateVariables();

	float first, second;
	std::stack<float> nums;
	string curr = "";


	for (auto i : toRPN()) {
		if (i == ' ' || i == '\t') {
			if (curr != "")
				nums.push(stoi(curr, nullptr));
			curr = "";
			continue;
		}
		else if (isDigit(i)) {
			curr += i;
			continue;
		}

		if (nums.size() < 2) {
			std::cerr << "invalid expression: not enought numbers\n";
			continue;
		}

		second = nums.top();
		nums.pop();
		first = nums.top();
		nums.pop();

		if (i == '+')
			first += second;
		else if (i == '-')
			first -= second;
		else if (i == '*')
			first *= second;
		else if (i == '/')
			first /= second;
		else {
			std::cerr << "what is: " << i << "?\n";
			break;
		}

		nums.push(first);
	}
	if (nums.size() > 1)
		std::cerr << "numbers left in stack";
	if (nums.empty())
		return 0;

	return nums.top();
}

void Expression::setString(string expression) {
	expr = expression;
}


void Expression::hydrateVariables() {

	string name = "";
	string hydrated = "";

	std::vector<Expression> args;
	bool argMode = false;
	string arg = "";

	for (const char& i : expr + ' ') {
		if (argMode) {
			if (isWhitespace(i)) continue;

			if (i == ')' || i == ',') {
				args.push_back(Expression(arg, scope));
				arg = "";
			}

			if (i == ')') {
				argMode = false;

				if (name == "out")
					std::cout << "out: " << args[0].eval() << '\n';

				name = "";
				args.clear();
			}
			else arg += i;
		}
		else if (name.empty()){
			if (!isDigit(i) && isValidInVariableName(i))
				name += i;
			else
				hydrated += i;
		}
		else if (isValidInVariableName(i))
			name += i;
		else if (i == '(') {
			argMode = true;

			if(name == "out")
				continue; // functions
		}
		else{
			if (!(*scope)[name].exists())
				std::cerr << "word: " << name << " is not a variable(will be 0)\n";

			hydrated += std::to_string((int)(*scope)[name].getValue()); //FIXME: shouldnt always be int

			name = "";

			hydrated += i;
		}
	}

	expr = hydrated;
}
