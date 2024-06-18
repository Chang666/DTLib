#ifndef GTREE_H
#define GTREE_H
#include "exception.h"
#include "tree.h"
#include "gtreenode.h"
#include<iostream>
#include "linkqueue.h"
using namespace std;
namespace DTLib {
    template < typename T >
    class GTree : public Tree<T>
    {
    protected:
        LinkQueue<GTreeNode<T>*> m_queue;//用于层次变量
//剪切到父类
//        GTree(const GTree<T>&);//不能拷贝构造
//        GTree<T>& operator =(const GTree<T>&)//不能赋值
//        {

//        }

            GTreeNode<T>* find(GTreeNode<T>*node,const T& value) const//递归 基于数据的查找
            {
                GTreeNode<T>* ret=NULL;
                if(node!=NULL)
                {
                    if(node->value==value)
                    {
                        return node;
                    }
                    else
                    {
                        for(node->child.move(0);!(node->child.end())&&(ret==NULL);node->child.next())//(!node->child.end)&&(ret!=NULL)//逻辑非 ! 的优先级最高，逻辑与 && 次之，逻辑或  ||  优先级最低
                        {
                            ret=find(node->child.current(),value);
                        }
                    }
                }

                return ret;//null
            }
            GTreeNode<T>*find(GTreeNode<T>*node,GTreeNode<T>*obj)const // G  G
            {
                GTreeNode<T>* ret=NULL;
                if(node!=NULL)
                {
                    if(node==obj)
                    {
                        return node;
                    }
                    else
                    {
                        for(node->child.move(0);!(node->child.end())&&(ret==NULL);node->child.next())//node->child.end
                        {
                            ret=find(node->child.current(),obj);
                        }
                    }
                }

                return ret;//null

            }
            void free(GTreeNode<T>* node)//判断节点指向的一定是堆空间
            {
                if(node!=NULL)
                {
                    for(node->child.move(0);!(node->child.end());node->child.next())//node->child.end
                    {
                        free(node->child.current());
                        //位置1 不对 会存在入栈，退栈的情况





                    }
                    if(node->flag()){//和位置1有区别  //重新构建所有项目！！！！必须所有节点入栈，在退栈的时候判断
                       cout<<"nnn:"<<node->value<<endl;
                        delete node;
                    }
                    else
                    {
                        cout<<"zhan:"<<node->value<<endl;
                    }



                    //delete node;//位置2

                }

            }
            void remove(GTreeNode<T> *node,GTree<T> *&ret)//GTreeNode<DTLib::T> *&ret
            {
                ret=new GTree<T>();
                if(ret!=NULL)
                {
                    if(root()!=node)
                    {
                        LinkList<GTreeNode<T>*>& child=dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                        child.remove(child.find(node));
                        node->parent=NULL;

                    }
                    else
                    {
                        this->m_root==NULL;//root()

                    }
                    ret->m_root=node;

                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new GTreenode...");

                }

            }
            int count(GTreeNode<T>* node)const
            {
                int ret=0;
                if(node!=NULL)
                {
                        ret=1;
                        for(node->child.move(0);!node->child.end();node->child.next())
                        {
                            ret+=count(node->child.current());
                        }

                }
                return ret;

            }
            int height(GTreeNode<T>* node)const
            {
                int ret=0;
                if(node!=NULL)
                {
                        ret=1;
                        int h=0;
                        for(node->child.move(0);!node->child.end();node->child.next())
                        {
                            h=height(node->child.current())+1;//没jia

                            if(h>ret)ret=h;
                        }
                      //这里加一
                }
                return ret;

            }
            int degree(GTreeNode<T>* node)const
            {
                int ret=0;
                if(node!=NULL)
                {
                        ret=1;
                        int h=0;
                        int h1=node->child.length();//直接ret=  后面少写一个if
                        for(node->child.move(0);!node->child.end();node->child.next())
                        {
                            h=degree(node->child.current());

                            if(h>ret)ret=h;
                            else if(h1>ret)ret=h1;
                        }

                }
                return ret;

            }


    public:
        GTree(){}//漏了 error: no matching function for call to 'DTLib::GTree<int>::GTree()'
       // GTree<int> t;// error: cannot declare variable 't' to be of abstract type 'DTLib::GTree<int>'//find鍑芥暟鍦╬rotected鍐呮湁鎴愬憳鍑芥暟锛宲ublic璋冪敤鍐呴儴protected鍑芥暟锛屾敞鎰忚緭鍏ュ弬鏁扮被鍨




        bool insert(TreeNode<T>* node)//先找到前驱节点 ，作为子节点 ????
        {
            bool ret=true;
            if(node==NULL)
            {
                ret=false;
                THROW_EXCEPTION(InvalidParameterException,"parameter node cannot be NULL...");


            }
            else
            {
                if(this->m_root!=NULL)
                {
                    GTreeNode<T>*np =find(node->parent); //node的父哪里来的??
                    if(np!=NULL)
                    {
                        GTreeNode<T>*n =dynamic_cast<GTreeNode<T>*>(node);
                        if(np->child.find(n)<0)
                        {
                            np->child.insert(n);
                        }

                    }
                    else
                    {
                        ret=false;
                        THROW_EXCEPTION(InvalidOperationException,"Invalid parent tree node...");

                    }
                }
                else //目标树是空的
                {
                    node->parent=NULL;
                    this->m_root=node;
                }
            }

            return ret;

        }
        bool insert(const T& value, TreeNode<T>* parent)//插入数据元素
        {
            bool ret=true;

            GTreeNode<T>*node=GTreeNode<T>::NewNode();//new GTreeNode<T>();改用工厂方法 <T>漏了
            if(node!=NULL)
            {
                node->value=value;


                node->parent=parent;
                ret=insert(node);//diaoyong




            }
            else
            {
                ret=false;
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new GTreenode...");
            }


            return ret;

        }
        SharedPointer< Tree<T> > remove(const T& value)
        {
            GTree<T>* ret=NULL;
            GTreeNode<T>* node=find(value);
            if(node==NULL)
            {
                THROW_EXCEPTION(InvalidParameterException,"can not find the node via parameter value");
            }
            else
            {
                remove(node,ret);
                m_queue.clear();//删除元素的话，清除队列
            }


            return ret;

        }
        SharedPointer< Tree<T> > remove(TreeNode<T>* node)
        {
            GTree<T>* ret=NULL;
            node=find(node);
            if(node==NULL)
            {
                THROW_EXCEPTION(InvalidParameterException,"can not find the node ...");
            }
            else
            {
                remove(dynamic_cast<GTreeNode<T>*>(node),ret);
                m_queue.clear();//删除元素的话，清除队列
            }
            return ret;

        }

        GTreeNode<T>* find(TreeNode<T>*node) const //loule  G
        {
            return find(root(), dynamic_cast<GTreeNode<T>*>(node));

        }
        GTreeNode<T>* find(const T &value) const
       {
           return find(root(), value);
       }
        GTreeNode<T>* root()const
        {
            return dynamic_cast<GTreeNode<T>*>(this->m_root);

        }
        int degree()const
        {
            return degree(root());


        }
        int count() const
        {
            return count(root());

        }
        int height()const
        {
            return height(root());

        }
        void clear()
        {
            free(root());//root() this->m_root error: invalid conversion from 'DTLib::TreeNode<char>*' to 'DTLib::GTreeNode<char>*' [-fpermissive]

            this->m_root=NULL;

            m_queue.clear();//晴空


        }

        bool begin()
        {
            bool ret=(root()!=NULL);
            if(ret)
            {
                m_queue.clear();//
                m_queue.add(root());

            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"No element in the gtree...");
            }
            return ret;

        }
        bool end()
        {
            return m_queue.length()==0;//(m_queue==NULL);
        }
        T current()
        {
            if(!end())//loule只有在遍历过程中，才可以
            {
                return m_queue.front()->value;

            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"no value in this position...");

            }
        }
        bool next()
        {
            bool ret=(m_queue.length()>0);//true;先判断对列是否有数据

            if(ret)
            {
                    GTreeNode<T>* node=m_queue.front();
                    m_queue.remove();//loule
                    for(node->child.move(0);!node->child.end();node->child.next())
                    {
                        m_queue.add(node->child.current());
                    }

            }

            return ret;//游标有没有走满


        }

        ~GTree()
        {
            clear();
        }
    };



}

#endif // GTREE_H
