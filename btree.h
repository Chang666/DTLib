#ifndef BTREE_H
#define BTREE_H

#include "exception.h"
#include "tree.h"
#include "btreenode.h"
#include<iostream>
#include "linkqueue.h"
#include"sharedpointer.h"
#include"dynamicarray.h"
using namespace std;
namespace DTLib {
enum BTtraversal{preOrder,inOrder,postOrder,levelOrder};//放在这个类的外部
template<typename T>
class BTree:public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;//用于层次遍历

    virtual BTreeNode<T>* find(BTreeNode<T>*node,const T& value) const//递归 基于数据的查找 //？虚函数
    {
       // cout<<"find(BTreeNode<T>*node,const T& value) const"<<endl;
        BTreeNode<T>* ret=NULL;
       //  cout<<"ret=NULL;"<<endl;
        if(node!=NULL)
        {
            if(node->value==value)
            {
                ret=node;
            }
            else
            {
                if(ret==NULL)

                    ret=find(node->left,value);
                if(ret==NULL)
                    ret=find(node->right,value);//比我复杂

            }
        }
       // cout<<"ret;"<<ret<<endl;

        return ret;//null
    }
    virtual BTreeNode<T>*find(BTreeNode<T>*node,BTreeNode<T>*obj)const // G  G  //？虚函数
    {
        BTreeNode<T>* ret=NULL;
        if(node!=NULL)
        {
            if(node==obj)
            {
                ret=node;//return node;
            }
            else
            {
                if(node!=NULL)
                {
                    if(ret==NULL)
                    {
                        ret=find(node->left,obj);

                    }
                    if(ret==NULL)
                    {
                        ret=find(node->right,obj);

                    }
                }


            }
        }

        return ret;//null

    }
    virtual bool insert(BTreeNode<T>*p,BTreeNode<T>*np,BTNodePos pos)//要插入的节点   目标树的目标父节点  插入的位置选项   //？虚函数
    {
        bool ret=true;
        if(pos==ANY)
        {
            if(np->left==NULL)
            {
                np->left=p;
            }
            else if(np->right==NULL)
            {
                np->right=p;
            }
            else
            {
                ret=false;
            }

        }
        else if(pos==LEFT)
        {
            if(np->left==NULL)
            {
                np->left=p;
            }
            else
            {
                ret=false;
            }

        }
        else if(pos==RIGHT)
        {
            if(np->right==NULL)
            {
                np->right=p;
            }
            else
            {
                ret=false;
            }

        }
        else
        {
            ret=false;
        }
        return ret;
    }
    virtual void remove(BTreeNode<T> *node,BTree<T> *&ret)//为啥改成虚函数
    {
        ret=new BTree<T>();
        if(ret!=NULL)
        {
            if(root()!=node)//要删除的是不是根节点
            {
//                LinkList<GTreeNode<T>*>& child=dynamic_cast<GTreeNode<T>*>(node->parent)->child;

//                child.remove(child.find(node));
                BTreeNode<T>* parent=dynamic_cast<BTreeNode<T>*>(node->parent);//
                if(parent->left==node)//要删除的是父节点的左孩子
                {
                    parent->left=NULL;
                }
                else if(parent->right==node)
                {
                    parent->right=NULL;
                }

                node->parent=NULL;//要删除的节点内部的指针，清除

            }
            else
            {
                this->m_root==NULL;//root()

            }
            ret->m_root=node;//作为子树返回

        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new BTree...");

        }

    }
    virtual void free(BTreeNode<T>* node)//判断节点指向的一定是堆空间  ??虚函数
    {
        if(node!=NULL)
        {
//            for(node->child.move(0);!(node->child.end());node->child.next())//node->child.end
//            {
//                free(node->child.current());
//            }
            if(node->left!=NULL)
            {
                free(node->left);

            }
            if(node->right!=NULL)
            {
                free(node->right);

            }

            if(node->flag()){//和位置1有区别  //重新构建所有项目！！！！必须所有节点入栈，在退栈的时候判断
               cout<<"del:"<<node->value<<endl;
                delete node;
            }
            else
            {
                cout<<"zhan:"<<node->value<<endl;
            }



            //delete node;//位置2

        }

    }

    int count(BTreeNode<T>* node)const
    {
        int ret=0;
        if(node!=NULL)
        {
                ret=1;
//                for(node->child.move(0);!node->child.end();node->child.next())
//                {
//                    ret+=count(node->child.current());
//                }
                ret+=count(node->left);
                ret+=count(node->right);

        }
        return ret;
        //一行代码可以搞定

    }
    int height(BTreeNode<T>* node)const
    {
        int ret=0;
        if(node!=NULL)
        {
//                ret=1;
//                int h=0;
//                for(node->child.move(0);!node->child.end();node->child.next())
//                {
//                    h=height(node->child.current())+1;//没jia

//                    if(h>ret)ret=h;
//                }
              //这里加一
                ret=height(node->left)+1;
                int h;
                h=height(node->right)+1;
                if(h>ret)ret=h;
        }
        return ret;

    }
    int degree(BTreeNode<T>* node)const
    {
        int ret=0;
        if(node!=NULL)
        {
                ret=1;
                int h=0;
//                int h1=node->child.length();//直接ret=  后面少写一个if
//                for(node->child.move(0);!node->child.end();node->child.next())
//                {
//                    h=degree(node->child.current());

//                    if(h>ret)ret=h;
//                    else if(h1>ret)ret=h1;
//                }
                if(node->left&&node->right)ret=2;
                else
                {
                    if(node->left)ret=degree(node->left);
                    if(node->right)ret=degree(node->right);
                }

        }
        return ret;

    }
    void PreOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& queue)//漏了引用
    {
        if(node!=NULL)
        {
            queue.add(node);
            PreOrderTraversal(node->left,queue);
            PreOrderTraversal(node->right,queue);
        }

    }
    void InOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node!=NULL)
        {

            InOrderTraversal(node->left,queue);
            queue.add(node);
            InOrderTraversal(node->right,queue);
        }

    }
    void PostOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node!=NULL)
        {

            PostOrderTraversal(node->left,queue);
            PostOrderTraversal(node->right,queue);
            queue.add(node);
        }

    }
    void LevelOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node!=NULL)
        {
            LinkQueue<BTreeNode<T>*> temp;// =NULL loule//通过临时队列存储数据，在放到queue

            temp.add(root());
            while(temp.length()>0)
            {
                BTreeNode<T>*node=temp.front();
                if(node->left!=NULL)
                {
                    temp.add(node->left);

                }
                if(node->right!=NULL)
                {
                temp.add(node->right);
                }
                temp.remove();
                queue.add(node);
            }



        }

    }
    BTreeNode<T>* clone(BTreeNode<T>* node)const
    {
        BTreeNode<T>* ret=NULL;
        if(node!=NULL)
        {
            ret=BTreeNode<T>::NewNode();
            if(ret!=NULL)//panduan
            {
                ret->value=node->value;
                ret->left=clone(node->left);//loule digui
                ret->right=clone(node->right);

//                ret->parent=node->parent;
//                if(node==Dynamic_cast<BTreeNode<T>* >(node->parent))
                if(ret->left!=NULL)//loule
                {
                    ret->left->parent=ret;//左子树的父亲就是当前节点，指定父子关系
                }
                if(ret->right!=NULL)
                {
                    ret->right->parent=ret;//you子树的父亲就是当前节点，指定父子关系
                }
            }
            else
            {
                // cout<<"BTreeNode<T>* clone"<<endl;
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new BTreenode...");
            }



        }

        return ret;
    }
    bool equal(BTreeNode<T>* lh,BTreeNode<T>* rh)const
    {
        if(lh==rh)
        {
            return true;

        }
        else if((lh!=NULL)&&(rh!=NULL))
        {
            return (lh->value==rh->value)&&equal(lh->left,rh->left)&&equal(lh->right,rh->right);

        }
        else
        {
            return false;
        }

    }
    BTreeNode<T>* add(BTreeNode<T>* lh,BTreeNode<T>* rh)const
    {
        BTreeNode<T>* ret=NULL;

        if((lh==NULL)&&(rh!=NULL))
        {
            ret=clone(rh);

        }
        else if((lh!=NULL)&&(rh==NULL))
        {
            ret=clone(lh);

        }
        else if((lh==NULL)&&(rh==NULL))
        {
            ret=NULL;

        }
        else
        {
            ret=BTreeNode<T>::NewNode();
            if(ret!=NULL)
            {
                ret->value=lh->value+rh->value;
                ret->left=add(lh->left,rh->left);
                ret->right=add(lh->right,rh->right);
                if(ret->left!=NULL)
                {
                    ret->left->parent=ret;
                }
                if(ret->right!=NULL)
                {
                    ret->right->parent=ret;
                }


            }else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new btreenode...");
            }
        }
        return ret;

    }
    void traversal(BTtraversal order,LinkQueue<BTreeNode<T>*>& queue)
    {


        switch (order) {
        case preOrder:
            PreOrderTraversal(root(),queue);//漏了一个引用符号！！！！！
            //return NULL;//忘记删除了
            break;
        case inOrder:
            InOrderTraversal(root(),queue);

            break;
        case postOrder:
            PostOrderTraversal(root(),queue);
            break;
        case levelOrder:
            LevelOrderTraversal(root(),queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException,"Parameter is invalid...");
            break;
        }
    }
    BTreeNode<T>* connected(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret=NULL;
        if(queue.length()>0)
        {
            ret=queue.front();//loule
            BTreeNode<T>* slider =queue.front();
            queue.remove();
            slider->left=NULL;
            while(queue.length()>0)
            {
                slider->right=queue.front();
                queue.front()->left=slider;
                slider =queue.front();
                queue.remove();
            }
            slider->right=NULL;//最后节点指向空

        }

        return ret;

    }


public:
    //enum BTtraversal{preOrder,inOrder,postOrder};//放在这个类的外部
    BTree() {}
    bool insert( TreeNode<T>* node)
    {
        return insert(node,ANY);

    }
    bool insert(TreeNode<T>* node,BTNodePos pos)
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
                BTreeNode<T>*np =find(node->parent); //node的父哪里来的??
                if(np!=NULL)
                {
                    ret=insert(dynamic_cast<BTreeNode<T>*>(node),np,pos);

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
        return ret;//loule
    }
    bool insert(const T& value, TreeNode<T>* parent)//插入数据元素
    {
        return insert(value, parent,ANY);

    }
    virtual bool insert(const T& value, TreeNode<T>* parent,BTNodePos pos)//插入数据元素  ???虚函数为啥
    {
        bool ret=true;

        BTreeNode<T>*node=BTreeNode<T>::NewNode();//new GTreeNode<T>();改用工厂方法 <T>漏了
        if(node!=NULL)
        {
            node->value=value;


            node->parent=parent;
            ret=insert(node,pos);//diaoyong
            if(ret==false)
            {
                delete node;
            }




        }
        else
        {
            //ret=false;//??需要吗？？
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new GTreenode...");
        }


        return ret;

    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>*ret=NULL;//B
        BTreeNode<T>* node=find(value);
        if(node!=NULL)
        {
            remove(node,ret);
            m_queue.clear();

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"invalid value...");
        }

        return ret;//gai NULL

    }
    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        //先判断节点是不是属于这个树
        BTree<T>*ret=NULL;
        node=find(node);
        if(node!=NULL)
        {
            remove(dynamic_cast<BTreeNode<T>*>(node),ret);//dynamic_cast<BTreeNode<T>*>()
            m_queue.clear();

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"node is not belong to the tree...");
        }

        return ret;
    }
    BTreeNode<T>* find(const T& value) const
    {
        //cout<<"find(const T& value);cccc"<<endl;
        return find(root(),value);
    }
    BTreeNode<T>*find(TreeNode<T>*node)const//BTreeNode<T>*node TreeNode<T>*node
    {
        //cout<<"find(const T& value);"<<endl;
        return find(root(),dynamic_cast<BTreeNode<T>*>(node));
    }
    BTreeNode<T>* root()const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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
        free(root());
        m_queue.clear();
        this->m_root=NULL;


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
                BTreeNode<T>* node=m_queue.front();
                m_queue.remove();//loule
//                for(node->child.move(0);!node->child.end();node->child.next())
//                {
//                    m_queue.add(node->child.current());
//                }
                if(node->left!=NULL)//loule
                {
                    m_queue.add(node->left);

                }

                if(node->right!=NULL)//loule
                {
                    m_queue.add(node->right);

                }


        }

        return ret;//游标有没有走满


    }
    SharedPointer<Array<T>> traversal(BTtraversal order)
    {
        DynamicArray<T>* ret=NULL;

        LinkQueue<BTreeNode<T>*> queue;//保存次序
        //return NULL;
//        switch (order) {
//        case preOrder:
//            PreOrderTraversal(root(),queue);//漏了一个引用符号！！！！！
//            //return NULL;//忘记删除了
//            break;
//        case inOrder:
//            InOrderTraversal(root(),queue);

//            break;
//        case postOrder:
//            PostOrderTraversal(root(),queue);
//            break;
//        default:
//            THROW_EXCEPTION(InvalidParameterException,"Parameter is invalid...");
//            break;
//        }
        traversal(order,queue);//提取出来
        ret=new DynamicArray<T>(queue.length());
        if(ret!=NULL)
        {
            for(int i=0;i<ret->length();i++)
            {
                //ret[i]=queue.front();
                //cout<<"queue.front()->value:"<<queue.front()->value<<endl;
                ret->set(i,queue.front()->value);
                queue.remove();//也可，放i++后面
            }


        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to dynamic array...");
        }

       return ret;

    }
    SharedPointer<BTree<T>> clone()const
    {
        BTree<T>* ret=new BTree();
        if(ret!=NULL)
        {
            ret->m_root=clone(root());//duidui

        }
        else
        {
            //cout<<"SharedPointer<BTree<T>> clone()"<<endl;
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new Btree");
        }
        return ret;
    }

    bool operator ==(const BTree<T>& btree)
    {
        return equal(root(),btree.root());//m_root

    }

    bool operator !=(const BTree<T>& btree)
    {
        return !(*this==btree);

    }
    SharedPointer<BTree<T>> add(const BTree<T>& btree)
    {
        BTree<T>* ret=new BTree();
        if(ret!=NULL)
        {
            ret->m_root=add(root(),btree.root());// ret->root()   ret->m_root

        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new btree...");

        }
        return ret;//漏了
    }
    BTreeNode<T>* thread(BTtraversal order)
    {
        BTreeNode<T>* ret=NULL;
        LinkQueue<BTreeNode<T>*> queue;
        traversal(order,queue);
        ret=connected(queue);
        this->m_root=NULL;
        m_queue.clear();

        return ret;


    }



    ~BTree()
    {
        clear();
    }
};


}
#endif // BTREE_H
