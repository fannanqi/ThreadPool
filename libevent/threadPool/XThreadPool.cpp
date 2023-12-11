/*
 * @Author: FanNanqi
 * @Date: 2023-09-23 10:55:22
 * @LastEditTime: 2023-09-28 18:17:28
 * @FilePath: /vsgcc/libevent/threadPool/XThreadPool.cpp
 * @Description:
 *
 */
#include "XThreadPool.h"
#include "XThread.h"
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;
XThreadPool::XThreadPool(/* args */)
{
}

void XThreadPool::Dispatch(XTask *task)
{
    // 轮询
    if (!task)
        return;
    int tid = (lastThread + 1) % threadCount;
    lastThread = tid;
    XThread *t = threads[tid];
    task->thread_id = tid;
    t->AddTask(task);
    // 激活线程
    t->Active();
}

XThreadPool::~XThreadPool()
{
}

void XThreadPool::Init(int threadCount)
{
    this->threadCount = threadCount;
    for (int i = 0; i < threadCount; ++i)
    {
        XThread *t = new XThread();
        t->id = i;
        cout << "create thread :" << i << endl;
        // 启动线程
        t->Start();
        threads.push_back(t);
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
