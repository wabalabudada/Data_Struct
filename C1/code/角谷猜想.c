#include <stdio.h>
int times[110];

void JiaoGu(int i,int t)
{
    times[t]++;
    if(i==1)
    {  
        printf("%d",i);
        return;
    }
    printf("%d-->",i);
    if(i%2==0)
    {
        i/=2;
    }
    else if(i%2==1)
    {
        i*=3;
        i+=1;
    }
    JiaoGu(i,t);
}

int main()
{
    for(int i=1;i<=100;i++)
    {
        JiaoGu(i,i);
        printf("\n");
    }
    int max_index=1;
    for(int i=2;i<=100;i++)
    {
        if(times[i]>times[max_index])   max_index=i;
    }
    printf("%d",max_index);
    return 0;
}