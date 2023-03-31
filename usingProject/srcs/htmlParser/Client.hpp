#include <map>
#include <string>
#include <utility>
#include "Request.hpp"
#include "Response.hpp"
#include "RequestParser.hpp"

class Client{
	private:
		cookie_type 			_cookieList;
		std::string				_buff;
		Request					_request;
		Response				_response; //server로 옮겨야 될듯?!


	public:

		
};

int main()
{

	Client A;
	RequestParser B;

	B.parsing(A._request, A.buff);	
	
}
