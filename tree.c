#include "metadata.h"

TreeNode* addendLL(TreeNode* parent, TreeNode* newnode){
    if(parent->child == NULL) {
        parent->child = newnode;
        return newnode;
    }
    TreeNode* temp = parent->child;
    while(temp->nextsib){
        temp = temp->nextsib;
    }
    temp->nextsib = newnode;
    return newnode;
}

TreeNode* createNode(struct StackNode* top){
    if(top->data == S){
        top->parent = (TreeNode*)malloc(sizeof(TreeNode));
        top->parent->ruleno = top->ruleno;
        top->parent->is_term = top->is_term;
        top->parent->parent = NULL;
        top->parent->child = NULL;
        top->parent->nextsib = NULL;
        return top->parent;
    }
    TreeNode* newnode = (TreeNode*) malloc(sizeof(TreeNode));
    newnode->ruleno = top->ruleno;
    newnode->is_term = top->is_term;
    newnode->parent = top->parent;
    newnode->child = NULL;
    newnode->nextsib = NULL;
    return addendLL(top->parent , newnode);
}

void removeAndReplace(TreeNode* parent, Grammar* G,  int ruleno, Token* tkptr){
    popRule(ruleno);
    deleteRule(parent, &tkptr);
    pushNextRule(parent, G, ruleno, tkptr);
}

int countTerminals(TreeNode* P){
    if(P->child == NULL)return 0;
    int count = 0;
    TreeNode* temp = P->child;
    while(temp){
        if(temp->is_term == 1) count++;
        else count += countTerminals(temp);
        temp = temp->nextsib;
    }
    return count;
}
void deleteLL(TreeNode* parent){
    if(parent->child == NULL)return;
    TreeNode* temp = parent->child, *temp2;

    while(temp){
        deleteLL(temp);
        temp2 = temp;
        temp = temp->nextsib;
        free(temp2);
    }
}
TreeNode* deleteRule(TreeNode* parent, Token** tkptr){
    int num = countTerminals(parent);
    //go back in tkptr
    *tkptr = *tkptr - num*(sizeof(Token));
    deleteLL(parent);
}