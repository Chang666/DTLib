#ifndef EXCEPTION_H
#define EXCEPTION_H
#include "object.h"//2
namespace DTLib {
#define THROW_EXCEPTION(e,m) throw e(m,__FILE__,__LINE__)//定义宏在头文件  test13 可以注释成：#define THROW_EXCEPTION(e,m) //throw e(m,__FILE__,__LINE__);
                                                                                    //使得使用时失效
    class Exception:public Object//1
    {
    protected:
        char* m_message;//const char* m_message;XXX
        char*m_location;//const char*m_location;XXX
        void init(const char* message, const char* file, int line);//有重载的构造函数

    public:
        Exception(const char* message);
        Exception(const char*file, int line);
        Exception(const char* message, const char* file, int line);
        Exception(const Exception& e);
        Exception& operator=(const Exception& e);
        virtual const char* message() const;
        virtual const char* location() const;
        virtual~Exception();//纯虚函数不需要实现，等子类完成，此出例外，析构函数必须要实现  =0去掉，抽象类不能生成对象，报错
    };
    class ArithmeticException:public Exception
    {
        //C++中可以在函数声明时为参数提供一人默认值当函数调用时没有提供参数的值，则使用默认值
        //继承的构造？？？不对 初始化列表，利用父类初始化子类
    public:
        ArithmeticException():Exception(0){}//ArithmeticException:Exception(0)(){}  NULL 不能用

        ArithmeticException(const char* message):Exception(message){}
        ArithmeticException(const char*file, int line):Exception(file,line){}
        ArithmeticException(const char* message, const char* file, int line):Exception(message,file,line){}
        ArithmeticException(const ArithmeticException& e):Exception(e){}
        ArithmeticException& operator=(const ArithmeticException& e)
        {
            Exception::operator =(e);
            return *this;
        }


    };
    class NullPointerException:public Exception
    {
    public:
        NullPointerException():Exception(0){}
        NullPointerException(const char* message):Exception(message){}
        NullPointerException(const char*file, int line):Exception(file,line){}
        NullPointerException(const char* message, const char* file, int line):Exception(message,file,line){}
        NullPointerException(const NullPointerException& e):Exception(e){}
        NullPointerException& operator=(const NullPointerException& e)
        {
            Exception::operator =(e);
            return *this;
        }

    };
    class IndexOutOfBoundsException:public Exception
    {
    public:
        IndexOutOfBoundsException():Exception(0){}
        IndexOutOfBoundsException(const char* message):Exception(message){}
        IndexOutOfBoundsException(const char*file, int line):Exception(file,line){}
        IndexOutOfBoundsException(const char* message, const char* file, int line):Exception(message,file,line){}
        IndexOutOfBoundsException(const IndexOutOfBoundsException& e):Exception(e){}
        IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& e)
        {
            Exception::operator =(e);
            return *this;
        }

    };
    class NoEnoughMemoryException:public Exception
    {
    public:
        NoEnoughMemoryException():Exception(0){}
        NoEnoughMemoryException(const char* message):Exception(message){}
        NoEnoughMemoryException(const char*file, int line):Exception(file,line){}
        NoEnoughMemoryException(const char* message, const char* file, int line):Exception(message,file,line){}
        NoEnoughMemoryException(const NoEnoughMemoryException& e):Exception(e){}
        NoEnoughMemoryException& operator=(const NoEnoughMemoryException& e)
        {
            Exception::operator =(e);
            return *this;
        }

    };
    class InvalidParameterException:public Exception
    {
    public:
        InvalidParameterException():Exception(0){}
        InvalidParameterException(const char* message):Exception(message){}
        InvalidParameterException(const char*file, int line):Exception(file,line){}
        InvalidParameterException(const char* message, const char* file, int line):Exception(message,file,line){}
        InvalidParameterException(const InvalidParameterException& e):Exception(e){}
        InvalidParameterException& operator=(const InvalidParameterException& e)
        {
            Exception::operator =(e);
            return *this;
        }

    };
    class InvalidOperationException:public Exception//3
    {
    public:
        InvalidOperationException():Exception(0){}
        InvalidOperationException(const char* message):Exception(message){}
        InvalidOperationException(const char*file, int line):Exception(file,line){}
        InvalidOperationException(const char* message, const char* file, int line):Exception(message,file,line){}
        InvalidOperationException(const InvalidOperationException& e):Exception(e){}
        InvalidOperationException& operator=(const InvalidOperationException& e)
        {
            Exception::operator =(e);
            return *this;
        }

    };

}
//ArithmeticException
//NullPointerException
//IndexOutOfBoundsException
//NoEnoughMemoryExceptior
//InvalidParameterException
//计算异常
//空指针异常
//越界异常
//内存不足异常
//参数错误异常



#endif // EXCEPTION_H
