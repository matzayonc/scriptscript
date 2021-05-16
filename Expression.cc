#include "Expression.h"


bool isDigit(const char character) {
	return (int)character >= 48 && (int)character <= 57;
}

bool isOperator(const char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isValidInVariableName(const char c) {
	return !isWhitespace(c) && !isOperator(c) && c != '(' && c != ')' && c != ',' && c != '\\' ;
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

	for (auto i : expr)
		if (isOperator(i))
			return 0;


	return (float)stoi(expr);
}


float Expression::evalLegacy() { //REPLACEME!
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
	defloat();
}

void Expression::defloat() {
	string defloated = "";
	for (auto i : expr)
		if (i == '\n' || !isWhitespace(i))
			defloated += i;

	expr = defloated;
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

			if (i == ',' || i == ')') {
				args.push_back(Expression(arg, scope, VarType::NUM)); //FIXME: expected type should change based on function (I feel bad for whoever has to do it)
				arg = "";
			}

			if (i == ')') {
				argMode = false;

				if (name == "out") {
					std::cout << "out: ";
					for (Expression& e : args)
						std::cout << e.eval() << ", ";
						
					std::cout << "\b\b \n";

				}

				arg = "";
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

			std::cerr << "function :\"" << name << "\" does not exist";
		}
		else{
			if ((*scope).count(name) == 0)
				std::cerr << "word: " << name << " is not a variable(will be 0)\n";
			else
				hydrated += std::to_string(stoi((*scope)[name]->getAsString())); //FIXME: shouldnt always be int

			name = "";

			hydrated += i;
		}
	}
	//std::cout << expr <<  ", hydrated is: " << hydrated << '\n';
	expr = hydrated;
}
