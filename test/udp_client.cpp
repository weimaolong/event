#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <string.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    int fd;
    struct sockaddr_in sa = { AF_INET, htons(6010), inet_addr("127.0.0.1") };

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    // bind(fd, (sockaddr*)&sa, sizeof(sa));

    while (1)
    {
        char buf[1024] = {0};

        std::cin >> buf;

        int n = sendto(fd, buf, strlen(buf), 0, (const struct sockaddr *)&sa, sizeof(sa));

        std::cout << "send: " << n << std::endl;
        std::cout << "no " << errno << ": " << strerror(errno) << std::endl;
    }

    return 0;
}
