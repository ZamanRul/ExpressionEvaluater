#include "UnExpr.h"
#include "ErrorHandling.h"
#include "TagManager.h"

#include <boost/format.hpp>

UnExpr::UnExpr( Operator _operator, IExprPtr _child ) :
	BaseExpr{},
	m_operator{ _operator },
	m_child{ _child }
{}

void UnExpr::accept( IVisitorPtr _visitor )
{
	if ( m_child )
		m_child->accept( _visitor );

	_visitor->visit( shared_from_this() );
}

std::string UnExpr::to_string()
{
	using namespace boost;

	return str( format { "(%1%%2%)" } 
				% operator_to_string( m_operator )
				% m_child->to_string()
	);
}

void UnExpr::evaluate()
{
	if ( m_is_const )
		return;

	if ( m_child->get_type() == VariableType::UNDEFINED )
		throw UnappropriateType{ std::string{ "UNDEFINED" } };

	Var result;

	switch ( m_operator )
	{
	case Operator::TAG:
		result = evaluate_tag();
		break;

	default:
		throw OperationNSY { std::string{ "Unknown unary operator" } };
	}

	if ( result.get_type() != VariableType::UNDEFINED )
	{
		m_type = result.get_type();
		m_value = std::make_shared< Var >( result );

		if ( m_child->is_const() )
			m_is_const = true;
	}
}


Var UnExpr::evaluate_tag()
{
	if ( m_operator != Operator::TAG )
		throw OperationNSY { std::string{ "Operator mismatch" } };

	if ( m_child->get_type() != VariableType::STRING )
		throw UnappropriateType { std::string{ "STRING" }, type_to_string( m_child->get_type() ) };

	std::string tag_name{ m_child->get_value()->get_value< std::string >() };

	if ( !TagManager::get().tag_exists( tag_name ) )
		throw UnknownTag { tag_name };

	switch ( TagManager::get().get_tag_type( tag_name ) )
	{
	case VariableType::BOOL:
		return Var { boost::get< bool >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::STRING:
		return Var { boost::get< std::string >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::SINT:
		return Var { boost::get< short int >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::USINT:
		return Var { boost::get< unsigned short int >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::INT:
		return Var { boost::get< int >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::UINT:
		return Var { boost::get< unsigned int >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::LINT:
		return Var { boost::get< long int >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::ULINT:
		return Var { boost::get< unsigned long int >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::REAL:
		return Var { boost::get< float >( TagManager::get().get_tag_value( tag_name ) ) };

	case VariableType::LREAL:
		return Var { boost::get< double >( TagManager::get().get_tag_value( tag_name ) ) };

	default:
		throw UnappropriateType { std::string{ "UNDEFINED" } };
	}
}