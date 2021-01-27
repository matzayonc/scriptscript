#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <stack>


using string = std::string;

enum class VarType {
	VOID = 0,
	NUM
};

class Variable {
	string name;
	VarType type = VarType::NUM;
	float value = NULL;

public:
	Variable() :name("undefined") {};
	Variable(string name) :name(name) {};
	Variable(const Variable& var) :name(var.getName()) {};
	string getName() const {
		return name;
	}
	bool isType(VarType t) const {
		return t == type;
	}
	void setValue(const float val) {
		value = val;
	}
	float getValue(bool skipValidation = false) {
		return value;
	}
	bool exists() {
		return name != "undefined";
	}
};


using Scope = std::map<std::string, Variable>;

bool isDigit(const char character) {
	return (int)character >= 48 && (int)character <= 57;
}

bool isOperator(const char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

string toRPN(string expr) {
	string polish;
	std::stack<char> ops;
	string curr = "";

	for (const char& i : expr) {
		if (i == ' ' || i == '\t')
			continue;

		if (isDigit(i)) {
			curr += i;
			continue;
		}

		polish += curr + ' ';
		curr = "";

		if (!ops.empty() && ops.top()) {
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


float eval(string expr) {
	float first, second;
	std::stack<float> nums;
	string curr = "";

	std::cout << "\nRPN: '" << toRPN(expr) << '\n';

	for (auto i : toRPN(expr)) {
		if (i == ' ' || i == '\t') {
			if(curr != "")
				nums.push(stoi(curr, nullptr));
			curr = "";
			continue;
		}
		else if (isDigit(i)) {
			curr += i;
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


	return nums.top();
}


int main() {

	std::cout << "result: " << eval("1");

	Scope scope;
	std::ifstream file("./script.ss");
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
								rhs += std::to_string(scope[last].getValue());
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
								std::cout << rhs;
								lhs->setValue(eval(rhs));
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
					std::cout << "lhs: " << last << '\n';
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