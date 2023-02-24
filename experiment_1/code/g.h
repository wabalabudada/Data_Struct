#ifndef DDD
#define DDD
#define MAX_LENGTH  1000    //输入表达式最大长度
#define MAX_ITEM 20         //每条数据或操作最大长度

//栈的存储结构
struct STACK
{
    char item[MAX_ITEM];
    struct STACK * next;
};
typedef struct STACK* stack;

void ShowDetail(stack lat_stack,stack op_stack);
double Calc(stack S,int flag_show);
stack IntoSuf(int flag_show,char *mid);
void InputInto(char mid[]);
void ERR();
int Priority(char op[]);
double NumPop(double num_stack[],int *num_stack_top);
int OpNum(char op[]);
void ValtoCnt(stack lat_stack);

#endif