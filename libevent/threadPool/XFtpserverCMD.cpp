/*
 * @Author: FanNanqi
 * @Date: 2023-09-28 10:06:04
 * @LastEditTime: 2023-10-02 22:43:38
 * @FilePath: /vsgcc/libevent/threadPool/XFtpserverCMD.cpp
 * @Description:
 *
 */
#include "XFtpserverCMD.h"
#include <iostream>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <string.h>
using namespace std;

/**
 * @description: bufevent的读回调函数，子线程 XThread event事件分发
 *             将在XThread::Main中调用
 * @param {bufferevent} *bev
 * @param {void} *ctx
 * @return {*}
 */

void EventCB(struct bufferevent *bev, short what, void *ctx)
{
    XFtpserverCMD *xft = (XFtpserverCMD *)ctx;
    // 如果对方网络断掉，或者机器死机有可能收不到该事件（超时事件）
    if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
    {
        cout << "BEV_EVENT_EOF|BEV_EVENT_ERROR" << endl;
        bufferevent_free(bev);
        delete xft;
    }
}
static void ReadCB(bufferevent *bev, void *ctx)
{
    XFtpserverCMD *xft = (XFtpserverCMD *)ctx;
    char data[1024] = {0};
    // for (;;)
    //{
    int len = bufferevent_read(bev, data, sizeof(data) - 1);
    if (len <= 0)
        return;
    // break;
    data[len] = '\0';
    cout << data << " thread_id=" << xft->thread_id << endl;
    if (strstr(data, "quit"))
    {
        bufferevent_free(bev);
        delete xft;
        // break;
    }
    //}
}

/**
 * @description: 初始化任务，运行在子线程中
 * @return {*}
 */
bool XFtpserverCMD::Init()
{
    cout << "XFtpserverCMD::Init()" << endl;
    // 监听socket bufferevent
    // base,socket
    bufferevent *bev = bufferevent_socket_new(base, this->sock, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, ReadCB, 0, EventCB, this);
    // 设置权限
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    timeval rt = {10, 0};
    bufferevent_set_timeouts(bev, &rt, 0);
    return true;
}

XFtpserverCMD::XFtpserverCMD()
{
}

XFtpserverCMD::~XFtpserverCMD()
{
}
