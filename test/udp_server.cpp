#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "../core/event_factory.h"

void handle_recv(int fd, void *ctx, int revents)
{
    char buf[1024] = {0};
    struct sockaddr_in sa;
    socklen_t sa_len = sizeof(sa);

    if (revents & Event::EVENT_IN)
    {
        int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&sa, &sa_len);
        if (n > 0)
        {
            std::cout << "recv " << inet_ntoa(sa.sin_addr) << ":" << ntohs(sa.sin_port) << " " << buf << std::endl;
        }
        else
        {
            std::cout << "error:" << errno << strerror(errno) << "EAGAIN:" << EAGAIN << std::endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    int fd;
    struct sockaddr_in addr = { AF_INET, htons(6010), INADDR_ANY };

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    bind(fd, (sockaddr*)&addr, sizeof(addr));

    Event *ev = EventFactory::Create("epoll");
    // Event *ev = EventFactory::Create("select");

    ev->Init(10);

    ev->Register(fd, handle_recv, NULL);

    ev->Set(fd, Event::EVENT_IN);

    while (1)
    {
        ev->Loop(100, 10);
    }

    ev->Free();

    return 0;
}
