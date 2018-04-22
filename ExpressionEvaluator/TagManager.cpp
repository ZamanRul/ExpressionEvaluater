#include "TagManager.h"

TagManager& TagManager::get()
{
	static TagManager manager;

	return manager;
}

void TagManager::add( const TagData& _data )
{
	m_tags_list.insert( { _data.m_name, _data } );
}

void TagManager::remove( const std::string& _tag_name )
{
	m_tags_list.erase( _tag_name );
}

bool TagManager::tag_exists( const std::string& _tag_name )
{
	auto it = m_tags_list.find( _tag_name );

	if ( it != m_tags_list.end() )
		return true;

	return false;
}

VariableType TagManager::get_tag_type( const std::string& _tag_name )
{
	auto it = m_tags_list.find( _tag_name );

	if ( it != m_tags_list.end() )
		return ( *it ).second.m_type;

	return VariableType::UNDEFINED;
}

TagData::data_type TagManager::get_tag_value( const std::string& _tag_name )
{
	auto it = m_tags_list.find( _tag_name );

	if ( it != m_tags_list.end() )
		return (*it).second.m_value;

	return TagData::data_type { 0 };
}


TagManager::TagManager()
{}