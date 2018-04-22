#include "BaseExpr.h"

BaseExpr::BaseExpr() :
	m_value{ nullptr },
	m_type{ VariableType::UNDEFINED },
	m_is_const{ false }
{}

VarPtr BaseExpr::get_value() const
{
	return m_value;
}

VariableType BaseExpr::get_type() const
{
	return m_type;
}

bool BaseExpr::is_const() const
{
	return m_is_const;
}