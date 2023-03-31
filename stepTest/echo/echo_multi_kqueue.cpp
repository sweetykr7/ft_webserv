#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/event.h>

using namespace std;

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int master_socket, addrlen, valread, new_socket;
    int kq, nevents, event_fd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};
    const char* message = "Hello from server!";
    int client_fds[MAX_CLIENTS] = {0};

    // Create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(master_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(master_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Create a kqueue
    kq = kqueue();
    if (kq == -1) {
        perror("kqueue");
        exit(EXIT_FAILURE);
    }

    // Register the master socket for read events
    struct kevent event_list[MAX_CLIENTS + 1];
    EV_SET(&event_list[0], master_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);

    // Event loop
    while (true) {
        nevents = kevent(kq, event_list, MAX_CLIENTS + 1, event_list, MAX_CLIENTS + 1, NULL);
        if (nevents == -1) {
            perror("kevent");
            exit(EXIT_FAILURE);
        }

        // Check activity on each socket
        for (int i = 0; i < nevents; i++) {
            event_fd = event_list[i].ident;

            if (event_fd == master_socket) {
                // Accept new connections
                addrlen = sizeof(address);
                if ((new_socket = accept(master_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                // Add new socket to the kqueue
                struct kevent kev;
                EV_SET(&kev, new_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
                kevent(kq, &kev, 1, NULL, 0, NULL);

                // Add new socket to the client_fds array
                for (int j = 0; j < MAX_CLIENTS; j++) {
                    if (client_fds[j] == 0) {
                        client_fds[j] = new_socket;
                        cout << "New connection, socket fd is " << new_socket << ", ip is " << inet_ntoa(address.sin_addr) << ", port is " << ntohs(address.sin_port) << endl;
                        break;
                   
                    }
                }
            } else {
                // Check for data from clients
                valread = read(event_fd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // Client disconnected
                    cout << "Client disconnected, socket fd is " << event_fd << endl;
                    close(event_fd);

                    // Remove socket from the kqueue and client_fds array
                    struct kevent kev;
                    EV_SET(&kev, event_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                    kevent(kq, &kev, 1, NULL, 0, NULL);

                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (client_fds[j] == event_fd) {
                            client_fds[j] = 0;
                            break;
                        }
                    }
                } else {
                    // Echo the received message back to the client
                    cout << "Received message: " << buffer << endl;
                    send(event_fd, message, strlen(message), 0);
                    memset(buffer, 0, BUFFER_SIZE);
                }
            }
        }
    }

    return 0;
}
