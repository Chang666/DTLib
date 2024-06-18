#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H
#include "linklist.h"
namespace DTLib {
//文件加入主函数头文件，再编译！！！！
    template <typename T,int N>
    class StaticLinkList:public LinkList<T>//<T>
    {
//        LinkList<T>::Node
//        typename DTLib::LinkList<T>::Node

    protected:
        typedef typename DTLib::LinkList<T>::Node Node;
        class SNode:public Node
        {
        public:
            void* operator new(unsigned int size,void * loc)//XX:void *operator new(int size,SNode* loc)
            {
                //???zenmexie
                (void)size;//注释掉此行，并删掉形参 unsigned int size, 也可以
                return loc;
            }
//            void operator delete(void* p)
//            {
//                de
//            }
        };
        unsigned char m_spaces[sizeof(SNode)*N];//sizeof(T) ?unsigned char m_spaces[sizeof(Node)*N]?Node内部与T有关系  zz
        int m_used[N];


        Node* create()//Node* T*???
        {
            SNode* ret=NULL;//zz
            //chongzai new
            for(int i=0;i<N;i++)
            {
                if(!m_used[i])//没用过的
                {
                    ret=reinterpret_cast<SNode*>(m_spaces)+i;//zz
                    //T可能是一个类，类需要构造函数，这里不涉及 ，需要构造在指定的地址上，子类重载new  zz位置改为 SNode
                    ret=new(ret) SNode();//重载new

                    m_used[i]=1;
                    break;//loule

                }
            }
             return ret;

        }
//        void * operator new(int size,T* loc)
//        {

//        }
        void destroy(Node* mp)
        {
            Node* sp=reinterpret_cast<SNode*>(m_spaces);
            SNode* smp=dynamic_cast<SNode*>(mp);//强转
            for(int i=0;i<N;i++)
            {
                if(smp==(sp+i))//判断地址有效性
                {
                    if(m_used[i]!=0)
                    {
                        //delete pm;//调用析构指针 要强转
                        smp->~SNode();//直接调用析构函数
                        m_used[i]=0;
                        break;//test16 4
                    }

                }
//                if(m_used[i]!=0)
//                {
//                    delete sp+i;

//                }
            }
        }
        public:
        StaticLinkList()
        {
            for(int i=0;i<N;i++)
            {
                m_used[i]=0;
            }


        }
        int capacity()
        {
            return N;
        }
        ~StaticLinkList()
        {
            this->clear();//此时内部的destroy，为staticlinklist的成员函数
        }
    };

}

#endif // STATICLINKLIST_H
