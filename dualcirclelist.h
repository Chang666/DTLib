#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H
#include"LinuxList.h"
#include"duallinklist.h"
#include"exception.h"
namespace DTLib {
template <typename T>
class DualCircleList:public DualLinkList<T>
{
protected:
    struct Node
    {
        list_head head;
        T value;
    };
    list_head m_header;
    list_head * m_current;
    list_head * position(int i) const  //返回值类型 不是链表的节点指针类型
    {
        list_head* ret=const_cast<list_head*>(&m_header);//const函数内部要取地址，只能类型转换
        for(int k=0;k<i;k++)
        {
            ret=ret->next;
        }
        return ret;
    }
    int mod(int i)const
    {
        return (this->m_length!=0?(i%(this->m_length)):0);
    }
public:
    DualCircleList()
    {
        this->m_length=0;
        this->m_current=NULL;
        this->m_steps=1;

        INIT_LIST_HEAD(&m_header);
    }
    bool insert(const T &e)
    {
        return(this->m_length,e);

    }
    bool insert(int i,const T& e)
    {
        bool ret=true;
        //i=mod(i);XXX
        Node* node=new Node();
        i=i%(1+this->m_length);
        if(node!=NULL)
        {
            node->value=e;
            list_add_tail(&node->head,position(i)->next);//类型转换  node,position(i)->next)  &node->head,position(i)->next)
               this->m_length++;//漏了！！！
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to new element..");
        }

    }
    bool remove(int i)
    {
        bool ret=true;
        i=mod(i);
        ret=ret&&((i>=0)&&(i<this->m_length));
        if(ret)
        {
             list_head* todel=position(i)->next;//Node* XXX
            if(m_current==todel)
            {
                m_current=todel->next;
            }
            list_del(todel);
            this->m_length--;
            delete list_entry(todel,Node,head);//不能直接 delete todel

        }
    }

    bool set(int i,const T& e)  //O(n)
    {
        bool ret=true;
        i=mod(i);
        ret=ret&&(0<=i)&&(i<this->m_length);
        if(ret)
        {
             list_head *cur=this->position(i);//Node *cur=this->position(i);
             //cur->next->value=e;
             list_entry(cur->next,Node,head)->value=e;//偏移量
        }



        return ret;

    }

    T get(int i)const
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
//        bool ret = true;

//                i = mod(i);//mod函数改为const函数

//                ret = ((0 <= i) && (i < this->m_length));

//                if (ret)
//                {
//                   e = list_entry(position(i)->next, Node, head)->value;
//                }

               // return ret;
        bool ret=true;
        i=mod(i);
        ret=(0<=i)&&(i<this->m_length);
        if(ret)
        {
             //list_head *cur=position(i);


           // e=cur->next->value;
            e=list_entry(position(i)->next,Node,head)->value;


        }

        return ret;

    }
    int find(const T& e)const
    {
        int ret=-1;
        int i=0;
        list_head* slider=NULL;
        list_for_each(slider,(&m_header))//(&m_header)->next
        {
            //i++;
            if(list_entry(slider,Node,head)->value==e)
            {
                ret=i;
                break;

            }
            i++;

        }

        return ret;
    }
    int length()
    {
        return this->m_length;
    }

    void clear()
    {
        while (length()>0) {
            remove(0);

        }
    }
    bool move(int i,int step=1)
    {
        bool ret=true;
        i=mod(i);
        ret=ret&&(0<=i)&&(i<this->m_length)&&(step>0);
        if(ret)
        {
            m_current=position(i)->next;//头节点的value为空，往后移动
            this->m_steps=step;

        }
        return ret;

    }
    bool end()
    {
        return (m_current==NULL)||(this->length()==0);
    }
    T current()
    {
        if(!end())//loule
        {
            //return m_current->value;//list_entry(cur->next,Node,head)
            return list_entry(m_current,Node,head)->value;

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"operation is invalid...");

        }
    }
    bool next()//跳过头节点
    {


        int i=0;
        while(i<this->m_steps&&!(end()))
        {
            if(m_current==&m_header)
            {
                m_current=m_current->next;
            }
            else
            {
                m_current=m_current->next;

                i++;

            }

        }
        if(m_current==&m_header)
        {
            m_current=m_current->next;
        }

        return (i==this->m_steps);//游标有没有走满


    }
    bool pre()//新增
    {


        int i=0;
        while(i<this->m_steps&&!(end()))
        {
            if(m_current==&m_header)
            {
                m_current=m_current->prev;
            }
            else
            {
                m_current=m_current->prev;

                i++;

            }

        }
        if(m_current==&m_header)
        {
            m_current=m_current->prev;
        }
        return (i==this->m_steps);//游标有没有走满


    }
    ~DualCircleList()
    {
        clear();
    }
};

}

#endif // DUALCIRCLELIST_H
