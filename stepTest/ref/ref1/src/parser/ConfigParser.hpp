#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <vector>

#include "Webserv.hpp"
#include "VirtualServer.hpp"
#include "parser/AParser.hpp"
#include "tokenizer/FileTokenizer.hpp"

class	ConfigParser: public AParser<FileTokenizer, void>
{
// deleted
	ConfigParser(ConfigParser const& configParser);
	ConfigParser	&operator=(ConfigParser const& configParser);

public:
	class	ConfigParserException;

// constructors & destructor
	ConfigParser();
	virtual ~ConfigParser();

// member functions
	void			init(std::string configPath, VirtualServerTable& serverTable);

	virtual void	parse();
	void			parseServer();

private:
	void	checkDuplicateServerName(VirtualServer& server);
	void	addNameToTable(VirtualServer& server);

	VirtualServerTable*	m_serverTable;
};

#endif
