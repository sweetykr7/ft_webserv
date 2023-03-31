#ifndef VIRTUALSERVER_HPP
#define VIRTUALSERVER_HPP

#include <vector>
#include <map>
#include <utility>

#include "Webserv.hpp"
#include "http/RequestHandler.hpp"

class	VirtualServer
{
	friend class	FindLocation;
	friend class	AResponder;
	friend class	GetResponder;

	typedef	std::map<std::string, Location>	LocationTable;

public:
// constructors & destructor
	VirtualServer();
	~VirtualServer();

// member functions
	std::map<std::string, std::string>	m_cgiPass;
private:
	void	setToDefault();

// member variales - config
	bool								m_autoindex;
	int32_t								m_clientMaxBodySize;
	std::string							m_root;
	std::vector<std::string>			m_index;
	std::vector<std::string>			m_serverNames;
	std::map<int, std::string>			m_errorPageTable;
	std::map<std::string, Location>		m_locationTable;

	AddrKey				m_addrKey;
	sockaddr_in			m_listen;
// friends
	friend class			ConfigParser;
	friend class			ServerParser;
	friend void				RequestHandler::checkRequestMessage();
	friend std::ostream&	operator<<(std::ostream& os, const VirtualServer& server);
};

#endif
