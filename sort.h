#ifndef SORT_H
#define SORT_H
#include "object.h"
#include "exception.h"
#include"array.h"
namespace DTLib {
class Sort
{
private:
    Sort() {}
    Sort(const Sort&);// obj

    Sort& operator=(const Sort&);


    template <typename T>
    static void SWAP(T& a,T& b)//static
    {
        T c=a;//T c(a);
        a=b;
        b=c;
    }
    template <typename T>
    static void Merge(T arr[],T helper[],int begin,int mid,int end,bool MIN2MAX=true)
    {
        int i=begin;
        int j=mid+1;
        int k=begin;
        while((i<=mid)&&(j<=end))
        {
            if(MIN2MAX?(arr[i]<arr[j]):(arr[i]>arr[j]))
            {
                helper[k++]=arr[i++];
            }
            else
            {
                helper[k++]=arr[j++];

            }

        }
        while((i<=mid)&&(j>=end))
        {
             helper[k++]=arr[i++];

        }
        while((i>=mid)&&(j<=end))
        {
             helper[k++]=arr[j++];

        }
        for(int m=begin;m<=end;m++)
        {
            arr[m]=helper[m];
        }



    }

    template <typename T>
    static void Merge(T arr[],T helper[],int begin,int end,bool MIN2MAX=true)
    {
        if(begin<end)
        {
            int mid=(begin+end)/2;//+begin
            Merge(arr,helper,begin,mid,MIN2MAX);
            Merge(arr,helper,mid+1,end,MIN2MAX);

            Merge(arr,helper,begin,mid,end,MIN2MAX);
        }


    }
    template <typename T>
    static int Partition(T arr[],int begin,int end,bool MIN2MAX)
    {
       T pv=arr[begin];//基准
       while (begin<end)
       {
           while((begin<end)&&(MIN2MAX?(arr[end]>pv):(arr[end]<pv)))
           {
               end--;
           }
           SWAP(arr[begin],arr[end]);

           while((begin<end)&&(MIN2MAX?(arr[begin]<=pv):(arr[begin]>=pv)))//=
           {
               begin++;
           }
           SWAP(arr[begin],arr[end]);


       }
       arr[begin]=pv;
       return begin;
    }

    template <typename T>
    static void Quick(T arr[],int begin,int end,bool MIN2MAX)//
    {
        if(begin<end)
        {
            int pivot=Partition(arr,begin,end,MIN2MAX);
            Quick(arr,begin,pivot-1,MIN2MAX);
            Quick(arr,pivot+1,end,MIN2MAX);

        }


    }

public:
    template <typename T>
    static void Select(T arr[],int len,bool MIN2MAX=true)//不需要用引用  T& arr[]
    {
        for(int i=0;i<len;i++)
        {
            int se=i;
            for(int j=i+1;j<len;j++)
            {
                if(MIN2MAX?(arr[j]<arr[se]):(arr[j]>arr[se]))
                {
                    se=j;

                }

            }
            if(se!=i)
            {
                 SWAP(arr[se],arr[i]);
            }

        }

    }

    template <typename T>
    static void Insert(T arr[],int len,bool MIN2MAX=true)//
    {
        for(int i=1;i<len;i++)
        {
            int se=i;
            T setvalue=arr[se];
            for(int j=i-1;j>-1;j--)
            {
                if(MIN2MAX?(arr[j]>setvalue):(arr[j]<setvalue))
                {
                    arr[j+1]=arr[j];
                    se=j;

                }

            }
            if(i!=se)//漏了,
            {
                arr[se]=setvalue;

            }



        }

    }
    template <typename T>
    static void Bubble(T arr[],int len,bool MIN2MAX=true)//
    {
        bool exchange=true;
        for(int i=0;i<len&&exchange;i++)//exchange应该在这里
        {
             exchange=false;//一开始设置为false,若没进入if,循环结束就为false;


            for(int j=len-1;j>i;j--)
            {

                if(MIN2MAX?(arr[j-1]>arr[j]):(arr[j-1]<arr[j]))
                {
                    SWAP(arr[j-1],arr[j]);
                    exchange=true;


                }

            }



        }

    }

    template <typename T>
    static void Shell(T arr[],int len,bool MIN2MAX=true)//
    {
        int d=len;
        do
        {
                d=d/3+1;
                for(int i=d;i<len;i+=d)
                {
                    int se=i;
                    T e=arr[se];
                    for(int j=i-d;j>-1;j-=d)
                    {
                        if(MIN2MAX?(arr[j]>e):(arr[j]<e))
                        {
                            arr[j+d]=arr[j];
                            se=j;

                        }

                    }
                    if(i!=se)//漏了,
                    {
                        arr[se]=e;

                    }

                }
        }
        while(d>1);

    }

    template <typename T>
    static void Merge(T arr[],int len,bool MIN2MAX=true)//
    {
        T* helper = new T[len];
        if(helper!=NULL)
        {
            Merge(arr,helper,0,len-1,MIN2MAX);

            delete[] helper;


        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new array...");

        }

    }

    template <typename T>
    static void Quick(T arr[],int len,bool MIN2MAX=true)//
    {
        Quick(arr,0,len-1,MIN2MAX);

    }

    template <typename T>
    static void Select(Array<T>& array,bool MIN2MAX=true)//<T>
    {
        Select(array.array(),array.length(),MIN2MAX);


    }

    template <typename T>
    static void Insert(Array<T>& array,bool MIN2MAX=true)
    {
        Insert(array.array(),array.length(),MIN2MAX);


    }

    template <typename T>
    static void Bubble(Array<T>& array,bool MIN2MAX=true)
    {
        Bubble(array.array(),array.length(),MIN2MAX);


    }

    template <typename T>
    static void Shell(Array<T>& array,bool MIN2MAX=true)
    {
        Shell(array.array(),array.length(),MIN2MAX);


    }

    template <typename T>
    static void Merge(Array<T>& array,bool MIN2MAX=true)
    {
        Merge(array.array(),array.length(),MIN2MAX);


    }

    template <typename T>
    static void Quick(Array<T>& array,bool MIN2MAX=true)
    {
        Quick(array.array(),array.length(),MIN2MAX);


    }


};

}



#endif // SORT_H
