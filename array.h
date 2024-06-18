#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "exception.h"
namespace DTLib {
template <typename T>
class Array:public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i,const T& e)//const Array<T>& e  error: no matching function for call to 'DTLib::StaticArray<int, 5>::set(int, int)'

    {
        bool ret=(0<=i)&&(i<length());//m_length XXX

        if(ret)
        {

            m_array[i]=e;

        }
        return ret;

    }
    virtual bool get(int i,T& e)const       //T& e  !!!!
    {
        bool ret=(0<=i)&&(i<length());

        if(ret)
        {

            e=m_array[i];

        }
        return ret;

    }
    T& operator [](int i)
    {
        bool ret=(0<=i)&&(i<length());

        if(ret)
        {

        return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"i is invalid....");
        }
    }
    T operator [](int i)const
    {


        return (const_cast<Array<T>&>(*this))[i]; //T和Array<T >区别？？  return (const_cast<Array<T>&>(*this))[i];


    }
    virtual int length()const=0;
    T* array()const//增加一个返回自己的函数  数组首地址
    {
        return m_array;
    }


};

}

#endif // ARRAY_H
