#pragma once

#include "GlobalDefinitions.h"

#include <string>
#include <unordered_map>

#include <boost/variant.hpp>

class TagData
{
public:

	using data_type = boost::variant<
		bool,
		std::string,
		short,
		unsigned short,
		int,
		unsigned int,
		long int,
		unsigned long int,
		float,
		double
	>;

public:

	std::string m_name;
	VariableType m_type;
	data_type m_value;
};

class TagManager
{
public:

	static TagManager& get();

	TagManager( TagManager& ) = delete;
	TagManager( TagManager&& ) = delete;
	TagManager operator=( TagManager& ) = delete;

	void add( const TagData& _data );
	void remove( const std::string& _tag_name );

	bool tag_exists( const std::string& _tag_name );
	
	VariableType get_tag_type( const std::string& _tag_name );
	TagData::data_type get_tag_value( const std::string& _tag_name );

private:

	TagManager();

private:

	std::unordered_map< std::string, TagData > m_tags_list;
};