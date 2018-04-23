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

bool is_integer( VariableType _type );
bool is_floating( VariableType _type );

std::string type_to_string( VariableType _type );


enum class Operator : short
{
	TAG,
	PLUS,
	MINUS,
	MUL,
	DIV,
	MOD
};

std::string operator_to_string( Operator _operator );

bool is_only_integral_operator( Operator _operator );