#ifndef GRAPH_H
#define GRAPH_H
#include "object.h"
#include "sharedpointer.h"
#include"array.h"
#include"linkqueue.h"
#include"dynamicarray.h"
#include"linkstack.h"
#include<iostream>
#include"sort.h"
using namespace std;

namespace DTLib {
template <  typename E>
struct Edge :public Object
{
    int a;
    int b;
    E data;//权重
    Edge (int ma=-1,int mb=-1)
    {
        a=ma;
        b=mb;
    }
    Edge (int ma,int mb,const E& value)
    {
        a=ma;
        b=mb;
        data=value;
    }
    Edge(const Edge<E>& e)
    {
        a=e.a;
        b=e.b;
        data=e.data;
    }

    bool operator ==(const Edge<E>& e)//只要起点和终点一样，就相等
    {
        return (a==e.a)&&(b==e.b);
    }
    bool operator !=(const Edge<E>& e)//只要起点和终点一样，就相等
    {
        return !(*this==e);
    }
    bool operator >(const Edge<E>& e)//只要起点和终点一样，就相等
    {
        return (this->data>e.data);
    }
    bool operator <(const Edge<E>& e)//只要起点和终点一样，就相等
    {
        return (this->data<e.data);
    }
};

    template < typename V, typename E>
    class Graph:public Object
    {
    protected:
        template <typename T>
        DynamicArray<T>* toarray(LinkQueue<T>& r)
        {
            DynamicArray<T>* ret=new DynamicArray<T>(r.length());//new DynamicArray(r.length())
            //cout<<"r.length:"<<r.length()<<endl;
            int len=r.length();
            if(ret!=NULL)//loule
            {
                for(int i=0;i<len;i++)//不能用r.length,一直在变化，直接用ret.length
                {
                    ret->set(i,r.front());
                    //cout<<"r.front:"<<r.front()<<endl;
                    r.remove();//XXXX
                }

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no memory to create new dynamic array object...");
            }

            return ret;
        }
        SharedPointer<Array<Edge<E>>> getUndirectedEdges()
        {
            DynamicArray<Edge<E>>* ret=NULL;
            if(asundirected())
            {
                LinkQueue<Edge<E>> queue;
                for(int i=0;i<vCount();i++)
                {
                    for(int j=0;j<vCount();j++)
                    {
                        if(isAdjacent(i,j))
                        {
                            queue.add(Edge<E>(i,j,getEdge(i,j)));
                        }
                    }
                }
                ret=toarray(queue);

            }

            else
            {

                THROW_EXCEPTION(InvalidParameterException,"the function is only for undirected graph...");
            }


            return ret;
        }

        int find(Array<int>& arr,int v)//找标记前驱数据
        {
            while(arr[v]!=-1)
            {
                v=arr[v];
            }
            return v;
        }
    public:
    virtual V getVertex(int i) =0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
    virtual bool isAdjacent(int i,int j)=0;
    virtual E getEdge(int i,int j)=0;
    virtual bool getEdge(int i, int j, E& value) =0;
    virtual bool setEdge(int i, int j, const E& value) =0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) =0;
    virtual int ID(int i) = 0;
    virtual int TD(int i)
        {
            return OD(i)+ID(i);

        }

        SharedPointer<Array<int>> bfs(int i)
        {
            DynamicArray<int>* r=NULL;
            if((0<=i)&&(i<vCount()))
            {
                LinkQueue<int> queue;
                LinkQueue<int> ret;
                DynamicArray<bool>visited(vCount());

                for(int j=0;j<vCount();j++)
                {
                    visited[j]=false;

                }
                queue.add(i);
                while(queue.length()>0)
                {
                    int pos=queue.front();
                    queue.remove();

                    if(!visited[pos])
                    {
                        SharedPointer<Array<int>> pj=getAdjacent(pos);
                        for(int j=0;j<pj->length();j++)
                        {
                           // cout<<"(*pj)[i]:"<<(*pj)[i]<<endl;
                            queue.add((*pj)[j]);
                        }
                        cout<<"pos:"<<pos<<endl;
                        ret.add(pos);
                        visited[pos]=true;
                    }
                }

                r=toarray(ret);

            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"index i is invalid...");
            }


            return r;
        }

        SharedPointer<Array<int>> dfs(int i)
        {
            DynamicArray<int>* r=NULL;
            if((0<=i)&&(i<vCount()))
            {
                LinkStack<int> stack;
                LinkQueue<int> ret;
                DynamicArray<bool>visited(vCount());

                for(int j=0;j<vCount();j++)
                {
                    visited[j]=false;

                }
                stack.push(i);
                while (stack.size()>0)
                {
                    int pos=stack.top();
                    stack.pop();

                    if(!visited[pos])
                    {
                        SharedPointer<Array<int>> pj=getAdjacent(pos);
                        for(int j=pj->length()-1;j>-1;j--)//int j=0;j<pj->length();j++ ??为啥一定要倒序，为了保证出栈是正确的顺序
                        {
                           // cout<<"(*pj)[i]:"<<(*pj)[i]<<endl;
                            stack.push((*pj)[j]);
                        }
                        cout<<"pos:"<<pos<<endl;
                        ret.add(pos);
                        visited[pos]=true;
                    }

                }
                r=toarray(ret);

            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"index i is invalid...");
            }

            return r;
        }
        bool asundirected()
        {
            bool ret=true;
            for(int i=0;i<vCount()&&ret;i++)//&&ret
            {
                for(int j=0;j<vCount()&&ret;j++)//j=i+1
                {
                    if(isAdjacent(i,j))
                    {
                       //cout<<"length"<<i<<":"<<j<<endl;

                        ret=isAdjacent(j,i)&&(getEdge(i,j)==getEdge(j,i));//ret&&
                        //if(!ret)break;

                       // cout<<"length2"<<endl;
                    }//isAdjacent(i,j)

                }
            }
            return ret;
        }
        SharedPointer<Array<Edge<E>>> prim(const E& Limit,const bool MINIMUM=true)//最小生成树
        {

            LinkQueue<Edge<E>> ret;
            /**/
            if(asundirected())//
            {
                //cout<<"asundirected()"<<endl;
                DynamicArray<bool>mark(vCount());//T false F集合  true
                DynamicArray<E>cost(vCount());
                DynamicArray<int> adjVex(vCount());
                SharedPointer<Array<int>> aj=NULL;//
                bool end=false;//区分有没有在F集合
                int v=0;//

                for(int i=0;i<vCount();i++)
                {
                    mark[i]=false;
                    cost[i]=Limit;
                    adjVex[i]=-1;
                }
                mark[v]=true;
                aj=getAdjacent(v);

                for(int i=0;i<aj->length();i++)
                {
                    cost[(*aj)[i]]=getEdge(v,(*aj)[i]);
                    adjVex[(*aj)[i]]=v;

                }

                for(int i=0;i<vCount()&&!end;i++)   //!end 都不满足
                {
                     E min=Limit;
                     int k=-1;
                     for(int j=0;j<vCount();j++)
                     {
                         if(!mark[j]&&(MINIMUM?(min>cost[j]):(min<cost[j])))
                         {


                                 min=cost[j];
                                 k=j;

                         }
                     }

                     end=(k==-1);//若都不满足，就停止循环


                     if(!end)//如果找到了，加入队列
                     {

                         ret.add(Edge<E>(adjVex[k],k,getEdge(adjVex[k],k)));

                         mark[k]=true;//标记顶点进入T集合

                         aj=getAdjacent(k);
                         for(int j=0;j<aj->length();j++)
                         {
                             if(!mark[(*aj)[j]]&&(MINIMUM?(getEdge(k,(*aj)[j])<cost[(*aj)[j]]):(getEdge(k,(*aj)[j])>cost[(*aj)[j]])))//F集合
                             {
                                 cost[(*aj)[j]]=getEdge(k,(*aj)[j]);
                                 adjVex[(*aj)[j]]=k;//i


                             }
                         }
                     }

                }


            }
            else
            {

                THROW_EXCEPTION(InvalidParameterException,"the graph is not undirected,cannot prim...");
            }
            if(ret.length()!=(vCount()-1))
            {

                THROW_EXCEPTION(InvalidParameterException,"no enough edge for prim operation...");
            }

            return toarray(ret);




        }
        SharedPointer<Array<Edge<E>>> Kruskal(const bool MINIMUM=true)
        {
            LinkQueue<Edge<E>> ret;
            DynamicArray<int> p(vCount());
            SharedPointer<Array<Edge<E>>> Edges=getUndirectedEdges();

            for(int i=0;i<p.length();i++)
            {
                p[i]=-1;

            }
            Sort::Shell(*Edges,MINIMUM);

            for(int i=0;(i<Edges->length())&&(ret.length()<vCount()-1);i++)
            {
                int b=find(p,(*Edges)[i].a);
                int e=find(p,(*Edges)[i].b);
                if(b!=e)
                {
                    p[e]=b;
                    ret.add((*Edges)[i]);//    Edge<E>(b,e,getEdge(b,e))
                }
            }
            if(ret.length()!=(vCount()-1))
            {

                THROW_EXCEPTION(InvalidParameterException,"no enough edge for kruskal operation...");
            }

            return toarray(ret);

        }

        SharedPointer<Array<int>> dijkstra(int i,int j,const E LIMIT)
        {
            LinkQueue<int> ret;
            if((i>=0)&&(i<vCount())&&(j>=0)&&(j<vCount()))
            {
                DynamicArray<E> dist(vCount());
                DynamicArray<int> path(vCount());
                DynamicArray<bool> mark(vCount());

                for(int m=0;m<vCount();m++)
                {
                    path[m]=-1;
                    mark[m]=false;
                    dist[m]=isAdjacent(i,m)?(path[m]=i,getEdge(i,m)):LIMIT;//(path[k]=i,
                }
                mark[i]=true;

                for(int k=0;k<vCount();k++)//循环有啥用？？？？ mark一次循环只能标记一个点
                {
                    E m=LIMIT;
                    int u=-1;
                    for(int w=0;w<vCount();w++)//找最小路径值
                    {
                        if(!mark[w]&&(m>dist[w]))
                        {
                            m=dist[w];
                            u=w;
                        }

                    }

                    if(u==-1)//找不到 例如只有顶点，没有边
                    {
                        break;


                    }

                    mark[u]=true;
                    for(int w=0;w<vCount();w++)//通过已知的顶点的路径，与原来的路径比较，如果小就更新
                    {
                        if(!mark[w]&&isAdjacent(u,w)&&(dist[u]+getEdge(u,w)<dist[w]))//判断有没有边
                        {
                            dist[w]=dist[u]+getEdge(u,w);
                            path[w]=u;//路径的前驱节点
                        }
                    }

}

                LinkStack<int> sa;//路径是倒过来的
                sa.push(j);
                for(int k=path[j];k!=-1;k=path[k])
                {
                    sa.push(k);
                }
                while(sa.size()>0)
                {
                    ret.add(sa.top());
                    sa.pop();
                }



            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"index i,j is invalid ...");
            }
            if(ret.length()<2)
            {
                THROW_EXCEPTION(ArithmeticException,"There is no path from i to j...");

            }
            return toarray(ret);
        }

        SharedPointer<Array<int>> Flyod(int x,int y,const E& LIMIT)//int ----->  SharedPointer<Array<int>>  返回最短路径值， 最短路径序列
        {
            LinkQueue<int > ret;//int ret=-1;  LinkQueue<int > ret=NULL;  =NULL
            if((0<=x)&&(x<vCount())&&(0<=y)&&(y<vCount()))
            {
                DynamicArray<DynamicArray<E>> dist(vCount());
                DynamicArray<DynamicArray<int>> path(vCount());//增加路径

                for(int i=0;i<vCount();i++)
                {
                    dist[i].resize(vCount());
                    path[i].resize(vCount());//
                }
                for(int i=0;i<vCount();i++)
                {
                    for(int j=0;j<vCount();j++)
                    {
                        if(isAdjacent(i,j))
                        {
                            dist[i][j]=getEdge(i,j);
                            path[i][j]=j;//
                        }
                        else
                        {
                            dist[i][j]=LIMIT;
                            path[i][j]=-1;//
                        }

                    }
                }
                for(int k=0;k<vCount();k++)
                {
                    for(int i=0;i<vCount();i++)
                    {
                        for(int j=0;j<vCount();j++)
                        {
                            if(dist[i][j]>(dist[i][k]+dist[k][j]))
                            {
                                   dist[i][j]=dist[i][k]+dist[k][j];
                                   path[i][j]=path[i][k];//k;//i到j的第一个顶点 就是 i到k的第一个顶点
                            }


                        }
                    }

                }
                //ret=dist[x][y];
                while ((x!=-1)&&x!=y) //起点有效，起点终点不是一个点
                {
                   ret.add(x);
                   x=path[x][y];
//                   while (x!=-1)
//                   {
//                       ret.add(x);
//                       x=path(x,y);

//                   }
                }
                if(x!=-1)//加上终点
                {
                    ret.add(x);

                }

            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"index i,j is invalid ...");
            }
            if(ret.length()<2)//
            {
                THROW_EXCEPTION(ArithmeticException,"There is no path from i to j...");

            }

            return toarray(ret);//ret;

        }

    };




}

#endif // GRAPH_H
