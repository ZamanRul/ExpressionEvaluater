#pragma once

#include "BaseExpr.h"


class Const : public BaseExpr
{
public:

	using pointer_type = std::shared_ptr< Const >;

public:

	explicit Const( bool _value );
	explicit Const( const std::string& _value );
	explicit Const( short _value );
	explicit Const( unsigned short _value );
	explicit Const( int _value );
	explicit Const( unsigned int _value );
	explicit Const( long int _value );
	explicit Const( unsigned long int _value );
	explicit Const( float _value );
	explicit Const( double _value );

	void evaluate() override;

	void accept( IVisitorPtr _visitor );

	std::string to_string() override;
	
};

using ConstPtr = Const::pointer_type;