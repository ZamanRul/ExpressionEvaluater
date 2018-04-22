#include "Const.h"

Const::Const( bool _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::BOOL;
	m_is_const = true;
}

Const::Const( const std::string& _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::STRING;
	m_is_const = true;
}

Const::Const( short _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::SINT;
	m_is_const = true;
}

Const::Const( unsigned short _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::USINT;
	m_is_const = true;
}

Const::Const( int _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::INT;
	m_is_const = true;
}

Const::Const( unsigned int _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::UINT;
	m_is_const = true;
}

Const::Const( long int _value ) :
	BaseExpr{}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::LINT;
	m_is_const = true;
}

Const::Const( unsigned long int _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::ULINT;
	m_is_const = true;
}

Const::Const( float _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::REAL;
	m_is_const = true;
}

Const::Const( double _value ) :
	BaseExpr {}
{
	m_value = std::make_shared< Var >( _value );
	m_type = VariableType::LREAL;
	m_is_const = true;
}

void Const::accept( IVisitorPtr _visitor )
{
	_visitor->visit( this );
}

std::string Const::to_string()
{
	if ( m_value == nullptr )
		return std::string { "UNDEFINED" };

	return m_value->to_string();
}

void Const::evaluate()
{
	// For Consts evaluation is redundant
}