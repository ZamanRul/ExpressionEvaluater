#pragma once


#include "BaseExpr.h"

class BinExpr : public BaseExpr, public std::enable_shared_from_this< BinExpr >
{
public:

	using pointer_type = std::shared_ptr< BinExpr >;

public:

	BinExpr( Operator _operator, IExprPtr _left, IExprPtr _right );

	void evaluate() override;

	void accept( IVisitorPtr _visitor );

	std::string to_string() override;

protected:

	Var evaluate_or();
	Var evaluate_and();
	Var evaluate_equal();
	Var evaluate_not_equal();
	Var evaluate_less();
	Var evaluate_less_equal();
	Var evaluate_greater();
	Var evaluate_greater_equal();

	Var evaluate_plus();
	Var evaluate_minus();
	Var evaluate_mul();
	Var evaluate_div();
	Var evaluate_modulo();

protected:

	Operator m_operator;

	IExprPtr m_left;
	IExprPtr m_right;

};

using BinExprPtr = BinExpr::pointer_type;