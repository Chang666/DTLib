#include "object.h"
#include<cstdlib>
#include<iostream>
using namespace std;
namespace DTLib {
void* Object::operator new (unsigned int size) throw()
{
    cout<<"void* Object::operator new size:"<<size<<endl;
    return malloc(size);


}
void Object::operator delete(void* p)
{
    cout<<"void Object::operator:"<<p<<endl;
    free(p);

}
void * Object::operator new[](unsigned int size) throw()
{
    cout<<"void * Object::operator new[]"<<endl;
    return malloc(size);

}
void Object::operator delete[](void* p)
{
    cout<<"void Object::operator delete[]"<<endl;
    free(p);

}
 bool Object::operator ==(const Object& obj)//loule Object::
{
    return (this==&obj);
//    if(this==&obj)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
}
bool Object::operator !=(const Object& obj)
{
    return (this!=&obj);

}
Object::~Object()
{
    cout<<"Object::~Object"<<endl;

}

}


