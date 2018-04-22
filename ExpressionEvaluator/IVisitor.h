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

public:

	virtual ~IVisitor() {}

	virtual void visit( Const* _ptr ) = 0;
	virtual void visit( UnExpr* _ptr ) = 0;
	virtual void visit( BinExpr* _ptr ) = 0;
	virtual void visit( TriExpr* _ptr ) = 0;
};

using IVisitorPtr = IVisitor::pointer_type;