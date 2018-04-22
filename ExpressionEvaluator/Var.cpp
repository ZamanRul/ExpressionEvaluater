#include "Var.h"
#include "ErrorHandling.h"

#include <type_traits>
#include <boost/lexical_cast.hpp>

Var::Var() :
	m_type{ VariableType::UNDEFINED },
	m_value { 0 }
{}

Var::Var( bool _value ) :
	m_type{ VariableType::BOOL },
	m_value{ _value }
{}

Var::Var( const std::string& _value ) :
	m_type{ VariableType::STRING },
	m_value{ _value }
{}

Var::Var( short _value ) :
	m_type{ VariableType::SINT },
	m_value{ _value }
{}

Var::Var( unsigned short _value ) :
	m_type{ VariableType::USINT },
	m_value{ _value }
{}

Var::Var( int _value ) :
	m_type{ VariableType::INT },
	m_value{ _value }
{}

Var::Var( unsigned int _value ) :
	m_type{ VariableType::UINT },
	m_value{ _value }
{}

Var::Var( long int _value ) :
	m_type{ VariableType::LINT },
	m_value{ _value }
{}

Var::Var( unsigned long int _value ) :
	m_type{ VariableType::ULINT },
	m_value{ _value }
{}

Var::Var( float _value ) :
	m_type{ VariableType::REAL },
	m_value{ _value }
{}

Var::Var( double _value ) :
	m_type{ VariableType::LREAL },
	m_value{ _value }
{}

VariableType Var::get_type() const
{
	return m_type;
}

std::string Var::to_string()
{
	if ( m_type == VariableType::UNDEFINED )
		return std::string { "UNDEFINED" };

	return boost::lexical_cast< std::string >( m_value );
}

Var Var::operator+( const Var& _rhs )
{
	return oper( Operator::PLUS, *this, _rhs );
}

template< typename T >
Var Var::arith_operations( Operator _operator, const T& _left, const T& _right )
{
	switch ( _operator )
	{
	case Operator::PLUS:
		return Var { _left + _right };
	}

	throw OperationNSY{ std::string { "Unknown arithmetic's operator" } };
}

template< typename left_type, typename right_type >
Var Var::oper_internal( Operator _operator, const Var& _left, const Var& _right )
{
	using common_type = typename std::common_type< left_type, right_type>::type;

	return arith_operations( _operator, get_as< common_type, left_type >( _left ), get_as< common_type, right_type >( _right ) );
}

template< typename left_type >
Var Var::oper_right( Operator _operator, const Var& _left, const Var& _right )
{
	switch ( _right.get_type() )
	{
	case VariableType::BOOL:
		return oper_internal< left_type, bool >( _operator, _left, _right );
	//case VariableType::STRING:														// String should not be used in binary expressions except '+'
	//	return oper_internal< left_type, std::string >( _operator, _left, _right );
	case VariableType::SINT:
		return oper_internal< left_type, short int >( _operator, _left, _right );
	case VariableType::USINT:
		return oper_internal< left_type, unsigned short int >( _operator, _left, _right );
	case VariableType::INT:
		return oper_internal< left_type, int >( _operator, _left, _right );
	case VariableType::UINT:
		return oper_internal< left_type, unsigned int >( _operator, _left, _right );
	case VariableType::LINT:
		return oper_internal< left_type, long int >( _operator, _left, _right );
	case VariableType::ULINT:
		return oper_internal< left_type, unsigned long int >( _operator, _left, _right );
	case VariableType::REAL:
		return oper_internal< left_type, float >( _operator, _left, _right );
	case VariableType::LREAL:
		return oper_internal< left_type, double >( _operator, _left, _right );
	}

	throw UnappropriateType{ type_to_string( _right.get_type() ) };
}

Var Var::oper( Operator _operator, const Var& _left, const Var& _right )
{
	switch ( _left.get_type() )
	{
	case VariableType::BOOL:
		return oper_right< bool >( _operator, _left, _right );
	//case VariableType::STRING:														// String should not be used in binary expressions except '+'
	//	return oper_right< std::string >( _operator, _left, _right );
	case VariableType::SINT:
		return oper_right< short int >( _operator, _left, _right );
	case VariableType::USINT:
		return oper_right< unsigned short int >( _operator, _left, _right );
	case VariableType::INT:
		return oper_right< int >( _operator, _left, _right );
	case VariableType::UINT:
		return oper_right< unsigned int >( _operator, _left, _right );
	case VariableType::LINT:
		return oper_right< long int >( _operator, _left, _right );
	case VariableType::ULINT:
		return oper_right< unsigned long int >( _operator, _left, _right );
	case VariableType::REAL:
		return oper_right< float >( _operator, _left, _right );
	case VariableType::LREAL:
		return oper_right< double >( _operator, _left, _right );
	}

	throw UnappropriateType { type_to_string( _left.get_type() ) };
}