#pragma once

#include <string>

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
