#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "array.h"
#include "exception.h"
//#include<cstdlib>
//using namespace std;
namespace DTLib
{


    template <typename T>
    class DynamicArray:public Array<T>
    {
    protected:
        int m_length;
        void init(T* array,int len) //O(1)
        {
            //array=new T[len];
            if(array!=NULL)
            {
                this->m_array=array;
                this->m_length=len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory to create dynamicArray object...");
            }

        }
        T* copy(T* array,int len,int Newlen) //O(min(len,Newlen))----->O(n)
        {
            T* arr=new T[Newlen];


            if(arr!=NULL)//array
            {
                int l=(Newlen>len?len:Newlen);//loule

                for(int i=0;i<l;i++)
                {
                    arr[i]=array[i];
                }


            }
            return arr;//不能放if内部



        }
        void update(T* array,int len) //O(1)
        {
            if(array!=NULL)//loule
            {
                T*tem=this->m_array;//保存原来的指针，再赋值，最后释放掉
                this->m_array=array;
                this->m_length=len;
                delete [] tem;


            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory to update dynamicArray object...");
            }


        }

    public:
        DynamicArray(int len=0)   //O(1)//
        {
            init(new T[len],len);
//            this->m_array=new T[len];//this->m_array=(T*)malloc(sizeof(T)*len);
//            if(this->m_array!=NULL)
//            {
//                this->m_length=len;//m_length=len;
//            }
//            else
//            {
//                THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory to dynamicArray object...");
//            }


        }


        DynamicArray(const DynamicArray<T>& obj)// const DynamicArray<T>& e  //O(n)
        {
            //init(new T[obj.length()],obj.length());//漏了复制,直接指向obj,造成两个指针指向同一片内存
//            T* arr=copy(obj.m_array,obj.m_length,obj.m_length);
//            init(arr,obj.m_length);

           init(copy(obj.m_array,obj.m_length,obj.m_length),obj.m_length);

//            this->m_array=new T[obj.length()];//(T*)malloc(sizeof(T)*obj.length());
//            if(this->m_array!=NULL)
//            {
//                for(int i=0;i<obj.length();i++)
//                {
//                    this->m_array[i]=obj.m_array[i];
//                }

//                this->m_length=obj.length();//m_length
//                //free(obj.m_array);

//            }
//            else
//            {
//                THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory to dynamicArray object...");
//            }


        }

        DynamicArray<T>& operator=(const DynamicArray<T>& obj)  //O(n)
        {
            if(this!=&obj)
            {
//                T* arr=copy(obj.m_array,obj.length(),obj.length());
//                update(arr,obj.length());

                update(copy(obj.m_array,obj.length(),obj.length()),obj.length());
            }

            return *this;
//            if(this!=&obj)//loule
//            {
//                //this->m_array=new T[obj.length()];   不对，本来m_array对应的空间未被释放，因此，新定义一个指针//obj.m_length
//                T* arr=new T[obj.m_length];
//                if(arr!=NULL)//obj.m_arrayXXXX
//                {
//                    for(int i=0;i<obj.m_length;i++)
//                    {
//                        arr[i]=obj.m_array[i];
//                    }

//                    //this->m_length=obj.length();//m_length
//                    T*tem=this->m_array;//保存原来的指针，再赋值，最后释放掉
//                    this->m_array=arr;
//                    this->m_length=obj.m_length;
//                    delete [] tem;


//                }
//                else
//                {
//                    THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory to copy dynamicArray object...");
//                }
//    //            this->m_array=obj.m_array;//??示例mei'xie   this->m_array=obj.m_spaces;
//    //            this->m_length=obj.m_length;
//    //            const_cast<T&>(obj.m_array)=NULL;

//            }
//            return *this;


        }

        int length()const  //O(1)
        {
            return m_length;
        }

        //loule
        void resize(int si)//O(n)
        {
            if(this->m_length!=si)
            {
//                T* arr=copy(this->m_array[i],m_length,si);
//                update(arr,si);

                update(copy(this->m_array,m_length,si),si);

//                T* arr=new T[si];
//                if(arr!=NULL)
//                {
//                    int s=(m_length<si)?m_length:si;
//                    for(int i=0;i<s;i++)
//                    {
//                        arr[i]=this->m_array[i];
//                    }

//                    //this->m_length=si;//m_length
//                    T*tem=this->m_array;//保存原来的指针，再赋值，最后释放掉
//                    this->m_array=arr;
//                    this->m_length=si;
//                    delete [] tem;


//                }
//                else
//                {
//                    THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory to resize dynamicArray object...");
//                }

            }
        }


        //loule
        ~DynamicArray()//O(1)
        {

        delete [] this->m_array;


        }

    };
}

#endif // DYNAMICARRAY_H
