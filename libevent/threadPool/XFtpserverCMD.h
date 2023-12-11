/*
 * @Author: FanNanqi
 * @Date: 2023-09-28 10:02:53
 * @LastEditTime: 2023-09-28 10:06:16
 * @FilePath: /vsgcc/libevent/threadPool/XFtpserverCMD.h
 * @Description:继承Task，作为fpt任务
 *
 */
#pragma once
#include "XTask.h"
class XFtpserverCMD : public XTask
{
private:
    /* data */
public:
    bool Init();
    XFtpserverCMD(/* args */);
    ~XFtpserverCMD();
};
