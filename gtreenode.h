#ifndef GTREENODE_H
#define GTREENODE_H
#include "tree.h"
#include "linklist.h"
namespace DTLib {
template < typename T >
class GTreeNode : public TreeNode<T>
{
protected:

    //工厂模式提取到父类
//    bool m_flag;//标记是否在堆空间，清除时判断
//    GTreeNode(const GTreeNode<T>&);//不能拷贝构造
//    GTreeNode<T>& operator =(const GTreeNode<T>&)//不能赋值
//    {

//    }
//    void* operator new(unsigned int size)throw()//void*
//    {
//        return Object::operator new(size);
//    }
public:
    LinkList<GTreeNode<T>*> child;
//    GTreeNode()//3构造函数不要了
//    {
//       // m_flag=false;//1抽取到父类
//    }
//    bool flag()//2抽取到父类
//    {
//        return m_flag;
//    }
    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret=new GTreeNode<T>();//<T>
        if(ret!=NULL)
        {
            ret->m_flag=true;//m_flag=true    error: invalid use of member 'DTLib::GTreeNode<T>::m_flag' in static member function

        }

    }



};
}


#endif // GTREENODE_H
