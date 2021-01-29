#include "Expression.h"


using Scope = std::map<std::string, Variable>;

bool isDigit(const char character) {
	return (int)character >= 48 && (int)character <= 57;
}

bool isOperator(const char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

string Expression::toRPN() {
	string polish;
	std::stack<char> ops;
	string curr = "";

	for (const char& i : expr) {
		if (i == ' ' || i == '\t')
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