// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#define PORT 1815
  
int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    // char hello[18] = "Hello from client";
    
    if (argc < 2)
    {
        printf("plz input message");
        return 0;
    }


    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    int flag = 0;
    int socket_connection_fd;
    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    while(1)
    {

        
            
        // send(client_fd, argv[1], strlen(argv[1]), 0);
        write(client_fd, argv[1], strlen(argv[1]));
        printf("message sent : %s\n", argv[1]);

        // if (flag == 0)
        // {
        //     struct sockaddr_in serv_addr, client_addr;
        //     int client_len;
        //     socket_connection_fd = accept(client_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
        //     flag = 1;
        // }

        // struct sockaddr_in serv_addr, client_addr;
        // int client_len;
        // socket_connection_fd = accept(client_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
        // flag = 1;
        
        char *buf = new char[1000];
        size_t bytes_read = recv(client_fd, buf, 1000, 0);
        printf("read data : %s\n", buf);

        usleep(1000000);


    }
    // valread = read(client_fd, buffer, 1024);
    // printf("%s\n", buffer);
  
    // closing the connected socket
    close(client_fd);
    printf("close socket\n");
    return 0;
}