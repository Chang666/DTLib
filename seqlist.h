#ifndef SEQLIST_H
#define SEQLIST_H
#include "list.h"
#include "exception.h"

namespace DTLib
{
    template <typename T>
    class SeqList:public List<T>//class SeqList:public List 漏了 <T>
    {

    protected:
        T* m_array;//空间
        int m_length;//长度
    public:
        bool insert(int i,const T& e)//插入
        {
            bool ret=(0<=i)&&(i<=m_length);//漏了，i<m_length,可以插在最后
            ret=ret&&(m_length<captcity());
            if(ret)
            {
                for(int k=m_length-1;k>=i;k--)//k++,error
                {
                    m_array[k+1]=m_array[k];
                }

                m_array[i]=e;
                m_length++;

            }
            return ret;
        }

        bool insert(const T& e)//插入test18
        {

                //m_length++;


            return insert(m_length,e);
        }

        bool remove(int i)
        {
            bool ret=(0<=i)&&(i<m_length);
            //ret=ret&&(m_length<captcity());
            if(ret)
            {
                for(int k=i;k+1<m_length;k++)
                {
                    m_array[k]=m_array[k+1];

                }
                m_length--;
            }
            return ret;

        }

        bool set(int i,const T& e)
        {
            bool ret=(0<=i)&&(i<m_length);
            if(ret)
            {
                m_array[i]=e;

            }
            return ret;

        }

        bool get(int i,T& e)const //??const
        {
            bool ret=(0<=i)&&(i<m_length);
            if(ret)
            {
                e=m_array[i];

            }
            return ret;

        }
        int find(const T& e)const       //O(n)
        {
            int ret=-1;
            for(int i=0;i<m_length;i++)
            {
                if(m_array[i]==e)
                {
                    ret=i;
                    break;
                }
            }

            return ret;

        }

        int length()const
        {
            return m_length;
        }

        void clear()
        {
            m_length=0;
        }
        //数组访问方式
        T& operator[](int i)
        {
            if((0<=i)&&(i<m_length))
            {
                return m_array[i];
            }
            else
            {
                //抛异常
                THROW_EXCEPTION(IndexOutOfBoundsException,"operator[]...i is invalid");
            }
        }

        T operator [](int i) const
        {
           return (const_cast<SeqList<T>&>(*this))[i];//constcast强制类型转换
           //一用于去除变量的只读属性
          // 一强制转换的目标类型必须是指针或引用
        }

        virtual int captcity()const=0;//子类实现

    };

}

#endif // SEQLIST_H
