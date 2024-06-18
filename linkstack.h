#ifndef LINKSTACK_H
#define LINKSTACK_H
#include"stack.h"
#include"linklist.h"
namespace DTLib {
template < typename T >
class LinkStack:public stack<T>
{
protected:
LinkList<T> m_list;
public:


void push(const T& e)
{
    m_list.insert(0,e);

}
void pop()
{
    if(m_list.length()>0)
    {
        m_list.remove(0);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException,"current stack is null...");
    }
}
 T top() const
{
     if(m_list.length()>0)
     {
         return m_list.get(0);
     }
     else
     {
         THROW_EXCEPTION(InvalidOperationException,"current stack is null...");
     }


}
void clear()
 {
    m_list.clear();
 }
int size() const
{
    return m_list.length();
}



};


}

#endif // LINKSTACK_H
