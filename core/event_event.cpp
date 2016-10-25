/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-10-10
 * Description:
 ******************************************************************************
 */
#include "event_event.h"


int Event::Init(int maxfds)
{
    Create(maxfds);

    maxfds_ = maxfds;
    nodes_ = new Node *[maxfds];

    return 0;
}

int Event::Free()
{
    Destroy();

    for (int i = 0; i < maxfds_; i++)
    {
        if (nodes_[i]) delete nodes_[i];
    }

    delete []nodes_;

    return 0;
}

int Event::Register(int fd, event_handler handler, void *ctx)
{
    Node *fdn;

    if (fd >= maxfds_) return -1;

    fdn = new Node;
    fdn->handler = handler;
    fdn->fd = fd;
    fdn->ctx = ctx;

    nodes_[fd] = fdn;

    return 0;
}

int Event::Unregister(int fd)
{
    if (fd >= maxfds_) return -1;

    delete nodes_[fd];
    nodes_[fd] = NULL;

    return 0;
}

int Event::Loop(int timeout_ms, int max_loop_cnt)
{
    int n;
    int ev_ndx = -1;
    int revents;
    int fd;
    Node *node;

    n = Poll(timeout_ms);

    while (n-- > 0 && max_loop_cnt-- > 0)
    {
        ev_ndx = GetNext(ev_ndx);
        revents = GetEvent(ev_ndx);
        fd = GetFd(ev_ndx);
        node = nodes_[fd];

        node->handler(fd, node->ctx, revents);
    }

    return n;
}
