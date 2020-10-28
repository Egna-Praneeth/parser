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

TreeNode* createNode(){
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
    return addtoLL(top->parent , newnode);
}

void removeAndReplace(TreeNode* parent, Grammar* G,  int ruleno, Token* tkptr){
    popRule(ruleno);
    deleteRule(parent, &tkptr);
    pushNextRule(stack, G, parent, ruleno);
}