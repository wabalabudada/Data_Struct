#ifndef AdjMar
#define AdjMar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
#include "var.h"

deque <int>q1;
//顶点和边从0开始编号

MGraph CreatMGraph()
{
    MGraph G;
    int n,e;
    printf("请输入顶点和边的数量:");
    scanf("%d %d",&n,&e);
    G.e=e;G.n=n;
    for(int i=0;i<n;i++)
    {
        printf("请输入第%d个顶点的数据:",i);
        scanf("%d",&G.verlist[i]);
    }
    int tmp1,tmp2;
    for(int i=0;i<e;i++)
    {
        printf("请输入第%d条边的两个顶点:",i);
        scanf("%d %d",&tmp1,&tmp2);
        G.edge[tmp1][tmp2]=1;
        G.edge[tmp2][tmp1]=1;
    }
    return G;
}

//遍历输出
void GMOutput(MGraph G)
{
    puts("顶点的数据:");
    for(int i=0;i<G.n;i++)
        printf("%d  ",G.verlist[i]);
    puts("\n邻接表:");
    for(int i=0;i<G.n;i++)
    {
        for(int j=0;j<G.n;j++)
        {
            printf("%d  ",G.edge[i][j]);
        }
        puts("");
    }
}


void GMDFSTraverse(MGraph G,void F(MGraph G,int i))
{
    count=1;
    q1.clear();
    memset(dfn,0,sizeof(dfn));
    for(int i=0;i<G.n;i++)
    {
        visited[i]=False;
        Tnodes[i].sonnum=0;
    }
    printf("DFS遍历结果:");
    for(int i=0;i<G.n;i++)
    if(!visited[i])
        F(G,i);
    printf("\n深度优先编号:");
    for(int i=0;i<G.n;i++)
    {
        printf("%d  ",dfn[i]);
    }
    if(F==GMDFS)
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

void GMDFS(MGraph G,int i)
{
    visited[i]=True;
    printf("%d  ",G.verlist[i]);
    dfn[i]=count++;
    for(int j=0;j<G.n;j++)
    {
        if(G.edge[i][j]&&!visited[j])
        {
            GMDFS(G,j);
            Tnodes[i].sons[++Tnodes[i].sonnum]=j;
        }
    }
}

void GMDFS2(MGraph G,int i)
{
    visited[i]=True;
    printf("%d  ",G.verlist[i]);
    dfn[i]=count++;
    q1.push_front(i);
    int p=0;
    while(!q1.empty())
    {
        if(!G.edge[i][p]||visited[p])
        {
            p++;
        }
        else
        {
            printf("%d  ",G.verlist[p]);
            dfn[p]=count++;
            visited[p]=True;
            q1.push_front(p);
            i=p;
            p=0;
        }
        if(p==G.n)
        {
            q1.pop_front();
            i=q1.front();
            p=0;
        }
    }
}

void GMBFSTraverse(MGraph G)
{
    count=1;
    q1.clear();
    for(int i=0;i<G.n;i++)
    {
        visited[i]=False;
        Tnodes[i].sonnum=0;
    }
    printf("BFS遍历结果:");
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
            GMBFS(G,i);
    }
    printf("\n广度优先编号:");
    for(int i=0;i<G.n;i++)
    {
        printf("%d  ",bfn[i]);
    }
    printf("\n广度优先森林:\n");
    for(int i=0;i<G.n;i++)
    {
        if(Tnodes[i].sonnum!=0)
        {
            printf("%d -->",i+1);   
            for(int j=1;j<=Tnodes[i].sonnum;j++)
            {
                printf("%d ",Tnodes[i].sons[j]+1);
            }
            puts("");
        }
    }
    puts("");
}

void GMBFS(MGraph G,int k)
{
    int t;
    printf("%d  ",G.verlist[k]);
    visited[k]=True;
    bfn[k]=count++;
    q1.push_back(k);
    while(!q1.empty())
    {
        t=q1.front();
        q1.pop_front();
        for(int i=0;i<G.n;i++)
        {
            if(G.edge[t][i]&&!visited[i])
            {
                q1.push_back(i);
                printf("%d  ",G.verlist[i]);
                visited[i]=True;
                bfn[i]=count++;
                Tnodes[t].sons[++Tnodes[t].sonnum]=i;
            }
        }
    }
}

#endif

