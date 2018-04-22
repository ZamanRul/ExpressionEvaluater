#include "Parser.h"

IExprPtr Parser::parse( std::string& _text )
{
	IExprPtr ast_tree;
	ScriptGrammar < std::string::iterator, ascii::space_type > script_grammar;

	if ( qi::phrase_parse( _text.begin(), _text.end(), script_grammar, ascii::space, ast_tree ) )
		return ast_tree;
	else
		return nullptr;
}