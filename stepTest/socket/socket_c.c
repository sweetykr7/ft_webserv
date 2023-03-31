#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


void error_handling(char *msg);

int main(int ac, char **av)
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("sock error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; //ipv4
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //ip address
	// printf("server addr : %d\n", serv_addr.sin_addr.s_addr);
	
	serv_addr.sin_port = htons(atoi(av[1]));	   //port

	//binding
	if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind error");

	//listen
	if (listen(serv_sock, 5) == -1)
		error_handling("listen error");

	//accept
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept error");
	
	//data send
	char msg[] = "Helloooooooo this server!!!";

	write(clnt_sock, msg, sizeof(msg));

	//socket close
	close(clnt_sock);
	close(serv_sock);

	return 0;
}

void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);	
}