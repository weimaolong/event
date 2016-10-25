/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-10-10
 * Description:
 ******************************************************************************
 */
#ifndef EVENT_FACTORY_H_
#define EVENT_FACTORY_H_

#include "event_epoll.h"
#include "event_select.h"


class EventFactory
{
public:
    static Event *Create(const char *type)
    {
        if (type == "epoll")
            return new Epoll;

        if (type == "select")
            return new Select;

        return NULL;
    }
};

#endif /*EVENT_FACTORY_H_*/
