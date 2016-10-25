/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-09-11
 * Description: 对epoll模型进行了简单封装
 ******************************************************************************
 */
#ifndef EVENT_EPOLL_H_
#define EVENT_EPOLL_H_

#include <sys/epoll.h>
#include "event_event.h"


class Epoll : public Event
{
public:
    Epoll() : epoll_fd_(-1), epoll_events_(NULL) {}
    virtual ~Epoll() {}

public:
    int Create(int maxfds);
    int Destroy();
    int Set(int fd, int events);
    int Del(int fd);
    int Poll(int timeout_ms);
    int GetNext(int ndx);
    int GetEvent(int ndx);
    int GetFd(int ndx);

private:
    int epoll_fd_;
    epoll_event *epoll_events_;
};

#endif /*EVENT_EPOLL_H_*/
