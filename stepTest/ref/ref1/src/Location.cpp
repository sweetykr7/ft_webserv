#include <ostream>

#include "Config.hpp"
#include "Location.hpp"

using namespace std;

// constructors & destructor
Location::Location()
{
	setToDefault();
}

Location::~Location()
{
}

void
Location::setToDefault()
{
	m_autoindex = -1;
	m_limitExcept = limitExcept;
	m_alias = "";
	m_clientMaxBodySize = 0;
}

ostream&
operator<<(std::ostream& os, const Location& location)
{
	os << "\tlocation\t" << location.m_path << "\n\t{\n";
	os << "\t\talias " << location.m_alias << "\n";
	os << "\t\troot " << location.m_root << "\n";
	os << "\t}\n";
	return os;
}
