#ifndef STATICQUEUE_H
#define STATICQUEUE_H
#include "queue.h"
#include"exception.h"
namespace DTLib
{
template < typename T, int N >
class StaticQueue : public Queue<T>
{
protected:
T m_space[N]; //队列存储空间，N 为模板参数
int m_front; //队头标识(包含成员)
int m_rear; //队尾标识（不包含成员）
int m_length;//当前队列的长度
public:
StaticQueue()
{
    m_front=0;
    m_rear=0;
    m_length=0;
}
int capacity()const//初始化成员变量
{
    return N;//m_length
}
void add(const T& e)   //O(1)
{
    if(m_length<N)
    {
        m_space[m_rear]=e;
        m_rear=(m_rear+1)%N;
        m_length++;

    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException,"queue is full No memory to add...");

    }

}
void remove()   //O(1)
{
     if(m_length>0)
     {
         m_front=(m_front+1)%N;
         m_length--;
     }
     else
     {
         THROW_EXCEPTION(InvalidOperationException,"queue is empty No value to remove...");

     }

}
T front() const  //O(1)
{
    if(m_length>0)
    {
    return m_space[m_front];
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException,"queue is empty ...");

    }
}
void clear()  //O(1)
{
    m_front=0;
    m_rear=0;
    m_length=0;
}
int length() const  //O(1)
{
    return m_length;
}
//~StaticQueue(){
//    clear();

//}






};


}
#endif // STATICQUEUE_H
