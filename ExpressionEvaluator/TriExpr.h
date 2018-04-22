#pragma once


#include "BaseExpr.h"


class TriExpr : public BaseExpr
{
public:

	using pointer_type = std::shared_ptr< TriExpr >;

public:

	TriExpr( Operator _operator, IExprPtr _first, IExprPtr _second, IExprPtr _third );

	void evaluate() override;	

	void accept( IVisitorPtr _visitor );
	
	std::string to_string() override;

protected:

	Operator m_operator;

	IExprPtr m_first;
	IExprPtr m_second;
	IExprPtr m_third;

};

using TriExprPtr = TriExpr::pointer_type;