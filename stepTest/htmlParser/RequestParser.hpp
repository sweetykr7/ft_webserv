#include "Request.hpp"

class RequestParser{

	public:
		void parsing(Request &_request, std::string &buff);
		

	
};


	
parser
	ft_getline(): /r/n을 한 줄로 반환
	flush(): 이미 get한 한 줄은 버퍼에서 지워준다

start line 파싱(첫번째 라인)
{
	request target

	char *temp = split()
	3개인지 확인
	request target 길이 확인(temp[0])
		? 기준으로 앞은 uri에 저장, 뒤는 querystring에 저장
	method 변수 확인
		GET, POST, DELETE가 아니면 501
	protocol
		"HTTP/1.1"가 아니면 500번대?

	각각 멤버변수에 저장
}

private:

public:
	parcing();
	


header_parsing()
{
	transfer encoding check()?????


}



header 파싱(나머지 라인 다)
{
	반복
		맵에 헤더필드 한 줄을 key: value로 추가하는 함수(맵, getline())
			: 기준
			key 앞뒤 공백 체크
			중복 체크
			toupper()로 넣는다
	host check() :server 있는지 체크
		헤더필드가 없으면 400
		저장
			앞뒤 trim()
			:기준으로 split()해서 저장
		find_server()
	transfer encoding check(map[tranfer encoding])
		,기준으로 split() 후 각각 trim()해서 저장(길이가 0이면 저장하지 않음)
		0개일 때 || 1개이고 chunked
			ok, 저장
		나머지
			400
	content-length check()
		,기준으로 split()
		첫 번째 값이 유효한지 check, 400
		나머지 값들이 첫번째 값과 같은지 check,  400
		넣는다
}