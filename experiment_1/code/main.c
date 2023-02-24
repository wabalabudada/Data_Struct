#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g.h"
#include "fun.c"

int main(int argc,char *argv[])
{
    //如果从命令行输入第二个参数show，则会展示中缀表达式转为后缀表达式和计算的细节，否则直接得到计算结果
    int flag_show=(argc==2&&strcmp(argv[1],"show")==0)?1:0;
    char mid[MAX_LENGTH];
    InputInto(mid);
    stack lat_stack=IntoSuf(flag_show,mid);
    ValtoCnt(lat_stack);
    double ans=Calc(lat_stack,flag_show);
    printf("Final answer:%lf",ans);
}