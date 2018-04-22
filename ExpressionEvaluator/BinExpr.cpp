#include "BinExpr.h"
#include "ErrorHandling.h"

#include <boost/format.hpp>


BinExpr::BinExpr( Operator _operator, IExprPtr _left, IExprPtr _right ) :
	BaseExpr{},
	m_operator{ _operator },
	m_left{ _left },
	m_right{ _right }
{}

void BinExpr::accept( IVisitorPtr _visitor )
{
	if ( m_left )
		m_left->accept( _visitor );

	if ( m_right )
		m_right->accept( _visitor );

	_visitor->visit( shared_from_this() );
}

std::string BinExpr::to_string()
{
	using namespace boost;

	return str( format { "(%1%%2%%3%)" }
		% m_left->to_string()
		% operator_to_string( m_operator )
		% m_right->to_string()
	);
}

void BinExpr::evaluate()
{
	if ( m_is_const )
		return;

	if ( m_left->get_type() == VariableType::UNDEFINED || m_right->get_type() == VariableType::UNDEFINED )
		throw UnappropriateType{ std::string{ "UNDEFINED" } };

	Var result;

	switch ( m_operator )
	{
	case Operator::PLUS:
		result = evaluate_plus();
		break;

	default:
		throw OperationNSY { std::string{ "Unknown binary operator" } };
	}

	if ( result.get_type() != VariableType::UNDEFINED )
	{
		m_type = result.get_type();
		m_value = std::make_shared< Var >( result );

		if ( m_right->is_const() && m_left->is_const() )
			m_is_const = true;
	}
}

Var BinExpr::evaluate_plus()
{
	if ( m_operator != Operator::PLUS )
		throw OperationNSY { std::string{ "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();


	if ( ( left_type == VariableType::STRING && right_type != VariableType::STRING ) ||
		( left_type != VariableType::STRING && right_type == VariableType::STRING ) )
	{
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };
	}

	if ( left_type == VariableType::STRING && right_type == VariableType::STRING )
	{
		auto left_string = m_left->get_value()->get_value< std::string >();
		auto right_string = m_left->get_value()->get_value< std::string >();

		return Var { left_string.append( right_string ) };
	}

	if ( left_type == VariableType::BOOL || right_type == VariableType::BOOL )
		throw UnappropriateType { std::string { "BOOL" } };

	return *m_left->get_value() + *m_right->get_value();
}