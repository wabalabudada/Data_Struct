//借由柱子b将n块板砖从a移动到c

#include <stdio.h>
int count=0;
//将a上的k块砖通过b移到c
void Move(int k,char a ,char b,char c)
{
    if(k==0)    return;
    Move(k-1,a,c,b);
    printf("step%d: move %d from %c to %c\n",++count,k,a,c);
    Move(k-1,b,a,c);
}
int main()
{
    int n=3;
    Move(n,'a','b','c');    
}