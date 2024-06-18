#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
#include "pointer.h"//2头文件添加
namespace DTLib {
template<typename T>
class SmartPointer:public Pointer<T>//1  <T>loule
{
//protected:
//    T* m_pointer;
public:
    SmartPointer(T* p=NULL):Pointer<T>(p)
    {
      //this->m_pointer=p;
    }
    //拷贝构造函数
    SmartPointer(const SmartPointer<T>& obj):Pointer<T>(NULL)//SmartPointer(const T& obj)XXX
    {


       // delete m_pointer;不需要
        this->m_pointer=obj.m_pointer;//改为pointer继承 添加this
        const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;//obj.m_pointer=NULL;const对象不能直接赋值  const_cast<SmartPointer<T>&>(obj.m_pointer)=NULL
    }
    //赋值函数
    SmartPointer<T>& operator =(const SmartPointer<T>& obj)//SmartPointer(const T& obj)  XXX   T& operator =(const SmartPointer<T>& obj)xxx
    {
        if((this)!=&obj)//error: no match for 'operator!=' (operand types are 'DTLib::SmartPointer<Test>' and 'const DTLib::SmartPointer<Test>')  if((*this)!=obj)

        {
            T* tem=this->m_pointer;//防止释放堆空间抛出异常，先赋值
           // delete m_pointer;//
            this->m_pointer=obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
           delete tem;//释放放到最后

        }
        return *this;
    }

//    T* operator ->()
//    {
//        return m_pointer;
//    }
//    T& operator *()
//    {
//        return *m_pointer;
//    }
//    bool isNull()
//    {
//        return (m_pointer==NULL);
//    }
//    T* get()
//    {
//        return m_pointer;

//    }
    ~SmartPointer()
    {
        delete this->m_pointer;//改为pointer继承 添加this
    }
};

}

#endif // SMARTPOINTER_H
