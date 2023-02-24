#include "g.h"
#include "fun.c"

int main()
{
    printf("Please input the binary tree by PreOrder like this :ABDH##I##E##CF#J##G##\n");
    Btree T=CreatBT();
    OutputTree(T);
    Output("The result of PreOrder:",PreOrder,T);
    Output("The result of InOrder:",InOrder,T);
    Output("The result of PostOrder:",PostOrder,T);
    Output("The result of LeverOrder:",LeverOrder,T);
    Output("The result of PreOrder_Stack:",PreOrder_Stack,T);
    Output("The result of InOrder_Stack:",InOrder_Stack,T);
    Output("The result of PostOrder_Stack:",PostOrder_Stack,T);
    printf(CompleteBTree(T)==1?"The binary is a complete Tree\n":"The binary is not a complete Tree\n");
    printf("The width of this binary tree is %d\n",MaxWidth(T));
}