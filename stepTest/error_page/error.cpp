#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>

using namespace std;

const int PORT = 1815;
const int BUFFER_SIZE = 1024;

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    // const char* message = "HTTP/1.1 404 error\r\nLocation: index.html\r\nContent-Length:X\r\n\r\n";
    // const char* message = "HTTP/1.1 404 error\r\nLocation: aaa.html\r\n\r\n";


    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        // Accept incoming connections
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Receive data from client
        valread = read(new_socket, buffer, BUFFER_SIZE);
        printf("Client message: %s\n", buffer);



        std::ifstream file("404.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string error_page = buffer.str();

        // Set up the response message
        std::string response = "HTTP/1.1 100 Continue\r\n";
        // response += "Content-Type: text/html\r\n";

        // Set the `Location` header to the new URL if you want to redirect the client
        // response += "Location: https://www.example.com/new-url\r\n";

        // response += "Content-Length: " + std::to_string(error_page.length()) + "\r\n\r\n";
        response += "\r\n\r\n";
        // response += error_page;

        // Send response back to client
        // const char* message = response;
        send(new_socket, response.c_str(), strlen(response.c_str()), 0);

        

        usleep(5000000);

        response = "";
        response = "HTTP/1.1 404 Bad Request\r\n";
        // response += "Content-Type: text/html\r\n";

        // Set the `Location` header to the new URL if you want to redirect the client
        // response += "Location: https://www.example.com/new-url\r\n";
        
        response += "Content-Length: " + std::to_string(error_page.length()) + "\r\n\r\n";
        response += "\r\n\r\n";
        response += error_page;

        // Send response back to client
        // const char* message = response;
        send(new_socket, response.c_str(), strlen(response.c_str()), 0);
        printf("Hello message sent\n");
    }
    // close(new_socket);
    return 0;
}
