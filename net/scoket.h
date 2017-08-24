/*
 ******************************************************************************
 * Copyright (c) 2016 Tencent Inc. All rights reserved
 * Author: markwei@tencent.com
 * Date: 2016-09-11
 * Description: 对epoll模型进行了简单封装
 ******************************************************************************
 */
#ifndef SOCKET_H_
#define SOCKET_H_

class Socket
{
public:
    Socket();
    ~Socket();


private:
    int socket;
};


#endif
