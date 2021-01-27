#include <iostream>
#include <fstream>
#include <string>
#include <map>



using string = std::string;

enum class VarType {
	VOID = 0,
	NUM
};

class Variable {
	string name;
	VarType type = VarType::NUM;
	float value;

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
	float getValue() {
		return value;
	}
};


using Scope = std::map<std::string, Variable>;


int main() {

	Scope scope;

	std::ifstream file("./script.ss");

	string line = "";
	

	if (file.is_open()) {
		while (getline(file, line)) {


			VarType declaredType = VarType::VOID;
			string last = "";
			bool pause = true;
			Variable* lhs = nullptr;

			bool assigning = false;

			bool printing = false;


			
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
					if(printing)
						std::cout << "out: " << scope[last].getValue() << '\n';

				}
				else if (i == ' ' || i == '\t') {
					pause = true;

					if (last.size()) {
						if (assigning && lhs->isType(VarType::NUM)) {
							lhs->setValue(stoi(last, nullptr));
							assigning = false;
						}
						if (declaredType != VarType::VOID) {

							scope.insert({ last, Variable(last) });
							std::cout << "ccc" << scope[last].getName() << '\n';

							declaredType = VarType::VOID;
						}
						else if (last == "num")
						{
							declaredType = VarType::NUM;
							last = "";
						}
					}
	

				}
				else if (i == '=') {
					std::cout << "lhs: " << last << '\n';
					lhs = &(scope[last]);
					assigning = true;
					last = "";
				}
				else
					last += i;

			}



		}
		file.close();
	}

	
	return 0;
}