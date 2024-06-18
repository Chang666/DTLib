#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H
#include "pointer.h"
#include <cstdlib>
#include "exception.h"
namespace DTLib {

    template <typename T>
    class SharedPointer:public Pointer<T>
    {
    protected:
        int * m_ref=NULL;//初始化
        void assigned(const SharedPointer<T>& obj)
        {
            this->m_pointer=obj.m_pointer;
            this->m_ref=obj.m_ref;
            if(this->m_ref){
                (*(this->m_ref))++;

            }

        }
    public:
        SharedPointer(T* p=NULL)
        {
            if(p!=NULL)
            {
                m_ref=static_cast<int*>(std::malloc(sizeof(int)));
                if(m_ref)
                {
                    this->m_pointer = p;//漏了

                    *m_ref=1;

                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"no memory to m_ref...");

                }

            }





        }
        SharedPointer(const SharedPointer<T>& obj):Pointer<T>(NULL)//
        {
            assigned(obj);
//:Pointer<T>(NULL)不写会有警告 如下
            //初始化列表+子类 父类构造顺序
//            初始化列表的使用
//           类中定义const成员,不用初始化列表报错，初始化列表先于构造函数执行   初始化列表顺序 声明顺序
            //子类对象的构造子类中  test46
//            可以定义构造函数子类构造函数
//            一必须对继承而来的成员进行初始化
//            ·直接通过初始化列表或者赋值的方式进行初始
//              调用父类构造函数进行初始化
//warning: base class 'class DTLib::Pointer<Test>' should be explicitly initialized in the copy constructor [-Wextra]

            //const& 初始化， 用相同 不同类型 赋值

//            this->m_pointer=obj.m_pointer;
//            this->ref=obj.ref;
//            if(this->ref){
//                (*(this->ref))++;

//            }

        }
        //赋值函数
        SharedPointer<T>& operator =(const SharedPointer<T>& obj)
        {
            if((this)!=&obj)

            {
                clear();
                assigned(obj);


//                this->m_pointer=obj.m_pointer;
//                this->ref=obj.ref;
//                if(ref){
//                    (*ref)++;

//                } 相同函数段改为内部函数调用



            }
            return *this;
        }
        void clear()
        {
            T* todel=this->m_pointer;
            int* ref=this->m_ref;

            this->m_pointer=NULL;//loule
            this->m_ref=NULL;//loule

            if(ref)
            {
                (*ref)--;
                if((*ref)==0)
                {
                    free(ref);
                    //free(todel);
                    delete todel;
                }
            }



        }
        ~SharedPointer()
        {
            clear();

        }
    };

    template <typename T>
    bool operator == (const SharedPointer<T>& l,const SharedPointer<T>& r)
    {
        return (l.get()==r.get());
    }
//    template <typename T>
//    bool operator== (const SharedPointer<T> &lhs, const SharedPointer<T> &rhs)
//    {
//        return (lhs.get() == rhs.get());
//    }

    template <typename T>
    bool operator!= (const SharedPointer<T> &lhs, const SharedPointer<T> &rhs)
    {
        return  !(lhs == rhs);
    }

}

#endif // SHAREDPOINTER_H
