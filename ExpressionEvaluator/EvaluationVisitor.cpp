#include "EvaluationVisitor.h"

#include <iostream>

EvaluationVisitor::EvaluationVisitor( bool _enable_logging ) :
	m_enable_logging { _enable_logging }
{}

void EvaluationVisitor::visit( Const* _ptr )
{
	LOG( "Evaluater: Proceeding const value: " << _ptr->to_string() << " (" << type_to_string( _ptr->get_type() ) << ")" );

	_ptr->evaluate();
}

void EvaluationVisitor::visit( UnExpr* _ptr )
{
	LOG( "Evaluater: Proceeding unary expression: " << _ptr->to_string() );

	_ptr->evaluate();

	LOG( "\tEvaluater: Result: " << _ptr->get_value()->to_string() << " (" << type_to_string( _ptr->get_type() ) << ")" );
}


void EvaluationVisitor::visit( BinExpr* _ptr )
{
	LOG( "Evaluater: Proceeding binary expression: " << _ptr->to_string() );

	_ptr->evaluate();

	LOG( "\tEvaluater: Result: " << _ptr->get_value()->to_string() << " (" << type_to_string( _ptr->get_type() ) << ")" );
}

void EvaluationVisitor::visit( TriExpr* _ptr )
{

}

void EvaluationVisitor::log()
{
	std::cout << m_stream.str();
	m_stream.str( std::string { "" }) ;
}