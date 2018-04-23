#include "Var.h"
#include "ErrorHandling.h"

#include <type_traits>
#include <boost/lexical_cast.hpp>

#pragma warning(disable : 4146)

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
	using namespace boost;

	if ( m_type == VariableType::UNDEFINED )
		return std::string { "UNDEFINED" };

	if ( m_type == VariableType::STRING )
		return str( format { "\"%1%\"" }
			% boost::get< std::string >( m_value )
		);

	return boost::lexical_cast< std::string >( m_value );
}

Var Var::operator+()
{
	return oper( Operator::POS, *this );
}

Var Var::operator-()
{
	return oper( Operator::NEG, *this );
}

Var Var::operator+( const Var& _rhs )
{
	return oper( Operator::PLUS, *this, _rhs );
}

Var Var::operator-( const Var& _rhs )
{
	return oper( Operator::MINUS, *this, _rhs );
}

Var Var::operator*( const Var& _rhs )
{
	return oper( Operator::MUL, *this, _rhs );
}

Var Var::operator/( const Var& _rhs )
{
	return oper( Operator::DIV, *this, _rhs );
}

Var Var::operator%( const Var& _rhs )
{
	return oper( Operator::MOD, *this, _rhs );
}

template< typename T>
Var Var::unary_operations( Operator _operator, const T& _child )
{
	switch ( _operator )
	{
	case Operator::POS:
		return Var { +_child };

	case Operator::NEG:
		return Var { -_child };

	}

	throw OperationNSY { std::string { "Unknown unary operator" } };
}


template< typename T >
Var Var::arith_operations( Operator _operator, const T& _left, const T& _right )
{
	switch ( _operator )
	{
	case Operator::PLUS:
		return Var { _left + _right };

	case Operator::MINUS:
		return Var { _left - _right };

	case Operator::MUL:
		return Var { _left * _right };

	case Operator::DIV:
		return Var { _left / _right };
	}

	throw OperationNSY{ std::string { "Unknown arithmetic's operator" } };
}

template< typename T >
Var Var::arith_operations_only_int( Operator _operator, const T& _left, const T& _right )
{
	switch ( _operator )
	{
		case Operator::MOD:
			return Var { _left % _right };
	}

	throw OperationNSY{ std::string { "Unknown arithmetic's operator" } };
}

template< typename T >
Var Var::oper_internal( Operator _operator, const Var& _child )
{
	return unary_operations( _operator, get_as< T, T >( _child ) );
}

template< typename left_type, typename right_type >
auto Var::oper_internal( Operator _operator, const Var& _left, const Var& _right )
	-> typename std::enable_if< !std::is_floating_point< left_type >::value && !std::is_floating_point< right_type >::value, Var >::type
{
	using common_type = typename std::common_type< left_type, right_type >::type;

	if ( is_only_integral_operator( _operator ) )
		return arith_operations_only_int( _operator, get_as< common_type, left_type >( _left ), get_as< common_type, right_type >( _right ) );
	else
		return arith_operations( _operator, get_as< common_type, left_type >( _left ), get_as< common_type, right_type >( _right ) );
}

template< typename left_type, typename right_type >
auto Var::oper_internal( Operator _operator, const Var& _left, const Var& _right )
	-> typename std::enable_if< std::is_floating_point< left_type >::value || std::is_floating_point< right_type >::value, Var >::type
{
	using common_type = typename std::common_type< left_type, right_type >::type;

	return arith_operations( _operator, get_as< common_type, left_type >( _left ), get_as< common_type, right_type >( _right ) );
}

template< typename left_type >
Var Var::oper_right( Operator _operator, const Var& _left, const Var& _right )
{
	switch ( _right.get_type() )
	{
	case VariableType::BOOL:
		return oper_internal< left_type, bool >( _operator, _left, _right );
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

Var Var::oper( Operator _operator, const Var& _child )
{
	switch ( _child.get_type() )
	{
	case VariableType::BOOL:
		return oper_internal< bool >( _operator, _child );
	case VariableType::SINT:
		return oper_internal< short int >( _operator, _child );
	case VariableType::USINT:
		return oper_internal< unsigned short int >( _operator, _child );
	case VariableType::INT:
		return oper_internal< int >( _operator, _child );
	case VariableType::UINT:
		return oper_internal< unsigned int >( _operator, _child );
	case VariableType::LINT:
		return oper_internal< long int >( _operator, _child );
	case VariableType::ULINT:
		return oper_internal< unsigned long int >( _operator, _child );
	case VariableType::REAL:
		return oper_internal< float >( _operator, _child );
	case VariableType::LREAL:
		return oper_internal< double >( _operator, _child );
	}

	throw UnappropriateType{ type_to_string( _child.get_type() ) };
}

bool MathHelper::is_zero( VarPtr _ptr )
{
	if ( _ptr )
	{
		VariableType type = _ptr->get_type();
		
		switch ( type )
		{

		case VariableType::SINT:
			return _ptr->get_value< short int >() == 0;

		case VariableType::USINT:
			return _ptr->get_value< unsigned short int >() == 0;

		case VariableType::INT:
			return _ptr->get_value< int >() == 0;

		case VariableType::UINT:
			return _ptr->get_value< unsigned int >() == 0;

		case VariableType::LINT:
			return _ptr->get_value< long int >() == 0;

		case VariableType::ULINT:
			return _ptr->get_value< unsigned long int >() == 0;

		case VariableType::REAL:
			{
				const float epsilon_float = std::numeric_limits< float >::epsilon();
				return fabs( _ptr->get_value< float >() ) < epsilon_float;
			}

		case VariableType::LREAL:
			{
				const double epsilon_double = std::numeric_limits< double >::epsilon();
				return fabs( _ptr->get_value< double >() ) < epsilon_double;
			}
		}
	}

	return false;
}