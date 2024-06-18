#ifndef LISTGRAPH_H
#define LISTGRAPH_H
#include "graph.h"
#include "exception.h"
#include"dynamicarray.h"
#include"linklist.h"
#include<iostream>
using namespace std;
namespace DTLib {

template <typename V,typename E>
class ListGraph :public Graph<V,E>
{
protected:
    struct Vertex:public Object
    {
        V* data;
        LinkList<Edge<E>> edge;//<E>
        //loule
        Vertex()
        {
            data=NULL;
        }
    };

    LinkList<Vertex*> m_list;//邻接链表
public:
    ListGraph(unsigned int n=0)
    {
        for(unsigned int i=0;i<n;i++)
        {
            addVertex();
        }


    }
    int addVertex()
    {
        int ret=-1;
        Vertex* v=new Vertex();
        if(v!=NULL)
        {
            m_list.insert(v);
            ret=m_list.length()-1;

        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new vertex object...");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret=addVertex();
        //m_list.set(ret,)
        if(ret>=0)//>0 漏了
        {
            setVertex(ret, value);

        }

        return ret;
    }

    bool setVertex(int i, const V value)
    {
        bool ret=(0<=i)&&(i<vCount());
        if(ret)
        {
            //cout<<"aaa"<<endl;
            Vertex* v=m_list.get(i);
            V* dat=v->data;//data是指针
            if(dat==NULL)//(v!=NULL)
            {
                //v->data=value;//没有安全异常
                dat=new V();

            }
            if(dat!=NULL)
            {
                *dat=value;
                v->data=dat;

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new V object...");
            }
//            else
//            {
//                THROW_EXCEPTION(InvalidOperationException,"parameter i is invalid...");
//            }

        }
        return ret;

    }
    //int addVertex();
//   ·增加新的顶点，返回顶点编号
//    int addVertex(const v& value);
//   ·增加新顶点的同时附加数据元素
//   void removeVertex():
//   ，册删除最近增加的顶点
    void removeVertex()//先删除相关的边，在删除顶点
    {
        if(m_list.length()>0)
        {
            int index=m_list.length()-1;
            Vertex* v=m_list.get(index);

            if(m_list.remove(index))//先删除顶点，和以顶点为开始的边
            {
                //再删除点链表里，末尾为此顶点的边
                for(int i=(m_list.move(0),0);!m_list.end();m_list.next(),i++)
                {
                    int pos=m_list.current()->edge.find(Edge<E>(i,index));//重载比较操作符 （起点，终点一样就是相等）
                    if(pos>=0)//如果有就删除
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }
                delete v->data;//数据
                delete v;//dingdian
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"NO vertex to remove...");

        }

    }

    V getVertex(int i)
    {
        V ret;//=NULL
        if(!getVertex(i,ret))
        {
            THROW_EXCEPTION(InvalidParameterException,"i  is invalid...");

        }
        return ret;

    }
    bool getVertex(int i, V& value)
    {
        bool ret=(0<=i)&&(i<vCount());
        if(ret)
        {
            Vertex* v=m_list.get(i);
            //V* dat=(v->data);//data是指针

            if((v->data)!=NULL)
            {
                value=*(v->data);
                //v->data=dat;


            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"the vertex object no value ...");
            }

        }

    return ret;


    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret =NULL;
//        int n=0;

        if((0<=i)&&(i<vCount()))
        {
            Vertex* vertex=m_list.get(i);
//            for(vertex->edge.move(0);!vertex->edge.end();vertex->edge.next())
//            {
//                n++;
//            }
            ret=new DynamicArray<int>(vertex->edge.length());
            if(ret!=NULL)//loule
            {


                for(int j=(vertex->edge.move(0),0);!vertex->edge.end();vertex->edge.next(),++j)
                {
                    (*ret)[j]=vertex->edge.current().b;//ret[j]=vertex->edge.current().b;???
                    //ret->set(j,vertex->edge.current().b)  e???
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"i  is invalid...");

            }



        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"the index i  is invalid...");

        }
        return ret;

    }

    bool isAdjacent(int i,int j)
    {

        return (0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount())&&
                (m_list.get(i)->edge.find(Edge<E>(i,j))>=0);//loule，只需单向有边就好  &&(m_list.get(j)->edge.find(Edge<E>(j,i))>=0)&&(getEdge(i,j)==getEdge(j,i))
    }


    E getEdge(int i,int j)
    {
        E ret;
        if(!getEdge(i,j,ret))
        {
            THROW_EXCEPTION(InvalidParameterException,"the edge<i,j>  is invalid...");

        }
        return ret;

    }
    bool getEdge(int i, int j, E& value)
    {

        bool ret=(0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount());
        if(ret)
        {
            Vertex* vertex=m_list.get(i);
            //V* dat=(v->data);//data是指针

//            if(v->edge!=NULL)
//            {
//                for((vertex->edge.move(0));!vertex->edge.end();vertex->edge.next())
//                {
//                    ret=false;//jia
//                    if(j==vertex->edge.current().b)
//                    {
//                        value=vertex->edge.current().data;
//                        ret=true;//jia

//                    }//如果都不匹配，就直接退出了,jia

//                }

//            }
//            else
//            {
//                THROW_EXCEPTION(InvalidOperationException,"the edge object  is invalid...");
//            }
            int pos=vertex->edge.find(Edge<E>(i,j));
            if(pos>=0)
            {
                //value=vertex->edge.get(pos);
                value=vertex->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"the edge object  is invalid...");

            }

        }

    return ret;

    }
    bool setEdge(int i, int j, const E& value)
    {
        bool ret=(0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount());
        if(ret)
        {
            Vertex* vertex=m_list.get(i);
            int pos=vertex->edge.find(Edge<E>(i,j));
            if(pos>=0)
            {
                //vertex->edge.get(pos)=value;//Vertex*    E
                //vertex->edge.set(pos,value);
                ret=vertex->edge.set(pos,Edge<E>(i,j,value));

            }
            else
            {
//                if(!vertex->edge.insert(j,value))
//                {
//                    THROW_EXCEPTION(NoEnoughMemoryException,"no memory to insert new edge...");

//                }
               // THROW_EXCEPTION(InvalidOperationException,"the edge object  is invalid...");
                ret=vertex->edge.insert(0,Edge<E>(i,j,value));
            }


        }
        return ret;

    }
    bool removeEdge(int i, int j)
    {
        bool ret=(0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount());
        if(ret)
        {
            Vertex* vertex=m_list.get(i);
            int pos=vertex->edge.find(Edge<E>(i,j));
            if(pos>=0)
            {
                ret=vertex->edge.remove(pos);

            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"the edge object  is invalid...");

            }

        }
        return ret;


    }
    int vCount()
    {
        return m_list.length();

    }
    int eCount()
    {
        int ret=0;
        for(m_list.move(0);!m_list.end();m_list.next())
        {
            ret+=(m_list.current()->edge.length());
        }
        return ret;

    }
    int OD(int i)
    {
        int ret=0;
        if((0<=i)&&(i<vCount()))
        {
            ret=m_list.get(i)->edge.length();//原来直接在这里返回

        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"index i is invalid...");
        }

        return ret;



    }
    int ID(int i)
    {
        int ret=0;
        if((0<=i)&&(i<vCount()))
        {
            for(m_list.move(0);!m_list.end();m_list.next())//re
            {
                Vertex* vertex=m_list.current();//LinkList<Edge<E>>& edge =m_list.current()->edge
                for(vertex->edge.move(0);!vertex->edge.end();vertex->edge.next())
                {
                    if(vertex->edge.current().b==i)
                    {
                        ret++;
                    }
                }
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"index i is invalid...");
        }
        return ret;


    }
    ~ListGraph()
    {
        while(m_list.length()>0)
        {
            Vertex* todel=m_list.get(0);
            m_list.remove(0);
            delete todel->data;
            delete todel;
        }
    }


};
}

#endif // LISTGRAPH_H
