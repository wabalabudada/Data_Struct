#include <stdio.h>
#include <stdlib.h>
#include "AdjList.cpp"
#include "AdjMar.cpp"
#include "var.h"
#include "Switch.cpp"

int main()
{
    printf("请输入一个邻接表表示的图：\n");
    LGraph GL=CreatLGraph();       //邻接表
    printf("请输入一个邻接矩阵表示的图：\n");
    MGraph GM=CreatMGraph();      //邻接矩阵
    LGraph NewGL=GMtoGL(GM);
    MGraph NewGM=GLtoGM(GL);
    printf("GL:\n");
    GLOutput(GL);
    printf("将邻接表的图GL转化为邻接矩阵的图NewGL\n");
    GLOutput(NewGL);
    printf("GM:\n");
    GMOutput(GM);
    printf("将邻接矩阵的图GM转化为邻接表的图NewGM:\n");
    GMOutput(NewGM);
    puts("The BFS of GM");
    GMBFSTraverse(GM);
    puts("The DFS of GM");
    GMDFSTraverse(GM,GMDFS);
    puts("The DFS of GM(not recursion)");
    GMDFSTraverse(GM,GMDFS2);
    puts("The BFS of GL");
    GLBFSTraverse(GL);
    puts("The DFS of GL");
    GLDFSTraverse(GL,GLDFS);
    puts("The DFS of GL(not recursion)");
    GLDFSTraverse(GL,GLDFS2);
    puts("The degree of every vertex in GL");
    CountDegree(GL);
    return 0;
}