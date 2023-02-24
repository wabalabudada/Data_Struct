#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#define Max 100
#define True 1
#define False 0
#define Infinity 0x00ff00


typedef struct struct1
{
    int n,e;   //顶点和边数
    int verlist[Max];
    int edge[Max][Max];
}Graph;

int dist[Max];
//bridge[i]存储的是从s到i需要经过的顶点
int bridge[Max];

//S为1说明该顶点已经确定最短路，为0说明没确定
int S[Max];

//Floyd算法给出的最短距离
int A[Max][Max];

//Floya算法给出的最短路径
int P[Max][Max];

//可达矩阵
bool Reach[Max][Max];

//用于堆优化的堆
int heap[Max];
int heap_tail;

FILE *infile;

void OutputMar(Graph G);
Graph CreatGraph();
void Dijkstra(Graph G,int s);
void Dijkstra_opt(Graph G,int s);
void FindPath(int des);
void FindPath2(int des);
void OutputPath(Graph G,int from,int des);
void OutputPath2(Graph G,int s,int i);
void T(Graph *G);
void OutputPathFloyd(Graph G,int from,int des);
void FindPathFloyd(int from,int des);
void Floyd(Graph G);

//用于堆结构优化
void UpTiaoZheng(int tail);
void DownTiaoZheng(int begin);
void HeapInsert(int i);
int HeapPop();

void UpTiaoZheng(int tail)
{
    int tmp_idx=tail,tmp_val=heap[tail];
    while(tmp_idx!=1&&tmp_val<dist[heap[tmp_idx/2]])
    {
        heap[tmp_idx]=heap[tmp_idx/2];
        tmp_idx/=2;
    }
    heap[tmp_idx]=tmp_val;
}

void DownTiaoZheng(int begin)
{
    int parent=begin,child=2*begin,tmp_val=heap[begin];
    while(child<=heap_tail)
    {
        if(child<heap_tail&&(dist[heap[child+1]]<dist[heap[child]]))
            child++;
        if(tmp_val<heap[child]) break;
        heap[parent]=heap[child];
        parent=child;
        child*=2;
    }
    heap[parent]=tmp_val;
}

void HeapInsert(int i)
{
    heap[++heap_tail]=i;
    UpTiaoZheng(heap_tail);
}

int HeapPop()
{
    int item=heap[1];
    heap[1]=heap[heap_tail--];
    DownTiaoZheng(1);
    return item;
}

void FindPath(int des)
{
    int k=bridge[des];
    if(k!=0)
    {
        FindPath(k);
        printf("%d-->",k);
    }
}

void FindPath2(int des)
{
    int k=bridge[des];
    if(k!=0)
    {
        printf("%d-->",k);
        FindPath(k);
    }
}

void Dijkstra(Graph G,int s)
{
    int i,j;
    for(i=1;i<=G.n;i++)
    {
        dist[i]=G.edge[s][i];
        bridge[i]=0;
        S[i]=0;
    }
    S[s]=1;
    for(j=1;j<G.n;j++)
    {
        int min=Infinity,min_idx;
        for(i=1;i<=G.n;i++)
        {   
            if(dist[i]<=min&&S[i]==0)
            {
                min=dist[i];min_idx=i;
            }
        }
        S[min_idx]=1;
        for(i=1;i<=G.n;i++)
        {
            if(S[i]==0&&(dist[min_idx]+G.edge[min_idx][i]<dist[i]))
            {
                dist[i]=dist[min_idx]+G.edge[min_idx][i];
                bridge[i]=min_idx;
            }            
        }
    }
}

//optimized by heap.
void Dijkstra_opt(Graph G,int s)
{
    int i,j,min_idx;
    for(i=1;i<=G.n;i++)
    {
        dist[i]=G.edge[s][i];
        bridge[i]=0;
    }
    heap_tail=0;
    for(i=1;i<=G.n;i++)
    {
        if(i!=s)
        HeapInsert(i);
    }
    for(j=1;j<G.n;j++)
    {
        min_idx=HeapPop();
        for(i=1;i<=heap_tail;i++)
        {
            if(dist[min_idx]+G.edge[min_idx][heap[i]]<dist[heap[i]])
            {
                dist[heap[i]]=dist[min_idx]+G.edge[min_idx][heap[i]];
                bridge[heap[i]]=min_idx;
                DownTiaoZheng(i);
                UpTiaoZheng(i);
            }
        }
    }
}

void Floyd(Graph G)
{
    int i,j,k;
    for(i=1;i<=G.n;i++)
    {
        for(j=1;j<=G.n;j++)
        {
            A[i][j]=G.edge[i][j];
            P[i][j]=0;
        }
    }
    for(k=1;k<=G.n;k++)
    {
        for(i=1;i<=G.n;i++)
        {
            for(j=1;j<=G.n;j++)
            {
                if(A[i][k]+A[k][j]<A[i][j])
                {
                    P[i][j]=k;
                    A[i][j]=A[i][k]+A[k][j];
                }
            }
        }
    }
}

Graph CreatGraph()
{
    Graph G;
    int n,e;
    if(infile==stdin)
        printf("请输入顶点和边的数量:");
    fscanf(infile,"%d %d",&n,&e);
    G.e=e;G.n=n;
    for(int i=1;i<=n;i++)
    {
        if(infile==stdin)
            printf("请输入第%d个顶点的数据:",i);
        fscanf(infile,"%d",&G.verlist[i]);
    }
    for(int i=1;i<=G.n;i++)
    {
        for(int j=0;j<=G.n;j++)
            G.edge[i][j]=Infinity;
    }
    for(int i=1;i<=G.n;i++)
    {
        G.edge[i][i]=0;
    }
    int tmp1,tmp2,weight;
    for(int i=1;i<=e;i++)
    {
        if(infile==stdin)
            printf("请输入第%d条边的起点、终点、权值:",i);
        fscanf(infile,"%d %d %d",&tmp1,&tmp2,&weight);
        G.edge[tmp1][tmp2]=weight;
    }
    return G;
}

//遍历输出
void OutputMar(Graph G)
{
    puts("顶点的数据:");
    for(int i=1;i<=G.n;i++)
        printf("%d  ",G.verlist[i]);
    puts("\n邻接表:");
    for(int i=1;i<=G.n;i++)
    {
        for(int j=1;j<=G.n;j++)
        {
            if (G.edge[i][j]==Infinity)     printf("-1   ");
            else        printf("%-5d",G.edge[i][j]);
        }
        puts("");
    }
}

void OutputPath(Graph G,int from,int des)
{
    printf("%d to %d:",from,des);
    if(bridge[des]==0&&G.edge[from][des]==Infinity)
    {
        printf("No Path!\n");
    }
    else{
        printf("%d-->",from);
        FindPath(des);
        printf("%d",des);
        printf(" , distance:%d\n",dist[des]);
    }

}

void OutputPath2(Graph G,int des,int from)
{
    printf("%d to %d:",from,des);
    if(bridge[from]==0&&G.edge[des][from]==Infinity)
    {
        printf("No Path!\n");

    }
    else{
        printf("%d-->",from);
        FindPath2(from);
        printf("%d",des);
        printf(" , distance:%d\n",dist[from]);
    }
}

void FindPathFloyd(int from,int des)
{
    int k=P[from][des];
    if(k!=0)
    {
        FindPathFloyd(from,k);
        printf("%d-->",k);
        FindPathFloyd(k,des);
    }
    return;
}

void OutputPathFloyd(Graph G,int from,int des)
{
    printf("%d to %d:",from,des);
    if(P[from][des]==0&&G.edge[from][des]==Infinity)
    {
        printf("No Path!\n");

    }
    else{
        printf("%d-->",from);
        FindPathFloyd(from,des);
        printf("%d",des);
        printf(" , distance:%d\n",A[from][des]);
    }
}

void T(Graph *G)
{
    int i,j,tmp;
    for(i=1;i<=G->n;i++)
    {
        for(j=i+1;j<=G->n;j++)
        {
            tmp=G->edge[i][j];
            G->edge[i][j]=G->edge[j][i];
            G->edge[j][i]=tmp;
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc == 1) {  
	    infile = stdin;
    } 
    else if (argc == 2) {
	if (!(infile = fopen(argv[1], "r"))) {
	    printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	    exit(1);
	    }
    }

    Graph G=CreatGraph();

    printf("\nQuestion1\n");
    int from=1;
    Dijkstra(G,from);
    // Dijkstra_opt(G,from);
    for(int i=1;i<=G.n;i++)
    {
        OutputPath(G,from,i);
    }
    puts("\nQuestion2");
    Floyd(G);
    for(int i=1;i<=G.n;i++)
    {
        for(int j=1;j<=G.n;j++)
        {
            OutputPathFloyd(G,i,j);
        }
    }
    puts("\nQuestion3");
    T(&G);
    int des=1;
    Dijkstra(G,des);
    for(int i=1;i<=G.n;i++)
    {
        OutputPath2(G,des,i);
    }
    puts("\nQuestion4");
    from=1,des=2;
    for(int i=1;i<=2;i++)
    {
        T(&G);
        Dijkstra(G,from);
        OutputPath(G,from,des);
    }
    puts("\nQuestion5");
    OutputMar(G);
    puts("\nQuestion6");
    for(int i=1;i<=G.n;i++)
    {
        for(int j=1;j<=G.n;j++)
        {
            if(A[i][j]!=Infinity)
                Reach[i][j]=1;
            else Reach[i][j]=0;
        }
    }
    for(int i=1;i<=G.n;i++)
    {
        for(int j=1;j<=G.n;j++)
        {
            printf("%d  ",Reach[i][j]);
        }
        puts("");
    }
    puts("\nQuestion7");

    //make test file
    FILE *testfile=fopen("testfile.txt","w+");
    int tn=20,te=80;
    fprintf(testfile,"%d %d\n",tn,te);
    for(int i=1;i<=tn;i++)
        fprintf(testfile,"%d ",i);
    fprintf(testfile,"\n");
    for(int i=1;i<=te;i++)
    {
        fprintf(testfile,"%d %d %d\n",(rand()%tn)+1,(rand()%tn)+1,rand());
    }
    fclose(testfile);
    FILE *tfp=fopen("testfile.txt","r");
    infile=tfp;
    Graph TG=CreatGraph();
    auto origin_begin = std::chrono::high_resolution_clock::now();
    for(int i=1;i<=100;i++)     Dijkstra(G,1);
    auto origin_end = std::chrono::high_resolution_clock::now();
    auto origin_time = std::chrono::duration_cast<std::chrono::nanoseconds>(origin_end - origin_begin);
    printf("原算法时间(执行100次):%.4f\n",origin_time.count()*1e-6);

    auto opt_begin = std::chrono::high_resolution_clock::now();
    for(int i=1;i<=100;i++)     Dijkstra_opt(G,1);
    auto opt_end = std::chrono::high_resolution_clock::now();
    auto opt_time = std::chrono::duration_cast<std::chrono::nanoseconds>(opt_end - opt_begin);
    printf("堆结构优化后算法时间(执行100次);%.4f\n",opt_time.count()*1e-6);
    return 0;
}