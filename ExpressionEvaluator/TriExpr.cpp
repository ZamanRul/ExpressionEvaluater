#include "TriExpr.h"
#include "ErrorHandling.h"

#include <boost/format.hpp>

TriExpr::TriExpr( Operator _operator, IExprPtr _first, IExprPtr _second, IExprPtr _third ) :
	BaseExpr{},
	m_operator { _operator },
	m_first{ _first },
	m_second{ _second },
	m_third{ _third }
{}

void TriExpr::accept( IVisitorPtr _visitor )
{
	if ( m_first )
		m_first->accept( _visitor );

	if ( m_second )
		m_second->accept( _visitor );

	if ( m_third )
		m_third->accept( _visitor );

	_visitor->visit( this );
}

std::string TriExpr::to_string()
{
	using namespace boost;

	return str( format{ "%1%(%2%,%3%,%4%)" }
		% operator_to_string( m_operator )
		% m_first->to_string()
		% m_second->to_string()
		% m_third->to_string()
	);
}

void TriExpr::evaluate()
{
	if ( m_is_const )
		return;

	throw OperationNSY { std::string{ "Unknown triary operator during determining expression's type" } };
}