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

TreeNode* createNode(struct StackNode* node){
    if(node->data == S){
        
        return node->parent;
    }
    TreeNode* newnode = (TreeNode*) malloc(sizeof(TreeNode));
    newnode->symbol = node->data;
    newnode->ruleno = node->ruleno;
    newnode->is_term = node->is_term;
    newnode->parent = node->parent;
    newnode->child = NULL;
    newnode->nextsib = NULL;
    return addendLL(node->parent , newnode);
}

void removeAndReplace(TreeNode* parent, Grammar* G,  int ruleno, Token** tkptr){
    popRule(ruleno);
    deleteRule(parent, tkptr);
    pushNextRule(G, parent, ruleno, tkptr);
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
    parent->child = NULL;
}
TreeNode* deleteRule(TreeNode* parent, Token** tkptr){
    int num = countTerminals(parent);
    //go back in tkptr
        while(num){
        *tkptr = (*tkptr)->prev;
        num--;
        }


    deleteLL(parent);
}