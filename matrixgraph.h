#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "graph.h"
#include "exception.h"
#include"dynamicarray.h"
#include<iostream>
using namespace std;
namespace DTLib {

template <int N,typename V,typename E>
class MatrixGraph :public Graph<V,E>
{
protected:
    V* m_Vertexes[N];
    E* m_Edges[N][N];
    int m_eCount;
public:
    MatrixGraph()
    {
        for(int i=0;i<vCount();i++)
        {
            m_Vertexes[i]=NULL;
            for(int j=0;j<vCount();j++)
            {
                m_Edges[i][j]=NULL;
            }
        }
        m_eCount=0;

    }

    V getVertex(int i)
    {
        V re;
        if(getVertex(i, re))
        {

        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"the parameter i is invalid...");

        }
        return re;

    }
     bool getVertex(int i, V& value)
     {
         bool ret=(0<=i)&&(i<vCount());
         if(ret)
         {
             if((m_Vertexes[i])!=NULL)
             {
                 value=*(m_Vertexes[i]);

             }
             else
             {
                 THROW_EXCEPTION(InvalidOperationException,"the vertex is null...");
             }


         }

         return ret;
     }
     bool setVertex(int i, const V value)
     {
         bool ret=(0<=i)&&(i<vCount());
         if(ret)
         {
             /**/
             V*data=NULL;//保证异常安全  also V*data=m_Vertexes[i]
             if((m_Vertexes[i])==NULL)
             {
                 //m_Vertexes[i]=new V();
                 data=new V(); //保证异常安全
                 if(data==NULL)
                 {
                     THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new vertex...");
                 }
             }
             //*(m_Vertexes[i])=value;//不能保证异常安全，若有异常，图被改变
            (*data)=value;//保证异常安全
             m_Vertexes[i]=data;//保证异常安全




         }

         return ret;


     }
     SharedPointer< Array<int> > getAdjacent(int i)
     {
         DynamicArray<int>* ret=NULL;
         if((0<=i)&&(i<vCount()))
         {
             int n=0;
             for(int j=0;j<vCount();j++)//
             {
                 if(m_Edges[i][j]!=NULL)
                 {
                     n++;
                 }
             }
             ret=new DynamicArray<int>(n);
             for(int j=0,k=0;j<vCount();j++)//int j=0,int k=0;j<vCount();j++
             {
                 if(m_Edges[i][j]!=NULL)
                 {
                     ret->set(k++,j);
                 }
             }

         }
         else
         {
             THROW_EXCEPTION(InvalidParameterException,"the parameter i is invalid...");

         }

         return ret;


     }

     bool isAdjacent(int i,int j)
     {
         return (0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount())&&(m_Edges[i][j]!=NULL);//&&(m_Edges[j,i]!=NULL)&&(*m_Edges[j,i]==(*m_Edges[i,j]))//m_Edges[i,j
     }
     E getEdge(int i,int j)
     {
         E ret=NULL;

         if(!getEdge(i,j,ret))
         {

             THROW_EXCEPTION(InvalidOperationException," <i,j> is invalid...");

         }
         return  ret;

     }
     bool getEdge(int i, int j, E& value)
     {
         bool ret=(0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount());
         if(ret)
         {

             if((m_Edges[i][j])!=NULL)
             {
                 value=*(m_Edges[i][j]);

             }
             else
             {
//
                 THROW_EXCEPTION(InvalidOperationException," <i,j> is invalid...");
             }


         }

         return ret;

     }
     bool setEdge(int i, int j, const E& value)
     {
         bool ret=(0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount());
         if(ret)
         {
             E* tem=m_Edges[i][j];
             if(tem==NULL)
             {
                 tem=new E();
                 if(tem==NULL)
                 {
                     THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new edge object...");
                 }
                 else
                 {

                      *tem=value;
                       m_Edges[i][j]=tem;
                        m_eCount++;

                 }

             }
             else//loule
             {
                 *tem=value;
                 //m_Edges[i][j]=tem;//louel!!!

             }

            // m_eCount++;XXX
             //m_Edges[i][j]=tem;XXX


         }
         return ret;

     }
     bool removeEdge(int i, int j)
     {
         bool ret=(0<=i)&&(i<vCount())&&(0<=j)&&(j<vCount());
         if(ret)
         {
             if(m_Edges[i][j]!=NULL)
             {
                 E* todel=m_Edges[i][j];
                // if(todel!=NULL)

                 m_Edges[i][j]=NULL;

                 m_eCount--;
                 delete todel;


             }
             else
             {
                 THROW_EXCEPTION(InvalidOperationException,"the edge   is invalid...");

             }
         }
         return ret;


     }
     int vCount()
     {
         return N;
     }
     int eCount()
     {
         return m_eCount;
     }
     int OD(int i)
     {
         int ret=0;
         if((0<=i)&&(i<vCount()))
         {
             for(int k=0;k<vCount();k++)
             {
                 if(m_Edges[i][k]!=NULL)//m_Edges[i,k]//二未数组写成一维数组
                 {
                     //cout<<"Od:k:"<<k<<endl;
                    //cout<<"*m_Edges[i,k]:"<<*m_Edges[i,k]<<endl;
                     ret++;
                 }
             }

         }
         else
         {
             THROW_EXCEPTION(InvalidOperationException,"i  is invalid...");

         }

         return ret;
     }
     int ID(int i)
     {
         int ret=0;
         if((0<=i)&&(i<vCount()))
         {
             for(int k=0;k<vCount();k++)
             {
                 if(m_Edges[k][i]!=NULL)
                 {
                     //cout<<"Id:k:"<<k<<endl;
                     ret++;
                 }
             }

         }
         else
         {
             THROW_EXCEPTION(InvalidOperationException,"i  is invalid...");

         }

         return ret;
     }
     ~MatrixGraph()
     {
         for(int i=0;i<vCount();i++)
         {

             for(int j=0;j<vCount();j++)
             {
                 delete m_Edges[i][j];
             }
             delete  m_Vertexes[i];
         }
         //m_eCount=0;

     }
};

}

#endif // MATRIXGRAPH_H
