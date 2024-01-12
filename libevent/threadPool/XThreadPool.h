/*
 * @Author: FanNanqi
 * @Date: 2023-09-23 10:13:57
 * @LastEditTime: 2024-01-12 21:08:40
 * @FilePath: /vsgcc/libevent/threadPool/XThreadPool.h
 * @Description:
 *
 */
#pragma once
#include <vector>
#include "XFtpserverCMD.h"

class XThread;

class XThreadPool
{
private:
    // 在private中的构造函数的目的：不允许new，符合单例模式
    XThreadPool(/* args */);
    int threadCount = 0;
    int lastThread = -1;
    /**
     * @description: 线程池线程
     * @return {*}
     */
    std::vector<XThread *> threads;

public:
    /**
     * @description: 单例模式
     * @return {*}
     */
    static XThreadPool *Get()
    {
        static XThreadPool p;
        return &p;
    }

    /**
     * @description: 初始化所有线程并启动线程
     * @param {int} threadCount
     * @return {*}
     */
    void Init(int threadCount);

    /**
     * @description: 分发线程
     * @param {XTask} *task
     * @return {*}
     */
    void Dispatch(XTask *task);
    ~XThreadPool();
};
