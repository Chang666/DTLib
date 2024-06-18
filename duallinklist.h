#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H
#include "list.h"
#include "exception.h"
namespace DTLib {

template <typename T>
class DualLinkList:public List<T>
{
protected:
    struct Node:public Object
    {
        T value;
        Node * next;
        Node * pre;

    };
    //mutable Node m_header;//get函数 为const，增加mutable  头节点的问题：Test构造函数抛出异常实验
    mutable struct:public Object //改为匿名结构体,增加继承 :public Object,最后重新构建所有项目！！！！！！结果改变
    {
        char r[sizeof(T)];
        Node * next;
        Node * pre;

    }m_header;

    Node* positon(int i) const      //O(n)
    {
        Node *cur=reinterpret_cast<Node*>(&m_header);//loule & 取地址可能改变值  头节点的问题Node *cur=&m_header更改


        for(int k=0;k<i;k++)
        {
            cur=cur->next;

        }
        return cur;

    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* p)//子类重写此函数
    {
        delete p;
    }

    Node* m_current;//游标
    int m_steps;
    int m_length;

public:
    DualLinkList()
    {
        m_header.next=NULL;
        m_header.pre=NULL;
        m_length=0;
        m_current=NULL;
        m_steps=1;
    }

    bool insert(const T& e)
    {
        return insert(m_length,e);
    }
    bool insert(int i,const T& e)  //O(n)
    {

        bool ret=(0<=i)&&(i<=m_length);
        if(ret)
        {
            Node* node=create();
            if(node!=NULL)
            {
                Node *cur=positon(i);
                Node *next=cur->next;

                node->value=e;
                node->next=next;
                if(cur!=reinterpret_cast<Node*>(&this->m_header))//强制类型转换？？哪种
                {
                    node->pre=cur;//如果cur是头节点呢？？漏了

                }
                else {
                    node->pre=NULL;
                }

                cur->next=node;//cur=nodeXX
                if(next!=NULL)
                {
                    next->pre=node;//如果next是null呢？？漏了

                }


                m_length++;

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to insert object...");

            }

        }

        return ret;
    }
    bool remove(int i)   //O(n)
    {
        bool ret=(0<=i)&&(i<m_length);
        if(ret)
        {
             Node *cur=positon(i);


            Node* todel=cur->next;

            Node *next=todel->next;//增加
            if(m_current==todel)//应该放到前面去
            {
                m_current=todel->next;
            }

            cur->next=next;//todel->
            if(next!=NULL)//增加
            {
//                if(cur!=reinterpret_cast<Node*>(&m_header))//例子漏了，多次一举了，若是头节点，todel->pre就直接是NULL了，不需要判断
//                {
//                    next->pre=todel->pre;//cur;

//                }

//                else
//                {
//                    next->pre=NULL;

//                }
                next->pre=todel->pre;

            }
            m_length--;//

//            if(m_current==todel)//应该放到前面去，值被改变了
//            {
//                m_current=todel->next;
//            }


            destroy(todel);//delete todel;


        }

        return ret;


    }
    bool set(int i,const T& e)  //O(n)
    {
        bool ret=(0<=i)&&(i<m_length);
        if(ret)
        {
             Node *cur=positon(i);
             cur->next->value=e;
        }



        return ret;

    }

    virtual T get(int i)const  //为啥是虚函数？？？子类调用时，需要重写，返回出来的是子类
    {
        T e;
        if(get(i,e))
        {
            return e;
        }
        else
        {
             THROW_EXCEPTION(IndexOutOfBoundsException,"i is invild...");

        }


    }

    bool get(int i,T& e)const  //O(n)
    {
        bool ret=(0<=i)&&(i<m_length);
        if(ret)
        {
             Node *cur=positon(i);


            e=cur->next->value;


        }

        return ret;

    }
    int find(const T& e)const       //O(n)
    {
        int ret=-1;
        Node *cur=reinterpret_cast<Node*>(&m_header);//loule & 取地址可能改变值  头节点的问题Node *cur=&m_header更改


        for(int k=0;k<m_length;k++)
        {
            cur=cur->next;
            if(cur->value==e)
            {
                ret=k;
                break;
            }


        }


        return ret;

    }

    int length()const  //O(1)
    {
        return m_length;
    }
    void clear()   //O(n)
    {
        while(m_length>0)
        {
            remove(0);
        }

    }
    virtual bool move(int i,int step=1)
    {
        bool ret=(0<=i)&&(i<m_length)&&(step>0);
        if(ret)
        {
            m_current=positon(i)->next;//头节点的value为空，往后移动
            m_steps=step;

        }
        return ret;

    }
    virtual bool end()
    {
        return (m_current==NULL);
    }
    virtual T current()
    {
        if(!end())//loule
        {
            return m_current->value;

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"operation is invalid...");

        }
    }
    virtual bool next()
    {


        int i=0;
        while(i<m_steps)
        {
            if(end())break;
            m_current=m_current->next;

            i++;
        }
        return (i==m_steps);//游标有没有走满


    }
    virtual bool pre()//新增
    {


        int i=0;
        while(i<m_steps)
        {
            if(end())break;
            m_current=m_current->pre;

            i++;
        }
        return (i==m_steps);//游标有没有走满


    }
    ~DualLinkList()
    {
        clear();
    }

};

}

#endif // DUALLINKLIST_H
