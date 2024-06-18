#include "exception.h"
#include <cstring>
#include<cstdlib>
using namespace std;

namespace DTLib {
void Exception::init(const char *message, const char *file, int line)
{
    //m_message=message;//不安全，可能在堆，栈，全局数据区
    m_message=(m_message?strdup(message):NULL);//添加头文件cstring  test26 case1:  strdup(message)直接赋值
    if(file!=NULL)
    {
        char sl[16]={0};
        itoa(line,sl,10);//将整数转换为字符串的函数
        m_location=static_cast<char*>(malloc((strlen(file)+strlen(sl)+2)*sizeof(char)));//+2??: \0//reinterpret_cast
//        dynamic_cast强制类型转换
//        一用于有继承关系的类指针间的转换
//        一用于有交叉关系的类指针间的转换
//        一具有类型检查的功能
//        一需要虚函数的支持

//        reinterpret_cast 强制类型转换
//        一用于指针类型间的强制转换
//        一用于整数和指针类型间的强制转换

//        constcast强制类型转换
//        一用于去除变量的只读属性
//        一强制转换的目标类型必须是指针或引用


//        static_cast强制类型转换
//        一用于基本类型间的转换
//        一不能用于基本类型指针间的转换
//        一用于有继承关系类对象之间的转换和类指针之间的转换
        //4  test13
        if(m_location!=NULL)
        {
            m_location=strcpy(m_location,file);//const char* m_message;成员变量设置不对，无法赋值
            m_location=strcat(m_location,":");
            m_location=strcat(m_location,sl);

        }
        else
        {
           // THROW_EXCEPTION(NoEnoughMemoryException,"void Exception::init");//test13 error 父类内部抛出子类异常？？？？有死循环
            //不处理就好
        }


    }
    else
    {
        m_location=NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message,NULL,0);
}
Exception::Exception(const char*file, int line)
{
    init(NULL,file,line);

}
Exception::Exception(const char* message, const char* file, int line)
{
    init(message,file,line);
}

Exception::Exception(const Exception& e)
{
    m_message=strdup(e.m_message);
    m_location=strdup(e.m_location);


}
Exception& Exception::operator=(const Exception& e)
{
    if(this!=&e)
    {
        free(m_message);//??loule
        free(m_location);//??loule
        m_message=strdup(e.m_message);
        m_location=strdup(e.m_location);


    }
    return *this;
}
const char* Exception::message() const//virtual
{
    return m_message;
}
const char* Exception::location() const//virtual
{
    return m_location;
}
Exception::~Exception()//纯虚函数不需要实现，等子类完成，此出例外，析构函数必须要实现
{
    free(m_message);//??loule
    free(m_location);//??loule


}

}
