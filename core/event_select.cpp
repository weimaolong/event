/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-10-10
 * Description: 对select模型进行了简单封装
 ******************************************************************************
 */
#include "event_select.h"


int Select::Create(int maxfds)
{
    select_max_fd_ = -1;

    FD_ZERO(&select_set_rfds_);
    FD_ZERO(&select_set_wfds_);
    FD_ZERO(&select_set_efds_);

    FD_ZERO(&select_set_rfds_);
    FD_ZERO(&select_set_wfds_);
    FD_ZERO(&select_set_efds_);

    return 0;
}

int Select::Destroy()
{
    return 0;
}

int Select::Set(int fd, int events)
{
    if (fd >= maxfds_) return -1;

    FD_CLR(fd, &select_set_rfds_);
    FD_CLR(fd, &select_set_wfds_);
    FD_CLR(fd, &select_set_efds_);

    if (events & EVENT_IN)  FD_SET(fd, &select_set_rfds_);
    if (events & EVENT_OUT) FD_SET(fd, &select_set_wfds_);

    FD_SET(fd, &select_set_efds_);

    if (fd > select_max_fd_)
    {
        select_max_fd_ = fd;
    }

    return 0;
}

int Select::Del(int fd)
{
    FD_CLR(fd, &select_set_rfds_);
    FD_CLR(fd, &select_set_wfds_);
    FD_CLR(fd, &select_set_efds_);

    return 0;
}

int Select::Poll(int timeout_ms)
{
    struct timeval tv;

    tv.tv_sec =  timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    select_rfds_ = select_set_rfds_;
    select_wfds_ = select_set_wfds_;
    select_efds_ = select_set_efds_;

    return select(select_max_fd_ + 1, &select_rfds_, &select_wfds_, &select_efds_, &tv);
}

int Select::GetNext(int ndx)
{
    int i;

    i = (ndx < 0) ? 0 : ndx + 1;

    for (; i < select_max_fd_ + 1; ++i)
    {
        if (FD_ISSET(i, &select_rfds_)) return i;
        if (FD_ISSET(i, &select_wfds_)) return i;
        if (FD_ISSET(i, &select_efds_)) return i;
    }

    return -1;
}

int Select::GetEvent(int ndx)
{
    int events = 0;

    if (FD_ISSET(ndx, &select_rfds_))   events |= EVENT_IN;
    if (FD_ISSET(ndx, &select_wfds_))   events |= EVENT_OUT;
    if (FD_ISSET(ndx, &select_efds_))   events |= EVENT_ERR;

    return events;
}

int Select::GetFd(int ndx)
{
    return ndx;
}
