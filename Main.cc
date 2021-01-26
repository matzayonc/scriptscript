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
public:
	//Variable() :name("undefined") {};
	Variable(string name) :name(name) {};
	Variable(const Variable& var) :name(var.getName()) {};
	string getName() const {
		return name;
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
			
			
			for (const char& i : line) {
				if (i == ' ' || i == '\t') {
					pause = true;

					if (declaredType != VarType::VOID) {

						scope.insert({ last, Variable(last) });
						std::cout << "ccc" << scope[last].getName();

						declaredType = VarType::VOID;
					}
					else if (last == "num")
					{
						declaredType = VarType::NUM;
					}

					last = "";
				}
				else if (i == '=')
					std::cout << "lhs: " << last << '\n';
				else
					last += i;

			}



		}
		file.close();
	}

	
	return 0;
}