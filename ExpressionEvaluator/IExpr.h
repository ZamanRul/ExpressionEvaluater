#pragma once

#include <memory>

#include "Var.h"
#include "GlobalDefinitions.h"
#include "IVisitor.h"

class IVisitor;

class IExpr
{
public:

	using pointer_type = std::shared_ptr< IExpr >;

public:

	virtual ~IExpr() {}

	virtual void evaluate() = 0;

	virtual void accept( IVisitorPtr _visitor ) = 0;

	virtual VarPtr get_value() const = 0;
	virtual VariableType get_type() const = 0;
	virtual bool is_const() const = 0;

	virtual std::string to_string() = 0;

};

using IExprPtr = IExpr::pointer_type;