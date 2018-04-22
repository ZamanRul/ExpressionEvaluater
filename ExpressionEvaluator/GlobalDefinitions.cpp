#include "GlobalDefinitions.h"


VariableType get_variable_type( const std::type_info& _type_info )
{
	if ( _type_info == typeid( bool ) )
		return VariableType::BOOL;

	if ( _type_info == typeid( std::string ) )
		return VariableType::STRING;

	if ( _type_info == typeid( short int ) )
		return VariableType::SINT;

	if ( _type_info == typeid( unsigned short int ) )
		return VariableType::USINT;

	if ( _type_info == typeid( int ) )
		return VariableType::INT;

	if ( _type_info == typeid( unsigned int ) )
		return VariableType::UINT;

	if ( _type_info == typeid( long int ) )
		return VariableType::LINT;

	if ( _type_info == typeid( unsigned long int ) )
		return VariableType::ULINT;

	if ( _type_info == typeid( float ) )
		return VariableType::REAL;

	if ( _type_info == typeid( double ) )
		return VariableType::LREAL;

	return VariableType::UNDEFINED;
}


std::string type_to_string( VariableType _type )
{
	switch ( _type )
	{
	case VariableType::UNDEFINED:
		return std::string { "UNDEFINED" };

	case VariableType::BOOL:
		return std::string { "BOOL" };

	case VariableType::STRING:
		return std::string { "STRING" };

	case VariableType::SINT:
		return std::string { "SINT" };

	case VariableType::USINT:
		return std::string { "USINT" };

	case VariableType::INT:
		return std::string { "INT" };

	case VariableType::UINT:
		return std::string { "UINT" };

	case VariableType::LINT:
		return std::string { "LINT" };

	case VariableType::ULINT:
		return std::string { "ULINT" };

	case VariableType::REAL:
		return std::string { "REAL" };

	case VariableType::LREAL:
		return std::string { "LREAL" };

	default:
		return std::string { "UNDEFINED" };
	}
}


std::string operator_to_string( Operator _operator )
{
	switch ( _operator )
	{
		case Operator::TAG:
			return std::string { "TAG: " };

		case Operator::PLUS:
			return std::string { "+" };

		case Operator::MUL:
			return std::string { "*" };

		default:
			return std::string { "" };
	}
}