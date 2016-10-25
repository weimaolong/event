/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-09-11
 * Description: 对epoll模型进行了简单封装
 ******************************************************************************
 */
#include <unistd.h>
#include "event_epoll.h"


int Epoll::Create(int maxfds)
{
    epoll_fd_ = epoll_create(maxfds);

    if (-1 == epoll_fd_) return -1;

    epoll_events_ = new epoll_event[maxfds];

    return 0;
}

int Epoll::Destroy()
{
    close(epoll_fd_);

    delete epoll_events_;

    return 0;
}

int Epoll::Set(int fd, int events)
{
    struct epoll_event ep = { 0, 0 };

    if (fd >= maxfds_) return -1;

    if (events & EVENT_IN)  ep.events |= EPOLLIN;
    if (events & EVENT_OUT) ep.events |= EPOLLOUT;

    ep.events |= EPOLLERR;

    ep.data.fd = fd;

    if (0 != epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ep))
    {
        return -1;
    }

    return 0;
}

int Epoll::Del(int fd)
{
    struct epoll_event ep;

    if (0 != epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &ep))
    {
        return -1;
    }

    return 0;
}

int Epoll::Poll(int timeout_ms)
{
    return epoll_wait(epoll_fd_, epoll_events_, maxfds_, timeout_ms);
}

int Epoll::GetNext(int ndx)
{
    return ndx < 0 ? 0 : ndx + 1;
}

int Epoll::GetEvent(int ndx)
{
    int events = 0;
    int e;

    e = epoll_events_[ndx].events;

    if (e & EPOLLIN)     events |= EVENT_IN;
    if (e & EPOLLOUT)    events |= EVENT_OUT;
    if (e & EPOLLERR)    events |= EVENT_ERR;

    return events;
}

int Epoll::GetFd(int ndx)
{
    return epoll_events_[ndx].data.fd;
}
