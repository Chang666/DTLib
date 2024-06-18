#ifndef CIRCLELIST_H
#define CIRCLELIST_H
#include "linklist.h"
namespace DTLib
{

    template <typename T>
    class CircleList:public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;//定义node
        Node* Last() const  //O(n)
        {
            return this->positon(this->m_length-1)->next;//this->
        }

        void Last_to_First() const  //O(n)
        {
            Last()->next=this->m_header.next;//this->m_header->next  XXX
        }

        int mod(int i) const//O(1)
        {
            return (this->m_length==0?0:i%(this->m_length));//没有加一
        }


    public:


        bool insert(int i,const T& e)  //O(n)
        {

            bool ret=true;
            i=i%(this->m_length+1);//计算插入后i的位置
            ret=LinkList<T>::insert(i,e);//调用单链表的insert函数
            if(ret&&(i==0))
            {
                Last_to_First();//首尾相连
            }

            return ret;
        }
        bool insert(const T& e)//O(n)
        {
            return insert(this->m_length,e);
        }
        bool remove(int i)   //O(n)
        {
            bool ret=true;
            i=mod(i);// 由于 m_length 等价于删除0 号？？？ m_length-1 0  对的
            if(i==0)
            {
                Node* todel=this->m_header.next;//->next
                if(todel!=NULL)//?????
                {
                    this->m_header.next=todel->next;//由于头节点已经指向下标1的节点了，实际已经有新的循环链表了，且数目少1  m_header->next XXX
                    this->m_length--;//应该放在这里
                    if(this->m_length>0)//loule
                    {
                        Last_to_First();//漏洞，有些情况不需要执行，例如，没有节点的情况
                        //遗漏游标指向要删掉的节点
                        if(this->m_current==todel)
                        {
                            this->m_current=todel->next;//this->m_current->next;
                        }

                    }
                    else//漏了
                    {
                        this->m_header.next=NULL;//是否可以不写 ,如果原来只有一个节点，todel->next就是自己，而不是NULL
                        this->m_current=NULL;



                    }

                    this->destroy(todel);
                    //this->m_length--;//不对

                }
                else
                {
                    //不用抛异常，直接false
                    ret=false;
                }

            }
            else
            {
                ret=LinkList<T>::remove(i);

            }

            return ret;


        }

        //继续，set get get  find clear 不好的例子 ok的例子 游标相关的函数 析构
        bool set(int i,const T& e)  //O(n)
        {


            return LinkList<T>::set(mod(i),e);//调用父类的函数

        }

        T get(int i)const//O(n)
        {

            return LinkList<T>::get(mod(i));//调用父类的函数

        }

        bool get(int i,const T& e)const  //O(n)
        {
            return LinkList<T>::get(mod(i),e);

        }
        int find(const T& e)const       //O(n)
        {
            int ret=-1;
    //        Last()->next=NULL;
    //        ret=LinkList<T>::find(e);//内部有cur->value==e  ，T如果是类，有可能抛出异常，导致循环链表状态改变
    //        Last_to_First();
            Node* slider=this->m_header.next;
            for(int i=0;i<this->m_length;i++)
            {
                if(slider->value==e)
                {
                    ret=i;
                    break;
                }

                    slider=slider->next;

            }


            return ret;

        }





        void clear()   //O(n)
        {
    //        if(this->m_length>0)
    //        {
    //            Last()->next=NULL;
    //            LinkList<T>::clear();//若发生异常，链表状态改变
    //        }

            while(this->m_length>1)
            {
                LinkList<T>::remove(1);//0的话有大量移动，销量低
               // this->m_length--;//remove本身内部有length--
            }
            if(this->m_length==1)//loule
            {
                Node* Todel=this->m_header.next;//若没来没有节点,以下5行不执行 //->next

                this->m_header.next=NULL;//为空后，长度归零，//->next
                this->m_length--;
                this->m_current=NULL;
                this->destroy(Todel);//this-> loule error: 'destroy' was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]


                //this->m_length--; xxxx

            }


        }
        //两个遍历相关函数
        bool move(int i,int step=1)//O(n)
        {

            return LinkList<T>::move(mod(i),step);//

        }
        bool end()//O(1)
        {
            return (this->m_length==0||this->m_current==NULL);//这两种情况下不用遍历
        }
        T current()
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
        ~CircleList()  //O(n)
        {
            clear();
        }


    };

}

#endif // CIRCLELIST_H
