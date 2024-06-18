#include <iostream>
#include "gtree.h"
#include"linkstack.h"
#include"staticstack.h"
#include "matrixgraph.h"
#include "listgraph.h"
#include<cstdlib>
#include"exception.h"
#include"sharedpointer.h"
#include"sort.h"
#include"dtstring.h"
using namespace std;
using namespace DTLib;

class Test:public Object
{


public:
    int value;
    Test():value(0)
    {
        //value=m;
        cout<<"Test()"<<endl;
    }


    ~Test()
    {
        cout<<"~Test()"<<endl;

    }
};

//void Josephus(int n,int s,int m)//人数 开始数字 末尾数字
//{
//    CircleList<int> cl;
//    for(int i=1;i<=n;i++)
//    {
//        cl.insert(i);

//    }


//    while(cl.length()>0)
//    {
//        for(cl.move(s-1+2,m-1);!cl.end();cl.next())//下标为2,值为3的节点开始
//        {

//            cout<<cl.current()<<endl;
//            cl.remove(cl.find(cl.current()));
//        }

//    }


//}
template<typename V,typename E>
void DFS(Graph<V,E>& g,int v,DynamicArray<bool>& visited)//&
{
    if((0<=v)&&(v<g.vCount()))
    {
        cout<<v<<endl;
        visited[v]=true;


        SharedPointer<Array<int>> ad=g.getAdjacent(v);//DynamicArray<int>
                    for(int i=0;i<ad->length();i++)
                    {
                        if(!visited[(*ad)[i]])
                        {
                            DFS(g,(*ad)[i],visited);
                        }

                    }
//        if(ad==NULL)//E:\qtFile\DTLib\main.cpp:61: error: no match for 'operator==' (operand types are 'DTLib::DynamicArray<int>' and 'int')

//        {
//            if(!visited[v])
//            cout<<v<<endl;
//            visited[v]=true;


//        }
//        else

//        {
//            if(!visited[v])
//            cout<<v<<endl;
//            visited[v]=true;
//            for(int i=0;i<(*ad).length();i++)
//            {
//                if(!visited[(*ad)[i]])
//                {
//                    DFS(g,(*ad)[i],visited);
//                }

//            }

//        }

    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException,"v is invalid...");
    }



}
template<typename V,typename E>
void DFS(Graph<V,E>& g,int v)
{
    DynamicArray<bool> visited(g.vCount());
    for(int i=0;i<visited.length();i++)//g.vCount()
    {
        visited[i]=false;
    }
    DFS(g,v,visited);

}
template< typename V, typename E >
Graph<V, E>& GraphEasy()
{
    static MatrixGraph<4, V, E> g;

    g.setEdge(0, 1, 1);
    g.setEdge(0, 2, 3);
    g.setEdge(1, 2, 1);
    g.setEdge(1, 3, 4);
    g.setEdge(2, 3, 1);

    return g;
}

template< typename V, typename E >
Graph<V, E>& GraphComplex()
{
    static ListGraph<V, E> g(5);

    g.setEdge(0, 1, 10);
    g.setEdge(0, 3, 30);
    g.setEdge(0, 4, 100);

    g.setEdge(1, 2, 50);

    g.setEdge(2, 4, 10);

    g.setEdge(3, 2, 20);
    g.setEdge(3, 4, 60);

    return g;
}
int main()
{
    String s;
    s="asdfsdfg";
    for(int i=0;i<s.length();i++)
    {
        cout<<s[i]<<endl;
    }
    cout<<s.StartWith("as1d")<<endl;
    cout<<s.EndOf("df2g")<<endl;
    /*
    Graph<int, int>& g = GraphComplex<int, int>();
        SharedPointer< Array<int> > p = g.dijkstra(0, 4, 65535);

        for(int i=0; i<p->length(); i++)
        {
            cout << (*p)[i] << " ";
        }

        cout << endl;*/

    /*
    int n[3][3]={1,2,3,4,5,6,7,8,9};

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<n[i,j]<<endl;//相当于行矩阵的首地址
        }
    }
                  cout<<&n[0][0]<<endl;*/

    /*
    Graph<int,int>& g1=graphcomplex<int,int>();//<int,int>


    SharedPointer<Array<Edge<int>>> sa1=g1.Kruskal(false);//(65535);prim(0,false)

    int w=0;
    for(int i=0;i<sa1->length();i++)
    {
        w+=(*sa1)[i].data;
        cout<<"begin:"<<(*sa1)[i].a<<"  end:"<<(*sa1)[i].b<<" "<<(*sa1)[i].data<<endl;
    }
    cout<<"w="<<w<<endl;*/






    /*
    int arr[]={7,9,3,8,2,6,4,5,1,9};
    for(int i=0;i<10;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"shell sort:"<<endl;
    Sort::Bubble(arr,10,false);//,false  ,false
    for(int i=0;i<10;i++)
    {
        cout<<arr[i]<<endl;
    }*/
    /*
    String s;
    s='D';
    cout<<s.str()<<endl;
    cout<<s.length()<<endl;
    cout<<(s=="D")<<endl;
    cout<<(s>"CC")<<endl;
   s+=" asdf";
   cout<<s.str()<<endl;
   cout<<s.length()<<endl;
   cout<<(s=="D asdf")<<endl;*/


/*
    MatrixGraph<9,char,int> g;
    const char* VD="ABCDEFGHI";
    for(int i=0;i<9;i++)
    {
        g.setVertex(i,VD[i]);
    }
    g.setEdge(0,1,0);
    g.setEdge(1,0,0);

    g.setEdge(0,3,0);
    g.setEdge(3,0,0);

    g.setEdge(0,4,0);
    g.setEdge(4,0,0);

    g.setEdge(1,2,0);
    g.setEdge(2,1,0);

    g.setEdge(2,5,0);
    g.setEdge(5,2,0);

    g.setEdge(1,4,0);
    g.setEdge(4,1,0);

    g.setEdge(3,6,0);
    g.setEdge(6,3,0);


    g.setEdge(4,6,0);
    g.setEdge(6,4,0);

    g.setEdge(6,7,0);
    g.setEdge(7,6,0);

    g.setEdge(7,8,0);
    g.setEdge(8,7,0);

    SharedPointer<Array<int>> pj=g.bfs(0);

    for(int i=0;i<pj->length();i++)
    {
        cout<<(*pj)[i]<<"   ";
    }
    cout<<endl;
    for(int i=0;i<9;i++)
    {
    cout<<i<<":"<<g.getVertex(i)<<" ";
    }
    cout<<endl;

    SharedPointer<Array<int>> dj=g.dfs(0);

    for(int i=0;i<dj->length();i++)
    {
        cout<<(*dj)[i]<<"   ";
    }
    cout<<endl;
    DFS(g,0);*/

    /**/

//    ListGraph<char,int> g;//(4)



//    g.addVertex('A');

//    g.addVertex('B');
//    g.addVertex('C');
//    g.addVertex('D');
//    //g.removeVertex();
//    for(int i=0;i<g.vCount();i++)
//    {

//        cout<<i<<":"<<g.getVertex(i)<<endl;
//    }

//    g.setEdge(0,1,5);
//    g.setEdge(0,3,6);
//    g.setEdge(1,2,8);
//    g.setEdge(2,3,2);
//    g.setEdge(3,1,9);

//  cout<<"w(0,1):"<<g.getEdge(0,1)<<endl;
//  cout<<"w(0,3):"<<g.getEdge(0,3)<<endl;
//  cout<<"w(1,2):"<<g.getEdge(1,2)<<endl;
//  cout<<"w(2,3):"<<g.getEdge(2,3)<<endl;
//  cout<<"w(3,1):"<<g.getEdge(3,1)<<endl;

//  cout<<"ecount:"<<g.eCount()<<endl;

////g.removeEdge(3,1);
////cout<<"w(3,1):"<<g.getEdge(3,1)<<endl;
// cout<<"ecount:"<<g.eCount()<<endl;

// SharedPointer<Array<int>> pj=g.getAdjacent(0);
// for(int i=0;i<pj->length();i++)
// {
//     cout<<"adjace:"<<(*pj)[i]<<endl;
// }

// cout<<"vcount:"<<g.vCount()<<endl;

// cout<<"ID0:"<<g.ID(0)<<endl;
// cout<<"OD0:"<<g.OD(0)<<endl;
// cout<<"TD0:"<<g.TD(0)<<endl;


// cout<<"ID1:"<<g.ID(1)<<endl;


//     cout<<"vcount:"<<g.vCount()<<endl;
//     cout<<"OD1:"<<g.OD(1)<<endl;



// cout<<"TD1:"<<g.TD(1)<<endl;
// g.removeVertex();

//cout<<"ecount:"<<g.eCount()<<endl;
//cout<<"w(0,1):"<<g.getEdge(0,1)<<endl;

//cout<<"w(1,2):"<<g.getEdge(1,2)<<endl;
////cout<<"w(0,3):"<<g.getEdge(0,3)<<endl;
         //b.clear();
         //SharedPointer<Tree<int>> sp=b.remove(3);//=b.remove(3);//SharedPointer<BTree<int>>   error: conversion from 'DTLib::SharedPointer<DTLib::Tree<int> >' to non-scalar type 'DTLib::SharedPointer<DTLib::BTree<int> >' requested

        //SharedPointer<BTree<int>> sp=dynamic_cast<BTree<int>*>(b.remove(3));error: cannot dynamic_cast 'DTLib::BTree<T>::remove(const T&) [with T = int](3)' (of type 'class DTLib::SharedPointer<DTLib::Tree<int> >') to type 'class DTLib::BTree<int>*' (source is not a pointer)
        /*
         int a[]={8,9,10,6,7};
         //cout<<"sta"<<endl;
         for(int i=0;i<5;i++)
         {
             TreeNode<int> *node=b.find(a[i]);//删除后的子树
             //TreeNode<int> *node=sp->find(a[i]);//被删掉的子树
            // cout<<"i"<<endl;
             while(node)
                {
             //cout<<"asdfdf";
                    cout<<node->value<<" ";
                    node=(node->parent);

                }
                    cout<<endl;


         }

         cout<<b.count()<<endl;
         cout<<b.height()<<endl;
         cout<<b.degree()<<endl;*/
//         for(b.begin();!b.end();b.next())
//         {
//           cout<<b.current()<<endl;

//         }









//    b.find(1);
//    b.find(bn);
//    GTree<char> tt;
//    GTreeNode<char>* node=NULL;
//    GTreeNode<char> root;
//    root.parent=NULL;
//    root.value='A';
//    tt.insert(&root);//在栈上面
//   // tt.insert('A',NULL);

//   node=tt.find('A');
//   tt.insert('B',node);

//   tt.insert('C',node);

//   tt.insert('D',node);

//   node=tt.find('B');
//   tt.insert('E',node);

//   tt.insert('F',node);

//   node=tt.find('E');
//   tt.insert('K',node);

//   tt.insert('L',node);

//   node=tt.find('C');
//   tt.insert('G',node);

//   node=tt.find('D');
//   tt.insert('H',node);
//   tt.insert('I',node);
//   tt.insert('J',node);

//   node=tt.find('H');
//   tt.insert('M',node);
//   //tt.clear();
//   //tt.remove('D');
//   //tt.remove(tt.find('D'));
//   SharedPointer<Tree<char>> p=tt.remove(tt.find('D'));
//   char gen[]="KLFGMIJ";
//   for(int i=0;i<7;i++)
//   {
//       TreeNode<char>* node=tt.find(gen[i]);
//       while(node)
//       {
//           cout<<node->value<<" ";
//           node=node->parent;

//       }
//       cout<<endl;


//   }
//   for(int i=0;i<7;i++)//打印子树
//   {
//       TreeNode<char>* node=p->find(gen[i]);
//       while(node)
//       {
//           cout<<node->value<<" ";
//           node=node->parent;

//       }
//       cout<<endl;


//   }
//    cout<<tt.count()<<endl;
//    cout<<tt.height()<<endl;
//    cout<<tt.degree()<<endl;
//    for(tt.begin();!tt.end();tt.next())
//    {
//        cout<<tt.current()<<endl;
//    }
//    DualCircleList<int> dl;
//    for(int i=0;i<5;i++)
//    {
//        dl.insert(0,i);
//        dl.insert(0,5);
//    }
//    int count=0;

//    for(int i=0;i<dl.length();i++)
//    {
//        cout<<dl.get(i)<<endl;
//    }
//    for(dl.move(0);!dl.end();dl.next())
//    {
//        cout<<dl.current()<<endl;
//        count++;
//       if(count>=20)break;
//    }
//    for(dl.move(dl.length()-1);!dl.end();dl.pre())
//    {
//        cout<<dl.current()<<endl;
//        count++;
//        if(count>=20)break;
//    }
    /**/
    //    dl.move(dl.length()-1);
    //    cout<<"begin..."<<endl;
    //    while(dl.find(5)!=-1)
    //    {
    //        if(dl.current()==5)
    //        {
    //            cout<<dl.current()<<"dl.find(dl.current()):"<<dl.find(dl.current())<<endl;//游标移动的方向和find的方向相反，当游标移动到倒数第二个元素是时候，删除的其实是下标0的元素
    //            dl.remove(dl.find(dl.current()));
    //        }
    //        else
    //        {
    //            cout<<dl.current()<<endl;
    //            dl.pre();//当是5的时候不用跳
    //        }


    //    }

//     cout<<"begin..."<<endl;
//     for(int i=0;i<10;i++)
//     {
//         cout<<dl.get(i)<<endl;
//     }
    //duallinklist test

//    DualLinkList<int> dl;
//    for(int i=0;i<5;i++)
//    {
//        dl.insert(0,i);
//        dl.insert(0,5);
//    }
//    for(dl.move(0);!dl.end();dl.next())
//    {
//        cout<<dl.current()<<endl;
//    }
//    for(dl.move(dl.length()-1);!dl.end();dl.pre())
//    {
//        cout<<dl.current()<<endl;
//    }
//    dl.move(dl.length()-1);
//    cout<<"begin..."<<endl;
//    while(!dl.end())
//    {
//        if(dl.current()==5)
//        {
//            cout<<dl.current()<<"dl.find(dl.current()):"<<dl.find(dl.current())<<endl;//游标移动的方向和find的方向相反，当游标移动到倒数第二个元素是时候，删除的其实是下标0的元素
//            dl.remove(dl.find(dl.current()));
//        }
//        else
//        {
//            cout<<dl.current()<<endl;
//            dl.pre();//当是5的时候不用跳
//        }
//        //dl.pre();//不对，当是5的时候不用跳，游标倒过来移动，find正向寻找
//        //cout<<"pre:"<<dl.current()<<endl;//游标最后会为空，抛出异常

//    }

//     cout<<"begin..."<<endl;


//    for(dl.move(dl.length()-1);!dl.end();dl.pre())
//    {
//        cout<<dl.current()<<endl;
//    }
    //Josephus(41,1,3);

//    LinkQueue<int> lq;
//    for(int i=0;i<10;i++)
//    {
//        lq.add(i);

//    }
//    while(lq.length()>0)
//    {
//        cout<<lq.front()<<endl;
//        lq.remove();
//    }

//    StaticQueue<int,5> dd;
//    try{
//        dd.remove();
//    }
//    catch(const Exception& e)
//    {
//        cout<<e.message()<<endl;
//        cout<<e.location()<<endl;
//    }

//    for(int i=0;i<5;i++)
//    {
//        dd.add(i);
//    }
//    while(dd.length()>0)
//    {
//        cout<<dd.front()<<endl;
//        dd.remove();
//    }

//    StaticStack<int,5> dd;
//    try{
//        dd.pop();
//    }
//    catch(const Exception& e)
//    {
//        cout<<e.message()<<endl;
//        cout<<e.location()<<endl;
//    }

//    for(int i=0;i<5;i++)
//    {
//        dd.push(i);
//    }
//    while(dd.size()>0)
//    {
//        cout<<dd.top()<<endl;
//        dd.pop();
//    }


//    GTree<int> t;// error: cannot declare variable 't' to be of abstract type 'DTLib::GTree<int>'//find函数在protected内有成员函数，public调用内部protected函数，注意输入参数类型
//    GTreeNode<int> tn;
//    GTree<char> tt;
//    GTreeNode<char>* node=NULL;
//    GTreeNode<char> root;
//    root.parent=NULL;
//    root.value='A';
//    tt.insert(&root);//在栈上面
//   // tt.insert('A',NULL);

//   node=tt.find('A');
//   tt.insert('B',node);

//   tt.insert('C',node);

//   tt.insert('D',node);

//   node=tt.find('B');
//   tt.insert('E',node);

//   tt.insert('F',node);

//   node=tt.find('E');
//   tt.insert('K',node);

//   tt.insert('L',node);

//   node=tt.find('C');
//   tt.insert('G',node);

//   node=tt.find('D');
//   tt.insert('H',node);
//   tt.insert('I',node);
//   tt.insert('J',node);

//   node=tt.find('H');
//   tt.insert('M',node);
//   //tt.clear();
//   cout<<tt.count()<<endl;
//   cout<<tt.height()<<endl;
//   cout<<tt.degree()<<endl;
//   for(tt.begin();!tt.end();tt.next())
//   {
//       cout<<tt.current()<<endl;
//   }
   //tt.remove('D');
   //tt.remove(tt.find('D'));
//   SharedPointer<Tree<char>> p=tt.remove(tt.find('D'));
//   char gen[]="KLFGMIJ";
//   for(int i=0;i<7;i++)
//   {
//       TreeNode<char>* node=tt.find(gen[i]);
//       while(node)
//       {
//           cout<<node->value<<" ";
//           node=node->parent;

//       }
//       cout<<endl;


//   }
//   for(int i=0;i<7;i++)//打印子树
//   {
//       TreeNode<char>* node=p->find(gen[i]);
//       while(node)
//       {
//           cout<<node->value<<" ";
//           node=node->parent;

//       }
//       cout<<endl;


//   }















    //Test 27;

//        SharedPointer<Test> pt=new Test();
//       SharedPointer<Test> ptn=pt;
//       SharedPointer<Test> ptm=NULL;
//       ptm=pt;
//       pt->value=3;

//        cout <<"pt->value:"<< pt->value << endl;
//       cout << "ptn->value:"<<ptn->value<< endl;
//       cout << "ptm->value:"<<ptm->value<< endl;
//       const SharedPointer<Test> spt=new Test();//const 调用const成员函数

//       cout<<(ptm==pt)<<endl; //重载比较函数 == !=

//       ptm.clear();
//       cout<<(ptm==pt)<<endl;



//        SmartPointer<Test> pt=new Test();
//        SmartPointer<Test> ptn;
//        cout <<"operator = test:" << endl;
//        cout <<"pt.isNull():"<< pt.isNull() << endl;
//        cout << "ptn.isNull():"<<ptn.isNull() << endl;

//        cout << "Hello World!" << endl;
//        ptn=pt;
//        cout <<"pt.isNull():"<< pt.isNull() << endl;
//        cout << "ptn.isNull():"<<ptn.isNull() << endl;

    return 0;
}




//case2:
//#include <iostream>
//#include "LinkList.h"

//using namespace std;
//using namespace DTLib;

//class Test : public Object
//{
//    int m_id;
//public:
//    Test(int id = 0)
//    {
//        m_id = id;
//    }


//    ~Test()
//    {
//        if( m_id == 1 )
//        {
//            throw m_id;
//        }
//    }
//};

//int main()
//{
//    LinkList<Test> list;
//    Test t0(0), t1(1), t2(2);

//    try
//    {
//        list.insert(t0);
//        list.insert(t1);//析构 抛出异常
//        list.insert(t2);

//        list.remove(1);
//    }
//    catch(int e)
//    {
//        cout << e << endl;
//        cout << list.length() << endl;//期望输出2
//        //gcc不允许析构抛出异常，程序中止
//        //vs 可以  输出  1
//       // 3
//    }

//    return 0;
//}

//case3:
//#include <iostream>
//#include "LinkList.h"

//using namespace std;
//using namespace DTLib;

//int main()
//{
//    LinkList<int> list;

//    for(int i=0; i<5; i++)
//    {
//        list.insert(i);
//    }

//    for(list.move(0); !list.end(); list.next())
//    {
//        if( list.current() == 3 )
//        {
//            list.remove(list.find(list.current()));
//            cout<<list.current()<<endl;

//        }
//        //cout<<list.current()<<endl;//删掉后还被打印，随机值
//    }
//    cout<<endl;

//    for(int i=0; i<list.length(); i++)
//    {
//        cout << list.get(i) << endl;
//    }

//    return 0;
//}


//case4:

//#include <iostream>
//#include "StaticLinkList.h"

//using namespace std;
//using namespace DTLib;

//int main()
//{
//    StaticLinkList<int, 10> list;

//    for(int i=0; i<5; i++)
//    {
//        list.insert(i);
//    }

//    list.remove(3);

//    for(int i=0; i<list.length(); i++)
//    {
//        cout << list.get(i) << endl;
//    }

//    return 0;
//}

//case5:

//case6:
//#include <iostream>
//#include "StaticLinkList.h"
//#include "DynamicArray.h"

//using namespace std;
//using namespace DTLib;

//int main()
//{
//    DynamicArray< DynamicArray<int> > d;//构造函数添加默认值0

//    d.resize(3);

//    for(int i=0; i<d.length(); i++)
//    {
//        d[i].resize(i + 1);
//    }

//    for(int i=0; i<d.length(); i++)
//       {
//           for(int j=0; j<d[i].length(); j++)
//           {
//               d[i][j] = i + j;
//           }
//       }

//       for(int i=0; i<d.length(); i++)
//       {
//           for(int j=0; j<d[i].length(); j++)
//           {
//               cout << d[i][j] << " ";
//           }

//           cout << endl;
//       }
//       return 0;

//       }
//       output:
//       void * Object::operator new[]
//       void * Object::operator new[]
//       void Object::operator delete[]
//       0
//       1 2
//       2 3 4
//       Object::~Object
//       Object::~Object
//       Object::~Object
//       void Object::operator delete[]
//       Object::~Object




//#include <iostream>

//#include "exception.h"

//using namespace std;
//using namespace DTLib;



//int main()
//{
//    //test26
//    //case1:
//    try
//    {
//        NullPointerException npe;

//        cout << "throw" << endl;

//        throw npe;
//    }
//    catch(const Exception& e)
//    {
//        cout << "catch" << endl;
//    }
//    output:
//    throw
//    Object::~Object     //临时对象析构
//    catch
//    Object::~Object      //npe对象析构
//    //glic代码 strdup函数并没有判断空 修改strdup

//    return 0;
//}





    //test25
//        StaticLinkList<int,5> li;//LinkList<int> li;
//        for(int i=0;i<5;i++)
//        {
//            li.insert(i);

//        }
//        try
//        {
//            li.insert(6);//异常

//        }
//        catch(const Exception& e)
//        {
//            cout<<e.message()<<endl;
//            cout<<e.location()<<endl;
//        }

//        for(li.move(0);!li.end();li.next())//
//        {
//            //cout<<"kk"<<endl;
//            cout<<li.current()<<endl;
//        }

    //test24
//        LinkList<int> li;
//        for(int i=0;i<5;i++)
//        {
//            li.insert(i);

//        }
//            for(int i=0;i<li.length();i++)
//            {
//                //int t;
//                //if(li.get(i,t))
//                cout<<"li["<<i<<"]="<<li.get(i)<<endl;
//            }
//        cout<<"kk"<<endl;
//        if(li.move(0,2))
//                cout<<"move((0,1)"<<endl;
//         cout<<li.current()<<endl;
//         if(li.next())
//                 cout<<"li.next()"<<endl;
//    for(li.move(0);!li.end();li.next())//li.end();li.next()   li.move(0,X)  1 2 3 4 5 6 ok  li.move(0)
//    {
//        //cout<<"kk"<<endl;
//        cout<<li.current()<<endl;
//    }

    //    //test12  test类继承Object 成员i，j   child类继承Test 成员k
//        Object* ob1=new Test();
//        Object* ob2=new child();
//        cout<<"ob1="<<ob1<<endl;
//        cout<<"ob2="<<ob2<<endl;
//        delete ob1;
//        delete ob2;
    //    output:
    //    void* Object::operator new size:12
    //    void* Object::operator new size:16
    //    ob1=0x761988
    //    ob2=0x7619a0
    //    Object::~Object
    //    void Object::operator:0x761988
    //    Object::~Object
    //    void Object::operator:0x7619a0

    //test23
//    LinkList<int> li;
//    for(int i=0;i<5;i++)
//    {
//        li.insert(0,i);

//    }
//    cout<<li.find(-1)<<endl;
//    output:
//    void* Object::operator new size:12
//    void* Object::operator new size:12
//    void* Object::operator new size:12
//    void* Object::operator new size:12
//    void* Object::operator new size:12
//    -1
//    Object::~Object
//    void Object::operator:0x7119e8
//    Object::~Object
//    void Object::operator:0x7119d0
//    Object::~Object
//    void Object::operator:0x7119b8
//    Object::~Object
//    void Object::operator:0x7119a0
//    Object::~Object
//    void Object::operator:0x711988
//    Object::~Object
//    Object::~Object

//    LinkList<int> li;
//    for(int i=0;i<1;i++)
//    {
//        li.insert(0,i);

//    }
//    output:
//    void* Object::operator new size:12
//    Object::~Object
//    void Object::operator:0xfd1988
//    Object::~Object
//    Object::~Object   为啥会有这么多析构函数？？？？
   // cout<<li.find(3)<<endl;


    //test22  头节点的问题：Test构造函数抛出异常实验
//    LinkList<Test> li;//terminate called after throwing an instance of 'int'
//    cout<<"asas"<<endl;
//    //Test t;//异常
//    //ok 后测试原来的例子


//LinkList<Test> ti;
//    LinkList<int> li;
//    for(int i=0;i<5;i++)
//    {
//        li.insert(0,i);
//        li.set(0,i*i); //ok
//    }
//    for(int i=0;i<li.length();i++)
//    {
//        //int t;
//        //if(li.get(i,t))
//        cout<<"li["<<i<<"]="<<li.get(i)<<endl;
//    }
//    li.remove(2);
//    //li.clear();//ok
//    for(int i=0;i<li.length();i++)
//    {
//        //int t;
//        //if(li.get(i,t))
//        cout<<"remove(2),li["<<i<<"]="<<li.get(i)<<endl;
//    }



//    //test20
//        DynamicArray<int> ss(5);
//        for(int i=0;i<ss.length();i++)
//       {
//           ss[i]=i;

//       }
//       ss.set(1,50);
//       //cout<<"length="<<ss.length()<<endl;

//       for(int i=0;i<ss.length();i++)
//       {
//           //int tem;
//           //if(ss.get(i,tem))
//           //cout<<"tem="<<tem<<endl;
//           cout<<"ss="<<ss[i]<<endl;

//       }
//      DynamicArray<int> sl(8);
//      sl=ss;//长度被改变
//      for(int i=0;i<sl.length();i++)
//      {
//          cout<<"sl="<<sl[i]<<endl;

//      }
//     // DynamicArray<int> se(ss);//拷贝构造实验
//      cout<<endl;
//     DynamicArray<int> se=ss;
//      for(int i=0;i<se.length();i++)
//      {
//          cout<<"se="<<se[i]<<endl;

//      }
//      sl.resize(10);
//      cout<<endl;
//      for(int i=0;i<sl.length();i++)
//      {
//          cout<<"sl="<<sl[i]<<endl;

//      }
//      sl.resize(3);
//      cout<<endl;
//      for(int i=0;i<sl.length();i++)
//      {
//          cout<<"sl="<<sl[i]<<endl;

//      }
//      try{
//          sl[5]=4;
//      }
//      catch(const Exception& e)
//      {
//          cout<<e.message()<<endl;
//          cout<<e.location()<<endl;
//      }








//   // test19
//    StaticArray<int,5> ss;
//    for(int i=0;i<ss.length();i++)
//       {
//           ss[i]=i;

//       }
//       ss.set(1,50);
//       cout<<"length="<<ss.length()<<endl;

//       for(int i=0;i<ss.length();i++)
//       {
//           int tem;
//           if(ss.get(i,tem))
//           cout<<"tem="<<tem<<endl;
//           cout<<"ss="<<ss[i]<<endl;

//       }

//       StaticArray<int,5> sl;
//       sl=ss;
//       for(int i=0;i<sl.length();i++)
//       {
//           cout<<"sl="<<sl[i]<<endl;

//       }
//       //sl[6]=230;//产生异常

//       int s3[5];
//       for(int i=0;i<5;i++)
//          {
//              s3[i]=i;

//          }
//       cout<<s3[3]<<endl;
//       s3[6]=100;//原生数组越界不会 预警






//            //test18
//            DynamicList<int> l(5);
//    DynamicList<int> n(5);
//    //DynamicList<int> nn=n;//拷贝构造禁用E:\qtFile\DTLib\seqlist.h:9: error: undefined reference to `DTLib::List<int>::List(DTLib::List<int> const&)'
//   // n=l;//赋值禁用E:\qtFile\DTLib\seqlist.h:9: error: undefined reference to `DTLib::List<int>::operator=(DTLib::List<int> const&)'

//    for(int i=0;i<l.captcity();i++)
//       {
//           l.insert(i);

//       }
//       cout<<"length="<<l.length()<<endl;

//       for(int i=0;i<l.length();i++)
//       {
//           cout<<"l="<<l[i]<<endl;

//       }

//    //test17
//    DynamicList<int> l(5);//DynamicList<int ,5> l;   DynamicList<int> [5]XXXX
//    cout<<"length="<<l.length()<<endl;

//    for(int i=0;i<l.captcity();i++)
//    {
//        l.insert(0,i);

//    }
//    cout<<"length="<<l.length()<<endl;

//    for(int i=0;i<l.length();i++)
//    {
//        cout<<"l="<<l[i]<<endl;

//    }
//    l[0]*=l[0];
//    try{

//        //gai
//        l.resize(10);
//        l[5]=5;
//    }
//    catch(const Exception& e)
//    {
//        cout<<e.message()<<endl;
//        cout<<e.location()<<endl;
//    }
//    l.insert(5,10);
//    l[5]=5;

//    for(int i=0;i<l.length();i++)
//    {
//        cout<<"l="<<l[i]<<endl;

//    }
//    l.resize(3);
//    for(int i=0;i<l.length();i++)
//    {
//        cout<<"l="<<l[i]<<endl;

//    }

//    StaticList<int ,5> l;
//    cout<<"length="<<l.length()<<endl;

//    for(int i=0;i<l.captcity();i++)
//    {
//        l.insert(0,i);

//    }
//    cout<<"length="<<l.length()<<endl;

//    for(int i=0;i<l.length();i++)
//    {
//        cout<<"l="<<l[i]<<endl;

//    }
//    l[0]*=l[0];
//    try{
//        l[5]=5;
//    }
//    catch(const Exception& e)
//    {
//        cout<<e.message()<<endl;
//        cout<<e.location()<<endl;
//    }

//    for(int i=0;i<l.length();i++)
//    {
//        cout<<"l="<<l[i]<<endl;

//    }


    //test16
      //SeqList<int> l;//抽象类 不能定义对象
      //SeqList<int>* l;

    //test14
//    List<int>* l=NULL;

    //test13
//    SmartPointer<int>* sp=new SmartPointer<int>();
//    //打断点 证明使用的手动定义的new

//    delete sp;
    //头文件
//    InvalidOperationException* a=new InvalidOperationException();
//    //打断点 证明使用的手动定义的new
//    delete a;



//    //test12  test类继承Object 成员i，j   child类继承Test 成员k
//    Object* ob1=new Test();
//    Object* ob2=new child();
//    cout<<"ob1="<<ob1<<endl;
//    cout<<"ob2="<<ob2<<endl;
//    delete ob1;
//    delete ob2;
//    output:
//    void* Object::operator new size:12
//    void* Object::operator new size:16
//    ob1=0x761988
//    ob2=0x7619a0
//    Object::~Object
//    void Object::operator:0x761988
//    Object::~Object
//    void Object::operator:0x7619a0


//    test11
//    try{
//       // throw Exception("test",__FILE__,__LINE__);
//        //使用技巧：
//       // #define THROW_EXCEPTION(e,m) throw e(m,__FILE__,__LINE__);//定义宏在头文件
//        //THROW_EXCEPTION(ArithmeticException,"test");//ArithmeticException替换Exception
//        //THROW_EXCEPTION(NullPointerException,"test");
//        //THROW_EXCEPTION(IndexOutOfBoundsException,"test");
//       // THROW_EXCEPTION(NoEnoughMemoryException,"test");
//        THROW_EXCEPTION(InvalidParameterException,"test");
//        //ArithmeticException
//        //NullPointerException
//        //IndexOutOfBoundsException
//        //NoEnoughMemoryException
//        //InvalidParameterException


//    }
//    catch(const ArithmeticException& e)//子类应该放上面
//    {
//        cout<<"catch(const ArithmeticException& e)"<<endl;
//        cout<<"e.message="<<e.message()<<endl;
//        cout<<"e.location="<<e.location()<<endl;

//    }
//    catch(const NullPointerException& e)//子类应该放上面
//    {
//        cout<<"catch(const NullPointerException& e)"<<endl;
//        cout<<"e.message="<<e.message()<<endl;
//        cout<<"e.location="<<e.location()<<endl;

//    }
//    catch(const IndexOutOfBoundsException& e)//子类应该放上面
//    {
//        cout<<"catch(const IndexOutOfBoundsException& e)"<<endl;
//        cout<<"e.message="<<e.message()<<endl;
//        cout<<"e.location="<<e.location()<<endl;

//    }
//    catch(const NoEnoughMemoryException& e)//子类应该放上面
//    {
//        cout<<"catch(const NoEnoughMemoryException& e)"<<endl;
//        cout<<"e.message="<<e.message()<<endl;
//        cout<<"e.location="<<e.location()<<endl;

//    }
//    catch(const InvalidParameterException& e)//子类应该放上面
//    {
//        cout<<"catch(const InvalidParameterException& e)"<<endl;
//        cout<<"e.message="<<e.message()<<endl;
//        cout<<"e.location="<<e.location()<<endl;

//    }
//    catch(const Exception& e)
//    {
//        cout<<"catch(const Exception& e)"<<endl;
//        cout<<"e.message="<<e.message()<<endl;
//        cout<<"e.location="<<e.location()<<endl;

//    }

//    test10
//    output:
//    catch(const Exception& e)
//    e.message=test
//    e.location=..\DTLib\main.cpp:20
//    SmartPointer<Test> pt=new Test();
//    SmartPointer<Test> ptn;
//    cout <<"operator = test:" << endl;
//    cout <<"pt.isNull():"<< pt.isNull() << endl;
//    cout << "ptn.isNull():"<<ptn.isNull() << endl;

//    cout << "Hello World!" << endl;
//    ptn=pt;
//    cout <<"pt.isNull():"<< pt.isNull() << endl;
//    cout << "ptn.isNull():"<<ptn.isNull() << endl;
//    //++ptn;//E:\qtFile\DTLib\main.cpp:29: error: no match for 'operator++' (operand type is 'DTLib::SmartPointer<Test>')
//      //++ptn;
//     // ^
//    一指针生命周期结束时主动释放
//    堆空间一片堆空间最多只能由一人指针标识
//    社绝指针运算和指针比较





