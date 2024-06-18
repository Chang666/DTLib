#ifndef TREENODE_H
#define TREENODE_H
#include "object.h"
namespace DTLib {

template <typename T>
class TreeNode:public Object
{
protected:

    //工厂模式提取
    bool m_flag;//标记是否在堆空间，清除时判断
    TreeNode(const TreeNode<T>&);//不能拷贝构造
    TreeNode<T>& operator =(const TreeNode<T>&)//不能赋值
    {

    }
    void* operator new(unsigned int size)throw()//void*
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;
    TreeNode()
    {
        parent=NULL;
        m_flag=false;//抽取到父类
    }


bool flag()//抽取到父类
{
    return m_flag;
}
    virtual ~TreeNode()=0;
};

template <typename T>
TreeNode<T>::~TreeNode()//漏了
{

}

}

#endif // TREENODE_H
