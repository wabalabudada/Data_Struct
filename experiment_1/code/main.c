#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g.h"
#include "fun.c"

int main(int argc,char *argv[])
{
    //���������������ڶ�������show�����չʾ��׺���ʽתΪ��׺���ʽ�ͼ����ϸ�ڣ�����ֱ�ӵõ�������
    int flag_show=(argc==2&&strcmp(argv[1],"show")==0)?1:0;
    char mid[MAX_LENGTH];
    InputInto(mid);
    stack lat_stack=IntoSuf(flag_show,mid);
    ValtoCnt(lat_stack);
    double ans=Calc(lat_stack,flag_show);
    printf("Final answer:%lf",ans);
}