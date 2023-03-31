#include <sys/socket.h>
#include <iostream>
// int socket(int domain, int type, int protocol);


int main()
{
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		std::cout << "socket error" << std::endl;
	
	struct sockaddr serv_addr;
	if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		std::cout << "bind error" << std::endl;
	
	int backlog = 10;
	if (listen(sockfd, backlog) == -1)
		std::cout << "listen error" << std::endl;
	
	

}
