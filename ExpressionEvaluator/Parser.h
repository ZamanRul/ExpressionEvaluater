#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3 1

#include "ExprFactory.h"

#include <string>
#include <iostream>
#include "boost/spirit/include/classic.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/spirit/include/qi_numeric.hpp>

using namespace boost::spirit;

template < typename Iterator, typename Skipper >
struct ScriptGrammar : boost::spirit::qi::grammar< Iterator, IExprPtr, Skipper >
{
protected:

	template < typename T >
	struct strict_real_policies : qi::real_policies< T >
	{
		static bool const expect_dot = true;
	};
	
public:

	ScriptGrammar( bool _debug_mode = false ) :
		ScriptGrammar::base_type { expression },
		m_debug_mode { _debug_mode }
	{       
		using qi::_val;

		qi::char_type char_;
		qi::real_parser< double, strict_real_policies< double > > real_parser;

		int_const = int_[ _val = boost::phoenix::bind( []( int i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		uint_const = ( uint_ >> 'u' )[ _val = boost::phoenix::bind( []( unsigned int i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		sint_const = short_[ _val = boost::phoenix::bind( []( short i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		usint_const = ushort_[ _val = boost::phoenix::bind( []( unsigned short i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		lint_const = ( long_ >> 'l' )[ _val = boost::phoenix::bind( []( long i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		ulint_const = ( ulong_ >> "ul" )[ _val = boost::phoenix::bind( []( unsigned long i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		real_const = ( float_ >> 'f' )[ _val = boost::phoenix::bind( []( float i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];
		lreal_const = real_parser[ _val = boost::phoenix::bind( []( double i) { return ExprFactory::create_const( i ); }, qi::_1 ) ];

		number_const = ulint_const[ _val = _1 ] |
						uint_const[ _val = _1 ] |
						lint_const[ _val = _1 ] |
						lreal_const[ _val = _1 ] |
						real_const[ _val = _1 ] |
						int_const[ _val = _1 ] |
						usint_const[ _val = _1 ] |
						sint_const[ _val = _1 ];

		bool_const = bool_[ _val = boost::phoenix::bind( []( bool i ) { return ExprFactory::create_const( i ); }, qi::_1 ) ];

		string_const = ( '"' >> *~char_( '"' ) >> '"' )[ _val = boost::phoenix::bind( []( std::vector< char > i ) { return ExprFactory::create_const( std::string { i.begin(), i.end() } ); }, qi::_1 ) ];

		const_literal = number_const[ _val = _1 ] |
						bool_const[ _val = _1 ] |
						string_const[ _val = _1 ];

		expression = ( const_literal >> char_( '+' ) >> const_literal )[ _val = boost::phoenix::bind( []( IExprPtr _left, IExprPtr _right ) { 
																	return ExprFactory::create_binary( Operator::PLUS, _left, _right ); }, qi::_1, qi::_3 ) ] |
						const_literal[ _val =_1 ] |
						( char_( '(' ) >> expression >> char_( ')' ) )[ _val = qi::_2 ];

		if ( m_debug_mode )
			enable_debug();
	}

	void enable_debug()
	{
		expression.name( "expression" );	
		const_literal.name( "const_literal" );

		bool_const.name( "bool_const" );
		string_const.name( "string_const" );
		number_const.name( "number_const" );

		lreal_const.name( "lreal_const" );
		real_const.name( "real_const" );
		ulint_const.name( "ulint_const" );
		lint_const.name( "lint_const" );
		uint_const.name( "uint_const" );
		int_const.name( "int_const" );
		usint_const.name( "usint_const" );
		sint_const.name( "sint_const" );
						
		qi::debug( expression );
		qi::debug( const_literal );
		qi::debug( string_const );
		qi::debug( bool_const );
		qi::debug( number_const );
		qi::debug( lreal_const );
		qi::debug( real_const );
		qi::debug( ulint_const );
		qi::debug( lint_const );
		qi::debug( uint_const );
		qi::debug( int_const );
		qi::debug( usint_const );
		qi::debug( sint_const );
	}

	qi::rule< Iterator, IExprPtr, Skipper > lreal_const;
	qi::rule< Iterator, IExprPtr, Skipper > real_const;
	qi::rule< Iterator, IExprPtr, Skipper > ulint_const;
	qi::rule< Iterator, IExprPtr, Skipper > lint_const;
	qi::rule< Iterator, IExprPtr, Skipper > uint_const;
	qi::rule< Iterator, IExprPtr, Skipper > int_const;
	qi::rule< Iterator, IExprPtr, Skipper > usint_const;
	qi::rule< Iterator, IExprPtr, Skipper > sint_const;

	qi::rule< Iterator, IExprPtr, Skipper > bool_const;
	qi::rule< Iterator, IExprPtr, Skipper > string_const;
	qi::rule< Iterator, IExprPtr, Skipper > number_const;

	qi::rule< Iterator, IExprPtr, Skipper > const_literal;
	qi::rule< Iterator, IExprPtr, Skipper > expression;


	bool m_debug_mode;
};


class Parser 
{
public:

	using pointer_type = std::shared_ptr< Parser >;

public:

	IExprPtr parse( std::string& _text );
};

using ParserPtr = Parser::pointer_type;