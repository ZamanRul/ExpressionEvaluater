#pragma once

#include "Const.h"
#include "UnExpr.h"
#include "BinExpr.h"
#include "TriExpr.h"

class ExprFactory
{
public:

	template< typename T >
	static ConstPtr create_const( const T& _value ) 
	{
		return std::make_shared< Const >( _value );
	}

	static UnExprPtr create_unary( Operator _operator, IExprPtr _child )
	{
		return std::make_shared< UnExpr >( _operator, _child );
	}

	static BinExprPtr create_binary( Operator _operator, IExprPtr _left, IExprPtr _right )
	{
		return std::make_shared< BinExpr >( _operator, _left, _right );
	}

	static TriExprPtr create_triary( Operator _operator, IExprPtr _first, IExprPtr _second, IExprPtr _third )
	{
		return std::make_shared< TriExpr >(_operator, _first, _second, _third );
	}
};