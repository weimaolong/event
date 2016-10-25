/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-10-10
 * Description: 对select模型进行了简单封装
 ******************************************************************************
 */
#ifndef EVENT_SELECT_H_
#define EVENT_SELECT_H_

#include <sys/select.h>
#include "event_event.h"


class Select : public Event
{
public:
    Select() {}
    virtual ~Select() {}

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
    int select_max_fd_;

    fd_set select_set_rfds_;
    fd_set select_set_wfds_;
    fd_set select_set_efds_;

    fd_set select_rfds_;
    fd_set select_wfds_;
    fd_set select_efds_;
};

#endif /*EVENT_SELECT_H_*/
