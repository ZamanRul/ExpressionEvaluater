#include <iostream>

#include "ErrorHandling.h"
#include "TagManager.h"
#include "ExprFactory.h"
#include "Parser.h"

#include "EvaluationVisitor.h"

int main()
{
	TagManager::get().add( {
		std::string { "::local::my_int" },
		VariableType::LREAL,
		69.9
	} );
		
	EvaluationVisitorPtr evaluater { std::make_shared< EvaluationVisitor >( true ) };
	ParserPtr parser { std::make_shared< Parser >() };

	std::string line;

	while ( std::getline( std::cin, line ) )
	{
		try
		{
			if ( line.empty() || line[ 0 ] == 'q' || line[ 0 ] == 'Q' )
				break;

			auto res = parser->parse( line );

			if ( res )
				res->accept( evaluater );
			else
				std::cout << "Unable to parse given line: " << line << std::endl;

		}
		catch ( const EEException& _exception )
		{
			std::cout << "Exception! " << _exception.what() << std::endl;
		}
	}

	return 0;
}