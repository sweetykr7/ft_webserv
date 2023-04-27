#include "Request.hpp"
#include <utility>
#include <map>
#include <vector>
#include <string>

class RequestParser
{
	private:
		void parseStartLine(Request &_request, std::string &buff);
		void parseHeaderFields(Request &_request, std::string &buff);
			//parseHeaderFields 내에서 사용
		void initHost(Request &_request, std::pair<std::string, std::string>);
		void initTransferEncoding(Request &_request, std::pair<std::string, std::string>);
		void initContentLength(Request &_request, std::pair<std::string, std::string>);
		void initCookie(Request &_request, std::pair<std::string, std::string>);
		void parseBody(Request &_request, std::string &buff);

	public:
		void parse(Request &_request, std::string &buff);
};

class Utils
{
	public:
		std::vector<std::string> split(char delimeter);
		std::string trim(char delimeter);
		std::pair<std::string, std::string> getPair(std::string src, char delimeter);
};

class Buffer : public std::string
{
	public:
		std::string getLine();// /r/n까지 반환하고 반환했을 경우 그 줄 flush
		//void flush(size_t count);
};