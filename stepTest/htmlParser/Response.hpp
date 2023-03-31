#include <map>
#include <string>
#include <utility>

//typedef
typedef std::pair<std::string, std::string>	cookie_value_type; //value, exp date
typedef std::map<std::string, cookie_value_type> cookie_type; //cookie_id, cookie_value	
typedef std::string	body_type; //body

enum	status_code_line{
	S200, S201, S205, S300, S400, S401, S404, S411, S410, S413, S414, S503, S504, S505
}; //Response message에서 쓰는 상태 코드에 대한 enum

class Response{
	//member variable
	private:
		body_type				_responseMsg;
		body_type 				_startLine;
		body_type 				_headLine;
		body_type 				_body;
		cookie_type				_setCookie;
		status_code_line		_statusCode;

		//class
		CookieSessionHandler 	_cookieSessionHandler;
		MethodHandler			_methodHandler; //CgiHandler랑 FileHandler를 상속받아서 기능을 쓸 수 있게 만듬.
		ResponseMsgHandler		_responseMsgHandler;

	//member function
	public:
		//method 	#####isMethodEnable함수 서버쪽으로 이전해야 될듯?
		bool 		isMethodEnable(); //메소드 권한 확인 : limit_accept에 allow를 확인, 서버 클래스에서 limit_accept 확인해서 없으면 에러코드(미정)
};


class CookieSessionHandler{
	private:
	public:
		//cookie
		bool 		isCookie(); //쿠키 존재 여부 확인
		void 		createInfoForCookie(); //쿠키 관련 정보 생성, _setCookie에 생성된 정보를 담는다.
		std::string createCookieExpTime(); //쿠키의 유효기간 시간을 생성해서 리턴한다.

		//session
		bool 		isSession(); //세션 존재 여부 확인
		bool 		checkInfoForLogin(); //로그인 관련 정보, 쿼리 스트링에서 id/pw를 확인한다.
		void		createSession(); //setCookie에 세션 id를 추가 한다.
};


class MethodHandler 
	: public FileHandler, public CgiHandler
{
	private:
	public:

		bool		isFunctionEnable(); //uri에 접근하려는 리소스가 있는지 확인, 메소드 단위로 나누는게 좋을듯 (write.cgi  update.cgi, delete.cgi등등)
		
		//method processing
		void		methodRun(); //메소드 실행하는 곳
		void		getMethod();		 //GET METHOD 안에서 파일할지 CGI할지 분기
		void		postMethod();		 //POST METHOD
		void		deleteMethod();	 //DELETE METHOD

};

class FileHandler{
	private:
	public:
		//resource check(chmod)
		bool 		isResourceEnable(); //접근하려는 리소스가 가능한지 확인, 내부 GET/POST/DELETE에 따라 분기
		bool		isFileEnable();	 //file 접근가능한지 확인, stat()으로 접근(same like 미니쉐르)
		//file processing in METHOD 
		body_type 	getBodyFromFile();	//파일열고 내용을 추출한다.
};

class CgiHandler{
	private:
	public:
		//cgi processing in METHOD
		body_type	cgiRun();		//cgi전체 진행, 환경변수 셋팅, 파이프, 포크, exceve/read 이벤트를 등록, 끝나고 파이프 읽기등을 진행
		void		setEnvForCgi();		//cgi를 위한 환경변수 셋팅
		void		addCgiExceveEvent();		//cgi process(execve)를  event에 등록, EventHandler쪽으로 요청해야될듯.
		void		addCgiReadEvent();			//cgi에서 자식 프로세스가 종료되고 pipe를 읽기 전에 read를 event에 등록

};

class ResponseMsgHandler{
	private:
	public:
		//응답 메세지 만들기
		body_type	createResponseMsg();	//응답 메세지 만들기, _status변수를 바탕으로 각각 다르게 만든다.
											//스타트라인, 헤더, 그리고 이미 만들어져 있는 바디를 붙이거나 에러 바디를 가져온다.
		body_type	createStartLine();		//version status-code message(ex : complete)를 만든다.			
			
		body_type	createHeaderLine();		//startline을 제외한 나머지 헤더라인을 만든다. 필수 : date, content-type, content-length
		std::string	createResponseDate();	//헤더라인의 date를 만든다.
		std::string	createContentType();	//컨텐트 타입을 만든다.
		u_int32_t	getResponseContentLength();	//Content-length를 만들어서 가져온다.				
		//에러메세지 만들기
		body_type	getErrorBody(); 		//에러 코드별 해당 페이지를 가져온다.(ex : 401.html 만들어 놓고 페이지 가져옴)

};