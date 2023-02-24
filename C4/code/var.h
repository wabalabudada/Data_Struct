#ifndef BBB
#define BBB
#define Max 100
#define True 1
#define False 0
int count;
int dfn[Max],bfn[Max];
int visited[Max];
using namespace std;
//邻接表结点
typedef struct node
{
    int adjvex;  //邻接点（下标）
    // int weight; //边上的权值
    struct node *next;  //下一边的指针
}EdgeNode;

//顶点表结点
typedef struct noname1
{
    int data;
    EdgeNode *firstedge;
}VertexNode;

//图的定义
typedef struct noname2
{
    VertexNode verlist[Max];
    int n,e;
}LGraph;

typedef struct struct1
{
    int n,e;   //顶点和边数
    int verlist[Max];
    int edge[Max][Max];
}MGraph;

typedef struct noname
{
    int sons[20];
    int sonnum;
}Tnode;
Tnode Tnodes[Max];

MGraph CreatMGraph();
void GMOutput(MGraph G);
void GMDFSTraverse(MGraph G,void F(MGraph G,int i));
void GMDFS(MGraph G ,int i);
void GMDFS2(MGraph G,int i);
void GMBFSTraverse(MGraph G);
void GMBFS(MGraph G,int k);
void GLOutput(LGraph G);
void GLDFS(LGraph G,int i);
void GLDFS2(LGraph G,int i);
void GLDFSTraverse(LGraph G,void F(LGraph G,int i));
LGraph CreatLGraph();
void GLBFSTraverse(LGraph G);
void GLBFS(LGraph G,int k);
void CountDegree(LGraph G);

#endif