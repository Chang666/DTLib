#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H
#include "seqlist.h"
#include"exception.h"
namespace DTLib {
template <typename T>
class DynamicList:public SeqList<T>
{
private:
    //T* m_space;
    int m_capacity;
public:
    DynamicList(int cap) //指定个数
    {
        //m_space=(DynamicList<T>)malloc(sizeof(T)*N);
        this->m_array=new T[cap];//?
        if(this->m_array!=NULL)
        {
            this->m_capacity=cap;//this->??
            this->m_length=0;

        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no enough space to dynamiclist Object...");
        }


    }
    int captcity()const
    {
        return m_capacity;
    }
    //重置大小
    void resize(int captcity)
    {
        if(captcity!=m_capacity)//panduan
        {
            T* arr=new T[captcity];
            if(arr!=NULL)
            {
                int len=(this->m_length<captcity?this->m_length:captcity);//this->
                for(int i=0;i<len;i++)
                {
                    arr[i]=this->m_array[i];
                }
                T*tem=this->m_array;
                this->m_array=arr;//loule
                this->m_length=len;
                this->m_capacity=captcity;//this->
                delete[]tem;

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough space to resize dynamiclist object...");
            }

        }


    }
    ~DynamicList()//归还空间
    {
        delete []this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
