#pragma once


#include "IVisitor.h"

#include "Const.h"
#include "UnExpr.h"
#include "BinExpr.h"
#include "TriExpr.h"

#include <string>
#include <sstream>

#define LOG(message)					\
if ( m_enable_logging )					\
{										\
	m_stream << message << std::endl;	\
	log();								\
}

class EvaluationVisitor : public IVisitor
{
public:

	using pointer_type = std::shared_ptr< EvaluationVisitor >;

public:

	EvaluationVisitor( bool _enable_logging );

	void visit( Const* _ptr ) override;
	void visit( UnExpr* _ptr ) override;
	void visit( BinExpr* _ptr ) override;
	void visit( TriExpr* _ptr ) override;

protected:

	void log();

protected:	

	bool m_enable_logging;

	std::stringstream m_stream;
};

using EvaluationVisitorPtr = EvaluationVisitor::pointer_type;