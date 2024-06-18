#ifndef STATICSTACK_H
#define STATICSTACK_H
#include "stack.h"
#include "exception.h"
//#include<iostream>
//using namespace std;
namespace DTLib {

template < typename T, int N >
class StaticStack:public stack<T>
{
protected:
T m_space[N];//栈存储空间，N为模板参数
int m_top; //栈顶标识
int m_size;//当前栈的大小
public:
StaticStack()
{
    m_top=-1;//=0;
    m_size=0;

}
int capacity()const//初始化成员变量
{
    return N;//N  m_size
}
void push(const T& e)
{
    //cout<<"aa"<<endl;
    if(m_size<N)
    {
        //m_top=(m_top+1)%N;
//        cout<<"aa"<<endl;
        m_space[m_top+1]=e;//异常安全，若有异常，不改变栈的状态
        m_top++;
        m_size++;//loule

    }
    else
    {
//        cout<<"bb"<<endl;
//        cout<<m_size<<endl;
//        cout<<N<<endl;
        THROW_EXCEPTION(InvalidOperationException,"no memory to push..");
    }

}
void pop()
{
    if(m_size>0)
    {

        m_top=m_top-1;
        m_size--;//loule

    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException,"invalid operation stack is empty..");
    }
}
 T top() const
{
     if(m_size>0)
     {
     return m_space[m_top];//-1
     }
     else
     {
         THROW_EXCEPTION(InvalidOperationException,"No element in current StaticStack ...");
     }

}
void clear()
 {
    m_top=-1;
    m_size=0;
 }
int size() const
{
    return m_size;
}
//~StaticStack()  // O(1)//loule
//    {
//        clear();
//    }


};


}

#endif // STATICSTACK_H
