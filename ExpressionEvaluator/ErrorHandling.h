#pragma once

#include <exception>
#include <string>
#include <boost/format.hpp>

class EEException : public std::exception
{
public:

	const char* what() const override;

protected:

	std::string m_message;
};

class TypeMismatch : public EEException
{
public:

	TypeMismatch( const std::string& _type1, const std::string& _type2 );
	TypeMismatch( const std::string& _type1, const std::string& _type2, const std::string& _type3 ); 
};

class UnappropriateType : public EEException
{
public:

	UnappropriateType( const std::string& _type );
	UnappropriateType( const std::string& _expected_type, const std::string& _current_type );
};

class UnknownTag : public EEException
{
public:

	UnknownTag( const std::string& _tag_name );
};

class OperationNSY : public EEException
{
public:

	OperationNSY( const std::string& _description );
};

class DivisionByZero : public EEException
{
public:

	DivisionByZero();
};

class ModuloBadArguments : public EEException
{
public:

	ModuloBadArguments( const std::string& _type_1, const std::string& _type_2 );
};