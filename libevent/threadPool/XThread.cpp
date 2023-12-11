/*
 * @Author: FanNanqi
 * @Date: 2023-09-23 11:01:26
 * @LastEditTime: 2023-09-28 16:42:54
 * @FilePath: /vsgcc/libevent/threadPool/XThread.cpp
 * @Description:
 *
 */
#include "XThread.h"
#include <thread>
#include <iostream>
#include "XTask.h"
#ifdef _WIN32
#else
#include <unistd.h>
#endif

using namespace std;

// 激活线程任务的回调函数，event的回调函数
static void NotifyCB(evutil_socket_t fd, short what, void *arg)
{
    XThread *t = (XThread *)arg;
    t->Notify(fd, what);
}

void XThread::Start()
{
    Setup();

    // 启动线程
    thread th(&XThread::Main, this);

    // 断开与主线程联系
    th.detach();
}
void XThread::Main()
{
    cout << id << "XThread::Main() begin" << endl;
    event_base_dispatch(this->base);
    event_base_free(this->base);
    cout << id << "XThread::Main() end" << endl;
}
bool XThread::Setup()
{
    // windows用配对socket linux用管道
#ifdef _WIN32
    // 创建一个socketpair，可以互相通信:fds[0]读,fds[1]写
    evutil_socket_t fds[32];

    if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0)
    {
    }
    // 设置成非阻塞
    evutil - evutil_make_socket_nonblocking(fds[0]);
    evutil - evutil_make_socket_nonblocking(fds[1]);
#else
    // Unix----创建管道
    // 不能用send recv读取read write
    int fds[2];
    if (pipe(fds) == -1)
    {
        cerr << "pipe failed!" << endl;
        return false;
    }
#endif
    // 将读取绑定到event事件中，写入要保存
    notify_send_fd = fds[1];

    // 创建libevent上下文
    event_config *ev_config = event_config_new();
    event_config_set_flag(ev_config, EVENT_BASE_FLAG_NOLOCK);
    this->base = event_base_new_with_config(ev_config);
    event_config_free(ev_config);
    if (!base)
    {
        cerr << "event_base_new_with_config failed in thread!" << endl;
        return false;
    }

    // 添加管道监听事件，用于激活线程执行任务
    event *ev = event_new(base, fds[0], EV_READ | EV_PERSIST, NotifyCB, this);
    if (!ev)
    {
        cerr << "event_new failed!" << endl;
        return false;
    }
    event_add(ev, 0);
    return true;
}
void XThread::Notify(evutil_socket_t fd, short what)
{
    // 水平触发 只要没有接受完成，会再次进来
    char buf[2] = {0};
#ifdef _WIN32
    int re = recv(fd, buf, 1, 0);
#else
    // Unix是管道不能用recv
    int re = read(fd, buf, 1);
#endif
    if (re <= 0)
        return;
    cout << id << " thread" << buf << endl;

    // 获取任务，并初始化任务(有锁队列)
    XTask *task = NULL;
    task_mutex.lock();
    if (tasks.empty())
    {
        task_mutex.unlock();
        return;
    }
    // 先进先出
    task = tasks.front();
    tasks.pop_front();
    task_mutex.unlock();
    // 任务执行
    task->Init();
}
void XThread::Active()
{
#ifdef _WIN32
    int re = send(this->notify_send_fd, "c", 1, 0);
#else
    // Unix是管道不能用write,
    int re = write(this->notify_send_fd, "c", 1);
#endif
    if (re <= 0)
    {
        cerr << "XThread::Active() failed!" << endl;
    }
}
void XThread::AddTask(XTask *t)
{
    if (!t)
        return;
    // 将线程的base下发传递给任务的base
    t->base = this->base;
    task_mutex.lock();
    // 添加任务
    tasks.push_back(t);
    task_mutex.unlock();
}
XThread::XThread(/* args */)
{
    cout << "构造函数的线程id" << std::this_thread::get_id() << endl;
}

XThread::~XThread()
{
    cout << "析构函数的线程id" << std::this_thread::get_id() << endl;
}