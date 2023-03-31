#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

using namespace std;

int main() {
    int server_fd, new_socket, max_fd, valread;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from server";
    int client_fds[MAX_CLIENTS] = {0};

    // Create a socket for the server
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to allow multiple connections
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a specific IP address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Listening on port " << PORT << endl;

    // Set up the file descriptor set for select()
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(server_fd, &read_fds);
    max_fd = server_fd;

    // Main loop for handling client connections and incoming data
    while (true) {
        // Wait for activity on any of the file descriptors in the set
        fd_set tmp_fds = read_fds;
        int activity = select(max_fd + 1, &tmp_fds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            perror("select error");
            exit(EXIT_FAILURE);
        }

        // Check if there is activity on the server socket
        if (FD_ISSET(server_fd, &tmp_fds)) {
            // Accept incoming connection from a client
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&address)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            cout << "New connection, socket fd is " << new_socket << ", ip is " << inet_ntoa(address.sin_addr) << ", port is " << ntohs(address.sin_port) << endl;

            // Add the new client socket file descriptor to the set of file descriptors to watch for events
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_fds[i] == 0) {
                    client_fds[i] = new_socket;
                    break;
                }
            }

            // Add the new client socket file descriptor to the set of file descriptors to watch for events
            FD_SET(new_socket, &read_fds);

            // Update the maximum file descriptor value to watch for events
            if (new_socket > max_fd) {
                max_fd = new_socket;
            }
        }

        // Check activity on client sockets
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int client_fd = client_fds[i];
            if (FD_ISSET(client_fd, &tmp_fds)) {
                // Read data from the client
                valread = read(client_fd, buffer, BUFFER_SIZE);
                if (valread <= 0) {
                    // Client has disconnected
                    cout << "Client disconnected, socket fd is " << client_fd << endl;
                    close(client_fd);
                    client_fds[i] = 0;
                    FD_CLR(client_fd, &read_fds);
                } else {
                    // Print the received data and send a response to the client
                    cout << "Received data from client on socket fd " << client_fd << ": " << buffer << endl;
                    send(client_fd, message, strlen(message), 0);
                }
            }
        }
    }

    return 0;
}
