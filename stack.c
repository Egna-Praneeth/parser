#include "metadata.h"
struct StackNode* newNode(bool is_term, Symbol data, int ruleindex, struct treenode* parenttreelink) 
{ 
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
    stackNode->data = data;
    stackNode-> is_term = is_term; 
    stackNode-> ruleindex = ruleindex;
    stackNode -> parenttreelink = parenttreelink;
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, bool is_term, Symbol data, int ruleindex, struct treenode* parenttreelink) 
{ 
    struct StackNode* stackNode = newNode(is_term,data, ruleindex, parenttreelink); 
    stackNode->next = *root; 
    *root = stackNode; 
    printf("%d pushed to stack\n", data); 
} 
  
int pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) 
        return INT_MIN; 
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    Symbol popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
int peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) 
        return INT_MIN; 
    return root->data; 
} 