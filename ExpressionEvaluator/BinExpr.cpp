#include "BinExpr.h"
#include "ErrorHandling.h"

#include <boost/format.hpp>


BinExpr::BinExpr( Operator _operator, IExprPtr _left, IExprPtr _right ) :
	BaseExpr {},
	m_operator { _operator },
	m_left { _left },
	m_right { _right }
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
	case Operator::OR:
		result = evaluate_or();
		break;
	
	case Operator::AND:
		result = evaluate_and();
		break;

	case Operator::EQ:
		result = evaluate_equal();
		break;

	case Operator::NEQ:
		result = evaluate_not_equal();
		break;

	case Operator::LESS:
		result = evaluate_less();
		break;

	case Operator::LESS_EQ:
		result = evaluate_less_equal();
		break;

	case Operator::GREATER:
		result = evaluate_greater();
		break;

	case Operator::GREATER_EQ:
		result = evaluate_greater_equal();
		break;

	case Operator::PLUS:
		result = evaluate_plus();
		break;

	case Operator::MINUS:
		result = evaluate_minus();
		break;

	case Operator::MUL:
		result = evaluate_mul();
		break;

	case Operator::DIV:
		result = evaluate_div();
		break;

	case Operator::MOD:
		result = evaluate_modulo();
		break;

	default:
		throw OperationNSY { std::string { "Unknown binary operator" } };
	}

	if ( result.get_type() != VariableType::UNDEFINED )
	{
		m_type = result.get_type();
		m_value = std::make_shared< Var >( result );

		if ( m_right->is_const() && m_left->is_const() )
			m_is_const = true;
	}
}

Var BinExpr::evaluate_and()
{
	if ( m_operator != Operator::AND )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();
	
	if ( is_string( left_type ) || is_string( right_type ) )
		throw UnappropriateType { std::string { "STRING" } };

	return *m_left->get_value() && *m_right->get_value();
}

Var BinExpr::evaluate_or()
{
	if ( m_operator != Operator::OR )
		throw OperationNSY{ std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) || is_string( right_type ) )
		throw UnappropriateType { std::string { "STRING" } };

	return *m_left->get_value() || *m_right->get_value();
}

Var BinExpr::evaluate_equal()
{
	if ( m_operator != Operator::EQ )
		throw OperationNSY { std::string{ "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) && is_string( right_type ) )
	{
		std::string left_string = get_as< std::string, std::string >( *m_left->get_value() );
		std::string right_string = get_as< std::string, std::string >( *m_right->get_value() );

		return Var { left_string == right_string };
	}

	if ( is_string( left_type ) || is_string( right_type ) )
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };

	return *m_left->get_value() == *m_right->get_value();
}

Var BinExpr::evaluate_not_equal()
{
	if ( m_operator != Operator::NEQ )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) && is_string( right_type ) )
	{
		std::string left_string = get_as< std::string, std::string >( *m_left->get_value() );
		std::string right_string = get_as< std::string, std::string >( *m_right->get_value() );

		return Var { left_string != right_string };
	}

	if ( is_string( left_type ) || is_string( right_type ) )
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };

	return *m_left->get_value() != *m_right->get_value();
}

Var BinExpr::evaluate_less()
{
	if ( m_operator != Operator::LESS )
		throw OperationNSY { std::string{ "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) && is_string( right_type ) )
	{
		std::string left_string = get_as< std::string, std::string >( *m_left->get_value() );
		std::string right_string = get_as< std::string, std::string >( *m_right->get_value() );

		return Var { left_string < right_string };
	}

	if ( is_string( left_type ) || is_string( right_type ) )
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };

	return *m_left->get_value() < *m_right->get_value();
}

Var BinExpr::evaluate_less_equal()
{
	if ( m_operator != Operator::LESS_EQ )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) && is_string( right_type ) )
	{
		std::string left_string = get_as< std::string, std::string >( *m_left->get_value() );
		std::string right_string = get_as< std::string, std::string >( *m_right->get_value() );

		return Var { left_string <= right_string };
	}

	if ( is_string( left_type ) || is_string( right_type ) )
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };

	return *m_left->get_value() <= *m_right->get_value();
}

Var BinExpr::evaluate_greater()
{
	if ( m_operator != Operator::GREATER )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) && is_string( right_type ) )
	{
		std::string left_string = get_as< std::string, std::string >( *m_left->get_value() );
		std::string right_string = get_as< std::string, std::string >( *m_right->get_value() );

		return Var{  left_string > right_string };
	}

	if ( is_string( left_type) || is_string( right_type ) )
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };

	return *m_left->get_value() > *m_right->get_value();
}

Var BinExpr::evaluate_greater_equal()
{
	if ( m_operator != Operator::GREATER_EQ )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_string( left_type ) && is_string( right_type ) )
	{
		std::string left_string = get_as< std::string, std::string >( *m_left->get_value() );
		std::string right_string = get_as< std::string, std::string >( *m_right->get_value() );

		return Var { left_string >= right_string };
	}

	if ( is_string( left_type ) || is_string( right_type ) )
		throw TypeMismatch { type_to_string( left_type ), type_to_string( right_type ) };

	return *m_left->get_value() >= *m_right->get_value();
}

Var BinExpr::evaluate_plus()
{
	if ( m_operator != Operator::PLUS )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( is_boolean( left_type ) || is_boolean( right_type ) )
		throw UnappropriateType { std::string { "BOOL" } };

	if ( is_string( left_type ) || is_string( right_type ) )
	{
		std::string left_string = m_left->get_value()->to_string( false );
		std::string right_string = m_right->get_value()->to_string( false );

		return Var { left_string.append( right_string ) };
	}
	
	return *m_left->get_value() + *m_right->get_value();
}

Var BinExpr::evaluate_minus()
{
	if ( m_operator != Operator::MINUS )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();


	if ( left_type == VariableType::STRING || right_type == VariableType::STRING )
		throw UnappropriateType { std::string { "STRING" } };

	if ( left_type == VariableType::BOOL || right_type == VariableType::BOOL )
		throw UnappropriateType { std::string { "BOOL" } };

	return *m_left->get_value() - *m_right->get_value();
}

Var BinExpr::evaluate_mul()
{
	if ( m_operator != Operator::MUL )
		throw OperationNSY { std::string{ "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();
	
	if ( left_type == VariableType::BOOL || right_type == VariableType::BOOL )
		throw UnappropriateType { std::string { "BOOL" } };

	if ( left_type == VariableType::STRING || right_type == VariableType::STRING )
		throw UnappropriateType { std::string { "STRING" } };

	return ( *m_left->get_value() ) * ( *m_right->get_value() );
}

Var BinExpr::evaluate_div()
{
	if ( m_operator != Operator::DIV )
		throw OperationNSY { std::string{ "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( left_type == VariableType::BOOL || right_type == VariableType::BOOL )
		throw UnappropriateType { std::string { "BOOL" } };

	if ( left_type == VariableType::STRING || right_type == VariableType::STRING )
		throw UnappropriateType { std::string { "STRING" } };
	
	if ( MathHelper::is_zero( m_right->get_value() ) )
		throw DivisionByZero {};

	return ( *m_left->get_value() ) / ( *m_right->get_value() );
}


Var BinExpr::evaluate_modulo()
{
	if ( m_operator != Operator::MOD )
		throw OperationNSY { std::string { "Operator mismatch" } };

	VariableType left_type = m_left->get_type();
	VariableType right_type = m_right->get_type();

	if ( !is_integer( left_type ) || !is_integer( right_type ) )
		throw ModuloBadArguments { type_to_string( left_type ), type_to_string( right_type ) };

	if ( MathHelper::is_zero( m_right->get_value() ) )
		throw DivisionByZero {};

	return ( *m_left->get_value() ) % ( *m_right->get_value() );
}