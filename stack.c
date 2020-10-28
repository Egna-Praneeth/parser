#include "metadata.h"

bool isEmpty(){ 
    if(top == NULL)
        return true;
    return false; 
} 
  
void push(bool is_term, Symbol data, int ruleno, TreeNode* parent){ 
    Stack* temp = (Stack*)malloc(sizeof(Stack)); 
    temp -> data = data;
    temp -> is_term = is_term; 
    temp -> ruleno = ruleno;
    temp -> parent = parent;
    temp -> next = top;
    top = temp;
} 

void pop(){ 
    if(isEmpty())
        return;
    Stack* temp = top; 
    top = top -> next; 
    free(temp); 
} 
  
Symbol peek(){ 
    if(isEmpty()) 
        return -1; 
    return top -> data; 
} 


//int pushRule(Grammar* G, TreeNode* parent, Symbol symbol, int searchfrom);
//assuming that the stack top send is
int pushNextRule(Grammar* G, TreeNode* parentlink, int ruleno){
    //assuming push rule returns -1 on error.
   int i =  pushRule(G, parentlink, parentlink->symbol, ruleno + 1);
   if(i == -1){
       removeAndReplace(parentlink->parent, G);
   }
}
//return 1 on success