/*
 * @Author: FanNanqi
 * @Date: 2023-09-23 10:59:44
 * @LastEditTime: 2023-09-28 10:43:37
 * @FilePath: /vsgcc/libevent/threadPool/XThread.h
 * @Description:每个线程一个event_base
 *
 */
#pragma once
#include <event2/event.h>
#include <list>
#include <mutex>
class XTask;
class XThread
{
public:
    /**
     * @description: 启动线程
     * @return {*}
     */
    void Start();

    /**
     * @description: 线程入口函数
     * @return {*}
     */
    void Main();

    /**
     * @description: 安装线程，初始化event_base和管道事件用于激活
     * @return {*}
     */
    bool Setup();

    /**
     * @description: 收到主线程发出的激活消息（线程池的分发）
     * @param {evutil_socket_t} fd
     * @param {short} what
     * @return {*}
     */
    void Notify(evutil_socket_t fd, short what);

    /**
     * @description: 线程激活
     * @return {*}
     */
    void Active();

    /**
     * @description: 线程添加任务，一个线程可以同时处理多个任务，共用一个event_base
     * @return {*}
     */
    void AddTask(XTask *t);

    XThread(/* args */);
    ~XThread();

    // 线程编号
    int id = 0;

private:
    int notify_send_fd = 0;
    struct event_base *base = 0;

    // 任务列表
    std::list<XTask *> tasks;

    // 线程安全 互斥量
    std::mutex task_mutex;
};
