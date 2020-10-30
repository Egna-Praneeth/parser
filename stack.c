/*
Group no.: 11
Group member names and IDs:
Aditya V. Bodade
2018A7PS0256P

Egna Praneeth Gummana
2018A7PS0284P

Yogya Modi
2018A7PS0235P

Kartikaya Sharma
2018A7PS0386P

*/
#include "metadata.h"

bool isEmpty(){ 
    if(stack == NULL)
        return true;
    return false; 
} 
  
void push(bool is_term, Symbol data, int ruleno, TreeNode* parent){ 
    Stack* temp = (Stack*)malloc(sizeof(Stack)); 
    temp -> data = data;
    temp -> is_term = is_term; 
    temp -> ruleno = ruleno;
    temp -> parent = parent;
    temp -> next = stack;
    stack = temp;
} 

void pop(){ 
    if(isEmpty())
        return;
    Stack* temp = stack; 
    stack = stack -> next; 
    free(temp); 
} 
  
Stack* peek(){ 
    if(isEmpty()) 
        return NULL ;
    Stack* node = (Stack*) malloc(sizeof(Stack));
    *node = *stack;
    node->next = NULL;
    return node; 
} 


//int pushRule(Grammar* G, TreeNode* parent, Symbol symbol, int searchfrom);
//assuming that the stack stack send is
int pushNextRule(Grammar** G, TreeNode* parentlink, int ruleno, Token** tkptr){
    //assuming push rule returns -1 on error.
   int i =  pushRule(G, parentlink, parentlink->symbol, ruleno + 1);
   if(i == -1){
       removeAndReplace(parentlink->parent, G, parentlink->ruleno, tkptr);
   }
}
//return 1 on success


