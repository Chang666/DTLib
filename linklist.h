#ifndef LINKLIST_H
#define LINKLIST_H
#include "list.h"
#include "object.h"
#include "exception.h"
namespace DTLib {
    template <typename T>
    class LinkList:public List<T>
    {
    protected:
        struct Node:public Object
        {
            T value;
            Node * next;

        };
        //mutable Node m_header;//get函数 为const，增加mutable  头节点的问题：Test构造函数抛出异常实验
        mutable struct:public Object //改为匿名结构体,增加继承 :public Object,最后重新构建所有项目！！！！！！结果改变
        {
            char r[sizeof(T)];
            Node * next;

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
        LinkList()
        {
            m_header.next=NULL;
            m_length=0;
            m_current=NULL;
            m_steps=1;


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

//                    Node *cur=reinterpret_cast<Node*>(&m_header);//loule & 取地址可能改变值  头节点的问题Node *cur=&m_header更改


//                    for(int k=0;k<i;k++)
//                    {
//                        cur=cur->next;

//                    }
                    node->value=e;
                    node->next=cur->next;
                    cur->next=node;//cur=nodeXX
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
//                Node *cur=reinterpret_cast<Node*>(&m_header);// 头节点的问题Node *cur=&m_header更改

//                for(int k=0;k<i;k++)
//                {
//                    cur=cur->next;

//                }
                Node* todel=cur->next;

                cur->next=todel->next;

                if(m_current==todel)
                {
                    m_current=todel->next;
                }

                m_length--;//
                destroy(todel);//delete todel;
                //m_length--;//防止析构异常，应放在destroy之前

            }

            return ret;


        }
        bool set(int i,const T& e)  //O(n)
        {
            bool ret=(0<=i)&&(i<m_length);
            if(ret)
            {
                 Node *cur=positon(i);
//                Node *cur=reinterpret_cast<Node*>(&m_header);// 头节点的问题Node *cur=&m_header更改


//                for(int k=0;k<i;k++)
//                {
//                    cur=cur->next;

//                }

                cur->next->value=e;


            }

            return ret;

        }

        virtual T get(int i)const//为啥是虚函数？？？
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
//                Node *cur=reinterpret_cast<Node*>(&m_header);// 头节点的问题Node *cur=&m_header更改


//                for(int k=0;k<i;k++)
//                {
//                    cur=cur->next;

//                }

                e=cur->next->value;


            }

            return ret;

        }
        int find(const T& e)const       //O(n)
        {
            int ret=-1;
            Node *cur=reinterpret_cast<Node*>(&m_header);//loule & 取地址可能改变值  头节点的问题Node *cur=&m_header更改

            //Node *cur=reinterpret_cast<Node*>(&m_header);m_header->next;
            for(int k=0;k<m_length;k++)
            {
                cur=cur->next;
                if(cur->value==e)  //test23 error: no match for 'operator==' (operand types are 'Test' and 'const Test')
//T如果是类需要重载== ,每个类都要重载   在顶层类实现，让实验的类继承顶层类
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
            while(m_header.next)
            {
                Node* Todel=m_header.next;
                m_header.next=Todel->next;
                m_length--;//
                destroy(Todel);
            }
            //m_length=0;//析构如果出问题，有异常，程序跑不到这里,解决  m_length--;//
        }
        ~LinkList()  //O(n)
        {
            clear();
        }

    };

}

#endif // LINKLIST_H
