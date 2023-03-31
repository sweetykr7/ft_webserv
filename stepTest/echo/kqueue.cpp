#include <sys/types.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_EVENTS 10
#define BUF_SIZE 1024

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        std::exit(1);
    }

    int port = std::atoi(argv[1]);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::perror("socket");
        std::exit(1);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        std::perror("setsockopt");
        std::exit(1);
    }

    struct sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1)
    {
        std::perror("bind");
        std::exit(1);
    }

    if (listen(server_fd, SOMAXCONN) == -1)
    {
        std::perror("listen");
        std::exit(1);
    }

    int kq = kqueue();
    if (kq == -1)
    {
        std::perror("kqueue");
        std::exit(1);
    }

    struct kevent events[MAX_EVENTS];

    EV_SET(&events[0], server_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);

    while (true)
    {
        int nevents = kevent(kq, events, MAX_EVENTS, NULL, 0, NULL);
        if (nevents == -1)
        {
            std::perror("kevent");
            std::exit(1);
        }

        for (int i = 0; i < nevents; ++i)
        {
            int fd = events[i].ident;

            if (fd == server_fd)
            {
                int client_fd = accept(server_fd, NULL, NULL);
                if (client_fd == -1)
                {
                    std::perror("accept");
                    std::exit(1);
                }

                fcntl(client_fd, F_SETFL, O_NONBLOCK);

                EV_SET(&events[i], client_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
            }
            else
            {
                char buf[BUF_SIZE];
                ssize_t nread = read(fd, buf, sizeof(buf));

                if (nread == -1)
                {
                    std::perror("read");
                    std::exit(1);
                }

                if (nread == 0)
                {
                    EV_SET(&events[i], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                    close(fd);
                }
                else
                {
                    EV_SET(&events[i], fd, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, NULL);
                }
            }
        }
    }

    return 0;
}