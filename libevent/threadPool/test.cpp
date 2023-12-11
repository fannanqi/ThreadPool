/*
 * @Author: FanNanqi
 * @Date: 2023-10-05 23:25:06
 * @LastEditTime: 2023-10-06 21:20:53
 * @FilePath: /vsgcc/libevent/threadPool/test.cpp
 * @Description:
 *
 */
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
using namespace std;

class HasPtr
{
public:
    // 默认构造函数
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0)
    {
    }

    // 拷贝构造函数
    HasPtr(const HasPtr &data) : ps(new string(*(data.ps))), i(data.i)
    {
    }

    // 移动构造函数
    HasPtr(HasPtr &&rhs) noexcept : ps(rhs.ps), i(rhs.i)
    {
        rhs.ps = nullptr;
        rhs.i = 0;
    }

    // 析构函数
    ~HasPtr() { delete ps; } // 释放HasPtr类对象占用的资源。

private:
    std::string *ps;
    int i;
};

int main()
{
    HasPtr data1("123");
    HasPtr data2 = std::move(data1); // 移动语义
    HasPtr data3 = data2;            // 拷贝语义
}
// 这个单步调试，看看会不会有什么问题