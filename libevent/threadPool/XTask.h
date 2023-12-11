/*
 * @Author: FanNanqi
 * @Date: 2023-09-26 23:30:39
 * @LastEditTime: 2023-09-28 11:09:00
 * @FilePath: /vsgcc/libevent/threadPool/XTask.h
 * @Description:
 *
 */
/*
 * @Author: FanNanqi
 * @Date: 2023-09-26 23:30:39
 * @LastEditTime: 2023-09-28 11:05:49
 * @FilePath: /vsgcc/libevent/threadPool/XTask.h
 * @Description:作为任务的父类
 *
 */
#pragma once
class XTask
{
private:
    /* data */
public:
    //
    struct event_base *base = 0;

    //
    int sock = 0;

    // 线程id号
    int thread_id = 0;

    // 初始化任务
    virtual bool Init() = 0;
    XTask(/* args */);
    ~XTask();
};
