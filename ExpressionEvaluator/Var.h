#pragma once

#include "GlobalDefinitions.h"

#include <memory>
#include <string>

#include <boost\variant.hpp>


class Var
{
public:

	using pointer_type = std::shared_ptr< Var >;

	using data_type = boost::variant<
		bool,
		std::string,
		short,
		unsigned short,
		int,
		unsigned int, 
		long int, 
		unsigned long int, 
		float,
		double	
	>;


public:

	Var();
	Var( bool _value );
	Var( const std::string& _value );
	Var( short _value );
	Var( unsigned short _value );
	Var( int _value );
	Var( unsigned int _value );
	Var( long int _value );
	Var( unsigned long int _value );
	Var( float _value );
	Var( double _value );

	template< class T >
	T get_value() const
	{
		return boost::get< T >( m_value );
	}

	VariableType get_type() const;
		
	std::string to_string( bool _quotation_marks = true );

	Var operator+();
	Var operator-();
	Var operator+( const Var& _rhs );
	Var operator-( const Var& _rhs );
	Var operator*( const Var& _rhs );
	Var operator/( const Var& _rhs );
	Var operator%( const Var& _rhs );


private:

	Var oper( Operator _operator, const Var& _child );

	template< typename T >
	Var oper_internal( Operator _operator, const Var& _child );

	template< typename left_type, typename right_type >
	auto oper_internal( Operator _operator, const Var& _left, const Var& _right )
		-> typename std::enable_if< !std::is_floating_point< left_type >::value && !std::is_floating_point< right_type >::value, Var >::type;

	template< typename left_type, typename right_type >
	auto oper_internal( Operator _operator, const Var& _left, const Var& _right )
		-> typename std::enable_if< std::is_floating_point< left_type >::value || std::is_floating_point< right_type >::value, Var >::type;

	template< typename left_type >
	Var oper_right( Operator _operator, const Var& _left, const Var& _right );

	Var oper( Operator _operator, const Var& _left, const Var& _right );

	template< typename T>
	Var unary_operations( Operator _operator, const T& _child );

	template< typename T >
	Var arith_operations( Operator _operator, const T& _left, const T& _right );

	template< typename T >
	Var arith_operations_only_int( Operator _operator, const T& _left, const T& _right );

private:

	VariableType m_type;

	data_type m_value;
};

template< typename Target, typename Source >
Target get_as( const Var& _object )
{
	return static_cast< Target >( _object.get_value< Source >() );
}

using VarPtr = Var::pointer_type;


class MathHelper
{
public:

	static bool is_zero( VarPtr _ptr );
};
