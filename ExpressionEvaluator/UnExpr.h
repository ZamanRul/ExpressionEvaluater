#pragma once


#include "BaseExpr.h"


class UnExpr : public BaseExpr, public std::enable_shared_from_this< UnExpr >
{
public:

	using pointer_type = std::shared_ptr< UnExpr >;

public:

	UnExpr( Operator _operator, IExprPtr _child );

	void evaluate() override;

	void accept( IVisitorPtr _visitor );

	std::string to_string() override;

protected:

	Var evaluate_tag();

	Var evaluate_not();
	Var evaluate_pos();
	Var evaluate_neg();
	
protected:

	Operator m_operator;

	IExprPtr m_child;

};

using UnExprPtr = UnExpr::pointer_type;