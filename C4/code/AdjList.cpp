#ifndef AdjList
#define AdjList
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
#include "var.h"

deque <int>q2;
//顶点和边从1开始编号

//无向图
LGraph CreatLGraph()
{
    LGraph G;
    int n,e;
    printf("请输入顶点和边的数量:\n");
    scanf("%d %d",&n,&e);
    G.e=e;G.n=n;
    for(int i=1;i<=n;i++)
    {
        printf("请输入第%d个顶点的数据:",i);
        scanf("%d",&G.verlist[i].data);
        G.verlist[i].firstedge=NULL;
    }    
    int weight,head,tail;
    for(int i=1;i<=e;i++)
    {
        printf("请输入第%d条边的两个顶点:",i);
        // printf("请输入第%d条边的两个顶点和权值:",i);
        // scanf("%d %d %d",&head,&tail,&weight);
        scanf("%d %d",&head,&tail);
        EdgeNode *p=(EdgeNode *)malloc(sizeof(EdgeNode));
        p->adjvex=tail;
        // p->weight=weight;
        p->next=G.verlist[head].firstedge;
        G.verlist[head].firstedge=p;
        EdgeNode *p2=(EdgeNode *)malloc(sizeof(EdgeNode));
        p2->adjvex=head;
        // p2->weight=weight;
        p2->next=G.verlist[tail].firstedge;
        G.verlist[tail].firstedge=p2;
    }
    return G;
}

void GLDFSTraverse(LGraph G,void F(LGraph G,int i))
{
    count=1;
    q2.clear();
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=G.n;i++)
    {
        visited[i]=False;
        Tnodes[i].sonnum=0;
    }
    printf("DFS遍历结果:");
    for(int i=1;i<=G.n;i++)
    {
        if(!visited[i])
            F(G,i);
    }
    printf("\n深度优先编号:");
    for(int i=1;i<=G.n;i++)
    {
        printf("%d  ",dfn[i]);
    }
    if(F==GLDFS)
    {
        printf("\n深度优先森林:\n");
        for(int i=1;i<=G.n;i++)
        {
            if(Tnodes[i].sonnum!=0)
            {
                printf("%d -->",i);   
                for(int j=1;j<=Tnodes[i].sonnum;j++)
                {
                    printf("%d ",Tnodes[i].sons[j]);
                }
                puts("");
            }
        }
    }
    puts("");
}

void GLDFS(LGraph G,int i)
{
    printf("%d  ",G.verlist[i].data);
    visited[i]=True;
    dfn[i]=count++;
    EdgeNode *p=G.verlist[i].firstedge;
    while(p)
    {
        if(!visited[p->adjvex])
        {
            GLDFS(G,p->adjvex);
            Tnodes[i].sons[++Tnodes[i].sonnum]=p->adjvex;
        }
        p=p->next;
    }
}

void GLDFS2(LGraph G,int i)
{
    printf("%d  ",G.verlist[i].data);
    visited[i]=True;
    dfn[i]=count++;
    q2.push_front(i);
    EdgeNode *p=G.verlist[i].firstedge;
    while(!q2.empty())
    {
        if(p&&!visited[p->adjvex])
        {
            printf("%d  ",G.verlist[p->adjvex].data);
            dfn[p->adjvex]=count++;
            visited[p->adjvex]=True;
            q2.push_front(p->adjvex);
            p=G.verlist[p->adjvex].firstedge;
        }
        else if(p&&visited[p->adjvex])
        {
            p=p->next;
        }
        else if(!p)
        {
            q2.pop_front();
            p=G.verlist[q2.front()].firstedge;
        }
    }
}

//可以与DFSTraverse合并成一个函数
void GLBFSTraverse(LGraph G)
{
    q2.clear();
    count=1;
    for(int i=1;i<=G.n;i++)
    {
        visited[i]=False;
        Tnodes[i].sonnum=0;
    }
    printf("BFS遍历结果:");
    for(int i=1;i<=G.n;i++)
    {
        if(!visited[i])
            GLBFS(G,i);
    }
    printf("\n广度优先编号:");
    for(int i=1;i<=G.n;i++)
    {
        printf("%d  ",bfn[i]);
    }
    printf("\n广度优先森林:\n");
    for(int i=1;i<=G.n;i++)
    {
        if(Tnodes[i].sonnum!=0)
        {
            printf("%d -->",i);   
            for(int j=1;j<=Tnodes[i].sonnum;j++)
            {
                printf("%d ",Tnodes[i].sons[j]);
            }
            puts("");
        }
    }
    puts("");
}



void GLBFS(LGraph G,int k)
{
    int i;EdgeNode *p;
    printf("%d  ",G.verlist[k].data);
    visited[k]=True;
    bfn[k]=count++;
    q2.push_back(k);
    while(!q2.empty())
    {
        i=q2.front();
        q2.pop_front();
        p=G.verlist[i].firstedge;
        while(p)
        {
            if(!visited[p->adjvex])
            {
                bfn[p->adjvex]=count++;
                printf("%d  ",G.verlist[p->adjvex].data);
                visited[p->adjvex]=True;
                q2.push_back(p->adjvex);
                Tnodes[i].sons[++Tnodes[i].sonnum]=p->adjvex;
            }
            p=p->next;
        }
    }
}

void GLOutput(LGraph G)
{
    for(int i=1;i<=G.n;i++)
    {
        
        printf("顶点 %d 邻接的顶点：",i);
        EdgeNode *p=G.verlist[i].firstedge;
        while(p)
        {
            printf("%d ",p->adjvex);
            p=p->next;
        }
        puts("");
    }
}

void CountDegree(LGraph G)
{
    EdgeNode *p;
    int degree;
    printf("The vertex || The degree\n");
    for(int i=1;i<=G.n;i++)
    {
        degree=0;
        p=G.verlist[i].firstedge;
        while(p)
        {
            degree++;
            p=p->next;
        }
        printf("    %-4d   ||    %-4d\n",G.verlist[i].data,degree);
    }
}
#endif