#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int swap(int *a,int *b);
int Bubble_Sort(int a[],int n);
int Select_Sort(int a[],int n);
int Insert_Sort(int a[],int n);
void mprintf(int a[],int n,char s[]);

int Bubble_Sort(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(a[j]>a[j+1]) swap(&a[j],&a[j+1]);
        }
    }
}

int Select_Sort(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int min_index=i;
        for(int j=i;j<n;j++)
        {
            if(a[j]<a[min_index])
                min_index=j;
        }
        if(min_index!=i)    swap(&a[i],&a[min_index]);
    }
}

int Insert_Sort(int a[],int n)
{
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(a[j]>a[i])
            {
                int tmp=a[i];
                for(int k=i;k>=j+1;k--)
                    a[k]=a[k-1];
                a[j]=tmp;
            }
        }
    }
}

//用于交换两个值的通用函数
int swap(int *a,int *b)
{
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

//用于打印数组
void mprintf(int a[],int n,char s[])
{
    printf("%s: ",s);
    for(int i=0;i<n;i++)    printf("%d  ",a[i]);
    printf("\n");
}

int main()
{
    clock_t start_time, end_time; 
    //数据大小
    int num=100;
    int *exap=(int*) malloc(sizeof(int)*(num));
    for(int i=0; i<num; i++)
    {
        exap[i]=rand()%(10*num);
    }
    // // 用于测试时间的代码段
    // start_time=clock();
    // for(int i=0;i<99;i++)
    // {
    //     Bubble_Sort(exap,num);
    //     // Select_Sort(exap,num);
    //     // Insert_Sort(exap,num);
    // }
    // end_time=clock();
    // printf("The sort time is %lfs. ", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    // 用于进行一次排序并输出结果的代码段
    mprintf(exap,num,"Before Sort");
    for(int i=0;i<10;i++)
    {
        Bubble_Sort(exap,num);
        // Select_Sort(exap,num);
        // Insert_Sort(exap,num);
    }
    mprintf(exap,num,"After Sort");
}