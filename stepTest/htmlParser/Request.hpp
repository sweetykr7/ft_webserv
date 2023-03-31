#include <map>
#include <string>
#include <utility>




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
		//스타트 라인 + 헤더필드 중요사항
		method_enum								_method;
		std::string								_uri;
		std::string 							_queryString;
		std::string 							_protocol;
		std::pair<std::string, unsigned int>	_host;
		std::string 							_transferEncoding;
		uint32_t 								_contentLength; //content_length 자료형 수정 필요함.
		std::map<std::string, std::string>		_cookie//쿠키 추가, 파싱함수에도 추가해야함.

		HeaderFieldsMap							header_field;//헤더필드 나머지 넣는곳.
		Location*								m_locationBlock; //이름 가칭, 가상서버 위치 
	
};