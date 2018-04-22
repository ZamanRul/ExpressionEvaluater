#pragma once


#include "BaseExpr.h"


class UnExpr : public BaseExpr
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
	
protected:

	Operator m_operator;

	IExprPtr m_child;

};

using UnExprPtr = UnExpr::pointer_type;