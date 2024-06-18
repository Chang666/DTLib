#ifndef BTREENODE_H
#define BTREENODE_H
#include "treenode.h"
namespace DTLib {

enum BTNodePos//插入函数使用
{
    ANY,
    LEFT,
    RIGHT,
};

template<typename T>
class BTreeNode:public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;
    BTreeNode()
    {
        left=NULL;
        right=NULL;
    }
    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret=new BTreeNode<T>();//<T>
        if(ret!=NULL)
        {
            ret->m_flag=true;//m_flag=true    error: invalid use of member 'DTLib::GTreeNode<T>::m_flag' in static member function

        }

    }
};


}

#endif // BTREENODE_H
