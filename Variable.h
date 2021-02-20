#pragma once

#include <string>

using string = std::string;


enum class VarType {
	VOID = 0,
	NUM
};


union VariableValue {
	float n;
	bool b;
};


class Var {
protected:
	string name;

public:
	Var() :name("undefined") {};
	Var(string name) :name(name) {};

	string getName() const {
		return name;
	}


	virtual void setValue(float val, VarType variableType) {};
	virtual float getValue() = 0;

	bool exists() {  
		return name != "undefined";
	}

};



template<class T>
class VariableBase: public Var {
protected:
	bool defined = false;
	VarType type = VarType::NUM;
	T value = NULL;

public:
	VariableBase(string name, T value, VarType type)
		:Var(name), value(value), type(type) {};
	VariableBase(const VariableBase& rhs)
		:Var(rhs.getName()){};



	bool isType(VarType t) const {
		return t == type;
	}

	void setValue(T val, VarType variableType) {
		type = variableType;
		value = val;
	}

	float getValue() override {
		return value;
	}

};




class Variable: public VariableBase<float> {

public:
	
	Variable(string name, float value, VarType type)
		: VariableBase<float>(name, value, type){};

	float getValue() override {
		return value;
	}
};
