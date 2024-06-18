#ifndef POINTER_H
#define POINTER_H
#include "object.h"
namespace DTLib {
template <typename T>
class Pointer:public Object
{
protected:
    T* m_pointer=NULL;//初始化
public:
    Pointer(T* p=NULL) {
        m_pointer=p;
    }

    T* operator ->()
    {
        return m_pointer;
    }
    T& operator *()
    {
        return *m_pointer;
    }

    const T* operator ->()const//
    {
        return m_pointer;
    }
    const T& operator *()const//
    {
        return *m_pointer;
    }
    bool isNull() const//加const
    {
        return (m_pointer==NULL);
    }
    T* get() const
    {
        return m_pointer;

    }
};

}

#endif // POINTER_H
