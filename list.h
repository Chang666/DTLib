#ifndef LIST_H
#define LIST_H
#include "object.h"

namespace DTLib {
template <typename T>
class List:public Object
{
protected:
    List(const List<T>&);//test18  <T>没区别     List(const List<T>& e);XXXXX  e
    List<T>& operator =(const List<T>&);//test18   List<T>& operator =(const List<T>& e);XXX  e
public:
    List(){}//test18
    virtual bool insert(const T& e)=0;//test18
    virtual bool insert(int i,const T& e)=0;
    virtual bool remove(int i)=0;
    virtual bool set(int i,const T& e)=0;
    virtual bool get(int i,T& e)const =0;
    virtual int find(const T& e)const=0;//test23
    virtual int length()const =0;
    virtual void clear()=0;
};


}

#endif // LIST_H
