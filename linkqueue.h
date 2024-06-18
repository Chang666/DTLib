#ifndef LINKQUEUE_H
#define LINKQUEUE_H
//#include"linklist.h"
#include"exception.h"
#include"linuxlist.h"
namespace DTLib {
template < typename T>//, int N
class LinkQueue:public LinkList<T>
{
protected:

    //LinkList<T> m_list;case1 销率低
    struct Node:public Object
    {
        list_head head;
        T value;

    };
    list_head m_header;
    int m_length;
public:
    LinkQueue()//O(1)
    {
        m_length=0;
        INIT_LIST_HEAD(&m_header);//

    }
    //int capacity()const//初始化成员变量
    //{
    //    return N;//m_length
    //}
    void add(const T& e)   //O(n)   O(1)
    {
        //m_list.insert(e);  O(n)
        Node * node=new Node();
        node->value=e;
        if(node!=NULL)
        {
            list_add_tail(&node->head,&m_header);//O(1)
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to add new node...");
        }

    }
    void remove()  //O(1)
    {
//         if(m_list.length()>0)
//         {
//             m_list.remove(0);//删除首届点
//         }
         if(m_length>0)
         {
             //m_list.remove(0);//删除首届点
             list_head* todel=m_header.next;
             list_del(todel);//O(1)
             m_length--;
             delete list_entry(todel,Node,head);

         }
         else
         {
             THROW_EXCEPTION(InvalidOperationException,"queue is empty No value to remove...");

         }

    }
    T front() const   //O(1)
    {
        if(m_length>0)//(m_list.length()>0)
        {
        return list_entry(m_header.next,Node,head)->value;//m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"queue is empty ...");

        }
    }
    void clear()   //O(n)
    {
        //m_list.clear();
        while(length()>0)
        {
            remove();
        }
    }
    int length() const  //O(1)
    {
        return this->m_length;//m_list.length();
    }
    ~LinkQueue()
    {
        clear();
    }

};

}

#endif // LINKQUEUE_H
