#ifndef STATICARRAY_H
#define STATICARRAY_H
#include "array.h"//漏了

namespace DTLib {


template <typename T,int N>
class StaticArray:public Array<T>
{
protected:
    T m_spaces[N];

public:
    StaticArray()
    {
        this->m_array=m_spaces;

    }
    StaticArray(const StaticArray<T,N>& obj)// const StaticArray<T>& e
    {
        this->m_array=m_spaces;//this->m_array=obj.m_spaces;||this->m_array=m_spaces;
        for(int i=0;i<N;i++)
        {
            m_spaces[i]=obj.m_spaces[i];//this->m_array[i]=obj.m_spaces[i];||m_spaces[i]=obj.m_spaces[i];
        }
    }

    StaticArray<T,N>& operator=(const StaticArray<T,N>& obj)
    {
        if(this!=&obj)//loule
        {
            this->m_array=m_spaces;//??示例mei'xie   this->m_array=obj.m_spaces;
            for(int i=0;i<N;i++)
            {
                m_spaces[i]=obj.m_spaces[i];
            }

        }
        return *this;


    }
    int length()const
    {
        return N;
    }

};

}

#endif // STATICARRAY_H
