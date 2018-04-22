#pragma once

#include <memory>

class Const;
class UnExpr;
class BinExpr;
class TriExpr;

class IVisitor
{
public:

	using pointer_type = std::shared_ptr< IVisitor >;

	using ConstPtr = std::shared_ptr< Const >;
	using UnExprPtr = std::shared_ptr< UnExpr >;
	using BinExprPtr = std::shared_ptr< BinExpr >;
	using TriExprPtr = std::shared_ptr< TriExpr >;

public:

	virtual ~IVisitor() {}

	virtual void visit( ConstPtr _ptr ) = 0;
	virtual void visit( UnExprPtr _ptr ) = 0;
	virtual void visit( BinExprPtr _ptr ) = 0;
	virtual void visit( TriExprPtr _ptr ) = 0;
};

using IVisitorPtr = IVisitor::pointer_type;