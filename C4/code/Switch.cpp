#include <stdio.h>
#include <stdlib.h>
#include "AdjList.cpp"
#include "AdjMar.cpp"
#include "var.h"

MGraph GLtoGM(LGraph GL)
{
    MGraph GM;
    GM.e=GL.e;
    GM.n=GL.n;
    for(int i=0;i<GM.n;i++)
    {
        GM.verlist[i]=GL.verlist[i+1].data;
    }
    for(int i=1;i<=GL.n;i++)
    {
        EdgeNode *p=GL.verlist[i].firstedge;
        while(p)
        {
            GM.edge[i-1][p->adjvex-1]=1;
            p=p->next;
        }
    }
    return GM;
}

LGraph GMtoGL(MGraph GM)
{
    LGraph GL;
    GL.e=GM.e;
    GL.n=GM.n;
    for(int i=1;i<=GL.n;i++)
    {
        GL.verlist[i].data=GM.verlist[i-1];
        GL.verlist[i].firstedge=NULL;
    }
    int weight,head,tail;
    for(int i=0;i<GM.n;i++)
    {
        for(int j=0;j<GM.n;j++)
        {
            if(GM.edge[i][j]==1)
            {
                EdgeNode *p=(EdgeNode *)malloc(sizeof(EdgeNode));
                head=i+1;tail=j+1;
                p->adjvex=tail;
                // p->weight=weight;
                p->next=GL.verlist[head].firstedge;
                GL.verlist[head].firstedge=p;
            }
        }
    }
    return GL;
}
