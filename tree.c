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
    if( top->data == S) {
        top->parenttreelink = (TreeNode* ) malloc(sizeof(TreeNode));
        top->parenttreelink->ruleindex = top->ruleindex;
        top->parenttreelink->is_term = top->is_term;
        top->parenttreelink->parent = NULL;
        top->parenttreelink->child = NULL;
        top->parenttreelink->nextsib = NULL;
        return top->parenttreelink;
    }
    TreeNode* newnode = (TreeNode*) malloc(sizeof(TreeNode));
    newnode->ruleindex = top->ruleindex;
    newnode->is_term = top->is_term;
    newnode->parent = top->parenttreelink;
    newnode->child = NULL;
    newnode->nextsib = NULL;
    return addtoLL(top->parenttreelink , newnode);
}

void removeAndReplace(struct StackNode* stack, TreeNode* parent, Grammar* G,  int ruleindex, Token* tkptr){
    popRule(stack, ruleindex);
    deleteRule(parent, &tkptr);
    pushNextRule(stack, G, parent, ruleindex);
}