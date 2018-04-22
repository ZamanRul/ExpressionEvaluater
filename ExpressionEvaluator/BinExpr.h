#pragma once


#include "BaseExpr.h"

class BinExpr : public BaseExpr
{
public:

	using pointer_type = std::shared_ptr< BinExpr >;

public:

	BinExpr( Operator _operator, IExprPtr _left, IExprPtr _right );

	void evaluate() override;

	void accept( IVisitorPtr _visitor );

	std::string to_string() override;

protected:

	Var evaluate_plus();

protected:

	Operator m_operator;

	IExprPtr m_left;
	IExprPtr m_right;

};

using BinExprPtr = BinExpr::pointer_type;