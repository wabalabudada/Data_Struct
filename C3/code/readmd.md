1. Please use UTF-8 to show the Chinese properly.


test1
input: 
ABDH##I##E##CF#J##G##

output: 
node1: A ,left child:B ,right child:C 
node2: B ,left child:D ,right child:E 
node3: C ,left child:F ,right child:G 
node4: D ,left child:H ,right child:I 
node5: E ,left child:- ,right child:- 
node6: F ,left child:- ,right child:J 
node7: G ,left child:- ,right child:- 
node8: H ,left child:- ,right child:- 
node9: I ,left child:- ,right child:- 
node10: J ,left child:- ,right child:-
The result of PreOrder:
A B D H I E C F J G 
The result of InOrder:
H D I B E A F J C G 
The result of PostOrder:
H I D E B J F G C A 
The result of LeverOrder:
A B C D E F G H I J
The result of PreOrder_Stack:
A B D H I E C F J G
The result of InOrder_Stack:
H D I B E A F J C G
The result of PostOrder_Stack:
H I D E B J F G C A
The binary is not a complete Tree
The width of this binary tree is 4


test2 
input: 
ABDH##I##EJ###CF##G##
output:
node1: A ,left child:B ,right child:C
node2: B ,left child:D ,right child:E
node3: C ,left child:F ,right child:G
node4: D ,left child:H ,right child:I
node5: E ,left child:J ,right child:-
node6: F ,left child:- ,right child:-
node7: G ,left child:- ,right child:-
node8: H ,left child:- ,right child:-
node9: I ,left child:- ,right child:-
node10: J ,left child:- ,right child:-
The result of PreOrder:
A B D H I E J C F G
The result of InOrder:
H D I B J E A F C G
The result of PostOrder:
H I D J E B F G C A
The result of LeverOrder:
A B C D E F G H I J
The result of PreOrder_Stack:
A B D H I E J C F G
The result of InOrder_Stack:
H D I B J E A F C G
The result of PostOrder_Stack:
H I D J E B F G C A
The binary is a complete Tree
The width of this binary tree is 4