

// #include <string>

// struct  server
// {
//     std::string server_name;
//     std::string root;
//     std::string listen;
//     std::string cgi_pass;
//     std::string index;
//     std::string error_page; // 필요한가? 
//     int         client_max_body_size; // 음수인경우 처리

// };
#include <fstream>
#include <iostream>


int main()
{
	std::string filePath = "server.config";
	std::string sum = "";
		// read File
	std::ifstream openFile(filePath.data());
	if( openFile.is_open() ){
		std::string line;
		while(std::getline(openFile, line)){
			sum = sum + line;
			std::cout << line << std::endl;
		}
		openFile.close();
	}
	std::cout << sum << std::endl;

}
	