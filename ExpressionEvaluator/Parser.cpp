#include "Parser.h"

IExprPtr Parser::parse( std::string& _text )
{
	IExprPtr ast_tree;
	ScriptGrammar < std::string::iterator, ascii::space_type > script_grammar { true };

	auto it = _text.begin();
	if ( qi::phrase_parse( it, _text.end(), script_grammar, ascii::space, ast_tree ) )
	{
		if ( it == _text.end() )
			return ast_tree;
		else
			return nullptr;
	}
	else
		return nullptr;
}