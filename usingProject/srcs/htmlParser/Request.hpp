class Request
{
	typedef std::map<std::string, std::string> HeaderFieldsMap;

	enum	method_enum
	{
		GET = 0,
		POST = 1,
		DELETE = 2
	};

	private:
		//start line
		method_enum								_method;
		std::string								_absolutePath;
		std::string 							_query;
		std::string 							_httpVersion;

		// header fields
		HeaderFieldsMap							headerFields;//헤더필드 전체를 이곳에 우선 저장 후, 필요한 내용만 꺼내 requeset 구조체 멤버변수에 저장
		std::pair<std::string, unsigned int>	_host;
		std::string 							_transferEncoding;
		uint32_t 								_contentLength;
		std::map<std::string, std::string>		_cookie;

		Location*								m_locationBlock; //이름 가칭, 가상서버 위치
};