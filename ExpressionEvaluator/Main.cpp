#include <iostream>

#include "TagManager.h"
#include "ExprFactory.h"
#include "Parser.h"

#include "EvaluationVisitor.h"

/*
	TODO:

	- refaktoryzacja visitors - wyrugowanie naked ptr

*/

int main()
{
	TagManager::get().add( {
		std::string { "::local::my_int" },
		VariableType::LREAL,
		69.9
	} );

	ConstPtr l { ExprFactory::create_const( 6.1f ) };
	ConstPtr r { ExprFactory::create_const( 666ul ) };

	BinExprPtr e { ExprFactory::create_binary( Operator::PLUS, l ,r ) };

	ConstPtr t { ExprFactory::create_const( std::string { "::local::my_int" } ) };
	UnExprPtr y { ExprFactory::create_unary( Operator::TAG, t ) };
	
	BinExprPtr z { ExprFactory::create_binary( Operator::PLUS, y , e ) };

	EvaluationVisitorPtr evaluater { std::make_shared< EvaluationVisitor >( true ) };

	z->accept( evaluater );

	ParserPtr parser { std::make_shared< Parser >() };

	std::string text { "20%8" };
	auto res = parser->parse( text );

	if ( res )
		res->accept( evaluater );

	return 0;
}