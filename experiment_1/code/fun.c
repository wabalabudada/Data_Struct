#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "g.h"
#include "stack.c"

//输入错误时直接跳转到该函数终止程序
void ERR()
{
    printf("Wrong input!\n");
    exit(1);
}

//展示中缀表达式转换为后缀表达式时的细节
void ShowDetail(stack lat_stack,stack op_stack)
{
    static int i=1;
    printf("step%d:\n",i);
    puts("lat_stack:");
    output(lat_stack);
    puts("op_stack");
    output(op_stack);
    puts("");
    i++;
}

//计算后缀表达式的值
double Calc(stack S,int flag_show)
{
    if(flag_show==1) printf("计算时栈的状态变化过程如下:\n");
    double num_stack[MAX_LENGTH];
    int num_stack_top=-1;
    while(!Empty(S))
    {
        char tmpstr[MAX_ITEM]="";
        strcpy(tmpstr,top(S));
        pop(S);
        if(flag_show==1)
        {
            static int i=1;
            printf("step%d:\n",i);
            puts("lat_stack:");
            output(S);
            i++;
        }
        if(strcmp(tmpstr,"0")!=0&&atof(tmpstr)==0)
        {
            double num1,num2;
            num1=NumPop(num_stack,&num_stack_top);
            if(OpNum(tmpstr)==2)
            num2=NumPop(num_stack,&num_stack_top);
            char op=tmpstr[0];
            switch (op)
            {
            case '+':
                num_stack[++num_stack_top]=num2+num1;
                break;
            case '-':
                num_stack[++num_stack_top]=num2-num1;
                break;
            case '*':
                num_stack[++num_stack_top]=num2*num1;
                break;
            case '/':
                num_stack[++num_stack_top]=num2/num1;
                break;
            case '!':
                if((num1-(int)num1)!=0) ERR();
                double ans=1;
                for(int j=1;j<=(int)num1;j++)   ans*=j;
                num_stack[++num_stack_top]=ans;
                break;
            case '^':
                num_stack[++num_stack_top]=pow(num2,num1);
                break;
            default:
                break;
            }
        }
        else
        {
            num_stack[++num_stack_top]=atof(tmpstr);
        }
        if(flag_show==1)
        {
            puts("numbers in stack:");
            for(int j=0;j<=num_stack_top;j++)   printf("%lf  ",num_stack[j]);
            puts("");
            puts("");
        }
    }
    return num_stack[0];
}

//从文本文件读入表达式
void InputInto(char mid[])
{
    printf("请输入要从中读入表达式的文本文件:");
    scanf("%s",mid);
    FILE* fp=fopen(mid,"r");
    fscanf(fp,"%s",mid);
    fclose(fp);
} 

//将中缀表达式转换为后缀表达式
stack IntoSuf(int flag_show,char *mid)
{
    stack lat_stack=MakeNull();
    stack op_stack=MakeNull();
    char lat[MAX_LENGTH];
    int flag_num=0,flag_op=1,fir;
    char tmp[MAX_ITEM];
    int num_count=0,l=0;
    for(int i=0;i<=strlen(mid);i++)
    {
        if(mid[i]=='#') {fir=i+1;continue;}
        else if(mid[i]>='0'&&mid[i]<='9'||mid[i]=='.'||(mid[i]=='-'&&flag_op==1))
        {
            tmp[l++]=mid[i];
            flag_num=1;
            flag_op=0;
        }
        else if(mid[i]>='a'&&mid[i]<='z'||mid[i]>='A'&&mid[i]<='Z')
        {
            flag_op=0;
            char tmpbl[5];
            tmpbl[0]=mid[i];tmpbl[1]='\0';
            push(lat_stack,tmpbl);
        }
        else
        {
            if(flag_num==1)
            { 
                tmp[l]='\0';
                push(lat_stack,tmp);
                l=0;flag_num=0;
            }
            if(mid[i]=='\n'||mid[i]=='\0')  continue;
            if(mid[i]=='(')
            {
                push(op_stack,"(");
            }
            else if(mid[i]==')')
            {
                char tmpstr[5];
                strcpy(tmpstr,top(op_stack));
                pop(op_stack);
                while(strcmp(tmpstr,"(")!=0)
                {
                    push(lat_stack,tmpstr);
                    strcpy(tmpstr,top(op_stack));
                    pop(op_stack);
                }
            }
            else
            {
                char tmpstr[5],str[5];
                str[0]=mid[i];str[1]='\0';
                int now_priority=Priority(str);
                if(!Empty(op_stack))
                {
                    strcpy(tmpstr,top(op_stack));
                    while(Priority(tmpstr)>=now_priority)
                    {
                        push(lat_stack,tmpstr);
                        pop(op_stack);
                        if(!Empty(op_stack))
                        {
                            strcpy(tmpstr,top(op_stack));
                        }
                        else    break;
                    }
                }
                push(op_stack,str);
            }
            if(mid[i]!=')')    flag_op=1;
            if(flag_show==1)
                ShowDetail(lat_stack,op_stack);
        }
    }
    while(!Empty(op_stack))
    {
        push(lat_stack,top(op_stack));
        pop(op_stack);
    }
    Reversal(lat_stack);
    puts("后缀表达式:");
    output(lat_stack);
    return lat_stack;
}

//返回算术符优先级
int Priority(char op[])
{
    char s=op[0];
    if(s=='+'||s=='-')  return 1;
    else if(s=='*'||s=='/') return 2;
    else if(s=='^')     return 3;
    else if(s=='!')     return 4;
    else if(s=='(')     return -1;
    else ERR();
}

//操作符是几元运算符就返回几
int OpNum(char op[])
{
    char s=op[0];
    if(s=='+'||s=='-'||s=='*'||s=='/'||s=='^')  return 2;
    else if(s=='!')                     return 1;
    else ERR();
}

//数字栈出栈返回栈顶元素
double NumPop(double num_stack[],int *num_stack_top)
{   
    double tmp=num_stack[(*num_stack_top)--];
    if(*num_stack_top<-1)   ERR();
    return tmp;
}

//变量带入
void ValtoCnt(stack S)
{
    if(!Empty(S))
    {
        stack tmps=S;
        char tmpstr[MAX_ITEM];
        while(tmps->next!=NULL)
        {
            if(tmps->next->item[0]>='a'&&tmps->next->item[0]<='z'
                ||tmps->next->item[0]>='A'&&tmps->next->item[0]<='Z')
            {
                printf("%s= ",tmps->next->item);
                scanf("%s",tmpstr);
                puts("");
                strcpy(tmps->next->item,tmpstr);
            }
            tmps=tmps->next;
        }
    }
}