#pragma once

#include <string>

using string = std::string;


enum class VarType {
	VOID = 0,
	NUM
};


class Variable {
public:
	Variable() {};

	virtual void setValue(float val, VarType variableType) = 0;
	virtual float getValue() const = 0;

	virtual string getName() const = 0;

};


class VariableName: virtual public Variable {
protected:
	string name;

public:
	VariableName() :name("undefined") {};
	VariableName(string name) :name(name) {};

	string getName() const {
		return name;
	}


	bool exists() {  
		return name != "undefined";
	}

};



template<class T>
class VariableValue: virtual public Variable {
protected:
	bool defined = false;
	VarType type = VarType::NUM;
	T value = NULL;

public:
	VariableValue(T value, VarType type)
		:value(value), type(type) {};
	VariableValue(const VariableValue& rhs)
		:value(rhs.getValue()), type(type) {};



	bool isType(VarType t) const {
		return t == type;
	}

	void setValue(T val, VarType variableType) {
		type = variableType;
		value = val;
	}

	T getValue() const {
		return value;
	}

};




class NumericVariable : public VariableName, public VariableValue<float> {

public:
	
	NumericVariable(string name, float value, VarType type)
		: VariableName(name), VariableValue<float>(value, type){};

	float getValue() const override {
		return value;
	}

	string getName() const override {
		return name;
	}

	void setValue(float val, VarType variableType) override {
		type = variableType;
		value = val;
	}
};
