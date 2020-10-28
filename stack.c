#include "metadata.h"

bool isEmpty(){ 
    if(top == NULL)
        return true;
    return false; 
} 
  
void push(bool is_term, Symbol data, int ruleno, Treenode* parent){ 
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