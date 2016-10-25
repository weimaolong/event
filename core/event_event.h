/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-10-10
 * Description:
 ******************************************************************************
 */
#ifndef EVENT_EVENT_H_
#define EVENT_EVENT_H_

#include <functional>


class Event
{
public:
    typedef std::function<void (int fd, void *ctx, int revents)> event_handler;

    struct Node
    {
        Node(): fd(-1), ctx(NULL), handler(NULL) {}
        int fd;
        void *ctx;
        event_handler handler;
    };

    enum Type
    {
        EVENT_IN  = 1 << 0,
        EVENT_OUT = 1 << 1,
        EVENT_ERR = 1 << 2,
    };

public:
    Event(): maxfds_(-1), nodes_(NULL) {}
    virtual ~Event() {}

public:
    int Init(int maxfds);
    int Free();
    int Register(int fd, event_handler handler, void *ctx);
    int Unregister(int fd);
    int Loop(int timeout_ms, int max_loop_cnt);

    virtual int Set(int fd, int events) = 0;
    virtual int Del(int fd) = 0;

protected:
    virtual int Create(int maxfds) = 0;
    virtual int Destroy() = 0;
    virtual int Poll(int timeout_ms) = 0;
    virtual int GetNext(int ndx) = 0;
    virtual int GetEvent(int ndx) = 0;
    virtual int GetFd(int ndx) = 0;

protected:
    int maxfds_;
    Node **nodes_;
};

#endif /*EVENT_EVENT_H_*/
