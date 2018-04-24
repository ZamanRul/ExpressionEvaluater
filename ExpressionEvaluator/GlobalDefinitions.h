#pragma once

#include <string>

enum class VariableType : short int
{
	UNDEFINED,
	BOOL,
	STRING,
	SINT,
	USINT,
	INT,
	UINT,
	LINT,
	ULINT,
	REAL,
	LREAL
};

VariableType get_variable_type( const std::type_info& _type_info );

bool is_boolean( VariableType _type );
bool is_string( VariableType _type );

bool is_integer( VariableType _type );
bool is_floating( VariableType _type );

std::string type_to_string( VariableType _type );


enum class Operator : short
{
	TAG,
	NOT,
	OR,
	AND,
	EQ,
	NEQ,
	LESS,
	LESS_EQ,
	GREATER,
	GREATER_EQ,
	POS,
	NEG,
	PLUS,
	MINUS,
	MUL,
	DIV,
	MOD
};

std::string operator_to_string( Operator _operator );

bool is_boolean_operator( Operator _operator );

bool is_only_integral_arithmetic_operator( Operator _operator );