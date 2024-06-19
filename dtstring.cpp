#include "dtstring.h"
#include<cstdlib>
#include<cstring>
#include "exception.h"
#include<iostream>
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

String& String::insert(int i,const String& s)
{
    return insert(i,s.m_str);

}
String& String::insert(int i,const char* s)
{
    bool ret=(0<=i)&&(i<=length());
    if(ret)
    {
        if((s!="")&&(s[0]!='\0'))//放在这里判断
        {
            int len=strlen(s);
            char* str=reinterpret_cast<char*>(malloc(m_length+len+1));
            if(str!=NULL)
            {
                strncpy(str,m_str,i);
                strncpy(str+i,s,len);
                strncpy(str+i+len,m_str+i,m_length-i);
                str[m_length+len]='\0';
                free(m_str);
                m_str=str;
                m_length=m_length+len;

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create string value...");
            }

        }



    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException,"index i is invalid...");
    }
    return *this;//m_str

}

String& String::trim()
{
    int b=0;
    int e=length()-1;
    while (m_str[b]==' ')//=
    {
        b++;
    }
    while (m_str[e]==' ')//=
    {
        e--;
    }
    if(b==0)
    {
        m_str[e+1]='\0';
        m_length=e+1;//e
    }
    else
    {
        if(b<e)
        {
            for(int i=0,j=b;j<=e;i++,j++)
            {
                m_str[i]=m_str[j];
            }
            m_str[e-b+1]='\0';//+1


            m_length=e-b+1;

        }
        else
        {
            free(m_str);
            m_str="";
            m_length=0;
        }

    }

   return *this;
}

int * String::make_pmt(const char * p)
{
    int len=strlen(p);
    int * ret=static_cast<int *>(malloc(sizeof(int)*len));
    if(ret!=NULL)
    {
        int ll=0;
        ret[0]=0;
        for(int i=1;i<len;i++)
        {
            while ((ll>0)&&(p[ll]!=p[i]))
            {
              ll=ret[ll-1];
            }
            if(p[ll]==p[i])
            {
                ll++;

            }
            ret[i]=ll;

        }

    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create pmt ...");
    }
    return ret;
}

int String::kmp(const char* d,const char * s)
{
    int ret=-1;
    int dlen=strlen(d);
    int slen=strlen(s);
    int * pmt=make_pmt(s);//

    if((pmt!=NULL)&&(slen!=0)&&(dlen>=slen))//(pmt!=NULL)
    {
        //int * pmt=make_pmt(s);//

        for(int i=0,j=0;i<dlen;i++)
        {
            while((j>0)&&(s[j]!=d[i]))//???
            {
                j=pmt[j-1];

            }
            if(s[j]==d[i])
            {
                j++;
            }

            if(j==slen)
            {
                ret=i-slen+1;
                break;
            }

        }


        free(pmt);

    }
    return ret;
}

int String::IndexOf(const String& s)const
{
    return IndexOf(s.m_str);

}
int String::IndexOf(const char* s)const
{
    return kmp(m_str,s?s:"");

}

String& String::remove(int i,int len)
{
    if((i>=0)&&(i<length()))
    {
        int n=i;
        int m=i+len;
        while((n<m)&&(m<length()))
        {
            m_str[n++]=m_str[m++];

        }
        m_str[n]='\0';
        m_length=n;//m_length-len;
    }
    return *this;
}

String& String::remove(const String& s)
{
    return remove(IndexOf(s),s.length());

}
String& String::remove(const char* s)
{

    return remove(IndexOf(s),strlen(s?s:""));

}

String String::operator -(const String& s)const
{
    return String(*this).remove(s);//不改变原有的数值

}
String String::operator -(const char* s)const
{
    return String(*this).remove(s);//不改变原有的数值

}
String& String::operator -=(const String& s)
{
    return remove(s);

}
String& String::operator -=(const char* s)
{
    return remove(s?s:"");
}

String& String::replace(const char* t, const char* s)
{
    int index=IndexOf(t);
    if(index>=0)
    {
        remove(t);
        insert(index,s);
    }
    return *this;

}
String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str,s);
}
String& String::replace(const char* t, const String& s)
{
    return replace(t,s.m_str);
}
String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str,s.m_str);
}

String String::sub(int i, int len) const
{
    String ret;
    if((i>=0)&&(i<length()))//loule
    {
            if(len<0)len=0;//louel
            if(i+len>m_length)len=m_length-i;
            char* str=reinterpret_cast<char*>(malloc(sizeof(char)*(len+1)));

            if(str!=NULL)
            {
//                cout<<len<<endl;
//                cout<<i<<endl;
//cout<<m_str[i]<<endl;
//cout<<m_str[i+1]<<endl;
                strncpy(str,m_str+i,len);//strncpy  strncat??
//                cout<<str[0]<<endl;
//                cout<<str[1]<<endl;
                str[len]='\0';

            ret=str;
//            ret.m_str=str;
//            ret.m_length=len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create substring ...");

            }

        }

    return ret;
}

String::~String()
{
    free(m_str);

}

}


