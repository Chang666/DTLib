#ifndef DTSTRING_H
#define DTSTRING_H

#include "object.h"
namespace DTLib {


class String :public Object
{
protected:
    char* m_str;
    int m_length;
    void init(const char* s);
    bool equal(const char* l,const char* r,int len) const;
    static int * make_pmt(const char * p);
    static kmp(const char* d,const char * s);
public:

    String();
    String(char c);
    String(const char* s);
    String(const String& obj);
    int length() const;
    const char* str() const;

    bool operator ==(const String& s)const;
    bool operator ==(const char* s)const;
    bool operator !=(const String& s)const;
    bool operator !=(const char* s)const;
    bool operator <(const String& s)const;
    bool operator <(const char* s)const;
    bool operator >(const String& s)const;
    bool operator >(const char* s)const;
    bool operator <=(const String& s)const;
    bool operator <=(const char* s)const;
    bool operator >=(const String& s)const;
    bool operator >=(const char* s)const;

    String operator +(const String& s)const;
    String operator +(const char* s)const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);

    String operator -(const String& s)const;
    String operator -(const char* s)const;
    String& operator -=(const String& s);
    String& operator -=(const char* s);

    String& operator =(const String& s);
    String& operator =(const char* s);
    String& operator =(char c);

    char& operator [](int i);
    char operator [](int i) const;

    bool StartWith(const String& s)const;
    bool StartWith(const char* s)const;

    bool EndOf(const String& s)const;
    bool EndOf(const char* s)const;

    String& insert(int i,const String& s);
    String& insert(int i,const char* s);
    String& trim();

    int IndexOf(const String& s)const;
    int IndexOf(const char* s)const;
     String& remove(int i,int len);
    String& remove(const String& s);
    String& remove(const char* s);

    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s) ;
    String& replace(const char* t, const String& s) ;
    String& replace(const String& t, const String& s);

    String sub(int i, int len) const;


    ~String();
};

}


#endif // DTSTRING_H
