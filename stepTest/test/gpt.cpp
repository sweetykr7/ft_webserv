#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define PORT "8080"
#define BACKLOG 10

using namespace std;

// Helper function to read a file into a string
string readFile(string filename) {
    stringstream ss;
    FILE* fp = fopen(filename.c_str(), "rb");
    if (fp) {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), fp))
            ss.write(buf, len);
        fclose(fp);
    }
    return ss.str();
}

// Handler function for incoming requests
void handleRequest(int client) {
    char buf[1024];
    recv(client, buf, sizeof(buf), 0);
    stringstream ss;
    ss << buf;
    string method, path, version;
    ss >> method >> path >> version;
    string response;
    if (method == "GET" && path == "/") {
        response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + readFile("index.html");
    } else {
        response = "HTTP/1.1 404 Not Found\r\n\r\n";
    }
    send(client, response.c_str(), response.length(), 0);
    close(client);
}

int main() {
    int status, yes = 1;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        cerr << "getaddrinfo error: " << gai_strerror(status) << endl;
        return 1;
    }
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        close(sockfd);
        perror("bind");
        return 1;
    }
    freeaddrinfo(res);
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        return 1;
    }
    cout << "Listening on port " << PORT << endl;
    while (1) {
        struct sockaddr_storage client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }
        handleRequest(client_fd);
    }
    return 0;
}
