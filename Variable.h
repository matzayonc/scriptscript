#pragma once

#include <string>

using string = std::string;


enum class VarType {
	VOID = 0,
	NUM
};


class Variable {
protected:
	string name = "undefined";
	VarType type = VarType::VOID;
	bool defined = false;


public:
	Variable() {
	}

	Variable(string name) : name(name) {
	}

	bool isType(VarType VariableType = VarType::VOID) {
		return VariableType == type;
	}

	string getName() {
		return name;
	}

	virtual string getAsString() = 0;
};


class NumericVariable : public Variable {
private:
	double value = 0;

	void removeNonCode();

public:
	NumericVariable(string name, int value) : Variable(name), value(value) {
		type = VarType::NUM;
	}

	string getAsString()  override {
		return std::to_string(value);
	}

	void setValue(double v) {
		value = v;
	};

};


template<class T>
Variable* VariableFactory(string name, VarType type, T value) {

	switch (type) {
	case VarType::NUM:
		return new NumericVariable(name, value);

	default:
		std::cerr << "not a valid type in variable factory for variable: " << name ;
	}

}