#include "dtstring.h"
#include<cstdlib>
#include<cstring>
#include "exception.h"
using namespace std;
namespace DTLib {
void String::init(const char* s)
{
    m_str=strdup(s);
    if(m_str)
    {
        m_length=strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create string object...");
    }

}

String::String()
{
    init("");

}
String::String(const char* s)
{
    init(s?s:"");

}
String::String(const String& obj)
{
    init(obj.m_str);
//    m_str=obj.m_str;
//    m_length=obj.length();

}
String::String(char c)
{
    char s[]={c,'\0'};

    init(s);
}
int String::length() const
{
    return m_length;

}
const char* String::str() const
{
    return m_str;

}

bool String::operator ==(const String& s)const
{
    return (strcmp(m_str,s.m_str)==0);
}
bool String::operator ==(const char* s)const
{
    return (strcmp(m_str,s ? s:"")==0);
}

bool String::operator !=(const String& s)const
{
    return !(*this==s);
}

bool String::operator !=(const char* s)const
{
    return !(*this==s);
}
bool String::operator <(const String& s)const
{
    return (strcmp(m_str,s.m_str)<0);

}
bool String::operator <(const char* s)const
{
    return (strcmp(m_str,s? s :"")<0);

}
bool String::operator >(const String& s)const
{
    return (strcmp(m_str,s.m_str)>0);
}

bool String::operator >(const char* s)const
{
    return (strcmp(m_str,s? s :"")>0);
}

bool String::operator <=(const String& s)const
{
    return (strcmp(m_str,s.m_str)<=0);
}

bool String::operator <=(const char* s)const
{
    return (strcmp(m_str,s ? s : "")<=0);
}

bool String::operator >=(const String& s)const
{
    return (strcmp(m_str,s.m_str)>=0);
}

bool String::operator >=(const char* s)const
{
    return (strcmp(m_str,s?s:"")>=0);
}

String String::operator +(const String& s)const
{
    return (*this)+s.m_str;


}
String String::operator +(const char* s)const
{
    String ret;
    int len=m_length+strlen(s?s:"");
    char* str=reinterpret_cast<char*>(malloc(len+1));

    if(str)
    {
        strcpy(str,m_str);
        strcat(str,s?s:"");

        //ret.init(str);
        ret.m_length=len;
        ret.m_str=str;


    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create string ...");
    }
    return ret;

}

String& String::operator +=(const String& s)
{
    return ((*this)=(*this)+s);

}
String& String::operator +=(const char* s)
{
    return ((*this)=(*this)+(s?s:""));

}

String& String::operator =(const String& s)
{
    return (*this=s.m_str);
}

String& String::operator =(const char* s)
{
    if(m_str!=s)
    {
        char* str=strdup(s?s:"");
        if(str)
        {
            free(m_str);
            m_str=str;
            m_length=strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create string value...");
        }

    }
    return *this;

}
String& String::operator =(char c)
{
    char s[]={c,'\0'};
    return (*this=s);
}

char& String::operator [](int i)
{
    //char ret=NULL;
    if((i>=0)&&(i<length()))
    {
        return m_str[i];

    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException,"index i is invalid...");


    }
    //return ret;

}
char String::operator [](int i)const
{
    return (const_cast<String&>(*this)[i]);//  char  String&
}

bool String::equal(const char* l,const char* r,int len) const
{
    bool ret=true;
   for(int i=0;i<len&&ret;i++)
   {
       if(l[i]==r[i])
       {
           ret=true;
       }
       else
       {
           ret=false;
       }
   }
   return ret;
}
bool String::StartWith(const char* s)const
{
    bool ret=(s!=NULL);
    if(ret)
    {
        int len=strlen(s);
        ret=(len<=m_length);
        if(ret)
        {
            ret=equal(m_str,s,len);

        }

    }

    return ret;
}
bool String::StartWith(const String& s)const
{
    return StartWith(s.m_str);

}

bool String::EndOf(const String& s)const
{
    return EndOf(s.m_str);
}
bool String::EndOf(const char* s)const
{
    bool ret=(s!=NULL);
    if(ret)
    {
        int len=strlen(s);
        ret=(len<=m_length);
        if(ret)
        {
            ret=equal(m_str+(m_length-len),s,len);

        }

    }

    return ret;


}

String::~String()
{
    free(m_str);

}

}


