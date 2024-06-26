#ifndef OBJECT_H
#define OBJECT_H

namespace DTLib{
class Object
{
public:
    //Object();
    void* operator new (unsigned int size) throw();
    void operator delete(void* p);
    void * operator new[](unsigned int size) throw();
    void operator delete[](void* p);
    bool operator ==(const Object& obj);//链表find函数 ==
    bool operator !=(const Object& obj);
    virtual ~Object()=0;
};


}


#endif // OBJECT_H
