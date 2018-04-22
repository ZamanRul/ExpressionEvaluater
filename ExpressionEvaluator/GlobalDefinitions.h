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

std::string type_to_string( VariableType _type );


enum class Operator : short
{
	TAG,
	PLUS,
	MUL
};

std::string operator_to_string( Operator _operator );