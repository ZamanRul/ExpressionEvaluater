#include "ErrorHandling.h"

#include <boost/format.hpp>

const char* EEException::what() const
{
	return m_message.c_str();
}

TypeMismatch::TypeMismatch( const std::string& _type1, const std::string& _type2 )
{
	using namespace boost;

	m_message = str( format { "Type mismatch between %1% and %2%" }
		% _type1
		% _type2
	);
}

TypeMismatch::TypeMismatch( const std::string& _type1, const std::string& _type2, const std::string& _type3 )
{
	using namespace boost;

	m_message = str( format { "Type mismatch between %1%, %2% and %3%" }
		% _type1
		% _type2
		% _type3
	);
}

UnappropriateType::UnappropriateType( const std::string& _type )
{
	using namespace boost;

	m_message = str( format { "Unappropriate type %1%" }
		% _type
	);
}

UnappropriateType::UnappropriateType( const std::string& _expected_type, const std::string& _current_type )
{
	using namespace boost;

	m_message = str( format { "Unappropriate type. Expected %1%, but received %2%" }
		% _expected_type
		% _current_type
	);
}

UnknownTag::UnknownTag( const std::string& _tag_name )
{
	using namespace boost;

	m_message = str( format { "Unknown tag %1%" }
		% _tag_name
	);
}

OperationNSY::OperationNSY( const std::string& _description )
{
	using namespace boost;

	m_message = str( format { "Operation not supported yet: %1%" }
		% _description
	);
}

DivisionByZero::DivisionByZero()
{
	m_message = std::string { "Division by zero" };
}

ModuloBadArguments::ModuloBadArguments( const std::string& _type_1, const std::string& _type_2 )
{
	using namespace boost;

	m_message = str( format { "Operation modulo bad arguments: %1%, %2%" }
		% _type_1
		% _type_2
	);
}