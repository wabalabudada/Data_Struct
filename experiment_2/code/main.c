#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#define CHARNUM 128

//存放数组下标对应字符的出现频次
int num_of_char[CHARNUM];
//哈夫曼树的结点
typedef struct HTNODE
{
    int weight;
    int lchild;
    int rchild;
    int parent;
}HTnode;
//哈夫曼树
HTnode HuffmanT[2*CHARNUM-1];
//存放每个字符的哈夫曼编码
char bits[CHARNUM][CHARNUM];
//哈夫曼树的根节点
int root;
//堆
int heaps[2*CHARNUM];
//堆的最后一个元素
int heap_num=0;

void CountChar(char *name);
void Encode(char *name1,char*name2);
int MakeHuffmanT();
void Decode(char *name1,char *name2);
void swap(int *a,int *b);
void MinHeapify(int start,int end);
int GetMin();


int main()
{
    char name[40];
    char name2[40];
    char op;
    while(1)
    {
        printf("What do you need to do?\n");
        printf("1. Encode a file.\n");
        printf("2. Decode a file.\n");
        printf("3. Exit.\n");
        fflush(stdin);
        scanf("%c",&op);
        if(op=='1')
        {
            printf("Please input the path of the file:\n");
            scanf("%s",name);
            CountChar(name);
            root=MakeHuffmanT();
            int len=strlen(name);
            strcpy(name2,name);
                name2[len-1]='t';name2[len-2]='a';name2[len-3]='d';
            Encode(name,name2);
            printf("Output the frequency of the letters?(y/n)\n");
            fflush(stdin);
            scanf("%c",&op);
            if(op=='y'||op=='Y')
            {
                double sum=0;
                for(int i=0;i<CHARNUM;i++)
                    sum+=num_of_char[i];
                for(int i=0;i<CHARNUM;i++)
                {
                    if(num_of_char[i]!=0)
                    {
                        if(i!=10)
                            printf("The frequency of '%c' is %f\n",i,num_of_char[i]/sum);
                        else    
                            printf("The frequency of '\\n' is %f\n",num_of_char[i]/sum);
                    }
                }
            }
            printf("Output the Huffman encode table?(y/n)\n");
            fflush(stdin);
            scanf("%c",&op);
            if(op=='y'||op=='Y')
            {
                for(int i=0;i<CHARNUM;i++)
                {
                    if(HuffmanT[i].weight!=0)
                    {
                        if(i!=10)
                            printf("The code number of '%c': ",i);
                        else
                            printf("The code number of '\\n': ");
                        puts(bits[i]);
                    }
                }
            }
        }
        else if(op=='2')
        {
            printf("Please input the path of the file:\n");
            scanf("%s",name);
            strcpy(name2,name);
            int len=strlen(name2);
            name2[len-3]='\0';
            strcat(name2,"(decoded).txt");
            Decode(name,name2);
            printf("%s has been decoded as %s\n",name,name2);
        }
        else if(op=='3')
        {
            break;
        }
        printf("continue?(y/n)\n");
        fflush(stdin);
        scanf("%c",&op);
        if(op=='Y'||op=='y')
            system("cls");
        else    break;;
    }
    return 0;
}

//统计字符出现频次
void CountChar(char *name)
{
    FILE *fp=fopen(name,"r");
    if(fp==NULL) 
    {
        printf("Can't open file.\n");
        exit(1);
    }  
    char c=fgetc(fp);
    while(c!=-1)
    {
        num_of_char[c]++;
        c=fgetc(fp);
    }
    fclose(fp);
}

//最小堆调用，用于获取堆顶元素
int GetMin()
{
    int min=heaps[1];
    swap(&heaps[1],&heaps[heap_num]);
    heap_num--;
    MinHeapify(1,heap_num);
    return min;
}

//交换两数，传地址
void swap(int *a,int *b)
{
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}

//调整堆从start到end的部分
void MinHeapify(int start,int end)
{
    int dad=start;
    int son=dad*2;
    while(son<=end)
    {
        if(son+1<=end&&HuffmanT[heaps[son+1]].weight<HuffmanT[heaps[son]].weight) son++;
        if(HuffmanT[heaps[son]].weight<HuffmanT[heaps[dad]].weight)
        {
            swap(&heaps[son],&heaps[dad]);
            dad=son;
            son=dad*2;
        }
        else    return;
    }
}

//解码
void Decode(char *name1,char *name2)
{
    FILE *fp=fopen(name1,"rb");
    if(fp==NULL)
    {
        printf("Can't find the file.\n");
        exit(1);
    }
    FILE *fpt=fopen(name2,"w+");
    fseek(fp,0,SEEK_END);
    long long size = ftell(fp);
    //多出的4个字节指明了冗余了几个比特，lessbit是冗余比特数
    fseek(fp,-4,SEEK_END);
    long lessbit;
    fread(&lessbit,1,4,fp);
    fseek(fp,0,0);
    unsigned cc;
    int tmp32bit[32];
    int now=0;
    int tmpnode=root;
    fread(&cc,1,4,fp);
    for(int i=31;i>=0;i--)
    {
        tmp32bit[i]=cc%2;
        cc=cc>>1;
    }
    for(long long i=0;i<size*8-32-11;i++)
    {
        if(tmp32bit[now]==0)
        {
            tmpnode=HuffmanT[tmpnode].lchild;
        }
        else if(tmp32bit[now]==1)
        {
            tmpnode=HuffmanT[tmpnode].rchild;
        }
        if(HuffmanT[tmpnode].lchild==-1)
        {
            fputc(tmpnode,fpt);
            tmpnode=root;
        }
        now++;
        if(now==32)
        {
            now=0;
            fread(&cc,1,4,fp);
            for(int j=31;j>=0;j--)
            {
                tmp32bit[j]=cc%2;
                cc=cc>>1;
            }
        }
    }
    fclose(fp);
    fclose(fpt);
}

//构造哈夫曼树
int MakeHuffmanT()
{
    int node_num=0;
    //初始化结点
    for(int i=0;i<2*CHARNUM-1;i++)
    {
        if(i<CHARNUM)
        {
            HuffmanT[i].weight=num_of_char[i];
            if(HuffmanT[i].weight!=0)   
                node_num++;
        }
        HuffmanT[i].lchild=-1;
        HuffmanT[i].rchild=-1;
        HuffmanT[i].parent=-1;
    }

    //构造哈夫曼树
    int min1,min2;   
    for(int i=0;i<CHARNUM;i++)
    {
        if(HuffmanT[i].weight!=0)
            heaps[++heap_num]=i;
    }
    for(int i=heap_num/2;i>=1;i--)
    {
        MinHeapify(i,heap_num);
    }
    for(int t=CHARNUM;t<=CHARNUM+node_num-2;t++)
    {
        min1=GetMin();
        min2=GetMin();
        HuffmanT[min1].parent=t;
        HuffmanT[min2].parent=t;
        HuffmanT[t].lchild=min1;
        HuffmanT[t].rchild=min2;
        HuffmanT[t].weight=HuffmanT[min1].weight+HuffmanT[min2].weight;
        int son=++heap_num;
        heaps[heap_num]=t;
        int dad=son/2;
        while(dad>=1)
        {
            if(HuffmanT[heaps[son]].weight<HuffmanT[heaps[dad]].weight)
            {
                swap(&heaps[son],&heaps[dad]);
                son=dad;
                dad=son/2;
            }
            else    break;
        }
    }
    int root=heaps[1];

    //得到每个结点对应字符的哈夫曼编码
    for(int i=0;i<CHARNUM;i++)
    {

        if(HuffmanT[i].weight!=0)
        {
            char tmp[CHARNUM];
            int p=CHARNUM-1;
            int par=HuffmanT[i].parent,son=i;
            tmp[p]='\0';
            while(par!=-1)
            {
                p--;
                if(son==HuffmanT[par].lchild)
                tmp[p]='0';
                else tmp[p]='1';
                son=par;
                par=HuffmanT[son].parent;
            }
            strcpy(bits[i],&tmp[p]);
        }
    }
    return root;
}

//用哈夫曼编码表堆文本进行编码
void Encode(char *name1,char*name2)
{
    FILE *fp=fopen(name1,"r");
    FILE *fpb=fopen(name2,"wb+");
    char c=fgetc(fp);
    int pbits=0,ptmp=0;
    unsigned tmp=0;
    while(c!=-1)
    {
        while(bits[c][pbits]!='\0')
        {
            if(ptmp!=0)     
            {
                tmp=tmp<<1;
            }
            if(bits[c][pbits]=='1')      
            {
                tmp++;
            }
            pbits++;
            ptmp++;
            if(ptmp==32)
            {
                fwrite(&tmp,1,4,fpb);
                ptmp=0;
                tmp=0;
            }
        }
        pbits=0;
        c=fgetc(fp);
    }

    //lessbit是冗余比特数，这个数字被编码进文件的末尾
    unsigned lessbit;
    if(ptmp!=32)
    {       
        lessbit=32-ptmp;
        tmp=tmp<<lessbit;
        fwrite(&tmp,1,4,fpb);
        tmp=lessbit;
        fwrite(&tmp,1,4,fpb);
    }    

    //求压缩率
    double size1,size2;
    fseek(fp,0,SEEK_END);
    size1=ftell(fp);
    fseek(fpb,0,SEEK_END);
    size2=ftell(fpb);
    printf("%s has been encoded as %s\n",name1,name2);
    printf("The size before compression is %lfkb\nThe size after compression is %lfkb\nThe compression ratio is %.2llf\n",
            size1/1024,size2/1024,size2/size1);
    fclose(fp);
    fclose(fpb);
}
