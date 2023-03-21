#include <fcntl.h>

#include "Logger.hpp"
#include "VirtualServer.hpp"
#include "ServerManager.hpp"
#include "io/IoMultiplex.hpp"
#include "event/Cgi.hpp"
#include "http/AutoIndex.hpp"
#include "util/Util.hpp"
#include "responder/GetResponder.hpp"

using namespace std;

extern string	g_tempDir;

// constructors & destructor
GetResponder::GetResponder(RequestHandler& requestHandler)
:	AResponder(requestHandler)
{
}

GetResponder::~GetResponder()
{
}

// operators
GetResponder&
GetResponder::operator=(const GetResponder& getMethod)
{
	(void)getMethod;
	return *this;
}

void
GetResponder::respondWork()
{
	string readBody;

	switch (m_responseStatus)
	{
		case RES_HEADER:
			if (isAutoIndex())
				m_request.m_status = 200;
			respondStatusLine(m_request.m_status);
			respondHeader();
			m_responseStatus = RES_CONTENT; // fall through
		case RES_CONTENT:
			if (isAutoIndex())
				readBody = AutoIndex::autoIndex(m_request.m_path, m_request.m_uri);
			else if (m_request.m_isCgi == true)
			{
				// WARNING: /a/a.html and /b/a.html has same filename.
				// if two request has same filename, later request will delete and rewrite it
				// so that earlier request will lost
				string tmpFile = g_tempDir + m_request.m_file + ".temp";
				openFile(tmpFile);
				constructCgi(readBody);
				unlink(tmpFile.c_str());
			}
			else if (m_request.m_status != 200)
			{
				m_request.m_path = getErrorPage(readBody);
			}
			readFile(readBody);
			respondBody(readBody);
			// TODO: change code to use swap instead of appen
			m_responseStatus = RES_DONE; // fall through
			// break;
		case RES_DONE:
		// method must know end of response(content length, chunked)
			endResponse();
			break;
		default:
			;
	}
}

void
GetResponder::constructCgi(std::string& readBody)
{
	int	pipeSet[2];

	pipe(pipeSet);

	Cgi*	cgi = new Cgi(m_fileFd, pipeSet[1], m_requestHandler);

	ServerManager::registerEvent(pipeSet[1], Cgi::IoEventPoller::OP_ADD, Cgi::IoEventPoller::FILT_READ, cgi);
	ServerManager::registerEvent(pipeSet[0], Cgi::IoEventPoller::OP_ADD, Cgi::IoEventPoller::FILT_WRITE, cgi);
	cgi->initEnv(m_request);
	cgi->executeCgi(pipeSet, readBody);
	m_responseStatus = RES_DONE;
}

bool
GetResponder::isAutoIndex()
{
	if (m_request.m_file == "")
	{
		if (m_request.m_locationBlock != NULL)
			return (m_request.m_locationBlock->m_autoindex);
		return (m_request.m_virtualServer->m_autoindex);
	}
	return (false);
}
