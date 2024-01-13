/*
 * @Author: fannanqi 1773252187@qq.com
 * @Date: 2023-12-21 19:41:53
 * @LastEditors: fannanqi 1773252187@qq.com
 * @LastEditTime: 2024-01-13 11:58:52
 * @FilePath: /vsgcc/test.cpp
 * @Description: 关于多态中如何确保全部析构，1、在父类中析构函数定义为virtual，2、将父类定义为抽象类
 */
#include <iostream>
using namespace std;
class A
{
public:
    A()
    {
        cout << "A create\n";
    }
    virtual void fun()
    {
        cout << "A fun\n";
    }
    virtual ~A()
    {
        cout << "A delete\n";
    }
};
class B : public A
{
public:
    B()
    {
        cout << "B create\n";
    }
    void fun()
    {
        cout << "B fun\n";
    }
    ~B()
    {
        cout << "B delete\n";
    }
};
int main(void)
{
    A *tmp = new B();
    delete tmp;
    getchar();
    return 0;
}
