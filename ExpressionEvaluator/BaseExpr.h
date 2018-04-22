#pragma once

#include "IExpr.h"

class BaseExpr : public IExpr
{
public:

	using pointer_type = std::shared_ptr< BaseExpr >;

public:

	BaseExpr();

	VarPtr get_value() const override;

	VariableType get_type() const override;

	bool is_const() const override;

protected:

	VarPtr m_value;
	VariableType m_type;

	bool m_is_const;

};